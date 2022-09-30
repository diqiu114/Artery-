/**
  ******************************************************************************
  * File   : USART/Smartcard/main.c 
  * Version: V1.3.2
  * Date   : 2021-08-08
  * Brief  : Main program body
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "at32f4xx.h"
#include "platform_config.h"
#include "at32_board.h"

/** @addtogroup AT32F415_StdPeriph_Examples
  * @{
  */

/** @addtogroup USART_Smartcard
  * @{
  */ 
  
/* Private define ------------------------------------------------------------*/
#define T0_PROTOCOL           0x00 /* T0 PROTOCOL */
#define SETUP_LENGHT          20 
#define HIST_LENGHT           20
#define SC_Receive_Timeout    0x4000 /* direction to reader */


/* Private typedef -----------------------------------------------------------*/
/* ATR STRUCTURE - ANSWER TO RESET */
typedef  struct 
{
  uint8_t TS; /* Bit Convention */
  uint8_t T0; /* High Nibble = N. of setup byte; low nibble = N. of historical byte */
  uint8_t T[SETUP_LENGHT]; /* Setup array */
  uint8_t H[HIST_LENGHT]; /* Historical array */
  uint8_t Tlenght; /* Setup array dimension */
  uint8_t Hlenght; /* Historical array dimension */
} SC_ATR;

typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
USART_InitType USART_InitStructure;
USART_ClockInitType USART_ClockInitStructure; 
SC_ATR  SC_A2R;
__IO uint32_t index_1 = 0, Counter = 0;
volatile TestStatus ATRDecodeStatus = FAILED;
__IO uint32_t CardInserted = 0, CardProtocol = 1;

__IO uint8_t DST_Buffer[50]= {
                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
void RCC_Configuration(void);
void GPIO_Configuration(void);
void EXTI_Configuration(void);
void NVIC_Configuration(void);
uint8_t SC_decode_Answer2reset(__IO uint8_t *card);

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{      
  /* System Clocks Configuration */
  RCC_Configuration();
       
  /* NVIC configuration */
  NVIC_Configuration();

  /* Configure the GPIO ports */
  GPIO_Configuration();

  /* Initialize Leds mounted on board */
  AT32_Board_Init();
  
  /* Configure the EXTI Controller */
  EXTI_Configuration();


/* SC_USART configuration ----------------------------------------------------*/
  /* SC_USART configured as follow:
        - Word Length = 9 Bits
        - 0.5 Stop Bit
        - Even parity
        - BaudRate = 12096 baud
        - Hardware flow control disabled (RTS and CTS signals)
        - Tx and Rx enabled
        - USART Clock enabled
        - USART CPOL Low
        - USART CPHA on first edge
        - USART Last Bit Clock Enabled
  */

  /* SC_USART Clock set to 4.36MHz (PCLK1 = 96 MHZ / 22) */
  USART_SetPrescaler(SC_USART, 11);
  /* SC_USART Guard Time set to 2 Bit */
  USART_SetGuardTime(SC_USART, 0x2);
  
  USART_ClockStructInit(&USART_ClockInitStructure);
  USART_ClockInitStructure.USART_Clock = USART_Clock_Enable;
  USART_ClockInit(SC_USART, &USART_ClockInitStructure);

  USART_StructInit(&USART_InitStructure);
  USART_InitStructure.USART_BaudRate = 12096;
  USART_InitStructure.USART_WordLength = USART_WordLength_9b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1_5;
  USART_InitStructure.USART_Parity = USART_Parity_Even;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_Init(SC_USART, &USART_InitStructure);  

  /* Enable the SC_USART Parity Error Interrupt */
  USART_INTConfig(SC_USART, USART_INT_PERR, ENABLE);

  /* Enable SC_USART */
  USART_Cmd(SC_USART, ENABLE);

  /* Enable the NACK Transmission */
  USART_SmartCardNACKCmd(SC_USART, ENABLE);

  /* Enable the Smartcard Interface */
  USART_SmartCardCmd(SC_USART, ENABLE);

  /* Loop while no Smartcard is detected */  
  while(CardInserted == 0)
  {
  }

  /* Read Smartcard ATR response */ 
  for(index_1 = 0; index_1 < 40; index_1++, Counter = 0)
  {
    while((USART_GetFlagStatus(SC_USART, USART_FLAG_RDNE) == RESET) && (Counter != SC_Receive_Timeout))
    {
      Counter++;
    }

    if(Counter != SC_Receive_Timeout)
    {
      DST_Buffer[index_1] = USART_ReceiveData(SC_USART);
    }
  }

  /* Decode ATR */
  CardProtocol = SC_decode_Answer2reset(DST_Buffer);

  /* Test if the inserted card is ISO7816-3 T=0 compatible */
  if(CardProtocol == 0)
  {
    /* Inserted card is ISO7816-3 T=0 compatible */
    ATRDecodeStatus = PASSED;
  }
  else 
  { 
    /* Inserted Smartcard is not ISO7816-3 T=0 compatible */
    ATRDecodeStatus = FAILED;
  } 

  /* Judge whether the result is correct */
  if(ATRDecodeStatus == PASSED)
  {
    /*Trun on the LED*/
    AT32_LEDn_ON(LED2);
    AT32_LEDn_ON(LED3);
    AT32_LEDn_ON(LED4);
  }
  while (1)
  {   
  }
}

/**
  * @brief  Configures the different system clocks.
  * @param  None
  * @retval None
  */
void RCC_Configuration(void)
{  
  /* Enable GPIO_3_5V, SC_USART_GPIO_CLK, GPIO_CMDVCC, GPIO_RESET, GPIO_OFF and 
     AFIO clocks */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_3_5V | SC_USART_GPIO_CLK | RCC_APB2Periph_RESET | 
                         RCC_APB2Periph_CMDVCC | RCC_APB2Periph_OFF | RCC_APB2PERIPH_AFIO, ENABLE);

  /* Enable SC_USART clocks */
  RCC_APB1PeriphClockCmd(SC_USART_CLK, ENABLE);
}

