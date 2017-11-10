/*
* print.c
*
*  Created on: 2017年11月7日
*      Author: xiuxiu
*/

#include "print.h"
#include <stdarg.h>
#include "UART_DEBUG.h"

void UARTwrite(const uint8_t *pcBuf, uint32_t ulLen)
{
	word bytesSended;
	while(0 != UART_DEBUG_GetCharsInTxBuf())  {}
		UART_DEBUG_SendBlock((UART_DEBUG_TComData*)pcBuf, (word)ulLen, &bytesSended);
}

/*
support %c, \%d, \%p, \%s, \%u,\%x, and \%X.
*/
const char * const g_pcHex = "0123456789abcdef";
void UARTprintf(const uint8_t *pcString, ...)
{
	uint32_t ulIdx;
	uint32_t ulValue;      
	uint32_t ulPos, ulCount;
	uint32_t ulBase;       
	uint32_t ulNeg;      
	uint8_t *pcStr;        
	uint8_t pcBuf[32]; 
	uint8_t cFill; 

	va_list vaArgP;

	va_start(vaArgP, pcString);
	while(*pcString)
	{

		for(ulIdx = 0; (pcString[ulIdx] != '%') && (pcString[ulIdx] != '\0'); ulIdx++)
			{ }
		UARTwrite(pcString, ulIdx);

		pcString += ulIdx;
		if(*pcString == '%')
		{
			pcString++;

			ulCount = 0;
			cFill = ' ';
			again:
			switch(*pcString++)
			{
				case '0': case '1': case '2': case '3': case '4':
				case '5': case '6': case '7': case '8': case '9':
				{

					if((pcString[-1] == '0') && (ulCount == 0))
					{
						cFill = '0';
					}
					ulCount *= 10;
					ulCount += pcString[-1] - '0';
					goto again;
				}
				case 'c':
				{
					ulValue = va_arg(vaArgP, unsigned long);
					UARTwrite((unsigned char *)&ulValue, 1);
					break;
				}
				case 'd':
				{
					ulValue = va_arg(vaArgP, unsigned long);
					ulPos = 0;

					if((long)ulValue < 0)
					{
						ulValue = -(long)ulValue;
						ulNeg = 1;
					}
					else
					{
						ulNeg = 0;
					}
					ulBase = 10;
					goto convert;
				}
				case 's':
				{
					pcStr = va_arg(vaArgP, unsigned char *);
					for(ulIdx = 0; pcStr[ulIdx] != '\0'; ulIdx++)
					{
					}
					UARTwrite(pcStr, ulIdx);
					if(ulCount > ulIdx)
					{
						ulCount -= ulIdx;
						while(ulCount--)
						{
							UARTwrite((uint8_t *)&" ", 1);
						}
					}
					break;
				}
				case 'u':
				{
					ulValue = va_arg(vaArgP, unsigned long);
					ulPos = 0;
					ulBase = 10;
					ulNeg = 0;
					goto convert;
				}
				case 'x': case 'X': case 'p':
				{
					ulValue = va_arg(vaArgP, unsigned long);
					ulPos = 0;
					ulBase = 16;
					ulNeg = 0;
					convert:  
					for(ulIdx = 1; (((ulIdx * ulBase) <= ulValue) &&(((ulIdx * ulBase) / ulBase) == ulIdx)); ulIdx *= ulBase, ulCount--)
						{ }
					if(ulNeg)
					{
						ulCount--;
					}
					if(ulNeg && (cFill == '0'))
					{
						pcBuf[ulPos++] = '-';
						ulNeg = 0;
					}
					if((ulCount > 1) && (ulCount < 16))
					{
						for(ulCount--; ulCount; ulCount--)
						{
							pcBuf[ulPos++] = cFill;
						}
					}

					if(ulNeg)
					{
						pcBuf[ulPos++] = '-';
					}
					for(; ulIdx; ulIdx /= ulBase)
					{
						pcBuf[ulPos++] = g_pcHex[(ulValue / ulIdx) % ulBase];
					}
					UARTwrite(pcBuf, ulPos);
					break;
				}
				case '%':
				{
					UARTwrite(pcString - 1, 1);
					break;
				}
				default:
				{
					UARTwrite((uint8_t *)&"ERROR", 5);
					break;
				}
			}
		}
	}

	va_end(vaArgP);
}


void printArray(uint8_t* data, uint32_t len)
{
	uint32_t i;
	if(len == 0)
		return;
	for(i = 0; i < len; i++)
	{
		MY_DEBUGF(((uint8_t*)&" %x", *(data + i)));
	}
	MY_DEBUGF(((uint8_t*)&"\r\n"));
}

void printCAN(uint8_t device, LDD_CAN_TFrame* msg)
{
	uint8_t i;
	MY_DEBUGF(((uint8_t*)&"can %d id %d data", device, msg->MessageID));
	for(i = 0; i < msg->Length; i++)
	{
		MY_DEBUGF(((uint8_t*)&" %d", msg->Data[i]));
	}
	MY_DEBUGF(((uint8_t *)&"\r\n"));
}


