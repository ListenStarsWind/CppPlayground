#include"Date.h"
#include<ctime>

int main()
{
    // ��ȡ��ǰʱ��
    std::time_t t = std::time(nullptr);
    std::tm localTime;

    // ʹ�� localtime_s ��ȡ����ʱ��
    localtime_s(&localTime, &t);

    // ��ȡ�ꡢ�¡���
    int year = localTime.tm_year + 1900; // tm_year�Ǵ�1900�꿪ʼ��
    int month = localTime.tm_mon + 1;    // tm_mon�Ǵ�0��ʼ��
    int day = localTime.tm_mday;

	wind::Date d1(year,month,day);
    std::cout << "d1�ĳ�ʼ״̬Ϊ��";
    d1.Print();

    wind::Date d2 = d1 + 50;
    std::cout << "d2�ĳ�ʼ״̬Ϊ��";
    d2.Print();

    if (d2 > d1)
    {
        std::cout << "d2����" << std::endl;
    }
    else
    {
        std::cout << "d1����" << std::endl;
    }
	

    int variety = 0;

    variety = 600;
    d1 += variety;
    std::cout << "d1�Լ�" << variety << "Ϊ��";
    d1.Print();

    d1 -= variety;
    std::cout << "d1�Լ�" << variety << "Ϊ��";
    d1.Print();

    
    variety = 50;
    d2 -= variety;
    std::cout << "d2�Լ�" << variety << "Ϊ��";
    d1.Print();
   
	return 0;
}