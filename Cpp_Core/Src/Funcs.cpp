//
// Created by Administrator on 2024/8/11.
//

/**
 * @author : Misaki
 * 这里实现了菜单内的各种功能
 * 注意 : 因为使用的分光棱镜大小 小于1.3寸OLED,所以图像宽度取值在0~96
 */

#include "Funcs.h"
#include "OLED.h"
#include "DoubleButtonControl.h"
#include "cstdio"
#include "tim.h"
#include "BuzzerControl.h"
#include "SuperVoiceWave.h"
#include "DS3231.h"

typedef long long ll;   //如果你也曾经是一名ACMer的话

//默认时间
uint8_t seconds = 0;
uint8_t minutes = 0;
uint8_t hour = 12;
uint8_t date = 11;
uint8_t month = 8;
uint8_t year = 24;
uint8_t week = 7;

//辅助函数,检查时间是否越界
void Check()
{
    if(year > 99){
        year = 0;
    }
    if(year < 0){
        year = 99;
    }

    if(month > 12){
        month = 1;
    }
    if(month < 1){
        month = 12;
    }

    if(week > 7){
        week = 1;
    }
    if(week < 1){
        week = 7;
    }

    if(date > 31){
        date = 1;
    }
    if(date < 1){
        date = 31;
    }

    if(hour > 23){
        hour = 0;
    }
    if(hour < 0){
        hour = 23;
    }

    if(minutes > 59){
        minutes = 0;
    }
    if(minutes < 0){
        minutes = 59;
    }

    if(seconds > 59){
        seconds = 0;
    }
    if(seconds < 0){
        seconds = 59;
    }
}

//设置时间
void SetTime()
{
    //光标控制
    int cursor = 0; //默认指向第一个

    //状态控制
    int state = 0;   //设置两种状态，一种状态为光标控制选择状态(0),一种状态为输入数字状态(1)

    //通用字符串
    char str[20];

    //手动设置时间,调用底层接口应用时间
    while(1){
        if (DoubleButtonEnter()) {  //如果检测到了相关菜单案件被按下,并设置下时间
            QF_DS3231_SetTime(year,month,date,hour,minutes,seconds,week);
            break;
        }
        OLED_Clear();
        Check();    //检查时间是否越界
        if(state == 0){
            if(EncoderEnter()){ //选择后按下旋转编码器切换状态
                state = 1;
            }
            if(cursor < 0){
                cursor = 0;
            }
            if(cursor > 6){ //下标为0~6
                cursor = 6;
            }

            cursor += EncoderUpDown();
            //渲染左箭头光标
            OLED_ShowImage(48,cursor * 8,8,8,LeftArrow);

        }
        if(state == 1){ //根据当前的cursor的值来确定修改的为哪一个值
            if(EncoderEnter()){ //选择后按下旋转编码器切换状态
                state = 0;
            }
            OLED_ShowImage(48,cursor * 8,8,8,LeftArrow);    //定死左箭头光标
            //根据cursor的值,喵喵偷了个懒,写了段日语的代码,可以使用数组或者结构体进行指针增减优化的哦~
            if(cursor == 0){    //对应年
                year += EncoderUpDown();
            }
            if(cursor == 1){    //对应月
                month += EncoderUpDown();
            }
            if(cursor == 2){    //对应日
                date += EncoderUpDown();
            }
            if(cursor == 3){    //对应时
                hour += EncoderUpDown();
            }
            if(cursor == 4){    //对应分
                minutes += EncoderUpDown();
            }
            if(cursor == 5){    //对应秒
                seconds += EncoderUpDown();
            }
            if(cursor == 6){
                week += EncoderUpDown();
            }
        }

        //正常显示待设置菜单
        sprintf(str,"Year:%d",year);
        OLED_ShowString(0,0,(char *)str,OLED_6X8);

        sprintf(str,"Month:%d",month);
        OLED_ShowString(0,8,(char *)str,OLED_6X8);

        sprintf(str,"Date:%d",date);
        OLED_ShowString(0,16,(char *)str,OLED_6X8);

        sprintf(str,"Hour:%d",hour);
        OLED_ShowString(0,24,(char *)str,OLED_6X8);

        sprintf(str,"Min:%d",minutes);
        OLED_ShowString(0,32,(char *)str,OLED_6X8);

        sprintf(str,"Sec:%d",seconds);
        OLED_ShowString(0,40,(char *)str,OLED_6X8);

        sprintf(str,"Week:%d",week);
        OLED_ShowString(0,48,(char *)str,OLED_6X8);

        OLED_Update();
    }
}

