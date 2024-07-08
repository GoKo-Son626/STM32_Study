/**
 ****************************************************************************************************
 * @file        main.c
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2020-04-20
 * @brief       ����ͨ�� ʵ��
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
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED/led.h"
#include "./BSP/WDG/wdg.h"
#include "./BSP/KEY/key.h"


int main(void)
{
    HAL_Init();                             /* ��ʼ��HAL�� */
    sys_stm32_clock_init(RCC_PLL_MUL9);     /* ����ʱ��Ϊ72Mhz */
    delay_init(72);                         /* ��ʱ��ʼ�� */
    key_init();                             // ��ʼ������
    usart_init(115200);                     /* ���ڳ�ʼ��Ϊ115200 */
    delay_ms(100);
    iwdg_init(IWDG_PRESCALER_32, 1250);     /* Ԥ��Ƶϵ��Ϊ32����װ��ֵΪ1250�����ʱ��Ϊ1s */
    led_init();                             // ��ʼ��LED
    
    
//      ��֤1
//    printf("��ã��㻹ûι�����뼰ʱι��������\r\n");
//    
//    while (1)
//    {
//        delay_ms(1010);
//        iwdg_feed();
//        printf("�Ѿ�ι��\r\n");
//    }
    
    
//      ��֤2
    LED0(0);
    while(1)
    {
        if (key_scan(1) == WKUP_PRES)       /* ���WK_UP����,��ι�� */
        {
            LED1(0);                        /* ����LED1�����ƣ� */
            iwdg_feed();                    /* ι�� */
        }
        delay_ms(10);
        LED1(1);
    }
}





