#include"test.h"

int wind::a::_used;
int wind::a::_using;

void print(int& ed, int& ing)
{
	wind::a::out(ed, ing);
	std::cout << "�Ѿ������Ķ��������" << ed << std::endl;
	std::cout << "����ʹ�õĶ��������" << ing << std::endl;
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
	// ��Ϊ��Ա������Ҳ�����þ���Ķ�����þ�̬��Ա����
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
