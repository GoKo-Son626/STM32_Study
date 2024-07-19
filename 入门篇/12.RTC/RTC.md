<!--
 * @Date: 2024-06-06
 * @LastEditors: GoKo-Son626
 * @LastEditTime: 2024-07-19
 * @FilePath: \STM32_Study\入门篇\12.RTC\RTC.md
 * @Description: 该模板为所有笔记模板
-->

# RTC

> 内容目录：
> 
>       1. RTC简介（了解）
>       2. STM32 RTC框图介绍（熟悉）
>       3. RTC相关寄存器介绍（熟悉）
>       4. RTC相关HAL库驱动介绍（掌握）
>       5. RTC基本驱动步骤（掌握）
>       6. 时间设置和读取（掌握）
>       7. 编程实战（掌握）






#### 1. RTC简介（了解）

- **实时时钟(Real Time Clock，RTC)，本质是一个计数器，计数频率常为秒，专门用来记录时间。**
> 特性：
> 1. 能提供时间（秒钟数）
> 2. 能在MCU掉电后运行
> 3. 低功耗

- 普通定时器无法拿来作时钟，因为无法掉电运行！

**RTC方案**
![RTC方案](Pictures/RTC方案.png)

1. 一般都需要设计RTC外围电路；
2. 一般都可以给RTC设置独立的电源；
3. 多数RTC的寄存器采用[**BCD**](https://baike.baidu.com/item/BCD%E7%A0%81/826461?fr=aladdin)码存储时间信息；

#### 2. STM32 RTC框图介绍

**RTC框图**
![RTC框图](Pictures/RTC框图.png)

> 1. RTC预分频系数
> 2. 32位可编程计数器
> 3. 待机唤醒
> 4. RTC控制器与APB1接口

#### 3. RTC相关寄存器介绍





#### 4. RTC相关HAL库驱动介绍





#### 5. RTC基本驱动步骤





#### 6. 时间设置和读取





#### 7. 编程实战