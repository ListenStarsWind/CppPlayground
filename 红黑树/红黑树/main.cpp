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
	ts.Insert(std::make_pair("apple", "ƻ��"));
	ts.Insert(std::make_pair("banana", "�㽶"));
	ts.Insert(std::make_pair("grape", "����"));
	ts.Insert(std::make_pair("orange", "����"));
	ts.Insert(std::make_pair("kiwi", "⨺���"));
	ts.Insert(std::make_pair("pear", "��"));
	ts.Insert(std::make_pair("pineapple", "����"));
	ts.Insert(std::make_pair("peach", "����"));
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