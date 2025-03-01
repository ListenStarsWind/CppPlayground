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
//		cout << "δ֪���쳣" << endl;
//	}
//	return 0;
//}

#include<string>
#include<iostream>
#include<windows.h>

using namespace std;

//// ������������ͨ��ʹ�õ��쳣�̳���ϵ
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
//		throw SqlException("Ȩ�޲���", 100, "select * from name = '����'");
//	}
//	//throw "xxxxxx";
//}
//void CacheMgr()
//{
//	srand(time(0));
//	if (rand() % 5 == 0)
//	{
//		throw CacheException("Ȩ�޲���", 100);
//	}
//	else if (rand() % 6 == 0)
//	{
//		throw CacheException("���ݲ�����", 101);
//	}
//	SQLMgr();
//}
//void HttpServer()
//{
//	// ...
//	srand(time(0));
//	if (rand() % 3 == 0)
//	{
//		throw HttpServerException("������Դ������", 100, "get");
//	}
//	else if (rand() % 4 == 0)
//	{
//		throw HttpServerException("Ȩ�޲���", 101, "post");
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
//		catch (const Exception& e) // ���ﲶ�������Ϳ���
//		{
//			// ��̬
//			cout << e.what() << endl;
//		}
//		catch (...)
//		{
//			cout << "Unkown Exception" << endl;
//		}
//	}
//	return 0;
//}

// noexcept��ǵ���˼��˵
// ������:"���ﲻ�����쳣"
double division(int x, int y) noexcept
{
	if (y == 0)
	{
		throw "�Ƿ��Ĳ�����";
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
		// ����ʧ��
		// �����ͷ�
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
		// ���൱�ڲ���ʲô����ʲô
		throw;     // �����쳣   
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
		cout << "δ֪���쳣" << endl;
	}
	return 0;
}