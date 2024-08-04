<!--
 * @Date: 2024-06-06
 * @LastEditors: GoKo-Son626
 * @LastEditTime: 2024-08-05
 * @FilePath: \STM32_Study\入门篇\18.SPI\SPI.md
 * @Description: 该模板为所有笔记模板
-->

# SPI

> 内容目录：
> 
>       1. 1，SPI介绍（了解）
>       2. SPI结构框图介绍（熟悉）
>       3. SPI工作模式介绍（熟悉）
>       4. SPI相关寄存器介绍（熟悉）
>       5. SPI相关HAL库驱动介绍（掌握）
>       6. NOR FLASH介绍（掌握）
>       7. NOR FLASH基本驱动步骤（掌握）
>       8. 编程实战（掌握）


### 1. SPI介绍（了解）

- **SPI：串行外设设备接口（Serial Peripheral Interface），是一种高速的，全双工，同步的通信总线。**
| 功能说明 | SPI总线             | IIC总线                |
| -------- | ------------------- | ---------------------- |
| 通信方式 | 同步 串行 全双工    | 同步 串行 半双工       |
| 总线接口 | MOSI、MISO、SCL、CS | SDA、SCL               |
| 拓扑结构 | 一主多从/一主一从   | 多主从                 |
| 从机选择 | 片选引脚选择        | SDA上设备地址片选      |
| 通信速率 | 一般50MHz以下       | 100kHz、400kHz、3.4MHz |
| 数据格式 | 8位/16位            | 8位                    |
| 传输顺序 | MSB/LSB             | MSB                    |

- SPI接口主要应用在存储芯片、AD转换器以及LCD中。

### 2. SPI结构框图介绍（熟悉）

**SPI结构框图**
![SPI结构框图](Pictures/SPI结构框图.png)

**①SPI相关引脚**:MOSI（输出数据线）MISO（输入数据线）SCK（时钟）NSS（片选）
**②数据发送和接收**:与缓冲区、移位寄存器以及引脚相关
**③时钟信号**:SPI时钟信号是通过SPI_CR1寄存器配置
**④主控制逻辑**:涉及两个控制寄存器SPI_CR1/2用于配置SPI工作，SPI_SR用于查看工作状态

**外设对应引脚：**
- STM32F1有三个SPI。

| F1  | 引脚 | SPI1 | SPI2 | SPI3 |
| --- | ---- | ---- | ---- | ---- |
| -   | NSS  | PA4  | PB12 | PA15 |
| -   | CLK  | PA5  | PB13 | PB3  |
| -   | MISO | PA6  | PB14 | PB4  |
| -   | MOSI | PA7  | PB15 | PB5  |

> F4 / F7 / H7 系列芯片SPI外设都有6个，分别为SPI1、SPI2、SPI3、SPI4、SPI5和SPI6.不同系列的SPI外设用到的引脚是不一样的.

### 3. SPI工作模式介绍（熟悉）



### 4. SPI相关寄存器介绍（熟悉）



### 5. SPI相关HAL库驱动介绍（掌握）



### 6. NOR FLASH介绍（掌握）



### 7. NOR FLASH基本驱动步骤（掌握）



### 8. 编程实战（掌握）






