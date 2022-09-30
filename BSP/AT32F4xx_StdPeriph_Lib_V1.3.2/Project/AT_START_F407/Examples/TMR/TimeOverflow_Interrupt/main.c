 /**
  ******************************************************************************
  * File   : TMR/TimeOverflow_Interrupt/main.c 
  * Version: V1.3.2
  * Date   : 2021-08-08
  * Brief  : Main program body
  ******************************************************************************
  */ 

#include "at32f4xx.h"
#include "at32_board.h"

/** @addtogroup AT32F407_StdPeriph_Examples
  * @{
  */

/** @addtogroup TMR_TimeOverflow_Interrupt
  * @{
  */
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/ 
TMR_TimerBaseInitType  TMR_TMReBaseStructure;
uint16_t PrescalerValue = 0;

/* Private function prototypes -----------------------------------------------*/
void RCC_Configuration(void);
void NVIC_Configuration(void);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
  /*!< At this stage the microcontroller clock setting is already configured,
       this is done through SystemInit() function which is called from startup
       file (startup_at32f407vgt7.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
       system_at32f4xx.c file
     */

  /* System Clocks Configuration */
  RCC_Configuration();

  /* NVIC Configuration */
  NVIC_Configuration();

  /* LED Configuration */
  AT32_LEDn_Init(LED2);

  /* ---------------------------------------------------------------
    TMR1 Configuration:
    TMR1 counter clock at 40 KHz
    TMR1 Period configured to 20000-1, that means each 500ms enter interrupt
  --------------------------------------------------------------- */

  /* Compute the prescaler value */
  PrescalerValue = (uint16_t) (SystemCoreClock / 40000) - 1;

  /* TMRe base configuration */
  TMR_TimeBaseStructInit(&TMR_TMReBaseStructure);
  TMR_TMReBaseStructure.TMR_Period = 20000-1;
  TMR_TMReBaseStructure.TMR_DIV = PrescalerValue;
  TMR_TMReBaseStructure.TMR_ClockDivision = 0;
  TMR_TMReBaseStructure.TMR_CounterMode = TMR_CounterDIR_Up;

  TMR_TimeBaseInit(TMR1, &TMR_TMReBaseStructure);

  /* TMR IT enable */
  TMR_INTConfig(TMR1, TMR_INT_Overflow, ENABLE);

  /* TMR1 enable counter */
  TMR_Cmd(TMR1, ENABLE);

  while (1);
}

/**
  * @brief  Configures the different system clocks.
  * @param  None
  * @retval None
  */
void RCC_Configuration(void)
{
  /* TMR1 clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2PERIPH_TMR1, ENABLE);
}

/**
  * @brief  Configure the nested vectored interrupt controller.
  * @param  None
  * @retval None
  */
void NVIC_Configuration(void)
{
  NVIC_InitType NVIC_InitStructure;

  /* Enable the TMR1 overflow Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = TMR1_OV_TMR10_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

  NVIC_Init(&NVIC_InitStructure);
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  while (1)
  {}
}

#endif
/**
  * @}
  */ 

/**
  * @}
  */

  

