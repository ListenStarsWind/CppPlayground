# exception

在C语言中, 对错误的传统处理方式包括两种, 一是终止程序, 如`assert`, 这种处理方式动静有些太大了, 往往让人难以接受, 并且`assert`只在`Debug`版里才能起作用. 二是返回错误码, 也是C语言中主要的错误处理方式, 通过将各种错误进行归纳, 以错误码的方式进行呈现, 供程序员自己查询.

C++于是提出了新的错误处理方式, 即异常处理.

-----------------

异常机制的标志性特征即是`try   catch`语句, 下面我们通过代码学习异常的用法.

```cpp
#include<iostream>

using namespace std;

double division(int x, int y)
{
	if (y == 0)
	{
		// throw关键字可以抛出任意类型的异常
		// 在这里, 对象成为了异常信息的载体
		throw "非法的操作数";
	}
	else
	{
		return static_cast<double>(x) / static_cast<double>(y);
	}
}

void func()
{
	int x, y;
	cin >> x >> y;
	cout << division(x, y) << endl;
}

int main()
{
	func();
	return 0;
}
```

异常被抛出, 就需要接收, 不接受会造成程序的终止

![image-20250301095250564](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250301095250638.png)

异常的接收可以在异常抛出后调用链的任意位置上,在上面的代码中,  会形成三个函数栈帧, 它们分别代表`division, func, main`, 你可以在任意位置上捕获异常, 异常的捕获使用`try catch`, 其捕获的具体位置一般有两种, 一是就近捕获, 就在错误的附近捕获异常, 二是在最外层捕获, 需要注意的是, 只有类型相同才能捕获成功, 这种类型相同是强相同, 即是构造函数支持构造, 也不行, 比如, 对于`const char*`的异常, 不能拿`string`接收, `try catch`不能用`auto`

![image-20250301100354578](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250301100354794.png)

当异常被抛出后, 它会直接跳到`catch`, 不执行中间过程的代码

```cpp
class A
{
public:
	A()
	{
		cout << "A()" << endl;
	}

	~A()
	{
		cout << "~A()" << endl;
	}
};

void func()
{
	int x, y; 
	cin >> x >> y;
	cout << division(x, y) << endl;

	A a;
}
```

![image-20250301101221557](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250301101221604.png)

在这里, `A a;`这一行被跳过了, 因而没有执行构造函数, 更没有执行析构函数.

需要注意的是, 异常并不是一下子直接跳到`catch`的, 二是会对跳过的函数栈帧进行释放, 其外在表现就是栈帧中的局部对象仍会被析构

```cpp
void func()
{
	int x, y; 
	cin >> x >> y;
	A a;
	cout << division(x, y) << endl;
}
```

![image-20250301101955505](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250301101955563.png)

异常的捕获是一个栈展开的过程, 如下图所示, 即在之后的调用链栈帧中寻找`catch`, 找到合适的就处理, 如果一直找不到就会跳出`main`函数, 或者换种说法, 程序退出

![image-20250301102526652](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250301102526716.png)

如果抛出异常的附近就有对应的`catch`, 它就会选择最近的合适`catch`, 并继续执行后续代码

```cpp
void func()
{
	int x, y; 
	cin >> x >> y;
	A a;
	try
	{
		cout << division(x, y) << endl;
	}
	catch (const char* str)
	{
		cout << str << endl;
	}
	cout << "xchwesbhcb" << endl;
}
```

![image-20250301103024993](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250301103025041.png)

异常的传递过程类似于函数的传值返回

