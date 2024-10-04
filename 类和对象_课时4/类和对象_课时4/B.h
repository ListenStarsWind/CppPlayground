#pragma once

#include"A.h"

namespace wind
{
	class B
	{
	public:
		B(int& n, int c);
	private:
		A _i;
		int _j = 4;
		int _k = 6;
		int _m;
	};
}