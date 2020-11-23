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

// sbit BUZZ=P0^6;

// u8 code LedChar[] = {
//     0x03, 0x9f, 0x25, 0x0d, 0x99,
//     0x49, 0x41, 0x1f, 0x01, 0x09,
// };

void main()
{
    InitCar();
    while(1)
    {
        IRDetection();
        if(TURN_FORWARD)
        {
            SetCar(FORWARD,100,100);
            while(TURN_FORWARD) IRDetection();
        }
        if(TURN_LEFT)
        {
            SetCar(LEFT,100,100);
            while(TURN_LEFT) IRDetection();
            if(INSIDE_LINE)
            {
                SetCar(FORWARD,50,70);
                while(INSIDE_LINE) IRDetection();
            }
        }
        if(TURN_RIGHT)
        {
            SetCar(RIGHT,100,100);
            while(TURN_RIGHT) IRDetection();
            if(INSIDE_LINE)
            {
                SetCar(FORWARD,70,50);
                while(INSIDE_LINE) IRDetection();
            }
        }
    }
}