#ifndef __BLUETOOTH_H__
#define __BLUETOOTH_H__

#ifndef __U_8_16__
#define __U_8_16__
typedef unsigned char u8;
typedef unsigned int u16;
#endif

#include <reg52.h>

void InitBluetooth(void (*func)(u8*));

#endif // __BLUETOOTH_H__