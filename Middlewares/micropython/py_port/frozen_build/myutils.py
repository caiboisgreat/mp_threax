"""
自定义工具模块示例 - 演示如何创建可冻结的 Python 模块

此文件位于: Middlewares/micropython/py_port/frozen_build/myutils.py

编译方法:
    python tools/freeze_module.py myutils

使用方法:
    >>> import myutils
    >>> myutils.greet("STM32")
    'Hello, STM32!'
"""

# ============================================================================
# 模块信息
# ============================================================================

__version__ = "1.0.0"
__author__ = "CaiBo"
__date__ = "2026-01-28"

# ============================================================================
# 常量定义
# ============================================================================

# LED 引脚定义
LED_RED = 0
LED_GREEN = 1
LED_BLUE = 2

# 默认配置
DEFAULT_CONFIG = {
    'baud_rate': 115200,
    'timeout': 1000,
    'buffer_size': 256,
    'debug': False,
}

# 状态码
STATUS_OK = 0
STATUS_ERROR = -1
STATUS_TIMEOUT = -2
STATUS_BUSY = -3

# ============================================================================
# 实用函数
# ============================================================================

def greet(name="World"):
    """
    问候函数
    
    参数:
        name: 名字 (默认 "World")
    
    返回:
        问候字符串
    
    示例:
        >>> greet("MicroPython")
        'Hello, MicroPython!'
    """
    return f"Hello, {name}!"

def calculate_checksum(data):
    """
    计算简单的 8 位校验和
    
    参数:
        data: 字符串或字节数组
    
    返回:
        校验和 (0-255)
    
    示例:
        >>> calculate_checksum("TEST")
        233
        >>> calculate_checksum(b'\\x01\\x02\\x03')
        6
    """
    if isinstance(data, str):
        data = data.encode()
    return sum(data) & 0xFF

def hex_dump(data, width=16):
    """
    以十六进制格式打印数据
    
    参数:
        data: 要显示的数据
        width: 每行显示的字节数 (默认 16)
    
    示例:
        >>> hex_dump(b'Hello World!')
        00000000: 48 65 6c 6c 6f 20 57 6f  72 6c 64 21              Hello World!
    """
    if isinstance(data, str):
        data = data.encode()
    
    lines = []
    for i in range(0, len(data), width):
        chunk = data[i:i+width]
        
        # 十六进制部分
        hex_part = ' '.join(f'{b:02x}' for b in chunk)
        hex_part = hex_part.ljust(width * 3 - 1)
        
        # ASCII 部分
        ascii_part = ''.join(chr(b) if 32 <= b < 127 else '.' for b in chunk)
        
        # 组合
        line = f"{i:08x}: {hex_part}  {ascii_part}"
        lines.append(line)
    
    return '\n'.join(lines)

def clamp(value, min_val, max_val):
    """
    将值限制在指定范围内
    
    参数:
        value: 要限制的值
        min_val: 最小值
        max_val: 最大值
    
    返回:
        限制后的值
    
    示例:
        >>> clamp(150, 0, 100)
        100
        >>> clamp(-10, 0, 100)
        0
    """
    return max(min_val, min(value, max_val))

def map_range(value, in_min, in_max, out_min, out_max):
    """
    将值从一个范围映射到另一个范围
    
    参数:
        value: 输入值
        in_min, in_max: 输入范围
        out_min, out_max: 输出范围
    
    返回:
        映射后的值
    
    示例:
        >>> map_range(50, 0, 100, 0, 255)
        127
    """
    return (value - in_min) * (out_max - out_min) / (in_max - in_min) + out_min

# ============================================================================
# 类定义
# ============================================================================

class DataBuffer:
    """
    简单的循环缓冲区
    
    示例:
        >>> buf = DataBuffer(16)
        >>> buf.write("Hello")
        >>> buf.write(" World")
        >>> buf.read()
        b'Hello World\\x00\\x00\\x00\\x00\\x00'
    """
    
    def __init__(self, size=128):
        """
        初始化缓冲区
        
        参数:
            size: 缓冲区大小 (字节)
        """
        self.buffer = bytearray(size)
        self.pos = 0
        self.size = size
    
    def write(self, data):
        """
        写入数据到缓冲区
        
        参数:
            data: 要写入的数据 (字符串或字节)
        
        返回:
            实际写入的字节数
        """
        if isinstance(data, str):
            data = data.encode()
        
        written = 0
        for b in data:
            if self.pos < self.size:
                self.buffer[self.pos] = b
                self.pos += 1
                written += 1
            else:
                break  # 缓冲区满
        
        return written
    
    def read(self, length=None):
        """
        读取缓冲区数据
        
        参数:
            length: 读取长度 (None 表示全部)
        
        返回:
            读取的字节数据
        """
        if length is None:
            length = self.pos
        else:
            length = min(length, self.pos)
        
        return bytes(self.buffer[:length])
    
    def clear(self):
        """清空缓冲区"""
        self.pos = 0
        for i in range(self.size):
            self.buffer[i] = 0
    
    def available(self):
        """返回已用空间"""
        return self.pos
    
    def free(self):
        """返回剩余空间"""
        return self.size - self.pos
    
    def is_full(self):
        """检查缓冲区是否已满"""
        return self.pos >= self.size
    
    def is_empty(self):
        """检查缓冲区是否为空"""
        return self.pos == 0

