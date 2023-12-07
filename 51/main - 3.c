#include<reg52.h>
#define uchar unsigned char
#define uint unsigned int
#define ulong unsigned long

uchar i = 0;
ulong k = 0;
uchar  code dula [10]= {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F,};

sbit we = P2^7;
sbit du = P2^6;
void delay(uint z)
{
	uint x,y;
	for(x = z; x > 0; x--)
		for(y = 114; y > 0 ; y--); 		
} 

void TimerInitialization()
{
	TR0 = 1;
	TMOD = 0x01;
	TL0 = 0xfd;
	TH0 = 0x4b;
}

void dispiay(ulong i)
{
uchar qianwan,baiwan,shiwan,wan,qian,bai,shi,ge;
qianwan = i/10000000;
baiwan  = i%10000000/1000000;
shiwan = i%1000000/100000;
wan = i%100000/10000;
qian = i%10000/1000;
bai = i%1000/100;
shi = i%100/10;
ge = i%10;
		du = 0;
		we = 0;
		delay(5);
		
		P0 = 0XFE;
		we = 1;
		we = 0;
		P0 = dula[qianwan];
		du = 1;
		du = 0;
		delay(5);
		
		P0  = 0xfd;
		we = 1;
		we = 0;
		P0 = dula[baiwan];
		du = 1;
		du = 0;
		delay(5);
		
		P0  = 0xfb;
		we = 1;
		we = 0;
		P0 = dula[shiwan];
		du = 1;
		du = 0;
		delay(5);
		
		P0  = 0xf7;
		we = 1;
		we = 0;
		P0 = dula[wan];
		du = 1;
		du = 0;
		delay(5);

		P0  = 0xef;
		we = 1;
		we = 0;
		P0 = dula[qian];
		du = 1;
		du = 0;
		delay(5);
		
		
		P0  = 0xdf;
		we = 1;
		we = 0;
		P0 = dula[bai];
		du = 1;
		du = 0;
		delay(5);
		
		
		P0  = 0xbf;
		we = 1;
		we = 0;
		P0 = dula[shi];
		du = 1;
		du = 0;
		delay(5);
		
		
		P0  = 0x7f;
		we = 1;
		we = 0;
		P0 = dula[ge];
		du = 1;
		du = 0;
		delay(5);
}

void main()
{
	TimerInitialization();
	while (k < 99999999)
	{
		while (i < 20)
		{
			if (1 == TF0)
			{
				TF0 = 0;
				TL0 = 0xfd;
				TH0 = 0x4b;
				i++;
			}
		}
		if (20 == i)
		{
			k++;
			i = 0;
			dispiay(k);
		}
		//delay(50);
		dispiay(k);
		//delay(50);
		dispiay(k);
		//delay(50);
		dispiay(k);
	}
}
