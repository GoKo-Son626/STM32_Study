#include "./BSP/GTIM/gtim.h"



TIM_HandleTypeDef tim5_handle_init;             //��ʱ��5���

void g_tim5_init(uint16_t prr, uint16_t pse)
{
    tim5_handle_init.Instance = TIM5;
    tim5_handle_init.Init.Period = prr;         //�Զ���װ��ֵ��ʱ�ڣ�
    tim5_handle_init.Init.Prescaler = pse;      //����ʱ����Ƶ��
    tim5_handle_init.Init.CounterMode = TIM_COUNTERMODE_UP;
    HAL_TIM_IC_Init(&tim5_handle_init);
    
    /* ��������ͨ��ӳ�䡢������ص� */
    TIM_IC_InitTypeDef tim5_ic_inittypedef = {0};
    /* ���벶�񴥷���ʽѡ�񣬱����������½��ز��� */
    tim5_ic_inittypedef.ICPolarity = TIM_ICPOLARITY_RISING;             /* �����ز��� */
    /* ���벶��ѡ����������ӳ���ϵ */ 
    tim5_ic_inittypedef.ICSelection  = TIM_ICSELECTION_DIRECTTI;        /* ӳ�䵽TI1�� */
    /* ���벶���Ƶϵ�� */ 
    tim5_ic_inittypedef.ICPrescaler = TIM_ICPSC_DIV1;                   /* ���������Ƶ������Ƶ */
    /* ���벶���˲������� */ 
    tim5_ic_inittypedef.ICFilter = 0;                                   /* ���������˲��������˲� */
    
    HAL_TIM_IC_ConfigChannel(&tim5_handle_init, &tim5_ic_inittypedef, TIM_CHANNEL_1); /* ��ʼ����TIM5��ͨ��1 */
    
    /* ʹ�ܶ�ʱ�������ж�|�Լ�|ʹ�ܲ��񡢲����жϼ������� */
    __HAL_TIM_ENABLE_IT(&tim5_handle_init, TIM_IT_UPDATE);
    HAL_TIM_IC_Start_IT(&tim5_handle_init, TIM_CHANNEL_1);

}

void HAL_TIM_IC_MspInit(TIM_HandleTypeDef *htim)
{
    if(htim->Instance == TIM5)
    {
        GPIO_InitTypeDef gpio_init_struct;
        __HAL_RCC_TIM5_CLK_ENABLE();//ʹ��TIMʱ��
        __HAL_RCC_GPIOA_CLK_ENABLE();                           //ʹ��GPIOʱ��

        gpio_init_struct.Pin = GPIO_PIN_0;                      /* Ҫ�����(����)GPIO���� */
        /* GPIO_MODE_AF_PP���ܣ�����������Ϊ���ù��ܣ�Alternate Function���������ŵĹ��ܲ�������ͨ��GPIO����������
        ���������裨��UART��I2C��SPI�ȣ����ơ�ͬʱ�����ģʽΪ����ģʽ��Push Pull����
        �����ſ�����������ߵ�ƽ��͵�ƽ���������������ؽϴ�ĳ��ϡ� */
        gpio_init_struct.Mode = GPIO_MODE_AF_PP;            /* ����������� */
        gpio_init_struct.Pull = GPIO_PULLUP;                    /* ƽʱ���� */
        gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;          /* ���٣���ʱ�����ޣ� */
        HAL_GPIO_Init(GPIOA, &gpio_init_struct);       /* ��ʼ��LED0���� */

        HAL_NVIC_SetPriority(TIM5_IRQn, 1, 3);     /* ��ռ1�������ȼ�3 */
        HAL_NVIC_EnableIRQ(TIM5_IRQn);             /* ����TIM5�ж� */
    }
}

