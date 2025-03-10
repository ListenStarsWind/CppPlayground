#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<fstream>
#include<sstream>

using namespace std;

class A
{
public:
	// 由于返回的就是type  所以它的语法省略了类型
	// 类型转换重载
	operator int()
	{
		return 3;
	}

	operator string()
	{
		return "asdfgh";
	}
};

//int main()
//{
//	// 内置类型之间, 相近类型可转换
//	int i = 1.25;
//	// 构造函数可以支持不相关的类型进行妆转换
//	// 内置类型也可以认为有构造, 但我们写不了
//	// 构造函数是内置类型转换为自定义类型的渠道
//	string str("asdfg");
//	// 构造函数也可以把自定义类型转换成自定义类型
//
//	// 自定义类型也可以通过operator type 实现其向内置类型type 的转换
//	A a;
//	i = a;
//	// 这里语义有歧义, 所以显式调了
//	str = a.operator std::string();
//	cout << i << endl;
//	cout << str << endl;
//
//	return 0;
//}

//int main()
//{
//	string str;
//	while (cin >> str)
//	{
//		cout << str << endl;
//	}
//	return 0;
//}


//int main()
//{
//	// 同步开启, 能保证不乱序
//	int i, j;
//	cin >> i;
//	scanf("%d", &j);
//	cout << "i:" << i << " j:" << j << endl;
//
//	// 同步关闭, 结果未知, 需要结合实际环境
//	cin.sync_with_stdio(false);
//	int m, n;
//	cin >> m;
//	scanf("%d", &n);
//	cout << "m:" << m << " n:" << n << endl;
//
//	return 0;
//}

class Date
{
	friend ostream& operator << (ostream& out, const Date& d);
	friend istream& operator >> (istream& in, Date& d);
public:
	Date(int year = 1, int month = 1, int day = 1)
		:_year(year)
		, _month(month)
		, _day(day)
	{
	}
	operator bool()
	{
		// 这里是随意写的，假设输入_year为0，则结束
		if (_year == 0)
			return false;
		else
			return true;
	}
private:
	int _year;
	int _month;
	int _day;
};


istream& operator >> (istream& in, Date& d)
{
	in >> d._year >> d._month >> d._day;
	return in;
}
ostream& operator << (ostream& out, const Date& d)
{
	out << d._year << " " << d._month << " " << d._day;
	return out;
}

struct ServerInfo
{
	string _address;
	double _port;
	Date _date;
};

//int main()
//{
//	ServerInfo winfo = { "192.0.0.1", 12.13, { 2022, 4, 10 } };
//	ofstream bin("info.bin", ofstream::out | ofstream::binary);
//	bin.write(reinterpret_cast<const char*>(&winfo), sizeof(winfo));
//	// 可以主动关闭, 也可用析构自动关闭
//	return 0;
//}

//int main()
//{
//	ServerInfo rinfo;
//	ifstream bin("info.bin", ios_base::in | ios_base::binary);
//	bin.read(reinterpret_cast<char*>(&rinfo), sizeof(rinfo));
//	return 0;
//}

//int main()
//{
//	/*ServerInfo winfo = { "https://legacy.cplusplus.com/reference/fstream/ofstream/ofstream/", 12.13, { 2022, 4, 10 } };
//	ofstream bin("info.bin", ofstream::out | ofstream::binary);
//	bin.write(reinterpret_cast<const char*>(&winfo), sizeof(winfo));
//	bin.close();*/
//
//	ServerInfo rinfo;
//	ifstream bout("info.bin", ios_base::in | ios_base::binary);
//	bout.read(reinterpret_cast<char*>(&rinfo), sizeof(rinfo));
//
//	cout << rinfo._address << endl;
//	cout << rinfo._date << endl;
//	cout << rinfo._port << endl;
//
//	return 0;
//}

//int main()
//{
//	ServerInfo winfo = { "https://legacy.cplusplus.com/reference/fstream/ofstream/ofstream/", 12.13, { 2022, 4, 10 } };
//	ofstream ofs("info.bin");
//	ofs << winfo._address << " ";      // 调用 std::operator<< (string)
//	ofs << winfo._date << " ";		   // 调用 operator << (Data)
//	ofs << winfo._port << " ";         // 调用 std::operator<< (double)
//	return 0;
//}

//istream& operator>>(istream& in, ServerInfo& info)
//{
//	in >> info._address >> info._date >> info._port;
//	return in;
//}
//
//int main()
//{
//	ServerInfo rinfo; 
//	ifstream ifs("info.bin");
//	ifs >> rinfo;
//	cout << rinfo._address << endl;
//	cout << rinfo._date << endl;
//	cout << rinfo._port << endl;
//	return 0;
//}

//int main()
//{
//	char sq1[128];
//	char name[10];
//	scanf("%s", name);
//	sprintf(sq1, "select * from t_scroe where name = '%s'", name);
//	printf("%s\n", sq1);
//	return 0;
//}

//int main()
//{
//	string sq2;
//	Date date;
//	cin >> date;
//	ostringstream oss;
//	oss << date;
//
//	sq2 += "select * from t_data where data = '";
//	sq2 += oss.str();
//	sq2 += "'";
//	cout << sq2 << endl;
//
//	return 0;
//} 

//int main()
//{
//	Date date(2013, 5, 6);
//	ostringstream sqloss;
//	sqloss << "select * from t_data where data = '" << date << "'";
//	cout << sqloss.str() << endl;
//
//	return 0;
//}

struct ChatInfo
{
	string _name; // 名字
	int _id; // id
	Date _date; // 时间
	string _msg; // 聊天信息
};

int main()
{
	// 发送一个聊天消息
	ChatInfo winfo = { "张三", 135246, { 2022, 4, 10 }, "晚上一起看电影吧" };
	stringstream oss;
	oss << winfo._name << " ";
	oss << winfo._id << " ";
	oss << winfo._date << " ";
	oss << winfo._msg << " ";

	// 收到一个聊天消息
	ChatInfo rinfo;
	stringstream iss(oss.str());
	iss >> rinfo._name >> rinfo._id >> rinfo._date >> rinfo._msg;  // 注意把之前`Date`operator>>改回` `分割
	cout << rinfo._name << endl;
	cout << rinfo._id << endl;
	cout << rinfo._date << endl;
	cout << rinfo._msg << endl;
	

	return 0;
}