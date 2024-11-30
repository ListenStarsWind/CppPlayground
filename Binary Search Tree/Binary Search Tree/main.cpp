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
	Translator.Insert("sort", "排序");
	Translator.Insert("search", "搜索");
	Translator.Insert("filter", "过滤");
	Translator.Insert("merge", "合并");
	Translator.Insert("map", "映射");
	Translator.Insert("reduce", "归约");
	Translator.Insert("iterator", "迭代器");
	Translator.Insert("stack", "栈");
	Translator.Insert("queue", "队列");
	Translator.Insert("binary tree", "二叉树");

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
	// 统计水果出现的次数
	string arr[] = { "苹果", "西瓜", "苹果", "西瓜", "苹果", "苹果", "西瓜",
	"苹果", "香蕉", "苹果", "香蕉" };
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