#include"test.h"

int wind::a::_used;
int wind::a::_using;

void print(int& ed, int& ing)
{
	wind::a::out(ed, ing);
	std::cout << "已经创建的对象个数：" << ed << std::endl;
	std::cout << "正在使用的对象个数：" << ing << std::endl;
}

void test1()
{

	wind::a::init();
	int ed, ing;
	print(ed, ing);
	wind::a m;
	wind::a n;
	f(wind::a());
	print(ed, ing);
	wind::a o = m;
	wind::a p = n;
	wind::a q = m;
	print(ed, ing);
}

void test2()
{
	// 作为成员函数，也可以用具体的对象调用静态成员函数
	wind::a m;
	m.init();
}

void test3()
{
	wind::A x;
	F(x);
	std::cout << "==================" << std::endl;
	F(wind::A());
	std::cout << "==================" << std::endl;
	auto y = wind::A();
	std::cout << "==================" << std::endl;
}

wind::A test4()
{
	wind::A x;
	return x;
}

int main()
{
	wind::A y = test4();
	return 0;
}
