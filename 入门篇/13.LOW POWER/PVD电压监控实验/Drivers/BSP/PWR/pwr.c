/**
 ****************************************************************************************************
 * @file        pwr.c
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2020-04-26
 * @brief       �͹���ģʽ ��������
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
 * V1.0 20200426
 * ��һ�η���
 *
 ****************************************************************************************************
 */

#include "./BSP/PWR/pwr.h"
#include "./BSP/LED/led.h"
#include "./BSP/LCD/lcd.h"


/**
 * @brief       ��ʼ��PVD��ѹ������
 * @param       pls: ��ѹ�ȼ�(PWR_PVD_detection_level)
 *   @arg       PWR_PVDLEVEL_0,2.2V;
 *   @arg       PWR_PVDLEVEL_1,2.3V;
 *   @arg       PWR_PVDLEVEL_2,2.4V;
 *   @arg       PWR_PVDLEVEL_3,2.5V;
 *   @arg       PWR_PVDLEVEL_4,2.6V;
 *   @arg       PWR_PVDLEVEL_5,2.7V;
 *   @arg       PWR_PVDLEVEL_6,2.8V;
 *   @arg       PWR_PVDLEVEL_7,2.9V;
 * @retval      ��
 */
void pwr_pvd_init(uint32_t pls)
{
    PWR_PVDTypeDef pwr_pvd = {0};

    __HAL_RCC_PWR_CLK_ENABLE();                      /* ʹ��PWRʱ�� */
    
    pwr_pvd.PVDLevel = pls;                          /* ����ѹ���� */
    pwr_pvd.Mode = PWR_PVD_MODE_IT_RISING_FALLING;   /* ʹ���ж��ߵ������غ��½���˫��Ե���� */
    HAL_PWR_ConfigPVD(&pwr_pvd);

    HAL_NVIC_SetPriority(PVD_IRQn, 3 ,3);
    HAL_NVIC_EnableIRQ(PVD_IRQn);
    HAL_PWR_EnablePVD();                             /* ʹ��PVD��� */
}

/**
 * @brief       PVD�жϷ�����
 * @param       ��
 * @retval      ��
 */
void PVD_IRQHandler(void)
{
    HAL_PWR_PVD_IRQHandler();
}

/**
 * @brief       PVD�жϷ���ص�����
 * @param       ��
 * @retval      ��
 */
void HAL_PWR_PVDCallback(void)
{
    if (__HAL_PWR_GET_FLAG(PWR_FLAG_PVDO)) /* ��ѹ��PLS��ѡ��ѹ���� */
    {
        lcd_show_string(30, 110, 200, 16, 16, "PVD Low Voltage!", RED); /* LCD��ʾ��ѹ�� */
        LED1(0);                                                        /* �����̵�, ������ѹ���� */
    }
    else
    {
        lcd_show_string(30, 110, 200, 16, 16, "PVD Voltage OK! ", BLUE); /* LCD��ʾ��ѹ���� */
        LED1(1);                                                         /* ����̵� */
    }
}










