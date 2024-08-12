//
// Created by Administrator on 2024/8/9.
//
#include "tim.h"
#include "usTIM.h"

/**
 * ************************************************************************
 * @brief 基于32位定时器构造的微秒延时函数
 *
 * @param[in] us  微秒值
 * @note 选择32位定时器，可防止计数值溢出，避免加大运算量
 *
 * ************************************************************************
 */
void my_delay_us(uint32_t us)
{
    __HAL_TIM_SET_COUNTER(&htim5, 0);

    HAL_TIM_Base_Start(&htim5);

    while (__HAL_TIM_GET_COUNTER(&htim5) != us);

    HAL_TIM_Base_Stop(&htim5);
}
/**
 * ************************************************************************
 * @brief 基于32位定时器构造的毫秒延时函数
 *
 * @param[in] ms  毫秒值
 *
 * ************************************************************************
 */
void my_delay_ms(uint32_t ms)
{
    my_delay_us(ms * 1000);
}

