#include<iostream>

using namespace std;

//int main()
//{
//	double d = 1.25;
//	// int 和 double 表示数据大小,  意义相近, 形式不同
//	int a = static_cast<int>(d);
//	// 指针和int已经不是一个概念了, 无法使用static_cast
//	int* ptr = reinterpret_cast<int*>(a);
//	return 0;
//}

//int main()
//{
//	volatile const int a = 2;
//	//int* p = (int*)(&a);
//	int* p =const_cast<int*>(&a);
//	*p = 3;
//	cout << typeid(&a).name() << endl;
//	cout << p << endl;
//	cout << (void*)&a << endl;
//	cout << *p << endl;
//	cout << a << endl;
//	return 0;
//}

//void func(size_t pos)
//{
//	int end = 5;
//	while (end >= static_cast<int>(pos))
//	{
//		cout << end-- << endl;
//	}
//}
//
//int main()
//{
//	func(0);
//	return 0;
//}

class A
{
public:
	int _a = 0;

	virtual void func()
	{
		cout << "[class A] _a: " << _a << endl;
	}
};

class B : public A
{
public:
	int _b = 1;

	virtual void func()
	{
		cout << "[class B] _b: " << _b << endl;
	}
};

// 有时候, 会有这种需求
void f(A* ptr)
{
	// 默认传的是从class B切割下来的A*
	// 把它转回去
	B* Pb = dynamic_cast<B*>(ptr);
	Pb->_a++;
	Pb->_b++;
}

// 这里为了更好的模拟出越界访问的效果
// 临时修改对齐数, 让它们紧挨在一起
#pragma pack(1)
struct C
{
	A m;
	B n;
};
#pragma pack()

int main()
{
	A a;
	B b;

	cout << sizeof(a) << endl;
	cout << sizeof(b) << endl;
	cout << sizeof(C) << endl;

	// 派生可以直接转基类, 这是赋值兼容或者说切割
	A* Pa = &a;
	B* Pb = &b;
	Pa->func();
	Pb->func();

	C c;
	f(&c.m);
	f(&c.n);

	return 0;
}