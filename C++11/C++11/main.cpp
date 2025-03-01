#include<iostream>
#include<cstdio>
#include<vector>
#include<list>
#include<map>
#include"myVector.h"
#include"string.h"

using namespace std;


//// C++98中对列表初始化的应用
//struct Point
//{
//	int _x;
//	int _y;
//};
//
//int main()
//{
//	int array1[] = { 1, 2, 3, 4, 5 };
//	int array2[5] = { 0 };
//	Point p = { 1, 2 };
//	return 0;
//}

//// C++11  列表初始化
//int main()
//{
//	int i = 0;
//	int j = { 0 };					// 在范围上, C++中的所有原生类型都可以使用列表初始化
//	int array[]{ 1, 2, 3, 4, 5 };	// 在形式上, 可以省略"="
//	int* pa = new int[4] { 0 };     // 列表初始化也可以适用于new表达式中
//	return 0;
//}

//class Date
//{
//public:
//	Date(int year, int month, int day)
//		:_year(year)
//		, _month(month)
//		, _day(day)
//	{
//		cout << "Date(int year, int month, int day)" << endl;
//	}
//private:
//	int _year;
//	int _month;
//	int _day; 
//};
//
//int main()
//{
//	// 直接使用构造函数构造
//	Date d1(2025, 1, 15);
//
//	// 类型转换
//	Date d2 = {2024, 2, 10};
//	Date d3{2026, 7, 18};
//
//	// 由于"{}"生成的是临时变量, 具有常属性, 所以必须使用常引用
//	const Date& d4 = {2010, 6, 24};
//	// 由于是连续的构造, 拷贝构造, 构造, 所以可能被编译器优化为直接构造
//
//	return 0;
//}

//class Date
//{
//public:
//	Date(int year, int month, int day)
//		:_year(year)
//		, _month(month)
//		, _day(day)
//	{
//		printf("Date(%d, %d, %d)\n", year, month, day);
//	}
//private:
//	int _year;
//	int _month;
//	int _day;
//};
//
//int main()
//{
//	// C++98允许的初始化方式
//	Date d1(2025, 1, 15);
//	Date d2 = { 2024, 2, 10 };
//	Date d3{ 2026, 7, 18 };
//	Date* p1 = new Date[3]{d1, d2, d3};
//
//	// 当d1,d2,d3仅作为数组的成员, 而不发挥其它作用时, C++98的写法就略显繁琐
//	// C++11的写法
//	Date* p2 = new Date[3]{ {2030, 1, 15},{2034, 2, 10},{2036, 7, 18} };
//
//	return 0;
//}

//int main()
//{
//	vector<int> v = {1, 2, 3, 4, 5, 6};
//	list<int> s = {2, 4, 6, 8, 10};
//	return 0;
//}

//class Date
//{
//public:
//	Date(int year, int month, int day)
//		:_year(year)
//		, _month(month)
//		, _day(day)
//	{
//		printf("Date(%d, %d, %d)\n", year, month, day);
//	}
//private:
//	int _year;
//	int _month;
//	int _day;
//};
//
//int main()
//{
//	auto i = { 1, 2, 3, 4, 5, 6 };
//	auto j = {"abcd", "cdab"};
//	cout << typeid(i).name() << endl;
//	cout << typeid(j).name() << endl;
//	auto it = i.begin();
//	while (it != i.end())
//	{
//		cout << *it << " ";
//		++it;
//	}
//	cout << endl;
//	return 0;
//}

//int main()
//{
//	wind::vector<int> v1 = { 1, 2, 3, 4, 5, 6 };
//	wind::vector<string> v2{ "abcd", "cdab" };
//
//	for (auto e : v1)
//	{
//		cout << e << " ";
//	}
//	cout << endl;
//
//	for (auto e : v2)
//	{
//		cout << e << endl;
//	}
//	cout << endl;
//
//	return 0;
//}

//int main()
//{
//	map<string, string> dict{ {"Yorktown", "约克城"}, {"enterprise", "企业号"}, {"Ford", "福特"}};
//	for (const auto& e : dict)
//	{
//		cout << e.first << "->" << e.second << endl;
//	}
//	cout << endl;
//	return 0;
//}

