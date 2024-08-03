#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED/led.h"
#include "./BSP/LCD/lcd.h"
#include "./USMART/usmart.h"
#include "./BSP/RTC/rtc.h"

/* 定义字符数组用于显示周 */
char* weekdays[]={"Sunday","Monday","Tuesday","Wednesday",
                  "Thursday","Friday","Saterday"};

/* LED状态设置函数 */
void led_set(uint8_t sta)
{
    LED1(sta);
}

/* 函数参数调用测试函数 */
void test_fun(void(*ledset)(uint8_t), uint8_t sta)
{
    ledset(sta);
}

int main(void)
{
	uint8_t tbuf[40];
    uint8_t t = 0;
	
	
    HAL_Init();                         /* 初始化HAL库 */
    sys_stm32_clock_init(RCC_PLL_MUL9); /* 设置时钟, 72Mhz */
    delay_init(72);                     /* 延时初始化 */
    usart_init(115200);                 /* 串口初始化为115200 */
    usmart_dev.init(72);                /* 初始化USMART */
    led_init();                         /* 初始化LED */
    lcd_init();                         /* 初始化LCD */
    
	//rtc_set_alarm(2020, 4, 26, 9, 23, 45);  /* 设置一次闹钟 */
	
    lcd_show_string(30, 50, 200, 16, 16, "STM32", RED);
    lcd_show_string(30, 70, 200, 16, 16, "USMART TEST", RED);
    lcd_show_string(30, 90, 200, 16, 16, "ATOM@ALIENTEK", RED);
    
    while (1)
    {
        t++;

        if ((t % 10) == 0)                  /* 每100ms更新一次显示数据 */
        {
            rtc_get_time();
            sprintf((char *)tbuf, "Time:%02d:%02d:%02d", calendar.hour, calendar.min, calendar.sec);
            lcd_show_string(30, 120, 210, 16, 16, (char *)tbuf, RED);
            sprintf((char *)tbuf, "Date:%04d-%02d-%02d", calendar.year, calendar.month, calendar.date);
            lcd_show_string(30, 140, 210, 16, 16, (char *)tbuf, RED);
            sprintf((char *)tbuf, "Week:%s", weekdays[calendar.week]);
            lcd_show_string(30, 160, 210, 16, 16, (char *)tbuf, RED);
        }

        if ((t % 20) == 0)
        {
            LED0_TOGGLE();              /* 每200ms,翻转一次LED0 */
        }

        delay_ms(10);
    }
}
