#include "STC15F2K60S2.h"
#include "absacc.h"
#include "iic.h"
#include "ds1302.h"
#include "onewire.h"

code unsigned char tab[] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90, 0xff, 0xbf};
unsigned char dspbuf[8] = {0, 0, 0, 0, 0, 0, 0, 0};
unsigned char com=1, dscom=0, temp_flag=0;
unsigned long num=0, time=0;
float temperature=0;
unsigned char column, row;
unsigned int sum;
unsigned int key_press=0;

unsigned int time_data[]={ 40, 48, 8, 2, 3, 5, 19};

float Get_Temp(void)
{
	unsigned char High, Low;
	float temp;
	Init_DS18B20();
	Write_DS18B20(OW_SKIP_ROM);
	Write_DS18B20(DS18B20_CONVERT);
	Delay_OneWire(200);

	Init_DS18B20();
	Write_DS18B20(OW_SKIP_ROM);
	Write_DS18B20(DS18B20_READ);
	High = Read_DS18B20();
	Low = Read_DS18B20();
	//[0b____ + 0b____ + 0b____] /. 0b____ //center(no digits)
	//temp = (High<<4)|(Low>>4);
	//[0b____ + 0b____ + 0b____ /. 0b____] //full
	temp = (High<<4)|(Low>>4);
	//temp/=16;
	return temp;
}

void init_rtc()
{
	unsigned char i;
	unsigned char temp = 0x80;
	Ds1302_Single_Byte_Write(0x8e,0x00);//close write protect
	for( i = 0;i < 7;i++)
	{
		time_data[i] = time_data[i]+(time_data[i]/10)*6; //DEC2BCD
		Ds1302_Single_Byte_Write(temp,time_data[i]);
		temp += 2;
	}
	Ds1302_Single_Byte_Write(0x8e,0x81);//open write protect
}


void get_rtc()
{
	unsigned char i;
	unsigned char temp = 0x81;
	for( i = 0;i < 7;i++)
	{
		time_data[i] = Ds1302_Single_Byte_Read(temp);
		time_data[i] = time_data[i] % 16 + (time_data[i] >> 4) * 10; //BCD2DEC
		temp += 2;
	}
}


void cls_buzz(void)
{
	P2 = (P2 & 0x1F | 0xA0);
	P0 = 0x00;
	P2 &= 0x1F;
}

void Timer0Init(void)		//20??@12.000MHz
{
	AUXR |= 0x80;		//?????1T??
	TMOD &= 0xF0;		//???????
	TMOD |= 0x02;		//???????
	TL0 = 0x10;		//??????
	TH0 = 0x10;		//???????
	TF0 = 0;		//??TF0??
	TR0 = 1;		//???0????
}

void Timer1Init(void)		//20??@12.000MHz
{
	AUXR |= 0x40;		//?????1T??
	TMOD &= 0x0F;		//???????
	TMOD |= 0x20;		//???????
	TL1 = 0x10;		//??????
	TH1 = 0x10;		//???????
	TF1 = 0;		//??TF1??
	TR1 = 1;		//???1????
}


void main(void)
{
	cls_buzz();
	init_rtc();
	Timer0Init();
	Timer1Init();
	EA = 1;
	ET0 = 1;
	//ET1 = 1;

	while (1)
	{
		if(temp_flag){
			temperature = Get_Temp();
			temp_flag=0;
		}
	};
}

void Delay50us() //@11.0592MHz
{
	unsigned char i, j;

	_nop_();
	i = 1;
	j = 134;
	do
	{
		while (--j);
	} while (--i);
}

void EEPROM_Write(unsigned char addr, unsigned char dat)
{
	IIC_Start();
	IIC_SendByte(0xA0);
	IIC_WaitAck();
	IIC_SendByte(addr);
	IIC_WaitAck();
	IIC_SendByte(dat);
	IIC_WaitAck();
	IIC_Stop();

	Delay50us();
}

unsigned char EEPROM_Read(unsigned char addr)
{
	unsigned char buf;

	IIC_Start();
	IIC_SendByte(0xA0);
	IIC_WaitAck();
	IIC_SendByte(addr);
	IIC_WaitAck();
	IIC_Start();
	IIC_SendByte(0xA1);
	IIC_WaitAck();
	buf = IIC_RecByte();
	IIC_Ack(0);
	IIC_Stop();

	return buf;
}

void display()
{ //int time

	//P0=0xff;
	//Display
	P2 = (P2 & 0x1f) | 0xc0;
	P0 = 1 << dscom;
	P2 &= 0x1f;
	P2 = (P2 & 0x1f) | 0xe0;
	P0 = tab[dspbuf[dscom]];
	P2 &= 0x1f;
	if (++dscom == 8)
	{
		dscom = 0;
	}
}

int read_keyboard()
{
	char i, j;
	sum = 0;
	//column row 0bxxxx
	P3 = 0x0f;
	P42 = 0;
	P44 = 0;
	if(!P30||!P31||!P32||!P33)
	  key_press++;
	else
		key_press = 0;

if(key_press == 3){
	column = P3 & 0x0f;
	P3 = 0xf0;
	P42 = 1;
	P44 = 1;
	row = ((((((P44 * 2) | P42) * 2) | P35) * 2) | P34); //Affected with P4
	//scan
	for (i = 3; i >= 0; i--)
	{
		for (j = 3; j >= 0; j--)
		{
			if ((!((column >> i) & 1)) && (!((row >> j) & 1)))
			{
				sum=(i+1)+4*(j);
				break;
			}
		}
	}
}
	return sum;
}

unsigned int o=0,p=0,q=0,r=0;
void isr_timer_0(void) interrupt 1 //默认中断优先级 1
{
	char i;
	if(++o>=24){
	get_rtc();
	if (++q <= 1600)
	{
		//time_data Parser
		//time = ++num;
		time = EEPROM_Read(0x00);
		time += read_keyboard();
		EEPROM_Write(0x00,time);
		for (i = 7; i >= 5; i--)
		{
			dspbuf[i] = time % 10;
			time /= 10;
		}
		for (i = 5; i <= 7; i++)
		{
			if (dspbuf[i] == 0)
				dspbuf[i] = 10;
			else
				break;
		}
		time = temperature*100;
		for (i = 4; i >= 0; i--)
		{
			dspbuf[i] = time % 10;
			time /= 10;
		}
		for (i = 0; i <= 4; i++)
		{
			if (dspbuf[i] == 0)
				dspbuf[i] = 10;
			else
				break;
		}

///DS1302
	}else if(q <= 3200){
		dspbuf[0]=time_data[2]/10;
		dspbuf[1]=time_data[2]%10;
		dspbuf[2]=11;
		dspbuf[3]=time_data[1]/10;
		dspbuf[4]=time_data[1]%10;
		dspbuf[5]=11;
		dspbuf[6]=time_data[0]/10;
		dspbuf[7]=time_data[0]%10;

	}else if(q <= 4800){
		dspbuf[0]=time_data[5]/10;
		dspbuf[1]=time_data[5]%10;
		dspbuf[2]=11;
		dspbuf[3]=time_data[4]/10;
		dspbuf[4]=time_data[4]%10;
		dspbuf[5]=11;
		dspbuf[6]=time_data[3]/10;
		dspbuf[7]=time_data[3]%10;
		if(q>=4800)q=0;
	}else{

	}

	display(); //2ms执行一次 //time
	o=0;
	if(++r>=5600){
		temp_flag=1;
		r=0;
	}
	}

}

//void isr_timer_1(void) interrupt 3 //默认中断优先级 1
//{
//	if(++p>=1400){
//
//	p=0;
//	}
//}
