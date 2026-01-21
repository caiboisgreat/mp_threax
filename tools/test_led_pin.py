# LED和Pin类功能测试脚本
# 用于STM32F405 + ThreadX + MicroPython (pyboard v1.1兼容)

print("=" * 50)
print("测试 pyb.LED 类 (4个LED)")
print("=" * 50)

from pyb import LED
import time

# 测试所有4个LED
led_names = ["红色(RED)", "绿色(GREEN)", "黄色(YELLOW)", "蓝色(BLUE)"]
led_pins = ["PA13", "PA14", "PA15", "PB4"]

for i in range(1, 5):
    print(f"\n{i}. 测试 LED({i}) - {led_names[i-1]} ({led_pins[i-1]})")
    led = LED(i)
    print(f"   LED对象创建: {led}")
    
    print("   点亮LED...")
    led.on()
    time.sleep(0.3)
    
    print("   关闭LED...")
    led.off()
    time.sleep(0.3)
    
    print("   切换3次...")
    for j in range(3):
        led.toggle()
        time.sleep(0.15)

# 测试所有LED同时点亮
print("\n5. 测试所有LED同时点亮")
leds = [LED(i) for i in range(1, 5)]
for led in leds:
    led.on()
time.sleep(1)

# 流水灯效果
print("\n6. 流水灯效果")
for _ in range(2):
    for i, led in enumerate(leds):
        led.on()
        time.sleep(0.1)
        led.off()

# 关闭所有LED
for led in leds:
    led.off()

print("\n" + "=" * 50)
print("测试 pyb.Pin 类")
print("=" * 50)

from pyb import Pin

# 测试所有LED引脚
print("\n1. 测试通过board名称访问所有LED引脚")
led_board_names = ['LED_RED', 'LED_GREEN', 'LED_YELLOW', 'LED_BLUE']
for name in led_board_names:
    pin = Pin(name, Pin.OUT)
    print(f"   {name}: {pin}")
    pin.on()
    time.sleep(0.2)
    pin.off()

# 测试通过CPU pin名称创建
print("\n2. 测试通过CPU pin名称创建Pin")
pin_a15 = Pin('A15', Pin.OUT)
print(f"Pin对象: {pin_a15}")

print("设置高电平...")
pin_a15.value(1)
time.sleep(0.5)

print("设置低电平...")
pin_a15.value(0)
time.sleep(0.5)

print("使用on()方法...")
pin_a15.on()
time.sleep(0.5)

print("使用off()方法...")
pin_a15.off()
time.sleep(0.5)

# 测试通过board pin名称创建
print("\n3. 测试通过board.LED访问器")
led_red = Pin.board.LED_RED
led_green = Pin.board.LED_GREEN
print(f"   LED_RED: {led_red}")
print(f"   LED_GREEN: {led_green}")

# 测试Pin.cpu访问器
print("\n4. 测试 Pin.cpu 访问器")
cpu_a15 = Pin.cpu.A15
print(f"通过Pin.cpu访问: {cpu_a15}")

# 测试输入模式
print("\n5. 测试输入模式")
pin_input = Pin('A0', Pin.IN, Pin.PULL_UP)
print(f"输入Pin创建: {pin_input}")
value = pin_input.value()
print(f"读取值: {value}")

# 测试mode和pull查询
print(f"模式: {pin_a15.mode()}")
print(f"上下拉: {pin_a15.pull()}")

print("\n" + "=" * 50)
print("所有测试完成!")
print("=" * 50)
