#pragma once

#include <iostream>
#include <chrono>
#include <iomanip>
#include <ctime>
#include <stdbool.h>

namespace wind
{
	typedef enum flag
	{
		year,
		month,
		day
	}flag;

	int GetDate();
	int DayList(int year, int month);

	class Date
	{
		friend std::ostream& operator<<(std::ostream& out, const Date& d);
		friend std::istream& operator>>(std::istream& in, Date& d);
	public:
		Date(int year = 1, int month = 1, int day = 1);
		Date(const Date& d);
		~Date();
		Date& operator=(const Date& d);
		Date* operator&();
		const Date* operator&()const;
		Date operator+(int num)const;
		Date operator-(int num)const;
		bool operator!=(const Date& d)const;
		bool operator==(const Date& d)const;
		bool operator>(const Date& d)const;
		bool operator<(const Date& d)const;
		Date& operator+=(int num);
		Date& operator-=(int num);
		Date& operator++();
		Date operator++(int);
		Date& operator--();
		Date operator--(int);
		int operator-(const Date& d)const;
		void Print()const;
	private:
		int _year;
		int _month;
		int _day;
	};
}