#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<fstream>
#include<sstream>

using namespace std;

class A
{
public:
	// ���ڷ��صľ���type  ���������﷨ʡ��������
	// ����ת������
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
//	// ��������֮��, ������Ϳ�ת��
//	int i = 1.25;
//	// ���캯������֧�ֲ���ص����ͽ���ױת��
//	// ��������Ҳ������Ϊ�й���, ������д����
//	// ���캯������������ת��Ϊ�Զ������͵�����
//	string str("asdfg");
//	// ���캯��Ҳ���԰��Զ�������ת�����Զ�������
//
//	// �Զ�������Ҳ����ͨ��operator type ʵ��������������type ��ת��
//	A a;
//	i = a;
//	// ��������������, ������ʽ����
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
//	// ͬ������, �ܱ�֤������
//	int i, j;
//	cin >> i;
//	scanf("%d", &j);
//	cout << "i:" << i << " j:" << j << endl;
//
//	// ͬ���ر�, ���δ֪, ��Ҫ���ʵ�ʻ���
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
		// ����������д�ģ���������_yearΪ0�������
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
//	// ���������ر�, Ҳ���������Զ��ر�
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
//	ofs << winfo._address << " ";      // ���� std::operator<< (string)
//	ofs << winfo._date << " ";		   // ���� operator << (Data)
//	ofs << winfo._port << " ";         // ���� std::operator<< (double)
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
	string _name; // ����
	int _id; // id
	Date _date; // ʱ��
	string _msg; // ������Ϣ
};

int main()
{
	// ����һ��������Ϣ
	ChatInfo winfo = { "����", 135246, { 2022, 4, 10 }, "����һ�𿴵�Ӱ��" };
	stringstream oss;
	oss << winfo._name << " ";
	oss << winfo._id << " ";
	oss << winfo._date << " ";
	oss << winfo._msg << " ";

	// �յ�һ��������Ϣ
	ChatInfo rinfo;
	stringstream iss(oss.str());
	iss >> rinfo._name >> rinfo._id >> rinfo._date >> rinfo._msg;  // ע���֮ǰ`Date`operator>>�Ļ�` `�ָ�
	cout << rinfo._name << endl;
	cout << rinfo._id << endl;
	cout << rinfo._date << endl;
	cout << rinfo._msg << endl;
	

	return 0;
}