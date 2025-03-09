/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file    tim.c
 * @brief   This file provides code for the configuration
 *          of the TIM instances.
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "tim.h"

/* USER CODE BEGIN 0 */
#include "adc.h"
/* USER CODE END 0 */

TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim7;
TIM_HandleTypeDef htim8;
TIM_HandleTypeDef htim16;

/* TIM2 init function */
void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 79;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 999;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 500;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */
  HAL_TIM_MspPostInit(&htim2);
}
/* TIM3 init function */
void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 79;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 499;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 250;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */
  HAL_TIM_MspPostInit(&htim3);
}
/* TIM7 init function */
void MX_TIM7_Init(void)
{

  /* USER CODE BEGIN TIM7_Init 0 */

  /* USER CODE END TIM7_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM7_Init 1 */

  /* USER CODE END TIM7_Init 1 */
  htim7.Instance = TIM7;
  htim7.Init.Prescaler = 79;
  htim7.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim7.Init.Period = 65535;
  htim7.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim7) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim7, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM7_Init 2 */

  /* USER CODE END TIM7_Init 2 */
}
/* TIM8 init function */
void MX_TIM8_Init(void)
{

  /* USER CODE BEGIN TIM8_Init 0 */

  /* USER CODE END TIM8_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_IC_InitTypeDef sConfigIC = {0};

  /* USER CODE BEGIN TIM8_Init 1 */

  /* USER CODE END TIM8_Init 1 */
  htim8.Instance = TIM8;
  htim8.Init.Prescaler = 79;
  htim8.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim8.Init.Period = 65535;
  htim8.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim8.Init.RepetitionCounter = 0;
  htim8.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim8) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim8, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_IC_Init(&htim8) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterOutputTrigger2 = TIM_TRGO2_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim8, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_RISING;
  sConfigIC.ICSelection = TIM_ICSELECTION_DIRECTTI;
  sConfigIC.ICPrescaler = TIM_ICPSC_DIV1;
  sConfigIC.ICFilter = 0;
  if (HAL_TIM_IC_ConfigChannel(&htim8, &sConfigIC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM8_Init 2 */

  /* USER CODE END TIM8_Init 2 */
}
/* TIM16 init function */
void MX_TIM16_Init(void)
{

  /* USER CODE BEGIN TIM16_Init 0 */

  /* USER CODE END TIM16_Init 0 */

  TIM_IC_InitTypeDef sConfigIC = {0};

  /* USER CODE BEGIN TIM16_Init 1 */

  /* USER CODE END TIM16_Init 1 */
  htim16.Instance = TIM16;
  htim16.Init.Prescaler = 79;
  htim16.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim16.Init.Period = 65535;
  htim16.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim16.Init.RepetitionCounter = 0;
  htim16.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim16) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_IC_Init(&htim16) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_RISING;
  sConfigIC.ICSelection = TIM_ICSELECTION_DIRECTTI;
  sConfigIC.ICPrescaler = TIM_ICPSC_DIV1;
  sConfigIC.ICFilter = 0;
  if (HAL_TIM_IC_ConfigChannel(&htim16, &sConfigIC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM16_Init 2 */

  /* USER CODE END TIM16_Init 2 */
}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *tim_baseHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if (tim_baseHandle->Instance == TIM2)
  {
    /* USER CODE BEGIN TIM2_MspInit 0 */

    /* USER CODE END TIM2_MspInit 0 */
    /* TIM2 clock enable */
    __HAL_RCC_TIM2_CLK_ENABLE();
    /* USER CODE BEGIN TIM2_MspInit 1 */

    /* USER CODE END TIM2_MspInit 1 */
  }
  else if (tim_baseHandle->Instance == TIM3)
  {
    /* USER CODE BEGIN TIM3_MspInit 0 */

    /* USER CODE END TIM3_MspInit 0 */
    /* TIM3 clock enable */
    __HAL_RCC_TIM3_CLK_ENABLE();
    /* USER CODE BEGIN TIM3_MspInit 1 */

    /* USER CODE END TIM3_MspInit 1 */
  }
  else if (tim_baseHandle->Instance == TIM7)
  {
    /* USER CODE BEGIN TIM7_MspInit 0 */

    /* USER CODE END TIM7_MspInit 0 */
    /* TIM7 clock enable */
    __HAL_RCC_TIM7_CLK_ENABLE();

    /* TIM7 interrupt Init */
    HAL_NVIC_SetPriority(TIM7_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(TIM7_IRQn);
    /* USER CODE BEGIN TIM7_MspInit 1 */

    /* USER CODE END TIM7_MspInit 1 */
  }
  else if (tim_baseHandle->Instance == TIM8)
  {
    /* USER CODE BEGIN TIM8_MspInit 0 */

    /* USER CODE END TIM8_MspInit 0 */
    /* TIM8 clock enable */
    __HAL_RCC_TIM8_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**TIM8 GPIO Configuration
    PA15     ------> TIM8_CH1
    */
    GPIO_InitStruct.Pin = GPIO_PIN_15;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF2_TIM8;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* TIM8 interrupt Init */
    HAL_NVIC_SetPriority(TIM8_CC_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(TIM8_CC_IRQn);
    /* USER CODE BEGIN TIM8_MspInit 1 */

    /* USER CODE END TIM8_MspInit 1 */
  }
  else if (tim_baseHandle->Instance == TIM16)
  {
    /* USER CODE BEGIN TIM16_MspInit 0 */

    /* USER CODE END TIM16_MspInit 0 */
    /* TIM16 clock enable */
    __HAL_RCC_TIM16_CLK_ENABLE();

    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**TIM16 GPIO Configuration
    PB4     ------> TIM16_CH1
    */
    GPIO_InitStruct.Pin = GPIO_PIN_4;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF1_TIM16;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* TIM16 interrupt Init */
    HAL_NVIC_SetPriority(TIM1_UP_TIM16_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(TIM1_UP_TIM16_IRQn);
    /* USER CODE BEGIN TIM16_MspInit 1 */

    /* USER CODE END TIM16_MspInit 1 */
  }
}
void HAL_TIM_MspPostInit(TIM_HandleTypeDef *timHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if (timHandle->Instance == TIM2)
  {
    /* USER CODE BEGIN TIM2_MspPostInit 0 */

    /* USER CODE END TIM2_MspPostInit 0 */
    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**TIM2 GPIO Configuration
    PA3     ------> TIM2_CH4
    */
    GPIO_InitStruct.Pin = GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF1_TIM2;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* USER CODE BEGIN TIM2_MspPostInit 1 */

    /* USER CODE END TIM2_MspPostInit 1 */
  }
  else if (timHandle->Instance == TIM3)
  {
    /* USER CODE BEGIN TIM3_MspPostInit 0 */

    /* USER CODE END TIM3_MspPostInit 0 */

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**TIM3 GPIO Configuration
    PA4     ------> TIM3_CH2
    */
    GPIO_InitStruct.Pin = GPIO_PIN_4;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF2_TIM3;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* USER CODE BEGIN TIM3_MspPostInit 1 */

    /* USER CODE END TIM3_MspPostInit 1 */
  }
}

void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef *tim_baseHandle)
{

  if (tim_baseHandle->Instance == TIM2)
  {
    /* USER CODE BEGIN TIM2_MspDeInit 0 */

    /* USER CODE END TIM2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_TIM2_CLK_DISABLE();
    /* USER CODE BEGIN TIM2_MspDeInit 1 */

    /* USER CODE END TIM2_MspDeInit 1 */
  }
  else if (tim_baseHandle->Instance == TIM3)
  {
    /* USER CODE BEGIN TIM3_MspDeInit 0 */

    /* USER CODE END TIM3_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_TIM3_CLK_DISABLE();
    /* USER CODE BEGIN TIM3_MspDeInit 1 */

    /* USER CODE END TIM3_MspDeInit 1 */
  }
  else if (tim_baseHandle->Instance == TIM7)
  {
    /* USER CODE BEGIN TIM7_MspDeInit 0 */

    /* USER CODE END TIM7_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_TIM7_CLK_DISABLE();

    /* TIM7 interrupt Deinit */
    HAL_NVIC_DisableIRQ(TIM7_IRQn);
    /* USER CODE BEGIN TIM7_MspDeInit 1 */

    /* USER CODE END TIM7_MspDeInit 1 */
  }
  else if (tim_baseHandle->Instance == TIM8)
  {
    /* USER CODE BEGIN TIM8_MspDeInit 0 */

    /* USER CODE END TIM8_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_TIM8_CLK_DISABLE();

    /**TIM8 GPIO Configuration
    PA15     ------> TIM8_CH1
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_15);

    /* TIM8 interrupt Deinit */
    HAL_NVIC_DisableIRQ(TIM8_CC_IRQn);
    /* USER CODE BEGIN TIM8_MspDeInit 1 */

    /* USER CODE END TIM8_MspDeInit 1 */
  }
  else if (tim_baseHandle->Instance == TIM16)
  {
    /* USER CODE BEGIN TIM16_MspDeInit 0 */

    /* USER CODE END TIM16_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_TIM16_CLK_DISABLE();

    /**TIM16 GPIO Configuration
    PB4     ------> TIM16_CH1
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_4);

    /* TIM16 interrupt Deinit */
    HAL_NVIC_DisableIRQ(TIM1_UP_TIM16_IRQn);
    /* USER CODE BEGIN TIM16_MspDeInit 1 */

    /* USER CODE END TIM16_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
u32 adc2_value = 0;
u32 mcp_value = 0;
u32 adc1_value = 0;
float adc2_volat = 0;
float adc1_volat = 0;
float mcp_volat = 0;
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if (htim == &htim7)
  {
    HAL_ADC_Start(&hadc1);
    mcp_value = HAL_ADC_GetValue(&hadc1);
    mcp_volat = (float)mcp_value / 4096.0f * 3.3f;

    HAL_ADC_Start(&hadc1);
    adc1_value = HAL_ADC_GetValue(&hadc1);
    adc1_volat = (float)adc1_value / 4096.0f * 3.3f;

    HAL_ADC_Start(&hadc2);
    adc2_value = HAL_ADC_GetValue(&hadc2);
    adc2_volat = (float)adc2_value / 4096.0f * 3.3f;
    HAL_ADC_Stop(&hadc2);
    HAL_TIM_Base_Start_IT(&htim7);
  }
}
u32 adc_tick = 0;
void ADC_proc()
{
  if (uwTick - adc_tick < 100)
    return;
  adc_tick = uwTick;
  HAL_ADC_Start(&hadc1);
  mcp_value = HAL_ADC_GetValue(&hadc1);
  mcp_volat = (float)mcp_value / 4096.0f * 3.3f;

  HAL_ADC_Start(&hadc1);
  adc1_value = HAL_ADC_GetValue(&hadc1);
  adc1_volat = (float)adc1_value / 4096.0f * 3.3f;

  HAL_ADC_Start(&hadc2);
  adc2_value = HAL_ADC_GetValue(&hadc2);
  adc2_volat = (float)adc2_value / 4096.0f * 3.3f;
  HAL_ADC_Stop(&hadc2);
}
/* Captured Values */
uint32_t tim16_ch1_value1 = 0;
uint32_t tim16_ch1_value2 = 0;
uint32_t tim16_ch1_value3 = 0;
uint32_t tim16_ch1_high = 0;
uint32_t tim16_ch1_low = 0;
uint16_t tim16_ch1_Index = 0;
uint32_t tim16_ch1_frq = 0;
u8 tim16_ch1_duty = 0;

uint32_t tim2_ch1_value1 = 0;
uint32_t tim2_ch1_value2 = 0;
uint32_t tim2_ch1_value3 = 0;
uint32_t tim2_ch1_high = 0;
uint32_t tim2_ch1_low = 0;
uint16_t tim2_ch1_Index = 0;
uint32_t tim2_ch1_frq = 0;
u8 tim2_ch1_duty = 0;
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
  if (htim == &htim16)
  {
    HAL_TIM_IC_Start_IT(&htim16, TIM_CHANNEL_1);
    if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)
    {
      if (tim16_ch1_Index == 0)
      {
        /* Get the 1st Input Capture value */
        tim16_ch1_value1 = HAL_TIM_ReadCapturedValue(&htim16, TIM_CHANNEL_1);
        tim16_ch1_Index = 1;
        __HAL_TIM_SET_CAPTUREPOLARITY(&htim16, TIM_CHANNEL_1, TIM_INPUTCHANNELPOLARITY_FALLING);
      }
      else if (tim16_ch1_Index == 1)
      {
        /* Get the 2nd Input Capture value */
        tim16_ch1_value2 = HAL_TIM_ReadCapturedValue(&htim16, TIM_CHANNEL_1);

        /* Capture computation */
        if (tim16_ch1_value2 > tim16_ch1_value1)
        {
          tim16_ch1_high = (tim16_ch1_value2 - tim16_ch1_value1);
        }
        else if (tim16_ch1_value2 < tim16_ch1_value1)
        {
          /* 0xFFFF is max TIM1_CCRx value */
          tim16_ch1_high = ((0xFFFF - tim16_ch1_value1) + tim16_ch1_value2) + 1;
        }
        else
        {
          /* If capture values are equal, we have reached the limit of frequency
             measures */
          Error_Handler();
        }
        tim16_ch1_Index = 2;
        __HAL_TIM_SET_CAPTUREPOLARITY(&htim16, TIM_CHANNEL_1, TIM_INPUTCHANNELPOLARITY_RISING);
        /* Frequency computation: for this example TIMx (TIM1) is clocked by
           APB2Clk */
      }
      else if (tim16_ch1_Index == 2)
      {
        tim16_ch1_value3 = HAL_TIM_ReadCapturedValue(&htim16, TIM_CHANNEL_1);
        if (tim16_ch1_value3 > tim16_ch1_value2)
        {
          tim16_ch1_low = (tim16_ch1_value3 - tim16_ch1_value2);
        }
        else if (tim16_ch1_value3 < tim16_ch1_value2)
        {
          /* 0xFFFF is max TIM1_CCRx value */
          tim16_ch1_low = ((0xFFFF - tim16_ch1_value2) + tim16_ch1_value3) + 1;
        }
        else
        {
          /* If capture values are equal, we have reached the limit of frequency
             measures */
          Error_Handler();
        }
        tim16_ch1_Index = 0;
        tim16_ch1_frq = 1e6 / (tim16_ch1_high + tim16_ch1_low);
        tim16_ch1_duty = 100 * tim16_ch1_high / (tim16_ch1_high + tim16_ch1_low);
      }
    }
  }
  if (htim == &htim8)
  {
    HAL_TIM_IC_Start_IT(&htim8, TIM_CHANNEL_1);
    if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)
    {
      if (tim2_ch1_Index == 0)
      {
        /* Get the 1st Input Capture value */
        tim2_ch1_value1 = HAL_TIM_ReadCapturedValue(&htim8, TIM_CHANNEL_1);
        tim2_ch1_Index = 1;
        __HAL_TIM_SET_CAPTUREPOLARITY(&htim8, TIM_CHANNEL_1, TIM_INPUTCHANNELPOLARITY_FALLING);
      }
      else if (tim2_ch1_Index == 1)
      {
        /* Get the 2nd Input Capture value */
        tim2_ch1_value2 = HAL_TIM_ReadCapturedValue(&htim8, TIM_CHANNEL_1);

        /* Capture computation */
        if (tim2_ch1_value2 > tim2_ch1_value1)
        {
          tim2_ch1_high = (tim2_ch1_value2 - tim2_ch1_value1);
        }
        else if (tim2_ch1_value2 < tim2_ch1_value1)
        {
          /* 0xFFFF is max TIM1_CCRx value */
          tim2_ch1_high = ((0xFFFF - tim2_ch1_value1) + tim2_ch1_value2) + 1;
        }
        else
        {
          /* If capture values are equal, we have reached the limit of frequency
             measures */
          Error_Handler();
        }
        tim2_ch1_Index = 2;
        __HAL_TIM_SET_CAPTUREPOLARITY(&htim8, TIM_CHANNEL_1, TIM_INPUTCHANNELPOLARITY_RISING);
        /* Frequency computation: for this example TIMx (TIM1) is clocked by
           APB2Clk */
      }
      else if (tim2_ch1_Index == 2)
      {
        tim2_ch1_value3 = HAL_TIM_ReadCapturedValue(&htim8, TIM_CHANNEL_1);
        if (tim2_ch1_value3 > tim2_ch1_value2)
        {
          tim2_ch1_low = (tim2_ch1_value3 - tim2_ch1_value2);
        }
        else if (tim2_ch1_value3 < tim2_ch1_value2)
        {
          /* 0xFFFF is max TIM1_CCRx value */
          tim2_ch1_low = ((0xFFFF - tim2_ch1_value2) + tim2_ch1_value3) + 1;
        }
        else
        {
          /* If capture values are equal, we have reached the limit of frequency
             measures */
          Error_Handler();
        }
        tim2_ch1_Index = 0;
        tim2_ch1_frq = 1e6 / (tim2_ch1_high + tim2_ch1_low);
        tim2_ch1_duty = 100 * tim2_ch1_high / (tim2_ch1_high + tim2_ch1_low);
      }
    }
  }
}

/* USER CODE END 1 */
