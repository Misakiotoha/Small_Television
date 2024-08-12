//
// Created by Administrator on 2024/8/9.
//

/**
 * 代码链接 : https://www.cnblogs.com/zxr-blog/p/18088206
 */

#ifndef SMALL_TELEVISION_DHT11_H
#define SMALL_TELEVISION_DHT11_H

#include "usTIM.h"

/**
 * ************************************************************************
 *
 * @file My_DHT11.h
 * @author zxr
 * @brief
 *
 * ************************************************************************
 * @copyright Copyright (c) 2024 zxr
 * ************************************************************************
 */

#include "stm32f4xx_hal.h"

#define DHT11_PORT			GPIOA
#define DHT11_PIN			GPIO_PIN_0

#define DHT11_PULL_1		HAL_GPIO_WritePin(DHT11_PORT, DHT11_PIN, GPIO_PIN_SET)
#define DHT11_PULL_0		HAL_GPIO_WritePin(DHT11_PORT, DHT11_PIN, GPIO_PIN_RESET)

#define DHT11_ReadPin		HAL_GPIO_ReadPin(DHT11_PORT, DHT11_PIN)

/**
 * ************************************************************************
 * @brief 存储传感器数据的结构体
 *
 *
 * ************************************************************************
 */
typedef struct
{
    uint8_t humi_int;			// 湿度的整数部分
    uint8_t humi_dec;	 		// 湿度的小数部分
    uint8_t temp_int;	 		// 温度的整数部分
    uint8_t temp_dec;	 		// 温度的小数部分
    uint8_t check_sum;	 		// 校验和

} DHT11_Data_TypeDef;


uint8_t DHT11_ReadData(DHT11_Data_TypeDef* DHT11_Data);






#endif //SMALL_TELEVISION_DHT11_H
