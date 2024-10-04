#include"C.h"

//void test1()
//{
//	int k = 0;
//	wind::A m(10, k);
//	m.F();
//	std::cout << k <<std::endl;
//	std::cout << m << std::endl;
//}
//
//void test2()
//{
//	int k = 0;
//	wind::B x(k, 15);
//}

void test3()
{
	// 既可以这样构造
	wind::C m1(1);
	// 也可以这样构造
	wind::C m2 = 2;
}

void test4()
{
	wind::D n1(1, 2);
	wind::D n2 = {1, 2};
}

void test5()
{
	wind::D(1, 2);
}

int main()
{
	test4();
	return 0;
}