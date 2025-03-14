# thread

之前我们学习了Linux中的原生线程库, 现在, 我们来学习C++11的线程库.

## class thread

C++11之前, 涉及到多线程问题, 都是和平台相关的, 比如windows和linux下各有自己的接口，这使得代码的可移植性比较差。C++11中最重要的特性就是对线程进行支持了，使得C++在并行编程时不需要依赖第三方库. 它本身通过条件编译封装了各个平台的差异性,  以后线程操作就不必面向平台了. 除此之外, 它还具有C++11的语法特性, 使得其的接口更加友好.

### constructor

我们先来看构造函数. 

```cpp
default (1)	        thread() noexcept;

initialization (2)	template <class Fn, class... Args>
    			explicit thread (Fn&& fn, Args&&... args);

copy [deleted] (3)	thread (const thread&) = delete;

move (4)	        thread (thread&& x) noexcept;
```

第一个是默认无参构造, 它创建一个空线程对象, 该线程不执行, 不启动

第二个是线程初始化模版函数, 与`pthread_create`相比, 它的优势在于可以更方便地进行更变参数传参, 因为它使用了可变模版参数包, 而在`pthread_create`中, 则需要临时将传入参数包成一个结构体, 然后传结构体对象指针. `thread`的第一个参数是线程执行的函数, 其它的则是函数所需的参数, 并且, 很明显这里用的是万能引用, 里面很明显会有完美转发.

`thread`不允许进行拷贝构造.   但允许进行移动构造.

--------------

好的, 我们先简单创建一个线程

```cpp
#include<thread>
#include<iostream>

using namespace std;

void hello(size_t end)
{
	for (size_t i = 0; i < end; ++i)
	{
		cout << "hello class thread" << endl;
	}
}

int main()
{
	thread t(hello, 5);
	t.join();
	return 0;
}
```

```bash
hello class thread
hello class thread
hello class thread
hello class thread
hello class thread

E:\C language new project\routine\thread\x64\Debug\thread.exe (进程 14096)已退出，代码为 0 (0x0)。
按任意键关闭此窗口. . .
```

想要获得线程的ID, 需要用到`get_id()`, 它返回的是`class thread`内部自己封装的一个用于描述线程ID的类对象.

```cpp
void hello(size_t end)
{
	for (size_t i = 0; i < end; ++i)
	{
		cout << "hello class thread" << endl;
	}
}

int main()
{
	thread t1(hello, 5);
	thread t2(hello, 5);

	cout << "create a thread, t1: " << t1.get_id() << endl;
	cout << "create a thread, t2: " << t2.get_id() << endl;
	t1.join();
	t2.join();
	return 0;
}
```

```shell
create a thread, t1: 5952
create a thread, t2: 22692
hello class thread
hello class thread
hello class thread
hello class thread
hello class thread
hello class thread
hello class thread
hello class thread
hello class thread
hello class thread

E:\C language new project\routine\thread\x64\Debug\thread.exe (进程 27436)已退出，代码为 0 (0x0)。
按任意键关闭此窗口. . .
```

为了让线程可以获得自己的ID, `thread`库中定义了`class this_thread`, 其中的成员函数都是静态的, 与`class thread`构成友元关系, 可以回调`class thread`的`get_id()`. 

![image-20250312131624308](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250312131624406.png)

```cpp
#include<thread>
#include<iostream>

using namespace std;

void hello(size_t end)
{
	for (size_t i = 0; i < end; ++i)
	{
		cout << "[thread-" << this_thread::get_id() << "]info : ";
		cout << "hello class thread" << endl;
	}
}

int main()
{
	thread t1(hello, 5);
	thread t2(hello, 5);

	cout << "create a thread, t1: " << t1.get_id() << endl;
	cout << "create a thread, t2: " << t2.get_id() << endl;
	t1.join();
	t2.join();
	return 0;
}
```

```shell
create a thread, t1: 26972
create a thread, t2: 2676
[thread-26972]info : hello class thread
[thread-26972]info : hello class thread
[thread-26972]info : hello class thread
[thread-26972]info : hello class thread
[thread-26972]info : hello class thread
[thread-2676]info : hello class thread
[thread-2676]info : hello class thread
[thread-2676]info : hello class thread
[thread-2676]info : hello class thread
[thread-2676]info : hello class thread

E:\C language new project\routine\thread\x64\Debug\thread.exe (进程 24972)已退出，代码为 0 (0x0)。
按任意键关闭此窗口. . .
```

我们看到此时已经出现资源竞争问题了, 但我们先略过, 再看看其它接口.

`yield()`可以让线程让出自己的时间片, 它用于什么场景呢? 我们曾在Linux那边说过,  对于普通的互斥锁来说, 线程竞争锁失败就会进入阻塞状态, 但存在一种场景, 临界区的代码很少, 运行时间短, 此时绝大多数时间就会被浪费在线程唤醒上, 所以就有了自旋锁, 自旋锁获得不到不会阻塞, 而是继续尝试竞争锁, 此时就省下了线程唤醒的时间, 但即使如此, 那些没竞争到锁的线程还在空转, 占着时间片做不了有用功, 所以此时就可以用一下`yield()`, 让线程主动放弃时间片, 把CPU留给更需要的线程, 相当于把自己在进程中的时间片配比让给别的线程, 最后让来让去就让到了获得锁的那个线程上.

由于用的是可变参数包, 所以可以很轻松的改变参数的类型和个数.

