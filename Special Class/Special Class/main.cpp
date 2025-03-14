#include<iostream>
#include<mutex>
using namespace std;

//class HeapOnly
//{
//public:
//	void Destroy1()
//	{
//		delete this;
//	}
//
//	static void Destroy2(HeapOnly* ptr)
//	{
//		delete ptr;
//	}
//
//private:
//	~HeapOnly()
//	{
//	}
//};
//
//int main()
//{
//	auto hp1 = new HeapOnly;
//	auto hp2 = new HeapOnly;
//	hp1->Destroy1();
//	HeapOnly::Destroy2(hp2);
//	return 0;
//}
//

//class HeapOnly
//{
//public:
//	static HeapOnly* Create()
//	{
//		return new HeapOnly;
//	}
//
//	HeapOnly(const HeapOnly& that) = delete;
//private:
//	HeapOnly() {}
//};
//
//int main()
//{
//	auto hp1 = HeapOnly::Create();
//	delete hp1;
//	HeapOnly copy(*hp1);
//	return 0;
//}

//class StackOnly
//{
//public:
//	static StackOnly Create()
//	{
//		return StackOnly();
//	}
//private:
//	StackOnly() {}
//};
//
//int main()
//{
//	auto sk = StackOnly::Create();
//	auto skp = new StackOnly(sk);
//	return 0;
//}

//class StackOnly
//{
//	void* operator new(size_t size) = delete;
//};
//
//int main()
//{
//	auto sk = new StackOnly;
//	return 0;
//}


class A
{
public:
	static A& getInstance()
	{
		return _inst;
	}

	int& getN()
	{
		return n;
	}
private:
	A() {}
	A(const A& that) = delete;
	A& operator=(const A& that) = delete;
	int n = 0;
	static A _inst;
};

A A::_inst;

class B
{
	B() {}
	~B() { cout << "dsa" << endl; }
	B(const B& that) = delete;
	B& operator=(const B& that) = delete;

public:

	static B* getInstance()
	{
		if (_inst == nullptr)
		{
			unique_lock<mutex> mtx(_mtx);
			if (_inst == nullptr)
			{
				_inst = new B;
			}
		}
		return _inst;
	}

	void delInstance()
	{
		if (_inst)
		{
			delete _inst;
			_inst = nullptr;
		}
	}

	int& getM()
	{
		return m;
	}

private:
	int m = 0;
	static B* _inst;
	static std::mutex _mtx;
	
	struct gc
	{
		~gc()
		{
			_inst->delInstance();
		}
	};

	static gc _gc;

};

B* B::_inst = nullptr;
B::gc B::_gc;

//int main()
//{
//	B& b = *B::getInstance();
//	cout << b.getM() << endl;
//
//	b.delInstance();
//
//	return 0;
//}


//int main()
//{
//	cout << A::getInstance().getN() << endl;
//	return 0;
//}


class C
{
public:
	static C& getInstance()
	{
		static C inst;
		return inst;
	}
private:
	C()
	{
		cout << "C()" << endl;
	}

	C(const C& that) = delete;
	C& operator=(const C& that) = delete;
};

int main()
{
	cout << "==============" << endl;
	auto& singleton = C::getInstance();
	return 0;
}