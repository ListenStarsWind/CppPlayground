#include"test.h"


wind::A::A(int val)
	:_i(1)
{
	_i = val;
	std::cout << "A(int val)" << std::endl;
}

wind::A::A(const A& obj)
	:_i(obj._i)
{
	std::cout << "A(const A& obj)" << std::endl;
}

wind::A::~A()
{
	std::cout << "~A()" << std::endl;
}