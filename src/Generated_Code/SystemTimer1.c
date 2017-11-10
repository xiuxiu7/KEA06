/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : SystemTimer1.c
**     Project     : NIOday_Stop
**     Processor   : MKE06Z128VLD4
**     Component   : TimerUnit_LDD
**     Version     : Component 01.164, Driver 01.11, CPU db: 3.00.000
**     Repository  : Kinetis
**     Compiler    : GNU C Compiler
**     Date/Time   : 2017-11-07, 21:07, # CodeGen: 2
**     Abstract    :
**          This TimerUnit component provides a low level API for unified hardware access across
**          various timer devices using the Prescaler-Counter-Compare-Capture timer structure.
**     Settings    :
**          Component name                                 : SystemTimer1
**          Module name                                    : SysTick
**          Counter                                        : SYST_CVR
**          Counter direction                              : Down
**          Counter width                                  : 24 bits
**          Value type                                     : Optimal
**          Input clock source                             : Internal
**            Counter frequency                            : Auto select
**          Counter restart                                : On-match
**            Period device                                : SYST_RVR
**            Period                                       : 5 ms
**            Interrupt                                    : Enabled
**              Interrupt                                  : INT_SysTick
**              Interrupt priority                         : medium priority
**              ISR Name                                   : SystemTimer1_Interrupt
**          Channel list                                   : 0
**          Initialization                                 : 
**            Enabled in init. code                        : no
**            Auto initialization                          : no
**            Event mask                                   : 
**              OnCounterRestart                           : Enabled
**              OnChannel0                                 : Disabled
**              OnChannel1                                 : Disabled
**              OnChannel2                                 : Disabled
**              OnChannel3                                 : Disabled
**              OnChannel4                                 : Disabled
**              OnChannel5                                 : Disabled
**              OnChannel6                                 : Disabled
**              OnChannel7                                 : Disabled
**          CPU clock/configuration selection              : 
**            Clock configuration 0                        : This component enabled
**            Clock configuration 1                        : This component disabled
**            Clock configuration 2                        : This component disabled
**            Clock configuration 3                        : This component disabled
**            Clock configuration 4                        : This component disabled
**            Clock configuration 5                        : This component disabled
**            Clock configuration 6                        : This component disabled
**            Clock configuration 7                        : This component disabled
**     Contents    :
**         Init              - LDD_TDeviceData* SystemTimer1_Init(LDD_TUserData *UserDataPtr);
**         Deinit            - void SystemTimer1_Deinit(LDD_TDeviceData *DeviceDataPtr);
**         Enable            - LDD_TError SystemTimer1_Enable(LDD_TDeviceData *DeviceDataPtr);
**         Disable           - LDD_TError SystemTimer1_Disable(LDD_TDeviceData *DeviceDataPtr);
**         GetInputFrequency - uint32_t SystemTimer1_GetInputFrequency(LDD_TDeviceData *DeviceDataPtr);
**         GetPeriodTicks    - LDD_TError SystemTimer1_GetPeriodTicks(LDD_TDeviceData *DeviceDataPtr,...
**         ResetCounter      - LDD_TError SystemTimer1_ResetCounter(LDD_TDeviceData *DeviceDataPtr);
**         GetCounterValue   - SystemTimer1_TValueType SystemTimer1_GetCounterValue(LDD_TDeviceData...
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
** @file SystemTimer1.c
** @version 01.11
** @brief
**          This TimerUnit component provides a low level API for unified hardware access across
**          various timer devices using the Prescaler-Counter-Compare-Capture timer structure.
*/         
/*!
**  @addtogroup SystemTimer1_module SystemTimer1 module documentation
**  @{
*/         

/* MODULE SystemTimer1. */

#include "MQX1.h"
#include "SystemTimer1.h"
/* MQX Lite include files */
#include "mqxlite.h"
#include "mqxlite_prv.h"
#include "IO_Map.h"

#ifdef __cplusplus
extern "C" {
#endif 


typedef struct {
  LDD_RTOS_TISRVectorSettings SavedISRSettings_TUInterrupt; /* {MQXLite RTOS Adapter} Saved settings of allocated interrupt vector */
  LDD_TUserData *UserDataPtr;          /* RTOS device data structure */
} SystemTimer1_TDeviceData;

typedef SystemTimer1_TDeviceData *SystemTimer1_TDeviceDataPtr; /* Pointer to the device data structure. */

/* {MQXLite RTOS Adapter} Static object used for simulation of dynamic driver memory allocation */
static SystemTimer1_TDeviceData DeviceDataPrv__DEFAULT_RTOS_ALLOC;

#define AVAILABLE_EVENTS_MASK (LDD_TEventMask)(LDD_TIMERUNIT_ON_COUNTER_RESTART)

/* Internal method prototypes */
/*
** ===================================================================
**     Method      :  SystemTimer1_Init (component TimerUnit_LDD)
*/
/*!
**     @brief
**         Initializes the device. Allocates memory for the device data
**         structure, allocates interrupt vectors and sets interrupt
**         priority, sets pin routing, sets timing, etc. If the
**         property ["Enable in init. code"] is set to "yes" value then
**         the device is also enabled (see the description of the
**         [Enable] method). In this case the [Enable] method is not
**         necessary and needn't to be generated. This method can be
**         called only once. Before the second call of Init the [Deinit]
**         must be called first.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. This pointer will be
**                           passed as an event or callback parameter.
**     @return
**                         - Pointer to the dynamically allocated private
**                           structure or NULL if there was an error.
*/
/* ===================================================================*/
LDD_TDeviceData* SystemTimer1_Init(LDD_TUserData *UserDataPtr)
{
  /* Allocate device structure */
  SystemTimer1_TDeviceData *DeviceDataPrv;
  /* {MQXLite RTOS Adapter} Driver memory allocation: Dynamic allocation is simulated by a pointer to the static object */
  DeviceDataPrv = &DeviceDataPrv__DEFAULT_RTOS_ALLOC;
  DeviceDataPrv->UserDataPtr = UserDataPtr; /* Store the RTOS device structure */
  /* Interrupt vector(s) allocation */
  /* {MQXLite RTOS Adapter} Save old and set new interrupt vector (function handler and ISR parameter) */
  /* Note: Exception handler for interrupt is not saved, because it is not modified */
  DeviceDataPrv->SavedISRSettings_TUInterrupt.isrData = _int_get_isr_data(LDD_ivIndex_INT_SysTick);
  DeviceDataPrv->SavedISRSettings_TUInterrupt.isrFunction = _int_install_isr(LDD_ivIndex_INT_SysTick, SystemTimer1_Interrupt, DeviceDataPrv);
  /* SYST_CSR: ??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,COUNTFLAG=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,CLKSOURCE=0,TICKINT=0,ENABLE=0 */
  SYST_CSR = 0x00U;                    /* Clear control register */
  /* SYST_RVR: ??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,RELOAD=0x0003A97F */
  SYST_RVR = SysTick_RVR_RELOAD(0x0003A97F); /* Setup reload value */
  /* SYST_CVR: ??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,CURRENT=0 */
  SYST_CVR = SysTick_CVR_CURRENT(0x00); /* Clear current value */
  /* SCB_SHPR3: PRI_15=1 */
  SCB_SHPR3 = (uint32_t)((SCB_SHPR3 & (uint32_t)~(uint32_t)(
               SCB_SHPR3_PRI_15(0x02)
              )) | (uint32_t)(
               SCB_SHPR3_PRI_15(0x01)
              ));
  /* SYST_CSR: ??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,COUNTFLAG=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,CLKSOURCE=1,TICKINT=1,ENABLE=0 */
  SYST_CSR = (SysTick_CSR_CLKSOURCE_MASK | SysTick_CSR_TICKINT_MASK); /* Set up control register */
  /* Registration of the device structure */
  PE_LDD_RegisterDeviceStructure(PE_LDD_COMPONENT_SystemTimer1_ID,DeviceDataPrv);
  return ((LDD_TDeviceData *)DeviceDataPrv); /* Return pointer to the device data structure */
}

/*
** ===================================================================
**     Method      :  SystemTimer1_Deinit (component TimerUnit_LDD)
*/
/*!
**     @brief
**         Deinitializes the device. Switches off the device, frees the
**         device data structure memory, interrupts vectors, etc.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by Init method
*/
/* ===================================================================*/
void SystemTimer1_Deinit(LDD_TDeviceData *DeviceDataPtr)
{
  SystemTimer1_TDeviceData *DeviceDataPrv = (SystemTimer1_TDeviceData *)DeviceDataPtr;

  (void)DeviceDataPrv;
  SysTick_PDD_EnableDevice(SysTick_BASE_PTR, PDD_DISABLE);
  /* Interrupt vector(s) deallocation */
  /* {MQXLite RTOS Adapter} Restore interrupt vector (function handler and ISR parameter) */
  /* Note: Exception handler for interrupt is not restored, because it was not modified */
  (void)_int_install_isr(LDD_ivIndex_INT_SysTick, ((SystemTimer1_TDeviceDataPtr)DeviceDataPrv)->SavedISRSettings_TUInterrupt.isrFunction, ((SystemTimer1_TDeviceDataPtr)DeviceDataPrv)->SavedISRSettings_TUInterrupt.isrData);
  /* Unregistration of the device structure */
  PE_LDD_UnregisterDeviceStructure(PE_LDD_COMPONENT_SystemTimer1_ID);
  /* Deallocation of the device structure */
  /* {MQXLite RTOS Adapter} Driver memory deallocation: Dynamic allocation is simulated, no deallocation code is generated */
}

/*
** ===================================================================
**     Method      :  SystemTimer1_Enable (component TimerUnit_LDD)
*/
/*!
**     @brief
**         Enables the component - it starts the signal generation.
**         Events may be generated (see SetEventMask). The method is
**         not available if the counter can't be disabled/enabled by HW.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
**     @return
**                         - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - The component does not work in
**                           the active clock configuration
*/
/* ===================================================================*/
LDD_TError SystemTimer1_Enable(LDD_TDeviceData *DeviceDataPtr)
{
  (void)DeviceDataPtr;                 /* Parameter is not used, suppress unused argument warning */
  SysTick_PDD_EnableDevice(SysTick_BASE_PTR, PDD_ENABLE); /* Enable the device */
  return ERR_OK;
}

/*
** ===================================================================
**     Method      :  SystemTimer1_Disable (component TimerUnit_LDD)
*/
/*!
**     @brief
**         Disables the component - it stops signal generation and
**         events calling. The method is not available if the counter
**         can't be disabled/enabled by HW.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
**     @return
**                         - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - The component does not work in
**                           the active clock configuration
*/
/* ===================================================================*/
LDD_TError SystemTimer1_Disable(LDD_TDeviceData *DeviceDataPtr)
{
  (void)DeviceDataPtr;                 /* Parameter is not used, suppress unused argument warning */
  SysTick_PDD_EnableDevice(SysTick_BASE_PTR, PDD_DISABLE);
  return ERR_OK;
}

/*
** ===================================================================
**     Method      :  SystemTimer1_GetInputFrequency (component TimerUnit_LDD)
*/
/*!
**     @brief
**         Returns current input frequency of the counter in Hz as
**         32-bit unsigned integer number. This method can be used only
**         if ["Input clock source"] property is set to "internal".
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
**     @return
**                         - Input frequency
*/
/* ===================================================================*/
uint32_t SystemTimer1_GetInputFrequency(LDD_TDeviceData *DeviceDataPtr)
{
  (void)DeviceDataPtr;                 /* Parameter is not used, suppress unused argument warning */
  return SystemTimer1_CNT_INP_FREQ_U_0;
}

/*
** ===================================================================
**     Method      :  SystemTimer1_GetPeriodTicks (component TimerUnit_LDD)
*/
/*!
**     @brief
**         Returns the number of counter ticks before re-initialization.
**         See also method [SetPeriodTicks]. This method is available
**         only if the property ["Counter restart"] is switched to
**         'on-match' value.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
**     @param
**         TicksPtr        - Pointer to return value of the
**                           number of counter ticks before
**                           re-initialization
**     @return
**                         - Error code, possible codes:
**                           ERR_OK - OK 
**                           ERR_SPEED - The component does not work in
**                           the active clock configuration
*/
/* ===================================================================*/
LDD_TError SystemTimer1_GetPeriodTicks(LDD_TDeviceData *DeviceDataPtr, SystemTimer1_TValueType *TicksPtr)
{
  uint32_t tmp;

  (void)DeviceDataPtr;                 /* Parameter is not used, suppress unused argument warning */
  tmp = (SystemTimer1_TValueType)(SysTick_PDD_ReadReloadValueReg(SysTick_BASE_PTR));
  *TicksPtr = (SystemTimer1_TValueType)++tmp;
  *TicksPtr &= 0x00FFFFFFUL;
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  SystemTimer1_ResetCounter (component TimerUnit_LDD)
*/
/*!
**     @brief
**         Resets counter. If counter is counting up then it is set to
**         zero. If counter is counting down then counter is updated to
**         the reload value.
**         The method is not available if HW doesn't allow resetting of
**         the counter.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
**     @return
**                         - Error code, possible codes:
**                           ERR_OK - OK 
**                           ERR_SPEED - The component does not work in
**                           the active clock configuration
*/
/* ===================================================================*/
LDD_TError SystemTimer1_ResetCounter(LDD_TDeviceData *DeviceDataPtr)
{
  (void)DeviceDataPtr;                 /* Parameter is not used, suppress unused argument warning */
  /* {MQXLite RTOS Adapter} Critical section begin (RTOS function call is defined by MQXLite RTOS Adapter property) */
  _int_disable();
  if ((SysTick_PDD_GetEnableDeviceStatus(SysTick_BASE_PTR)) != 0U) {
    SysTick_PDD_EnableDevice(SysTick_BASE_PTR, PDD_DISABLE);
    SysTick_PDD_EnableDevice(SysTick_BASE_PTR, PDD_ENABLE);
  }
  /* {MQXLite RTOS Adapter} Critical section ends (RTOS function call is defined by MQXLite RTOS Adapter property) */
  _int_enable();
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  SystemTimer1_GetCounterValue (component TimerUnit_LDD)
*/
/*!
**     @brief
**         Returns the content of counter register. This method can be
**         used both if counter is enabled and if counter is disabled.
**         The method is not available if HW doesn't allow reading of
**         the counter.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
**     @return
**                         - Counter value (number of counted ticks).
*/
/* ===================================================================*/
SystemTimer1_TValueType SystemTimer1_GetCounterValue(LDD_TDeviceData *DeviceDataPtr)
{
  (void)DeviceDataPtr;                 /* Parameter is not used, suppress unused argument warning */
  return (SystemTimer1_TValueType)SysTick_PDD_ReadCurrentValueReg(SysTick_BASE_PTR);
}

/*
** ===================================================================
**     Method      :  SystemTimer1_Interrupt (component TimerUnit_LDD)
**
**     Description :
**         The method services the interrupt of the selected peripheral(s)
**         and eventually invokes event(s) of the component.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
void SystemTimer1_Interrupt(LDD_RTOS_TISRParameter _isrParameter)
{
  /* {MQXLite RTOS Adapter} ISR parameter is passed as parameter from RTOS interrupt dispatcher */
  SystemTimer1_TDeviceDataPtr DeviceDataPrv = (SystemTimer1_TDeviceDataPtr)_isrParameter;

  SysTick_PDD_ClearInterruptFlag(SysTick_BASE_PTR); /* Clear interrupt flag */
  SystemTimer1_OnCounterRestart(DeviceDataPrv->UserDataPtr); /* Invoke OnCounterRestart event */
}

/* END SystemTimer1. */

#ifdef __cplusplus
}  /* extern "C" */
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