```cpp
#include<thread>
#include<iostream>

using namespace std;

void hello(size_t begin, size_t end)
{
	for (size_t i = begin; i < end; ++i)
	{
		cout << "[thread-" << this_thread::get_id() << "]info : ";
		cout << "hello class thread" << endl;
	}
}

int main()
{
	thread t1(hello, 0, 5);
	thread t2(hello, 1, 3);

	cout << "create a thread, t1: " << t1.get_id() << endl;
	cout << "create a thread, t2: " << t2.get_id() << endl;
	t1.join();
	t2.join();
	return 0;
}
```

```shell
create a thread, t1: 28252
create a thread, t2: 28124
[thread-28124]info : hello class thread
[thread-28124]info : hello class thread
[thread-28252]info : hello class thread
[thread-28252]info : hello class thread
[thread-28252]info : hello class thread
[thread-28252]info : hello class thread
[thread-28252]info : hello class thread

E:\C language new project\routine\thread\x64\Debug\thread.exe (进程 11532)已退出，代码为 0 (0x0)。
按任意键关闭此窗口. . .
```

----------------

下面我们说说空构造的玩法.  空构造一般搭配容器和移动赋值使用, 和构造相同, `thread`也只支持移动赋值, 而不支持一般赋值, 我们可以先在容器中创建若干个空线程待命, 等到合适的时候, 就可以使用移动赋值激活这些空线程, 让它们实际运行.

```cpp
#include<thread>
#include<vector>
#include<iostream>

using namespace std;

void hello(size_t begin, size_t end)
{
	for (size_t i = begin; i < end; ++i)
	{
		cout << "[thread-" << this_thread::get_id() << "]info : ";
		cout << "hello class thread" << endl;
	}
}

int main()
{
	vector<thread> ts(5);         // vector (size_type n, const value_type& val = value_type())
	for (auto& t : ts)
	{
		t = thread(hello, 0, 2);
	}
	for (auto& t : ts)
	{
		t.join();
	}
	return 0;
}
```

```shell
[thread-20284]info : [thread-14288]info : hello class thread
[thread-[thread-27596]info : hello class threadhello class thread
[thread-20284]info : hello class thread
[thread-11012]info : hello class thread[thread-
[thread-27596]info :
[thread-1631611012]info : 14288]info : hello class thread]info :
hello class thread
hello class thread
hello class thread[thread-16316
]info : hello class thread

E:\C language new project\routine\thread\x64\Debug\thread.exe (进程 5592)已退出，代码为 0 (0x0)。
按任意键关闭此窗口. . .
```

然后我们单纯用一下移动构造

```cpp
#include<thread>
#include<vector>
#include<iostream>

using namespace std;

void hello(size_t begin, size_t end)
{
	for (size_t i = begin; i < end; ++i)
	{
		cout << "[thread-" << this_thread::get_id() << "]info : ";
		cout << "hello class thread" << endl;
	}
}

int main()
{
	thread t1(hello, 0, 3);
	thread t2(move(t1));
	t2.join();
	return 0;
}
```

```shell
[thread-28348]info : hello class thread
[thread-28348]info : hello class thread
[thread-28348]info : hello class thread

E:\C language new project\routine\thread\x64\Debug\thread.exe (进程 24164)已退出，代码为 0 (0x0)。
按任意键关闭此窗口. . .
```

移动之后, `t1`就变成了空线程, 不需要请求加入. 

我们来稍微总结一下, 对于线程的创建, 有两种方式, 一是直接使用有参构造, 二是先创建空线程对象, 然后移动赋值.

### resource sharing

#### mutex

上面我们都没有怎么用临界资源, 也就一个屏幕资源共享, 现在我们要来点真正日常会用的操作了.

```cpp
int main()
{
	size_t size = 0;
	thread t1(
		[&size]() {
			for (size_t i = 0; i < 100000; ++i)
				++size;
		}
	);

	thread t2(
		[&size]() {
			for (size_t i = 0; i < 100000; ++i)
				++size;
		}
	);

	t1.join();
	t2.join();

	cout << size << endl;
	return 0;
}
```

```shell
159227

E:\C language new project\routine\thread\x64\Debug\thread.exe (进程 25932)已退出，代码为 0 (0x0)。
按任意键关闭此窗口. . .
```

我们对同一个变量进行加加处理. 很明显, 这里出现了数据不一致问题, 这也是我们可以预料到的.

接下来我们就要保证临界区的互斥性了.要加锁.  我们先来看看`class mutex`. 

```cpp
#include<thread>
#include<vector>
#include<mutex>
#include<iostream>

using namespace std;

int main()
{
	mutex mtx;
	size_t size = 0;
	thread t1(
		[&size, &mtx]() {
			for (size_t i = 0; i < 100000; ++i)
			{
				mtx.lock();
				++size;
				mtx.unlock();
			}
		}
	);

	thread t2(
		[&size, &mtx]() {
			for (size_t i = 0; i < 100000; ++i)
			{
				mtx.lock();
				++size;
				mtx.unlock();
			}
		}
	);

	t1.join();
	t2.join();

	cout << size << endl;
	return 0;
}
```

```shell
200000

E:\C language new project\routine\thread\x64\Debug\thread.exe (进程 28544)已退出，代码为 0 (0x0)。
按任意键关闭此窗口. . .
```

好的, 现在让我们使用一下函数指针

