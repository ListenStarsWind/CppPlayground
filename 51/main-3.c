/*********************************************************************************
 * 【作    者】：	听风若依
 * 【版    本】：	V1.0
 * 【实验平台】：	清翔 QX-MCS51 单片机开发板
 * 【外部晶振】： 	11.0592mhz
 * 【主控芯片】： 	STC89C52
 * 【编译环境】： 	Keil μVisio5
 * 【编辑环境】： 	VS code
 * 【程序功能】： 	定时器0工作模式1，16位定时模式，由定时器0引发中断，执行中断程序。
 * 【使用说明】： 	按下S6数码管显示数字加一，按下S10数码管显示数字减一,按下S2数字清零。
 **********************************************************************************/
#include <reg52.h>
#define uint unsigned int
#define uchar unsigned char
#define ulong unsigned long
sbit DU = P2 ^ 6;
sbit WE = P2 ^ 7;
ulong number = 31415926;
uint flag = 20;
uchar code DUnumber[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F}; // 共阴极数码管段选表
uchar code WEnumber[] = {0xfe, 0xfd, 0xfb, 0xf7, 0xef, 0xdf, 0xbf, 0x7f};             // 八位数码管位选表（低电位表示选中该数码管)

/*====================================
函数	： delay(uint z)
参数	：z 延时毫秒设定，取值范围0-65535
返回值	：无
描述	：12T/Fosc11.0592M毫秒级延时
====================================*/
void delay(uint z)
{
    uint x, y;
    for (x = z; x > 0; x--)
        for (y = 114; y > 0; y--)
            ;
}

/*===========================================
函数	： disply(uint i)
参数    ： i 设定显示数字，取值范围0-99999999
描述	： 八位共阴极数码管显示函数。
===========================================*/
void disply(ulong i)
{

    static uchar location;
    P0 = 0xFF;
    WE = 1;
    P0 = WEnumber[location];
    WE = 0;
    switch (location)
    {
    case 0:
        DU = 1;
        P0 = DUnumber[number / 10000000];
        DU = 0;
        break;
    case 1:
        DU = 1;
        P0 = DUnumber[number % 10000000 / 1000000];
        DU = 0;
        break;
    case 2:
        DU = 1;
        P0 = DUnumber[number % 1000000 / 100000];
        DU = 0;
        break;
    case 3:
        DU = 1;
        P0 = DUnumber[number % 100000 / 10000];
        DU = 0;
        break;
    case 4:
        DU = 1;
        P0 = DUnumber[number % 10000 / 1000];
        DU = 0;
        break;
    case 5:
        DU = 1;
        P0 = DUnumber[number % 1000 / 100];
        DU = 0;
        break;
    case 6:
        DU = 1;
        P0 = DUnumber[number % 100 / 10];
        DU = 0;
        break;
    case 7:
        DU = 1;
        P0 = DUnumber[number % 10];
        DU = 0;
        break;
    }
    location++;
    if (8 == location)
        location = 0;
}

/*====================================
函数	： Initializer()
参数	：无
返回值	：无
描述	：初始化中断系统，定时器0。
====================================*/
void Initializer()
{
    EA = 1;
    ET0 = 1;
    TR0 = 1;
    TMOD = 0X01;
    // 一轮机器周期耗时1.085us,12轮时钟周期为一轮机器周期。
    TL0 = 0XFE;
    TH0 = 0XC9; // 定时15ms。
}

void main()
{

    Initializer();
    while (1)
    {
        // 矩阵键盘扫描。
        P3 = 0XF0;
        if (P3 != 0XF0)
        {
            delay(20);
            if (P3 != 0XF0)
            {
                switch (P3)
                {
                case 0xE0:
                    flag = 0; //
                    break;
                case 0xD0:
                    flag = 1;
                    break;
                case 0xB0:
                    flag = 2;
                    break;
                case 0x70:
                    flag = 3;
                    break;
                }
                P3 = 0X0F;
                switch (P3)
                {
                case 0x0E:
                    flag = flag;
                    break;
                case 0x0D:
                    flag = flag + 4;
                    break;
                case 0x0B:
                    flag = flag + 8;
                    break;
                case 0x07:
                    flag = flag + 12;
                    break;
                }
                while (P3 != 0X0F)
                    ;
            }
        }
        // 独立键盘扫描
        P3 = 0XFF;
        if (P3 != 0XFF)
        {
            delay(5);
            if (P3 != 0XFF)
                switch (P3)
                {
                case 0xFE: 
                flag = 16;
                    break;
                    case 0xFD:
                    flag = 17;
                    break;
                case 0xFB:
                    flag = 18;
                    break;
                case 0xF7:
                    flag = 19;
                    break;
                }
            while (P3 != 0XFF)
                ;
        }
        // 变量调整
        switch (flag)
        {
        case 0:
            flag = 20;
            if (99999999 != number)
                number++;
            break;
        case 4:
            flag = 20;
            if (0 != number)
                number--;
                break;
        case 16:
		flag = 20;
        number = 0;
		break;
		case 19:
		    flag = 20;
			number = 31415926;
            break;
		default:
        break;
    }
    }
}

/*====================================
函数	： timer0()
参数	：无
返回值	：无
描述	：定时器0溢出引发中断，执行中断程序。
====================================*/
void timer0() interrupt 1
{
    TL0 = 0XFE;
    TH0 = 0XC9; 
    disply(number);
   
}
