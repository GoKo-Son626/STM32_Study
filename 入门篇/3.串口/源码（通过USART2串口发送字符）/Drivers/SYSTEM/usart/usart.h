#ifndef _USART_H
#define _USART_H

#include "stdio.h"
#include "./SYSTEM/sys/sys.h"

extern UART_HandleTypeDef g_usart2_handle;
extern uint16_t g_rx_buffer[10];             //HAL��ʹ�õĴ��ڽ������ݻ�����
extern uint8_t g_user_rx_buffer[1024];             //HAL��ʹ�õĴ��ڽ������ݻ�����
extern uint16_t g_usart2_rx_flag;       // ���ڽ��յ���־

void usart_init(uint32_t baudrate);


#endif
