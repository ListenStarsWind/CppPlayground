#include"Date.h"

void test4()
{
	const int year = wind::GetDate();
	const int month = wind::GetDate();
	const int day = wind::GetDate();
	wind::Date d1(year, month, day);
	wind::Date d2(2005, 4, 11);
	const wind::Date d3;
	std::cout << "对象d1的值为：";
	d1.Print();
	std::cout << "对象d2的值为：";
	d2.Print();
	std::cout << "对象d3的值为：";
	d3.Print();
	if (d1 > d2)
	{
		std::cout << "d1更大" << std::endl;
	}
	else if (d1 == d2)
	{
		std::cout << "d1和d2一样大" << std::endl;
	}
	else
	{
		std::cout << "d2更大" << std::endl;
	}
	std::cout << "这是第" << d1 - d2 << "天" << std::endl;

	d1 += 600;
	d2 -= 500;
	std::cout << "d1 += 600 为：";
	d1.Print();
	std::cout << "d2 -= 500 为：";
	d2.Print();

	wind::Date d4 = d2 + 487;
	std::cout << "对象d4的值为：";
	d4.Print();

	wind::Date d5(2023, 2, 29);
	d5.Print();

	d5 = d4;
	d5 += -40;
	std::cout << "对象d5的值为：";
	d5.Print();
}

void test6()
{
	const int year = wind::GetDate();
	const int month = wind::GetDate();
	const int day = wind::GetDate();
	wind::Date d(year, month, day);
	std::cout << d <<std::endl;
	std::cin >> d;
	std::cout << d << std::endl;;
}

int main()
{
	test6();
	return 0;
}