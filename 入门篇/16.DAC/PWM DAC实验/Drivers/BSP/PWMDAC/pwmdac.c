/**
 ****************************************************************************************************
 * @file        pwmdac.c
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2020-04-24
 * @brief       PWM DAC��� ��������
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
 * �޸�˵��
 * V1.0 20200424
 * ��һ�η���
 *
 ****************************************************************************************************
 */

#include "./BSP/PWMDAC/pwmdac.h"


TIM_HandleTypeDef g_tim1_handle;         /* ��ʱ����� */

/**
 * @brief       PWM DAC��ʼ��, ʵ���Ͼ��ǳ�ʼ����ʱ��
 * @note
 *              ��ʱ����ʱ������APB1 / APB2, ��APB1 / APB2 ��Ƶʱ, ��ʱ��Ƶ���Զ�����
 *              ����, һ�������, �������ж�ʱ����Ƶ��, ����72Mhz ����ϵͳʱ��Ƶ��
 *              ��ʱ�����ʱ����㷽��: Tout = ((arr + 1) * (psc + 1)) / Ft us.
 *              Ft = ��ʱ������Ƶ��, ��λ: Mhz
 *
 * @param       arr: �Զ���װֵ��
 * @param       psc: ʱ��Ԥ��Ƶ��
 * @retval      ��
 */
void pwmdac_init(uint16_t arr, uint16_t psc)
{
    TIM_OC_InitTypeDef timx_oc_pwmdac = {0};

    PWMDAC_TIMX_CLK_ENABLE();                                                     /* PWM DAC ��ʱ��ʱ��ʹ�� */

    g_tim1_handle.Instance = TIM1;                                                /* ��ʱ��1 */
    g_tim1_handle.Init.Prescaler = psc;                                           /* ��ʱ����Ƶ */
    g_tim1_handle.Init.CounterMode = TIM_COUNTERMODE_UP;                          /* ��������ģʽ */
    g_tim1_handle.Init.Period = arr;                                              /* �Զ���װ��ֵ */
    g_tim1_handle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;         /* ʹ��TIMx_ARR���л��� */
    HAL_TIM_PWM_Init(&g_tim1_handle);                                             /* ��ʼ��PWM */

    timx_oc_pwmdac.OCMode = TIM_OCMODE_PWM1;                                      /* CH1/2 PWMģʽ1 */
    timx_oc_pwmdac.Pulse = 0;                                                     /* ���ñȽ�ֵ,��ֵ����ȷ��ռ�ձ� */
    timx_oc_pwmdac.OCPolarity = TIM_OCPOLARITY_HIGH;                              /* ����Ƚϼ���Ϊ�� */
    HAL_TIM_PWM_ConfigChannel(&g_tim1_handle, &timx_oc_pwmdac, PWMDAC_TIMX_CHY);  /* ����TIM1ͨ��1 */

    HAL_TIM_PWM_Start(&g_tim1_handle, TIM_CHANNEL_1);                             /* ������ʱ��1ͨ��1 */
}

/**
 * @brief       ��ʱ���ײ�������ʱ��ʹ�ܣ���������
 * @note
 *              �˺����ᱻHAL_TIM_PWM_Init()����
 * @param       htim:��ʱ�����
 * @retval      ��
 */
void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim)
{
    GPIO_InitTypeDef gpio_init_struct;

    if (htim->Instance == TIM1)
    {
        __HAL_RCC_TIM1_CLK_ENABLE();                           /* ʹ�ܶ�ʱ��1 */
        __HAL_AFIO_REMAP_TIM1_PARTIAL();                       /* TIM1ͨ�����Ų�����ӳ��ʹ�� */
        PWMDAC_GPIO_CLK_ENABLE();                              /* GPIO ʱ��ʹ�� */

        gpio_init_struct.Pin = PWMDAC_GPIO_PIN;
        gpio_init_struct.Mode = GPIO_MODE_AF_PP;
        gpio_init_struct.Pull = GPIO_PULLUP;
        gpio_init_struct.Speed = GPIO_SPEED_FREQ_LOW;
        HAL_GPIO_Init(PWMDAC_GPIO_PORT, &gpio_init_struct);    /* TIMX PWM CHY ����ģʽ���� */
    }
}

/**
 * @brief       ����PWM DAC�����ѹ
 * @param       vol : 0~3300,����0~3.3V
 * @retval      ��
 */
void pwmdac_set_voltage(uint16_t vol)
{
    float temp = vol;
    temp /= 100;                                                    /* ��С100��, �õ�ʵ�ʵ�ѹֵ */
    temp = temp * 256 / 3.3;                                        /* ����ѹת����PWMռ�ձ� */
    __HAL_TIM_SET_COMPARE(&g_tim1_handle, PWMDAC_TIMX_CHY, temp);   /* �����µ�ռ�ձ� */
}



