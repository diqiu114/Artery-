/**
  ******************************************************************************
  * File   : I2C/INT_SMBus_MA_TX&SLA_RX/at32f4xx_i2c_ex.h
  * Version: V1.3.2
  * Date   : 2021-08-08
  * Brief  : The header file of I2C driver.
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __AT32F4XX_I2C_EX_H
#define __AT32F4XX_I2C_EX_H

/* Includes ------------------------------------------------------------------*/
#include "at32f4xx.h"

/* Exported types ------------------------------------------------------------*/

/** @defgroup I2C_Exported_Types I2C Exported Types
  * @{
  */
  
/** 
  * @brief  I2C Status structures definition  
  */  
typedef enum 
{
  I2C_OK             = 0,
  
  I2C_ERROR_STEP_1   = 1,
  I2C_ERROR_STEP_2   = 2,
  I2C_ERROR_STEP_3   = 3,
  I2C_ERROR_STEP_4   = 4,
  I2C_ERROR_STEP_5   = 5,
  I2C_ERROR_STEP_6   = 6,
  I2C_ERROR_STEP_7   = 7,
  I2C_ERROR_STEP_8   = 8,  
  I2C_ERROR_STEP_9   = 9,
  I2C_ERROR_STEP_10  = 10,
  I2C_ERROR_STEP_11  = 11,
  I2C_ERROR_STEP_12  = 12,
  
  I2C_BUSY           = 100,
  I2C_TIMEOUT        = 101,
  I2C_ERROR          = 102,   

  I2C_START          = 110,  
  I2C_END            = 111,   
} I2C_StatusType;

/** 
  * @}
  */  

/* Exported constants --------------------------------------------------------*/

/** @defgroup I2C_Exported_Constants I2C Exported Constants
  * @{
  */

/** 
  * @brief  I2C Parameter definition  
  */  
#define I2C_SPEED                    100000
#define I2C_SLAVE_ADDRESS7           0xB0

/**
  * @brief  I2C Interface pins
  */
#define I2C_PORT                     I2C1
#define I2C_CLK                      RCC_APB1PERIPH_I2C1
#define I2C_SCL_PIN                  GPIO_Pins_6                  /* PB.06 */
#define I2C_SCL_GPIO_PORT            GPIOB                        /* GPIOB */
#define I2C_SCL_GPIO_CLK             RCC_AHBPERIPH_GPIOB
#define I2C_SCL_GPIO_PinsSource      GPIO_PinsSource6             
#define I2C_SCL_GPIO_GPIO_AF         GPIO_AF_1     

#define I2C_SDA_PIN                  GPIO_Pins_7                  /* PB.07 */
#define I2C_SDA_GPIO_PORT            GPIOB                        /* GPIOB */
#define I2C_SDA_GPIO_CLK             RCC_AHBPERIPH_GPIOB
#define I2C_SDA_GPIO_PinsSource      GPIO_PinsSource7             
#define I2C_SDA_GPIO_GPIO_AF         GPIO_AF_1    

#define I2Cx_EV_IRQn                 I2C1_EV_IRQn
#define I2Cx_ER_IRQn                 I2C1_ER_IRQn
#define I2Cx_EV_IRQHandler           I2C1_EV_IRQHandler
#define I2Cx_ER_IRQHandler           I2C1_ER_IRQHandler
/** 
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
#define MASTER_BOARD

/** @defgroup I2C_Exported_Macros I2C Exported Macros
  * @{
  */
/** 
  * @}
  */
/* Exported variables ------------------------------------------------------- */  
/* Exported functions ------------------------------------------------------- */

/** @addtogroup I2C_Exported_Functions
  * @{  
  */
  
  
void I2Cx_Init(I2C_Type* I2Cx);

I2C_StatusType I2C_Slave_Receive_INT(I2C_Type* I2Cx, uint8_t *pData, uint16_t Size, uint32_t Timeout);
I2C_StatusType I2C_Master_Transmit_INT(I2C_Type* I2Cx, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout);

void I2C_EV_IRQHandler(I2C_Type* I2Cx);
void I2C_ER_IRQHandler(I2C_Type* I2Cx);

/** 
  * @}
  */  

#endif /* __I2C_H */