```cpp
class A
{
public:
	A()
	{
		cout << "A()" << endl;
	}

	A(const A& _a)
	{
		cout << "A(const A&)" << endl;
	}

	~A()
	{
		cout << "~A()" << endl;
	}
};

double division(int x, int y)
{
	if (y == 0)
	{
		// throw关键字可以抛出任意类型的异常
		// 在这里, 对象成为了异常信息的载体
		//throw "非法的操作数";
		A _a;
		throw _a;
		// _a是局部对象, 栈帧销毁亦会被销毁
	}
	else
	{
		return static_cast<double>(x) / static_cast<double>(y);
	}
}

void func()
{
	int x, y; 
	cin >> x >> y;
	//A a;
	try
	{
		cout << division(x, y) << endl;
	}
	catch (const char* str)
	{
		cout << str << endl;
	}
	cout << "xchwesbhcb" << endl;
}

int main()
{
	try
	{
		func();
	}
	catch (const char* str)
	{
		cout << str << endl;
	}
	catch (A _b)
	{

	}
	return 0;
}
```

![image-20250301104439717](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250301104439776.png)

一般情况下, 程序是处于一个死循环中的, 当用户触发一个事件时, 就会调用对应的子功能, 在形式上就是某个具体的函数, 一个子功能异常, 不代表其它子功能也异常, 所以可以把该异常写到日志中去, 然后继续进行循环, 但由于异常可以以任意类型抛出,  所以当没有对应类型的`catch`时,  程序就会退出, 这种动静也是太大了, 所以对于异常的接收, 有一个最终解决方案, 那就是使用`...`, 代表接收任意类型的异常, 避免程序退出, 出现这种情况意味着项目组里面有人乱抛异常, 需要好好查查. 

```cpp
double division(int x, int y)
{
	if (y == 0)
	{
		throw 1;
	}
	else
	{
		return static_cast<double>(x) / static_cast<double>(y);
	}
}


int main()
{
	try
	{
		func();
	}
	catch (const char* str)
	{
		cout << str << endl;
	}
	catch (A _b)
	{

	}
	catch (...)
	{
		cout << "未知的异常" << endl;
	}
	return 0;
}
```

![image-20250301110118093](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250301110118141.png)

--------------------

一个较大的项目, 可能会有多个小组的参与, 如果各个小组之间没有约定统一的异常抛出规范, 异常的接收就会非常困难, 为了解决这种问题, 就需要引入异常真正的核心玩法,  那就是抛出派生类对象, `catch`用基类捕获.  

我们可以最开始定义一个公共的异常基类, 然后分发给各个小组, 各个小组再依据实际情况, 对基类进行重写, 从而在各个小组中实现异常的多态玩法, 

```cpp
#include<string>
#include<iostream>
#include<windows.h>

using namespace std;

// 服务器开发中通常使用的异常继承体系
class Exception
{
public:
	Exception(const string& errmsg, int id)
		:_errmsg(errmsg)
		, _id(id)
	{
	}
	virtual string what() const
	{
		return _errmsg;
	}
protected:
	string _errmsg;
	int _id;
};
class SqlException : public Exception
{
public:
	SqlException(const string& errmsg, int id, const string& sql)
		:Exception(errmsg, id)
		, _sql(sql)
	{
	}
	virtual string what() const
	{
		string str = "SqlException:";
		str += _errmsg;
		str += "->";
		str += _sql;
		return str;
	}
private:
	const string _sql;
};
class CacheException : public Exception
{
public:
	CacheException(const string& errmsg, int id)
		:Exception(errmsg, id)
	{
	}
	virtual string what() const
	{
		string str = "CacheException:";
		str += _errmsg;
		return str;
	}
};
class HttpServerException : public Exception
{
public:
	HttpServerException(const string& errmsg, int id, const string& type)
		:Exception(errmsg, id)
		, _type(type)
	{
	}
	virtual string what() const
	{
		string str = "HttpServerException:";
		str += _type;
		str += ":";
		str += _errmsg;
		return str;
	}
private:
	const string _type;
};
void SQLMgr()
{
	srand(time(0));
	if (rand() % 7 == 0)
	{
		throw SqlException("权限不足", 100, "select * from name = '张三'");
	}
	//throw "xxxxxx";
}
void CacheMgr()
{
	srand(time(0));
	if (rand() % 5 == 0)
	{
		throw CacheException("权限不足", 100);
	}
	else if (rand() % 6 == 0)
	{
		throw CacheException("数据不存在", 101);
	}
	SQLMgr();
}
void HttpServer()
{
	// ...
	srand(time(0));
	if (rand() % 3 == 0)
	{
		throw HttpServerException("请求资源不存在", 100, "get");
	}
	else if (rand() % 4 == 0)
	{
		throw HttpServerException("权限不足", 101, "post");
	}
	CacheMgr();
}
int main()
{
	while (1)
	{
		Sleep(500);
		try {
			HttpServer();
		}
		catch (const Exception& e) // 这里捕获父类对象就可以
		{
			// 多态
			cout << e.what() << endl;
		}
		catch (...)
		{
			cout << "Unkown Exception" << endl;
		}
	}
	return 0;
}
```

