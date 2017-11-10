/** ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : MQX1.h
**     Project     : NIOday_Stop
**     Processor   : MKE06Z128VLD4
**     Version     : Component 01.110, Driver 01.00, CPU db: 3.00.000
**     Repository  : Kinetis
**     Compiler    : GNU C Compiler
**     Date/Time   : 2017-11-07, 22:51, # CodeGen: 9
**     Abstract    :
**         MQX Lite RTOS Adapter component.
**     Settings    :
**
**     Copyright : 1997 - 2015 Freescale Semiconductor, Inc. 
**     All Rights Reserved.
**     
**     Redistribution and use in source and binary forms, with or without modification,
**     are permitted provided that the following conditions are met:
**     
**     o Redistributions of source code must retain the above copyright notice, this list
**       of conditions and the following disclaimer.
**     
**     o Redistributions in binary form must reproduce the above copyright notice, this
**       list of conditions and the following disclaimer in the documentation and/or
**       other materials provided with the distribution.
**     
**     o Neither the name of Freescale Semiconductor, Inc. nor the names of its
**       contributors may be used to endorse or promote products derived from this
**       software without specific prior written permission.
**     
**     THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**     ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**     WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**     DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**     ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**     LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**     ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**     (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**     SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**     
**     http: www.freescale.com
**     mail: support@freescale.com
** ###################################################################*/
/*!
** @file MQX1.h
** @version 01.00
** @brief
**         MQX Lite RTOS Adapter component.
*/         
/*!
**  @addtogroup MQX1_module MQX1 module documentation
**  @{
*/         

#ifndef __MQX1_H
#define __MQX1_H

/* MODULE MQX1. */

/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
/* Include inherited components */
#include "SystemTimer1.h"
#include "task_template_list.h"
/* MQX Lite include files */
#include "mqxlite.h"
#include "mqxlite_prv.h"


/* Path to MQX Lite source files */
#define MQX_PATH   "/opt/Freescale/KDS_v3/eclipse/ProcessorExpert/lib/mqxlite/V1.1.1/"

void      SystemTimer1_OnCounterRestart(LDD_TUserData *UserDataPtr);
uint32_t  SystemTimer1_GetTicsPerSecond(LDD_TDeviceData *DeviceDataPtr);


/* MQX Lite entrypoint */
void __boot(void);
/* SVC handler - called after SVC instruction */
void _svc_handler(void);
/* PendSV handler - task switch functionality */
void _pend_svc(void);
/* MQX Lite adapter system timer functions */
uint32_t system_timer_init (const void * timer_data_ptr);
uint32_t system_timer_start(const void * timer_data_ptr);

#define MQXLITE_SYSTEM_TIMER_INIT(param)    system_timer_init(param)
#define MQXLITE_SYSTEM_TIMER_START(param)   system_timer_start(param)
#define MQXLITE_SYSTEM_TIMER_GET_INPUT_FREQUENCY(param)         \
            SystemTimer1_GetInputFrequency(param)
#define MQXLITE_SYSTEM_TIMER_GET_PERIOD_TICKS(param, value)     \
            SystemTimer1_GetPeriodTicks(param, value)
#define MQXLITE_SYSTEM_TIMER_GET_COUNTER_VALUE(param)           \
            SystemTimer1_GetCounterValue(param)
#define MQXLITE_SYSTEM_TIMER_GET_TICKS_PER_SECOND(param)        \
            SystemTimer1_GetTicsPerSecond(param)
#define MQXLITE_SYSTEM_TIMER_SET_HWTICKS_FUNCTION(param)	\
            _time_set_hwtick_function((MQX_GET_HWTICKS_FPTR)&SystemTimer1_GetCounterValue, (pointer)(param))

void mqx_initialize_heap(void);


/* Task stacks declarations */
extern uint8_t HB_task_stack[HB_TASK_STACK_SIZE];
extern uint8_t uart2can_task_stack[UART2CAN_TASK_STACK_SIZE];
extern uint8_t cmd_task_stack[CMD_TASK_STACK_SIZE];

/* MQX Lite init structure and task template list */
extern const MQXLITE_INITIALIZATION_STRUCT       MQX_init_struct;
extern const TASK_TEMPLATE_STRUCT                MQX_template_list[];


/* MQX Lite initialization function */
#define PEX_RTOS_INIT()    if (MQX_OK != _mqxlite_init(&MQX_init_struct)) while(1)
/* MQX Lite start function */
#define PEX_RTOS_START()    _mqxlite()


/* The first interrupt vector that the application wants to have a 'C' ISR for.    */
#define FIRST_INTERRUPT_VECTOR_USED    (INT_SysTick)
/* The last interrupt vector that the application wants to handle. */
#define LAST_INTERRUPT_VECTOR_USED     (INT_MSCAN_TX)
#define MQX_INTERRUPT_TABLE_ITEMS      (LAST_INTERRUPT_VECTOR_USED - FIRST_INTERRUPT_VECTOR_USED + 1)
/* The table of 'C' handlers for interrupts. */
extern INTERRUPT_TABLE_STRUCT          mqx_static_isr_table[MQX_INTERRUPT_TABLE_ITEMS];


/* Task ready queue */
#define MQX_IDLE_TASK_PRIORITY         (9)
#define MQX_READY_QUEUE_ITEMS          (MQX_IDLE_TASK_PRIORITY + 1)
extern READY_Q_STRUCT                  mqx_static_ready_queue[MQX_READY_QUEUE_ITEMS];

/* Task stacks array of pointers */
extern const uint8_t * mqx_task_stack_pointers[];

void PEX_RTOS_InstallInterrupt(IRQInterruptIndex IntVector, void (*IsrFunction)(void *), void *IsrParam);
/*
** ===================================================================
**     Method      :  MQX1_PEX_RTOS_InstallInterrupt (component MQXLite)
**
**     Description :
**         Installs the interrupt service routine through the RTOS.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/



/* Backward compatibility */
#define MQXLITE_SYSTEM_TIMER_GET_TICS_PER_SECOND    MQXLITE_SYSTEM_TIMER_GET_TICKS_PER_SECOND

/* END MQX1. */

#endif
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.5 [05.21]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
