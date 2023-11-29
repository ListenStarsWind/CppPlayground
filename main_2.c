#include<reg52.h>
#include<intrins.h>
unsigned char code tabel[8]={0xFF,0xEF,0xEF,0x83,0xAB,0x83,0xEF,0xFF};
sbit DIO = P3^4;
sbit S_CLK = P3^5;
sbit O_CLK = P3^6;
int i,j;
unsigned char k;
void Send_Byte(unsigned char dat)//8位串行输入函数
{
    for(i=8;i>0;i--)
    {
        S_CLK = 0;
        if(dat & 0x01)
        {
            DIO = 1;
        }
        else
        {
            DIO = 0;
        }
        S_CLK = 1;
        dat>>=1;
    }  
    
    
} 
void main()
{
    k = 0x80;
    for(j=0;j<8;j++)
    {
        O_CLK = 0;
        Send_Byte(tabel[j]);
        Send_Byte(k);
        O_CLK = 1;
        k = _cror_(k,1);
    }
}
