#include<math.h>

// 用于描述潜艇坐标
typedef struct submarines_sizes
{
	int length;   //长度
	int width;    //宽度
	int height;   //高度
}submarines_sizes, * p_submarines_sizes;

// 用于描述炸弹
typedef struct bombshell_sizes
{
	int kill_radiu;			//杀伤半径
	int sigma;				//水平方向标准差
	int submarines_target;  //潜艇中心深度定位值
}bombshell_sizes, * p_bombshell_sizes;

