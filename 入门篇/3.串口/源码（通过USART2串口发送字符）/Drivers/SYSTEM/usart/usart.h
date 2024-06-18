#ifndef _USART_H
#define _USART_H

#include "stdio.h"
#include "./SYSTEM/sys/sys.h"

extern UART_HandleTypeDef g_usart2_handle;
extern uint16_t g_rx_buffer[10];             //HAL库使用的串口接收数据缓冲区
extern uint8_t g_user_rx_buffer[1024];             //HAL库使用的串口接收数据缓冲区
extern uint16_t g_usart2_rx_flag;       // 串口接收到标志

void usart_init(uint32_t baudrate);


#endif
