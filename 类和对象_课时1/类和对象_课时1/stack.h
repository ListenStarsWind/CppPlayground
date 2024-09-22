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
		// member function
		void Init();
		void Dest();
		void Ext();
		void push(stack_data val);
		bool IsEmpty();
		bool ReadTop(stack_data& val);
		bool Pop();
		bool ReadPop(stack_data& val);

	private:
		// member variable
		p_stack_data _p;
		int _top;
		int _capacity;
	};
}