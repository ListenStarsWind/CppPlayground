#include<iostream>
using namespace std;

namespace casual_talk
{
	class A
	{
	public:
		A() {}
	protected:
		int _a;
		int _b;
	};

	class B : public A {};

	void func() {}
}

namespace friend_function
{
	class Student;

	class Person
	{
	public:
		friend void Display(const Person& p, const Student& s);
	protected:
		string _name; // 姓名
	};

	class Student : public Person
	{
	public:
		friend void Display(const Person& p, const Student& s);
	protected:
		int _stuNum; // 学号
	};

	void Display(const Person& p, const Student& s)
	{
		cout << p._name << endl;
		cout << s._stuNum << endl;
	}

	void func()
	{
		Person p;
		Student s;
		Display(p, s);
	}
}

namespace static_member
{
	class Person
	{
	public:
		Person() { /*++_count;*/printf("Person内的_count地址为         %p\n", &_count); }
		//~Person() { --_count; }
	protected:
		string _name; // 姓名
	public:
		static int _count; // 统计人的个数。
	};

	int Person::_count = 0;

	class Student : public Person
	{
	public:
		Student() :Person(), _stuNum(0) { printf("Student内的_count地址为        %p\n", &_count); }
	protected:
		int _stuNum; // 学号
	};

	class Graduate : public Student
	{
	protected:
		string _seminarCourse; // 研究科目
	};

	void func()
	{
		printf("类外定义的_count静态成员地址为 %p\n", &Person::_count);
		printf("----------\n");
		Student();
		printf("----------\n");
		Person();
	}
}

namespace complex_inheritance
{
	class Person
	{
	public:
		string _name; // 姓名
		int _age;     // 年龄
	};

	class Student : virtual public Person
	{
	protected:
		int _num; //学号
	};

	class Teacher : virtual public Person
	{
	protected:
		int _id; // 职工编号
	};

	class Assistant : public Student, public Teacher
	{
	protected:
		string _majorCourse; // 主修课程
	};


	class A
	{
	public:
		int _a;
	};

	class B : virtual public A
	{
	public:
		int _b;
	};

	class C : virtual public A
	{
	public:
		int _c;
	};

	class D : public B, public C
	{
	public:
		int _d;
	};

	void func()
	{
		D d;
		d.B::_a = 1;
		d.C::_a = 2;
		d._b = 3;
		d._c = 4;
		d._d = 5;
	}

	void func1()
	{
		Assistant t;
		printf("%p\n", &t._name);
		printf("%p\n", &t.Student::_name);
		printf("%p\n", &t.Teacher::_name);
	}
}

namespace example_problem
{
	class A {
	public:
		A(const char* s) { cout << s << endl; }
		~A() {}
	};

	class B :virtual public A
	{
	public:
		B(const char* s1, const char* s2) :A(s1) { cout << s2 << endl; }
	};

	class C :virtual public A
	{
	public:
		C(const char* s1, const char* s2) :A(s1) { cout << s2 << endl; }
	};

	class D :public C, public B
	{
	public:
		D(const char* s1, const char* s2, const char* s3, const char* s4) :B(s1, s2), C(s1, s3), A(s1)
		{
			cout << s4 << endl;
		}
	};

	void func()
	{
		D* p = new D("class A", "class B", "class C", "class D");
		delete p;
	}
}

class task
{
	typedef void (*process) ();
public:
	void operator()() { _function(); }
private:
	process _function = example_problem::func;
};

int main()
{
	task action;
	action();
	return 0;
}