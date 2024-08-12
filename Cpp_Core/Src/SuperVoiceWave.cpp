//
// Created by Administrator on 2024/8/10.
//

#include "SuperVoiceWave.h"
#include "tim.h"

void SuperVoiceInit()
{
    HAL_TIM_Base_Start_IT(&htim8);  //初始化TIM8定时器
    HAL_TIM_IC_Start(&htim8, TIM_CHANNEL_1);
    HAL_TIM_IC_Start_IT(&htim8, TIM_CHANNEL_2);
}

int upEdge = 0;
int downEdge = 0;
float distance = 0;

float getDistance()
{
    //发出触发信号
    HAL_GPIO_WritePin(Super_Trig_GPIO_Port, Super_Trig_Pin, GPIO_PIN_SET);
    my_delay_us(45);
    HAL_GPIO_WritePin(Super_Trig_GPIO_Port, Super_Trig_Pin, GPIO_PIN_RESET);

    //清除计数器
    __HAL_TIM_SET_COUNTER(&htim8, 0);
    //等待中断函数执行完毕
    HAL_Delay(10);

    return distance;

}



//重写中断函数
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
    if(htim == &htim8){
        upEdge = HAL_TIM_ReadCapturedValue(&htim8, TIM_CHANNEL_1);
        downEdge = HAL_TIM_ReadCapturedValue(&htim8, TIM_CHANNEL_2);
        distance = (downEdge - upEdge) * 0.034 / 2;
    }
}


