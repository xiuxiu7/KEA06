/** ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : task_template_list.h
**     Project     : NIOday_Stop
**     Processor   : MKE06Z128VLD4
**     Version     : Component 01.110, Driver 01.00, CPU db: 3.00.000
**     Repository  : Kinetis
**     Compiler    : GNU C Compiler
**     Date/Time   : 2017-11-09, 17:00, # CodeGen: 19
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
** @file task_template_list.h                                                  
** @version 01.00
*/         
/*!
**  @addtogroup task_template_list_module task_template_list module documentation
**  @{
*/         


#ifndef __task_template_list_h__
#define __task_template_list_h__

/* MQX Lite task IDs */
#define HB_TASK              1U
#define UART2CAN_TASK        2U
#define CMD_TASK             3U

/* MQX Lite task stack sizes */
#define HB_TASK_STACK_SIZE   (sizeof(TD_STRUCT) + 512 + PSP_STACK_ALIGNMENT + 1)
#define UART2CAN_TASK_STACK_SIZE (sizeof(TD_STRUCT) + 512 + PSP_STACK_ALIGNMENT + 1)
#define CMD_TASK_STACK_SIZE  (sizeof(TD_STRUCT) + 1024 + PSP_STACK_ALIGNMENT + 1)


#endif /* __task_template_list_h__ */

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
