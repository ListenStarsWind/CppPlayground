#include"Date.h"

int main()
{
	const int year = wind::GetDate();
	const int month = wind::GetDate();
	const int day = wind::GetDate();
	wind::Date d1(year, month, day);
	wind::Date d2(2005, 4, 11);
	const wind::Date d3;
	std::cout << "����d1��ֵΪ��";
	d1.Print();
	std::cout << "����d2��ֵΪ��";
	d2.Print();
	std::cout << "����d3��ֵΪ��";
	d3.Print();
	if (d1 > d2)
	{
		std::cout << "d1����" << std::endl;
	}
	else if(d1 == d2)
	{
		std::cout << "d1��d2һ����" << std::endl;
	}
	else
	{
		std::cout << "d2����" << std::endl;
	}
	std::cout << "���ǵ�" << d1 - d2 << "��" << std::endl;

	d1 += 600;
	d2 -= 500;
	std::cout << "d1 += 600 Ϊ��";
	d1.Print();
	std::cout << "d2 -= 500 Ϊ��";
	d2.Print();

	wind::Date d4 = d2 + 487;
	std::cout << "����d4��ֵΪ��";
	d4.Print();

	wind::Date d5(2023, 2, 29);

	d5 = d4;
	d5 += -40;
	std::cout << "����d5��ֵΪ��";
	d5.Print();
	return 0;
}