```cpp
#include<thread>
#include<vector>
#include<mutex>
#include<iostream>

using namespace std;

// 不加下划线会和标准库冲突
void count__(size_t& size, mutex& mtx)
{
	for (size_t i = 0; i < 100000; ++i)
	{
		mtx.lock();
		++size;
		mtx.unlock();
	}
}

int main()
{
	size_t x = 0;
	mutex mtx;
	thread t1(count__, x, mtx);
	thread t2(count__, x, mtx);
	t1.join();
	t2.join();
	cout << x << endl;
	return 0;
}
```

编译这份代码, 会发生错误.     为什么呢? 因为锁没有拷贝构造, 因为`thread`的构造函数内部存在完美转发, 而完美转发为了保持数据的原有属性, 需要对其进行拷贝.   底层太过复杂, 我们这里说不清楚

我们可以实验一下

```cpp
template<class... Args>
void _func(Args... args)
{

}


template<class... Args>
void func(Args&&... args)
{
	//_func(forward<Args>(args)...);
}



int main()
{
	test t;
	cout << "====" << endl;
	func(t);
	return 0;
}
```

```shell
# 没有使用完美转发的情况
test()
====

E:\C language new project\routine\thread\x64\Debug\thread.exe (进程 26936)已退出，代码为 0 (0x0)。
按任意键关闭此窗口. . .
```

```shell
# 使用了之后
test()
====
test(const test& that)

E:\C language new project\routine\thread\x64\Debug\thread.exe (进程 30504)已退出，代码为 0 (0x0)。
按任意键关闭此窗口. . .
```

所以, 完美转发底层必然会进行一次拷贝.  它的具体底层我们不深究,   为此, 我们可以使用`ref`模版函数, 它可以让数据一直以左值引用属性向下传递, 这能避开拷贝, `ref`被称为引用适配器.

```cpp
int main()
{
	test t;
	cout << "====" << endl;
	func(ref(t));
	return 0;
}
```

```shell
test()
====

E:\C language new project\routine\thread\x64\Debug\thread.exe (进程 17456)已退出，代码为 0 (0x0)。
按任意键关闭此窗口. . .
```

好的, 现在我们回过头去, 把之前的代码改一下.

```cpp
// 不加下划线会和标准库冲突
void count__(size_t& size, mutex& mtx)
{
	for (size_t i = 0; i < 100000; ++i)
	{
		mtx.lock();
		++size;
		mtx.unlock();
	}
}

int main()
{
	size_t x = 0;
	mutex mtx;
	// 在构造函数的调用链内部, 参数会逐渐变为右值
	// ref模版函数可以让它们一直保持左值属性
	thread t1(count__, ref(x), ref(mtx));
	thread t2(count__, ref(x), ref(mtx));
	t1.join();
	t2.join();
	cout << x << endl;
	return 0;
}
```

```shell
200000

E:\C language new project\routine\thread\x64\Debug\thread.exe (进程 3276)已退出，代码为 0 (0x0)。
按任意键关闭此窗口. . .
```

比如, 我们可以实验一下, 既然, 函数参数不匹配, 我们把`count__`的第一个参数改成右值引用如何? 这样不就能匹配了.

```cpp
// 不加下划线会和标准库冲突
void count__(size_t&& size, mutex& mtx)
{
	for (size_t i = 0; i < 100000; ++i)
	{
		mtx.lock();
		++size;
		mtx.unlock();
	}
}

int main()
{
	size_t x = 0;
	mutex mtx;
	// 在构造函数的调用链内部, 参数会逐渐变为右值
	// ref模版函数可以让它们一直保持左值属性
	thread t1(count__, x, ref(mtx));
	thread t2(count__, x, ref(mtx));
	t1.join();
	t2.join();
	cout << x << endl;
	return 0;
}
```

```shell
0

E:\C language new project\routine\thread\x64\Debug\thread.exe (进程 25908)已退出，代码为 0 (0x0)。
按任意键关闭此窗口. . .
```

我们看到, 答案为零, 所以`count__`真正引用的, 是中间层的那个`x`, 而不是`main`里面的`x`.

![image-20250313085056968](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250313085057147.png)

`count__`真正用的是中间层的那个`obj1, obj2`, 不是`main`里面的`x, mtx`.

我们小节一下,  对于上面的这种通过构造函数间接传参的情况, (lambda表达式是直接捕捉参数, 没有经过中间层), 不要用引用, 而要用指针, 指针不会有这种问题, 它不会造成引用丢失的这种情况.

另外, 这个可调用对象也不能直接拿返回值, 如果真的需要返回值, 请使用输出性参数.

----------------

下面我们去看看其它的锁.

![image-20250313090039823](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250313090039888.png)

`recursive_mutex`是递归锁.  顾名思义, 就是用在递归函数里面的锁,  因为递归会自己调用自己, 所以容易死锁, 此时我们就可以使用递归锁, 它的实现可以理解为,  里面有一个递归计数器, 还会记录上一次线程的ID

假设线程 A 和线程 B，以及一个递归互斥锁 rmutex：

- 线程 A 调用 rmutex.lock()，计数器 = 1，锁归 A 拥有。
- 线程 A 再次调用 rmutex.lock()，计数器 = 2，仍然是 A 拥有。
- 线程 B 调用 rmutex.lock()，会被阻塞，因为锁已经被 A 占有。
- 线程 A 调用 rmutex.unlock()，计数器 = 1，锁仍未释放。
- 线程 A 再次调用 rmutex.unlock()，计数器 = 0，锁被释放，此时线程 B 才能尝试获取。

