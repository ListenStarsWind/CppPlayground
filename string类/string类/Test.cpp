#include<string>
#include<iostream>

void test1()
{
	// ���޲ε���ʽʵ����
	std::string s1;
	// �Գ����ַ�������ʽʵ����
	std::string s2("string");

	// �����������Լ�����

	// ֧��������
	std::cout << s2 << std::endl;
	// ֧������ȡ
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

	// ʹ��`[]`���ر����ַ���
	int i = 0;
	for (; i < s1.size(); i++)
	{
		++s1[i];
	}
	std::cout << s1 << std::endl;
	// ע�⣬`[]`û�з�Χ��飬���ܻ�Խ�����
	// �����ó�Ա����`at`���
	for (i = 0; i < s1.size(); i++)
	{
		--s1.at(i);
	}

	std::cout << s2 << std::endl;
	// ʹ�õ����������ַ���
	// �������Ƕ�������Ԫ�ر�����ͨ�÷���
	std::string::iterator it = s1.begin();
	while (it != s1.end())
	{
		std::cout<<*it;
		++it;
	}
	// begin����ָ���һ����Ч�ַ��ĵ�����
	// end����ָ�����һ����Ч�ַ�����һ�ַ��ĵ�����
	// s1�洢����"abcd\0",һ������ַ������һ����Ч�ַ���'d'
	// ����end���صĵ�����ָ��'\0'
	// ��������Ϊ����ָ�룬�������������ָ��
	std::cout << std::endl;
	// ע�⣬ѭ��������Ҫ��`<`�Ƚ�
	// ��Ϊ��������ͨ�õģ���ĳЩ�����еĳ�Աû���Ⱥ����
	// ������״�ṹ����װ�ṹ����������Щ������Ա��˵���Ƿ���ڵ�
	// ��������ȷ����
	std::cout << s2 << std::endl;
	// ����֮�⣬���з��������
	// rbegin����һ������ĵ�����������ָ���ַ��������һ����Ч�ַ�
	// rend����һ��ָ���һ����Ч�ַ�ǰһ�ַ��ĵ�����
	// ����һ����Ч�ַ�ǰһ�ַ���ֻ��һ�������ϵ�λ�ã�ʵ�ʲ�������
	std::string::reverse_iterator rit = s1.rbegin();
	while (rit != s1.rend())
	{
		std::cout << *rit;
		++rit;
	}
	std::cout << std::endl << s2 << std::endl;
	// ��������++�������ع��ģ���ʾ���򣬳���ֹλ`end`����
	// �Է��������������ˣ�++��ʾ����ֹλ`rend`����
	// ������Ҳ��--���أ������õ��˲���

	// ��Χfor��ʵ�ǶԵ������Ľ�һ����װ
	// ���ڵ�����������ͦ���ģ�����ֱ����autoռλ
	for (auto ch : s1)
	{
		std::cout << ch;
	}
	std::cout << std::endl;
	// �޸�������
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
	// �ѿո��±�Ϊ5������һ���ַ��滻��%?
	s1.replace(5, 1, "%?");
	std::cout << s1 << std::endl;
	// ��ʱ������������Ų��
	// ����ڶ����������ǵ�������������Ч�ַ�����
	// �Ǿ�ֻ�ǵ���ƽ�棬û��Ų������
	std::string s2("hello world");
	s2.replace(5, 2, "%x");
	std::cout << s2 << std::endl;
}


// �滻�ո�
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
	// �ڶ��������涨�˲��ҵ���ʼλ�ã�ȱʡֵΪ0
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