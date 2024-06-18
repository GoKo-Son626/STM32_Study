#include "./BSP/TIMER/btim.h"
#include "./BSP/LED/led.h"


TIM_HandleTypeDef g_btime_time6;


void btim_time6_init(uint16_t pre, uint16_t arr)
{
    g_btime_time6.Instance = TIM6;
    g_btime_time6.Init.Prescaler = pre;
    g_btime_time6.Init.Period = arr;
    
    HAL_TIM_Base_Init(&g_btime_time6);

    HAL_TIM_Base_Start_IT(&g_btime_time6);

}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
    if(htim->Instance == TIM6)
    {
        HAL_NVIC_SetPriority(TIM6_IRQn, 1, 3);
        HAL_NVIC_EnableIRQ(TIM6_IRQn);
        
        __HAL_RCC_TIM6_CLK_ENABLE();
    }
}

void TIM6_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&g_btime_time6);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(htim->Instance == TIM6)
    {
        LED0_TOGGLE();
    }
}









