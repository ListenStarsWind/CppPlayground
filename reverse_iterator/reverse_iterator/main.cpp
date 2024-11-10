#include"myList.h"
#include"myVector.h"
#include<iostream>
#include<string>

void test1()
{
	wind::list<int> lt;
	lt.push_back(1);
	lt.push_back(2);
	lt.push_back(3);
	lt.push_back(4);
	lt.push_back(5);

	wind::list<int>::iterator it1 = lt.begin();
	while (it1 != lt.end())
	{
		std::cout << (*it1)++ << " ";
		++it1;
	}
	std::cout << std::endl;

	wind::list<int>::reverse_iterator it2 = lt.rbegin();
	while (it2 != lt.rend())
	{
		std::cout << *it2 << " ";
		++it2;
	}
	std::cout << std::endl;
}

void test2()
{
	wind::list<std::string> ls;
	ls.push_back("123456");
	ls.push_back("abvdef");
	ls.push_back("ijklmn");
	ls.push_back("qwerty");
	ls.push_back("windname");

	const auto & l = ls;
	//for (auto& e : l)
	for (auto e : l)
	{
		e = "12345";
		std::cout << e << std::endl;
	}
}

void test_mylist()
{
	test1();
	test2();
}


struct A
{
	int _i;
	int _j;

	A(const int& i = int(), const int& j = int())
		:_i(i)
		,_j(j)
	{}
};

void test_myVector()
{
	wind::vector <A> v;
	v.push_back(A(1, 2));
	v.push_back(A(3, 4));
	v.push_back(A(5, 6));
	v.push_back(A(7, 8));

	const auto& cv = v;
	auto it = cv.rbegin();
	while (it != cv.rend())
	{
		std::cout << it->_i << " " << it->_j << std::endl;
		++it;
	}
}

int main()
{
	test_myVector();
	return 0;
}