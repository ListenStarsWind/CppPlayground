#include"SeqList.h"

void SLTest1()
{
	wind::SeqList s1;
	s1.Push(1);
	s1.Push(2);
	s1.Push(3);
	s1.Push(4);
	s1.Print();
}

void SLTest2()
{
	wind::SeqList s1;
	s1.Push(1);
	s1.Push(2);
	s1.Push(3);
	s1.Push(4);
	size_t i = 0, j = s1.Size();
	for (; i < j; i++)
	{
		std::cout << s1[i]++ << " ";
	}
	std::cout << std::endl;
	for (i = 0; i < j; i++)
	{
		std::cout << s1[i] << " ";
	}
	std::cout << std::endl;
}

// 为了提高效率，使用引用传参
// 为了避免被改，使用静态引用
void SLTest3_1(const wind::SeqList& s)
{
	size_t i = 0, j = s.Size();
	for (i = 0; i < j; i++)
	{
		std::cout << s[i] << " ";
	}
	std::cout << std::endl;
	/*for (i = 0; i < j; i++)
	{
		s[i]*=2;
	}*/
}

void SLTest3()
{
	wind::SeqList s1;
	s1.Push(1);
	s1.Push(2);
	s1.Push(3);
	s1.Push(4);
	SLTest3_1(s1);
	s1.Print();
}

//int main()
//{
//	int i = 4;
//	std::cout << i;
//	std::cin >> i;
//	std::cout << i;
//	return 0;
//}