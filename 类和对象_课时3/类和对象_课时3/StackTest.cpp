#include"Stack.h"

#define N 1000000

void test1()
{
	clock_t begin = clock();
	auto p = (wind::pSDate)malloc(sizeof(wind::SDate) * N);
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
	wind::Stack s(N, p);
	clock_t end = clock();
	std::cout << end - begin << "ms" << std::endl;
}

void test2()
{
	clock_t begin = clock();
	wind::Stack s;
	int i = 0;
	for (; i < N; i++)
	{
		s.Push(i + 1);
	}
	clock_t end = clock();
	std::cout << end - begin << "ms" << std::endl;
}

void test3()
{
	int* p = (int*)malloc(sizeof(int)*10);
	if (p == nullptr)
	{
		std::cout << "!" << std::endl;
	}
	const wind::Stack s;
	s.Print();
}

void test5(wind::Stack s)
{

}

//int main()
//{
//	wind::Stack s1;
//	test5(s1);
//	return 0;
//}