#include "stm32u5xx_hal.h"
/**
  * Initializes the Global MSP.
  */
void HAL_MspInit(void)
{
  __HAL_RCC_PWR_CLK_ENABLE();
}