-------

接着是`timed_mutex`, 与普通的互斥锁相比, 它有两个额外的成员函数：`try_lock_for` 和 `try_lock_until`

`try_lock_for`, 的功能是指定一个时间长度, 在这个时间长度耗尽之前, 线程会不停尝试竞争锁,  得到了就会从该函数中退出, 并且返回真, 得不到就会一直尝试竞争, 当时间长度耗尽仍未获得锁, 就会从函数中退出, 并且返回假.

```cpp
// 适合需要在有限时间内尝试获取锁但不想无限等待的场景。例如，
// 某个操作有时间限制，超过时间就放弃锁定并执行其他逻辑。

#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>

std::timed_mutex tmutex;

void try_lock_example() {
    // 从执行到13行向后的200毫秒里, 会竞争锁
    if (tmutex.try_lock_for(std::chrono::milliseconds(200))) {
        std::cout << "锁获取成功\n";
        tmutex.unlock();
    } else {
        std::cout << "超时，锁获取失败\n";
    }
}

int main() {
    std::thread t1(try_lock_example);
    t1.join();
    return 0;
}
```

 `try_lock_until`则是指定一个时间点, 在这个时间点之前, 会一直尝试竞争锁, 返回机制和`try_lock_for`相同.

```cpp
// 适合需要基于绝对时间点（例如某个具体截止时刻）控制锁定行为的场景。
// 例如，任务必须在某个具体时间之前完成，否则放弃锁定。

#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>

std::timed_mutex tmutex;

void try_lock_until_example() {
    // 从现在向后的300毫秒, 一直竞争锁
    auto deadline = std::chrono::steady_clock::now() + std::chrono::milliseconds(300);
    if (tmutex.try_lock_until(deadline)) {
        std::cout << "锁获取成功\n";
        tmutex.unlock();
    } else {
        std::cout << "到达截止时间，锁获取失败\n";
    }
}

int main() {
    std::thread t1(try_lock_until_example);
    t1.join();
    return 0;
}
```

表示时间的相关类和函数定义在`chrono`命名域中, 有需要可以自取.

-----------------

下面我们看看锁守卫, 它们用的是`RAII`, 用来防止异常导致锁丢失, 从而引发的死锁. 

先来看`lock_guard`,  它只有构造析构这两种成员函数, 而且不支持拷贝.

```cpp
#include<thread>
#include<vector>
#include<mutex>
#include<iostream>

using namespace std;

std::mutex mtx;

void print_even(int x) {
    if (x % 2 == 0) std::cout << x << " 是偶数\n";
    else throw (std::logic_error("不是偶数"));
}

void print_thread_id(int id) {
    try {
        //std::lock_guard<std::mutex> lck(mtx);
        mtx.lock();
        print_even(id);
        mtx.unlock();
    }
    catch (std::logic_error&) {
        std::cout << "[异常捕获]\n";
    }
}

int main()
{
    std::thread threads[10];
    for (int i = 0; i < 10; ++i)
        threads[i] = std::thread(print_thread_id, i + 1);

    for (auto& th : threads) th.join();

    return 0;
}

```

比如在这份代码中, 一旦抛出异常就会跳过`unlock`, 从而造成死锁.

```shell
2 是偶数
[异常捕获]

E:\C language new project\routine\thread\x64\Debug\thread.exe (进程 26348)已退出，代码为 -1073741510 (0xc000013a)。
按任意键关闭此窗口. . .
```

而当使用`lock_guard`时, 对象声明周期结束自动释放锁, 就不会造成死锁.

```shell
[异常捕获]
[异常捕获]
6 是偶数
2 是偶数
8 是偶数
[异常捕获]
[异常捕获]
10 是偶数
[异常捕获]
4 是偶数

E:\C language new project\routine\thread\x64\Debug\thread.exe (进程 25860)已退出，代码为 0 (0x0)。
按任意键关闭此窗口. . .
```

 `lock_guard`写起来也很简单

```cpp
template<class Mutex>
struct lock_guard__
{
    lock_guard__(Mutex& mtx)
        :_mtx(mtx)
    {
        _mtx.lock();
    }

    ~lock_guard__()
    {
        _mtx.unlock();
    }

    lock_guard__(const lock_guard__<Mutex>& that) = delete;

private:
    Mutex& _mtx;
};
```

-----------

接下来看看`unique_lock`, `unique_lock`又加了几个成员函数, 使得其和锁的行为相同. 

它的构造函数很杂, 为了适配各种各样的锁

![image-20250313102147230](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250313102147326.png)

它可以支持手动加锁解锁.

![image-20250313102516910](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250313102516989.png)

#### condition_variable

接下里是条件变量. 

我们直接来看`wait`

```cpp
unconditional (1)	
    void wait (unique_lock<mutex>& lck);

predicate (2)	
    template <class Predicate>
        void wait (unique_lock<mutex>& lck, Predicate pred);
```

需要注意的是, 它只能用`unique_lock`来传锁, 这和条件变量的等待逻辑有关, 线程在被条件变量阻塞前, 必须要释放锁, 否则就会造成死锁, 我们在Linux那边详谈过这一点, 也就是说, `wait`内部是要手动释放锁的. 

现在我们临时中断一下, 我们来说一道例题, 这个例题在面试上很容易见到: 创建两个线程`t1, t2`, 让它们轮流打印`1, 2, 3, 4, 5...`, `t1`打印奇数, `t2`打印偶数. 

