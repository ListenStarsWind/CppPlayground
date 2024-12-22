#include"RBTree.h"
#include<iostream>

using namespace std;

void test1()
{
	//vector<int> v = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };
	vector<int> v;
	srand(time(nullptr));
	for (size_t i = 0; i < 100000; ++i)
	{
		v.push_back(rand());
	}

	wind::RBTree<int, int> ts;
	for (const auto& i : v)
	{
		ts.Insert(make_pair(i, 0));
	}

	/*auto vr = ts.InOrder();
	for (const auto& e : vr)
	{
		cout << e.first << " ";
	}
	cout << endl;*/

	if (ts.IsBalance())
	{
		cout << "true" << endl;
	}
	else
	{
		cout << "false" << endl;
	}
}

int main()
{
	wind::RBTree<string, string> ts;
	ts.Insert(std::make_pair("apple", "Æ»¹û"));
	ts.Insert(std::make_pair("banana", "Ïã½¶"));
	ts.Insert(std::make_pair("grape", "ÆÏÌÑ"));
	ts.Insert(std::make_pair("orange", "³È×Ó"));
	ts.Insert(std::make_pair("kiwi", "â¨ºïÌÒ"));
	ts.Insert(std::make_pair("pear", "Àæ"));
	ts.Insert(std::make_pair("pineapple", "²¤ÂÜ"));
	ts.Insert(std::make_pair("peach", "ÌÒ×Ó"));
	if (ts.IsBalance())
	{
		cout << "true" << endl;
	}
	else
	{
		cout << "false" << endl;
	}

	auto v = ts.InOrder();
	for (auto e : v)
	{
		cout << e.first << "->" << e.second << endl;
	}
	return 0;
}