#include<iostream>

using namespace std;

namespace location_of_virtual_table
{
	int j = 0;
	int i;

	typedef void(*function)();

	class base
	{
	public:
		base() :_i(0) {/*cout << "base" << endl;*/ }
		virtual ~base() {}
		virtual void functi() { cout << "functi" << endl; }
	private:
		int _i;
	};

	void func()
	{
		// ¶ÑÇø
		void* p1 = new int;
		void* p2 = new int;
		void* p3 = new int;

		// ³£Á¿×Ö·û´®
		const char* str = "hello world";

		int a = 1;
		int b = 1;
		int c = 1;

		base t;

		printf("functi:address->%p\n", &base::functi);
		printf("func:address->%p\n", func);
		printf("VFT:address->%p\n", (function*)(*((void**)&t)));
		printf("'h':address->%p\n", str);
		printf("j:address->%p\n", &j);
		printf("i:address->%p\n", &i);
		printf("p1:address->%p\n", p1);
		printf("p2:address->%p\n", p2);
		printf("p3:address->%p\n", p3);
		printf("str:address->%p\n", &str);
		printf("a:address->%p\n", &a);
		printf("b:address->%p\n", &b);
		printf("c:address->%p\n", &c);

		delete p1;
		delete p2;
		delete p3;
	}
}

namespace VFT_in_SIC
{
	class I
	{
	public:
		virtual void func() { cout << "I::func()" << endl; }
		virtual void func1() { cout << "I::func1()" << endl; }
	private:
		int _i = 0;
	};

	class J:public I
	{
	public:
		virtual void func() { cout << "J::func()" << endl; }
		virtual void func2() { cout << "J::func2()" << endl; }
	private:
		int _j = 1;
	};

	class K :public J
	{
	public:
		virtual void func() { cout << "k::func()" << endl; }
		virtual void func2() { cout << "k::func2()" << endl; }
	private:
		int _j = 2;
	};

	typedef void(*function)();

	void VFTPprint(function* p)
	{
		int i = 0;
		while (p[i])
		{
			function fp = p[i++];
			printf("virtual function address:%p   ", fp);
			fp();
		}
		printf("\n");
	}

	void func()
	{
		I i;
		J j;
		K k;

		VFTPprint((function*)(*((void**)&i)));
		VFTPprint((function*)(*((void**)&j)));
		VFTPprint((function*)(*((void**)&k)));
	}
}

namespace VFT_in_MI
{
	typedef void(*function)();

	void VFTPprint(function* p)
	{
		int i = 0;
		while (p[i])
		{
			function fp = p[i++];
			printf("virtual function address:%p   ", fp);
			fp();
		}
		printf("\n");
	}

	class base1
	{
	public:
		virtual void func1() { cout << "base1::func1" << endl; }
		virtual void func2() { cout << "base1::func2" << endl; }
		virtual void func() { cout << "base1::func" << endl; }
	private:
		int _m = 1;
	};

	class base2
	{
	public:
		virtual void func1() { cout << "base2::func1" << endl; }
		virtual void func3() { cout << "base2::func3" << endl; }
		virtual void func() {  cout << "base2::func" << endl; }
	private:
		int _n = -1;
	};

	class derive : public base1, public base2
	{
	public:
		virtual void func2() { cout << "derive::func2" << endl; }
		virtual void func3() { cout << "derive::func3" << endl; }
		virtual void func() { int i = _i; cout << "derive::func" << endl; }
	private:
		int _i = 0;
	};

	void func()
	{
		derive d;
		d.func();

		base1* p1 = &d;
		base2* p2 = &d;

		p1->func();
		p2->func();

		VFTPprint((function*)(*((void**)&d)));

		base2* ptr = &d;
		VFTPprint((function*)(*((void**)ptr)));
	}
}

namespace Vft_in_Vi
{
	class A
	{
	public:
		virtual void functi() { cout << "A::functi" << endl; }
		virtual void functio() { cout << "A::functio" << endl; }
	protected:
		int _a = 0;
	};

	class B : virtual public A
	{
	public:
		virtual void functi() { cout << "B::functi" << endl; }
		virtual void functi_b() { cout << "B::functi" << endl; }
		virtual void functio1() { cout << "B::functio1" << endl; }
	protected:
		int _b = 1;
	};

	class C : virtual public A
	{
	public:
		virtual void functi() { cout << "C::functi" << endl; }
		virtual void functi_c() { cout << "C::functi" << endl; }
		virtual void functio2() { cout << "C::functio2" << endl; }
	protected:
		int _c = 2;
	};

	class D : public B, public C
	{
	public:
		virtual void functi() { cout << "D::functi" << endl; }
		virtual void functi_d() { cout << "D::functi" << endl; }
		virtual void functio() { cout << "D::functio" << endl; }
	protected:
		int _d = -1;
	};

	void func()
	{
		D d;
	}
}

class task {
	typedef void(*function)();
public:
	void operator()() { _func(); }
private:
	function _func = Vft_in_Vi::func;
};

int main()
{
	task t;
	t();
	return 0;
}