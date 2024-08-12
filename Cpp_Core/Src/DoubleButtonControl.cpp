//
// Created by Administrator on 2024/8/10.
//

/**
 * @author : Misaki
 * @date : 2024/8/10
 * 本文件为控制相关的底层函数,为上层提供接口调用
 */


#include "DoubleButtonControl.h"
#include "adc.h"
#include "OLED.h"

//旋转编码器也放在了这个文件里面,喵喵不想看见很多很多的工程文件~
#include "tim.h"

void EncoderInit()
{
    HAL_TIM_Encoder_Start(&htim1, TIM_CHANNEL_ALL); //开启所有通道Encoder
}

int count = 0;
int isEW = 0;

//记录上一次的count值
int last_count = 0;

//辅助函数,限制count的值
void count_value()
{
    if(count >= 6000){  //防止count溢出产生问题
        count = 0;
        __HAL_TIM_SET_COUNTER(&htim1, 0);
    }
}

/**
 * @author : Misaki
 * @return
 * 思路 : 为了契合旋转编码器控制UI菜单的功能,我们只需要记录count上一次值和当前值的差即可
 */
int EncoderUpDown()
{
    count = __HAL_TIM_GET_COUNTER(&htim1);  //得到当前count的值
    count_value();

    //一个临时变量记录差值
    int temp = count - last_count;
    last_count = count; //更新last_count

    return temp;    //返回差值即可,由于编码器被预分频了,所以差值都为1或者-1
}

int EncoderEnter()
{
    if(isEW == 1){
//        HAL_Delay(500);
        isEW = 0;
        return 1;
    }
    return 0;
}




/**************************************分割线********************************************/

//ADC+DMA读取双轴按钮控制

uint16_t doubleX[5];
uint16_t doubleY[5];
int isSW=0;
int limit = 1000;

//辅助函数,限制limit的值
void limit_value()
{
    if(limit >= 1200){
        limit = 1200;
    }
    if(limit <= 800){
        limit = 800;
    }
}

void DoubleButtonInit()
{
    //开启ADC DMA
    HAL_ADC_Start_DMA(&hadc1, (uint32_t*)doubleX, 5);
    HAL_ADC_Start_DMA(&hadc2, (uint32_t*)doubleY, 5);

}

int DoubleButtonEnter()
{
    if(isSW == 1){
//        HAL_Delay(500);
        isSW = 0;
        return 1;
    }
    return 0;
}

int DoubleButtonUp()
{
    limit_value();
    if(doubleY[0]>=3000){
        limit += 20;
        if(limit == 1200){
            limit -= 60;    //回弹
            return 1;
        }
    }
    return 0;
}

int DoubleButtonDown()
{
    limit_value();
    if(doubleY[0]<=1000){
        limit -= 20;
        if(limit == 800){
            limit += 60;    //回弹
            return 1;
        }

    }
    return 0;
}

void test()
{
    OLED_ShowNum(0,0,doubleX[0],5,OLED_8X16);
    OLED_ShowNum(0,16,doubleY[0],5,OLED_8X16);
    OLED_ShowNum(0,32,isSW,1,OLED_8X16);
    OLED_Update();
}



/**************************************分割线********************************************/

//重写GPIO中断函数
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if(GPIO_Pin == GPIO_PIN_2){
        isSW = 1;
    }
    if(GPIO_Pin == GPIO_PIN_3){
        isEW = 1;
    }
}


