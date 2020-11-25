#include "Bluetooth.h"

void (*deal_data)(u8*);

void InitBluetooth(void (*func)(u8*))
{
    deal_data=func;
    TMOD |= 0x20;
	TH1 = 0xFD; //11.0592M晶振，9600波特率
	TL1 = 0xFD;
	SCON = 0x50;
	PCON = 0x00;
	TR1 = 1;
	ES = 1;
	EA = 1;
}

void serial_port() interrupt 4 //串口中断
{
    static u8 str[20], pos=0;
    static bit read_flag=0;
    u8 dat;
	if (RI) //是否接收中断
	{
		RI = 0;
		dat = SBUF;
        if(read_flag==0)
        {
            if(dat=='B')
                read_flag=1;
            else
                return;
        }
        else
        {
            str[pos++]=dat;
            if(dat=='\0')
            {
                deal_data(str);
                pos=0;
                read_flag=0;
            }
        }
        

	}
}