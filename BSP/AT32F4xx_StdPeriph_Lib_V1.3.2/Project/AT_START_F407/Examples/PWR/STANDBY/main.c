/**
  **************************************************************************
  * File   : PWR/STANDBY/main.c
  * Version: V1.3.2
  * Date   : 2021-08-08
  * Brief  : Main program body
  **************************************************************************
  */
 
 /* Includes ------------------------------------------------------------------*/
#include "at32f4xx.h"
#include "at32_board.h"

/** @addtogroup AT32F407_StdPeriph_Examples
  * @{
  */

/** @addtogroup PWR_STANDBY
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

GPIO_InitType GPIO_InitStructure;

/* Private function prototypes -----------------------------------------------*/

/**
  * @brief  RTC Alarm Configiguration.Setting alarm time.
  * @param  AlarmTim : RTC Alam new value.
  * @retval None
  */
void PWR_AlarmSet(uint8_t AlarmTim)
{
  RTC_ClearFlag(RTC_FLAG_PACE);
  while(RTC_GetFlagStatus(RTC_FLAG_PACE) == RESET);
  RTC_SetAlarmValue(RTC_GetCounter() + AlarmTim);
  RTC_WaitForLastTask();                 ///<Wait until last write operation on RTC registers has finished
}

/**
 *  @brief  RTC Configiguration.Configures RTC clock source and prescaler.
 *  @param  None
 *  @return None
 */
void RTC_Configuration(void)
{
  PWR_BackupAccessCtrl(ENABLE);
  BKP_Reset();                                       ///<Reset Backup Domain
  RCC_LSICmd(ENABLE);                                ///<Enable LSI OSC
  while(RCC_GetFlagStatus(RCC_FLAG_LSISTBL) == RESET)///<Wait till LSI is ready
  {
  }
  RCC_RTCCLKConfig(RCC_RTCCLKSelection_LSI);         ///<Select the RTC Clock Source
  RCC_RTCCLKCmd(ENABLE);                             ///<Enable the RTC Clock

  RTC_WaitForSynchro();                              ///<Wait for RTC APB registers synchronisation
  RTC_SetDIV(32767);                                 ///<Set the RTC time base to 1s
  RTC_WaitForLastTask();                             ///<Wait until last write operation on RTC registers has finished
}

/**
  * @brief  Main Function.
  * @param  None
  * @retval None
  */
int main(void)
{
  GPIO_StructInit(&GPIO_InitStructure);
  RCC_APB1PeriphClockCmd(RCC_APB1PERIPH_PWR | RCC_APB1PERIPH_BKP, ENABLE);
  AT32_Board_Init();
  AT32_LEDn_OFF(LED2);
  AT32_LEDn_OFF(LED3);
  AT32_LEDn_OFF(LED4);
  RTC_Configuration(); 
  Delay_sec(3);
  AT32_LEDn_ON(LED2);
  AT32_LEDn_ON(LED3);
  AT32_LEDn_ON(LED4);
  Delay_sec(8);

  PWR_AlarmSet(10u);
  RCC_LSEConfig(RCC_LSE_DISABLE);
  PWR_EnterSTANDBYMode();
  while(1)
  {
  }
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

  /* Infinite loop */
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

