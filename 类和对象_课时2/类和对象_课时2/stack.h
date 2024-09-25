#pragma once
#include<stdlib.h>
#include<iostream>
#include<stdbool.h>

namespace wind
{
	typedef int stack_data, * p_stack_data;
	class stack
	{
	public:
		stack(size_t sz = 4, p_stack_data pArr = nullptr);
		~stack();
		void Ext();
		void push(stack_data val);
		bool IsEmpty();
		bool ReadTop(stack_data& val);
		bool Pop();
		bool ReadPop(stack_data& val);

	private:
		p_stack_data _p;
		size_t _top;
		size_t _capacity;
	};
}