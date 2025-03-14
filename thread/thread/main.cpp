#include<thread>
#include<vector>
#include<mutex>
#include<atomic>
#include<iostream>

using namespace std;

int main()
{
	size_t x__ = 0;
	atomic<size_t> x(x__);
	mutex mtx__;
	thread t1(
		[&]() {
				for (size_t i = 0; i < 100000; ++i)
				{
					size_t oldval, newval;
					do
					{
						oldval = x;
						newval = oldval + 1;
					} while (!atomic_compare_exchange_weak(&x, &oldval, newval));
				}
		}
	);

	thread t2(
		[&]() {
			for (size_t i = 0; i < 100000; ++i)
			{
				size_t oldval, newval;
				do
				{
					oldval = x;
					newval = oldval + 1;
				} while (!atomic_compare_exchange_weak(&x, &oldval, newval));
			}
		}
	);

	t1.join();
	t2.join();

	cout << x << endl;

	return 0;
}

//int main()
//{
//	int x = 1;
//	mutex __mtx;
//	condition_variable cond;
//
//	thread t2(
//		[&]() {
//			for (int i = 0; i < 10; ++i)
//			{
//				unique_lock<mutex> mtx(__mtx);
//				while (x % 2 != 0)
//					cond.wait(mtx);
//				cout << "[thread-" << 2 << "]info : " << x++ << endl;
//				cond.notify_one(); // 唤醒一个线程
//				this_thread::sleep_for(std::chrono::milliseconds(100)); // 睡眠0.1秒
//			}
//		}
//	);
//
//	thread t1(
//		[&]() {
//			for (int i = 0; i < 10; ++i)
//			{
//				unique_lock<mutex> mtx(__mtx);
//				while (x % 2 == 0)
//					cond.wait(mtx);
//				cout << "[thread-" << 1 << "]info : " << x++ << endl;
//				cond.notify_one();
//				this_thread::sleep_for(std::chrono::milliseconds(100));
//			}
//		}
//	);
//
//	t1.join();
//	t2.join();
//
//	return 0;
//}


//std::mutex mtx;
//
//template<class Mutex>
//struct lock_guard__
//{
//    lock_guard__(Mutex& mtx)
//        :_mtx(mtx)
//    {
//        _mtx.lock();
//    }
//
//    ~lock_guard__()
//    {
//        _mtx.unlock();
//    }
//
//    lock_guard__(const lock_guard__<Mutex>& that) = delete;
//
//private:
//    Mutex& _mtx;
//};
//
//void print_even(int x) {
//    if (x % 2 == 0) std::cout << x << " 是偶数\n";
//    else throw (std::logic_error("不是偶数"));
//}
//
//void print_thread_id(int id) {
//    try {
//        lock_guard__<std::mutex> lck(mtx);
//        //mtx.lock();
//        print_even(id);
//        //mtx.unlock();
//    }
//    catch (std::logic_error&) {
//        std::cout << "[异常捕获]\n";
//    }
//}
//
//int main()
//{
//    std::thread threads[10];
//    for (int i = 0; i < 10; ++i)
//        threads[i] = std::thread(print_thread_id, i + 1);
//
//    for (auto& th : threads) th.join();
//
//    return 0;
//}

//void Print1(size_t n, const string& s, mutex& m, int& rx)
//{
//	for (size_t i = 0; i < n; i++)
//	{
//		m.lock();
//
//		cout <<this_thread::get_id()<<s<<":" << i << endl;
//		++rx;
//
//		m.unlock();
//
//		this_thread::sleep_for(chrono::milliseconds(300));
//	}
//}
//
//int main()
//{
//	mutex mtx;
//	int x = 0;
//	thread t1(Print1, 100,  "我是鹏哥", ref(mtx), ref(x));
//	thread t2(Print1, 200, "我是蛋哥", ref(mtx), ref(x));
//
//	//thread t3(t1);
//
//	cout <<"线程1：" << t1.get_id() << endl;
//	cout <<"线程2："<< t2.get_id() << endl;
//
//	t1.join();
//	t2.join();
//
//	cout << x << endl;
//
//	return 0;
//}

//// 不加下划线会和标准库冲突
//void count__(size_t& size, mutex& mtx)
//{
//	for (size_t i = 0; i < 100000; ++i)
//	{
//		mtx.lock();
//		++size;
//		mtx.unlock();
//	}
//}
//
//int main()
//{
//	size_t x = 0;
//	mutex mtx;
//	// 在构造函数的调用链内部, 参数会逐渐变为右值
//	// ref模版函数可以让它们一直保持左值属性
//	thread t1(count__, ref(x), ref(mtx));
//	thread t2(count__, ref(x), ref(mtx));
//	t1.join();
//	t2.join();
//	cout << x << endl;
//	return 0;
//}
 
//struct test
//{
//	test() { cout << "test()" << endl; }
//	test(const test& that) { cout << "test(const test& that)" << endl; }
//	test(test&& that) { cout << "test(test&& that)" << endl; }
//	test& operator=(const test& that) { cout << "operator=(const test& that)" << endl; return *this; }
//	test& operator=(test&& that) { cout << "operator=(test&& that)" << endl; return *this; }
//};
//
//template<class... Args>
//void _func(Args... args)
//{
//
//}
//
//
//template<class... Args>
//void func(Args&&... args)
//{
//	_func(forward<Args>(args)...);
//}
//
//
//
//int main()
//{
//	test t;
//	cout << "====" << endl;
//	func(ref(t));
//	return 0;
//}

//int main()
//{
//	mutex mtx;
//	size_t size = 0;
//	thread t1(
//		[&size, &mtx]() {
//			for (size_t i = 0; i < 100000; ++i)
//			{
//				mtx.lock();
//				++size;
//				mtx.unlock();
//			}
//		}
//	);
//
//	thread t2(
//		[&size, &mtx]() {
//			for (size_t i = 0; i < 100000; ++i)
//			{
//				mtx.lock();
//				++size;
//				mtx.unlock();
//			}
//		}
//	);
//
//	t1.join();
//	t2.join();
//
//	cout << size << endl;
//	return 0;
//}

//void hello(size_t begin, size_t end)
//{
//	for (size_t i = begin; i < end; ++i)
//	{
//		cout << "[thread-" << this_thread::get_id() << "]info : ";
//		cout << "hello class thread" << endl;
//	}
//}
//
//int main()
//{
//	thread t1(hello, 0, 3);
//	thread t2(move(t1));
//	t2.join();
//	return 0;
//}

//int main()
//{
//	vector<thread> ts(5);         // vector (size_type n, const value_type& val = value_type())
//	for (auto& t : ts)
//	{
//		t = thread(hello, 0, 2);
//	}
//	for (auto& t : ts)
//	{
//		t.join();
//	}
//	return 0;
//}

//int main()
//{
//	thread t1(hello, 0, 5);
//	thread t2(hello, 1, 3);
//
//	cout << "create a thread, t1: " << t1.get_id() << endl;
//	cout << "create a thread, t2: " << t2.get_id() << endl;
//	t1.join();
//	t2.join();
//	return 0;
//}