/* ###################################################################
**     Filename    : main.c
**     Project     : NIOday_Stop
**     Processor   : MKE06Z128VLD4
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2017-11-07, 20:38, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file main.c
** @version 01.01
** @brief
**         Main module.
**         This module contains user's application code.
*/         
/*!
**  @addtogroup main_module main module documentation
**  @{
*/         
/* MODULE main */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "mqx_tasks.h"
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
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "PDD_Includes.h"
#include "Init_Config.h"
/* User includes (#include below this line is not maintained by Processor Expert) */

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  /* For example: for(;;) { } */

  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
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
