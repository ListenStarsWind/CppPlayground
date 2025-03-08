# Special Class

## Non-copyable Class

如何设计一个不能被拷贝的类?

拷贝只会放生在两个场景中：拷贝构造函数以及赋值运算符重载，因此想要让一个类禁止拷贝，只需让该类不能调用拷贝构造函数以及赋值运算符重载即可.

- C++98风格:    对这两个默认成员函数只声明不定义(防止编译器自动生成),  并设置为私有(防止用户类外定义)
- C++11风格:    在默认成员函数声明后面加上`=delete`,  表示让编译器删除该默认成员函数.

## Heap-Only Class

如何创建一个只能在堆上实例化对象的类?         有两种思路,   一是朝析构函数下手,    二是朝构造函数下手

先说第一个:  从析构函数下手

有两个步骤:   一将析构函数私有化(此时已经只能在堆上建了)     二设计公有接口, 用于`delete`类指针(成员函数没有公私有的概念, 可以直接调用析构)

![image-20250306091117246](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250306091118169.png)

```cpp
class HeapOnly
{
public:
	void Destroy1()
	{
		delete this;
	}

	static void Destroy2(HeapOnly* ptr)
	{
		delete ptr;
	}

private:
	~HeapOnly()
	{
	}
};

int main()
{
	auto hp1 = new HeapOnly;
	auto hp2 = new HeapOnly;
	hp1->Destroy1();
	HeapOnly::Destroy2(hp2);

	return 0;
}
```

第二种:  朝构造函数下手

同样有两个步骤,   一是将构造函数私有化,     二是提供一个公有接口, 在堆上开辟一个空间, 并返回指针,  因为对象还没有被创建, 没有`this`指针, 所以只能以静态函数形式来写.

```cpp
class HeapOnly
{
public:
	static HeapOnly* Create()
	{
		return new HeapOnly;
	}

private:
	HeapOnly() {}
};

int main()
{
	auto hp1 = HeapOnly::Create();
	delete hp1;

	return 0;
}
```

对于第二种方法,  需要注意一个问题:   构造函数不止一个, 都需要处理干净,  默认构造没了, 可以上拷贝构造.

![image-20250306093101633](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250306093101920.png)

为了解决这个问题, 还需要禁用拷贝构造

```cpp
class HeapOnly
{
public:
	static HeapOnly* Create()
	{
		return new HeapOnly;
	}

	HeapOnly(const HeapOnly& that) = delete;
private:
	HeapOnly() {}
};
```

## Stack-Only Class

如何创建一个只能在栈上实例化对象的类

目前来看,  似乎只有一种方法,  那就是对重载`operator new`,   我们知道`new`操作符背后有两个步骤,  一是使用全局`void* operator new(size_t size)`,  获得一处对空间,   二是在这处空间上实例化对象.   当我们在类里重载`operator new`时,  依据就近原则,  使用`new`操作符调用的就是我们的`operator new`,  之后我们再将其禁用, `new`对于该类就无法使用了.

![image-20250306095138741](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250306095139034.png)

注意,   想要设计一个不能在堆上实例化对象的类,  不能模仿不能在栈上实例化对象的类, 将构造函数私有化,  如下:

```cpp
class StackOnly
{
public:
	static StackOnly Create()
	{
		return StackOnly();
	}
private:
	StackOnly() {}
};

int main()
{
	auto sk = StackOnly::Create();
	auto skp = new StackOnly(sk);
	return 0;
}
```

为了让`Create`里面的临时对象传过来,  我们必须要有拷贝构造,   但拷贝构造又使得可以在堆上实例对象,   所以不能用这个思路

## Non-inheritable Class

如何设计一个不能被继承的类?   本小节跳过,   我们之前已经说过, 用`final`即可.

## Singleton-model

对于某些对象来说, 总是需要做到这点:  全局只有一个对象.   比如各种池, 池是对资源进行统一管理的, 比如对于内存池来说, 你不能从`a`内存池申请个空间, 然后还给`b`.   这种特殊类在实际场景下还是很常见的, 以至于形成了固定的套路, 称之为"单例模式". 

单例模式是一种设计模式, 所谓设计模式, 就是写代码的固定套路, 这些固定套路一方面被经常使用, 经过了实际过程实践的检验, 凝聚了很多代码设计的经验总结, 也被大家广泛接受, 用设计模式一方面能保证代码可靠性, 另一方面, 让代码更能让别人理解.   不过我们这里就不会细说设计模式了, 设计模式对于上层来说, 还是很重要的, 对我们这种底层其实并不是特别重要, 设计模式对我们来说是锦上添花的东西.    我们以前的迭代器模式, 适配器模式什么的, 也是一种设计模式.

单例模式有两种, 分别是饿汉模式和懒汉模式, 由于系统层的进度原因, 我们先不考虑多线程环境.

饿汉模式的设计思路是,  在`main`函数之前就把对象实例化出来, 

首先由于这是单例, 所以各种各样构造函数, 肯定是要私有的, 甚至我们可以直接`delete`, 赋值也禁用, 防止自己给自己赋值.

