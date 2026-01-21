# LED PWM调光功能测试脚本
# STM32F405 + ThreadX + MicroPython (官方pyboard v1.1完整版)

print("=" * 50)
print("测试 pyb.LED 类 - 带PWM调光支持")
print("=" * 50)

from pyb import LED
import time

# 测试基本开关功能
print("\n1. 基本开关测试")
led1 = LED(1)  # 红色
led2 = LED(2)  # 绿色
led3 = LED(3)  # 黄色 (支持PWM)
led4 = LED(4)  # 蓝色 (支持PWM)

for i, led in enumerate([led1, led2, led3, led4], 1):
    print(f"   LED {i}: {led}")
    led.on()
    time.sleep(0.2)
    led.off()

# 测试PWM调光 - LED3 (Yellow, PA15 - TIM2_CH1)
print("\n2. PWM调光测试 - LED3 (黄色)")
print("   渐亮...")
for intensity in range(0, 256, 25):
    led3.intensity(intensity)
    print(f"   亮度: {intensity}/255 = {led3.intensity()}")
    time.sleep(0.1)

print("   渐灭...")
for intensity in range(255, -1, -25):
    led3.intensity(intensity)
    print(f"   亮度: {intensity}/255 = {led3.intensity()}")
    time.sleep(0.1)

# 测试PWM调光 - LED4 (Blue, PB4 - TIM3_CH1)
print("\n3. PWM调光测试 - LED4 (蓝色)")
print("   呼吸灯效果...")
for _ in range(2):
    # 渐亮
    for intensity in range(0, 256, 5):
        led4.intensity(intensity)
        time.sleep(0.01)
    # 渐灭
    for intensity in range(255, -1, -5):
        led4.intensity(intensity)
        time.sleep(0.01)

led4.off()

# 测试不同亮度级别
print("\n4. 不同亮度级别测试")
levels = [0, 32, 64, 128, 192, 255]
for level in levels:
    print(f"   设置LED3亮度为 {level}/255")
    led3.intensity(level)
    time.sleep(0.5)

led3.off()

# 测试双LED同时PWM
print("\n5. 双LED同时PWM控制")
for i in range(256):
    led3.intensity(i)
    led4.intensity(255 - i)
    time.sleep(0.005)

# 关闭所有LED
for led in [led1, led2, led3, led4]:
    led.off()

print("\n" + "=" * 50)
print("PWM调光测试完成!")
print("=" * 50)
print("\n注意:")
print("- LED1 (红色) 和 LED2 (绿色) 仅支持开关")
print("- LED3 (黄色) 和 LED4 (蓝色) 支持0-255亮度调节")
print("- 使用 led.intensity(value) 设置/读取亮度")
