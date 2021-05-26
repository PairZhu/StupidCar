#include "Infrared.h"

#define HIRT 0xFF //红外循迹检测十分之一周期 当前周期:0.1ms
#define LIRT 0xF7

sbit LIR = P3 ^ 7;
sbit RIR = P3 ^ 6;
sbit FIR = P3 ^ 7; //左 右 前 3个红外传感器

bit LeftIR = 1;
bit RightIR = 1;

void InitIR()
{
    TMOD |= 0x10; //设置定时器1为模式1
    EA = 1;       //使能中断
    ET1 = 1;
    TH1 = HIRT; //设置定时初值
    TL1 = LIRT;
    TR1 = 1; //打开定时器1
}

void T1IRDetection() interrupt 3
{
    static u8 cntL = 0, cntR = 0, cntF = 0;
    static bit lastL = 1, lastR = 1, lastF = 1;
    bit value;
    TH1 = HIRT; //重载定时初值
    TL1 = LIRT;
    
    value = LIR;
    if (value == lastL)
    {
        if (cntL == 9)
        {
            LeftIR = lastL;
            cntL = 0;
        }
        else
        {
            ++cntL;
        }
    }
    else
    {
        cntL = 1;
        lastL = value;
    }

    value = RIR;
    if (value == lastR)
    {
        if (cntR == 9)
        {
            RightIR = lastR;
            cntR = 0;
        }
        else
        {
            ++cntR;
        }
    }
    else
    {
        cntR = 1;
        lastR = value;
    }
}