//测距
//直接调用底层的超声波测距接口
void Dis()
{
    char str[20];
    while(1){
        if (DoubleButtonEnter()) {  //如果检测到了相关菜单案件被按下
            break;
        }


        OLED_Clear();
        OLED_ShowChinese(16,0,(char *)"距离");
        sprintf(str,"%.2fcm",getDistance());
        OLED_ShowString(0,16,str,OLED_8X16);

        OLED_ShowChinese(0,32,(char *)"待测距物体放");
        OLED_ShowChinese(0,48,(char *)"在两个圆头前");

        OLED_Update();
    }
}




//定时
static int times = 0;  //以分钟为单位
static ll secs =0;

//一个接口函数,对外提供剩余的计时时间,单位为s
int getTimes(){
    return times * 60 - secs;
}

void Timer()
{
    //思考思考,一个定时功能应该怎么去做呢,首先是要能实时显示时间,以及定时时效,默认就按分钟来做把,然后使用旋转编码器控制
    //使用定时器中断来实现1s时基的计时

    times = 0;
    char str[20];
    while(1) {
        if (DoubleButtonEnter()) {  //如果检测到了相关菜单案件被按下
            break;
        }
        if(EncoderEnter()){ //检测编码器按钮是否被按下,按下则保存当前定时时长,开始定时
            if(times != 0){
                HAL_TIM_Base_Start_IT(&htim2);      //开启TIM2基本定时器中断
            }
            break;

        }
        if(times < 0){
            times = 0;
        }
        times += EncoderUpDown();   //看一看EncoderUpDown()的底层实现就知道这里为什么要这么做了喵~

        OLED_Clear();

        OLED_ShowChinese(0,0,(char *)"设定计时时长");
        sprintf(str,"%d",times);

        OLED_ShowString(0,16,str,OLED_8X16);
        OLED_ShowChinese(32,16,(char *)"分钟");

        OLED_ShowChinese(0,32,(char *)"旋转旋钮设定");
        OLED_ShowChinese(0,48,(char *)"按下旋钮开始");

        OLED_Update();
    }
}


//关于
void About()
{
    while(1){
        if(DoubleButtonEnter()){  //如果检测到了相关菜单案件被按下
            break;
        }
        OLED_Clear();
        OLED_ShowImage(0,0,16,16,Heart);
        OLED_ShowChinese(16,0,(char *)"无论今后");
        OLED_ShowImage(0,16,16,16,Heart);
        OLED_ShowChinese(16,16,(char *)"发生什么");
        OLED_ShowChinese(16,32,(char *)"请都不要");
        OLED_ShowChinese(0,48,(char *)"后悔与我相遇");
        OLED_Update();
    }
}


//重写定时器中断函数
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(htim == &htim2){ //执行定时器2产生的1s时基中断
        //每触发一次中断就增加一秒时间
        secs++;
        if((times * 60) - secs == 0){   //如果达到了设定的时间
            HAL_TIM_Base_Stop_IT(&htim2);   //关闭中断
            secs = 0;   //置零
            //控制蜂鸣器发出警报
            BeefStart();    //这个时候你最好是在主界面,不过其他界面也没事,按下双轴摇杆才可以停止警报喵~
                            //要是关不掉了,喵喵可就完蛋了惹~
        }
    }
}

