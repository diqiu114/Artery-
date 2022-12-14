/**
  **************************************************************************
  * File   : PWR/PVD/main.c
  * Version: V1.3.2
  * Date   : 2021-08-08
  * Brief  : Main program body
  **************************************************************************
  * @brief     : 
  */
 
 /* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include "at32f4xx.h"
#include "at32_board.h"

/** @addtogroup AT32F403A_StdPeriph_Examples
  * @{
  */

/** @addtogroup PWR_PVD
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
GPIO_InitType GPIO_InitStructure;
EXTI_InitType EXTI_InitStructure;
NVIC_InitType NVIC_InitStructure = {0};

/* Private function prototypes -----------------------------------------------*/
void EXTI_Configuration(void);
void NVIC_Configuration(void);

/* Private functions ---------------------------------------------------------*/

/**
 *  @brief  main function
 *  @param  None
 *  @retval None
 */
int main(void)
{
  uint32_t i;
  GPIO_StructInit(&GPIO_InitStructure);
  EXTI_StructInit(&EXTI_InitStructure);
  AT32_Board_Init();
  AT32_LEDn_ON(LED2);
  AT32_LEDn_ON(LED3);
  AT32_LEDn_ON(LED4);
  
  RCC_APB1PeriphClockCmd(RCC_APB1PERIPH_PWR | RCC_APB1PERIPH_BKP, ENABLE);
  PWR_PVDLevelConfig(PWR_PVDS_2V9);
  PWR_PVDCtrl(ENABLE);

  EXTI_Configuration();
  for(i=0;i<2000;i++);

  EXTI_ClearIntPendingBit(EXTI_Line16);
  NVIC_ClearPendingIRQ(PVD_IRQn);
  NVIC_Configuration();
  while (1)
  {
  }
}

/**
  * @brief  EXTI Configuration.Configures EXTI Line 16.
  * @param  None
  * @retval None
  */
void EXTI_Configuration(void)
{
  EXTI_ClearIntPendingBit(EXTI_Line16);
  EXTI_InitStructure.EXTI_Line        = EXTI_Line16;
  EXTI_InitStructure.EXTI_Mode        = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger     = EXTI_Trigger_Rising_Falling;
  EXTI_InitStructure.EXTI_LineEnable  = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
}

/**
  * @brief  NVIC Configuration.Configures NVIC and Vector Table base location.
  * @param  None
  * @retval None
  */
void NVIC_Configuration(void)
{
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
  NVIC_InitStructure.NVIC_IRQChannel                      = PVD_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority    = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority           = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd                   = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

/**
  * @}
  */ 

/**
  * @}
  */ 

