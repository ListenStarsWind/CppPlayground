#include<string>
#include<iostream>

void test1()
{
	// 以无参的形式实例化
	std::string s1;
	// 以常量字符串的形式实例化
	std::string s2("string");

	// 容量不够会自己扩容

	// 支持流插入
	std::cout << s2 << std::endl;
	// 支持流提取
	std::cin >> s1;
	std::cout << s1 << std::endl;
}

void test2()
{
	std::string s1("class");
	std::string s2(" string");
	std::string s3 = s1 + s2;
	std::cout << s3 << std::endl;
	std::cout << "std::" + s3 << std::endl;
}

void test3()
{
	std::string s1("abcd");
	std::string s2("-----------------");

	// 使用`[]`重载遍历字符串
	int i = 0;
	for (; i < s1.size(); i++)
	{
		++s1[i];
	}
	std::cout << s1 << std::endl;
	// 注意，`[]`没有范围检查，可能会越界访问
	// 可以用成员函数`at`替代
	for (i = 0; i < s1.size(); i++)
	{
		--s1.at(i);
	}

	std::cout << s2 << std::endl;
	// 使用迭代器遍历字符串
	// 迭代器是对容器中元素遍历的通用方案
	std::string::iterator it = s1.begin();
	while (it != s1.end())
	{
		std::cout<<*it;
		++it;
	}
	// begin返回指向第一个有效字符的迭代器
	// end返回指向最后一个有效字符的下一字符的迭代器
	// s1存储的是"abcd\0",一共五个字符，最后一个有效字符是'd'
	// 即，end返回的迭代器指向'\0'
	// 迭代器行为很像指针，甚至它本身就是指针
	std::cout << std::endl;
	// 注意，循环条件不要用`<`比较
	// 因为迭代器是通用的，而某些容器中的成员没有先后概念
	// 比如树状结构，环装结构，但对于这些容器成员来说，是否等于的
	// 概念仍是确定的
	std::cout << s2 << std::endl;
	// 除此之外，还有反向迭代器
	// rbegin返回一个反向的迭代器，具体指向字符串的最后一个有效字符
	// rend返回一个指向第一个有效字符前一字符的迭代器
	// “第一个有效字符前一字符”只是一个概念上的位置，实际并不存在
	std::string::reverse_iterator rit = s1.rbegin();
	while (rit != s1.rend())
	{
		std::cout << *rit;
		++rit;
	}
	std::cout << std::endl << s2 << std::endl;
	// 迭代器的++都是重载过的，表示方向，朝终止位`end`迭代
	// 对反向迭代器仍是如此，++表示朝终止位`rend`迭代
	// 迭代器也有--重载，不过用的人不多

	// 范围for其实是对迭代器的进一步封装
	// 由于迭代器的类型挺长的，所以直接用auto占位
	for (auto ch : s1)
	{
		std::cout << ch;
	}
	std::cout << std::endl;
	// 修改用引用
	for (auto& ch : s1)
	{
		++ch;
	}
	std::cout << s1 << std::endl;
}

int main()
{
	test3();
	return 0;
}