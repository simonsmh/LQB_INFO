//LED_ON_OFF
//LED-on -> delay 500ms -> LED-off -> delay 500ms

#include <STC15F2K60S2.h>
#include <intrins.h>

void Delay500ms() //@11.0592MHz
{
	unsigned char i, j, k;

	_nop_();
	_nop_();
	i = 22;
	j = 3;
	k = 227;
	do
	{
		do
		{
			while (--k)
				;
		} while (--j);
	} while (--i);
}

void main(){
	while(1){
		P2 = (P2 & 0x1f) | 0x80;
		// Equals `P2 = (P2 & 0b00011111) | 0b10000000;`, but Keil C51 compiler doesn't have binary format support.
		//                    ^^^^^^^^^^    ^^^^^^^^^^
		// Select U24-74HC138 with only P25 P26 P27, AND Select Y4 for `0b100 == 4`
		P0 = 0xff; // Set 1 to turn OFF ALL LED `0xff == 0b11111111`
		P2 &= 0x1f;
		//    ^^^^
		// As `0b00011111 == 0x1f`, The Hex format is shorter for read.

		Delay500ms();
		P2 = (P2 & 0x1f) | 0x80;
		P0 = 0x00;
		P2 &= 0x1f;
		Delay500ms();
	}
}
