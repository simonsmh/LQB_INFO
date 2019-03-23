#include <stc15f2k60s2.h>
#include <iic.h>
#include <intrins.h>

code unsigned char tab[] = {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0xff};
unsigned char dspbuf[] = {0,0,0,0,0,0,0,0,0};
unsigned char dspcom = 0;
unsigned char dist_data[] = {0, 0, 0, 0, 0};
void cls_buzz(){
	P2=(P2&=0x1f)|0xa0;
	P0&=0xaf;
	P2&=0x1f;
}

void display(){
	P2=(P2&=0x1f)|0xc0;
	P0=0x00;
	P2&=0x1f;
	P2=(P2&=0x1f)|0xe0;
	P0=tab[dspbuf[dspcom]];
	P2&=0x1f;
	P2=(P2&=0x1f)|0xc0;
	P0=(1<<dspcom);
	P2&=0x1f;
	if(++dspcom==8)
		dspcom=0;
}

void Timer0Init(void)		//2毫秒@11.0592MHz
{
	AUXR &= 0x7F;		//定时器时钟12T模式
	TMOD &= 0xF0;		//设置定时器模式
	TL0 = 0xCD;		//设置定时初值
	TH0 = 0xF8;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时
}

void SomeDelay(unsigned char i)
{
	do
	{
		_nop_();
	} while (i--);
}

void IIC_Write(unsigned char Slave, unsigned char Address, unsigned char Data)
{
	EA = 0;
	IIC_Start();
	IIC_SendByte(Slave);
	IIC_WaitAck();
	IIC_SendByte(Address);
	IIC_WaitAck();
	IIC_SendByte(Data);
	IIC_WaitAck();
	IIC_Stop();
	SomeDelay(10);
	EA = 1;
}

unsigned char IIC_Read(unsigned char Slave, unsigned char Address)
{
	unsigned char Data;
	EA = 0;
	IIC_Start();
	IIC_SendByte(Slave);
	IIC_WaitAck();
	IIC_SendByte(Address);
	IIC_WaitAck();
	IIC_Start();
	IIC_SendByte(Slave+1);
	IIC_WaitAck();
	Data = IIC_RecByte();
	IIC_SendAck(0);
	IIC_Stop();
	EA = 1;
	return Data;
}

void EEPROM_Write_Page(unsigned char Address){
	unsigned char i;
	EA = 0;
	IIC_Start();
	IIC_SendByte(0xa0);
	IIC_WaitAck();
	IIC_SendByte(Address);
	IIC_WaitAck();
	for (i = 0; i <= 4; i++)
	{
		IIC_SendByte(dist_data[i]);
		IIC_WaitAck();
	}
	IIC_Stop();
	SomeDelay(10);
	EA = 1;
}

void EEPROM_Read_Page(unsigned char Address){
	unsigned char i;
	EA = 0;
	IIC_Start();
	IIC_SendByte(0xa0);
	IIC_WaitAck();
	IIC_SendByte(Address);
	IIC_WaitAck();
	IIC_Start();
	IIC_SendByte(0xa1);
	IIC_WaitAck();
	for(i = 0; i <= 4; i++)
	{
		dist_data[i] = IIC_RecByte();
		IIC_SendAck(0);
	}
	IIC_Stop();
	EA = 1;
}

void buf(int a, char b, char c){
	char i;
	for(i=c;i>=b;i--){
		dspbuf[i]= a%10;
		a/=10;
	}
}

void buf_mute(char b, char c){
	char i;
	for(i=c;i>=b;i--){
		dspbuf[i]= 10;
	}
}

unsigned int key_press;
char key(){
	P3 = 0x0f;
	if(!P30||!P31||!P32||!P33)
		key_press++;
	else
		key_press=0;

	if(key_press==3){
		if(!P30)return 1;
		else if(!P31)return 2;
		else if(!P32)return 3;
		else if(!P33)return 4;
		else return 0;
	}else return 0;
}

