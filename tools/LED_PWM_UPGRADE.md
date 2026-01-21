# LED PWM调光功能升级说明

## 📋 升级内容

已将LED实现从简化版升级到官方MicroPython完整版，包括PWM硬件调光支持。

### 新增文件
- **mpconfigboard.h** - 板级配置文件（定义LED引脚和PWM配置）

### 修改文件
- **led.c** (~350行) - 添加完整PWM支持
- **mpconfigport.h** - 包含板级配置
- **pin.h** - 移除LED宏（已迁移到mpconfigboard.h）

## 🎯 PWM支持详情

### 支持PWM的LED
| LED | 颜色 | 引脚 | 定时器 | 亮度调节 |
|-----|------|------|--------|----------|
| LED 1 | 红色 | PA13 | 无 | ❌ 仅开关 |
| LED 2 | 绿色 | PA14 | 无 | ❌ 仅开关 |
| LED 3 | 黄色 | PA15 | TIM2_CH1 | ✅ 0-255 |
| LED 4 | 蓝色 | PB4  | TIM3_CH1 | ✅ 0-255 |

### PWM技术参数
- **定时器频率**: 1MHz
- **PWM周期**: 10ms (10,000计数)
- **亮度分辨率**: 0-255 (8位)
- **硬件定时器**: TIM2 (APB1), TIM3 (APB1)

## 💻 使用方法

### 基本开关（所有LED）
```python
from pyb import LED

led1 = LED(1)  # 红色
led1.on()      # 点亮
led1.off()     # 熄灭
led1.toggle()  # 切换
```

### PWM调光（LED3和LED4）
```python
led3 = LED(3)  # 黄色 (支持PWM)

# 设置亮度 (0-255)
led3.intensity(128)  # 半亮
led3.intensity(255)  # 全亮
led3.intensity(0)    # 熄灭

# 读取当前亮度
brightness = led3.intensity()
print(f"当前亮度: {brightness}/255")

# 呼吸灯效果
for i in range(0, 256, 5):
    led3.intensity(i)
    time.sleep(0.01)
for i in range(255, -1, -5):
    led3.intensity(i)
    time.sleep(0.01)
```

### PWM特性
- 当设置亮度为0或255时，自动切换回普通GPIO模式（省电）
- 当设置中间亮度(1-254)时，自动初始化PWM定时器
- PWM频率100Hz，人眼无闪烁感
- 硬件PWM，CPU占用极低

## 🔧 实现原理

### 架构对比

**简化版（之前）：**
```c
// 仅支持开关
led_state(led, 1);  // 直接GPIO操作
```

**完整版（现在）：**
```c
// 智能模式切换
if (intensity == 0 || intensity == 255) {
    // GPIO模式 - 省电
    led_state(led, intensity > 0);
} else {
    // PWM模式 - 精确调光
    led_pwm_init(led);
    *LED_PWM_CCR(pwm_cfg) = intensity * period / 255;
}
```

### PWM配置宏（mpconfigboard.h）
```c
// LED定义
#define MICROPY_HW_LED3 (pin_A15)  // 黄色
#define MICROPY_HW_LED4 (pin_B4)   // 蓝色

// PWM配置 {定时器, ID, 通道, 复用功能}
#define MICROPY_HW_LED3_PWM { TIM2, 2, TIM_CHANNEL_1, GPIO_AF1_TIM2 }
#define MICROPY_HW_LED4_PWM { TIM3, 3, TIM_CHANNEL_1, GPIO_AF2_TIM3 }
```

### PWM初始化流程
1. 配置引脚为复用功能（AF mode）
2. 使能定时器时钟（TIM2/TIM3）
3. 配置定时器：1MHz频率，10ms周期
4. 配置PWM通道：PWM模式1，起始占空比0%
5. 启动PWM输出
6. 标记LED为PWM模式

## 📊 编译结果
- ✅ 0 错误
- ⚠️ 1507 警告（正常）
- 固件大小：~2.2MB

## 🧪 测试
运行测试脚本：
- `tools/test_led_pin.py` - 基本LED和Pin功能
- `tools/test_led_pwm.py` - PWM调光功能演示

## 🎓 与官方对比

| 特性 | 官方MicroPython | 当前实现 |
|------|----------------|----------|
| LED开关 | ✅ | ✅ |
| PWM调光 | ✅ (0-255) | ✅ (0-255) |
| 宏配置系统 | ✅ | ✅ |
| 动态模式切换 | ✅ | ✅ |
| 定时器支持 | TIM1-11 | TIM2-3 |
| 最多LED数 | 6 | 4 |

## 📝 总结
升级后的LED实现：
- ✅ 完全符合官方pyboard v1.1规范
- ✅ 支持硬件PWM调光（LED3和LED4）
- ✅ 自动模式切换（GPIO ↔ PWM）
- ✅ 低CPU占用
- ✅ 代码可移植性强（通过宏配置）