在上面的代码中, 我们简单模拟了服务器开发的异常继承体系,  可以看到, 上面有三个模块, 数据库, 缓存, http, 他们各自对异常基类进行了继承, 加上了自己组的信息, 并实现了多态处理, 这样异常捕捉之后看的就非常清楚

```log
HttpServerException:get:请求资源不存在
HttpServerException:get:请求资源不存在
HttpServerException:get:请求资源不存在
HttpServerException:get:请求资源不存在
HttpServerException:get:请求资源不存在
HttpServerException:get:请求资源不存在
CacheException:数据不存在
CacheException:数据不存在
CacheException:权限不足
CacheException:权限不足
HttpServerException:post:权限不足
HttpServerException:post:权限不足
HttpServerException:get:请求资源不存在
HttpServerException:get:请求资源不存在
HttpServerException:get:请求资源不存在
HttpServerException:get:请求资源不存在
HttpServerException:get:请求资源不存在
HttpServerException:get:请求资源不存在
HttpServerException:get:请求资源不存在
HttpServerException:get:请求资源不存在
SqlException:权限不足->select * from name = '张三'
SqlException:权限不足->select * from name = '张三'
CacheException:权限不足
CacheException:权限不足
CacheException:数据不存在
CacheException:数据不存在
CacheException:权限不足
CacheException:权限不足
HttpServerException:post:权限不足
HttpServerException:post:权限不足
HttpServerException:post:权限不足
HttpServerException:post:权限不足
HttpServerException:post:权限不足
HttpServerException:post:权限不足
HttpServerException:get:请求资源不存在
HttpServerException:get:请求资源不存在
HttpServerException:get:请求资源不存在
HttpServerException:get:请求资源不存在
HttpServerException:get:请求资源不存在
CacheException:数据不存在
CacheException:数据不存在
SqlException:权限不足->select * from name = '张三'
SqlException:权限不足->select * from name = '张三'
HttpServerException:post:权限不足
HttpServerException:post:权限不足
HttpServerException:post:权限不足
HttpServerException:post:权限不足
```

一般来说, 异常基类都会有两个成员变量, 一个是错误码, 一个是错误的相关描述.  

这里的错误码主要是为了快速确定某种特定的错误, 我们可以建立两级`catch`, 首先是就近捕获, 快速确定错误种类, 看看有没有相应的补救措施, 有就执行, 没有就重抛异常, 来到外层`catch`, 跳过这个子功能.

比如, 对于微信来说, 发送一个消息, 发现报红色感叹号了, 这说明别人把你给拉黑了, 对待这种异常, 我们都不需要写到日志了, 只需要对用户提示一下; 又或者, 网络不好, 信息发出去之后转圈, 此时我们可以重试几下, 实在不行再向用户发个提示, 然后重抛异常, 来到最外层, 跳过这个子任务. 

C++标准库中有自己的异常继承体系, 所以对于C++标准库中的异常, 我们都是使用`exception`

![image-20250301115850503](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250301115850589.png)

