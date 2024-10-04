#pragma once

namespace wind
{
	class C
	{
	public:
		C(int i);
	private:
		int _i;
	};
}

namespace wind
{
	class D
	{
	public:
		explicit D(int i, int j);
	private:
		int _i;
		int _j;
	};
}