class RingBuffer:
    """
    环形缓冲区 (FIFO)
    
    示例:
        >>> rb = RingBuffer(8)
        >>> rb.write(b"12345")
        >>> rb.read(3)
        b'123'
        >>> rb.write(b"6789")
        >>> rb.available()
        6
    """
    
    def __init__(self, size):
        """
        初始化环形缓冲区
        
        参数:
            size: 缓冲区大小
        """
        self.buffer = bytearray(size)
        self.size = size
        self.head = 0
        self.tail = 0
        self.count = 0
    
    def write(self, data):
        """写入数据"""
        if isinstance(data, str):
            data = data.encode()
        
        written = 0
        for b in data:
            if self.count < self.size:
                self.buffer[self.head] = b
                self.head = (self.head + 1) % self.size
                self.count += 1
                written += 1
            else:
                break
        
        return written
    
    def read(self, length=1):
        """读取数据"""
        length = min(length, self.count)
        result = bytearray(length)
        
        for i in range(length):
            result[i] = self.buffer[self.tail]
            self.tail = (self.tail + 1) % self.size
            self.count -= 1
        
        return bytes(result)
    
    def peek(self, offset=0):
        """查看数据但不移除"""
        if offset >= self.count:
            return None
        
        pos = (self.tail + offset) % self.size
        return self.buffer[pos]
    
    def available(self):
        """返回可读字节数"""
        return self.count
    
    def free(self):
        """返回可写字节数"""
        return self.size - self.count
    
    def clear(self):
        """清空缓冲区"""
        self.head = 0
        self.tail = 0
        self.count = 0

class MovingAverage:
    """
    移动平均滤波器
    
    示例:
        >>> ma = MovingAverage(5)
        >>> for i in range(10):
        ...     print(ma.update(i))
    """
    
    def __init__(self, window_size=10):
        """
        初始化
        
        参数:
            window_size: 窗口大小
        """
        self.window = [0] * window_size
        self.size = window_size
        self.index = 0
        self.sum = 0
        self.filled = False
    
    def update(self, value):
        """
        更新并返回平均值
        
        参数:
            value: 新值
        
        返回:
            当前移动平均值
        """
        # 减去即将被替换的值
        self.sum -= self.window[self.index]
        
        # 添加新值
        self.window[self.index] = value
        self.sum += value
        
        # 移动索引
        self.index = (self.index + 1) % self.size
        
        # 标记是否已填满
        if self.index == 0 and not self.filled:
            self.filled = True
        
        # 计算平均值
        count = self.size if self.filled else self.index
        return self.sum / count if count > 0 else 0
    
    def reset(self):
        """重置滤波器"""
        self.window = [0] * self.size
        self.index = 0
        self.sum = 0
        self.filled = False

# ============================================================================
# 调试辅助函数
# ============================================================================

def print_dict(d, indent=0):
    """
    漂亮打印字典
    
    参数:
        d: 要打印的字典
        indent: 缩进级别
    """
    for key, value in d.items():
        print('  ' * indent + str(key) + ':', end=' ')
        if isinstance(value, dict):
            print()
            print_dict(value, indent + 1)
        else:
            print(value)

def sizeof(obj):
    """
    估算对象占用的内存
    
    参数:
        obj: 要检查的对象
    
    返回:
        估算的字节数
    """
    import sys
    
    # 这是一个简化实现
    size = 0
    
    if isinstance(obj, str):
        size = len(obj)
    elif isinstance(obj, (bytes, bytearray)):
        size = len(obj)
    elif isinstance(obj, (list, tuple)):
        size = sum(sizeof(item) for item in obj)
    elif isinstance(obj, dict):
        size = sum(sizeof(k) + sizeof(v) for k, v in obj.items())
    else:
        size = sys.getsizeof(obj) if hasattr(sys, 'getsizeof') else 0
    
    return size

# ============================================================================
# 模块测试
# ============================================================================

def self_test():
    """
    模块自测试
    
    使用:
        >>> import myutils
        >>> myutils.self_test()
    """
    print("=" * 60)
    print("myutils 模块自测试")
    print("=" * 60)
    
    # 测试问候函数
    print("\n1. 测试 greet()")
    assert greet("Test") == "Hello, Test!"
    print("   ✅ 通过")
    
    # 测试校验和
    print("\n2. 测试 calculate_checksum()")
    assert calculate_checksum("TEST") == 233
    assert calculate_checksum(b'\x01\x02\x03') == 6
    print("   ✅ 通过")
    
    # 测试 DataBuffer
    print("\n3. 测试 DataBuffer")
    buf = DataBuffer(16)
    buf.write("Hello")
    assert buf.available() == 5
    assert buf.read(5) == b'Hello'
    print("   ✅ 通过")
    
    # 测试 RingBuffer
    print("\n4. 测试 RingBuffer")
    rb = RingBuffer(8)
    rb.write(b"12345")
    assert rb.read(3) == b'123'
    assert rb.available() == 2
    print("   ✅ 通过")
    
    # 测试 MovingAverage
    print("\n5. 测试 MovingAverage")
    ma = MovingAverage(3)
    ma.update(10)
    ma.update(20)
    avg = ma.update(30)
    assert abs(avg - 20.0) < 0.001
    print("   ✅ 通过")
    
    print("\n" + "=" * 60)
    print("所有测试通过! ✅")
    print("=" * 60)

# 模块加载时的初始化代码（可选）
# print(f"myutils v{__version__} loaded")
