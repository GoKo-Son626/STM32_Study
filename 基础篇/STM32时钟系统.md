<!--
 * @Date: 2024-06-03
 * @LastEditors: GoKo-Son626
 * @LastEditTime: 2024-06-04
 * @FilePath: \STM32_Study\基础篇\STM32时钟系统.md
 * @Description: 
-->
### STM32时钟系统

##### 认识时钟树

1. 什么是时钟？

> 时钟是具有周期性的脉冲信号，最常用的是占空比50%的方波（时钟：单片机的脉搏）

2. 认识时钟树（F1）

HSE（4~16MHz）和HSI（8MHz）通过锁相环（PLL）得到72MHz（max）的SYSCLK
# 三张主要图

##### 配置系统时钟

1. 系统时钟配置步骤
>
> 1. 配置HSE_VALUE(外部晶振频率)
> 2. 调用SystemInit()函数（可选）(BECAUSE 只配置了中断向量表的位置，无意义)
> 3. 选择时钟源，配置PLL（通过HAL_RCC_OscConfig()函数设置）
> 4. 选择系统时钟源（PLL），配置总线分配器（通过HAL_RCC_ClockConfig()函数设置）

2. 外设时钟使能和失能

> 要使用外设，必须先使其使能
> 禁止时失能

3. sys_stm32_clock_init函数（F1）
>
>   1. HAL_RCC_OscConfig()函数 
>   > 38->8:40
>   2. HAL_RCC_ClockConfig()函数
>   > 38->15：16


##### 总结