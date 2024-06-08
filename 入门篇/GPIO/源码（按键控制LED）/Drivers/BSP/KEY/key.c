#include "./BSP/KEY/key.h"
#include "./SYSTEM/delay/delay.h"

void key_init(void)
{
    GPIO_InitTypeDef gpio_init_struct;
    
    __HAL_RCC_GPIOE_CLK_ENABLE();
    
    gpio_init_struct.Pin = GPIO_PIN_2;
    gpio_init_struct.Mode = GPIO_MODE_INPUT;
    gpio_init_struct.Pull = GPIO_PULLUP;
    
    HAL_GPIO_Init(GPIOE, &gpio_init_struct);
    
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_2, GPIO_PIN_SET);
}

uint8_t key_scan(void)
{
    if(HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_2) == 0)
    {
        delay_ms(10);
        while(1)
        {
            while(HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_2) == 0);
            return 1;
        }
    }
    return 0;
}
