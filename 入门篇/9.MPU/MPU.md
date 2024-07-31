<!--
 * @Date: 2024-06-06
 * @LastEditors: GoKo-Son626
 * @LastEditTime: 2024-07-31
 * @FilePath: \STM32_Study\入门篇\9.MPU\MPU.md
 * @Description: 该模板为所有笔记模板
-->

# MPU(F7/H7)

> 内容目录：
> 
>       1. 内存保护单元(MPU)介绍（了解）
>       2. Cache简介（了解）
>       3. MPU相关寄存器介绍（熟悉）
>       4. MPU相关HAL库驱动介绍（掌握）
>       5. MPU基本配置步骤（掌握）
>       6. 编程实战（掌握）


### 1. 内存保护单元(MPU)介绍（了解）
**内存保护单元（memory protection unit），简称：MPU。可理解为管理员**

> **功能：**
> - 设置不同存储区域的存储器访问权限（特权级、用户级）
> - 设置存储器(内存和外设)属性（可缓存、可缓冲、可共享）

> **好处：**
> ① 阻止用户应用程序破坏操作系统使用的数据
> ② 阻止一个任务访问其他任务的数据区，从而隔离任务
> ③ 把关键数据区域设置为只读，从根本上解决被破坏的可能
> ④ 检测意外的存储访问，如堆栈溢出、数组越界等
> ⑤ 将SRAM或RAM空间定义为不可执行，防止代码注入攻击

### 2. Cache简介（了解）
### 3. MPU相关寄存器介绍（熟悉）

| 寄存器      | 名称                    | 功能                                                 |
| ----------- | ----------------------- | ---------------------------------------------------- |
| MPU_TYPE    | MPU类型寄存器           | 用于指明MPU的一些特征(是否支持MPU、支持多少个Region) |
| MPU_CTRL    | MPU控制寄存器           | 设置MPU使能                                          |
| MPU_RNR	MPU | 区域编号寄存器          | 用于选择下一个要配置的region                         |
| MPU_RBAR    | MPU基地址寄存器         | 用于设置区域的起始地址                               |
| MPU_RASR    | MPU区域属性和容量寄存器 | 用于设置每个区域的属性                               |


### 4. MPU相关HAL库驱动介绍（掌握）

| 驱动函数                | 关联寄存器    | 功能描述    |
| ----------------------- | ------------- | ----------- |
| HAL_MPU_Enable(…)       | CTRL          | MPU使能     |
| HAL_MPU_Disable(…)      | CTRL          | MPU失能     |
| HAL_MPU_ConfigRegion(…) | RASR\RBAR\RNR | 配置MPU参数 |

### 5. MPU基本配置步骤（掌握）

1. **禁止MPU：** void HAL_MPU_Disable();
2. **配置某个区域的MPU保护参数：** 通过调用HAL_MPU_ComfigRegion()函数去设置
3. **使能MPU：** void HAL_MPU_Enable();
4. **编写MenManage中断服务函数：** void MemManage_Handler(void)

### 6. 编程实战（掌握）
### 7. 课堂总结
