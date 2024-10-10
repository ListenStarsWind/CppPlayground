#pragma once

#include<stdlib.h>
#include<iostream>


namespace wind
{
	typedef int SDate, * pSDate;
	class Stack
	{
	public:
		Stack(size_t sz = 4, pSDate pArr = nullptr);
		~Stack();
		Stack(const Stack& s);
		Stack& operator=(const Stack& s);
		void Push(int val);
		void Extend();
		void Print()const;
	private:
		pSDate _val;
		size_t _top;
		size_t _capacity;
	};
}