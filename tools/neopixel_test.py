# NeoPixel / WS2812 quick test for this STM32F405 + MicroPython port.
#
# This port provides a C module `neopixel` with:
#   neopixel.NeoPixel(pin, n, *, bpp=3, timing=(t0h,t0l,t1h,t1l))
# where pin is a 2-tuple like ("A", 5) meaning PA5.
#
# Example usage from REPL:
#   import neopixel_test
#   neopixel_test.run(("B", 6), 8)   # PB6, 8 LEDs

import time
import neopixel


def run(pin=("A", 5), n=8, bpp=3):
    np = neopixel.NeoPixel(pin, n, bpp=bpp)

    # Red, Green, Blue, Off sweep
    colors = [
        (255, 0, 0),
        (0, 255, 0),
        (0, 0, 255),
        (0, 0, 0),
    ]

    for c in colors:
        np.fill(c)
        np.write()
        time.sleep_ms(300)

    # Walking pixel
    np.fill((0, 0, 0))
    np.write()
    for i in range(n):
        np.fill((0, 0, 0))
        np[i] = (32, 32, 32)
        np.write()
        time.sleep_ms(80)

    np.fill((0, 0, 0))
    np.write()
    print("neopixel test done")


if __name__ == "__main__":
    run()
