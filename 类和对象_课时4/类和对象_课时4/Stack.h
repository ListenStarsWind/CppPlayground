#pragma once

#include<stdlib.h>
#include<iostream>


namespace wind
{
	typedef int SDate, * pSDate;
	class Stack
	{
	public:
		// When the data to be processed is stored in the dynamically allocated 
		// memory block and the memory block is all valid data, you can directly 
		// enter the pointer to the memory block, at this time, the number of 
		// data parameter ¡°sz¡± must be accurate; otherwise, you can roughly 
		// estimate the number of data to be processed as the first parameter, 
		// and do not enter the second parameter.
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