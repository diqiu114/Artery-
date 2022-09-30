/**
  ******************************************************************************
  * File   : ETH/Telnet/eth_config.h
  * Version: V1.3.2
  * Date   : 2021-08-08
  * Brief  : This file contains all the functions prototypes for the ethernet
                configuration related.
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __EHT_CONFIG_H
#define __ETH_CONFIG_H

#define ETH_DRIVER_FAIL     (0)
#define ETH_DRIVER_SUCCESS  (1)

#ifdef __cplusplus
 extern "C" {
#endif

uint32_t System_Setup(void);
void NVIC_Configuration(void);
void GPIO_Configuration(void);
uint32_t Ethernet_Configuration(void);
#endif
