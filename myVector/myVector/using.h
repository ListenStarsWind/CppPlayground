#pragma once

#include<vector>
#include<string>
#include<iostream>
#include<algorithm>

// construct https://legacy.cplusplus.com/reference/vector/vector/vector/
void using1()
{
	// 如果觉得缺省分配器的效率较低，可以自
	// 己实现一个，然后传给参数`alloc`

	// 基本构造
	std::vector<int> v1;

	// 将其中10个元素全部初始化为0
	std::vector<int> v2(10, 0);

	// 使用容器的迭代器区间进行初始化
	std::vector<int> v3(v2.begin(), v2.end());
	std::string s("hello world");
	std::vector<char> v4(s.begin(), s.end());
	
	// 类型强转 char·ASCII码形式 -> int
	std::vector<int> v5(s.begin(), s.end());

	// 构造一个二维数组
	std::vector<std::vector<int>> v;
	v.push_back(v1);
	v.push_back(v2);
	v.push_back(v3);
	v.push_back(v5);


	// 遍历

	// 下标
	size_t begin = 0;
	for (; begin < v5.size(); begin++)
	{
		std::cout << v5[begin] << " ";
	}
	std::cout << std::endl;

	// 迭代器
	std::vector<char>::iterator it = v4.begin();
	while (it != v4.end())
	{
		std::cout << *it;
		++it;
	}
	std::cout << std::endl;

	// 范围for
	for (auto& n : v5)
	{
		std::cout << ++n << " ";
	}
	std::cout<<std::endl;
}

// P.J.vector`Storage allocation mechanism`【内存分配机制】
void using2()
{
	size_t sz;
	std::vector<int> v;
	sz = v.capacity();
	std::cout << "making v grow:\n";
	for (int i = 0; i < 100; ++i)
	{
		v.push_back(i);
		if (sz != v.capacity())
		{
			sz = v.capacity();
			std::cout << "capacity changed: " << sz << '\n';
		}
	}
}

// `insert`【插入】 and `erase`【删除】 
// https://legacy.cplusplus.com/reference/vector/vector/insert/
// https://legacy.cplusplus.com/reference/vector/vector/erase/
// https://legacy.cplusplus.com/reference/algorithm/find/
void using3()
{
	// There are three modes of `insert`:
	// Insert value before the specified position
	// Insert n values before the specified position
	// Inserts a `segment`【一段】 of the iterator `interval`【区间】 before the specified position

	std::vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);

	for (auto n : v)
	{
		std::cout << n << " ";
	}
	std::cout << std::endl;

	// Finding elements in a container `through`【通过】 an `algorithm`【算法】 library
	std::vector<int>::iterator it = find(v.begin(), v.end(), 3);
	v.insert(it, 25);
	

	for (auto n : v)
	{
		std::cout << n << " ";
	}
	std::cout << std::endl;

	it = find(v.begin(), v.end(), 3);
	v.erase(it);

	for (auto n : v)
	{
		std::cout << n << " ";
	}
	std::cout << std::endl;
}