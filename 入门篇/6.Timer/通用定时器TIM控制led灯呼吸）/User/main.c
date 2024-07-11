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
    
    HAL_Init();                                 /* 初始化HAL库 */
    sys_stm32_clock_init(RCC_PLL_MUL9);         /* 设置时钟,72M */
    delay_init(72);                             /* 初始化延时函数 */
    led_init();                                 /* 初始化LED */
    timr_tim_init(71, 499);
    
    while(1)
    {
        delay_ms(10);

        if (dir)ledrpwmval++;               /* dir==1 ledrpwmval递增 */
        else ledrpwmval--;                  /* dir==0 ledrpwmval递减 */

        if (ledrpwmval > 300)dir = 0;       /* ledrpwmval到达300后，方向为递减 */
        if (ledrpwmval == 0)dir = 1;        /* ledrpwmval递减到0后，方向改为递增 */

        /* 修改比较值控制占空比 */
        //使用 __HAL_TIM_SET_COMPARE 宏，可以快速、有效地修改定时器的比较值，适合实时控制场景。
        //使用 TIM_OC_InitTypeDef 结构体和相应的配置函数，适合初始化或需要重新配置定时器多个参数的场景。
        __HAL_TIM_SET_COMPARE(&g_tim_handle, TIM_CHANNEL_2, ledrpwmval);
        
    }
}

