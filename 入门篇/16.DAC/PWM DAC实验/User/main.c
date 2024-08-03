/**
 ****************************************************************************************************
 * @file        main.c
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2020-04-24
 * @brief       PWM DAC��� ʵ��
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
#include "./USMART/usmart.h"
#include "./BSP/LED/led.h"
#include "./BSP/LCD/lcd.h"
#include "./BSP/KEY/key.h"
#include "./BSP/ADC/adc3.h"
#include "./BSP/PWMDAC/pwmdac.h"


extern TIM_HandleTypeDef g_tim1_handle;

int main(void)
{
    uint16_t adcx;
    float temp;
    uint8_t t = 0;
    uint8_t key;
    uint16_t pwmval = 0;

    HAL_Init();                         /* ��ʼ��HAL�� */
    sys_stm32_clock_init(RCC_PLL_MUL9); /* ����ʱ��, 72Mhz */
    delay_init(72);                     /* ��ʱ��ʼ�� */
    usart_init(115200);                 /* ���ڳ�ʼ��Ϊ115200 */
    usmart_dev.init(72);                /* ��ʼ��USMART */
    led_init();                         /* ��ʼ��LED */
    lcd_init();                         /* ��ʼ��LCD */
    key_init();                         /* ��ʼ������ */
    adc3_init();                        /* ��ʼ��ADC */
    pwmdac_init(256 - 1, 0);            /* PWM DAC��ʼ��, Fpwm = 72M / 256 =281.25Khz */

    lcd_show_string(30,  50, 200, 16, 16, "STM32", RED);
    lcd_show_string(30,  70, 200, 16, 16, "PWM DAC TEST", RED);
    lcd_show_string(30,  90, 200, 16, 16, "ATOM@ALIENTEK", RED);
    lcd_show_string(30, 110, 200, 16, 16, "KEY_UP:+  KEY1:-", RED);
    lcd_show_string(30, 130, 200, 16, 16, "PWM VAL:", BLUE);
    lcd_show_string(30, 150, 200, 16, 16, "DAC VOL:0.000V", BLUE);
    lcd_show_string(30, 170, 200, 16, 16, "ADC VOL:0.000V", BLUE);

    while (1)
    {
        t++;
        key = key_scan(0);         /* ����ɨ�� */

        if (key == WKUP_PRES)      /* PWMռ�ձȵ��� */
        {
            if (pwmval < 250)      /* ��Χ�޶� */
            {
                pwmval += 10;
            }
            __HAL_TIM_SET_COMPARE(&g_tim1_handle, PWMDAC_TIMX_CHY, pwmval); /* ����µ�PWMռ�ձ� */
        }
        else if (key == KEY1_PRES) /* PWMռ�ձȵ��� */
        {
            if (pwmval > 10)       /* ��Χ�޶� */
            {
                pwmval -= 10;
            }
            else
            {
                pwmval = 0;
            }
             __HAL_TIM_SET_COMPARE(&g_tim1_handle, PWMDAC_TIMX_CHY, pwmval); /* ����µ�PWMռ�ձ� */
        }

        if (t == 10 || key == KEY1_PRES || key == WKUP_PRES)                 /* WKUP / KEY1 ������, ���߶�ʱʱ�䵽�� */
        {
            adcx = __HAL_TIM_GET_COMPARE(&g_tim1_handle, PWMDAC_TIMX_CHY);   /* PWM DAC ��ʱ������Ƚ�ֵ */
            lcd_show_xnum(94, 130, adcx, 3, 16, 0, BLUE);       /* ��ʾCCRX�Ĵ���ֵ */

            temp = (float)adcx * (3.3 / 256);                   /* �õ�DAC��ѹֵ */
            adcx = temp;
            lcd_show_xnum(94, 150, temp, 1, 16, 0, BLUE);       /* ��ʾ��ѹֵ�������� */

            temp -= adcx;
            temp *= 1000;
            lcd_show_xnum(110, 150, temp, 3, 16, 0X80, BLUE);   /* ��ʾ��ѹֵ��С������ */

            adcx = adc3_get_result_average(ADC3_CHY, 10);       /* �õ�ADC3ͨ��1��ת����� */
            temp = (float)adcx * (3.3 / 4096);                  /* �õ�ADC��ѹֵ(adc��12bit��) */
            adcx = temp;
            lcd_show_xnum(94, 170, temp, 1, 16, 0, BLUE);       /* ��ʾ��ѹֵ�������� */

            temp -= adcx;
            temp *= 1000;
            lcd_show_xnum(110, 170, temp, 3, 16, 0X80, BLUE);   /* ��ʾ��ѹֵ��С������ */

            LED0_TOGGLE(); /* LED0��˸ */
            t = 0;
        }

        delay_ms(10);
    }
}
