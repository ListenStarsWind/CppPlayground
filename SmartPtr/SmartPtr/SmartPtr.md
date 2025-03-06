# SmartPtr

在之前关于异常的学习中, 我们说, 异常容易引发资源的丢失, 从而造成很严重的后果.

比如这种场景:

```cpp
using namespace std;

int div()
{
	int a, b;
	cin >> a >> b;
	if (b == 0)
		throw std::domain_error("除零错误");
	return a / b;
}

void func()
{
	// 如果p1这里new抛异常该做什么
	// 如果p2这里new抛异常该做什么
	// 如果div这里new抛异常该做什么
	int* p1 = new int;
	int* p2 = new int;

	cout << div() << endl;

	delete p1;
	delete p2;
}

int main()
{
	try
	{
		func();
	}
	catch (const exception& e)
	{
		cout << e.what() << endl;
	}
	catch (...)
	{
		cout << "未知错误" << endl;
	}
	return 0;
}
```

会引发内存泄露, 对于我们的服务器来说, 内存泄露是致命性错误, 毕竟服务要一直跑的, 积少成多可用内存就会越来越少.

为此, C++提出了一种利用对象生命周期实现资源托管的解决方案. 在异常抛出的过程中, 会对涉及到的函数栈帧进行释放, 从而结束其中对象的生命周期, 对象生命周期结束便会自动执行析构, 所以我们可以把资源返还写到析构了, 让对象自动返还资源.

```cpp
class SmartPtr
{
public:
	SmartPtr(int* ptr)
		:_ptr(ptr)
	{
	}

	~SmartPtr()
	{
		cout << "delete[]" << endl;
		delete[] _ptr;
	}

private:
	int* _ptr;
};

void func()
{
	// 如果p1这里new抛异常该做什么
	// 如果p2这里new抛异常该做什么
	// 如果div这里new抛异常该做什么
	int* p1 = new int[10];
	SmartPtr _p1(p1);
	int* p2 = new int[10];
	SmartPtr _p2(p2);

	cout << div() << endl;

	delete[] p1;
	delete[] p2;
} 
```

![image-20250301151348955](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250301151349049.png)

这样, 即使发生异常也会自动返还, 当然, 这引发了一些新的问题, 但它们和异常比起来已经好解决了很多, 下面我们会逐步解决.

这种代码体现的思路, 被称为`RAII `(Resource Acquisition Is Initialization), 中文翻译就是资源获取即初始化, 获得资源之后立刻交给对象, 让对象去管控, 所以这里的初始化是指对象的构造.

现在让我们把代码改的更规范一些, 我们先假设开辟的都是一个元素, 而非数组, 等到把智能指针讲的差不多了, 再回来解决这个问题.

```cpp
template<class T>
class SmartPtr
{
private:
	T* _ptr;
public:
	SmartPtr(T* ptr)
		:_ptr(ptr)
	{
	}

	~SmartPtr()
	{
		std::cout << "delete->" << _ptr << std::endl;
		delete _ptr;
	}
};


void SmartPtrTest()
{
	SmartPtr<int> p1(new int);
	SmartPtr<int> p2(new int);
}

int main()
{
	SmartPtrTest();
	return 0;
}
```

 ![image-20250303144108026](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250303144108105.png)

上面的代码体现了`RAII`思想, 下面我们就要让只能指针像指针那样使用.

```cpp
template<class T>
class SmartPtr
{
private:
	T* _ptr;
public:
	SmartPtr(T* ptr)
		:_ptr(ptr)
	{
	}

	~SmartPtr()
	{
		std::cout << "delete->" << _ptr << std::endl;
		delete _ptr;
	}

	T& operator*()
	{
		return *_ptr;
	}

	T* operator->()
	{
		return &(this->operator*());
	}
};


void SmartPtrTest()
{
	SmartPtr<int> sp1(new int);
	*sp1 = 1;
	SmartPtr<pair<string, int>> sp2(new pair<string, int>("xhsqabh", 1));
	sp2->first += "qqq";
	++sp2->second;
}
```

![image-20250303145530151](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250303145530355.png)

![image-20250303145611533](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250303145611721.png)

## New question

智能指针能不能拷贝或者赋值呢?            在上面的代码中, 我们没有写拷贝构造和赋值重载, 但它们是默认成员函数, 所以编译器会自动生成, 因此, 在语法上, 上面的`SmartPtr`是可以进行拷贝和赋值的,    但也只是在语法上可以.