```cpp
int main()
{
	try {
		vector<int> v(10, 5);
		// 这里如果系统内存不够也会抛异常
		v.reserve(1000000000);
		// 这里越界会抛异常
		v.at(10) = 100;
	}
	catch (const exception& e) // 这里捕获父类对象就可以
	{
		cout << e.what() << endl;
	}
	catch (...)
	{
		cout << "Unkown Exception" << endl;
	}
	return 0;
}
```

常见的就是`bad_alloc`, 分配(内存)异常, 和 `out_of_range`, 越界异常. 

不过, 据说C++的异常继承体系设计的并不好,  所以, 实际情况是, 大家自己设计`exception`继承体系, 各用各的.

---------------

异常有重抛机制,  这种机制主要有两种作用, 一是识别是否是可以补救的具体错误, 如果是, 执行相应的措施, 二是因为异常会跳代码, 所以可能会造成某些资源申请, 但因为异常而跳过了释放, 但其实上, 只有前一种才是真正主要的, 第二种有更好的解决方案, 即所谓的`RAII`技术, 等会我们会在智能指针重新见到它.

第一种我们已经说过很多遍了, 下面为我们主要说第二种, 说说它为什么用异常捕捉的方法不好

```cpp
double division(int x, int y)
{
	if (y == 0)
	{
		throw "非法的操作数";
	}
	else
	{
		return static_cast<double>(x) / static_cast<double>(y);
	}
}

void func()
{
	int x, y; 
	int* arry = new int[10];
	cin >> x >> y;
	/*try
	{
		cout << division(x, y) << endl;
	}
	catch (const char* str)
	{
		cout << str << endl;
	}*/
	cout << division(x, y) << endl;
	cout << "xchwesbhcb" << endl;
	delete[] arry;
}

int main()
{
	try
	{
		func();
	}
	catch (const char* str)
	{
		cout << str << endl;
	}
	catch (...)
	{
		cout << "未知的异常" << endl;
	}
	return 0;
}
```

![image-20250301123633526](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250301123633609.png)

我们看到, 异常的捕获破坏了代码的执行顺序, 由于直接跳过了`delete`, 所以产生了内存泄露, 所以我们就可以再定义一个就近捕获

```cpp
void func()
{
	int x, y; 
	int* arry = new int[10];
	cin >> x >> y;
	try
	{
		cout << division(x, y) << endl;
	}
	catch (const char* str)
	{
		delete[] arry;
		cout << "kxhsabjhc" << endl;
		throw str;     // 重抛异常   
	}
	//cout << division(x, y) << endl;
	cout << "xchwesbhcb" << endl;
	delete[] arry;
}
```

![image-20250301124630981](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250301124631052.png)

也有这样写的

```cpp
void func()
{
	int x, y; 
	int* arry = new int[10];
	cin >> x >> y;
	try
	{
		cout << division(x, y) << endl;
	}
	catch (...)
	{
		delete[] arry;
		cout << "kxhsabjhc" << endl;
		// 这相当于捕获到什么就抛什么
		throw;     // 重抛异常   
	}
	//cout << division(x, y) << endl;
	cout << "xchwesbhcb" << endl;
	delete[] arry;
}
```

![image-20250301124844139](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250301124844213.png)

但实际上没有这么简单, 首先, `new`本身是有可能抛异常的, 其次, 当多个`new`放在一块, 就会产生很多种情况, 对于这些情况, 我们需要分情况具体应对

```cpp
void func()
{
	int x, y; 
	int* arry1 = nullptr;
	int* arry2 = nullptr;
	try
	{
		arry1 = new int[10];
	}
	catch (const exception& e)
	{
		// 申请失败
		// 不用释放
	}
	try
	{
		arry2 = new int[10];
	}
	catch (const exception& e)
	{
		delete[] arry1;
	}
	cin >> x >> y;
	try
	{
		cout << division(x, y) << endl;
	}
	catch (const char* str)
	{
		delete[] arry1;
		delete[] arry2;
		cout << "kxhsabjhc" << endl;
		// 这相当于捕获到什么就抛什么
		throw;     // 重抛异常   
	}
	//cout << division(x, y) << endl;
	cout << "xchwesbhcb" << endl;
	delete[] arry1;
	delete[] arry2;
}
```

