#include<list>
#include<iostream>
#include<vector>
#include<time.h>
#include<algorithm>

void using1()
{
	std::list<int> lt;
	lt.push_back(5);
	lt.push_back(3);
	lt.push_back(2);
	lt.push_back(4);
	lt.push_back(1);

	// 默认是升序 less
	// 降序是greater
	// 使用仿函数降序排列
	// 仿函数之后会详细说
	std::greater<int> gt;
	lt.sort(gt);

	std::list<int>::iterator it = lt.begin();
	while (it != lt.end())
	{
		std::cout << *it << " ";
		++it;
	}
	std::cout << std::endl;
}

void using2(const int N)
{
	srand(time(0));
	
	std::list<int> l1, l2;
	for (int i = 0; i < N; i++)
	{
		int e = rand();
		l1.push_back(e);
		l2.push_back(e);
	}

	int begin1 = clock();
	std::vector<int> v(l1.begin(), l1.end());
	std::sort(v.begin(), v.end());
	l1.assign(v.begin(), v.end());
	int end1 = clock();

	int begin2 = clock();
	l2.sort();
	int end2 = clock();

	std::cout << "list->vector->list:" << end1 - begin1 << "ms." << std::endl;
	std::cout << "list:" << end2 - begin2 << "ms." << std::endl;
}

void using3()
{
	std::list<int> l;
	l.push_back(1);
	l.push_back(1);
	l.push_back(1);
	l.push_back(4);
	l.push_back(2);
	l.push_back(2);

	l.remove(1);

	for (auto e : l)
	{
		std::cout << e << " ";
	}
	std::cout << std::endl;
}

void using4()
{
	std::list<int> list1, list2;
	list1.push_back(1);
	list1.push_back(2);
	list1.push_back(3);
	list1.push_back(4);
	list1.push_back(5);

	list2.push_back(10);
	list2.push_back(20);
	list2.push_back(30);
	list2.push_back(40);
	list2.push_back(50);

	// 把单个元素转移
	list1.splice(++list1.begin(), list2, ++list2.begin());
	std::cout << "list1->";
	for (auto e : list1)
	{
		std::cout << e << " ";
	}
	std::cout << std::endl;
	std::cout << "list2->";
	for (auto e : list2)
	{
		std::cout << e << " ";
	}
	std::cout << std::endl;

	// 转移区间
	list1.splice(++list1.begin(), list2, ++list2.begin(), --list2.end());
	std::cout << "list1->";
	for (auto e : list1)
	{
		std::cout << e << " ";
	}
	std::cout << std::endl;
	std::cout << "list2->";
	for (auto e : list2)
	{
		std::cout << e << " ";
	}
	std::cout << std::endl;

	// 转移全部元素
	list1.splice(++list1.begin(), list2);
	std::cout << "list1->";
	for (auto e : list1)
	{
		std::cout << e << " ";
	}
	std::cout << std::endl;
	std::cout << "list2->";
	for (auto e : list2)
	{
		std::cout << e << " ";
	}
	std::cout << std::endl;
}

void using5()
{

}

//int main()
//{
//	using4();
//	return 0;
//}