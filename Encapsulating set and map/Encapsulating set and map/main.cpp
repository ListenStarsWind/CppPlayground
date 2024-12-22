#include"set.h"
#include"map.h"
#include<set>
#include<map>

using namespace std;

void test_set()
{
	wind::set<int> s;
	s.insert(1);
	s.insert(2);
	s.insert(3);
	s.insert(4);
	s.insert(5);

	for (auto& e : s)
	{
		cout << e << " ";
	}
	cout << endl;

	auto it = s.rbegin();
	while (it != s.rend())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;

}

void test_map()
{
	std::map<std::string, std::string> m;
	m.insert(std::make_pair("apple", "Æ»¹û"));
	m.insert(std::make_pair("banana", "Ïã½¶"));
	m.insert(std::make_pair("grape", "ÆÏÌÑ"));
	m.insert(std::make_pair("orange", "³È×Ó"));
	m.insert(std::make_pair("kiwi", "â¨ºïÌÒ"));
	m.insert(std::make_pair("pear", "Àæ"));
	m.insert(std::make_pair("pineapple", "²¤ÂÜ"));
	m.insert(std::make_pair("peach", "ÌÒ×Ó"));

	auto it = m.begin();
	while (it != m.end())
	{
		cout << it->first << "->" << it->second << endl;
		++it;
	}
	cout << endl;

}

void testSubscriptOperator()
{
	string arr[] = { "Æ»¹û", "Î÷¹Ï", "Æ»¹û", "Î÷¹Ï", "Æ»¹û", "Æ»¹û", "Î÷¹Ï",
		"Æ»¹û", "Ïã½¶", "Æ»¹û", "Ïã½¶" };
	wind::map<string, int> countMap;
	for (const auto& str : arr)
	{
		countMap[str]++;
	}

	for (auto& e : countMap)
	{
		cout << e.first << "::" << e.second << endl;
	}
	cout << endl;

	auto it = countMap.rbegin();
	while (it != countMap.rend())
	{
		cout << it->first << "::" << it->second << endl;
		++it;
	}
	cout << endl;
}

int main()
{
	test_set();
	testSubscriptOperator();
	return 0;
}