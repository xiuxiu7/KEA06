/*
 * uart2can.c
 *
 *  Created on: 2017年11月7日
 *      Author: xiuxiu
 */

#include "uart2can.h"
#include "print.h"
#include "mqx_tasks.h"
#include "string.h"

#define cmd_len		50
uint8_t uart_rx_buf[cmd_len];
uint16_t uart_rx_index = 0;
const char *wireless_cmd_list[] =
{
	"stop",
	"others"
};

LWSEM_STRUCT sem_uart2can;

void tUart2can(void)
{
	uint8_t i;
	uint_8 candata[8];
	LDD_CAN_TFrame msg =
	{
		.MessageID = 0x5B,
		.Length = 8
	};
	memset(candata, 0, 8);
	candata[7] = 0x30;
	msg.Data = candata;

	_lwsem_create(&sem_uart2can, 0);

	UART_WIRELESS_ClearRxBuf();
	UART_WIRELESS_EnableEvent();
	MY_DEBUGF(((uint8_t*)"waiting uart data ...\r\n"));
	while(1)
	{
		_lwsem_wait(&sem_uart2can);
		LED_RED_ClrVal();

		for(i = 0; i < sizeof(wireless_cmd_list); i++)
		{
			if(!strcmp(uart_rx_buf, wireless_cmd_list[i]))
			{
				break;
			}
		}

		CAN1_SendFrame(CAN1_DeviceData, 1, &msg);

		MY_DEBUGF(((uint8_t*)"uart data ok!\r\n%s\r\n", wireless_cmd_list[i]));
		LED_RED_SetVal();
	}
}

void uart_wireless_rx_irqhandler(void)
{
	uint8_t data_rx;
	UART_WIRELESS_RecvChar(&data_rx);
	if( '\n' == data_rx)
	{
		uart_rx_buf[uart_rx_index] = '\0';
		_lwsem_post(&sem_uart2can);
	}else{
		uart_rx_buf[uart_rx_index] = data_rx;
		uart_rx_index++;
		if(uart_rx_index >= cmd_len)
		{
			uart_rx_index = 0;
		}
	}
}

void handle_show_rx_buf(void)
{
	uint8_t i;
	MY_DEBUGF(((uint8_t*)"RX:\r\n"));
	for(i = 0; i < cmd_len; i++)
	{
		MY_DEBUGF(((uint8_t*)"%d\r\n", uart_rx_buf[i]));
	}
}