//// 伪代码
//int main()
//{
//	// 假如我们获得了一个类型未知的变量 x
//	auto y = x;
//	decltype(x) z = x;
//	// 现在我们想把x,y装进容器中
//	vector<decltype(x)> v{x, y, z};   // 对于模版类来说, decltype的功能无法被auto替代
//
//	return 0;
//}

//int main()
//{
//	// p是指针变量, 能被赋值, 是左值
//	int* p = new int();
//
//	// b是整型变量, 是左值
//	int b = 1;
//
//	// c拥有被赋值的能力, 是左值, 但这种能力被const压制了, 所以在初始化之后不能被赋值, 尽管如此, 它还是左值
//	const int c = 2;
//
//	// *p是new出来的那片空间, 它也能被赋值, 是左值
//	*p = 12;
//
//	// 上述左值的引用
//	int*& rp = p;
//	int& rb = b;
//	const int& rc = c;
//	int& pvalue = *p;
//
//	// 左值也可以在右边
//	int i = 0;
//	int j = i;
//
//	return 0;
//}

//string to_string(int num)
//{
//	string str;
//	int flag = 0;
//	if (num < 0)
//	{
//		num = -num;
//		flag = 1;
//	}
//
//	while (num)
//	{
//		int i = num % 10;
//		str += '0' + i;
//		num = num / 10;
//	}
//
//	str += flag == 0 ? '+' : '-';
//
//	reverse(str.begin(), str.end());
//
//	return str;
//}
//
//int main()
//{
//
//	int x = 211, y = 373;
//
//	// 以下都是常见的右值
//	0;       
//	x + y;   
//	to_string(x + y);
//
//	// 上述右值的引用
//	int&& rr1 = 0;
//	int&& rr2 = x + y;
//	string&& rr3 = to_string(x + y);
//
//	return 0;
//}

//int main()
//{
//	// 左值引用可以为右值起别名
//	// 右值本质是常属性变量 可以使用常引用
//	int i = 1, j = 2;
//	const int& a = 0;
//	const int& k = i + j;
//
//	// 右值引用也可以为左值起别名
//	// 但要通过移动语义
//	int&& b = move(i);
//
//	return 0;
//}

//wind::string to_string(int num)
//{
//	wind::string str;
//	int flag = 0;
//	if (num < 0)
//	{
//		num = -num;
//		flag = 1;
//	}
//
//	while (num)
//	{
//		int i = num % 10;
//		str += '0' + i;
//		num = num / 10;
//	}
//
//	str += flag == 0 ? '+' : '-';
//
//	reverse(str.begin(), str.end());
//
//	return str;
//}
//
//int main()
//{
//	int x = 123, y = 345;
//	wind::string str = "987";
//	str = to_string(x + y);
//	cout << str << endl;
//
//	return 0;
//}

//int main()
//{
//	wind::string str = "hello";
//	wind::string str1 = move(str);
//	cout << str << endl;
//	cout << str1 << endl;
//
//	return 0;
//}

//int main()
//{
//	std::list<wind::string> lt;
//	wind::string s1("hello world");
//	lt.push_back(s1);
//	return 0;
//}

//int main()
//{
//	std::list<wind::string> lt;
//	lt.push_back(wind::to_string(1234));
//	cout << endl;
//	lt.push_back(wind::string("hello world"));
//	return 0;
//} 

//#include"myList.h"
//
//int main()
//{
//	wind::list<wind::string> lt;
//	cout << endl;
//	lt.push_back(wind::to_string(1234));
//	cout << endl;
//	lt.push_back(wind::string("hello world"));
//	return 0;
//}

//void Fun(int& x) { cout << "Fun(int& x)" << endl; }
//void Fun(const int& x) { cout << "Fun(const int& x)" << endl; }
//void Fun(int&& x) { cout << "Fun(int&& x)" << endl; }
//void Fun(const int&& x) { cout << "Fun(const int&& x)" << endl; }
//
//template<class T>
//void PerfectForward(T&& t)
//{
//	Fun(forward<T>(t));
//}
//
//int main()
//{
//	// 实参是右值, 使用的就是右值引用
//	// 实参是左值, 使用的就是左值引用
//	PerfectForward(10);       // 右值
//
//	int a = 10;
//	PerfectForward(a);		  // 左值
//	PerfectForward(move(a));  // 右值
//
//	const int b = 8;
//	PerfectForward(b);			  // const 左值
//	PerfectForward(std::move(b)); // const 右值
//
//	return 0;
//}

