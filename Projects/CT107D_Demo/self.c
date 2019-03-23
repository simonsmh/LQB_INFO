#include <self.h>
#include <onewire.h>
#include <iic.h>
#include <ds1302.h>



void cls_buzz()
{
	P2 = (P2 & 0x1F | 0xA0);
	P0 = 0x00;
	P2 &= 0x1F;
}

float Get_Temp()
{
	unsigned char high, low;
	unsigned int temp;
	float temperature;
	Init_DS18B20();
	Write_DS18B20(OW_SKIP_ROM);
	Write_DS18B20(DS18B20_CONVERT);
	Delay_OneWire(200);

	Init_DS18B20();
	Write_DS18B20(OW_SKIP_ROM);
	Write_DS18B20(DS18B20_READ);
	low = Read_DS18B20();
	high = Read_DS18B20();
	//[0b____ + 0b____ + 0b____] /. 0b____ //center(no digits)
	//temp = high<<4;
	//temp |= low>>4;
	//[0b____ + 0b____ + 0b____ /. 0b____] //full
	temp = (high<<8)|low;
	temperature = temp;
	temperature/=16;
	return temperature;
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

void Delay50us() //@11.0592MHz
{
	unsigned char i, j;

	_nop_();
	i = 1;
	j = 134;
	do
	{
		while (--j)
			;
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

code unsigned char tab[] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90, 0xff, 0xbf, 0x63};
unsigned char dscom = 0;

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

unsigned int key_press = 0;

int read_keyboard()
{
	char i, j;
	unsigned char column, row;
	unsigned long sum = 0;
	//column row 0bxxxx
	P3 = 0x0f;
	P42 = 0;
	P44 = 0;
	if (!P30 || !P31 || !P32 || !P33)
		key_press++;
	else
		key_press = 0;

	if (key_press == 3)
	{
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
					sum = (i + 1) + 4 * (j);
					break;
				}
			}
		}
	}
	return sum;
}

int read_btn()
{
	char i=0;
	unsigned char column;
	P3 = 0xff;
	if (!P30 || !P31 || !P32 || !P33)
		key_press++;
	else
		key_press = 0;
	if (key_press == 3)
	{
		column = P3 & 0x0f;
		for (i = 3; i >= 0; i--)
		{
			if(!((column>>i)&1)){
				i += 1;
				break;
			}
		}
	}
	return i;
}

int read_btn_long()
{
	char i = 0;
	unsigned char column;
	P3 = 0xff;
	if (!P30 || !P31 || !P32 || !P33)
		key_press++;
	else
		key_press = 0;
	if (key_press >= 3)
	{
		column = P3 & 0x0f;
		for (i = 3; i >= 0; i--)
		{
			if (!((column >> i) & 1))
			{
				i += 1;
				break;
			}
		}
	}
	return i;
}
