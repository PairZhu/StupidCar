#ifndef __INFRARED_H__
#define __INFRARED_H__

#ifndef __U_8_16__
#define __U_8_16__
typedef unsigned char u8;
typedef unsigned int u16;
#endif

#include <reg52.h>

extern bit LeftIR;
extern bit RightIR;
extern bit FrontIR;

void IRDetection();

#endif // !__INFRARED_H__


