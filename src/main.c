#include "stm32u5xx_hal.h"
#include "adc.h"

void ClockConfig(void);
static void PowerConfig(void);
extern ADC_HandleTypeDef hadc1;

int main(void)
{

  /* Reset of all peripherals, Initializes the Flash interface and the HAL timer. */
  HAL_Init();

  /* Configure the System Power */
  PowerConfig();

  /* Configure the system clock */
  ClockConfig();

  /* Configure ADC */
  ConfigureADC();

  while (1)
  {
    HAL_ADC_Start(&hadc1);
    while (HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY) != HAL_OK)
    {
      __NOP();
    }
    uint32_t __unused val = HAL_ADC_GetValue(&hadc1);

    HAL_Delay(500);
  }
  return 1;
}

//------------------------------------------------------------------------------
/**
 * @brief System Clock Configuration
 * @retval None
 */
void ClockConfig(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the CPU, AHB and APB busses clocks
   */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI48 | RCC_OSCILLATORTYPE_HSI | RCC_OSCILLATORTYPE_MSI | RCC_OSCILLATORTYPE_MSIK;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = RCC_MSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_4;
  RCC_OscInitStruct.MSIKState = RCC_MSIK_ON;
  RCC_OscInitStruct.MSIKClockRange = RCC_MSIKRANGE_4;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMBOOST = RCC_PLLMBOOST_DIV1;
  /* With fHSI==16MHz this yields a PLL output frequency of 160 MHz;
    no other divisor is necessary as it's equivalent to MSI(4MHz)+PLLM(1)
    */
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 80;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLLVCIRANGE_0;
  RCC_OscInitStruct.PLL.PLLFRACN = 0;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);

  /** Initializes the CPU, AHB and APB busses clocks
   */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2 | RCC_CLOCKTYPE_PCLK3;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_HCLK_DIV1;
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4);
}

/**
 * @brief Power Configuration - Enable stepdown converter + VDDA
 * @retval None
 */
static void PowerConfig(void)
{

  // Switch to SMPS regulator instead of LDO
  HAL_PWREx_ConfigSupply(PWR_SMPS_SUPPLY);

  /** Configure the main internal regulator output voltage
   * PWR_REGULATOR_VOLTAGE_SCALE1 --> up to 160 MHz
   */
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1);

  GPIO_InitTypeDef conf;
  conf.Mode = GPIO_MODE_OUTPUT_PP;
  conf.Alternate = 0;
  conf.Speed = GPIO_SPEED_FREQ_MEDIUM;
  conf.Pull = GPIO_NOPULL;

  __HAL_RCC_GPIOC_CLK_ENABLE();
  conf.Pin = GPIO_PIN_15;
  HAL_GPIO_Init(GPIOC, &conf);
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_15, GPIO_PIN_SET);

  conf.Pin = GPIO_PIN_14;
  HAL_GPIO_Init(GPIOC, &conf);
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_14, GPIO_PIN_SET);

  // Check the analog power before switching!
  /// REF: 10.6.3 of ref. manual
  // Enable AVM1
  HAL_PWREx_EnableAVM1();
  // Wait for AVM1 wakeup
  // Wait for VDDA1RDY
  while (!(PWR->SVMSR & PWR_SVMSR_VDDA1RDY))
    ;
  // Enable VDDA
  HAL_PWREx_EnableVddA();
  // Disable AVM1 for power saving
  HAL_PWREx_DisableAVM1();
}
