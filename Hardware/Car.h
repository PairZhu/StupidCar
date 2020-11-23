#ifndef __CAR_h__
#define __CAR_h__

#ifndef __U_8_16__
#define __U_8_16__
typedef unsigned char u8;
typedef unsigned int u16;
#endif

#include <reg52.h>

typedef enum {FORWARD, BACKWARD, LEFT, RIGHT, STOP}  CarMode;

extern u8 LeftPower;
extern u8 RightPower;
extern CarMode RunMode;

void InitCar();
void SetCar(CarMode mode, u8 LPower, u8 RPower);

#endif // !__Motor_h__