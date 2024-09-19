#include"test.h"


namespace Whisper
{
	void Func1(int a)
	{
		std::cout << a << std::endl;
		return;
	}

	void Func2(int a, int b, int c)
	{
		std::cout << a << std::endl;
		std::cout << b << std::endl;
		std::cout << c << std::endl;
		return;
	}

	void Func3(int a, int b, int c)
	{
		std::cout << a << std::endl;
		std::cout << b << std::endl;
		std::cout << c << std::endl;
		return;
	}
}

// In C, functions with the same name are not allowed.
void Swap(int* x, int* y)
{
	int tem = *x;
	*x = *y;
	*y = tem;
}

void Swap(double* x, double* y)
{
	double tem = *x;
	*x = *y;
	*y = tem;
}


//int main()
//{
//	Whisper::Func1();
//	Whisper::Func1(15);
//	Whisper::Func2(1);
//	Whisper::Func2(1, 2);
//	Whisper::Func2(1, 2, 5);
//	Whisper::Func3();
//}

//int main()
//{
//	int n = 0;
//	int& a = n;
//	int& b = n;
//	int& c = a;
//
//	std::cout << &n << std::endl;
//	std::cout << &a << std::endl;
//	std::cout << &n << std::endl;
//	std::cout << &c << std::endl;
//	return 0;
//}

//int main()
//{
//	int i = 1;
//	double& j = i;
//	return 0;
//}

int main()
{
	int i = 0;
	double j = i;
	return 0;
}

//#include<assert.h>
//
//typedef struct SeqList
//{
//	int* _P;
//	int _Size;
//	int _Capacity;
//}SeqList, *pSeqList;
//
//
//// Modify the value at position i in the order table.
//int& SeqListModI(pSeqList ps, int i)
//{
//	assert(ps->_Size > i);
//	return ps->_P[i];
//}
//
//pSeqList Init(void)
//{
//	int* p = (int*)malloc(sizeof(int) * 10);
//	if (p == NULL)
//		return NULL;
//	pSeqList ps = (pSeqList)malloc(sizeof(SeqList));
//	if (ps == NULL)
//		return NULL;
//	ps->_Capacity = ps->_Size = 10;
//	ps->_P = p;
//	int cir = 0;
//	for (; cir < 10; cir++)
//	{
//		ps->_P[cir] = cir;
//	}
//	return ps;
//}
//
//void SeqListPrint(pSeqList ps)
//{
//	int cir = 0;
//	for (; cir < ps->_Size; cir++)
//	{
//		std::cout << ps->_P[cir] << " ";
//	}
//	std::cout << std::endl;
//}
//
//int main()
//{
//	pSeqList ps = Init();
//	SeqListPrint(ps);
//	SeqListModI(ps, 2) = 20;
//	SeqListModI(ps, 5) = 23;
//	SeqListModI(ps, 7) = 25;
//	SeqListPrint(ps);
//	return 0;
//}