"""Frozen stub for CPython-compatible `socket` module.

This project currently builds MicroPython without a network stack.
The goal of this module is to satisfy `import socket` for code that
optionally uses networking.

When a real network backend is integrated (eg lwIP + NIC/PPP/WiFi), this
module should be replaced by the proper C-backed implementation.
"""

import errno


class error(OSError):
    pass


# Common constants used by application code.
AF_INET = 2
AF_INET6 = 10
SOCK_STREAM = 1
SOCK_DGRAM = 2
SOCK_RAW = 3

SOL_SOCKET = 1


def _not_supported(*args, **kwargs):
    raise OSError(errno.ENOTSUP)


socket = _not_supported
create_connection = _not_supported
getaddrinfo = _not_supported
gethostbyname = _not_supported
gethostbyname_ex = _not_supported
inet_aton = _not_supported
inet_ntoa = _not_supported
