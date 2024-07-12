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
#include "./BSP/TPAD/tpad.h"


int main(void)
{
    uint16_t t = 0;
    
    HAL_Init();                                 /* ��ʼ��HAL�� */
    sys_stm32_clock_init(RCC_PLL_MUL9);         /* ����ʱ��,72M */
    delay_init(72);                             /* ��ʼ����ʱ���� */
    usart_init(115200);                         // ���ڳ�ʼ��
    led_init();                                 /* ��ʼ��LED */
    tpad_init(6);                               // ��ʼ����������
    
    while(1)
    {
        if (tpad_scan(0))   /* �ɹ�������һ��������(�˺���ִ��ʱ������15ms) */
        {
            LED1_TOGGLE();  /* LED1��ת */
        }

        t++;
        if (t == 15)
        {
            t = 0;
            LED0_TOGGLE();  /* LED0��ת */
        }

        delay_ms(10);
    }
}

