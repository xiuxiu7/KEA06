/*
 * HB.c
 *
 *  Created on: 2017年11月7日
 *      Author: xiuxiu
 */

#include "hb.h"
#include "print.h"
#include "LED_GREEN.h"
#include "mqx_tasks.h"

uint8_t data_tx[5];

void tHB(void)
{
	uint32_t hb_cnt = 0;
	word bytesSended;
	MY_DEBUGF(((uint8_t*)"hello NIO day!\r\n"));
	while(1)
	{
		hb_cnt++;
		LED_GREEN_NegVal();
		_time_delay_ticks(100);
		MY_DEBUGF(((uint8_t*)"HB Debug %d", hb_cnt));
		UART_WIRELESS_SendBlock(data_tx, 5, &bytesSended);
	}
}
