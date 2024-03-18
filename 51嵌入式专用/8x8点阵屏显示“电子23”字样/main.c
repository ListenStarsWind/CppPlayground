#include <reg52.h>
#include <intrins.h>
sbit serial_input = P3 ^ 4 ;    // 数据串行输入口
sbit SCLK = P3 ^ 5  ;           // 串行输入上升沿触发口
sbit PCLK = P3 ^ 6;             // 并行输出上升沿触发口

#define uchar unsigned char
#define uint unsigned int
// 字模
//0xE0,0xEF,0x01,0x6D,0x01,0x6D,0x01,0xEF 汉字“电”的字模
//0xE7,0xF7,0xF7,0xF7,0x80,0xF7,0xFB,0xC3 汉字“子”的字模
//0xFF,0x83,0xBF,0xBF,0x83,0xFB,0xFB,0x83 数字“2”的字模
//0x83,0xFB,0xFB,0x83,0xFB,0xFB,0x83,0xFF 数字“3”的字模
uchar code arr[][8] =   {   0xE0,0xEF,0x01,0x6D,0x01,0x6D,0x01,0xEF,
                            0xE7,0xF7,0xF7,0xF7,0x80,0xF7,0xFB,0xC3,
                            0xFF,0x83,0xBF,0xBF,0x83,0xFB,0xFB,0x83,
                            0x83,0xFB,0xFB,0x83,0xFB,0xFB,0x83,0xFF,
                        };

// 数据输入函数
void import(uchar x)
{
    uint a;
    SCLK = 0;
    for (a = 0; a < 8; a++)
    {
        if (x & 0x01)
            serial_input = 1;
        else
            serial_input = 0;
        SCLK = 1;
        SCLK = 0;
        x >>= 1;
    }
}
// 数据写入函数
void output()
{
    PCLK = 0;
    PCLK = 1;
}

void main()
{
    uint i;
		uint b;
    uchar j ; // 行选初始数据
    uint k;         // 用于将数组中的数据传入寄存器的循环变量
    while (1)
    {
        for (i = 0; i < 4; i++)
        {
					//不能使用delay函数，使用delay函数会停止扫描，就更难显示图案，这个循环的目的是让每个字反复叠加，从而效果更明显，每个字的内部要快速扫描，单个字要停留1秒。
					for(b=144000;b>0;b--)
					{
						j=0x80;
            for (k = 0; k < 8; k++)
            {
                import(arr[i][k]);
                import(j);
                output();
                j = _cror_(j, 1);
                
            }
					}
						
						
        }
    }
}