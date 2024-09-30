#include"stack.h"
#include<time.h>
//#include"vld.h"
#include"Date.h"

#define N 1000000

void test1()
{
	clock_t begin = clock();
	auto p = (wind::p_stack_data)malloc(sizeof(wind::stack_data) * N);
	if (p == nullptr)
	{
		perror("test1 malloc fail");
		return;
	}
	int i = 0;
	for (; i < N; i++)
	{
		p[i] = i + 1;
	}
	wind::stack s(N, p);
	/*while (!s.IsEmpty())
	{
		wind::stack_data i;
		s.ReadPop(i);
		std::cout << i << " ";
	}
	std::cout << std::endl;*/
	clock_t end = clock();
	std::cout << end - begin << "ms" << std::endl;
}

//void test2()
//{
//	clock_t begin = clock();
//	wind::stack s;
//	int i = 0;
//	for (; i < N; i++)
//	{
//		s.push(i + 1);
//	}
//	/*while (!s.IsEmpty())
//	{
//		wind::stack_data i;
//		s.ReadPop(i);
//		std::cout << i << " ";
//	}
//	std::cout << std::endl;*/
//	s.Dest();
//	clock_t end = clock();
//	std::cout << end - begin << "ms" << std::endl;
//}


//void f(wind::stack s)
//{
//	s.push(3);
//}
//
//int main()
//{
//	wind::stack s;
//	f(s);
//	return 0;
//}