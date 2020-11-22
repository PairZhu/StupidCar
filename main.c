#include<reg52.h>
#include "Car.h"

#ifndef __U_8_16__
#define __U_8_16__
typedef unsigned char u8;
typedef unsigned int u16;
#endif





sbit LIR=P3^5;
sbit RIR=P3^6;
sbit FIR=P3^7;		//左 右 前 3个红外传感器

sbit BUZZ=P0^6;

u8 code LedChar[] = {
    0x03, 0x9f, 0x25, 0x0d, 0x99,
    0x49, 0x41, 0x1f, 0x01, 0x09,
};

void main() 
{
    InitCar();
    SetCar(FORWARD,0,0);
    P2=LedChar[0];
    while(1);
}