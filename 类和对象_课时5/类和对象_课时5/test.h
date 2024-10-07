#pragma once

#include<iostream>

namespace wind
{
	class a
	{
	public:
		a();
		a(const a& object);
		~a();
		static void init();
		static void out(int& ed, int& ing);
	private:
		static int _using;
		static int _used;
	};
	void f(wind::a priject);
}

namespace wind
{
	class A
	{
	public:
		A();
		A(const A& object);
		~A();
		void print()const;
		A& operator=(const A& opject);
	private:
		int _i;
	};
	void F(A opject);
}