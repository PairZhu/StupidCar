#include<reg52.h>
#include <string.h>
#include "Car.h"
#include "Infrared.h"
#include "Bluetooth.h"

#ifndef __U_8_16__
#define __U_8_16__
typedef unsigned char u8;
typedef unsigned int u16;
#endif
//1表示检测到黑线
#define TURN_LEFT (LeftIR == 1 && RightIR == 0)
#define TURN_RIGHT (LeftIR == 0 && RightIR == 1)
#define TURN_FORWARD (LeftIR == 0 && RightIR == 0)
#define INSIDE_LINE (LeftIR == 1 && RightIR == 1)

// sbit BUZZ=P0^6;
sbit led = P1^0;

u8 code LedChar[] = {
    0x03, 0x9f, 0x25, 0x0d, 0x99,
    0x49, 0x41, 0x1f, 0x01, 0x09,
    0x45
};
u8 ForwardPower=100;

void ReadCMD(u8* cmd);
void Tracking();

void main()
{
    led=0;
    InitCar();
    InitBluetooth(ReadCMD);
    P2=LedChar[ForwardPower/10];
    while(1)
    {
        Tracking();
    }
}

void ReadCMD(u8* cmd)
{
    led=!led;
    if(strcmp(cmd,"plus")==0)
    {
        if(ForwardPower<=90)
            ForwardPower+=10;
    }
    else if(strcmp(cmd,"minus")==0)
    {
        if(ForwardPower>=10)
            ForwardPower-=10;
    }
    P2=LedChar[ForwardPower/10];
}

void Tracking()
{
    IRDetection();
    if(TURN_FORWARD)
    {
        SetCar(FORWARD,ForwardPower,ForwardPower);
        while(TURN_FORWARD) IRDetection();
    }
    if(TURN_LEFT)
    {
        SetCar(LEFT,0,60);
        while(TURN_LEFT) IRDetection();
        if(INSIDE_LINE)
        {
            SetCar(FORWARD,50,50);
            while(INSIDE_LINE) IRDetection();
        }
    }
    if(TURN_RIGHT)
    {
        SetCar(RIGHT,60,0);
        while(TURN_RIGHT) IRDetection();
        if(INSIDE_LINE)
        {
            SetCar(FORWARD,50,50);
            while(INSIDE_LINE) IRDetection();
        }
    }
}