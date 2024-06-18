#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"

/******************************************************************************************/
/* �������´���, ֧��printf����, ������Ҫѡ��use MicroLIB */

#if 1

#if (__ARMCC_VERSION >= 6010050)            /* ʹ��AC6������ʱ */
__asm(".global __use_no_semihosting\n\t");  /* ������ʹ�ð�����ģʽ */
__asm(".global __ARM_use_no_argv \n\t");    /* AC6����Ҫ����main����Ϊ�޲�����ʽ�����򲿷����̿��ܳ��ְ�����ģʽ */

#else
/* ʹ��AC5������ʱ, Ҫ�����ﶨ��__FILE �� ��ʹ�ð�����ģʽ */
#pragma import(__use_no_semihosting)

struct __FILE
{
    int handle;
    /* Whatever you require here. If the only file you are using is */
    /* standard output using printf() for debugging, no file handling */
    /* is required. */
};

#endif

/* ��ʹ�ð�����ģʽ��������Ҫ�ض���_ttywrch\_sys_exit\_sys_command_string����,��ͬʱ����AC6��AC5ģʽ */
int _ttywrch(int ch)
{
    ch = ch;
    return ch;
}

/* ����_sys_exit()�Ա���ʹ�ð�����ģʽ */
void _sys_exit(int x)
{
    x = x;
}

char *_sys_command_string(char *cmd, int len)
{
    return NULL;
}


/* FILE �� stdio.h���涨��. */
FILE __stdout;

/* MDK����Ҫ�ض���fputc����, printf�������ջ�ͨ������fputc����ַ��������� */
int fputc(int ch, FILE *f)
{
    while ((USART2->SR & 0X40) == 0);     /* �ȴ���һ���ַ�������� */

    USART2->DR = (uint8_t)ch;             /* ��Ҫ���͵��ַ� ch д�뵽DR�Ĵ��� */
    return ch;
}
#endif
/******************************************************************************************/

UART_HandleTypeDef g_usart2_handle;  //���
uint16_t g_rx_buffer[10];             //HAL��ʹ�õĴ��ڽ������ݻ�����
uint8_t g_user_rx_buffer[1024];
uint16_t g_usart2_rx_flag = 0;       // ���ڽ��յ���־

/*  ����״̬
 *  bit15��      ������ɱ�־
 *  bit14��      ���յ�0x0d
 *  bit13~0��    ���յ�����Ч�ֽ���Ŀ
*/


/**
 * @brief       ����X��ʼ������
 * @param       baudrate: ������, �����Լ���Ҫ���ò�����ֵ
 * @note        ע��: ����������ȷ��ʱ��Դ, ���򴮿ڲ����ʾͻ������쳣.
 *              �����USART��ʱ��Դ��sys_stm32_clock_init()�������Ѿ����ù���.
 * @retval      ��
 */
void usart_init(uint32_t baudrate)
{
    /*UART ��ʼ������*/
    g_usart2_handle.Instance = USART2;                                       /* USART_UX */
    g_usart2_handle.Init.BaudRate = baudrate;                                  /* ������ */
    g_usart2_handle.Init.WordLength = UART_WORDLENGTH_8B;                      /* �ֳ�Ϊ8λ���ݸ�ʽ */
    g_usart2_handle.Init.StopBits = UART_STOPBITS_1;                           /* һ��ֹͣλ */
    g_usart2_handle.Init.Parity = UART_PARITY_NONE;                            /* ����żУ��λ */
    g_usart2_handle.Init.HwFlowCtl = UART_HWCONTROL_NONE;                      /* ��Ӳ������ */
    g_usart2_handle.Init.Mode = UART_MODE_TX_RX;                               /* �շ�ģʽ */
    HAL_UART_Init(&g_usart2_handle);                                           /* HAL_UART_Init()��ʹ��UART2 */

    HAL_UART_Receive_IT(&g_usart2_handle, (uint8_t*)g_rx_buffer, 1);
}

/* ����MSP�ص����� */
void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
    GPIO_InitTypeDef gpio_init_struct;
    if(huart->Instance == USART2)
    {
        //1.ʹ��USART2�Ͷ�ӦIOʱ��
        __USART2_CLK_ENABLE();
        __HAL_RCC_GPIOA_CLK_ENABLE();
        //2.��ʼ��IO
        gpio_init_struct.Pin = GPIO_PIN_2;                 
        gpio_init_struct.Mode = GPIO_MODE_AF_PP;            /* ����ʽ������� */
        gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;          /* ���� */
        HAL_GPIO_Init(GPIOA, &gpio_init_struct);       /* ��ʼ��IO���� */

        gpio_init_struct.Pin = GPIO_PIN_3;                 
        gpio_init_struct.Mode = GPIO_MODE_AF_INPUT;            /* ���� */
        gpio_init_struct.Pull = GPIO_PULLUP;                    /* ���� */
        HAL_GPIO_Init(GPIOA, &gpio_init_struct);       /* ��ʼ��LED0���� */
        //3.ʹ��USART1�жϣ��������ȼ�
        HAL_NVIC_SetPriority(USART2_IRQn, 3, 3);
        HAL_NVIC_EnableIRQ(USART2_IRQn);

    }
}

/* ����1�жϷ����� */
void USART2_IRQHandler(void)
{
    HAL_UART_IRQHandler(&g_usart2_handle);      // �жϷ������е���HAL��Ĺ���������
    HAL_UART_Receive_IT(&g_usart2_handle, (uint8_t*)g_rx_buffer, 1);
}

/* �ض����жϻص����� */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
//     g_usart2_rx_flag = 1;
    // �����û�н��ճɹ�
    if((g_usart2_rx_flag & 0x8000) == 0) {
        // ���յ�����0x0d
        if(g_rx_buffer[0] == 0x0d) {
            // ���ճɹ�
            g_usart2_rx_flag |= 0x8000;
        } else{
            g_user_rx_buffer[g_usart2_rx_flag++ & 0x3fff] = g_rx_buffer[0];
        }
    } else {
        // ʲôҲ�������Ѿ����ճɹ���
    }
}
