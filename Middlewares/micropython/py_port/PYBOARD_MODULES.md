# Pyboard Board-Specific Modules

This document describes the pyboard-specific modules that have been ported to this ThreadX-based MicroPython implementation.

## Overview

The pyboard board-specific libraries provide access to hardware-specific features and legacy APIs from the official MicroPython pyboard. This port includes three main modules:

1. **`pyb`** - Pyboard legacy API for timing, delays, and system information
2. **`stm`** - Low-level STM32 register access
3. **`lcd160cr`** - Driver for the LCD160CR display (Python module)

## Module: `pyb`

The `pyb` module provides the traditional pyboard API for basic system functions.

### Functions

#### `pyb.info([dump_alloc_table])`
Print information about the board and system.

```python
import pyb
pyb.info()
# Output:
# --------------------------------
# MicroPython on ThreadX
# Board: PYBASE
# MCU: STM32F405RG6
# --------------------------------
```

#### `pyb.delay(ms)`
Delay for the given number of milliseconds.

```python
pyb.delay(1000)  # Delay for 1 second
```

#### `pyb.udelay(us)`
Delay for the given number of microseconds.

```python
pyb.udelay(100)  # Delay for 100 microseconds
```

#### `pyb.millis()`
Returns the number of milliseconds since boot.

```python
start = pyb.millis()
# ... do something ...
elapsed = pyb.millis() - start
```

#### `pyb.micros()`
Returns the number of microseconds since boot.

```python
start = pyb.micros()
# ... do something ...
elapsed = pyb.micros() - start
```

#### `pyb.elapsed_millis(start)`
Returns the number of milliseconds that have elapsed since the given start time.

```python
start = pyb.millis()
# ... do something ...
elapsed = pyb.elapsed_millis(start)
```

#### `pyb.elapsed_micros(start)`
Returns the number of microseconds that have elapsed since the given start time.

```python
start = pyb.micros()
# ... do something ...
elapsed = pyb.elapsed_micros(start)
```

## Module: `stm`

The `stm` module provides low-level access to STM32 peripheral registers and memory.

### Memory Access Objects

#### `stm.mem8[addr]`
Access memory as 8-bit (byte) values.

```python
import stm

# Read a byte from address 0x40021000 (RCC base)
value = stm.mem8[0x40021000]

# Write a byte
stm.mem8[0x40021000] = 0xFF
```

#### `stm.mem16[addr]`
Access memory as 16-bit (half-word) values.

```python
# Read a 16-bit value
value = stm.mem16[0x40021000]

# Write a 16-bit value
stm.mem16[0x40021000] = 0x1234
```

#### `stm.mem32[addr]`
Access memory as 32-bit (word) values.

```python
# Read a 32-bit value
value = stm.mem32[0x40021000]

# Write a 32-bit value
stm.mem32[0x40021000] = 0x12345678
```

### Peripheral Base Addresses

The `stm` module provides constants for all major STM32F405 peripheral base addresses:

#### GPIO Ports
- `stm.GPIOA`, `stm.GPIOB`, `stm.GPIOC`, `stm.GPIOD`, `stm.GPIOE`, `stm.GPIOF`, `stm.GPIOG`, `stm.GPIOH`

Example:
```python
# Read GPIOA->IDR (input data register)
gpioa_idr = stm.mem32[stm.GPIOA + 0x10]

# Set GPIOA->BSRR (bit set/reset register)
stm.mem32[stm.GPIOA + 0x18] = (1 << 5)  # Set pin 5
```

#### Timers
- `stm.TIM1`, `stm.TIM2`, `stm.TIM3`, `stm.TIM4`, `stm.TIM5`, `stm.TIM6`, `stm.TIM7`, `stm.TIM8`, etc.

#### UARTs/USARTs
- `stm.USART1`, `stm.USART2`, `stm.USART3`, `stm.UART4`, `stm.UART5`, `stm.USART6`

#### SPI
- `stm.SPI1`, `stm.SPI2`, `stm.SPI3`

#### I2C
- `stm.I2C1`, `stm.I2C2`, `stm.I2C3`

#### ADC/DAC
- `stm.ADC1`, `stm.ADC2`, `stm.ADC3`, `stm.DAC`