![image-20250303150502034](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250303150502212.png)

默认的拷贝构造和赋值重载采用的是值拷贝, 这使得`sp1`和`sp2`对指针指向的资源进行了重复析构.   看来我们要写一下构造和赋值了, 智能指针和我们以往学习的那些容器不同, 我们设计它的思路是将指针交给智能指针托管, 而非将指针指向的资源的资源交给它, 因此, 所谓赋值或者拷贝可以视为对托管权的转移, 既然是转移, 那么原来的智能指针就会丧失对指针的管理权, 而被拷贝出的新对象或者被赋值的对象获得了指针的管理权.  因此, 拷贝构造和复制重载可以如下定义

```cpp
SmartPtr(SmartPtr<T>& that)
	:_ptr(that._ptr)
{
	// 在此种场景下, 智能指针对于指针的托管权是互斥关系
	// 一个智能指针获得托管权, 意味着另一个失去
	that._ptr = nullptr;
}

SmartPtr<T>& operator=(SmartPtr<T>& that)
{
	// 由于只有一个_ptr, 所以对之前指针的托管权相当于被覆盖了
	_ptr = that._ptr;
	that._ptr = nullptr;
}
```

 ![image-20250303152716785](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250303152716843.png)

这便是智能指针在C++中的初始版本, 在标准库中被称为`auto_ptr`, 发布于C++98.

## To each his own

在我个人看来, `auto_ptr`的设计思路并没有什么大问题, 但很多人不怎么认为, 他们更多地将拷贝构造和赋值重载理解为托管权的分享, 而非转移, 所以经常会出现这种情况: 对已经做过构造参数或者是赋值的对象进行解引用, 从而将空指针解引用.

```cpp
void SmartPtrTest2()
{
	SmartPtr<int> sp1(new int);
	SmartPtr<int> sp2 = sp1;
	*sp1 = 2;
}
```

![image-20250303154621802](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250303154622027.png)

这时运算符重载的坏处就体现出来了, 同一个运算符, 长得一样, 但内部的设计思路可能并不相同, 所以就容易造成误解. 用户根据以往学习容器的经验, 自然认为这里的赋值类似于一种"资源上的分享", 不会对右操作数进行修改, 右操作数在被作为构造和赋值参数后, 仍然具备向其中写数据的能力, 所以继续往里写数据, 造成空指针解引用.

因为经常引发误会, 所以部分公司甚至禁止使用`auto_ptr`, 总之, `auto_ptr`很不受待见.

## C++11

在C++11阶段, 给出了基于`auto_ptr`思路的`unique_ptr`, `unique`的意思就是独一无二的, 怎么个独一无二法呢? 从外在行为来看, 就是`unique_ptr`对象间是互斥的, 它根本不支持`unique_ptr`对象间拷贝构造和复制重载, 只要写上就会报错.

现在让我们扩展一下思路, 如何禁用一个默认成员函数

从C++98 的思路走, 可以光声明, 但不实现, 这样编译器就不会生成默认成员函数, 编译的时候因为找不到函数实现会报错.,  又或者, 我们可以将其定义为私有成员函数, 那样只要一写就会报错, 

但既然是C++11, 那便可以直接使用`delete`关键字, 将该函数视为已删除的, 因此无法调用

```cpp
unique_ptr(unique_ptr<T>& that) = delete;

unique_ptr<T>& operator=(unique_ptr<T>& that) = delete;
```

![image-20250303163101304](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250303163101664.png)

![image-20250303163432564](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250303163432608.png)

![image-20250303163505678](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250303163505734.png)

## shared_ptr

`unique_ptr`尽管不会再产生误会了, 但还是达不到托管权共享的效果, 所以C++11也发布了`shared_ptr`, 它底层用的是引用计数, 下面我们就实现一下它.

当使用拷贝构造或者赋值重载时, 所有托管相同地址的智能指针, 其引用计数都会加一, 而其中一个智能指针对象被析构后, 引用计数就会减一, 当引用计数为0时, 变会对申请的堆上空间进行释放. 因为需要让所有托管相同地址的智能指针引用计数同时加一或减一, 所以, 引用计数本体会在堆上, 各指针指针通过指针链接计数本体.  不能用静态成员变量, 静态成员变量只能统计所有的智能指针个数, 但这些智能指针托管的很可能不是同一块堆空间, 我们无法区分它们.

