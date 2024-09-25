#pragma once

#include<iostream>


namespace wind
{
	class Date
	{
	public:
		//Date(int year = 1, int month = 1, int day = 1);
		void Init(int year, int month, int day);
		void Print();
	private:
		int _year = 1;
		int _month = 1;
		int _day = 1;
	};
}