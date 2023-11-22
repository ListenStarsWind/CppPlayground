#include<reg52.h>
#define uint unsigned int
#define uchar unsigned char
sbit du = P2^6;
sbit we = P2^7;
uchar key = 19;

uchar code dula[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71,0x76,0x38,0x40,0x00};
	
void delay(uint z)
{
	uint x,y;
	for(x = z; x > 0; x--)
		for(y = 114; y > 0 ; y--); 		
} 

void KeyValue()
{
			P3 = 0XF0;
			if(P3!= 0XF0)
			{
				delay(20);
				if(P3!= 0XF0)
				{
						switch(P3)
						{
							case 0XE0:key = 0;break;
							case 0XD0:key = 1;break;
							case 0XB0:key = 2;break;
							case 0X70:key = 3;break;
						}
						P3 = 0X0F;
						switch(P3)
						{
							case 0X0E:key = key;break;
							case 0X0D:key = key+4;break;
							case 0X0B:key = key+8;break;
							case 0X07:key = key+12;break;
						}
				
						while(P3!=0x0F);
				}
				
			}	
			P3=0xFF;
			if(P3!= 0XFF)
			{
				delay(20);
				if(P3!= 0XFF)
				{
						switch(P3)
						{
							case 0XFE:key = 16;break;
							case 0XFD:key = 17;break;
							case 0XFB:key = 18;break;
							case 0XF7:key = 19;break;
						}
				
						while(P3 != 0xFF);
				}
			}
				
}

/*void main()
{
	
	we = 1;//打开位选锁存器
	P0 = 0XFE; //1111 1110
	we = 0;//锁存位选数据

	du = 1;//打开段选锁存器
	while(1)
	{
		KeyValue();//20个按键键盘扫描
		P0 = dula[key];//显示按键值
	}		
du = 0;
}*/


void main()
{
	//du = 0;
	//we = 0;

	P0 = 0xfe;
	we = 1;
	we = 0;

	while (1)
	{
		KeyValue();
		P0 = dula[key];
	}
	du = 1;
	du = 0;
}	
