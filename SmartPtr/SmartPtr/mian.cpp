#define _CRT_SECURE_NO_WARNINGS 

#include<exception>
#include<iostream>
#include<utility>
#include<thread>
#include<mutex>
#include"SmartPtr.h"
#include"unique_ptr.h"
#include"shared_ptr.h"

using namespace std;

void SmartPtrTest1()
{
	SmartPtr<int> sp1(new int);
	*sp1 = 1;
	SmartPtr<pair<string, int>> sp2(new pair<string, int>("xhsqabh", 1));
	sp2->first += "qqq";
	++sp2->second;
}

void SmartPtrTest2()
{
	SmartPtr<int> sp1(new int);
	SmartPtr<int> sp2 = sp1;
	*sp1 = 2;
}

//void unique_ptr_test()
//{
//	wind::unique_ptr<int> p1(new int);
//	wind::unique_ptr<int> p2 = p1;
//	wind::unique_ptr<int> p3(new int);
//	p3 = p1;
//}

void shared_ptr_test()
{
	wind::shared_ptr<string> sp1(new string("aaaaaa"));
	wind::shared_ptr<string> sp2(sp1);
	wind::shared_ptr<string> sp3(new string("bbbbbb"));
	sp1 = sp3;
}

// weak_ptr
struct ListNode
{
	int _val;
	wind::weak_ptr<ListNode> _prev;
	wind::weak_ptr<ListNode> _next;

	~ListNode()
	{
		cout << "~ListNode()" << endl;
	}
};

void shared_ptr_test1()
{
	wind::shared_ptr<ListNode> p1(new ListNode);
	wind::shared_ptr<ListNode> p2(new ListNode);

	cout << p1.use_count() << "  " << p2.use_count() << endl;
	p1->_next = p2;
	p2->_prev = p1;
	cout << p1.use_count() << "  " << p2.use_count() << endl;
}

// ��ȻҲ�����÷º���
template<class T>
struct DelArray
{
	void operator()(T* _ptr)
	{
		delete[] _ptr;
	}
};

void shared_ptr_test2()
{
	// Ĭ�������, shread_ptrʹ��delete _ptr��ʽ�ͷ���Դ
	// �û������Զ�����Դ�ͷŷ�ʽ, ���ɵ��ö����빹�캯��
	wind::shared_ptr<ListNode> p1(new ListNode[2], [](ListNode* _ptr) {delete[] _ptr; });
	wind::shared_ptr<ListNode> p2(new ListNode[2], DelArray<ListNode>());
}

void shared_ptr_test3()
{
	wind::shared_ptr<FILE> f(fopen("shared_ptr.h", "r"), [](FILE* _ptr) {fclose(_ptr); });
}

void shared_ptr_test4()
{
	mutex mtx__;
	wind::shared_ptr<double> r(new double(1.25));
	thread t1(
		[&]() {
			for (size_t i = 0; i < 100000; ++i)
			{
				wind::shared_ptr<double> copy(r);

				unique_lock<mutex> mtx(mtx__);
				++*r;
			}
		}
	);

	thread t2(
		[&]() {
			for (size_t i = 0; i < 100000; ++i)
			{
				wind::shared_ptr<double> copy(r);

				unique_lock<mutex> mtx(mtx__);
				++*r;
			}
		}
	);

	t1.join();
	t2.join();

	cout << r.use_count() << endl;
	cout << *r.get() << endl;
}

int main()
{
	shared_ptr_test4();
	return 0;
}