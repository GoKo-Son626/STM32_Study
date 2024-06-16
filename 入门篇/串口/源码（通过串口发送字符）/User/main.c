/**
 ****************************************************************************************************
 * @file        main.c
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2020-04-20
 * @brief       跑马灯 实验
 * @license     Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
 ****************************************************************************************************
 * @attention
 *
 * 实验平台:正点原子 STM32F103开发板
 * 在线视频:www.yuanzige.com
 * 技术论坛:www.openedv.com
 * 公司网址:www.alientek.com
 * 购买地址:openedv.taobao.com
 *
 ****************************************************************************************************
 */

#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/delay/delay.h"
#include "./SYSTEM/usart/usart.h"
#include "./BSP/LED/led.h"


int main(void)
{
    HAL_Init();                                 /* 初始化HAL库 */
    sys_stm32_clock_init(RCC_PLL_MUL9);         /* 设置时钟,72M */
    delay_init(72);                             /* 初始化延时函数 */
    led_init();                                 /* 初始化LED */
    usart_init(115200);                         /* 波特率设置为115200 */
    
    printf("请输入一个英文字符:\r\n");
    while(1)
    {
        if(g_usart1_rx_flag == 1)
        {
            printf("输入的字符为:");
            HAL_UART_Transmit(&g_uart1_handle, (uint8_t*)g_rx_buffer, 1, 1000);
            while(__HAL_UART_GET_FLAG(&g_uart1_handle, UART_FLAG_TC) != 1);
            printf("\r\n");
            g_usart1_rx_flag = 0;
        }
        else
        {
            delay_ms(10);
        }
    }
}

