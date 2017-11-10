/*
 * print.h
 *
 *  Created on: 2017年11月7日
 *      Author: xiuxiu
 */

#ifndef SOURCES_DEV_PRINT_H_
#define SOURCES_DEV_PRINT_H_

#include <stdint.h>
#include <stdarg.h>
#include "PE_Types.h"

#define MY_DEBUG

void uart_send_process(void);

void UARTprintf(const uint8_t *pcString, ...);

void printArray(uint8_t* data, uint32_t len);

void printCAN(uint8_t device, LDD_CAN_TFrame* msg);

#ifdef MY_DEBUG
#define MY_DEBUGF(message) do { \
{UARTprintf message;} \
} while(0)
#else
#define MY_DEBUGF(message)
#endif



#endif /* SOURCES_DEV_PRINT_H_ */
