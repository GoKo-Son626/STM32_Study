<!--
 * @Date: 2024-05-29
 * @LastEditors: GoKo-Son626
 * @LastEditTime: 2024-05-31
 * @FilePath: \STM32_Study\基础篇\DAP下载程序及其调试.md
 * @Description: 
-->
### DAP下载程序

硬件连接：
- 连接DAP与开发板
- 使用STM下载器需要下载相应stlink驱动
- 在MDK IDE界面下配置相关设置
- F7调试，F8下载

DAP 仿真调试程序：
- 调试原理
1. Cortex-M内核含有硬件调试模块，可在取指或访问数据时停止，内核停止时可以查询内核内外部状态
2. SW调试接口使用PA13和PA14两个接口
3. 释放PA15，PB3,PB4时：禁止JATG-DP，使能SW-DP

- SWJ_CFG[2:0]:串行线JTAG配置：000， 001， 010， 100

### 基础执行控制按钮学习

- 断点设置
> 最多设置6个断点
  
结束仿真报错：
1. 结束前清除所有断点
2. 改写路径->全英文

**工具栏：**
1. Call Stack 窗口：查看函数调用关系&局部变量
2. Watch 窗口：函数首地址，变量值，设置读写后自动停止
3. Memory 窗口：内存查看窗口
4. Peripheral 窗口：查看寄存器值

> 仿真时需要level 0等级优化

