#include"myList.h"
#include<iostream>
#include<list>
#include<vector>
#include<string>

void test1()
{
	wind::list<int> l;
	l.push_back(1);
	l.push_back(2);
	l.push_back(3);
	l.push_back(4);
	l.push_back(5);

	for (auto e : l)
	{
		std::cout << e << " ";
	}
	std::cout << std::endl;
}

void test2()
{
	wind::list<int> l;
	l.push_front(6);
	l.push_front(4);
	l.push_front(3);
	l.push_front(2);
	l.push_front(1);

	l.pop_back();
	l.push_back(5);
	wind::list<int> ll(l);

	for (auto e : l)
	{
		std::cout << e << " ";
	}
	std::cout << std::endl;

	wind::list<int> i(l);
	for (auto e : i)
	{
		std::cout << e << " ";
	}
	std::cout << std::endl;

	for (auto e : l)
	{
		std::cout << e << " ";
	}
	std::cout << std::endl;
}

void test3()
{
	wind::list<int> l;
	l.push_back(1);
	l.push_back(2);
	l.push_back(3);
	l.push_back(4);
	l.push_back(5);

	wind::list<int> i;
	i.push_back(10);
	i.push_back(20);
	i.push_back(30);
	i.push_back(40);
	i.push_back(50);

	for (auto e : l)
	{
		std::cout << e << " ";
	}
	std::cout << std::endl;

	for (auto e : i)
	{
		std::cout << e << " ";
	}
	std::cout << std::endl;

	i = l;

	for (auto e : i)
	{
		std::cout << e << " ";
	}
	std::cout << std::endl;

}

template<typename container>
void print_containers(const container obj)
{
	typename container::const_iterator it = obj.begin();
	while (it != obj.end())
	{
		std::cout << *it << " ";
		++it;
	}
	std::cout << std::endl;
}

void test5()
{
	std::list<int> l;
	std::vector<std::string> v;
	l.push_back(1);
	l.push_back(2);
	l.push_back(3);
	l.push_back(4);
	l.push_back(5);

	v.push_back("abc");
	v.push_back("def");
	v.push_back("ghi");
	v.push_back("jkl");
	v.push_back("mno");

	print_containers(l);
	print_containers(v);
}

void test4()
{
	wind::list<int> obj;
	obj.push_back(1);
	obj.push_back(2);
	obj.push_back(3);
	obj.push_back(4);
	obj.push_back(5);
	print_containers(obj);
}

int main()
{
	test5();
	return 0;
}