/**
  ******************************************************************************
  * @file main.c
  * @brief Teste
  * @author Ricardo Sena
  * @version V1.0.0
  * @date 05/03/2025
  ******************************************************************************
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm8s.h"
#include "stm8s_conf.h"

/* Private defines -----------------------------------------------------------*/
#define STM8S_DISCOVERY_LED	GPIOD, GPIO_PIN_0
#define HIGH_MAX 0x4F

/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/**
  ******************************************************************************
	* HardwareConfiguration()
  * @brief Configures hardware things
  * @par Parameters:
  * None
  * @retval void None
  * @par Required preconditions:
  * None
  ******************************************************************************
  */
void HardwareConfiguration(void)
{

  /* Fmaster = 16MHz */
	CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);

  /* GPIOD reset */
  GPIO_DeInit(GPIOD);

  /* Configure PD0 (LED1) as output push-pull low (led switched on) */
  GPIO_Init(STM8S_DISCOVERY_LED, GPIO_MODE_OUT_PP_LOW_FAST);

} /* HardwareConfiguration() */

/**
  ******************************************************************************
	* toggleLedAndWait()
  * @brief Toggle LED state and wait 0->highFF cicles
  * @par Parameters:
  * high uint32_t * 8^2 cicles
  * @retval void None
  * @par Required preconditions:
  * None
  ******************************************************************************
  */
void toggleLedAndWait(uint32_t high)
{
	uint32_t i=0;
	GPIO_WriteReverse(STM8S_DISCOVERY_LED);
	for (i=0; i<(uint32_t)((uint32_t)(high<<8)|0xFF); i++) {
		__asm("NOP");
	}
} /* toggleLedAndWait() */

/**
  ******************************************************************************
	* main()
  * @brief Main loop
  * @par Parameters:
  * None
  * @retval void None
  * @par Required preconditions:
  * None
  ******************************************************************************
  */
void main(void)
{
	
	uint32_t high=0;
	
	// hardware inicialization
  HardwareConfiguration();

  while (1)
  {
		// increase time between LED blinks
		for (; high<HIGH_MAX; high++) {
			toggleLedAndWait(high);
		}
		// decrease time between LED blinks
		for (; high>0x00; high--) {
			toggleLedAndWait(high);
		}
  }
} /* main() */

#ifdef USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param file: pointer to the source file name
  * @param line: assert_param error line source number
  * @retval : None
  */
void assert_failed(u8* file, u32 line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {

  }
}
#endif

/*****END OF FILE****/
