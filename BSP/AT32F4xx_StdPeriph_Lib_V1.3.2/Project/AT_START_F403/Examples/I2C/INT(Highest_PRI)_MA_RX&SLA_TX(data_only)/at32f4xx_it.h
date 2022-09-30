/**
  ******************************************************************************
  * File   : I2C/INT(Highest_PRI)_MA_RX&SLA_TX(data_only)/at32f4xx_it.h
  * Version: V1.3.2
  * Date   : 2021-08-08
  * Brief  : Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and peripherals
  *          interrupt service routine.
  ******************************************************************************
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __AT32F4XX_IT_H
#define __AT32F4XX_IT_H

/* Includes ------------------------------------------------------------------*/
#include "at32f4xx.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

void NMI_Handler(void);
void HardFault_Handler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);
void SVC_Handler(void);
void DebugMon_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);
void TMR3_GLOBAL_IRQHandler(void);

#endif /* __AT32F4XX_IT_H */

