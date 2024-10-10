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
	// �����ڴ��
	auto p = (void*)new char[44];
	// д��һ������
	*((int*)p) = 10;
	// Ų��δд�����ʼλ��
	A* q = (A*)((char*)p + sizeof(int));
	// ʵ��������
	new(q) A;
	// �Ƶ�δд�����ʼλ��
	auto m = q + sizeof(A);
	// ʵ��������
	new(m) A(6);
	// �ֶ���������
	m->~A();
	q->~A();
	free(p);
	return 0;
}