"""
MicroPython driver for the official LCD160CR display
https://store.micropython.org/product/LCD160CRv1.0

MIT license; Copyright (c) 2017-2023 Damien P. George
"""

from micropython import const
from time import sleep_ms
import machine

try:
    Pin = machine.Pin
    I2C = machine.I2C
    SPI = machine.SPI
except AttributeError:
    Pin = None
    I2C = None
    SPI = None

try:
    SoftI2C = machine.SoftI2C
except AttributeError:
    SoftI2C = None

try:
    SoftSPI = machine.SoftSPI
except AttributeError:
    SoftSPI = None

# Constants for orientation
PORTRAIT = const(0x00)
LANDSCAPE = const(0x01)
PORTRAIT_UPSIDEDOWN = const(0x02)
LANDSCAPE_UPSIDEDOWN = const(0x03)

# Constants for startup decoration
STARTUP_DECO_NONE = const(0x00)
STARTUP_DECO_MLOGO = const(0x01)
STARTUP_DECO_INFO = const(0x02)


class LCD160CR:
    """Driver for the LCD160CR display."""

    @staticmethod
    def rgb(r, g, b):
        """Convert r, g, b values (0-255) to a 16-bit 565 encoded color."""
        return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3)

    def __init__(self, connect=None, *, pwr=None, i2c=None, spi=None, i2c_addr=0x62):
        """
        Initialize the LCD160CR display.
        
        Args:
            connect: Position where display is connected ('X', 'Y', 'XY', or 'YX')
            pwr: Pin object for display power control
            i2c: I2C object for display communication
            spi: SPI object for fast pixel data transfer
            i2c_addr: I2C address of the display (default 0x62/98)
        """
        if connect is not None:
            if Pin is None:
                raise ImportError('machine.Pin not available in this port')
            # Auto-configure based on position
            if connect == 'X':
                self.pwr = Pin('X4', Pin.OUT) if pwr is None else pwr
                if i2c is None:
                    if I2C is not None:
                        self.i2c = I2C('X')
                    elif SoftI2C is not None:
                        self.i2c = SoftI2C(scl=Pin('X9'), sda=Pin('X10'))
                    else:
                        raise ImportError('machine.I2C/SoftI2C not available in this port')
                else:
                    self.i2c = i2c
                if spi is None:
                    if SPI is not None:
                        self.spi = SPI('X')
                    elif SoftSPI is not None:
                        self.spi = SoftSPI(sck=Pin('X6'), mosi=Pin('X8'), miso=Pin('X7'))
                    else:
                        raise ImportError('machine.SPI/SoftSPI not available in this port')
                else:
                    self.spi = spi
            elif connect == 'Y':
                self.pwr = Pin('Y4', Pin.OUT) if pwr is None else pwr
                if i2c is None:
                    if I2C is not None:
                        self.i2c = I2C('Y')
                    elif SoftI2C is not None:
                        self.i2c = SoftI2C(scl=Pin('Y9'), sda=Pin('Y10'))
                    else:
                        raise ImportError('machine.I2C/SoftI2C not available in this port')
                else:
                    self.i2c = i2c
                if spi is None:
                    if SPI is not None:
                        self.spi = SPI('Y')
                    elif SoftSPI is not None:
                        self.spi = SoftSPI(sck=Pin('Y6'), mosi=Pin('Y8'), miso=Pin('Y7'))
                    else:
                        raise ImportError('machine.SPI/SoftSPI not available in this port')
                else:
                    self.spi = spi
            elif connect == 'XY':
                self.pwr = Pin('X4', Pin.OUT) if pwr is None else pwr
                if i2c is None:
                    if I2C is not None:
                        self.i2c = I2C('Y')
                    elif SoftI2C is not None:
                        self.i2c = SoftI2C(scl=Pin('Y9'), sda=Pin('Y10'))
                    else:
                        raise ImportError('machine.I2C/SoftI2C not available in this port')
                else:
                    self.i2c = i2c
                if spi is None:
                    if SPI is not None:
                        self.spi = SPI('X')
                    elif SoftSPI is not None:
                        self.spi = SoftSPI(sck=Pin('X6'), mosi=Pin('X8'), miso=Pin('X7'))
                    else:
                        raise ImportError('machine.SPI/SoftSPI not available in this port')
                else:
                    self.spi = spi
            elif connect == 'YX':
                self.pwr = Pin('Y4', Pin.OUT) if pwr is None else pwr
                if i2c is None:
                    if I2C is not None:
                        self.i2c = I2C('X')
                    elif SoftI2C is not None:
                        self.i2c = SoftI2C(scl=Pin('X9'), sda=Pin('X10'))
                    else:
                        raise ImportError('machine.I2C/SoftI2C not available in this port')
                else:
                    self.i2c = i2c
                if spi is None:
                    if SPI is not None:
                        self.spi = SPI('Y')
                    elif SoftSPI is not None:
                        self.spi = SoftSPI(sck=Pin('Y6'), mosi=Pin('Y8'), miso=Pin('Y7'))
                    else:
                        raise ImportError('machine.SPI/SoftSPI not available in this port')
                else:
                    self.spi = spi
            else:
                raise ValueError('unknown connect value')
        else:
            # Use provided parameters
            if pwr is None or i2c is None or spi is None:
                raise ValueError('must specify either connect or pwr,i2c,spi')
            self.pwr = pwr
            self.i2c = i2c
            self.spi = spi

        self.i2c_addr = i2c_addr
        
        # Display dimensions (updated by set_orient)
        self.w = 160
        self.h = 128

        # Power on the display
        self.pwr.value(1)
        sleep_ms(10)
        
        # Initialize the display
        self._send_cmd(0x01, b'\x00')  # Reset
        sleep_ms(50)

    def _send_cmd(self, cmd, data=b''):
        """Send a command to the display via I2C."""
        buf = bytearray(len(data) + 1)
        buf[0] = cmd
        buf[1:] = data
        self.i2c.writeto(self.i2c_addr, buf)

    def _recv_cmd(self, cmd, n_data):
        """Send a command and receive response via I2C."""
        self.i2c.writeto(self.i2c_addr, bytes([cmd]))
        return self.i2c.readfrom(self.i2c_addr, n_data)

    def set_power(self, on):
        """Turn the display on (True) or off (False)."""
        self._send_cmd(0x02, bytes([0x01 if on else 0x00]))

    def set_orient(self, orient):
        """Set the orientation of the display."""
        self._send_cmd(0x03, bytes([orient]))
        if orient in (PORTRAIT, PORTRAIT_UPSIDEDOWN):
            self.w, self.h = 160, 128
        else:
            self.w, self.h = 128, 160

    def set_brightness(self, value):
        """Set the brightness (0-31)."""
        self._send_cmd(0x04, bytes([value & 0x1F]))

    def set_pen(self, line, fill):
        """Set the pen line and fill colors (16-bit RGB565)."""
        self._send_cmd(0x10, bytes([line >> 8, line & 0xFF, fill >> 8, fill & 0xFF]))

    def erase(self):
        """Erase the entire screen with the current fill color."""
        self._send_cmd(0x20)

    def dot(self, x, y):
        """Draw a single pixel at (x, y) using the pen line color."""
        self._send_cmd(0x21, bytes([x, y]))

    def rect(self, x, y, w, h):
        """Draw a rectangle with outline and fill."""
        self._send_cmd(0x22, bytes([x, y, w, h]))

    def rect_outline(self, x, y, w, h):
        """Draw a rectangle outline only."""
        self._send_cmd(0x23, bytes([x, y, w, h]))

    def rect_interior(self, x, y, w, h):
        """Draw a filled rectangle."""
        self._send_cmd(0x24, bytes([x, y, w, h]))

    def line(self, x1, y1, x2, y2):
        """Draw a line from (x1, y1) to (x2, y2)."""
        self._send_cmd(0x25, bytes([x1, y1, x2, y2]))

    def dot_no_clip(self, x, y):
        """Draw a pixel without clipping checks (faster)."""
        self._send_cmd(0x31, bytes([x, y]))

    def rect_no_clip(self, x, y, w, h):
        """Draw a rectangle without clipping checks."""
        self._send_cmd(0x32, bytes([x, y, w, h]))

    def rect_outline_no_clip(self, x, y, w, h):
        """Draw a rectangle outline without clipping checks."""
        self._send_cmd(0x33, bytes([x, y, w, h]))

    def rect_interior_no_clip(self, x, y, w, h):
        """Draw a filled rectangle without clipping checks."""
        self._send_cmd(0x34, bytes([x, y, w, h]))

    def line_no_clip(self, x1, y1, x2, y2):
        """Draw a line without clipping checks."""
        self._send_cmd(0x35, bytes([x1, y1, x2, y2]))

    def set_text_color(self, fg, bg):
        """Set the text foreground and background colors."""
        self._send_cmd(0x40, bytes([fg >> 8, fg & 0xFF, bg >> 8, bg & 0xFF]))

    def set_font(self, font, scale=0, bold=0, trans=0, scroll=0):
        """Set the font and its properties."""
        attr = (scale & 3) | ((bold & 1) << 2) | ((trans & 1) << 3) | ((scroll & 1) << 4)
        self._send_cmd(0x41, bytes([font, attr]))

    def set_pos(self, x, y):
        """Set the cursor position for text."""
        self._send_cmd(0x42, bytes([x, y]))

    def write(self, s):
        """Write text to the display at the current cursor position."""
        if isinstance(s, str):
            s = s.encode('utf-8')
        # Send text in chunks
        for i in range(0, len(s), 32):
            chunk = s[i:i+32]
            self._send_cmd(0x43, chunk)

    def is_touched(self):
        """Check if the screen is currently being touched."""
        b = self._recv_cmd(0x50, 1)
        return b[0] != 0

    def get_touch(self):
        """Get the touch status and position."""
        b = self._recv_cmd(0x51, 4)
        return b[0], b[1] | (b[2] << 8), b[3]

    def set_spi_win(self, x, y, w, h):
        """Set the window for SPI pixel data transfer."""
        self._send_cmd(0x60, bytes([x, y, w, h]))

    def fast_spi(self, flush=True):
        """Prepare for fast SPI pixel data transfer."""
        if flush:
            # Ensure previous I2C commands are processed
            sleep_ms(1)
        return self.spi

    def show_framebuf(self, buf):
        """Display a framebuffer on the screen."""
        self.set_spi_win(0, 0, self.w, self.h)
        spi = self.fast_spi()
        spi.write(buf)

    def set_pixel(self, x, y, c):
        """Set a single pixel to the specified color."""
        self._send_cmd(0x70, bytes([x, y, c >> 8, c & 0xFF]))

    def get_pixel(self, x, y):
        """Get the color of a single pixel."""
        b = self._recv_cmd(0x71, 2)
        return (b[0] << 8) | b[1]

    def get_line(self, x, y, buf):
        """Read a line of pixels into a buffer."""
        self._send_cmd(0x72, bytes([x, y, len(buf) // 2]))
        self.i2c.readfrom_into(self.i2c_addr, buf)

    def screen_dump(self, buf, x=0, y=0, w=None, h=None):
        """Dump a region of the screen into a buffer."""
        if w is None:
            w = self.w - x
        if h is None:
            h = self.h - y
        
        line_buf = bytearray(w * 2 + 1)
        i = 0
        for yy in range(y, y + h):
            self.get_line(x, yy, line_buf)
            buf[i:i + w * 2] = line_buf[1:]
            i += w * 2

    def screen_load(self, buf):
        """Load a full screen image from a buffer."""
        self.set_spi_win(0, 0, self.w, self.h)
        spi = self.fast_spi()
        spi.write(buf)

    def touch_config(self, calib=False, save=False, irq=None):
        """Configure touch panel settings."""
        data = bytes([
            0x01 if calib else 0x00,
            0x01 if save else 0x00,
            0xFF if irq is None else (irq & 0xFF)
        ])
        self._send_cmd(0x80, data)

    def set_scroll(self, on):
        """Enable or disable scrolling."""
        self._send_cmd(0x90, bytes([0x01 if on else 0x00]))

    def set_scroll_win(self, win, x=-1, y=0, w=0, h=0, vec=0, pat=0, fill=0x07e0, color=0):
        """Configure a scrolling window region."""
        data = bytes([
            win & 7,
            x & 0xFF,
            y,
            w,
            h,
            vec & 0xFF,
            pat & 0xFF,
            fill >> 8, fill & 0xFF,
            color >> 8, color & 0xFF
        ])
        self._send_cmd(0x91, data)

    def set_scroll_buf(self, win, buf):
        """Set the buffer for a scroll window."""
        # This is a simplified version; full implementation would handle buffer transfer
        pass

    def jpeg(self, buf):
        """Display a JPEG image."""
        # Start JPEG transfer
        self._send_cmd(0xA0, bytes([len(buf) >> 8, len(buf) & 0xFF]))
        # Send JPEG data in chunks
        for i in range(0, len(buf), 32):
            chunk = buf[i:i+32]
            self._send_cmd(0xA1, chunk)

    def jpeg_start(self, total_len):
        """Start JPEG image transfer."""
        self._send_cmd(0xA0, bytes([total_len >> 8, total_len & 0xFF]))

    def jpeg_data(self, buf):
        """Send JPEG image data chunk."""
        self._send_cmd(0xA1, buf)

    def feed_wdt(self):
        """Feed the watchdog timer."""
        self._send_cmd(0xB0)

    def reset(self):
        """Reset the display."""
        self._send_cmd(0x01, b'\x00')
        sleep_ms(50)

    def set_uart_baudrate(self, baudrate):
        """Set the UART baudrate for the display."""
        b = baudrate & 0xFFFFFFFF
        self._send_cmd(0xC0, bytes([b >> 24, (b >> 16) & 0xFF, (b >> 8) & 0xFF, b & 0xFF]))

    def set_startup_deco(self, value):
        """Set startup decoration flags."""
        self._send_cmd(0xC1, bytes([value & 0xFF]))

    def save_to_flash(self):
        """Save current settings to flash."""
        self._send_cmd(0xC2)

    def set_i2c_addr(self, addr):
        """Set the I2C address of the display."""
        self._send_cmd(0xC3, bytes([addr & 0xFE]))
        self.i2c_addr = addr
