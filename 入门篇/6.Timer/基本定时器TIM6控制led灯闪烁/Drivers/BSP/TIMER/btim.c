#include "./BSP/TIMER/btim.h"
#include "./BSP/LED/led.h"

// 定时器句柄
TIM_HandleTypeDef g_btime_time6;


void btim_time6_init(uint16_t pre, uint16_t arr)
{
    g_btime_time6.Instance = TIM6;
    g_btime_time6.Init.Prescaler = pre;
    g_btime_time6.Init.Period = arr;
    
    HAL_TIM_Base_Init(&g_btime_time6);                  //初始化TIM，
    HAL_TIM_Base_Start_IT(&g_btime_time6);              //使能定时器及其更新中断

}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
    if(htim->Instance == TIM6)
    {
        __HAL_RCC_TIM6_CLK_ENABLE();                //开启时钟
        
        HAL_NVIC_SetPriority(TIM6_IRQn, 1, 3);      //设置优先级，使能中断
        HAL_NVIC_EnableIRQ(TIM6_IRQn);
    }
}
//定时器TIMX中断服务函数
void TIM6_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&g_btime_time6);
}
//定时器更新中断回调函数
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(htim->Instance == TIM6)
    {
        LED0_TOGGLE();
    }
}









