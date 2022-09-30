/**
  ******************************************************************************
  * File   : USB_Device/HID_IAP_Demo/inc/hw_config.h
  * Version: V1.3.2
  * Date   : 2021-08-08
  * Brief  : USB Hardware Configuration & setup header
  ******************************************************************************
  */


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HW_CONFIG_H
#define __HW_CONFIG_H

/* Includes ------------------------------------------------------------------*/
#include <at32f4xx.h>
#include "usb_type.h"


/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported define -----------------------------------------------------------*/
#define USBCLK_FROM_HSE  1
#define USBCLK_FROM_HSI  2

#define DOWN            1
#define LEFT            2
#define RIGHT           3
#define UP              4
#define CURSOR_STEP     40

/* Exported functions ------------------------------------------------------- */
void Set_System(void);
void Set_USBClock(u8 Clk_Source);
void GPIO_AINConfig(void);
void Enter_LowPowerMode(void);
void Leave_LowPowerMode(void);
void USB_Interrupts_Config(void);
void USB_Cable_Config (FunctionalState NewState);

void Get_SerialNum(void);
#endif  /*__HW_CONFIG_H*/


