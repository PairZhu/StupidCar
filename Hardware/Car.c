#include "Car.h"

#define HPWMT 0xFF //脉宽调制百分之一周期 当前周期：5ms
#define LPWMT 0xD2

sbit RMA = P0 ^ 0;
sbit RMB = P0 ^ 1;
sbit LMA = P0 ^ 2;
sbit LMB = P0 ^ 3; //左右两电机控制口
bit LmotorA = 0;
bit LmotorB = 0;
bit RmotorA = 0;
bit RmotorB = 0;

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
    switch (mode)
    {
    case FORWARD:
        LmotorA = 1;
        LmotorB = 0;
        RmotorA = 1;
        RmotorB = 0;
        break;
    case BACKWARD:
        LmotorA = 0;
        LmotorB = 1;
        RmotorA = 0;
        RmotorB = 1;
        break;
    case LEFT:
        LmotorA = 0;
        LmotorB = 1;
        RmotorA = 1;
        RmotorB = 0;
        break;
    case RIGHT:
        LmotorA = 1;
        LmotorB = 0;
        RmotorA = 0;
        RmotorB = 1;
        break;
    case STOP:
        LmotorA = 0;
        LmotorB = 0;
        RmotorA = 0;
        RmotorB = 0;
        break;
    }
    LeftPower = LPower;
    RightPower = RPower;
}

void T0PWM() interrupt 1
{
    static u8 i = 0;
    TH0 = HPWMT;
    TL0 = LPWMT;
    if (i < LeftPower)
    {
        LMA = LmotorA;
        LMB = LmotorB;
    }
    else
    {
        LMA = 0;
        LMB = 0;
    }

    if (i < RightPower)
    {
        RMA = RmotorA;
        RMB = RmotorB;
    }
    else
    {
        RMA = 0;
        RMB = 0;
    }
    if (i == 99)
        i = 0;
    else
        ++i;
}