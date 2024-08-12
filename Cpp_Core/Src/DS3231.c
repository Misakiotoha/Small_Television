//
// Created by Administrator on 2024/8/10.
//

/**
 * 源代码见 : https://www.cnblogs.com/lesterbor/p/17946871
 */


/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : DS3231.c
  * @brief          : DS3231 program body
  * @author         : 「千樊」
  * @time           : 2021-09-26
  * @update         : 2023-03-28
  ******************************************************************************
  * @attention
  *
  *
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "DS3231.h"
#include "i2c.h"

/* USER CODE END Includes */


/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PT */

char* QF_WEEK_NAMES[] = {"SUNDAY","MONDAY", "TUESDAY" ,"WEDNESDAY" ,"THURSDAY" ,"FRIDAY" ,"SATURDAY",};
struct DS3231_time_t DS3231_Buff;

/* USER CODE END PT */


/* Function definition -------------------------------------------------------*/
/* USER CODE BEGIN FD */
/**
  * @Function name  BCD_DEC
  * @Introduce      BCD(8421)转DEC
  * @Parameter      BCD(8421)值
  * @Return         DEC值
  */
uint8_t BCD_DEC(uint8_t BCD_Data){
    uint8_t DEC_Data;

    DEC_Data= BCD_Data&0x0f;
    BCD_Data >>= 4;
    BCD_Data &= 0x0f;
    BCD_Data *= 10;
    DEC_Data += BCD_Data;
    return DEC_Data;
}

/**
  * @Function name  DEC_BCD
  * @Introduce      DEC转BCD(8421)
  * @Parameter      DEC值
  * @Return         BCD(8421)值
  */
uint8_t DEC_BCD(uint8_t DEC_Data){
    uint8_t BCD_DataA,BCD_DataB,BCD_Data;

    BCD_DataA=DEC_Data/10;
    BCD_DataB=DEC_Data%10;
    BCD_Data=BCD_DataB+(BCD_DataA<<4);
    return BCD_Data;
}
/**
  * @Function name  I2C_DS3231_ReadData
  * @Introduce      DS3231通过I2C读取一个字节
  * @Parameter      ReadAddr I2C读取地址
  * @Return         NULL
  */
uint8_t I2C_DS3231_ReadData(uint8_t ReadAddr){
    uint8_t DS3231_DataAddr[1];
    DS3231_DataAddr[0]= ReadAddr;

    HAL_I2C_Master_Transmit(&hi2c1,(DS3231_ADDRESS|I2C_WR),DS3231_DataAddr,sizeof(DS3231_DataAddr), 1000);
    HAL_I2C_Master_Receive(&hi2c1,(DS3231_ADDRESS|I2C_RD),DS3231_DataAddr,sizeof(DS3231_DataAddr), 1000);
    return DS3231_DataAddr[0];
}

/**
  * @Function name  I2C_DS3231_WriteData
  * @Introduce      DS3231通过I2C写一个字节
  * @Parameter      WriteAddr I2C写入地址 Data I2C写入数据
  * @Return         NULL
  */
void I2C_DS3231_WriteData(uint8_t WriteAddr,uint8_t Data){
    uint8_t DS3231_Data[2];
    DS3231_Data[0]    = WriteAddr;
    DS3231_Data[1]    = Data;
    HAL_I2C_Master_Transmit(&hi2c1,(DS3231_ADDRESS|I2C_WR),DS3231_Data,sizeof(DS3231_Data), 1000);
}

/**
  * @Function name  DS3231_SetTime
  * @Introduce          DS3231通过I2C设置时间
  * @Parameter          Yea 年份范围在0~99
  *                     Mon    月份范围在0~12
  *                     Dat    日范围在1~31
  *                     Wee    周范围在1~7
  *                     Hou    小时范围在0~23
  *                     Min    分钟范围在0~59
  *                     Sec    秒范围在0~59
  * @Return             NULL
  */
void QF_DS3231_SetTime(uint8_t Yea,uint8_t Mon,uint8_t Dat,uint8_t Hou,uint8_t Min,uint8_t Sec,uint8_t Wee){
    I2C_DS3231_WriteData(Year_Register        ,DEC_BCD(Yea));
    I2C_DS3231_WriteData(Month_Register        ,DEC_BCD(Mon));
    I2C_DS3231_WriteData(Day_Register            ,DEC_BCD(Dat));
    I2C_DS3231_WriteData(Week_Register        ,DEC_BCD(Wee));
    I2C_DS3231_WriteData(Hour_Register        ,DEC_BCD(Hou));
    I2C_DS3231_WriteData(Minutes_Register    ,DEC_BCD(Min));
    I2C_DS3231_WriteData(Seconds_Register    ,DEC_BCD(Sec));
}

/**
  * @Function name  DS3231_ReadTime_ReturnPoint
  * @Introduce          将读到的时间数据通过指针返回
  * @Return                 NULL
  */
struct DS3231_time_t QF_DS3231_ReadTime_ReturnPoint(void){
    DS3231_Buff.Year        = BCD_DEC(I2C_DS3231_ReadData(Year_Register));
    DS3231_Buff.Month       = BCD_DEC(I2C_DS3231_ReadData(Month_Register));
    DS3231_Buff.Date         = BCD_DEC(I2C_DS3231_ReadData(Day_Register));
    DS3231_Buff.Hour        = BCD_DEC(I2C_DS3231_ReadData(Hour_Register));
    DS3231_Buff.Minutes      = BCD_DEC(I2C_DS3231_ReadData(Minutes_Register));
    DS3231_Buff.Seconds      = BCD_DEC(I2C_DS3231_ReadData(Seconds_Register));
    DS3231_Buff.Week        = BCD_DEC(I2C_DS3231_ReadData(Week_Register));
    return DS3231_Buff;
}

/* USER CODE END FD */
/************************ (C) COPYRIGHT 「千樊」 *****END OF FILE****/
