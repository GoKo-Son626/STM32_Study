<!--
 * @Date: 2024-06-06
 * @LastEditors: GoKo-Son626
 * @LastEditTime: 2024-07-12
 * @FilePath: \STM32_Study\入门篇\8.OLED\OLED.md
 * @Description: 该模板为所有笔记模板
-->

# OLED

> 内容目录：
> 
>       1. OLED显示屏介绍
>       2. OLED驱动原理
>       3. OLED驱动芯片介绍
>       4. 字符显示原理
>       5. OLED基本驱动步骤
>       6. 编程实战

### 1. OLED显示屏介绍

> - OLED，即有机发光二极管（Organic Light-Emitting Diode）,又称为有机激光显示（Organic Electroluminesence Display）。	
> - OLED显示屏就是利用有机发光二极管制成的显示屏，只要在正负极上加上正确的电压就会发光。

> **正点原子OLED模块介绍**
> - ATK_OLED模块是一块小尺寸（0.96寸）、高亮、自带升压电路的高性能OLED显示模块，分辨率为128 * 64，采用SSD1306驱动IC，该芯片内部集成DCDC升压，仅需3.3V供电。
> - 模块支持8位6800并口、8位8080并口、4线SPI以及IIC等4种通信接口。
**选择方式：通过BS1和BS2选择（默认8080并口）**

| 接口方式 | 8位8080 | 8位6800 | 4线SPI | IIC |
| -------- | ------- | ------- | ------ | --- |
| BS1      | 1       | 0       | 0      | 1   |
| BS2      | 1       | 1       | 0      | 0   |

### 2. OLED驱动原理

**驱动核心：驱动OLED驱动芯片**






### 3. OLED驱动芯片介绍



### 4. 字符显示原理



### 5. OLED基本驱动步骤



### 6. 编程实战