我们平常都对线程们一视同仁, 不管谁先谁后, 但这道题硬性规定了线程的打印先后, 这需要一定的技巧.   

我们先别一开始整得就这么难, 我们先让两个线程打印`1, 2, 3, 4, 5...`, 不在乎对应顺序

```cpp
int main()
{
	int x = 1;
	mutex __mtx;
	condition_variable cond;

	thread t2(
		[&]() {
			for (int i = 0; i < 10; ++i)
			{
				unique_lock<mutex> mtx(__mtx);
				cout << "[thread-" << 2 << "]info : " << x++ << endl;
				this_thread::sleep_for(std::chrono::milliseconds(100)); // 睡眠0.1秒
			}
		}
	);

	thread t1(
		[&]() {
			for (int i = 0; i < 10; ++i)
			{
				unique_lock<mutex> mtx(__mtx);
				cout << "[thread-" << 1 << "]info : " << x++ << endl;
				this_thread::sleep_for(std::chrono::milliseconds(100));
			}
		}
	);

	t1.join();
	t2.join();

	return 0;
}
```

```shell
[thread-1]info : 1
[thread-1]info : 2
[thread-1]info : 3
[thread-1]info : 4
[thread-1]info : 5
[thread-1]info : 6
[thread-1]info : 7
[thread-1]info : 8
[thread-1]info : 9
[thread-1]info : 10
[thread-2]info : 11
[thread-2]info : 12
[thread-2]info : 13
[thread-2]info : 14
[thread-2]info : 15
[thread-2]info : 16
[thread-2]info : 17
[thread-2]info : 18
[thread-2]info : 19
[thread-2]info : 20

E:\C language new project\routine\thread\x64\Debug\thread.exe (进程 15492)已退出，代码为 0 (0x0)。
按任意键关闭此窗口. . .
```

既然我们这里说的是条件变量, 那自然是要用条件变量解决这个问题. 我们要的效果是, 第一次打印必须由`t1`来执行, 第二次打印必须由`t2`来执行... 这里的言外之意就是如果`t2`尝试进行第一次打印, 它必须被条件变量所阻塞, 如果`t1`尝试进行第二次打印, 它必须被条件变量所阻塞, 也就是说, 解决这个问题的关键是让条件变量轮询阻塞两个线程, 为此, 我们可以引入一个`flag`, 因为这里只有两个线程, 所以`flag`有两种状态就已经够用了, 因此我们可以把`flag`定义为布尔类型, 我们把`wait`放在以`flag`为逻辑判断的`if`语句中, 当`falg == flase`, 那就能让一个进程进入`if`语句, 从而被阻塞, 当`flag == true`, 那就让另一个进程进入`if`语句被阻塞, 线程的每一次打印, 都会改变`flag`的状态.

```cpp
int main()
{
	int x = 1;
	mutex __mtx;
	bool flag = true;
	condition_variable cond;

	thread t2(
		[&]() {
			for (int i = 0; i < 10; ++i)
			{
				unique_lock<mutex> mtx(__mtx);
				if (flag == true)
					cond.wait(mtx);
				cout << "[thread-" << 2 << "]info : " << x++ << endl;
				flag = !flag;
				cond.notify_one(); // 唤醒一个线程
				this_thread::sleep_for(std::chrono::milliseconds(100)); // 睡眠0.1秒
			}
		}
	);

	thread t1(
		[&]() {
			for (int i = 0; i < 10; ++i)
			{
				unique_lock<mutex> mtx(__mtx);
				if (flag == false)
					cond.wait(mtx);
				cout << "[thread-" << 1 << "]info : " << x++ << endl;
				flag = !flag;
				cond.notify_one();
				this_thread::sleep_for(std::chrono::milliseconds(100));
			}
		}
	);

	t1.join();
	t2.join();

	return 0;
}
```

```shell
[thread-1]info : 1
[thread-2]info : 2
[thread-1]info : 3
[thread-2]info : 4
[thread-1]info : 5
[thread-2]info : 6
[thread-1]info : 7
[thread-2]info : 8
[thread-1]info : 9
[thread-2]info : 10
[thread-1]info : 11
[thread-2]info : 12
[thread-1]info : 13
[thread-2]info : 14
[thread-1]info : 15
[thread-2]info : 16
[thread-1]info : 17
[thread-2]info : 18
[thread-1]info : 19
[thread-2]info : 20

E:\C language new project\routine\thread\x64\Debug\thread.exe (进程 16432)已退出，代码为 0 (0x0)。
按任意键关闭此窗口. . .
```

又或者, 我们可以把`flag`的形式换一下, 既然, `t1`打印的是奇数, 那么, 当`x`是偶数时, 它就不能打印, 它就要被阻塞, 它就要进入`if`语句, `t2`打印的是偶数, 那么, 当`x`是奇数时, 它就不能打印, 它就要把打印的次数让给另一个线程, 它被阻塞, 其获得的锁被释放, 另一个线程就能获得该锁, 就能进行打印.

