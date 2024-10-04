#include"B.h"

wind::B::B(int& n, int c)
// A的默认构造函数必须要给参数
	:_i(5, n)
	,_m(10)
{
	_m = c;
}