#### Other Peripherals
- `stm.RCC` - Reset and Clock Control
- `stm.SYSCFG` - System Configuration
- `stm.PWR` - Power Control
- `stm.DMA1`, `stm.DMA2` - DMA Controllers
- `stm.CAN1`, `stm.CAN2` - CAN Bus
- `stm.USB_OTG_FS`, `stm.USB_OTG_HS` - USB OTG
- `stm.SDIO` - SD Card Interface
- `stm.RTC` - Real-Time Clock
- `stm.IWDG`, `stm.WWDG` - Watchdog Timers

## Module: `lcd160cr`

The `lcd160cr` module provides a Python driver for the official MicroPython LCD160CR display.

### Quick Start

```python
import lcd160cr

# Initialize the display
lcd = lcd160cr.LCD160CR('X')  # Connected to X position

# Set orientation
lcd.set_orient(lcd160cr.PORTRAIT)

# Set pen colors
lcd.set_pen(lcd.rgb(255, 0, 0), lcd.rgb(0, 0, 0))

# Draw shapes
lcd.erase()
lcd.rect(10, 10, 50, 50)
lcd.line(0, 0, 160, 128)

# Display text
lcd.set_text_color(lcd.rgb(255, 255, 255), lcd.rgb(0, 0, 0))
lcd.set_font(1)
lcd.set_pos(0, 0)
lcd.write('Hello MicroPython!')

# Read touch
if lcd.is_touched():
    touching, x, y = lcd.get_touch()
    print(f"Touch at ({x}, {y})")
```

### Class: `LCD160CR`

#### Constructor

```python
lcd = lcd160cr.LCD160CR(connect='X', pwr=None, i2c=None, spi=None, i2c_addr=0x62)
```

Parameters:
- `connect`: Position where display is connected ('X', 'Y', 'XY', or 'YX')
- `pwr`: Pin object for power control (optional if using connect)
- `i2c`: I2C object for communication (optional if using connect)
- `spi`: SPI object for fast pixel transfer (optional if using connect)
- `i2c_addr`: I2C address of the display (default 0x62)

#### Static Methods

##### `LCD160CR.rgb(r, g, b)`
Convert RGB values (0-255) to a 16-bit 565-encoded color.

```python
red = lcd160cr.LCD160CR.rgb(255, 0, 0)
green = lcd160cr.LCD160CR.rgb(0, 255, 0)
blue = lcd160cr.LCD160CR.rgb(0, 0, 255)
```

#### Setup Methods

##### `lcd.set_power(on)`
Turn the display on (True) or off (False).

##### `lcd.set_orient(orient)`
Set the orientation of the display.

Constants:
- `lcd160cr.PORTRAIT`
- `lcd160cr.LANDSCAPE`
- `lcd160cr.PORTRAIT_UPSIDEDOWN`
- `lcd160cr.LANDSCAPE_UPSIDEDOWN`

##### `lcd.set_brightness(value)`
Set the brightness (0-31).

#### Drawing Methods

##### `lcd.set_pen(line, fill)`
Set the pen line and fill colors (16-bit RGB565).

##### `lcd.erase()`
Erase the entire screen with the current fill color.

##### `lcd.dot(x, y)`
Draw a single pixel at (x, y).

##### `lcd.rect(x, y, w, h)`
Draw a rectangle with outline and fill.

##### `lcd.rect_outline(x, y, w, h)`
Draw only the rectangle outline.

##### `lcd.rect_interior(x, y, w, h)`
Draw only the filled rectangle.

##### `lcd.line(x1, y1, x2, y2)`
Draw a line from (x1, y1) to (x2, y2).

#### Text Methods

##### `lcd.set_text_color(fg, bg)`
Set the text foreground and background colors.

##### `lcd.set_font(font, scale=0, bold=0, trans=0, scroll=0)`
Set the font and its properties.

##### `lcd.set_pos(x, y)`
Set the cursor position for text.

##### `lcd.write(s)`
Write text to the display.

#### Touch Methods

##### `lcd.is_touched()`
Check if the screen is currently being touched.

##### `lcd.get_touch()`
Get the touch status and position.

Returns: `(touching, x, y)` where touching is 0 or 1.

#### Pixel Access Methods

##### `lcd.set_pixel(x, y, c)`
Set a single pixel to the specified color.

##### `lcd.get_pixel(x, y)`
Get the color of a single pixel.

##### `lcd.screen_dump(buf, x=0, y=0, w=None, h=None)`
Dump a region of the screen into a buffer.