```cpp
int main()
{
	int x = 1;
	mutex __mtx;
	condition_variable cond;

	thread t2(
		[&]() {
			for (int i = 0; i < 10; ++i)
			{
				unique_lock<mutex> mtx(__mtx);
				if (x % 2 != 0)
					cond.wait(mtx);
				cout << "[thread-" << 2 << "]info : " << x++ << endl;
				cond.notify_one(); // 唤醒一个线程
				this_thread::sleep_for(std::chrono::milliseconds(100)); // 睡眠0.1秒
			}
		}
	);

	thread t1(
		[&]() {
			for (int i = 0; i < 10; ++i)
			{
				unique_lock<mutex> mtx(__mtx);
				if (x % 2 == 0)
					cond.wait(mtx);
				cout << "[thread-" << 1 << "]info : " << x++ << endl;
				cond.notify_one();
				this_thread::sleep_for(std::chrono::milliseconds(100));
			}
		}
	);

	t1.join();
	t2.join();

	return 0;
}
```

上面, 我们从逻辑层面解释了为什么要这样写, 接下来, 让我们结合具体场景, 进行分类讨论.

我们假设`t1`先运行, (当然, 这可能性比较小, 因为我们先创建了`t2`, 不过也是存在这种可能的). `t1`先抢到锁, 然后它就在那里判断`if`条件, 发现`x`不是偶数, 所以跳过了`if`语句, 成功打印, 并且对`x`进行了加加操作,           现在`x`就变成了偶数, 之后, 即使`t2`还是没有开始运行, (这种情况可能性就更小了, 可能是时间片用完了, 或者还是线程没有创建完), `t1`又抢到锁, 但因为现在`x`是偶数, 所以一定会进入`if`语句, 从而被阻塞, 当然它阻塞前肯定也报锁释放了, 总之`t1`现在肯定是打印不了`x`的.

对于`t2`来说, 它要么因为调度问题迟迟没有去竞争锁, ,或者在锁那里阻塞, 都没关系, `t1`现在已经释放了锁, `t2`就可以进入了, 而且因为现在`x`是偶数, 所以`t2`不会进入`if`, 它会顺利的执行打印, 并对`x`加加.    接着是`t2`唤醒`t1`, 现在我们假设`t1`因为唤醒需要时间, 没有第一时间抢到锁, 那也没事, 就算`t2`先抢到锁, 成功进入了, 它也会进入`if`, 阻塞, 释放锁, 让`t1`进去....

假设`t2`先运行, 要么它干脆没抢到锁, 锁被`t1`抢到了, 就算抢到了, 由于一开始`x`是奇数, 它也会进`if`, 重新阻塞, 当然, 阻塞前还是会释放锁, `t1`还是能进来.然后继续该怎么走就怎么走. 

总之肯定是两个线程轮流来.

当然, 对于这道题来说, 可能还有其他解决方案, 但这些方案它可能要么不可靠(用`sleep`调节节奏), 要么过于复杂(引入多个条件变量, 过于复杂也会降低可靠性).

当然, 我们的这个代码还有些缺陷. 比如, 我们可以本着严谨的态度, 把`if`改成`while`, 提防可能存在的伪唤醒问题. 另外, 这两个线程可以说是相互依赖的, 当其中一个线程不知道为什么不运行了, 就很有可能出现死锁, 我们这里就不考虑这么细了.

## atomic

C++11引入了原子操作. 在说原子操作之前, 我们先回过头来看看之前的一份代码

```cpp
int main()
{
	size_t x = 0;
	thread t1(
		[&]() {
			for (size_t i = 0; i < 100000; ++i)
			{
				++x;
			}
		}
	);

	thread t2(
		[&]() {
			for (size_t i = 0; i < 100000; ++i)
			{
				++x;
			}
		}
	);

	t1.join();
	t2.join();

	cout << x << endl;

	return 0;
}
```

```shell
110941

E:\C language new project\routine\thread\x64\Debug\thread.exe (进程 22848)已退出，代码为 0 (0x0)。
按任意键关闭此窗口. . .
```

很明显, 这份代码有线程安全问题. 因为普通的加加很明显并不是原子化的操作. 所以我们要加锁.

```cpp
int main()
{
	size_t x = 0;
	mutex mtx__;
	thread t1(
		[&]() {
			for (size_t i = 0; i < 100000; ++i)
			{
				unique_lock<mutex> lock(mtx__);
				++x;
			}
		}
	);

	thread t2(
		[&]() {
			for (size_t i = 0; i < 100000; ++i)
			{
				unique_lock<mutex> lock(mtx__);
				++x;
			}
		}
	);

	t1.join();
	t2.join();

	std::cout << x << std::endl;

	return 0;
}
```

```shell
200000

E:\C language new project\routine\thread\x64\Debug\thread.exe (进程 20004)已退出，代码为 0 (0x0)。
按任意键关闭此窗口. . .
```

但这里就会出现一种效率上的问题.    `++x`这个操作本身非常简单, 所以就会出现一种情况, 就是线程要被反复的阻塞, 唤醒, 可能`t2`刚执行完加加, 释放锁, `t1`立刻进入, `t2`尝试竞争锁, 没有抢到, 所以阻塞了, `t1`又立刻加加完, 释放了锁, 此时`t2`还未被彻底阻塞, 就马上要被唤醒. 

或者来个生活场景, 张三李四是一个小组, 他们正在赶一个项目, 张三会的, 李四不会, 李四会的, 张三不会, 所以他们要轮流做项目, 做到了半夜, 张三对李四说这是我会的部分, 你去睡觉吧, 李四刚进卧室, 衣服还没脱完, 张三就说, 轮到你了, 赶紧过来, 于是张三就马上把衣服再穿上, 赶紧过去, 之后同样的事还会再发生一遍, 只不过张三和李四身份互换了. 