```cpp
template<class T>
class shared_ptr
{
private:
	T* _ptr;
	size_t* _count;

	inline void release_control()
	{
		if (--*_count == 0)
		{
			std::cout << "delete->" << _ptr << std::endl;
			delete _ptr;
			delete _count;
		}
	}

public:
	shared_ptr()
		:_ptr(nullptr)
		, _count(new size_t(1))
	{
	}

	shared_ptr(T* ptr)
		:_ptr(ptr)
		, _count(new size_t(1))
	{
	}

	shared_ptr(const shared_ptr<T>& that)
		:_ptr(that._ptr)
		, _count(that._count)
	{
		++*_count;
	}

	~shared_ptr()
	{
		release_control();
	}
};
```

![image-20250303173135055](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250303173135269.png)

![image-20250303173202272](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250303173202462.png)

对于赋值重载来说,  有三个重点: 不要给自己赋值, 释放管理权, 获得新的管理权.

为什么不能自己给自己赋值呢? 假设现在引用计数为`1`, 自己给自己赋值, 首先会释放管理权, 导致引用计数归零, 析构引用计数本体和用户资源, 此时再接纳原指针, 接纳的就是野指针了, 具体的解决方案是判断`that`指针与`this`是否相同, 不过我们这里判断用户资源是否相同, 一方面自己对自己赋值就可以过滤掉, 另一方面, 那些管理相同用户资源的智能指针相互赋值也可以过滤掉, 释放管理权的逻辑和析构其实相似, 在以往的析构函数中, 往往是对资源的直接释放, 但对于智能指针来说, 是管理权的释放, 只有引用计数归零才会进行资源释放,  所以这里使用内联函数的形式, 利用函数名增强可读性,  这里直接复用即可, 对于管理权的分享, 与拷贝构造逻辑相同, 这不过因为上面用了初始化列表, 所以没有统一写成内联函数进行复用.

```cpp
shared_ptr<T>& operator=(const shared_ptr<T>& that)
{
	if (_ptr != that._ptr)
	{
		release_control();

		_ptr = that._ptr;
		_count = that._count;
		++*_count;
	}
	return *this;
}
```

![image-20250303175803879](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250303175804030.png)

![image-20250303175824394](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250303175824531.png)

![image-20250303175902077](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250303175902231.png)

![image-20250303175956871](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250303175957071.png)

## development history

下面我们说一说C++中智能指针的发展历程.

首先是C++98引入了智能指针的概念, 并实现了最开始的智能指针`auto_ptr`, `auto_ptr`的设计很多人并不喜欢, 会导致对象悬空的问题, 引发空指针的解引用; 在C++11中, 就引入了简单粗暴的`unique_ptr`和几乎可以适应一切场景的`shared_ptr`, 稍后我们会说哪里有问题.   但其实, 在C++98和C++11之间还有C++boost库的故事.`boost`库是C++的准标准库, 它的职责就是对C++进行前沿探索, 对新的语法进行实验, 只有经过`boost`库的检验, 才可能成为下一代C++标准的语法, 比如C++11中的`unique_ptr`便来源于`scoped_ptr`, `shared_ptr`来源于`boost`的同名类.

## circular reference

`shared_ptr`在一些场景下会出现引用循环的问题:

```cpp
struct ListNode
{
	int _val;
	ListNode* _prev;
	ListNode* _next;
};

void shared_ptr_test1()
{
	auto p1 = new ListNode;
	auto p2 = new ListNode;
	p1->_next = p2;
	p2->_prev = p1;
}
```

这是以前的写法, 现在我们怕新建链表节点的时候抛出异常, 所以就能改成这样:

```cpp
struct ListNode
{
	int _val;
	wind::shared_ptr<ListNode> _prev;
	wind::shared_ptr<ListNode> _next;
};

void shared_ptr_test1()
{
	wind::shared_ptr<ListNode> p1(new ListNode);
	wind::shared_ptr<ListNode> p2(new ListNode);
	p1->_next = p2;
	p2->_prev = p1;
}
```

然后就会出现一件事, 无法析构

![image-20250303194019947](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250303194020405.png)

这两个空是赋值的时候产生的, `wind::shared_ptr`默认构造是`nullptr`, 所以`ListNode`中的两个智能指针最开始都是`nullptr`, 在赋值的时候管理权释放, 从而引发了资源释放.  我们把之前的打印信息注释掉, 为`ListNode`的析构写一下打印信息

