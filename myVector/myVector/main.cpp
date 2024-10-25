#include<iostream>
#include<string>
#include"myVector.h"
#include"using.h"

void realization1() {
	wind::vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	for (auto data : v)
	{
		std::cout << data << " ";
	}
	std::cout << std::endl;
}

void realization2()
{
	wind::vector<int> v;
	size_t sz = v.capacity();
	std::cout << "making v grow:\n";
	for (int i = 0; i < 100; i++)
	{
		v.push_back(i);
		if (sz != v.capacity())
		{
			sz = v.capacity();
			std::cout << "capacity changed: " << sz << '\n';
		}
	}
	for (auto data : v)
	{
		std::cout << data << " ";
	}
	std::cout << std::endl;
}

void realization3()
{
	wind::vector<std::string> str_arry;
	auto& v = str_arry;
	v.push_back("1111");
	v.push_back("11111111111111111111111111");
	v.push_back("xxxxxxxxxxxxxxxxxxxxxxxxxx");
	v.push_back("11111111111111111111111111");
	wind::vector<std::string>::iterator it = v.end();
	v.insert(it, "hello word");
	for (auto m : v)
	{
		std::cout<<m<<std::endl;
	}
}

// ��ʾ�������ⲿʧЧ
void realization4()
{
	std::vector<int> v;
	//wind::vector<int> v;
	v.push_back(0);
	v.push_back(1);
	v.push_back(2);
	v.push_back(2);
	v.push_back(3);
	v.push_back(3);
	//wind::vector<int>::iterator it = v.begin();
	std::vector<int>::iterator it = v.begin();
	// Ŀ�꣺ɾ������ż��Ԫ��
	while (it != v.end())
	{
		if (*it % 2 == 0)
		{
			v.erase(it);
		}
		++it;
	}
	for (auto val : v)
	{
		std::cout << val << " ";
	}
	std::cout << std::endl;
	// ��������1  2  3  3
	// it -> 0    0 1 2 2 3 3   ɾ�� ������ָ�����ݷ����ı� it -> 1  �ⲿѭ���ټ�һ it -> 2
	// it -> 2    1 2 2 3 3     ɾ�� ������ָ�����ݷ����ı� it -> 2  �ⲿѭ���ټ�һ it -> 3
	// it -> 3    1 2 3 3       �ⲿѭ����һ it -> 3
	// it -> 3    1 2 3 3       �ⲿѭ����һ it -> 3
	// ��������� erase���з���ֵ�ģ��������������ⲿ������
}

void realization5()
{
	//std::vector<int> v;
	wind::vector<int> v;
	v.push_back(1);
	v.push_back(1);
	v.push_back(1);
	v.push_back(2);
	wind::vector<int>::iterator it = v.begin();
	//std::vector<int>::iterator it = v.begin();
	// Ŀ�꣺ɾ������ż��Ԫ��
	while (it != v.end())
	{
		if (*it % 2 == 0)
		{
			v.erase(it);
		}
		++it;
	}
	for (auto val : v)
	{
		std::cout << val << " ";
	}
	std::cout << std::endl;
	// ���������assert����
	// ���һ��Ԫ�ر�ɾ��֮�󣬵������Ѿ�ָ��Ƿ�����
	// ��ֵΪ���ֵ
	// ��Ϊż��ʱ���ٴν���erase��������Χ��龯��
}

// ���������ɾ��֮��Ե�������������
void realization6()
{
	//std::vector<int> v;
	wind::vector<int> v;
	v.push_back(0);
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(4);
	wind::vector<int>::iterator it = v.begin();
	//std::vector<int>::iterator it = v.begin();
	// Ŀ�꣺ɾ������ż��Ԫ��
	while (it != v.end())
	{
		if (*it % 2 == 0)
		{
			it = v.erase(it);
		}
		else
		{
			++it;
		}
	}
	for (auto val : v)
	{
		std::cout << val << " ";
	}
	std::cout << std::endl;
}


// �ո�ʹ�õ��������Լ�ʵ�ֵ�vector
// ���ڻ���VS�Լ��Ŀ�һ��
// ���Ƿ��ִ�ʱ4 5�����ж�����
// VS�Ե�����������ǿ�Ƽ��
// ֻҪ���־���erase�ĵ�����
// û�б�������ֱ�Ӳ���������++���ͱ���
// ���ῴ���ܲ�����ʾinsert������Ч��

// g++���Ǹ�������ʵ�ֵ��߼�
// �Ͼ����ǵ�ʵ�־��Ǵ�����ԭ�뿪ʼ��


// ����˵һ�£�
// ����д��ģ���г�Ա�����Ĳ����ͷ���ֵ����
// ����ֱ����vector
// ��������ɲ���������
// ֮ǰ˵��vector��ģ��
// ���������ͣ�ʵ�������ģ��
// �������ͣ�����ģ������
// ������Ĭ��vector����vector<T>
// ����ģ�������дvector
void realization7()
{
	wind::vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);

	for (auto val : v)
	{
		std::cout << val << " ";
	}
	std::cout << std::endl;

	wind::vector<int> val;
	val.push_back(6);
	val.push_back(7);
	val.push_back(8);
	val.push_back(9);
	val.push_back(10);

	v = val;

	for (auto e : v)
	{
		std::cout << e << " ";
	}
	std::cout << std::endl;
}

void realization8()
{
	wind::vector<int> v1;
	v1.push_back(1);
	v1.push_back(2);
	v1.push_back(3);
	v1.push_back(4);
	v1.push_back(5);

	wind::vector<int> v2(v1.begin(), v1.end());

	for (auto e : v2)
	{
		std::cout << e << " ";
	}
	std::cout << std::endl;

	std::string s("hello world");
	wind::vector<int> v3(s.begin(), s.end());

	for (auto e : v3)
	{
		std::cout << e << " ";
	}
	std::cout << std::endl;
}

void realization9()
{
	//wind::vector<std::string> v(10, "xxxxxxxxx");

	// 10 �� 0������Ϊint,������ͬ������
	// ���������乹�����ΪInputIterator, InputIterator
	// ����ȫ��ͬ������
	// ��n��val���죬����Ϊsize_t , T
	// ���������n��val���죬Ҫ��������int����Ϊsize_t
	// ���������乹�첻������������ֱ���ã����Ի���
	// ���������乹��
	wind::vector<int> v(10, 0);

	for (auto e : v)
	{
		std::cout << e << " ";
	}
	std::cout << std::endl;
}

int main()
{
	realization9();
	return 0;
}