#include<iostream>
#include<string>

using namespace std;

class Person
{
public:
	Person(const string& name)
		:_name(name)
	{
		cout << "Person(const string&)" << endl;
	}

	Person(const Person& obj)
		:_name(obj._name)
	{
		cout << "Person(const Person&)" << endl;
	}

	Person& operator=(const Person& obj){
		if (&obj != this)
		{
			_name = obj._name;
		}
		cout << "operator=(const Person&)" << endl;
		return *this;
	}
	~Person() {
		cout << "~Person()" << endl;
	}
	/*void Print()
	{
		cout << "name:" << _name << endl;
		cout << "age:" << _age << endl;
	}*/
protected:
	string _name = "peter"; // 姓名
	//int _age = 18; // 年龄
	//int _number = 1024;
};
class Student : protected Person
{
public:
	Student(const string& name, int id)
		:Person(name)
		,_stuid(id)
	{
		cout << "Student(const string&, int)" << endl;
	}
	Student(const Student& obj)
		:Person(obj)
		,_stuid(obj._stuid)
	{
		cout << "Student(const Student&)" << endl;
	}
	Student& operator=(const Student& obj){
		if (&obj != this)
		{
			Person::operator=(obj);
			_stuid = obj._stuid;
		}
		cout << "operator=(const Student&)" << endl;
		return *this;
	}
	~Student(){
		cout << "~Student()" << endl;
	}
	//void f()
	//{
	//	//Print();
	//	cout << Person::_number << endl;
	//}
protected:
	int _stuid; // 学号
	//int _number = 512;
}; 

int main()
{
	Student s1("wind", 18);
	Student s2("whisper", 18);
	s2 = s1;
	return 0;
}

class Teacher : public Person
{
protected:
	int _jobid; // 工号
};

//class C : public Student
//{
//	void twq()
//	{
//		C i;
//		Person j = i;
//	}
//	int i = 4;
//};

//void test1()
//{
//	Student s;
//	Teacher t;
//
//	s.Print();
//	t.Print();
//
//}

//void test2()
//{
//	C i;
//	Person j = i;
//}


//=================================

class A
{
public:
	void fun()
	{
		cout << "func()" << endl;
	}
};

class B : public A
{
public:
	void fun(int i)
	{
		//A::fun();
		cout << "func(int i)->" << i << endl;
	}
};

void test3()
{
	B().A::fun();
}