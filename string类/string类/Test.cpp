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

int main()
{
	test3();
	return 0;
}