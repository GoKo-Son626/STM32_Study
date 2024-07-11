#include "./BSP/GTIM/gtim.h"



TIM_HandleTypeDef tim5_handle_init;             //定时器5句柄

void g_tim5_init(uint16_t prr, uint16_t pse)
{
    tim5_handle_init.Instance = TIM5;
    tim5_handle_init.Init.Period = prr;         //自动重装载值（时期）
    tim5_handle_init.Init.Prescaler = pse;      //（定时器分频）
    tim5_handle_init.Init.CounterMode = TIM_COUNTERMODE_UP;
    HAL_TIM_IC_Init(&tim5_handle_init);
    
    /* 配置输入通道映射、捕获边沿等 */
    TIM_IC_InitTypeDef tim5_ic_inittypedef = {0};
    /* 输入捕获触发方式选择，比如上升、下降沿捕获 */
    tim5_ic_inittypedef.ICPolarity = TIM_ICPOLARITY_RISING;             /* 上升沿捕获 */
    /* 输入捕获选择，用于设置映射关系 */ 
    tim5_ic_inittypedef.ICSelection  = TIM_ICSELECTION_DIRECTTI;        /* 映射到TI1上 */
    /* 输入捕获分频系数 */ 
    tim5_ic_inittypedef.ICPrescaler = TIM_ICPSC_DIV1;                   /* 配置输入分频，不分频 */
    /* 输入捕获滤波器设置 */ 
    tim5_ic_inittypedef.ICFilter = 0;                                   /* 配置输入滤波器，不滤波 */
    
    HAL_TIM_IC_ConfigChannel(&tim5_handle_init, &tim5_ic_inittypedef, TIM_CHANNEL_1); /* 开始捕获TIM5的通道1 */
    
    /* 使能定时器更新中断|以及|使能捕获、捕获中断及计数器 */
    __HAL_TIM_ENABLE_IT(&tim5_handle_init, TIM_IT_UPDATE);
    HAL_TIM_IC_Start_IT(&tim5_handle_init, TIM_CHANNEL_1);

}

void HAL_TIM_IC_MspInit(TIM_HandleTypeDef *htim)
{
    if(htim->Instance == TIM5)
    {
        GPIO_InitTypeDef gpio_init_struct;
        __HAL_RCC_TIM5_CLK_ENABLE();//使能TIM时钟
        __HAL_RCC_GPIOA_CLK_ENABLE();                           //使能GPIO时钟

        gpio_init_struct.Pin = GPIO_PIN_0;                      /* 要捕获的(输入)GPIO引脚 */
        /* GPIO_MODE_AF_PP功能：将引脚配置为复用功能（Alternate Function），即引脚的功能不再是普通的GPIO输入或输出，
        而是由外设（如UART、I2C、SPI等）控制。同时，输出模式为推挽模式（Push Pull），
        即引脚可以主动输出高电平或低电平，适用于驱动负载较大的场合。 */
        gpio_init_struct.Mode = GPIO_MODE_AF_PP;            /* 复用推挽输出 */
        gpio_init_struct.Pull = GPIO_PULLUP;                    /* 平时下拉 */
        gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;          /* 高速（此时可有无） */
        HAL_GPIO_Init(GPIOA, &gpio_init_struct);       /* 初始化LED0引脚 */

        HAL_NVIC_SetPriority(TIM5_IRQn, 1, 3);     /* 抢占1，子优先级3 */
        HAL_NVIC_EnableIRQ(TIM5_IRQn);             /* 开启TIM5中断 */
    }
}

/* 输入捕获状态(g_timxchy_cap_sta)
 * [7]  :0,没有成功的捕获;1,成功捕获到一次.
 * [6]  :0,还没捕获到高电平;1,已经捕获到高电平了.
 * [5:0]:捕获高电平后溢出的次数,最多溢出63次,所以最长捕获值 = 63*65536 + 65535 = 4194303
 *       注意:为了通用,我们默认ARR和CCRy都是16位寄存器,对于32位的定时器(如:TIM5),也只按16位使用
 *       按1us的计数频率,最长溢出时间为:4194303 us, 约4.19秒
 *
 *      (说明一下：正常32位定时器来说,1us计数器加1,溢出时间:4294秒)
 */
uint8_t g_timxchy_cap_sta = 0;    /* 输入捕获状态 */
uint16_t g_timxchy_cap_val = 0;   /* 输入捕获值 */


/**
 * @brief       定时器中断服务函数
 * @param       无
 * @retval      无
 */
void TIM5_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&tim5_handle_init);  /* 定时器HAL库共用处理函数 */
}

/**
 * @brief       定时器输入捕获中断处理回调函数
 * @param       htim:定时器句柄指针
 * @note        该函数在HAL_TIM_IRQHandler中会被调用
 * @retval      无
 */
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM5)
    {
        if ((g_timxchy_cap_sta & 0X80) == 0)                /* 还未成功捕获 */
        {
            if (g_timxchy_cap_sta & 0X40)                   /* 捕获到一个下降沿 */
            {
                g_timxchy_cap_sta |= 0X80;                  /* 标记成功捕获到一次高电平脉宽 */
                g_timxchy_cap_val = HAL_TIM_ReadCapturedValue(&tim5_handle_init, TIM_CHANNEL_1);  /* 获取当前的捕获值 */
                TIM_RESET_CAPTUREPOLARITY(&tim5_handle_init, TIM_CHANNEL_1);                      /* 一定要先清除原来的设置 */
                TIM_SET_CAPTUREPOLARITY(&tim5_handle_init, TIM_CHANNEL_1, TIM_ICPOLARITY_RISING); /* 配置TIM5通道1上升沿捕获 */
            }
            else /* 还未开始,第一次捕获上升沿 */
            {
                g_timxchy_cap_sta = 0;                              /* 清空 */
                g_timxchy_cap_val = 0;
                g_timxchy_cap_sta |= 0X40;                          /* 标记捕获到了上升沿 */
                __HAL_TIM_SET_COUNTER(&tim5_handle_init, 0);   /* 定时器5计数器清零 */
                TIM_RESET_CAPTUREPOLARITY(&tim5_handle_init, TIM_CHANNEL_1);   /* 一定要先清除原来的设置！！ */
                TIM_SET_CAPTUREPOLARITY(&tim5_handle_init, TIM_CHANNEL_1, TIM_ICPOLARITY_FALLING); /* 定时器5通道1设置为下降沿捕获 */
            }
        }
    }
}

/**
 * @brief       定时器更新中断回调函数
 * @param        htim:定时器句柄指针
 * @note        此函数会被定时器中断函数共同调用的
 * @retval      无
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM5)
    {
        if ((g_timxchy_cap_sta & 0X80) == 0)            /* 还未成功捕获 */
        {
            if (g_timxchy_cap_sta & 0X40)               /* 已经捕获到高电平了 */
            {
                if ((g_timxchy_cap_sta & 0X3F) == 0X3F) /* 高电平太长了 */
                {
                    TIM_RESET_CAPTUREPOLARITY(&tim5_handle_init, TIM_CHANNEL_1);                     /* 一定要先清除原来的设置 */
                    TIM_SET_CAPTUREPOLARITY(&tim5_handle_init, TIM_CHANNEL_1, TIM_ICPOLARITY_RISING);/* 配置TIM5通道1上升沿捕获 */
                    g_timxchy_cap_sta |= 0X80;          /* 标记成功捕获了一次 */
                    g_timxchy_cap_val = 0XFFFF;
                }
                else      /* 累计定时器溢出次数 */
                {
                    g_timxchy_cap_sta++;
                }
            }
        }
    }
}













