//
// Created by Administrator on 2024/8/9.
//

#include "TLB_OLED.h"
#include "cstdio"
#include "DHT11.h"
#include "DS3231.h"
#include "DoubleButtonControl.h"
#include "Funcs.h"

#include "BuzzerControl.h"

void TLB_OLED::Init()
{
    // 初始化
    OLED_Init();
}

DHT11_Data_TypeDef DHT11_Data;

DS3231_time_t DS;


/**
 * @author : Misaki
 * @brief : 系统启动界面
 */
void TLB_OLED::SystemStart()
{
    //TODO:实现开机启动动画
}

/**
 * @author : Misaki
 * @brief : 主界面
 */
void TLB_OLED::MainPage()
{
    char temper[20];

    char dity[20];

    char time[30];

    char time2[30];

    while(1){
        if(EncoderEnter()){  //如果检测到了相关菜单案件被按下
            break;
        }
        if(DoubleButtonEnter()){    //蜂鸣器紧急关闭接口
            BeefStop();
        }
        OLED_Clear();

        DHT11_ReadData(&DHT11_Data);        //读取温湿度

        sprintf(temper,"%d",DHT11_Data.temp_int);
        sprintf(dity,"%d%%",DHT11_Data.humi_int);

        OLED_ShowImage(0,0,16,16,Temper);   //温度图标
        OLED_ShowString(16,0,temper,OLED_8X16);
        OLED_ShowChinese(32,0,(char *)"度");


        OLED_ShowImage(0,16,16,16,Dity);    //湿度图标
        OLED_ShowString(16,16,dity,OLED_8X16);


        DS = QF_DS3231_ReadTime_ReturnPoint();      //获取时间数据
        sprintf(time,"%d:%d:%d",DS.Hour,DS.Minutes,DS.Seconds); //组合时分秒
        sprintf(time2,"%d-%d-%d-%d",DS.Year,DS.Month,DS.Date,DS.Week);     //组合年月日周

        OLED_ShowImage(0,32,16,16,Time);    //时间图标
        OLED_ShowString(16,32,time,OLED_8X16);
        OLED_ShowString(0,48,time2,OLED_8X16);

        OLED_Update();
    }
}

/**
 * @author : Misaki
 * @brief : 菜单
 */
void TLB_OLED::MENU()
{
    static MENU_OptionTypeDef OptionList[] = {
            {(char *)"<<<", NULL},
            {(char *)"Set Time",SetTime},      //时间设置
            {(char *)"Dis",Dis},           //实时距离
            {(char *)"Timer",Timer},         //定时功能
            {(char *)"About",About},         //关于
            {(char *)"..", NULL}
    };
    static MENU_HandleTypeDef hMENU = {.OptionList = OptionList};

    MENU_RunMenu(&hMENU);       //  <--左边的这个函数底层内就有一个while(1)
}


