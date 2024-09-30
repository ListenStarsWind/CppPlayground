#include"Date.h"
#include<ctime>

int main()
{
    // 获取当前时间
    std::time_t t = std::time(nullptr);
    std::tm localTime;

    // 使用 localtime_s 获取本地时间
    localtime_s(&localTime, &t);

    // 获取年、月、日
    int year = localTime.tm_year + 1900; // tm_year是从1900年开始的
    int month = localTime.tm_mon + 1;    // tm_mon是从0开始的
    int day = localTime.tm_mday;

	wind::Date d1(year,month,day);
    std::cout << "d1的初始状态为：";
    d1.Print();

    wind::Date d2 = d1 + 50;
    std::cout << "d2的初始状态为：";
    d2.Print();

    if (d2 > d1)
    {
        std::cout << "d2更大" << std::endl;
    }
    else
    {
        std::cout << "d1更大" << std::endl;
    }
	

    int variety = 0;

    variety = 600;
    d1 += variety;
    std::cout << "d1自加" << variety << "为：";
    d1.Print();

    d1 -= variety;
    std::cout << "d1自减" << variety << "为：";
    d1.Print();

    
    variety = 50;
    d2 -= variety;
    std::cout << "d2自减" << variety << "为：";
    d1.Print();
   
	return 0;
}