#include "adc.h"
#include "stm32u5xx_hal.h"
ADC_HandleTypeDef hadc1;

bool ConfigureADC(void)
{
        hadc1.Instance = ADC1;
        hadc1.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV1;
        hadc1.Init.Resolution = ADC_RESOLUTION_14B;
        hadc1.Init.GainCompensation = 0;
        hadc1.Init.ScanConvMode = ADC_SCAN_DISABLE;
        hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
        hadc1.Init.LowPowerAutoWait = DISABLE;
        hadc1.Init.ContinuousConvMode = DISABLE;
        hadc1.Init.NbrOfConversion = 1;
        hadc1.Init.DiscontinuousConvMode = DISABLE;
        hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
        hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_RISING;
        hadc1.Init.DMAContinuousRequests = DISABLE;
        hadc1.Init.TriggerFrequencyMode = ADC_TRIGGER_FREQ_HIGH;
        hadc1.Init.Overrun = ADC_OVR_DATA_PRESERVED;
        hadc1.Init.LeftBitShift = ADC_LEFTBITSHIFT_NONE;
        hadc1.Init.ConversionDataManagement = ADC_CONVERSIONDATA_DR;
        hadc1.Init.OversamplingMode = DISABLE;

        if (HAL_ADC_Init(&hadc1) != HAL_OK)
        {
                return false;
        }
        if (HAL_ADCEx_Calibration_Start(&hadc1, ADC_CALIB_OFFSET, ADC_SINGLE_ENDED) != HAL_OK)
        {
                return false;
        }
        return true;
}


void HAL_ADC_MspInit(ADC_HandleTypeDef *hadc)
{
        RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};
        /** Initializes the peripherals clock
         */
        PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADCDAC;
        PeriphClkInit.AdcDacClockSelection = RCC_ADCDACCLKSOURCE_HSI;
        HAL_StatusTypeDef retval = HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit);
        GPIO_InitTypeDef gpio_conf = {0};

        if (hadc->Instance == ADC1)
        {

                // Pin config for current sense
                __HAL_RCC_GPIOA_CLK_ENABLE();

                gpio_conf.Mode = GPIO_MODE_ANALOG;
                gpio_conf.Pull = GPIO_NOPULL;
                gpio_conf.Pin = GPIO_PIN_1;
                HAL_GPIO_Init(GPIOA, &gpio_conf);

                /* Peripheral clock enable */
                __HAL_RCC_ADC1_CLK_ENABLE();

                /* ADC1 interrupt Init */
                HAL_NVIC_SetPriority(ADC1_IRQn, 3U, 0);
                HAL_NVIC_EnableIRQ(ADC1_IRQn);
        }

}