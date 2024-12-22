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
	m.insert(std::make_pair("apple", "ƻ��"));
	m.insert(std::make_pair("banana", "�㽶"));
	m.insert(std::make_pair("grape", "����"));
	m.insert(std::make_pair("orange", "����"));
	m.insert(std::make_pair("kiwi", "⨺���"));
	m.insert(std::make_pair("pear", "��"));
	m.insert(std::make_pair("pineapple", "����"));
	m.insert(std::make_pair("peach", "����"));

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
	string arr[] = { "ƻ��", "����", "ƻ��", "����", "ƻ��", "ƻ��", "����",
		"ƻ��", "�㽶", "ƻ��", "�㽶" };
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