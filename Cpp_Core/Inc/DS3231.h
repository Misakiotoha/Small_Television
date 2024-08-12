//
// Created by Administrator on 2024/8/10.
//

#ifdef __cplusplus
extern "C"{
#endif

/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : DS3231.h
  * @brief          : Header for DS3231.c file.
  *                   This file provides code for the configuration
  *                   of the DS3231 instances
  * @author　　　　　 : 「千樊」
  * @time　　　　　　  :  2021-09-26
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BSP_DS3231_H_
#define __BSP_DS3231_H_

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "main.h"

/* USER CODE END Includes */
/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PT */

#define     I2C_WR                      0x00            //写指令
#define     I2C_RD                      0x01            //读指令
#define     DS3231_ADDRESS              0xD0           //DS3231地址

#define     Seconds_Register            0x00         //秒钟寄存器
#define     Minutes_Register            0x01         //分钟寄存器
#define     Hour_Register               0x02         //小时寄存器
#define     Week_Register               0x03      //星期寄存器
#define     Day_Register                0x04            //日期寄存器
#define     Month_Register              0x05        //月份寄存器
#define     Year_Register               0x06        //年份寄存器

typedef struct DS3231_time_t{
    uint8_t Seconds;
    uint8_t Minutes;
    uint8_t Hour;
    uint8_t Date;
    uint8_t Month;
    uint8_t Year;
    uint8_t Week;
}DS3231_time_t;

extern char* QF_WEEK_NAMES[];


/* USER CODE END PT */
/* Exported functions prototypes ---------------------------------------------*/
/* USER CODE BEGIN EFP */

void QF_DS3231_SetTime(uint8_t Yea,uint8_t Mon,uint8_t Dat,uint8_t Hou,uint8_t Min,uint8_t Sec,uint8_t Wee);
struct DS3231_time_t QF_DS3231_ReadTime_ReturnPoint(void);

/* USER CODE END EFP */

#endif /* __BSP_DS3231_H_ */


/************************ (C) COPYRIGHT Lesterbor *****END OF FILE*************/


#ifdef __cplusplus
}
#endif