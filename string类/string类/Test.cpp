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

void test4()
{
	std::string s;
	s.reserve(100);
	std::cout << "initial capacity:";
	size_t old = s.capacity();
	std::cout << old << std::endl;
	int cir = 0;
	for (; cir < 100; cir++)
	{
		s.push_back('c');
		size_t n = s.capacity();
		if (n != old)
		{
			std::cout << "trigger expansion,The new capacity is:";
			std::cout << n << std::endl;
			old = n;
		}
	}
	s.reserve(10);
	std::cout << "Current capacity:" << s.capacity() << std::endl;
}

void test5()
{
	std::string s("hello world");
	std::cout << s << std::endl;
	std::cout << "Current capacity:" << s.capacity() << std::endl;
	std::cout << "Current size:" << s.size() << std::endl;
	s.resize(5);
	std::cout << s << std::endl;
	std::cout << "Current capacity:" << s.capacity() << std::endl;
	std::cout << "Current size:" << s.size() << std::endl;
}

void test6()
{
	std::string s("hello world");
	s.insert(0, 1, 'x');
	std::cout << s << std::endl;
	s.insert(s.begin(), 'x');
	std::cout << s << std::endl;
}

void test7()
{
	std::string s1("hello world");
	// 把空格【下标为5】的那一个字符替换成%?
	s1.replace(5, 1, "%?");
	std::cout << s1 << std::endl;
	// 此时很明显有数据挪动
	// 如果第二个参数就是第三个参数的有效字符个数
	// 那就只是单纯平替，没有挪动数据
	std::string s2("hello world");
	s2.replace(5, 2, "%x");
	std::cout << s2 << std::endl;
}


// 替换空格
std::string& test8(std::string& s, const char* c)
{
	std::string r;
	r.reserve(s.size());
	for (auto ch : s)
	{
		if (ch != ' ')
		{
			r += ch;
		}
		else
		{
			r += c;
		}
	}
	swap(r, s);
	return s;
}

void test8_1()
{
	std::string s("The quick brown fox jumps over a lazy dog.");
	auto r = test8(s, "%#@");
	std::cout << r << std::endl;
	std::cout << s << std::endl;
}

void test9()
{
	std::string s1("hello world");
	std::string s2("hello linux");
	std::cout << &s1 << std::endl;
	std::cout << &s2 << std::endl;
	printf("%p\n", s1.c_str());
	printf("%p\n", s2.c_str());
	std::cout << "================" << std::endl;
	s1.swap(s2);
	std::cout << &s1 << std::endl;
	std::cout << &s2 << std::endl;
	printf("%p\n", s1.c_str());
	printf("%p\n", s2.c_str());
}

void test10()
{
	std::string s("wind_backup.tar.gz");
	size_t i = s.rfind('.');
	auto j = s.substr(i);
	std::cout << j << std::endl;
}

void test11()
{
	std::string s("https://cplusplus.com/reference/string/string/find/");
	size_t n = s.find(':');
	if (n != std::string::npos)
	{
		auto i = s.substr(0, n);
		std::cout << i << std::endl;
	}
	else
	{
		std::cout << "URL error!" << std::endl;
	}
	// 第二个参数规定了查找的起始位置，缺省值为0
	size_t m = s.find('/', n + 3);
	if (m != std::string::npos)
	{
		auto j = s.substr(n + 3, m - (n + 3));
		std::cout << j << std::endl;
	}
	else
	{
		std::cout << "URL error!" << std::endl;
	}
	n = s.find('/', m + 1);
	if (n != std::string::npos)
	{
		auto k = s.substr(m + 1);
		std::cout << k << std::endl;
	}
	else
	{
		std::cout << "URL error!" << std::endl;
	}
}

#include <cstddef>  
void test12()
{
	
	std::string str("Please, replace the vowels in this sentence by asterisks.");
	std::size_t found = str.find_first_not_of("aeiou");
	while (found != std::string::npos)
	{
		str[found] = '*';
		found = str.find_first_not_of("aeiou", found + 1);
	}
	std::cout << str << '\n';
}

void test13()
{
	std::string s1, s2;
	std::cin >> s1 >> s2;
	std::cout << s1 << std::endl;
	std::cout << s2 << std::endl;
}

void test14()
{
	std::string s1, s2;
	getline(std::cin, s1);
	getline(std::cin, s2, '!');
	std::cout << s1 << std::endl;
	std::cout << s2 << std::endl;
}

int main()
{
	test9();
	return 0;
}