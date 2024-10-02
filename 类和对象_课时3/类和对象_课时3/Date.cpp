#include"Date.h"

int wind::GetDate()
{
    static flag i = year;
    auto now = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(now);
    std::tm localTime;

    localtime_s(&localTime, &t);
    int ret = -1;
    switch (i)
    {
    case year:
        ret = localTime.tm_year + 1900;
        i = month;
        break;
    case month:
        ret = localTime.tm_mon + 1;
        i = day;
        break;
    case day:
        ret = localTime.tm_mday;
        i = year;
        break;
    }
    return ret;
}

wind::Date::Date(int year, int month, int day)
{
    if ((month < 1 || month > 12) || (day < 1 || day > DayList(year, month)))
    {
        std::cout << "Error: illegal initialization parameter!" << std::endl;
    }
   
        _year = year;
        _month = month;
        _day = day;
}

wind::Date::Date(const Date& d)
{
    _year = d._year;
    _month = d._month;
    _day = d._day;
}

wind::Date::~Date(){}

int wind::DayList(int year, int month)
{
    const static int arr[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
    if ((month == 2) && ((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0)))
        return 29;
    else
        return arr[month];
}

wind::Date& wind::Date::operator=(const Date& d)
{
    if (this != &d)
    {
        _year = d._year;
        _month = d._month;
        _day = d._day;
    }
    return *this;
}

//wind::Date wind::Date::operator+(int nu)const
//{
//    if (nu < 0)
//    {
//        return *this - (-nu);
//    }
//
//    Date d = *this;
//    d._day += nu;
//    int day = DayList(d._year, d._month);
//    while (d._day > day)
//    {
//        d._day -= day;
//        d._month++;
//
//        if (d._month > 12)
//        {
//            d._month = 1;
//            d._year++;
//        }
//        day = DayList(d._year, d._month);
//    }
//    return d;
//}

wind::Date wind::Date::operator+(int nu)const
{
    Date d = *this;
    d += nu;
    return d;
}

//wind::Date wind::Date::operator-(int nu)const
//{
//    if (nu < 0)
//    {
//        return *this + (-nu);
//    }
//
//    Date d = *this;
//    d._day -= nu;
//    int day = 0;
//    while (d._day < 1)
//    {
//        d._month--;
//        if (d._month < 1)
//        {
//            d._year--;
//            d._month = 12;
//        }
//        day = DayList(d._year, d._month);
//        d._day += day;
//    }
//    return d;
//}

wind::Date wind::Date::operator-(int nu)const
{
    Date d = *this;
    d -= nu;
    return d;
}

bool wind::Date::operator!=(const Date& d)const
{
    if (_year != d._year || _month != d._month || _day != d._day)
        return true;
    else
        return false;
}

bool wind::Date::operator==(const Date& d)const
{
    if (*this != d)
        return false;
    else
        return true;
}

bool wind::Date::operator>(const Date& d)const
{
    if (_year > d._year)
        return true;
    else if (_year < d._year)
        return false;
    else if (_month > d._month)
        return true;
    else if (_month < d._month)
        return false;
    else if (_day > d._day)
        return true;
    else
        return false;
}

bool wind::Date::operator<(const Date& d)const
{
    if (*this == d || *this > d)
        return false;
    else
        return true;
}

//wind::Date& wind::Date::operator+=(int num)
//{
//    *this = *this + num;
//    return *this;
//}

wind::Date& wind::Date::operator+=(int num)
{
    if (num < 0)
    {
        return *this -= (-num);
    }

    _day += num;
    int day = DayList(_year, _month);
    while (_day > day)
    {
        _day -= day;
        _month++;

        if (_month > 12)
        {
            _year++;
            _month = 1;
        }
        day = DayList(_year, _month);
    }
    return *this;
}

//wind::Date& wind::Date::operator-=(int num)
//{
//    *this = *this - num;
//    return *this;
//}

wind::Date& wind::Date::operator-=(int num)
{
    if (num < 0)
    {
        return *this += (-num);
    }

    _day -= num;
    int day = 0;
    while (_day < 1)
    {
        _month--;
        if (_month < 1)
        {
            _year--;
            _month = 12;
        }
        day = DayList(_year, _month);
        _day += day;
    }
    return *this;
}

wind::Date& wind::Date::operator++()
{
    return *this += 1;
}

wind::Date wind::Date::operator++(int)
{
    Date d = *this;
    *this += 1;
    return d;
}

wind::Date& wind::Date::operator--()
{
    return *this -= 1;
}

wind::Date wind::Date::operator--(int)
{
    Date d = *this;
    *this -= 1;
    return d;
}

int wind::Date::operator-(const Date& d)const
{
    int flag = 1;
    Date max = *this;
    Date min = d;
    
    if (*this < d)
    {
        flag = -1;
        max = d;
        min = *this;
    }

    int count = 0;
    while (min != max)
    {
        ++min;
        count++;
    }

    return flag * count;
}

void wind::Date::Print()const
{
    std::cout << _year << "/" << _month << "/" << _day << std::endl;
}