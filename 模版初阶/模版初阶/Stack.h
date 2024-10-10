#pragma once

#include<stdlib.h>
#include<iostream>


namespace wind
{
	template<class SDate>
	class Stack
	{
	public:
		Stack(size_t sz = 4, SDate* pArr = nullptr);
		~Stack();
		Stack(const Stack& s);
		Stack& operator=(const Stack& s);
		void Push(int val);
		void Extend();
		void Print()const;
	private:
		SDate* _val;
		size_t _top;
		size_t _capacity;
	};
}