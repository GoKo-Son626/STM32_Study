/**
 ******************************************************************************
 * @file     main.c
 * @author   ����ԭ���Ŷ�(ALIENTEK)
 * @version  V1.0
 * @date     2020-08-20
 * @brief    �½�����ʵ��-HAL��汾 ʵ��
 * @license  Copyright (c) 2020-2032, ������������ӿƼ����޹�˾
 ******************************************************************************
 * @attention
 * 
 * ʵ��ƽ̨:����ԭ�� STM32F103 ������
 * ������Ƶ:www.yuanzige.com
 * ������̳:www.openedv.com
 * ��˾��ַ:www.alientek.com
 * �����ַ:openedv.taobao.com
 ******************************************************************************
 */

#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED/led.h"
#include "./BSP/KEY/key.h"

//void led_init(void);                       /* LED��ʼ���������� */

int main(void)
{
    HAL_Init();                         /* ��ʼ��HAL�� */
    sys_stm32_clock_init(RCC_PLL_MUL9); /* ����ʱ��, 72Mhz */
    delay_init(72);                     /* ��ʱ��ʼ�� */
    led_init();                         /* LED��ʼ�� */
    key_init();
    while(1)
    { 
        if(key_scan() == 1)
        {
            HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_5);
        }
        delay_ms(10);
    }
}

///**
// * @brief       ��ʼ��LED���IO��, ��ʹ��ʱ��
// * @param       ��
// * @retval      ��
// */
//void led_init(void)
//{
//    GPIO_InitTypeDef gpio_initstruct;
//    __HAL_RCC_GPIOB_CLK_ENABLE();                          /* IO��PBʱ��ʹ�� */
//    __HAL_RCC_GPIOE_CLK_ENABLE();                          /* IO��PEʱ��ʹ�� */

//    gpio_initstruct.Pin = GPIO_PIN_5;                      /* LED0���� */
//    gpio_initstruct.Mode = GPIO_MODE_OUTPUT_PP;            /* ������� */
//    gpio_initstruct.Pull = GPIO_PULLUP;                    /* ���� */
//    gpio_initstruct.Speed = GPIO_SPEED_FREQ_HIGH;          /* ���� */
//    HAL_GPIO_Init(GPIOB, &gpio_initstruct);                /* ��ʼ��LED0���� */

//    gpio_initstruct.Pin = GPIO_PIN_5;                      /* LED1���� */
//    HAL_GPIO_Init(GPIOE, &gpio_initstruct);                /* ��ʼ��LED1���� */
//}
