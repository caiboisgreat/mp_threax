"""CPython-style `ssl` wrapper for this firmware.

The actual TLS implementation is provided by MicroPython's built-in `tls`
module (backed by mbedTLS). This wrapper exists because many libraries expect
`import ssl`.

Note: This port currently has no true random source integrated; TLS handshakes
may fail until a proper entropy source is added.
"""

import tls as _tls


class SSLError(OSError):
    pass


# Re-export common symbols.
SSLContext = _tls.SSLContext

PROTOCOL_TLS_CLIENT = _tls.PROTOCOL_TLS_CLIENT
PROTOCOL_TLS_SERVER = _tls.PROTOCOL_TLS_SERVER

CERT_NONE = _tls.CERT_NONE
CERT_OPTIONAL = _tls.CERT_OPTIONAL
CERT_REQUIRED = _tls.CERT_REQUIRED


def create_default_context(*args, **kwargs):
    # Minimal default: client context.
    # (We ignore purpose/cafile/capath/cadata kwargs for now.)
    return SSLContext(PROTOCOL_TLS_CLIENT)


def wrap_socket(sock, server_side=False, do_handshake_on_connect=True, server_hostname=None,
                ssl_context=None, **kwargs):
    # CPython-compatible convenience wrapper.
    if ssl_context is None:
        ssl_context = create_default_context()
    return ssl_context.wrap_socket(
        sock,
        server_side=server_side,
        do_handshake_on_connect=do_handshake_on_connect,
        server_hostname=server_hostname,
    )
