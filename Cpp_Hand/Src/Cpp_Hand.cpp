//
// Created by Administrator on 2024/8/9.
//

/**
 * @author : Misaki
 * @date : 2024/8/9
 * C和C++握手
 */

#include "Cpp_Hand.h"
#include "TLB_OLED.h"

#include "DHT11.h"
#include "DS3231.h"
#include "cstdio"
#include "DoubleButtonControl.h"
#include "SuperVoiceWave.h"

TLB_OLED tO;



void Start_Hand()
{
    tO.Init();
    EncoderInit();
    SuperVoiceInit();
//    QF_DS3231_SetTime(24,8,9,10,10,10,1);
}



void Loop_Hand()
{
    while(1){

        tO.MainPage();


//        sprintf(str2,"Y:%d M:%d M:%d",DS.Year,DS.Minutes,DS.Seconds);
//        OLED_ShowString(0,32,str2,OLED_8X16);
//
//        OLED_ShowString(0,0,str,OLED_8X16);
//        OLED_ShowString(0,16,str1,OLED_8X16);
//        OLED_Update();
//        DoubleButtonInit();
//        test();
//        DoubleButtonEnter();

//        float distance = getDistance();
//        sprintf(str,"%..2f cm",distance);
//        OLED_ShowString(0,0,str,OLED_8X16);

//        OLED_ShowChinese(0,0,"星");

        tO.MENU();
    }
}