我们上面也说过, 对于这种情况, 我们需要使用自旋锁, 但可惜的是, C++没有自旋锁, 所以我们可以把`try_lock()`包进循环.  模拟出自旋锁. 

```cpp
int main()
{
	size_t x = 0;
	mutex mtx__;
	thread t1(
		[&]() {
			for (size_t i = 0; i < 100000; ++i)
			{
				unique_lock<mutex> mtx(mtx__, defer_lock);   // 构造时不竞争锁
				while (!mtx.try_lock());				   // 抢到锁跳出循环
				++x;
			}
		}
	);

	thread t2(
		[&]() {
			for (size_t i = 0; i < 100000; ++i)
			{
				unique_lock<mutex> mtx(mtx__, defer_lock);
				while (!mtx.try_lock());
				++x;
			}
		}
	);

	t1.join();
	t2.join();

	cout << x << endl;

	return 0;
}
```

```shell
200000

E:\C language new project\routine\thread\x64\Debug\thread.exe (进程 9060)已退出，代码为 0 (0x0)。
按任意键关闭此窗口. . .
```

之前我们说`yield()`的时候也说过这种事, 所以这里也可以把`yield()`加上.

```cpp
int main()
{
	size_t x = 0;
	mutex mtx__;
	thread t1(
		[&]() {
			for (size_t i = 0; i < 100000; ++i)
			{
				unique_lock<mutex> mtx(mtx__, defer_lock);						// 构造时不竞争锁
				while (!mtx.try_lock())  this_thread::yield();					// 抢到锁跳出循环
				++x;
			}
		}
	);

	thread t2(
		[&]() {
			for (size_t i = 0; i < 100000; ++i)
			{
				unique_lock<mutex> mtx(mtx__, defer_lock);
				while (!mtx.try_lock())  this_thread::yield();
				++x;
			}
		}
	);

	t1.join();
	t2.join();

	cout << x << endl;

	return 0;
}
```

C++标准库为什么没有直接提供自旋锁？原因在于，相比自旋锁，`std::atomic`能更好地胜任原子操作的任务。对于绝大多数内置类型（如`int、bool`），`std::atomic`底层依赖无锁编程，利用硬件的原子指令实现高效操作。而对于更大体量的自定义类型或某些极端内置类型（如`int128_t`），当硬件不支持直接原子操作时，`std::atomic`会退化为锁机制。换句话说，`std::atomic`会根据类型的“轻重”自适应地选择实现方式：轻量级类型用无锁编程，重量级类型则使用锁保护, 无锁编程的效率高于互斥锁. 

我们可以把要操作的变量扔到`atomic`里面, 然后`class atomic`里面有一堆重载和常见运算的接口, 可以对里面的内置类型变量进行操作, 

![image-20250314170551751](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250314170551856.png)

我们可能更多用的是下图的运算符重载

![image-20250314170643605](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250314170643666.png)

```cpp
int main()
{
	size_t x__ = 0;
	atomic<size_t> x(x__);
	mutex mtx__;
	thread t1(
		[&]() {
			for (size_t i = 0; i < 100000; ++i)
			{
				++x;
			}
		}
	);

	thread t2(
		[&]() {
			for (size_t i = 0; i < 100000; ++i)
			{
				++x;
			}
		}
	);

	t1.join();
	t2.join();

	cout << x << endl;

	return 0;
}
```

```shell
200000

E:\C language new project\routine\thread\x64\Debug\thread.exe (进程 27804)已退出，代码为 0 (0x0)。
按任意键关闭此窗口. . .
```

需要注意的是, C接口很可能适应不了被`atomic`包的对象, 额, 我们把`atomic`里面包的那个对象叫负载, 对于C接口来说, 需要调用`load`成员函数, 把负载提取出来.   还有`store`, 用来修改值, 原子化操作.

```cpp
int main()
{
	size_t x__ = 0;
	atomic<size_t> x(x__);
	mutex mtx__;
	thread t1(
		[&]() {
			for (size_t i = 0; i < 100000; ++i)
			{
				++x;
			}
		}
	);

	thread t2(
		[&]() {
			for (size_t i = 0; i < 100000; ++i)
			{
				++x;
			}
		}
	);

	t1.join();
	t2.join();

	//cout << x << endl;
	printf("%d\n", x.load());

	return 0;
}
```

---------------