/**
  * @brief  Configures the different GPIO ports.
  * @param  None
  * @retval None
  */
void GPIO_Configuration(void)
{
  GPIO_InitType GPIO_InitStructure;

  /* Configure SC_USART CK as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pins = SC_USART_ClkPin;
  GPIO_InitStructure.GPIO_MaxSpeed = GPIO_MaxSpeed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(SC_USART_GPIO, &GPIO_InitStructure);

  /* Configure SC_USART Tx as alternate function open-drain */
  GPIO_InitStructure.GPIO_Pins = SC_USART_TxPin;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
  GPIO_Init(SC_USART_GPIO, &GPIO_InitStructure);

  /* Configure Smartcard Reset  */
  GPIO_InitStructure.GPIO_Pins = SC_RESET;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT_PP;
  GPIO_Init(GPIO_RESET, &GPIO_InitStructure);

  /* Set RSTIN HIGH */  
  GPIO_SetBits(GPIO_RESET, SC_RESET);

  /* Configure Smartcard 3/5V  */
  GPIO_InitStructure.GPIO_Pins = SC_3_5V;
  GPIO_Init(GPIO_3_5V, &GPIO_InitStructure);

  /* Select 5 V */  
  GPIO_SetBits(GPIO_3_5V, SC_3_5V);

  /* Configure Smartcard CMDVCC  */
  GPIO_InitStructure.GPIO_Pins = SC_CMDVCC;
  GPIO_Init(GPIO_CMDVCC, &GPIO_InitStructure);

  /* Select Smartcard CMDVCC */ 
  GPIO_SetBits(GPIO_CMDVCC, SC_CMDVCC);

  /* Select Smartcard OFF */
  GPIO_InitStructure.GPIO_Pins = SC_OFF;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIO_OFF, &GPIO_InitStructure);
}

/**
  * @brief  Configures the External Interrupts controller.
  * @param  None
  * @retval None
  */
void EXTI_Configuration(void)
{
  EXTI_InitType EXTI_InitStructure;

  /* Smartcard OFF */
  GPIO_EXTILineConfig(SC_PortSource, SC_PinSource);

  EXTI_StructInit(&EXTI_InitStructure);
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  EXTI_InitStructure.EXTI_Line = SC_EXTI;
  EXTI_InitStructure.EXTI_LineEnable = ENABLE;
  EXTI_Init(&EXTI_InitStructure);

  /* Clear SC EXTI Line Pending Bit */
  EXTI_ClearIntPendingBit(SC_EXTI);
}

/**
  * @brief  Configures the nested vectored interrupt controller.
  * @param  None
  * @retval None
  */
void NVIC_Configuration(void)
{
  NVIC_InitType NVIC_InitStructure;

  /* Configure the NVIC Preemption Priority Bits */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
  /* Clear the SC_EXTI IRQ Pending Bit */
  NVIC_ClearPendingIRQ(SC_EXTI_IRQ);

  NVIC_InitStructure.NVIC_IRQChannel = SC_EXTI_IRQ;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  NVIC_InitStructure.NVIC_IRQChannel = SC_USART_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

/**
  * @brief  Decode the Card ATR Response.
  * @param  card: pointer to the buffer containing the Card ATR.
  * @retval Card protocol
  */
uint8_t SC_decode_Answer2reset(__IO uint8_t *card)
{
  uint32_t i = 0, flag = 0, buf = 0, protocol = 0;

  SC_A2R.TS = 0;
  SC_A2R.T0 = 0;
  for (i = 0; i < SETUP_LENGHT; i++)
  {
    SC_A2R.T[i] = 0;
  }
  for (i = 0;i < HIST_LENGHT; i++)
  {
    SC_A2R.H[i] = 0;
  }
  SC_A2R.Tlenght = 0;
  SC_A2R.Hlenght = 0;

  SC_A2R.TS = card[0]; /* INITIAL CHARACTER */
  SC_A2R.T0 = card[1]; /* FORMAT CHARACTER */

  SC_A2R.Hlenght = SC_A2R.T0 & 0x0F;

  if((SC_A2R.T0 & 0x80) == 0x80) flag = 1;

  for(i = 0; i < 4; i++)
  {
    SC_A2R.Tlenght = SC_A2R.Tlenght + (((SC_A2R.T0 & 0xF0) >> (4 + i)) & 0x1);
  }

  for(i = 0; i < SC_A2R.Tlenght; i++)
  {
    SC_A2R.T[i] = card[i + 2];
  }

  protocol = SC_A2R.T[SC_A2R.Tlenght - 1] & 0x0F; 

  while(flag) 
  {
    if ((SC_A2R.T[SC_A2R.Tlenght-1] & 0x80)== 0x80)
    {
      flag = 1;
    }
    else
    {
      flag = 0;
    }
    buf = SC_A2R.Tlenght;
    SC_A2R.Tlenght = 0;

    for(i = 0; i < 4; i++)
    {
      SC_A2R.Tlenght = SC_A2R.Tlenght + (((SC_A2R.T[buf - 1] & 0xF0) >> (4 + i)) & 0x1);
    }
    for(i = 0; i < SC_A2R.Tlenght; i++)
    {
      SC_A2R.T[buf + i] = card[i + 2 + buf];
    }
    SC_A2R.Tlenght += buf;
  }

  for(i = 0;i < SC_A2R.Hlenght; i++)
  {
    SC_A2R.H[i] = card[i + 2 + SC_A2R.Tlenght];
  }
  
  return ((uint8_t)protocol);
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


