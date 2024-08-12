//
// Created by Administrator on 2024/8/11.
//

#include "BuzzerControl.h"
#include "gpio.h"

/**
 * @author ; Misaki
 *
 * 实现基本的蜂鸣器控制
 */
void BeefStart()
{
    HAL_GPIO_WritePin(Beef_GPIO_Port, Beef_Pin, GPIO_PIN_RESET);
}


void BeefToggle()
{
    HAL_GPIO_TogglePin(Beef_GPIO_Port, Beef_Pin);
}

void BeefStop()
{
    HAL_GPIO_WritePin(Beef_GPIO_Port, Beef_Pin, GPIO_PIN_SET);
}