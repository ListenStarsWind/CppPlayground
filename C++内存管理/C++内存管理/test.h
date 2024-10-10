#pragma once

#include<iostream>

namespace wind
{
	class A
	{
	public:
		A(int val = 2);
		A(const A& obj);
		~A();
	private:
		int _i;
	};
}