无锁编程, 用的是`CAS`操作, `CAS`是` Compare & Swap`的缩写. 陈皓大佬曾在自己的博客网站"酷客"上写过相应的文章, 我们这里就以他的文章来了解一下无锁编程,  [无锁队列的实现](https://coolshell.org/articles/8239.html/)

![image-20250314173821997](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250314173822110.png)

`CAS`操作是一个原子操作, 它的内部逻辑以C语言的形式来呈现(只是说来呈现, 但并不是真的是这样实现的, 它是依靠硬件直接实现的)如下

```cpp
bool compare_and_swap (int *addr, int oldval, int newval)
{
  if ( *addr != oldval ) {
      return false;
  }
  *addr = newval;
  return true;
}
```

其中, `reg`是我们要修改的变量, `oldval`是这个变量预期中的原有值, `newval`是变量预期的新值.   当变量的值和预期的原值不相同, 就意味着别的线程改过这个变量了, 此时我现在就不能继续改变变量, 于是直接返回, 这样就能避免数据不一致问题的出现, 当然, 此时你可能会问, 返回是返回了, 但我还没修改变量呀, 这个你不用担心, `compare_and_swap`外层还有一个循环, 这个循环会对`newval`和`oldval`进行修正, 然后重新再进行`CAS`操作, 直到, 操作成功, 返回真退出循环.

对于`++x`来说, 使用`CAS`方式操作大概是这样的(伪代码)

```cpp
size_t oldval = x;
size_t newval = x;

do
{
    oldval = x;
    ++newval;
}while(!CAS(&x, oldval, newval));
```

首先因为`oldval, newold`是局部变量, 它们不是共享资源, 所以是线程安全的, 因此对它们的操作都不会出现问题. 假设, 现在`x == 2`, `t1`和`t2`都在执行`++x`, 首先是`t1`先运行, `oldval == 2`, `newval == 3`, 然后`t1`就被切走了, `t2`再来, `oldval == 2, newval == 3`,它的`CAS`执行成功了, 跳出循环, 于是现在`x == 3`, 接着`t1`又回来运行了, 它进入`CAS` , 发现`x`不等于预期的值`oldval == 2`, 所以返回假, 就会重新进入循环, 对`oldval newval`进行调整, `oldval == 3, newold = 4`, 这次`CAS`执行成功, 于是就跳出了. 

各类平台的`CAS`各有不同, 对于我们来说, 当然应该用跨平台的C++`atomic`(<atomic\>头文件中除了`class atomic`, 还有很多用于原子操作的独立函数)

![image-20250314185033840](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250314185033991.png)

我们先用`windows`的`CAS`

```cpp
#include<windows.h> 
InterlockedCompareExchange ( __inout LONG volatile *Target,  // 要修改变量的地址
                                 __in LONG Exchange,          // 目标值
                                 __in LONG Comperand);		  // 原来的预期值
```

```cpp
int main()
{
	volatile LONGLONG x = 0;  // 类型适配
	//atomic<size_t> x(x__);
	mutex mtx__;
	thread t1(
		[&]() {
			for (size_t i = 0; i < 100000; ++i)
			{
				LONGLONG oldval = x;
				LONGLONG newval = x;
				do
				{
					oldval = x;
					newval = oldval + 1;
				} while (InterlockedCompareExchange64(&x, newval, oldval) != oldval);
				// 我这里是64位环境, size_t是64位整数, 所以应该用64这个版本
				// InterlockedCompareExchange64返回的是自身还未执行前的x
				// 当 x != oldval, 说明之前已经有别的线程改过值了, 导致 x 
				// 已经不是我们期望的原有值, 这意味着CSA操作失败, 需要重试
			}
		}
	);

	thread t2(
		[&]() {
			for (size_t i = 0; i < 100000; ++i)
			{
				LONGLONG oldval = x;
				LONGLONG newval = x;
				do
				{
					oldval = x;
					newval = oldval + 1;
				} while (InterlockedCompareExchange64(&x, newval, oldval) != oldval);
			}
		}
	);

	t1.join();
	t2.join();

	cout << x << endl;

	return 0;
}
```

```shell
200000

E:\C language new project\routine\thread\x64\Debug\thread.exe (进程 3400)已退出，代码为 0 (0x0)。
按任意键关闭此窗口. . .
```

然后用`C++`的, 对于`VS`来说, 这其实是`InterlockedCompareExchange`系列函数的封装, 另外要注意的是, `C++`这边要以`atomic`对象的形式传入.

```cpp
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
```

```shell
200000

E:\C language new project\routine\thread\x64\Debug\thread.exe (进程 30196)已退出，代码为 0 (0x0)。
按任意键关闭此窗口. . .
```

最后, 我们回到  无锁队列的实现   这篇文章, 来看看无锁队列如何实现插入, (伪代码)

```cpp
EnQueue(Q, data) //进队列
{
    //准备新加入的结点数据
    n = new node();
    n->value = data;
    n->next = NULL;

    do {
        p = Q->tail; //取链表尾指针的快照
    } while( CAS(p->next, NULL, n) != TRUE); 
    //while条件注释：如果没有把结点链在尾指针上，再试

    CAS(Q->tail, p, n); //置尾结点 tail = n;
}
```

首先新链节点的准备阶段是线程安全的, 因为`new, malloc`它们内部是有锁的, 可以实现原子操作.    然后我们要画图, 假设`t1`先运行

![image-20250314194850316](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250314194850520.png)

`t1`被切走了, `t2`运行

![image-20250314195030901](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250314195031053.png)

继续执行`CAS`, 执行成功, 跳出循环, 切走

![image-20250314195258904](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250314195259073.png)

`t1`运行, 

![image-20250314195344256](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250314195344395.png)

`[3]`后不为空, 操作失败, 继续循环, `p`还是`[3]`, 操作失败, 继续循环, 切走

`t2`修改`tail`, 切走, 

![image-20250314195646244](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250314195646386.png)

`p`是`[4]`, 操作成功, 跳出循环

![image-20250314195820610](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250314195820740.png)

`t1`修改`tail`

![image-20250314195951372](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250314195951503.png)

从上面的过程, 我们还可以看到, 如果出来的线程不修改`tail`, 其它线程就会一直被困在`do while`里, 所以第二个`CAS`不用加循环, 一定成功. 

当然, 上面的代码其实还是存在一定问题的, 所以还可以进一步优化, 但这里我们就不继续说了, 无锁编程是了解内容. 以我们的技术储备, 就算真的要写无锁编程, 公司也不会交给我们.     无锁编程在逻辑上本身就是锁, 它的原子性不依赖于外在锁的保证. 

# end

