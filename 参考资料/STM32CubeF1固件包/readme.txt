本目录下，包括两个文件夹：
    1，stm32cube_fw_f1_v183，这是ST提供的STM32CubeF1 固件包，是针对STM32F1系列的嵌入式软件包，
         其中包括：HAL库、底层API和CMSIS（CORE、DSP和RTOS）、USB、TCP/IP、文件系统、RTOS和图形库等，
         并附带有在ST官方Nucleo、探索套件和评估板运行的例程）。
         该固件包中，我们来说比较重要的是：
       （1）HAL库驱动，路径：Drivers\STM32F1xx_HAL_Driver
       （2）CMSIS驱动，路径：Drivers\CMSIS（注意CMSIS里面包含了非常多的文件，可大大精简，详见 精简版CMSIS.rar）

    2，精简版CMSIS，精简版CMSIS仅包含startup_stm32f103xe.s 这一个启动文件，适用于大容量 F103 系列芯片，
         其他一些F1系列启动文件在：stm32cube_fw_f1_v183.zip 里面，具体路径为：Drivers\CMSIS\Device\ST\STM32F1xx\Source\Templates\arm



 ***********************************************************************************************************
 * 公司名称：广州市星翼电子科技有限公司（正点原子）
 * 电话号码：020-38271790
 * 传真号码：020-36773971
 * 公司网址：www.alientek.com
 * 购买地址：zhengdianyuanzi.tmall.com
 * 技术论坛：http://www.openedv.com/forum.php
 * 最新资料：www.openedv.com/docs/index.html
 *
 * 在线视频：www.yuanzige.com
 * B 站视频：space.bilibili.com/394620890
 * 公 众 号：mp.weixin.qq.com/s/y--mG3qQT8gop0VRuER9bw
 * 抖    音：douyin.com/user/MS4wLjABAAAAi5E95JUBpqsW5kgMEaagtIITIl15hAJvMO8vQMV1tT6PEsw-V5HbkNLlLMkFf1Bd
 ***********************************************************************************************************