```cpp
struct ListNode
{
	int _val;
	wind::shared_ptr<ListNode> _prev;
	wind::shared_ptr<ListNode> _next;

	~ListNode()
	{
		cout << "~ListNode()" << endl;
	}
};

void shared_ptr_test1()
{
	wind::shared_ptr<ListNode> p1(new ListNode);
	wind::shared_ptr<ListNode> p2(new ListNode);
	p1->_next = p2;
	p2->_prev = p1;
}
```

我们看到, 开了两个节点但没有一个被释放

![image-20250303194455091](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250303194455153.png)

而且只要取消`p1->_next=p2;    p2->_next=p1`中的任意一个, 又都能析构, 为什么,呢, 这需要我们画个示意图分析.

首先我们在堆上开了一个节点, 与之相对应的还有一个引用计数.

![image-20250303200053372](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250303200053422.png)

每个`ListNode`里有两个智能指针, 它们最开始管理的都是空资源, 因为无参构造是用`nullptr`初始化的, 现在它们的引用计数都是`1`

第二个语句与之相同

![image-20250303200438132](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250303200438194.png)

现在是第三条语句, `p2`将资源的管理权分享给了`p1->_next`, 这导致之前的空资源释放, 由于是分享, 所以引用计数会加一

![image-20250303200819376](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250303200819447.png)

![image-20250303200846563](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250303200846623.png)

第四条语句过程类似

![image-20250303201052936](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250303201052986.png)

![image-20250303201114811](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250303201114863.png)

之后是析构环节

首先, 智能指针`p2`被析构, 这代表它不再管理之前的那份资源, 所以对应的引用计数减一

![image-20250303201312142](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250303201312189.png)

![image-20250303201409847](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250303201409905.png)

之后智能指针`p1`被析构, 引用计数也减一

![image-20250303201517433](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250303201517483.png)

![image-20250303201532006](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250303201532059.png)

然后它俩就没有释放.

为什么要叫循环引用呢? 因为它在逻辑上会出现死循环

为了方便描述, 我们把第一个开出的节点记为`A`, 第二个节点开出的节点记为`B`

若想让`B`这个节点被释放, 需要其引用计数归零, 如果需要引用计数归零, 就需要`A`中`_next`智能指针被析构

`_next`是`A`的成员变量, `A`释放的时候它才会被析构, `A`这个节点要被释放, 其引用计数需要归零, 这意味着`B`中的`_prev`智能指针要被析构, 

`_prev`是`B`的成员变量, `B`释放的时候它才会被析构

若想让`B`这个节点被释放.....

今天开了眼了, 在单执行流里见到了和死锁相同的逻辑死循环.

怎么解决呢? `shared_ptr`本身没有能力解决这个问题, 此时需要将指针域中的类型换成`weak_ptr`, `weak_ptr`的逻辑是单纯起索引功能, 不参与资源管理, 或者说的更明白些, 它不会让引用计数加一, 不会从`shared_ptr`那里获得管理权.

![image-20250303204726408](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250303204726484.png)

![image-20250303204747200](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250303204747244.png)

`weak_ptr`单纯就是为解决循环引用问题而生的, 其本身并不具有`RAII`功能

我们可以使用`use_count`查看引用计数的具体数值

```cpp
struct ListNode
{
	int _val;
	shared_ptr<ListNode> _prev;
	shared_ptr<ListNode> _next;

	~ListNode()
	{
		cout << "~ListNode()" << endl;
	}
};

void shared_ptr_test1()
{
	shared_ptr<ListNode> p1(new ListNode);
	shared_ptr<ListNode> p2(new ListNode);

	cout << p1.use_count() << "  " << p2.use_count() << endl;
	p1->_next = p2;
	p2->_prev = p1;
	cout << p1.use_count() << "  " << p2.use_count() << endl;
}
```

![image-20250303205249999](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250303205250087.png)

```cpp
struct ListNode
{
	int _val;
	weak_ptr<ListNode> _prev;
	weak_ptr<ListNode> _next;

	~ListNode()
	{
		cout << "~ListNode()" << endl;
	}
};

void shared_ptr_test1()
{
	shared_ptr<ListNode> p1(new ListNode);
	shared_ptr<ListNode> p2(new ListNode);

	cout << p1.use_count() << "  " << p2.use_count() << endl;
	p1->_next = p2;
	p2->_prev = p1;
	cout << p1.use_count() << "  " << p2.use_count() << endl;
}
```

