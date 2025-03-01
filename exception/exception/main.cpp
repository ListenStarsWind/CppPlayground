#include<iostream>


//using namespace std;
//
//class A
//{
//public:
//	A()
//	{
//		cout << "A()" << endl;
//	}
//
//	A(const A& _a)
//	{
//		cout << "A(const A&)" << endl;
//	}
//
//	~A()
//	{
//		cout << "~A()" << endl;
//	}
//};
//
//double division(int x, int y)
//{
//	if (y == 0)
//	{
//		throw 1;
//	}
//	else
//	{
//		return static_cast<double>(x) / static_cast<double>(y);
//	}
//}
//
//void func()
//{
//	int x, y; 
//	cin >> x >> y;
//	//A a;
//	try
//	{
//		cout << division(x, y) << endl;
//	}
//	catch (const char* str)
//	{
//		cout << str << endl;
//	}
//	cout << "xchwesbhcb" << endl;
//}
//
//int main()
//{
//	try
//	{
//		func();
//	}
//	catch (const char* str)
//	{
//		cout << str << endl;
//	}
//	catch (A _b)
//	{
//
//	}
//	catch (...)
//	{
//		cout << "未知的异常" << endl;
//	}
//	return 0;
//}

#include<string>
#include<iostream>
#include<windows.h>

using namespace std;

//// 服务器开发中通常使用的异常继承体系
//class Exception
//{
//public:
//	Exception(const string& errmsg, int id)
//		:_errmsg(errmsg)
//		, _id(id)
//	{
//	}
//	virtual string what() const
//	{
//		return _errmsg;
//	}
//protected:
//	string _errmsg;
//	int _id;
//};
//class SqlException : public Exception
//{
//public:
//	SqlException(const string& errmsg, int id, const string& sql)
//		:Exception(errmsg, id)
//		, _sql(sql)
//	{
//	}
//	virtual string what() const
//	{
//		string str = "SqlException:";
//		str += _errmsg;
//		str += "->";
//		str += _sql;
//		return str;
//	}
//private:
//	const string _sql;
//};
//class CacheException : public Exception
//{
//public:
//	CacheException(const string& errmsg, int id)
//		:Exception(errmsg, id)
//	{
//	}
//	virtual string what() const
//	{
//		string str = "CacheException:";
//		str += _errmsg;
//		return str;
//	}
//};
//class HttpServerException : public Exception
//{
//public:
//	HttpServerException(const string& errmsg, int id, const string& type)
//		:Exception(errmsg, id)
//		, _type(type)
//	{
//	}
//	virtual string what() const
//	{
//		string str = "HttpServerException:";
//		str += _type;
//		str += ":";
//		str += _errmsg;
//		return str;
//	}
//private:
//	const string _type;
//};
//void SQLMgr()
//{
//	srand(time(0));
//	if (rand() % 7 == 0)
//	{
//		throw SqlException("权限不足", 100, "select * from name = '张三'");
//	}
//	//throw "xxxxxx";
//}
//void CacheMgr()
//{
//	srand(time(0));
//	if (rand() % 5 == 0)
//	{
//		throw CacheException("权限不足", 100);
//	}
//	else if (rand() % 6 == 0)
//	{
//		throw CacheException("数据不存在", 101);
//	}
//	SQLMgr();
//}
//void HttpServer()
//{
//	// ...
//	srand(time(0));
//	if (rand() % 3 == 0)
//	{
//		throw HttpServerException("请求资源不存在", 100, "get");
//	}
//	else if (rand() % 4 == 0)
//	{
//		throw HttpServerException("权限不足", 101, "post");
//	}
//	CacheMgr();
//}
//int main()
//{
//	while (1)
//	{
//		Sleep(500);
//		try {
//			HttpServer();
//		}
//		catch (const Exception& e) // 这里捕获父类对象就可以
//		{
//			// 多态
//			cout << e.what() << endl;
//		}
//		catch (...)
//		{
//			cout << "Unkown Exception" << endl;
//		}
//	}
//	return 0;
//}

// noexcept标记的意思是说
// 编译器:"这里不会抛异常"
double division(int x, int y) noexcept
{
	if (y == 0)
	{
		throw "非法的操作数";
	}
	else
	{
		return static_cast<double>(x) / static_cast<double>(y);
	}
}

void func()
{
	int x, y; 
	int* arry1 = nullptr;
	int* arry2 = nullptr;
	try
	{
		arry1 = new int[10];
	}
	catch (const exception& e)
	{
		// 申请失败
		// 不用释放
	}
	try
	{
		arry2 = new int[10];
	}
	catch (const exception& e)
	{
		delete[] arry1;
	}
	cin >> x >> y;
	try
	{
		cout << division(x, y) << endl;
	}
	catch (const char* str)
	{
		delete[] arry1;
		delete[] arry2;
		cout << "kxhsabjhc" << endl;
		// 这相当于捕获到什么就抛什么
		throw;     // 重抛异常   
	}
	//cout << division(x, y) << endl;
	cout << "xchwesbhcb" << endl;
	delete[] arry1;
	delete[] arry2;
}

int main()
{
	try
	{
		func();
	}
	catch (const char* str)
	{
		cout << str << endl;
	}
	catch (...)
	{
		cout << "未知的异常" << endl;
	}
	return 0;
}