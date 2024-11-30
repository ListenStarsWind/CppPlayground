#include"BSTree.h"
#include<iostream>

using namespace std;

void test1()
{
	wind::K_model::BSTree<int> bt;
	int a[] = { 8, 3, 1, 10, 6, 4, 7, 14, 13 };
	for (auto e : a)
		bt.InsertR(e);
	bt.Erase(1);
	auto v = bt.InOrder();
	for (auto e : v)
		cout << e << " ";
	cout << endl;
}

void test2()
{
	wind::KV_model::BSTree<string, string> Translator;
	Translator.Insert("sort", "����");
	Translator.Insert("search", "����");
	Translator.Insert("filter", "����");
	Translator.Insert("merge", "�ϲ�");
	Translator.Insert("map", "ӳ��");
	Translator.Insert("reduce", "��Լ");
	Translator.Insert("iterator", "������");
	Translator.Insert("stack", "ջ");
	Translator.Insert("queue", "����");
	Translator.Insert("binary tree", "������");

	string str;
	while (cin >> str)
	{
		auto target = Translator.Find(str);
		if (target)
		{
			cout << target->_value << endl;
		}
		else
		{
			cout << "nonexistent keyword" << endl;
		}
	}
}

void test3()
{
	// ͳ��ˮ�����ֵĴ���
	string arr[] = { "ƻ��", "����", "ƻ��", "����", "ƻ��", "ƻ��", "����",
	"ƻ��", "�㽶", "ƻ��", "�㽶" };
	wind::KV_model::BSTree<string, int> countTree;
	for (const auto& str : arr)
	{
		auto ret = countTree.Find(str);
		if (ret == nullptr)
		{
			countTree.Insert(str, 1);
		}
		else
		{
			ret->_value++;
		}
	}
	auto ret = countTree.InOrder();
	for (const auto& e : ret)
	{
		cout << e._key << "::" << e._value << endl;
	}
}

//int main()
//{
//	test3();
//	return 0;
//}