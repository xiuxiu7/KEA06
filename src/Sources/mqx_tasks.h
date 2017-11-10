/* ###################################################################
**     Filename    : mqx_tasks.h
**     Project     : NIOday_Stop
**     Processor   : MKE06Z128VLD4
**     Component   : Events
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2017-11-07, 21:07, # CodeGen: 2
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
**     Contents    :
**         task_HB - void task_HB(uint32_t task_init_data);
**
** ###################################################################*/
/*!
** @file mqx_tasks.h
** @version 01.00
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/         
/*!
**  @addtogroup mqx_tasks_module mqx_tasks module documentation
**  @{
*/         

#ifndef __mqx_tasks_H
#define __mqx_tasks_H
/* MODULE mqx_tasks */

#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "AD1.h"
#include "AdcLdd1.h"
#include "UART_DEBUG.h"
#include "ASerialLdd1.h"
#include "UART_WIRELESS.h"
#include "ASerialLdd2.h"
#include "UART_BLUE.h"
#include "ASerialLdd3.h"
#include "DC_DIR_SET.h"
#include "BitsIoLdd1.h"
#include "LED_GREEN.h"
#include "BitIoLdd1.h"
#include "LED_RED.h"
#include "BitIoLdd2.h"
#include "IN2.h"
#include "BitIoLdd3.h"
#include "IN1.h"
#include "BitIoLdd4.h"
#include "IN3.h"
#include "BitIoLdd5.h"
#include "IN4.h"
#include "BitIoLdd6.h"
#include "MQX1.h"
#include "SystemTimer1.h"
#include "CAN1.h"

#ifdef __cplusplus
extern "C" {
#endif 

/*
** ===================================================================
**     Event       :  task_HB (module mqx_tasks)
**
**     Component   :  Task1 [MQXLite_task]
**     Description :
**         MQX task routine. The routine is generated into mqx_tasks.c
**         file.
**     Parameters  :
**         NAME            - DESCRIPTION
**         task_init_data  - 
**     Returns     : Nothing
** ===================================================================
*/
void task_HB(uint32_t task_init_data);


/*
** ===================================================================
**     Event       :  Task_uart2can (module mqx_tasks)
**
**     Component   :  Task2 [MQXLite_task]
**     Description :
**         MQX task routine. The routine is generated into mqx_tasks.c
**         file.
**     Parameters  :
**         NAME            - DESCRIPTION
**         task_init_data  - 
**     Returns     : Nothing
** ===================================================================
*/
void Task_uart2can(uint32_t task_init_data);

/*
** ===================================================================
**     Event       :  Task_cmd (module mqx_tasks)
**
**     Component   :  Task3 [MQXLite_task]
**     Description :
**         MQX task routine. The routine is generated into mqx_tasks.c
**         file.
**     Parameters  :
**         NAME            - DESCRIPTION
**         task_init_data  - 
**     Returns     : Nothing
** ===================================================================
*/
void Task_cmd(uint32_t task_init_data);

/* END mqx_tasks */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

#endif 
/* ifndef __mqx_tasks_H*/
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
