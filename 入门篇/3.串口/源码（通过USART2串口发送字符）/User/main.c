/**
 ****************************************************************************************************
 * @file        main.c
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2020-04-20
 * @brief       ����� ʵ��
 * @license     Copyright (c) 2020-2032, ������������ӿƼ����޹�˾
 ****************************************************************************************************
 * @attention
 *
 * ʵ��ƽ̨:����ԭ�� STM32F103������
 * ������Ƶ:www.yuanzige.com
 * ������̳:www.openedv.com
 * ��˾��ַ:www.alientek.com
 * �����ַ:openedv.taobao.com
 *
 ****************************************************************************************************
 */

#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/delay/delay.h"
#include "./SYSTEM/usart/usart.h"
#include "./BSP/LED/led.h"


int main(void)
{
    uint8_t len;
    
    HAL_Init();                                 /* ��ʼ��HAL�� */
    sys_stm32_clock_init(RCC_PLL_MUL9);         /* ����ʱ��,72M */
    delay_init(72);                             /* ��ʼ����ʱ���� */
    led_init();                                 /* ��ʼ��LED */
    usart_init(115200);                         /* ����������Ϊ115200 */
    
    printf("������һ������:\r\n");
    while(1)
    {
        if(g_usart2_rx_flag & 0x8000)
        {
            len = g_usart2_rx_flag & 0x3fff;
            
            printf("����ĵ���Ϊ:");
            HAL_UART_Transmit(&g_usart2_handle, (uint8_t*)g_user_rx_buffer, len, 1000);
            while(__HAL_UART_GET_FLAG(&g_usart2_handle, UART_FLAG_TC) != 1);
            printf("\r\n");
            g_usart2_rx_flag = 0;
        }
        else
        {
            delay_ms(10);
        }
    }
}

