# MicroPython btree verification script for STM32 + VFS FAT (/sd)
# Usage (from REPL):
#   import sys
#   sys.path.append('/sd')  # if you copy this file to SD
#   import btree_verify

import os
import btree

DB_PATH = "/sd/btree_test.db"


def hexdump(b):
    return " ".join("%02x" % x for x in b)


def run():
    # Remove any previous DB file
    try:
        os.remove(DB_PATH)
    except OSError:
        pass

    # Create+open underlying file in binary read/write
    f = open(DB_PATH, "w+b")

    # Open btree database on that stream
    db = btree.open(f)

    # Basic put/get
    db[b"k1"] = b"v1"
    db[b"k2"] = b"v2"
    assert db[b"k1"] == b"v1"
    assert db.get(b"k2") == b"v2"
    assert db.get(b"missing") is None

    # Overwrite
    db[b"k1"] = b"v1b"
    assert db[b"k1"] == b"v1b"

    # Iterate keys in order
    keys = [k for k in db]
    assert keys == sorted(keys)

    # Close+flush
    db.flush()
    db.close()
    f.close()

    # Re-open and verify persistence
    f2 = open(DB_PATH, "r+b")
    db2 = btree.open(f2)
    assert db2[b"k1"] == b"v1b"
    assert db2[b"k2"] == b"v2"

    # Delete
    del db2[b"k2"]
    try:
        _ = db2[b"k2"]
        raise AssertionError("expected KeyError")
    except KeyError:
        pass

    db2.flush()
    db2.close()
    f2.close()

    print("btree OK:", DB_PATH)


if __name__ == "__main__":
    run()
