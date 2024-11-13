//template<class T, size_t N>
//class stack
//{
//public:
//	T _a[N];
//};
//
//
//#include<iostream>
//
//using namespace std;
//
//template<class T1, class T2>
//class Date
//{
//public:
//	Date() { cout << "T1 and T2" << endl; };
//private:
//	T1 _a;
//	T2 _b;
//};
//
//template<>
//class Date<int, double>
//{
//public:
//	Date() { cout << "int and double" << endl; };
//};
//
//template<class T>
//class Date<T, double>
//{
//public:
//	Date() { cout << "T and double" << endl; };
//};
//
//
//int main()
//{
//	Date<double, int>();
//	Date<int, double>();
//	Date<double, double>();
//	return 0;
//}

#include<iostream>
#include<queue>

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

template<class T>
bool Less(const T& left, const T& right)
{
	return left < right;
}

bool Less(Date* & left, Date*  & right)
{
	return *left < *right;
}

void test3()
{
	Date* p1 = new Date(2024, 11, 10);
	Date* p2 = new Date(2024, 11, 9);
	std::cout << Less(p1, p2) << std::endl;
}

int main()
{
	test3();
	return 0;
}

//template<>
//class greater<Date*>
//{
//public:
//	bool operator()(const Date* p1, const Date* p2)
//	{
//		return *p1 > *p2;
//	}
//};
//
//template<class T>
//class greater<T*>
//{
//public:
//	bool operator()(const T* p1, const T* p2)
//	{
//		return *p1 > *p2;
//	}
//};
//
//void test2()
//{
//	priority_queue<Date*, vector<Date*>, greater<Date*>> q1;
//	q1.push(new Date(2018, 10, 29));
//	q1.push(new Date(2018, 10, 28));
//	q1.push(new Date(2018, 10, 30));
//	cout << *q1.top() << endl;
//
//	priority_queue<int*, vector<int*>, greater<int*>> q2;
//	q2.push(new int(5));
//	q2.push(new int(2));
//	q2.push(new int(7));
//	cout << *q2.top() << endl;
//
//}
//