##### `lcd.screen_load(buf)`
Load a full screen image from a buffer.

#### Advanced Methods

##### `lcd.set_spi_win(x, y, w, h)`
Set the window for SPI pixel data transfer.

##### `lcd.fast_spi(flush=True)`
Prepare for fast SPI pixel data transfer. Returns the SPI object.

##### `lcd.show_framebuf(buf)`
Display a framebuffer on the screen.

```python
import framebuf

# Create a framebuffer
buf = bytearray(160 * 128 * 2)  # 16-bit color
fb = framebuf.FrameBuffer(buf, 160, 128, framebuf.RGB565)

# Draw to framebuffer
fb.fill(0)
fb.rect(10, 10, 50, 50, lcd.rgb(255, 0, 0))

# Show on display
lcd.show_framebuf(buf)
```

## Build Instructions

### Keil MDK-ARM Project

To enable these modules in your Keil project:

1. **Add source files to your project:**
   - `Middlewares/micropython/py_port/modpyb.c`
   - `Middlewares/micropython/py_port/modstm.c`

2. **Add the lcd160cr Python module to frozen modules:**
   - The `lcd160cr.py` file is located at `Middlewares/micropython/lib/lcd160cr/lcd160cr.py`
   - It will be automatically frozen into the firmware during the build process

3. **Ensure `mpconfigport.h` has these settings:**
   ```c
   #define MICROPY_PY_PYB (1)
   #define MICROPY_PY_STM (1)
   ```

4. **Rebuild the project** to regenerate QSTRs and compile the new modules.

## Usage Examples

### Example 1: Simple Timing

```python
import pyb

print("Starting...")
start = pyb.millis()
pyb.delay(1000)
print(f"Elapsed: {pyb.elapsed_millis(start)} ms")
```

### Example 2: Register Access

```python
import stm

# Read the chip ID from DBGMCU
chip_id = stm.mem32[0xE0042000]
print(f"Chip ID: 0x{chip_id:08X}")

# Blink LED by toggling GPIOA pin 5
while True:
    # Toggle PA5
    stm.mem32[stm.GPIOA + 0x18] = (1 << 5)  # Set
    pyb.delay(500)
    stm.mem32[stm.GPIOA + 0x18] = (1 << (5 + 16))  # Reset
    pyb.delay(500)
```

### Example 3: LCD160CR Display

```python
import lcd160cr
import pyb

# Initialize display
lcd = lcd160cr.LCD160CR('X')

# Draw a simple animation
x, y = 80, 64
dx, dy = 2, 2

while True:
    # Erase screen
    lcd.set_pen(lcd.rgb(0, 0, 255), lcd.rgb(0, 0, 0))
    lcd.erase()
    
    # Draw moving circle (approximated by filled rect)
    lcd.set_pen(lcd.rgb(255, 0, 0), lcd.rgb(255, 0, 0))
    lcd.rect_interior(x-5, y-5, 10, 10)
    
    # Update position
    x += dx
    y += dy
    
    # Bounce off edges
    if x < 5 or x > 155:
        dx = -dx
    if y < 5 or y > 123:
        dy = -dy
    
    pyb.delay(20)
```

## Notes

1. **Hardware Requirements:**
   - STM32F405RGT6 microcontroller
   - LCD160CR display (for lcd160cr module)

2. **Module Availability:**
   - `pyb` and `stm` modules are written in C and always available
   - `lcd160cr` is a Python module that must be imported explicitly

3. **Future Enhancements:**
   - Additional pyb classes (LED, Switch, Timer, ADC, DAC, etc.) can be added as needed
   - More STM32 peripheral constants can be exposed in the stm module
   - Hardware-specific features for the LCD160CR (JPEG, scrolling windows, etc.) are included but may require additional testing

4. **Compatibility:**
   - These modules provide a similar API to the official MicroPython pyboard
   - Some advanced features may not be available in this ThreadX port
   - The lcd160cr module is a pure Python driver and should be compatible across different MicroPython ports

## References

- [Official MicroPython Documentation](https://docs.micropython.org/)
- [Pyboard Specific Libraries](https://docs.micropython.org/en/latest/library/index.html#port-specific-libraries)
- [STM Module Reference](https://docs.micropython.org/en/latest/library/stm.html)
- [LCD160CR Module Reference](https://docs.micropython.org/en/latest/library/lcd160cr.html)
