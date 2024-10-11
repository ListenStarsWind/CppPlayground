#include"Stack.h"

// 如何实现一个通用的交换函数呢？
//void Swap(int& left, int& right)
//{
//	int temp = left;
//	left = right;
//	right = temp;
//}
//void Swap(double& left, double& right)
//{
//	double temp = left;
//	left = right;
//	right = temp;
//}
//void Swap(char& left, char& right)
//{
//	char temp = left;
//	left = right;
//	right = temp;
//}
// ······

//template<typename v>
template<class v>
void Swap(v& val1, v& val2)
{
	auto temp = val1;
	val1 = val2;
	val2 = temp;
}

void test1()
{
	int i = 1, j = 10;
	double m = 1.25, n = 6.25;
	Swap(i, j);
	Swap(m, n);
}

//void test2()
//{
//
//	double i = add<double>(6, 1.25);
//	int j = add(6, (int)1.25);
//	std::cout << i << std::endl;
//	std::cout << j << std::endl;
//}

//void test2()
//{
//	wind::Stack<int> i;
//	wind::Stack<double> j;
//}

int add(const int& val1, const int& val2)
{
	std::cout << "int" << std::endl;
	return val1 + val2;
}

template<class T>
T add(const T& val1, const T& val2)
{
	std::cout << "template" << std::endl;
	return val1 + val2;
}

int main()
{
	auto i = add(1, 5);
	std::cout << i << std::endl;
	// 若是非要使用模版生成的函数也不是不行
	// 显式实例化即可
	auto j = add<int>(1, 5);
	std::cout << j << std::endl;
	return 0;
}
