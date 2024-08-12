/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define ADC1_IN10_Y_Pin GPIO_PIN_0
#define ADC1_IN10_Y_GPIO_Port GPIOC
#define ADC2_IN11_X_Pin GPIO_PIN_1
#define ADC2_IN11_X_GPIO_Port GPIOC
#define GPIO_EXTI2_BSW_Pin GPIO_PIN_2
#define GPIO_EXTI2_BSW_GPIO_Port GPIOC
#define GPIO_EXTI2_BSW_EXTI_IRQn EXTI2_IRQn
#define GPIO_EXTI3_BEN_Pin GPIO_PIN_3
#define GPIO_EXTI3_BEN_GPIO_Port GPIOC
#define GPIO_EXTI3_BEN_EXTI_IRQn EXTI3_IRQn
#define TIM1_CH1_S1_Pin GPIO_PIN_9
#define TIM1_CH1_S1_GPIO_Port GPIOE
#define TIM1_CH2_S2_Pin GPIO_PIN_11
#define TIM1_CH2_S2_GPIO_Port GPIOE
#define Beef_Pin GPIO_PIN_14
#define Beef_GPIO_Port GPIOD
#define Super_Trig_Pin GPIO_PIN_15
#define Super_Trig_GPIO_Port GPIOD
#define I2C1_SCL_C_Pin GPIO_PIN_6
#define I2C1_SCL_C_GPIO_Port GPIOB
#define I2C1_SDA_D_Pin GPIO_PIN_7
#define I2C1_SDA_D_GPIO_Port GPIOB
#define PB8_SCL_Pin GPIO_PIN_8
#define PB8_SCL_GPIO_Port GPIOB
#define PB9_SDA_Pin GPIO_PIN_9
#define PB9_SDA_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
