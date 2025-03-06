#include<iostream>

using namespace std;

//int main()
//{
//	double d = 1.25;
//	// int �� double ��ʾ���ݴ�С,  �������, ��ʽ��ͬ
//	int a = static_cast<int>(d);
//	// ָ���int�Ѿ�����һ��������, �޷�ʹ��static_cast
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

// ��ʱ��, ������������
void f(A* ptr)
{
	// Ĭ�ϴ����Ǵ�class B�и�������A*
	// ����ת��ȥ
	B* Pb = dynamic_cast<B*>(ptr);
	Pb->_a++;
	Pb->_b++;
}

// ����Ϊ�˸��õ�ģ���Խ����ʵ�Ч��
// ��ʱ�޸Ķ�����, �����ǽ�����һ��
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

	// ��������ֱ��ת����, ���Ǹ�ֵ���ݻ���˵�и�
	A* Pa = &a;
	B* Pb = &b;
	Pa->func();
	Pb->func();

	C c;
	f(&c.m);
	f(&c.n);

	return 0;
}