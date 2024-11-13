#include"template.h"

template<class T>
T add(const T& n1, const T& n2)
{
	return n1 + n2;
}

template
int add<int>(const int& n1, const int& n2);

template<class T>
void test<T>::push(const T&)
{
	std::cout << "using push(const T&)" << std::endl;
}

template
class test<int>;