```cpp
class A
{
    private:
    A() {}
    A(const A& that) = delete;
    A& operator=(const A& that) = delete;
    int n = 0;
    static A _inst;
};
```

 然后我们的要求是在`main`之前实例化对象,    什么对象能在`main`之前实例化出来?      据我所知, 就两种, 一是全局变量, 二是静态变量.  我们不使用全局对象思路, 一方面, 现在构造函数是私有的, 全局对象实例化不出来,  另一方面, 全局对象的生命周期和作用域都是全局的, 容易引发歧义, 造成链接错误.    对于静态变量来说, 它的生命周期确实是全局的, 但作用域只在本文件, 这样就能更好的进行管控, 那全局怎么用呢? 指针或者引用传参即可. 

好的, 现在我们来解决另一个问题,  构造函数是私有的, 那怎么实例化?  其实很简单, 但是不太容易想到, 那就是这个类自带一个自身的静态对象, 由于静态对象声明在类内, 所以虽然定义在类外, 但能调用私有的构造函数.

```cpp
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

int main()
{
	cout << A::getInstance().getN() << endl;
	return 0;
}
```

 关于饿汉模式的资源释放问题;   当进程正常退出时, 静态对象调用析构, 释放资源.

懒汉模式是在饿汉模式的基础上优化来的.

对于饿汉模式, 它存在某些问题,   由于对象是在`main`函数之前实例化, 所以如果单例类的成员很多, 或者有很多不同的单例类, 进程正式运行(从`main`函数开始)就会比较耗时, 因为要实例化很多东西. 对于图形化界面来说, 出现主界面就意味着进程已经启动了, 试想一下, 如果一个应用, 你点了之后三四十秒都没进主界面, 用户体验就会很差, 除此之外, 饿汉模式的致命缺点是它不能控制单例对象的实例化顺序, 这意味着, 如果一个单例类的实例化依赖于另一个单例类, 它们的实例化顺序就必须固定, 一定要是被依赖的在前, 依赖的在后.   饿汉的优点就是简单.

懒汉模式的设计思路就是第一次用的时候再实例化

首先还是老样子, 该私有的私有, 该禁用的禁用

```cpp
class B
{
	B() {}
	B(const B& that) = delete;
	B& operator=(const B& that) = delete;

public:


private:
	int m = 0;
};

```

之后我们还是用静态成员, 只不过是类的指针, 初始值为`nullptr`

```cpp
class B
{
	B() {}
	B(const B& that) = delete;
	B& operator=(const B& that) = delete;

public:
	int& getM()
	{
		return m;
	}

private:
	int m = 0;
	static B* _inst;
};

B* B::_inst = nullptr;
```

指针最大是八个字节, 并不是多大的负担.      等到第一次请求对象的时候, 直接在堆上实例化一个对象就行.

```cpp
class B
{
	B() {}
	B(const B& that) = delete;
	B& operator=(const B& that) = delete;

public:
	static B* getInstance()
	{
		if (_inst == nullptr)
		{
			_inst = new B;
		}
		return _inst;
	}

	int& getM()
	{
		return m;
	}

private:
	int m = 0;
	static B* _inst;
};

B* B::_inst = nullptr;


int main()
{
	B& b = *B::getInstance();
	cout << b.getM() << endl;
	return 0;
}

```

接着说一下懒汉模式的析构.    对于堆上的对象来说, 它的生命周期也是全局的, 如果不`delete`, 那就会在系统层面释放资源, 所以系统层面释放资源, 那就是直接绕过析构断页表, 那些虚拟内存就直接被系统回收了.   所以其实不考虑资源释放其实也行,   但有些情况下, 必须要调用析构函数,  比如析构函数会调用外设, 相当于是在外设上留下自己的痕迹,  术语叫做"持久化操作", 一般是把内存数据写到文件,  此时析构函数就需要被认真执行, 另一方面, 可能存在一种需求, 就是提前析构单例对象, 此时需要提供公有接口显示地析构对象.

先看第一种写法, 直接显式调用析构, 当然, 前提是析构为公有

```cpp
class B
{
	B() {}
	B(const B& that) = delete;
	B& operator=(const B& that) = delete;

public:
	~B() {}

	static B* getInstance()
	{
		if (_inst == nullptr)
		{
			_inst = new B;
		}
		return _inst;
	}

	int& getM()
	{
		return m;
	}

private:
	int m = 0;
	static B* _inst;
};

B* B::_inst = nullptr;


int main()
{
	B& b = *B::getInstance();
	cout << b.getM() << endl;

	delete &b;

	return 0;
}
```

但我们并不推荐, 因为可能存在一种情况, 有人在后面又使用了这个单例,....所以我们需要一种进程退出自动调用析构的机制

比如, 智能指针,   不过我们下面介绍一种新的方法, 其实用的也是`RAII`...

首先先把析构变为私有, 不让用户随便用, 然后专门再建一个接口析构单例, 这是为了允许用户可以提前析构

```cpp
void delInstance()
{
	if (_inst)
	{
		delete _inst;
		_inst = nullptr;
	}
}
```

接着我们要再写一个保底机制, 即使用户没调`delInstance`, 对象也能自动析构, 在单例类的私有域中定义一个没有成员的空内部类,  它的析构是调用 `delInstance`, 内部类是天然的友元, 所以能直接用`_inst`.  并在单例类中声明一个对应类型的静态成员.

```cpp
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
			_inst = new B;
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

```

# end