#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/delay/delay.h"
#include "./SYSTEM/usart/usart.h"
#include "./BSP/LED/led.h"
#include "./BSP/TIMER/timer.h"

extern TIM_HandleTypeDef g_tim_handle;

int main(void)
{
    uint16_t ledrpwmval = 0;
    uint8_t dir = 1;
    
    HAL_Init();                                 /* ��ʼ��HAL�� */
    sys_stm32_clock_init(RCC_PLL_MUL9);         /* ����ʱ��,72M */
    delay_init(72);                             /* ��ʼ����ʱ���� */
    led_init();                                 /* ��ʼ��LED */
    timr_tim_init(71, 499);
    
    while(1)
    {
        delay_ms(10);

        if (dir)ledrpwmval++;               /* dir==1 ledrpwmval���� */
        else ledrpwmval--;                  /* dir==0 ledrpwmval�ݼ� */

        if (ledrpwmval > 300)dir = 0;       /* ledrpwmval����300�󣬷���Ϊ�ݼ� */
        if (ledrpwmval == 0)dir = 1;        /* ledrpwmval�ݼ���0�󣬷����Ϊ���� */

        /* �޸ıȽ�ֵ����ռ�ձ� */
        __HAL_TIM_SET_COMPARE(&g_tim_handle, TIM_CHANNEL_2, ledrpwmval);
        
    }
}