//template<class T>
//struct ListNode
//{
//	ListNode* _next = nullptr;
//	ListNode* _prev = nullptr;
//	T _data;
//};
//template<class T>
//class List
//{
//	typedef ListNode<T> Node;
//public:
//	List()
//	{
//		_head = new Node;
//		_head->_next = _head;
//		_head->_prev = _head;
//	}
//	void PushBack(T&& x)
//	{
//		//Insert(_head, x);
//		Insert(_head, std::forward<T>(x));
//	}
//	void PushFront(T&& x)
//	{
//		//Insert(_head->_next, x);
//		Insert(_head->_next, std::forward<T>(x));
//	}
//	void Insert(Node* pos, T&& x)
//	{
//		Node* prev = pos->_prev;
//		Node* newnode = new Node;
//		newnode->_data = std::forward<T>(x); // 关键位置
//		// prev newnode pos
//		prev->_next = newnode;
//		newnode->_prev = prev;
//		newnode->_next = pos;
//		pos->_prev = newnode;
//	}
//	void Insert(Node* pos, const T& x)
//	{
//		Node* prev = pos->_prev;
//		Node* newnode = new Node;
//		newnode->_data = x; // 关键位置
//		// prev newnode pos
//		prev->_next = newnode; 
//			newnode->_prev = prev;
//		newnode->_next = pos;
//		pos->_prev = newnode;
//	}
//private:
//	Node* _head;
//};
//
//int main()
//{
//	List<wind::string> lt;
//	lt.PushBack("1111");
//	lt.PushFront("2222");
//	return 0;
//}

//class Person
//{
//public:
//    Person(const char* name = "", int age = 0)
//        : _name(name)
//        , _age(age)
//    {
//    }
//
//	Person(const Person& p) = default;
//    /*Person(const Person& p)
//        : _name(p._name)
//        , _age(p._age)
//    {
//    }*/
//
//	Person& operator=(const Person& p) = default;
//    /*Person& operator=(const Person& p)
//    {
//        if (this != &p)
//        {
//            _name = p._name;
//            _age = p._age;
//        }
//        return *this;
//    }*/
//
//    Person(Person&& p) = default;
//	Person& operator=(Person&& p) = default;
//
//	~Person() = default;
//    /*~Person()
//    {
//    }*/
//
//private:
//    wind::string _name;
//    int _age;
//};
//
//int main()
//{
//    Person s1;
//    Person s2 = s1;
//    Person s3 = std::move(s1);
//    cout << endl;
//    Person s4;
//    s4 = std::move(s2);
//    return 0;
//}

//void _ShowList()
//{
//	cout << endl;
//}
//
//template<class T, class ...Args>
//void _ShowList(const T& val, Args... args)
//{
//	cout << val << " ";
//	_ShowList(args...);
//}
//
//template<class ...Args>
//void ShowList(Args... args)
//{
//	//// sizeof...()是C++11的新特性, 用于获取模板参数的个数
//	//cout << sizeof...(args) << endl;
//
//	_ShowList(args...);
//}
//
//int main()
//{
//	ShowList(1, 2, 3, "xhiwsab", 5);
//	ShowList(1, 2, 3);
//	ShowList(1, 2.35);
//	ShowList(1);
//	ShowList();
//	return 0;
//}

//template<class T>
//void PrintArg(T t)
//{
//	cout << t << endl;
//}
//
//template<class ...Args>
//void ShowList(Args... args)
//{
//	int arr[] = { (PrintArg(args), 0)... };
//	cout << endl;
//}
//
//int main()
//{
//	ShowList(1, 2, 3, "xhiwsab", 5);
//	return 0;
//}

//int main()
//{
//	std::list<wind::string> lt;
//
//	/*wind::string s1("1111");
//	lt.push_back(s1);
//	lt.push_back(move(s1));
//	cout << endl;
//	wind::string s2("2222");
//	lt.emplace_back(s2);
//	lt.emplace_back(move(s2));*/
//
//	lt.push_back("xxxxxxxx");
//	cout << endl;
//	lt.emplace_back("xxxxxxxx");
//
//	return 0;
//}

//#include"myList.h"
//
//int main()
//{
//	wind::list<pair<wind::string, int>> lt;
//	cout << endl;
//	lt.push_back(make_pair("1111", 1));
//	cout << endl;
//	lt.emplace_back("3333", 3);
//	return 0;
//}