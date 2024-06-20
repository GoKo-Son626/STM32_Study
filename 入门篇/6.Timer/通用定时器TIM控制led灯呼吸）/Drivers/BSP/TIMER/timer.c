#include "./BSP/TIMER/timer.h"

TIM_HandleTypeDef g_tim_handle;



void timr_tim_init(uint16_t psc, uint16_t arr)
{
    TIM_OC_InitTypeDef tim_oc_init = {0};
    
    g_tim_handle.Instance = TIM3;
    g_tim_handle.Init.Prescaler = psc;
    g_tim_handle.Init.Period = arr;
    g_tim_handle.Init.CounterMode = TIM_COUNTERMODE_UP;
    HAL_TIM_PWM_Init(&g_tim_handle);
    
    tim_oc_init.OCMode = TIM_OCMODE_PWM1;
    tim_oc_init.Pulse = arr / 2;
    tim_oc_init.OCPolarity = TIM_OCPOLARITY_LOW;
    
    
    HAL_TIM_PWM_ConfigChannel(&g_tim_handle, &tim_oc_init, TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(&g_tim_handle, TIM_CHANNEL_2);

}

void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim)
{
    if(htim->Instance == TIM3)
    {
        GPIO_InitTypeDef gpio_init_struct;
        __HAL_RCC_GPIOB_CLK_ENABLE();
        __HAL_RCC_TIM3_CLK_ENABLE();

        gpio_init_struct.Pin = GPIO_PIN_5;
        gpio_init_struct.Mode = GPIO_MODE_AF_PP;            /* 推挽式复用功能 */
        gpio_init_struct.Pull = GPIO_PULLUP;                    /* 上拉 */
        gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;          /* 高速 */
        HAL_GPIO_Init(GPIOB, &gpio_init_struct);
        //应为重映射，
        __HAL_RCC_AFIO_CLK_ENABLE();
        __HAL_AFIO_REMAP_TIM3_PARTIAL();
    }
}


