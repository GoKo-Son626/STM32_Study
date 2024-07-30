
#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED/led.h"
#include "./BSP/WDG/wdg.h"


int main(void)
{
    HAL_Init();                             /* ��ʼ��HAL�� */
    sys_stm32_clock_init(RCC_PLL_MUL9);     /* ����ʱ��Ϊ72Mhz */
    delay_init(72);                         /* ��ʱ��ʼ�� */
    usart_init(115200);                     /* ���ڳ�ʼ��Ϊ115200 */
    led_init();
    

    if(__HAL_RCC_GET_FLAG(RCC_FLAG_WWDGRST) != RESET)
    {
        printf("���ڿ��Ź���λ!\r\n");
        __HAL_RCC_CLEAR_RESET_FLAGS();
    }
    else
    {
        printf("�ⲿ��λ��\r\n");
    }
    
    delay_ms(500);
    printf("���ڴ�������ι����\r\n");
    wwdg_init(0x7F, 0x5F, WWDG_PRESCALER_8);
    
    while(1)
    {
        delay_ms(25);
        HAL_WWDG_Refresh(&g_wwdg_handle);
        printf("ι����ɣ�\n");
    }
    

}
