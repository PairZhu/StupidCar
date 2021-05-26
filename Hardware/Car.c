#include "Car.h"

#define HPWMT 0xFF //脉宽调制百分之一周期 当前周期：5ms
#define LPWMT 0xD2

sbit LMA = P1^2;
sbit LMB = P1^3;
sbit RMA = P1^4;
sbit RMB = P1^5; //左右两电机控制口
sbit LEN = P1^6;
sbit REN = P1^7;

bit REnable = 0;
bit LEnable = 0;

CarMode RunMode = STOP;
u8 LeftPower = 100;
u8 RightPower = 100;

void InitCar()
{
    SetCar(STOP, 0, 0);
    TMOD |= 0x01; //设置定时器0为模式1
    EA = 1; //使能中断
    ET0 = 1;
    TH0 = HPWMT; //设置定时初值
    TL0 = LPWMT;
    TR0 = 1; //打开定时器0
}

void SetCar(CarMode mode, u8 LPower, u8 RPower)
{
    RunMode = mode;
    LEnable = 0;
    REnable = 0;
    switch (mode)
    {
    case FORWARD:
        LMA = 1;
        RMA = 1;
        LMB = 0;
        RMB = 0;
        break;
    case BACKWARD:
        LMA = 0;
        RMA = 0;
        LMB = 1;
        RMB = 1;
        break;
    case LEFT:
        LMA = 0;
        RMA = 1;
        LMB = 1;
        RMB = 0;
        break;
    case RIGHT:
        LMA = 1;
        RMA = 0;
        LMB = 0;
        RMB = 1;
        break;
    case STOP:
        LMA = 0;
        RMA = 0;
        LMB = 0;
        RMB = 0;
        break;
    }
    LeftPower = LPower;
    RightPower = RPower;
    LEnable = 1;
    REnable = 1;
}

void T0PWM() interrupt 1
{
    static u8 i = 0;
    TH0 = HPWMT;
    TL0 = LPWMT;
    if (i < LeftPower)
    {
        LEN = LEnable;
    }
    else
    {
        LEN = 0;
    }

    if (i < RightPower)
    {
        REN = REnable;
    }
    else
    {
        REN = 0;
    }
    if (i == 99)
        i = 0;
    else
        ++i;
}