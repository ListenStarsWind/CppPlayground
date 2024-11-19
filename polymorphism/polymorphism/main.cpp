#include<iostream>
using namespace std;

namespace concept
{
class A { protected: int _i; };
				   class B : public A { protected: int _j; };

				   class Person {
				   public:
					   virtual void BuyTicket() { cout << "买票-全价" << endl; }
					   virtual ~Person() { cout << "~Person" << endl; }
					   virtual void function() {}
				   private:
					   int _i = 0;
				   };

				   class Student : public Person {
				   public:
					   void BuyTicket() { cout << "买票-半价" << endl; }
					   ~Student() { cout << "~Student" << endl; }
					   void function() {}
				   private:
					   int _j = 1;
				   };

				   class C : public Student {
				   public:
					   void function() {}
				   private:
					   int _k = 2;
				   };

				   class D : public C {
				   public:
					   ~D() {}
				   };

				   void func1()
				   {
					   Person* p = new Person();
					   delete p;

					   p = new Student();
					   delete p;
				   }

				   void Function(Person& p)
				   {
					   p.BuyTicket();
				   }

				   void func()
				   {
					   Person ps;
					   Student st;
					   Person p = st;
					   C t;
					   D b;
					   Function(ps);
					   Function(st);
				   }

}

namespace what
{
	class A
	{
	public:
		virtual void function(int val = 1) { std::cout << "A->" << val << std::endl; }
		virtual void test() { function(); }
	};

	class B : public A
	{
	public:
		void function(int val = 0) override { std::cout << "B->" << val << std::endl; }
	};

	void func()
	{
		B* p = new B;
		p->test();
		p->A::function();
		p->function();
	}

	// A: A->0   B : B->1   C : A->1   D : B->0   E : 编译出错   F : 以上都不正确
}

namespace abstract_class
{
	class car
	{
	public:
		virtual void drive() = 0;
	};

	class tesla : public car
	{
	public:
		void drive() { cout << "disruptive" << endl; }
	};

	class xiaomi : public car
	{
	public:
		void drive() { cout << "cost-effective" << endl; }
	};

	void func()
	{
		car* pTesla = new tesla;
		pTesla->drive();

		car* pXiaomi = new xiaomi;
		pXiaomi->drive();
	}
}

namespace principle
{
	// 这里常考一道笔试题：sizeof(Base)是多少？
	class Base
	{
	public:
		virtual void Function1() { cout << "Function1()" << endl; }
		virtual void Function2() { cout << "Function2()" << endl; }
		virtual void Function3() { cout << "Function3()" << endl; }
	private:
		int _a = 1;
		char _b;
	};

	void func()
	{
		Base t;
		cout << sizeof(Base) << endl;
	}
}

class task
{
	typedef void (*process) ();
public:
	void operator()() { _function(); }
private:
	process _function = concept::func;
};

int main()
{
	task action;
	action();
	return 0;
}