unsigned int dist(){
	unsigned int distance, t = 0;
	unsigned char i = 8;  //发送8个脉冲
	TH1 = 0;
	TL1 = 0;
	do
	{
		P10 = 1;
		_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_(); _nop_();
		P10 = 0;
		_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_(); _nop_();
	}
	while(i--);
    TR1 = 1;  //启动计时
	while((P11 == 1) && (TF1 == 0));  //等待收到脉冲
	TR1 = 0;  //关闭计时

	//发生溢出
	if(TF1 == 1)
	{
		TF1 = 0;
		distance = 999;  //无返回
	}
	else
	{
		/**  计算时间  */
		t = TH1;
		t <<= 8;
		t |= TL1;
		distance = (unsigned int)(t*0.017);  //计算距离
	}
	return distance;
}


unsigned int tmp=0;
unsigned int q=1000;
unsigned char status_2=0, status_3=0, status_4=0;

//unsigned char dist_block[] = {0x03, 0x04, 0x05, 0x06};
// unsigned char conf = 1;
// unsigned char conf_data[]={0,10,20,30};
void main(){
	unsigned char i;
	cls_buzz();
	Timer0Init();
	ET0=1;
	EA=1;
	// for (i = 0; i <= 3;i++){
	// 	P2=(P2&=0x1f)|0x80;
	// 	P0=(0xff-1<<i);
	// 	P2&=0x1f;
	// 	dist_data[i] = IIC_Read(0xa0, dist_block[i]);
	// }
	EEPROM_Read_Page(0x00);
	while (1)
	{
		if(--q==0){
			q=1000;
			tmp = dist();
//			if(tmp >= dist_data[0])
				IIC_Write(0x90, 0x40, (tmp - dist_data[0]) * 0.02);
//			else
//				IIC_Write(0x90, 0x40, 0);
		}
		if((status_2==0) && (status_3==0)){
			buf(0, 0, 0);
			buf_mute(1,1);
			buf(tmp, 2, 4);
			buf(dist_data[1], 5, 7);
		}else if(status_2==1){
			status_3=0;
			buf(status_4+1, 0, 0);
			buf_mute(1,4);
			buf(dist_data[status_4+1], 5, 7);
			//buf(IIC_Read(0xa0, dist_block[status_4]), 5, 7);
		}else if(status_3==1){
			status_2=0;
			buf(5, 0, 0);

			buf_mute(1,4);
			//conf = status_4;
			// dist_data[0] = status_4 * 10;
			buf(dist_data[0], 5, 7);
		}
		switch(key()){
			case 1:
				if((status_2==0)&&(status_3==0)){
					for (i = 4; i >= 2; i--){
						dist_data[i] = dist_data[i-1];
						//EEPROM_Write(dist_block[i], dist_data[i]);
					}
					dist_data[1] = tmp;
					//EEPROM_Write(dist_block[0], dist_data[0]);
					EEPROM_Write_Page(0x00);
					// for(i=0;i<3;i++){
					// 	P2=(P2&=0x1f)|0x80;
					// 	P0=0xfe;
					// 	P2&=0x1f;
					// 	Delay200us();
					// 	P2=(P2&=0x1f)|0x80;
					// 	P0=0xff;
					// 	P2&=0x1f;
					// 	Delay200us();
					// }
				}
				//buf(1, 1, 1);
				break;
			case 2:
				if(++status_2==2){
					status_2=0;
					status_4=0;

					// P2=(P2&=0x1f)|0x80;
					// P0=0xff;
					// P2&=0x1f;
				}else{
					// P2=(P2&=0x1f)|0x80;
					// P0=0x7f;
					// P2&=0x1f;
				};
				//buf(1, 1, 1);
				break;
			case 3:
				if(++status_3==2){
					status_3=0;
					status_4 = dist_data[0]/10;

					// P2=(P2&=0x1f)|0x80;
					// P0=0xff;
					// P2&=0x1f;
				}else{
					// P2=(P2&=0x1f)|0x80;
					// P0=0xbf;
					// P2&=0x1f;
				};
				//buf(3, 0, 0);
				break;
			case 4:
				if(++status_4==4)
					status_4=0;
				if (status_3==1)
				{
					dist_data[0] = status_4 * 10;
					IIC_Write(0xa0, 0x00, dist_data[0]);
				}

				//buf(4, 1, 1);
				break;
			default:
				break;
				}
	}
}

void tr0_interrupt() interrupt 1{
	display();
}
