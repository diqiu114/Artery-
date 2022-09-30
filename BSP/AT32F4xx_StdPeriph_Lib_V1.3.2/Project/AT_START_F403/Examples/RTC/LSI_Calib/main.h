/**
  ******************************************************************************
  * File   : RTC/LSI_Calib/main.h 
  * Version: V1.3.2
  * Date   : 2021-08-08
  * Brief  : Header file for main.c.
  ******************************************************************************
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/
#include "at32f4xx.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
uint32_t IncrementVar_OperationComplete(void);
uint32_t GetVar_OperationComplete(void);
void SetVar_PeriodValue(uint32_t Value);

#endif /* __MAIN_H*/

