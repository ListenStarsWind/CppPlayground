#pragma once

#include<iostream>
#include<stdbool.h>

namespace wind
{
	class Date
	{
	public:
		Date(int year = 1, int month = 1, int day = 1);
		~Date();
		bool operator>(const Date& d);
		bool operator==(const Date& d);
		bool operator!=(const Date& d);
		bool operator<(const Date& d);
		Date operator+(int n);
		void operator+=(int n);
		void operator++();
		Date operator-(int n);
		int operator-(const Date& d);
		void operator-=(int n);
		void operator--();
		//void Init(int year, int month, int day);
		void Print();
	private:
		int _year = 1;
		int _month = 1;
		int _day = 1;
	};
}