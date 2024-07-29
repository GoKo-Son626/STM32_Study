#include "./BSP/EXTI/exti.h"
#include "./SYSTEM/delay/delay.h"



void exti_init(void)
{
    //��ʼ��������GPIO
    __HAL_RCC_GPIOE_CLK_ENABLE();
    GPIO_InitTypeDef gpio_init_struct;
    gpio_init_struct.Pin = GPIO_PIN_4;
    gpio_init_struct.Mode = GPIO_MODE_IT_FALLING;
    gpio_init_struct.Pull = GPIO_PULLUP;
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOE, &gpio_init_struct);
    
    // �����ж����ȼ���ʹ���ж�
    HAL_NVIC_SetPriority(EXTI4_IRQn, 2, 0);
    HAL_NVIC_EnableIRQ(EXTI4_IRQn);
}

/* �жϹ��������� */

void EXTI4_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_4);
}


/* �жϻص����� */

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    delay_ms(20);
    
    if(GPIO_Pin == GPIO_PIN_4)
    {
           if(HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_4) == 0)
           {
               HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_5);
				  delay_ms(20);
           }
    }
}


