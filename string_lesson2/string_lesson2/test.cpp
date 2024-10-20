#include"string.h"
#include<string>
#include<iostream>

void test1()
{
	wind::string s;
	// 输入"hello string"
	std::cin >> s;
	// 只会提取"hello"
	// "string"还留在缓冲区
	std::cout << s;
}

void test2()
{
	wind::string s;
	s.get('!');
	std::cout << s;
}

void test3()
{
	wind::string s("hello world");
	std::cout << s.find("world");
}

void test4()
{
	wind::string s("hello world");
	std::cout << s.substr(6).c_str();
}

void test5()
{
	std::cout <<"std::string->" << sizeof(std::string)<<std::endl;
	std::cout <<"wind::string->" << sizeof(wind::string)<<std::endl;
}

void test6()
{
	std::string s("abcdefghijklmno");
	std::cout << s.size() << std::endl;
	std::cout << s.capacity() << std::endl;
	s += 'p';
	std::cout << s.size() << std::endl;
	std::cout << s.capacity() << std::endl;
}

int main()
{
	test6();
	return 0;
}