"""Frozen stub for MicroPython `_thread` module.

This firmware build runs MicroPython inside a single ThreadX thread, but does
not enable MicroPython's own multi-threading subsystem (MICROPY_PY_THREAD=0).

The goal is to satisfy `import _thread` for libraries that optionally use it.
Thread creation is not supported yet.
"""

import utime as time

class LockType:
    def __init__(self):
        self._locked = False

    def locked(self):
        return self._locked

    def acquire(self, waitflag=True):
        # Single-thread stub: emulate blocking by polling until unlocked.
        if self._locked:
            if not waitflag:
                return False
            while self._locked:
                time.sleep_ms(1)
        self._locked = True
        return True

    def release(self):
        if not self._locked:
            raise RuntimeError("release unlocked lock")
        self._locked = False

    def __enter__(self):
        self.acquire(True)
        return self

    def __exit__(self, exc_type, exc, tb):
        self.release()
        return False


def allocate_lock():
    return LockType()


def start_new_thread(*args, **kwargs):
    raise NotImplementedError


def get_ident():
    return 0


def stack_size(*args, **kwargs):
    # Not supported; return 0 like CPython's default-query behaviour.
    return 0


def exit():
    raise SystemExit
