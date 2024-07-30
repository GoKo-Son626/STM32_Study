
#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED/led.h"
#include "./BSP/WDG/wdg.h"


int main(void)
{
    HAL_Init();                             /* 初始化HAL库 */
    sys_stm32_clock_init(RCC_PLL_MUL9);     /* 设置时钟为72Mhz */
    delay_init(72);                         /* 延时初始化 */
    usart_init(115200);                     /* 串口初始化为115200 */
    led_init();
    

    if(__HAL_RCC_GET_FLAG(RCC_FLAG_WWDGRST) != RESET)
    {
        printf("窗口看门狗复位!\r\n");
        __HAL_RCC_CLEAR_RESET_FLAGS();
    }
    else
    {
        printf("外部复位！\r\n");
    }
    
    delay_ms(500);
    printf("请在窗口期内喂狗！\r\n");
    wwdg_init(0x7F, 0x5F, WWDG_PRESCALER_8);
    
    while(1)
    {
        delay_ms(25);
        HAL_WWDG_Refresh(&g_wwdg_handle);
        printf("喂狗完成！\n");
    }
    

}
