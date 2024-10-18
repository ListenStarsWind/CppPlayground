#include"string.h"
#include<string>
#include<iostream>

int main()
{
	std::string s;
	// 输入"hello string"
	std::cin >> s;
	// 只会提取"hello"
	// "string"还留在缓冲区
	std::cout << s;
	return 0;
}