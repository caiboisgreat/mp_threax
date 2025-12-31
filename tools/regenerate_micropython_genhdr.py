import argparse
import os
import subprocess
import sys
import xml.etree.ElementTree as ET
from pathlib import Path


def _empty_dir(dir_path: Path):
    if not dir_path.exists():
        return
    for child in dir_path.iterdir():
        if child.is_file():
            child.unlink()
        elif child.is_dir():
            # Avoid shutil.rmtree to keep dependencies minimal.
            _empty_dir(child)
            try:
                child.rmdir()
            except OSError:
                pass


def parse_uvprojx(uvprojx_path: Path):
    tree = ET.parse(uvprojx_path)
    root = tree.getroot()

    # Find the global C compiler controls (Cads/VariousControls)
    include_path_text = None
    define_text = ""
    misc_controls = ""

    for cads in root.iter("Cads"):
        vc = cads.find("VariousControls")
        if vc is None:
            continue
        ip = vc.findtext("IncludePath")
        if ip:
            include_path_text = ip
            define_text = vc.findtext("Define") or ""
            misc_controls = vc.findtext("MiscControls") or ""
            break

    if include_path_text is None:
        raise RuntimeError("Failed to find Cads/VariousControls/IncludePath in uvprojx")

    # Collect all MicroPython sources that are included in the project.
    mp_sources: list[Path] = []
    for file_node in root.iter("File"):
        fp = file_node.findtext("FilePath")
        if not fp:
            continue
        # Normalise Keil's backslashes.
        fp_norm = fp.replace("/", "\\")
        if "\\Middlewares\\micropython\\" not in fp_norm:
            continue
        if not fp_norm.lower().endswith((".c", ".cc", ".cpp", ".cxx")):
            continue
        mp_sources.append(Path(fp_norm))

    return include_path_text, define_text, misc_controls, mp_sources


