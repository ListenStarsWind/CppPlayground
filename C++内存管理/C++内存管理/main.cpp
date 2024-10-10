#include"test.h"
#include"Stack.h"
//#include"vld.h"

wind::Stack* func()
{
	auto p = new wind::Stack;
	return p;
}

void test1()
{
	auto x = func();
	x->Push(1);
	x->Push(2);
	x->Push(3);
	x->Print();
	delete x;
}

void test2()
{
	auto p = new int[10];
	delete p;
}


class A
{
public:
	A(int val = 5)
		:_i(1)
	{
		_i = val;
	}
	~A()
	{
		std::cout << "===" << std::endl;
	}
private:
	int _i;
};


void test3()
{
	auto p = new A[10];
	free(p);
}

int main()
{
	// 建立内存池
	auto p = (void*)new char[44];
	// 写入一个整型
	*((int*)p) = 10;
	// 挪到未写入的起始位置
	A* q = (A*)((char*)p + sizeof(int));
	// 实例化对象
	new(q) A;
	// 移到未写入的起始位置
	auto m = q + sizeof(A);
	// 实例化对象
	new(m) A(6);
	// 手动调用析构
	m->~A();
	q->~A();
	free(p);
	return 0;
}