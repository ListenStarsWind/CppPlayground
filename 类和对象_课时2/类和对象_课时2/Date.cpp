#include"Date.h"

wind::Date::Date(int year, int month, int day)
{
	_year = year;
	_month = month;
	_day = day;
}

//void wind::Date::Init(int year, int month, int day)
//{
//	_year = year;
//	_month = month;
//	_day = day;
//}

wind::Date::~Date()
{
	//std::cout << "~Date()" << std::endl;
}

bool wind::Date::operator>(const Date& d)
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

bool wind::Date::operator==(const Date& d)
{
	if (_year == d._year && _month == d._month && _day == d._day)
		return true;
	else
		return false;
}

bool wind::Date::operator!=(const Date& d)
{
	if (*this == d)
		return false;
	else
		return true;
}

bool wind::Date::operator<(const Date& d)
{
	if ((*this > d) || (*this == d))
		return false;
	else
		return true;
}

static int DayList(int year, int month)
{
	int arr[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
	if ((month == 2) && ((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0)))
		return 29;
	else
		return arr[month];
}

wind::Date wind::Date::operator+(int n)
{
	Date d = *this;
	d._day += n;
	int day = DayList(d._year, d._month);
	while (d._day > day || d._day < 1)
	{
		if (d._day > day)
		{
			d._day -= day;
			d._month++;
			if (d._month > 12)
			{
				d._month = 1;
				d._year++;
			}
		}
		else if (d._day < 1)
		{
			d._day += day;
			d._month--;
			if (d._month < 1)
			{
				d._month = 12;
				d._year--;
			}
		}

		day = DayList(d._year, d._month);
	}
	return d;
}

void wind::Date::operator+=(int n)
{
	*this = *this + n;
}

void wind::Date::operator++()
{
	*this += 1;
}

wind::Date wind::Date::operator-(int n)
{
	n++;
	return *this + (-n);
}

int wind::Date::operator-(const Date& d)
{
	if (*this == d)
		return 0;
	Date max, min;
	if (*this > d)
	{
		max = *this;
		min = d;
	}
	else if (*this < d)
	{
		max = d;
		min = *this;
	}

	while (max != min)
	{
		min++;
	}
}

void wind::Date::operator-=(int n)
{
	*this = *this - n;
}

void wind::Date::operator--()
{
	*this -= 1;
}

void wind::Date::Print()
{
	std::cout << _year << "/" << _month << "/" << _day << std::endl;
}