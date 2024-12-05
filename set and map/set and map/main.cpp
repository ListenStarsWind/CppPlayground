#include<iostream>
#include<string>
#include<set>
#include<map>

using namespace std;

namespace set_using
{
	void test1()
	{
		set<int> s;

		pair<set<int>::iterator, bool> ret = s.insert(6);
		cout << ret.second << endl;

		if (s.count(6))
			cout << "6 in the container." << endl;
		else
			cout << "6 is not in the container." << endl;

		s.insert(6);
		s.insert(5);
		s.insert(2);
		s.insert(1);
		s.insert(1);
		s.insert(3);
		s.insert(2);
		s.insert(6);

		ret = s.insert(6);
		cout << ret.second << endl;

		set<int>::iterator fd = s.find(6);
		if (fd != s.end())
			s.erase(fd);

		if (s.count(6))
			cout << "6 in the container." << endl;
		else
			cout << "6 is not in the container." << endl;
		
		set<int>::iterator it = s.begin();
		while (it != s.end())
		{
			cout << *it << " ";
			++it;
		}
		cout << endl;

		s.erase(1);
		for (const auto& e : s)
			cout << e << " ";
		cout << endl;
	}

	void test2()
	{
		std::set<int> myset;
		std::set<int>::iterator itlow, itup;

		for (int i = 1; i < 10; i++) myset.insert(i * 10); // 10 20 30 40 50 60 70 80 90

		itlow = myset.lower_bound(25);                //            ^
		itup = myset.upper_bound(65);                 //                         ^

		myset.erase(itlow, itup);                     // 10 20 70 80 90

		for (const auto& e : myset)
			cout << e << " ";
		cout << endl;
	}

	void test3()
	{
		std::set<int> myset;

		for (int i = 1; i <= 5; i++) myset.insert(i * 10);   // myset: 10 20 30 40 50

		std::pair<std::set<int>::const_iterator, std::set<int>::const_iterator> ret;
		ret = myset.equal_range(35);

		std::cout << "the lower bound points to: " << *ret.first << '\n';
		std::cout << "the upper bound points to: " << *ret.second << '\n';
	}
}

namespace multiset_using
{
	void test1()
	{
		multiset<int> s;

		s.insert(6);
		s.insert(5);
		s.insert(2);
		s.insert(1);
		s.insert(1);
		s.insert(3);
		s.insert(2);
		s.insert(6);

		multiset<int>::iterator it = s.find(2);
		while (it != s.end())
		{
			cout << *it << " ";
			++it;
		}
		cout << endl;
	}

	typedef std::multiset<int>::iterator It;
	void test2()
	{
		int myints[] = { 77,30,16,2,30,30 };
		std::multiset<int> mymultiset(myints, myints + 6);  // 2 16 30 30 30 77

		std::pair<It, It> ret = mymultiset.equal_range(30); //      ^        ^

		size_t count = mymultiset.erase(30);
		cout << count << endl;

		for (const auto& e : mymultiset)
			cout << e << " ";
		cout << endl;
	}
}

namespace map_using
{
	void test1()
	{
		map<string, string> dict;
		dict.insert(pair<string, string>("sort", "排序"));
		dict.insert(pair<const char*, string>("insert", "插入"));
		dict.insert(pair<const char*, const char*>("left", "剩余"));
		dict.insert(make_pair("right", "正确的"));

		dict["map"];           // 插入
		dict["map"] = "映射";  // 修改key映射的value

		map<string, string>::iterator it = dict.begin();
		while (it != dict.end())
		{
			cout << it->first << "::" << it->second << endl;
			++it;
		}
		cout << endl;
	}

	void test2()
	{
		// 统计水果出现的次数
		string arr[] = { "苹果", "西瓜", "苹果", "西瓜", "苹果", "苹果", "西瓜",
		"苹果", "香蕉", "苹果", "香蕉" };
		map<string, int> countMap;
		for (const auto& str : arr)
		{
			/*auto ret = countMap.find(str);
			if (ret == countMap.end())
				countMap.insert(make_pair(str, 1));
			else
				ret->second++;*/
			countMap[str]++;
		}

		for (const auto& e : countMap)
			cout << e.first << "::" << e.second << endl;
		cout << endl;
	}
}

class task
{
	typedef void (*func) ();
public:
	void operator()() { _func(); }
private:
	func _func = map_using::test1;
};

int main()
{
	task t;
	t();
	return 0;
}