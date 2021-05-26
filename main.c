#include<reg52.h>
#include "Car.h"
#include "Infrared.h"

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

void main()
{
    InitIR();
    InitCar();
    while(1)
    {
        if(TURN_FORWARD)
        {
            SetCar(FORWARD,100,100);
            while(TURN_FORWARD);
        }
        if(TURN_LEFT)
        {
            SetCar(LEFT,100,100);
            while(TURN_LEFT);
            if(INSIDE_LINE)
            {
                SetCar(FORWARD,50,70);
                while(INSIDE_LINE);
            }
        }
        if(TURN_RIGHT)
        {
            SetCar(RIGHT,100,100);
            while(TURN_RIGHT);
            if(INSIDE_LINE)
            {
                SetCar(FORWARD,70,50);
                while(INSIDE_LINE);
            }
        }
    }
}