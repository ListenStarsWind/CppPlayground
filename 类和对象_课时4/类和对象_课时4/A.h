#pragma once

#include<iostream>

namespace wind
{
	class A
	{
		friend std::ostream& operator<<(std::ostream& out, const wind::A& m);
	public:
		A(int i, int& j);
		void F();
	private:
		const int _a;
		int& _b;
	};
}