![image-20250303205333722](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250303205333796.png)

如果想要速成一个`weak_ptr`, 可以这样写

```cpp
template<class T>
class shared_ptr
{
private:
	T* _ptr;
	size_t* _count;

	inline void release_control()
	{
		if (--*_count == 0)
		{
			//std::cout << "delete->" << _ptr << std::endl;
			delete _ptr;
			delete _count;
		}
	}

public:
	shared_ptr()
		:_ptr(nullptr)
		, _count(new size_t(1))
	{
	}

	shared_ptr(T* ptr)
		:_ptr(ptr)
		, _count(new size_t(1))
	{
	}

	shared_ptr(const shared_ptr<T>& that)
		:_ptr(that._ptr)
		, _count(that._count)
	{
		++*_count;
	}

	~shared_ptr()
	{
		release_control();
	}

	shared_ptr<T>& operator=(const shared_ptr<T>& that)
	{
		if (_ptr != that._ptr)
		{
			release_control();

			_ptr = that._ptr;
			_count = that._count;
			++*_count;
		}
		return *this;
	}

	T& operator*()
	{
		return *_ptr;
	}

	T* operator->()
	{
		return &(this->operator*());
	}

	T* get()const
	{
		return _ptr;
	}

	size_t use_count()const
	{
		return *_count;
	}
};

template<class T>
class weak_ptr
{
private:
	T* _ptr;
public:
	weak_ptr()
		:_ptr(nullptr)
	{
	}

	weak_ptr(const shared_ptr<T>& that)
		:_ptr(that.get())
	{
	}

	weak_ptr<T>& operator=(const shared_ptr<T>& that)
	{
		_ptr = that.get();
		return *this;
	}

	T& operator*()
	{
		return *_ptr;
	}

	T* operator->()
	{
		return &(this->operator*());
	}
};
```

```cpp
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

```

![image-20250303210754399](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250303210754471.png)

对于`weak_ptr`需要注意的是, 尽管它不会改变`shared_ptr`的引用计数, 但其实它内部还是有引用计数的, 它只是说不去改变而已, 我们去文档那里看一看.

![image-20250305202604250](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250305202604390.png)

我们看到, 也是有`use_count`, 它的返回值就是与它本身使用同一指针的`shared_ptr`的引用计数.   

对于`shared_ptr`可能存在一种尴尬的情况, 引用计数已经归零了, 也就是说`weak_ptr`内部已经是野指针了, 此时再进行访问就会出问题. 

如果担心`weak_ptr`内部的指针已经失效, 可以使用`expired`来进行检测, 返回真就说明指针指向的空间资源已经被释放了, 这个`weak_ptr`已经不能用了, 另外, 也可以使用`lock`接口, 返回一个与`weak_ptr`使用相同指针的`shared_ptr`, 但总的来说, `weak_ptr`我们本身就用的很少, 它内部的接口就用的更少了, 用了反而会让代码更复杂,   所以我们只需要了解一下即可.

-------------

好的, 我们最后再对指针指针收个尾, 返回我们之前的问题,  那就是如果开辟的是数组,  该怎么办?    `boost`库的做法很简单粗暴,   它有两份`shread`, 一份叫做`shread_ptr`, 用来做单个对象的管理, 另一份叫做`shread_array`, 用来对数组进行管理.

C++11则不是这样, C++11提供了一种"自定义删除器"极值, 这个自定义删除器其实就是可调用对象, 用户在外部指定资源的释放方式, 然后以对象的形式传入`shread_ptr`, 从而使得`shread_ptr`的资源释放方式可以根据实际情况进行自定义.

![image-20250305205105530](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250305205105832.png)

![image-20250305205834850](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250305205835260.png)

增加自定义删除器的好处是, 使得`shared_ptr`也可以管理其它的指针资源, 比如文件指针

![image-20250305210924374](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250305210924902.png)

下面我们实现一下, 首先我们需要增加一个`function`对象, 将用户传入的可调用对象包装起来.   然后对于一般构造, 直接用默认的`lambda`(写在声明上做缺省值或许更好)

![image-20250305212127484](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250305212128105.png)

我们看到, 是可以正常使用的

![image-20250305212416109](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250305212416492.png)

库里面的`shared_ptr`还有一些其它设计, 我们可以利用构造函数声明从侧面看一看.

![image-20250305214355542](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250305214355614.png)

# end 