/* ���벶��״̬(g_timxchy_cap_sta)
 * [7]  :0,û�гɹ��Ĳ���;1,�ɹ�����һ��.
 * [6]  :0,��û���񵽸ߵ�ƽ;1,�Ѿ����񵽸ߵ�ƽ��.
 * [5:0]:����ߵ�ƽ������Ĵ���,������63��,���������ֵ = 63*65536 + 65535 = 4194303
 *       ע��:Ϊ��ͨ��,����Ĭ��ARR��CCRy����16λ�Ĵ���,����32λ�Ķ�ʱ��(��:TIM5),Ҳֻ��16λʹ��
 *       ��1us�ļ���Ƶ��,����ʱ��Ϊ:4194303 us, Լ4.19��
 *
 *      (˵��һ�£�����32λ��ʱ����˵,1us��������1,���ʱ��:4294��)
 */
uint8_t g_timxchy_cap_sta = 0;    /* ���벶��״̬ */
uint16_t g_timxchy_cap_val = 0;   /* ���벶��ֵ */


/**
 * @brief       ��ʱ���жϷ�����
 * @param       ��
 * @retval      ��
 */
void TIM5_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&tim5_handle_init);  /* ��ʱ��HAL�⹲�ô����� */
}

/**
 * @brief       ��ʱ�����벶���жϴ���ص�����
 * @param       htim:��ʱ�����ָ��
 * @note        �ú�����HAL_TIM_IRQHandler�лᱻ����
 * @retval      ��
 */
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM5)
    {
        if ((g_timxchy_cap_sta & 0X80) == 0)                /* ��δ�ɹ����� */
        {
            if (g_timxchy_cap_sta & 0X40)                   /* ����һ���½��� */
            {
                g_timxchy_cap_sta |= 0X80;                  /* ��ǳɹ�����һ�θߵ�ƽ���� */
                g_timxchy_cap_val = HAL_TIM_ReadCapturedValue(&tim5_handle_init, TIM_CHANNEL_1);  /* ��ȡ��ǰ�Ĳ���ֵ */
                TIM_RESET_CAPTUREPOLARITY(&tim5_handle_init, TIM_CHANNEL_1);                      /* һ��Ҫ�����ԭ�������� */
                TIM_SET_CAPTUREPOLARITY(&tim5_handle_init, TIM_CHANNEL_1, TIM_ICPOLARITY_RISING); /* ����TIM5ͨ��1�����ز��� */
            }
            else /* ��δ��ʼ,��һ�β��������� */
            {
                g_timxchy_cap_sta = 0;                              /* ��� */
                g_timxchy_cap_val = 0;
                g_timxchy_cap_sta |= 0X40;                          /* ��ǲ����������� */
                __HAL_TIM_SET_COUNTER(&tim5_handle_init, 0);   /* ��ʱ��5���������� */
                TIM_RESET_CAPTUREPOLARITY(&tim5_handle_init, TIM_CHANNEL_1);   /* һ��Ҫ�����ԭ�������ã��� */
                TIM_SET_CAPTUREPOLARITY(&tim5_handle_init, TIM_CHANNEL_1, TIM_ICPOLARITY_FALLING); /* ��ʱ��5ͨ��1����Ϊ�½��ز��� */
            }
        }
    }
}

/**
 * @brief       ��ʱ�������жϻص�����
 * @param        htim:��ʱ�����ָ��
 * @note        �˺����ᱻ��ʱ���жϺ�����ͬ���õ�
 * @retval      ��
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM5)
    {
        if ((g_timxchy_cap_sta & 0X80) == 0)            /* ��δ�ɹ����� */
        {
            if (g_timxchy_cap_sta & 0X40)               /* �Ѿ����񵽸ߵ�ƽ�� */
            {
                if ((g_timxchy_cap_sta & 0X3F) == 0X3F) /* �ߵ�ƽ̫���� */
                {
                    TIM_RESET_CAPTUREPOLARITY(&tim5_handle_init, TIM_CHANNEL_1);                     /* һ��Ҫ�����ԭ�������� */
                    TIM_SET_CAPTUREPOLARITY(&tim5_handle_init, TIM_CHANNEL_1, TIM_ICPOLARITY_RISING);/* ����TIM5ͨ��1�����ز��� */
                    g_timxchy_cap_sta |= 0X80;          /* ��ǳɹ�������һ�� */
                    g_timxchy_cap_val = 0XFFFF;
                }
                else      /* �ۼƶ�ʱ��������� */
                {
                    g_timxchy_cap_sta++;
                }
            }
        }
    }
}













