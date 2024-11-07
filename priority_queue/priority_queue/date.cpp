#include<iostream>
#include<queue>
#include"priority_queue.h"

using namespace std;

class Date
{
public:
	Date(int year = 1900, int month = 1, int day = 1)
		: _year(year)
		, _month(month)
		, _day(day)
	{}
	bool operator<(const Date& d)const
	{
		return (_year < d._year) ||
			(_year == d._year && _month < d._month) ||
			(_year == d._year && _month == d._month && _day < d._day);
	}
	bool operator>(const Date& d)const
	{
		return (_year > d._year) ||
			(_year == d._year && _month > d._month) ||
			(_year == d._year && _month == d._month && _day > d._day);
	}

	friend ostream& operator<<(ostream& _cout, const Date& d);

private:
	int _year;
	int _month;
	int _day;
};

ostream& operator<<(ostream& _cout, const Date& d)
{
	_cout << d._year << "-" << d._month << "-" << d._day;
	return _cout;
}


void test1()
{
	vector<Date> v;
	v.push_back(Date(2018, 10, 28));
	v.push_back(Date(2018, 10, 29));
	v.push_back(Date(2018, 10, 30));
	wind::priority_queue<Date> q(v.begin(), v.end());
	cout << q.top() << endl;
}

struct pDate_less
{
	bool operator()(const Date* p1, const Date* p2)
	{
		return *p1 < *p2;
	}
};

struct pDate_greater
{
	bool operator()(const Date* p1, const Date* p2)
	{
		return *p1 > *p2;
	}
};

void test2()
{
	wind::priority_queue<Date*, vector<Date*>, pDate_greater> q1;
	q1.push(new Date(2018, 10, 29));
	q1.push(new Date(2018, 10, 28));
	q1.push(new Date(2018, 10, 30));
	cout << *q1.top() << endl;
}

void TestPriorityQueue()
{
	// 大堆，需要用户在自定义类型中提供<的重载
	priority_queue<Date> q1;
	q1.push(Date(2018, 10, 29));
	q1.push(Date(2018, 10, 28));
	q1.push(Date(2018, 10, 30));
	cout << q1.top() << endl;
	// 如果要创建小堆，需要用户提供>的重载
	priority_queue<Date, vector<Date>, greater<Date>> q2;
	q2.push(Date(2018, 10, 29));
	q2.push(Date(2018, 10, 28));
	q2.push(Date(2018, 10, 30));
	cout << q2.top() << endl;
}

int main()
{
	test1();
	return 0;
}