def run(cmd: list[str], cwd: Path | None = None):
    p = subprocess.run(cmd, cwd=str(cwd) if cwd else None, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True)
    if p.returncode != 0:
        raise RuntimeError(f"Command failed ({p.returncode}): {' '.join(cmd)}\n\n{p.stdout}")
    return p.stdout


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--uvprojx", default=str(Path("MDK-ARM") / "mp_threadx.uvprojx"))
    ap.add_argument(
        "--armclang",
        default=r"D:\Program Files\Keil_v5\ARM\ARMCLANG\Bin\armclang.exe",
        help="Path to armclang.exe (used as preprocessor)",
    )
    ap.add_argument("--target", default="arm-arm-none-eabi")
    ap.add_argument("--cpu", default="cortex-m4")
    ap.add_argument("--thumb", action="store_true", default=True)
    ap.add_argument("--fpu", default="fpv4-sp-d16")
    ap.add_argument("--float-abi", default="hard")
    ap.add_argument("--verbose", action="store_true")
    args = ap.parse_args()

    workspace_root = Path(__file__).resolve().parents[1]
    uvprojx_path = (workspace_root / args.uvprojx).resolve()
    mdk_arm_dir = uvprojx_path.parent

    include_path_text, define_text, misc_controls, mp_sources_rel = parse_uvprojx(uvprojx_path)

    include_paths: list[Path] = []
    for p in include_path_text.split(";"):
        p = p.strip()
        if not p:
            continue
        include_paths.append((mdk_arm_dir / p).resolve())

    defines = [d.strip() for d in define_text.replace(";", ",").split(",") if d.strip()]
    # Keil/RTE commonly defines this; many projects rely on it.
    if "_RTE_" not in defines:
        defines.append("_RTE_")

    armclang = Path(args.armclang)
    if not armclang.exists():
        raise RuntimeError(f"armclang not found: {armclang}")

    genhdr_dir = workspace_root / "Middlewares" / "micropython" / "genhdr"
    genhdr_dir.mkdir(parents=True, exist_ok=True)

    # Resolve all sources relative to MDK-ARM dir (Keil project file paths are relative to MDK-ARM)
    mp_sources = [(mdk_arm_dir / p).resolve() for p in mp_sources_rel]

    # Preprocess sources into a single file for makeqstrdefs.py split.
    # (MicroPython's build calls this qstr.i.last.)
    pp_out = genhdr_dir / "qstr.i.last"
    pp_out.write_text("", encoding="utf-8")

    base_flags = [
        "-E",
        "-dD",
        f"--target={args.target}",
        f"-mcpu={args.cpu}",
        "-mthumb" if args.thumb else "",
        f"-mfpu={args.fpu}",
        f"-mfloat-abi={args.float_abi}",
    ]
    base_flags = [f for f in base_flags if f]

    # Ensure qstr/root pointers generation doesn't depend on existing generated headers.
    cpp_defines = ["NO_QSTR"] + defines

    inc_flags: list[str] = []
    for inc in include_paths:
        inc_flags += ["-I", str(inc)]

    def_flags: list[str] = []
    for d in cpp_defines:
        def_flags.append("-D" + d)

    misc_flags: list[str] = []
    if misc_controls:
        # For now, only keep simple tokens (e.g. -fgnu). Avoid passing Keil-specific flags.
        for tok in misc_controls.split():
            if tok.startswith("-"):
                misc_flags.append(tok)

    if args.verbose:
        print(f"Using {len(mp_sources)} MicroPython sources from {uvprojx_path}")
        print(f"Writing preprocessed output to {pp_out}")

    with pp_out.open("ab") as out_f:
        for src in mp_sources:
            cmd = [str(armclang)] + base_flags + misc_flags + inc_flags + def_flags + ["-xc", str(src)]
            if args.verbose:
                print("PP:", src)
            try:
                out = subprocess.check_output(cmd, cwd=str(workspace_root), stderr=subprocess.STDOUT)
            except subprocess.CalledProcessError as e:
                raise RuntimeError(f"Preprocess failed for {src}\n\n{e.output.decode(errors='replace')}")
            out_f.write(out)

    py_dir = workspace_root / "Middlewares" / "micropython" / "py"

    # 1) QSTR collection
    qstr_dir = genhdr_dir / "qstr"
    qstr_dir.mkdir(exist_ok=True)
    # Important: makeqstrdefs.py does not overwrite per-source output files
    # when the extracted output is empty, so stale entries can persist across
    # config changes unless we clear the directory.
    _empty_dir(qstr_dir)
    # Note: makeqstrdefs.py requires an output_file arg even for "split" (it's unused),
    # so we pass a dummy value "_".
    run(
        [sys.executable, str(py_dir / "makeqstrdefs.py"), "split", "qstr", str(pp_out), str(qstr_dir), "_"],
        cwd=workspace_root,
    )
    qstr_collected = genhdr_dir / "qstrdefs.collected.h"
    run([sys.executable, str(py_dir / "makeqstrdefs.py"), "cat", "qstr", "_", str(qstr_dir), str(qstr_collected)], cwd=workspace_root)

    # makeqstrdata.py expects QCFG(...) lines (from py/qstrdefs.h) to be present.
    # MicroPython's build does this by concatenating py/qstrdefs.h + port qstrdefs
    # + collected Q(...) lines, quoting Q(...) lines to protect them from the CPP,
    # running the CPP, then unquoting.
    qstrdefs_py = py_dir / "qstrdefs.h"
    qstrdefs_port = workspace_root / "Middlewares" / "micropython" / "py_port" / "qstrdefsport.h"

    qstr_concat = genhdr_dir / "qstrdefs.concat.h"
    qstr_concat_quoted = genhdr_dir / "qstrdefs.concat.quoted.h"
    qstr_preprocessed_for_data = genhdr_dir / "qstrdefs.preprocessed.h"

    concat_parts: list[Path] = [qstrdefs_py]
    if qstrdefs_port.exists():
        concat_parts.append(qstrdefs_port)
    concat_parts.append(qstr_collected)

    with qstr_concat.open("wb") as out_f:
        for idx, part in enumerate(concat_parts):
            if idx:
                out_f.write(b"\n")
            out_f.write(part.read_bytes())
            out_f.write(b"\n")

    # Quote Q(...) lines so the preprocessor doesn't interpret them.
    with qstr_concat.open("rt", encoding="utf-8", errors="replace") as in_f, qstr_concat_quoted.open(
        "wt", encoding="utf-8", newline="\n"
    ) as out_f:
        for line in in_f:
            stripped = line.strip()
            if stripped.startswith("Q(") and stripped.endswith(")"):
                out_f.write('"' + stripped + '"\n')
            else:
                out_f.write(line)

    # Preprocess with normal build defines (no NO_QSTR needed here).
    cpp_defines_for_data = defines
    def_flags_for_data = ["-D" + d for d in cpp_defines_for_data]
    cmd = [str(armclang)] + base_flags + misc_flags + inc_flags + def_flags_for_data + ["-xc", str(qstr_concat_quoted)]
    preprocessed = subprocess.check_output(cmd, cwd=str(workspace_root), stderr=subprocess.STDOUT).decode(
        "utf-8", errors="replace"
    )

    # Unquote the protected Q(...) lines.
    with qstr_preprocessed_for_data.open("wt", encoding="utf-8", newline="\n") as out_f:
        for line in preprocessed.splitlines():
            s = line.strip()
            if s.startswith('"Q(') and s.endswith(')"'):
                out_f.write(s[1:-1] + "\n")
            else:
                out_f.write(line + "\n")

    qstr_generated = genhdr_dir / "qstrdefs.generated.h"
    qstr_data = run([sys.executable, str(py_dir / "makeqstrdata.py"), str(qstr_preprocessed_for_data)], cwd=workspace_root)
    qstr_generated.write_text(qstr_data, encoding="utf-8")

    # 2) Root pointers
    rp_dir = genhdr_dir / "root_pointer"
    rp_dir.mkdir(exist_ok=True)
    _empty_dir(rp_dir)
    run(
        [
            sys.executable,
            str(py_dir / "makeqstrdefs.py"),
            "split",
            "root_pointer",
            str(pp_out),
            str(rp_dir),
            "_",
        ],
        cwd=workspace_root,
    )
    rp_collected = genhdr_dir / "root_pointers.collected.h"
    run([sys.executable, str(py_dir / "makeqstrdefs.py"), "cat", "root_pointer", "_", str(rp_dir), str(rp_collected)], cwd=workspace_root)

    rp_generated = genhdr_dir / "root_pointers.h"
    rp_text = run([sys.executable, str(py_dir / "make_root_pointers.py"), str(rp_collected)], cwd=workspace_root)
    rp_generated.write_text(rp_text, encoding="utf-8")

    # 3) Module registrations
    mod_dir = genhdr_dir / "module"
    mod_dir.mkdir(exist_ok=True)
    _empty_dir(mod_dir)
    run(
        [sys.executable, str(py_dir / "makeqstrdefs.py"), "split", "module", str(pp_out), str(mod_dir), "_"],
        cwd=workspace_root,
    )
    mod_collected = genhdr_dir / "moduledefs.collected.h"
    run([sys.executable, str(py_dir / "makeqstrdefs.py"), "cat", "module", "_", str(mod_dir), str(mod_collected)], cwd=workspace_root)

    moduledefs_h = genhdr_dir / "moduledefs.h"
    mod_text = run([sys.executable, str(py_dir / "makemoduledefs.py"), str(mod_collected)], cwd=workspace_root)
    moduledefs_h.write_text(mod_text, encoding="utf-8")

    print("Regenerated MicroPython genhdr:")
    print(f"- {qstr_generated}")
    print(f"- {rp_generated}")
    print(f"- {moduledefs_h}")


if __name__ == "__main__":
    main()