实际情况只会比现在说的更复杂, 毕竟我们这里找不到实例, 所以随手模拟的, 实际情况中开空间总是要用的, 那里面有没有写数据, 写了又该怎么处理. 所以用捕获并不能很好的解决这些问题.

--------------

因为异常能抛各种类型, 异常到底抛不抛也不能确定, 所以C++提供了一个道德性的标识

```cpp
// throw(const char*)的意思就是说
// "我"认为division这个函数只有抛出`const char*`这种可能
double division(int x, int y) throw(const char*)
{
	if (y == 0)
	{
		throw "非法的操作数";
	}
	else
	{
		return static_cast<double>(x) / static_cast<double>(y);
	}
}
```

```cpp
// throw(const char*, int)的意思就是说
// "我"认为division这个函数只有抛出`const char* or int`这种可能
double division(int x, int y) throw(const char*, int)
{
	if (y == 0)
	{
		throw "非法的操作数";
	}
	else
	{
		return static_cast<double>(x) / static_cast<double>(y);
	}
}
```

```cpp
// throw()的意思就是说
// "我"认为division这个函数不会抛出任何异常
double division(int x, int y) throw()
{
	if (y == 0)
	{
		throw "非法的操作数";
	}
	else
	{
		return static_cast<double>(x) / static_cast<double>(y);
	}
}
```

```cpp
//      的意思就是说
// "我"也不知道它抛不抛异常, 抛了又具体是什么类型
double division(int x, int y) 
{
	if (y == 0)
	{
		throw "非法的操作数";
	}
	else
	{
		return static_cast<double>(x) / static_cast<double>(y);
	}
}
```

```cpp
// throw(std::string)的意思就是说
// "我"认为division这个函数只有抛出`string`这种可能
double division(int x, int y) throw(std::string)
{
	if (y == 0)
	{
		throw "非法的操作数";
	}
	else
	{
		return static_cast<double>(x) / static_cast<double>(y);
	}
}
```

上述代码都能正常运行, 所以说`throw()`是道德性的, 实际上可以随便标,  此时`throw()`的可信度就要看"我"到底是谁了, 

C++11引入了`noexcept`关键字, 

```cpp
// noexcept标记的意思是说
// 编译器:"这里不会抛异常"
double division(int x, int y) noexcept
{
	if (y == 0)
	{
		throw "非法的操作数";
	}
	else
	{
		return static_cast<double>(x) / static_cast<double>(y);
	}
}
```

`noexcept`具有强制性, 被`noexcept`修饰的函数, 绝对不会抛异常.

--------------------

最后, 我们说一说异常的优缺点:

优点:

异常抛的是对象, 能展现更多信息, 甚至可以通过特殊设计记录堆栈的调用关系, 这样就更好定位`Bug`到底在哪.

异常会跳代码,  如果确认一个子任务已经无法继续下去了, 那就不用再走子任务的后续代码, 直接跳到`main`中的`catch`

很多第三方库也使用异常捕获这种错误处理方式, 异常这种机制已经固定占据了某个生态位, 再朝着标准化的方向发展

有些函数在机制上没有返回值, 比如构造析构, 又比如某些函数, 不适合把返回值作为错误码, 用输出型参数的方式又显得冗余, 比如`operator[]`系列  

缺点:

异常会跳代码, 会让代码的逻辑变得混乱, 它跳代码的特性也不利于我们调试程序

异常会增加一些可以忽略不计的性能开销

异常不会自动回收已申请的资源, 从而引发内存泄露, 死锁等情况出现

C++标准库设计的异常类体系不好, 大家各用各的, 没有标准

异常规范不是完全可信的, 甚至有误导可能

总结:

异常这种机制本身已经成为程序开发不可分割的一部分, 尽管C++在这一块已经有些赶不上后起之秀了, 有很多麻烦问题, 但该用还是要用的.