# C++内存管理

让我们先回顾一下C语言是如何进行动态内存管理的：我们使用`malloc`从堆上分配内存，使用完后再用`free`释放。然而，`malloc - free`体系存在显著问题：它无法有效支持自定义类型，也不便于使用类中的成员函数。此外，构造函数和析构函数是自动调用的，开发人员不好显式调用，这意味着我们需要重写逻辑，只是将逻辑的运行场景从栈转移到了堆。

除了这个主要问题，`malloc - free`体系还有一些令人烦恼的小问题：我们必须手动检查内存是否成功分配，并在手动释放时小心不要释放野指针指向的内存。这些问题表明，C++需要一个更完善的内存管理方案。

## new和delete

new和delete是C++的两个关键字，用于动态内存管理。

关键字new可以在堆上开辟出一块内存，对于单个对象（C++喜欢用对象的说法，一个`int`变量，亦可以被称为对象），其格式为`new type`，对于多个对象，其格式为`new type[num]`，它会自动返回一个合适的指针类型，不用手动强转类型，和类相似，如果类型`type`是内置类型，就不初始化，如果`type`是自定义类型，会自动调用对应的构造函数。或者也可以统一一下说法，无论是单个对象还是数组，格式都为`new type`，数组的类型是`成员类型[成员个数]`。

关键字delete可以把开辟的内存块还给操作系统，对于单个对象，格式为`delete pointer`；对于多个对象，格式为`delete[] pointer`。内置类型，直接释放；自定义类型则会自动调用析构函数。

```cpp
int main()
{
	//int* p1 = (int*)malloc(sizeof(int));
	auto p1 = new int;

	//int* p2 = (int*)malloc(sizeof(int) * 10);
	auto p2 = new int[10];
	
	//free(p1);
	delete p1;

	//free(p2);
	delete[] p2;
	return 0;
}
```

C++11后，也支持对内置类型对象`new`的时候初始化，单个对象的初始化形式和初始化列表很像，多个对象的初始化，则像C中局部数组省略`=`号的样子；初始化逻辑仍和C相同，成员没给满，其他成员就初始化成对应类型的0；对于自定义类型成员，初始化就是用来给构造函数传参，传参逻辑请参考上节的类与对象。

```cpp
int main()
{
	//int* p1 = (int*)malloc(sizeof(int));
	//*p1 = 1;
	auto p1 = new int(1);

	//int* p2 = (int*)malloc(sizeof(int) * 10);
	//int arr[10] = { 1,2,3 };
	auto p2 = new int[10] {1,2,3};
	
	//free(p1);
	delete p1;

	//free(p2);
	delete[] p2;

	return 0;
}
```

![image-20241009165537544](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410091655856.png)

```cpp
#include<iostream>

namespace wind
{
	class A
	{
	public:
		A(int val = 2);
		A(const A& obj);
		~A();
	private:
		int _i;
	};
}

wind::A::A(int val)
	:_i(1)
{
	_i = val;
	std::cout << "A(int val)" << std::endl;
}

wind::A::A(const A& obj)
	:_i(obj._i)
{
	std::cout << "A(const A& obj)" << std::endl;
}

wind::A::~A()
{
	std::cout << "~A()" << std::endl;
}
```

如果`A`里的成员变量是其它自定义类型的，还可以用我们之前说的匿名对象，隐式类型转化方式传参，这样更方便。

![image-20241009173233775](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410091732189.png)

-----------------

检查`new`是否开辟成功需要用`try - catch`结构，若`try`结构中的`new`开辟失败，就会直接略过`try`结构中的剩余代码，像`go to`一样立刻跑到`catch`结构中，执行里面的内容，如果开辟成功，则在`try`结束之后略过`catch`结构。

为了方便制造异常，我们改成`x86`框架，开辟的对象个数为`0x7fffffff`。

如果没有`try - catch`结构捕获异常，则程序异常之后直接终止。`const std::exception& e`可用于接收异常信息。

```cpp
void f()
{
	auto p = new char[0x7fffffff];
	std::cout << "----------" << std::endl;
}

int main()
{
	try
	{
		f();
		std::cout << "===========" << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	return 0;
}
```

![image-20241009202223827](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410092022007.png)

`bad allocation`：无法分配。

## new和delete的基本逻辑

关键字`new`和`delete`会分别调用函数`operator new`和`operator delete`。`operator new`会在堆上开出足够大小的空间，之后构造函数会在这块被`operator new`开辟出的内存中实例化出对象；`delete`会在这片内存中对实例化对象进行析构，然后再通过`operator delete`将这片内存归还给操作系统。

`operator new`是对`malloc`的包装，`malloc`如果开辟失败，就会自动执行某些处理措施（有`try - catch`就直接跳到`catch`，没有就程序终止）。`operator delete`是对`free`的再包装。`operator new`和`operator delete`尽管看着像运算符重载函数，但其实并不是运算符重载函数，使用`operator`的原因可能是它们的功能十分类似，运算符重载函数对运算符的运行逻辑进行了重定义，而`operator new`和`operator delete`则是去解释关键字`new`和`delete`的背后到底在干什么。

```cpp
void test1()
{
	auto x = func();
	x->Push(1);
	x->Push(2);
	x->Push(3);
	x->Print();
	delete x;
}

int main()
{
	test1();
	return 0;
}
```

![image-20241009210335539](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410092103687.png)

![image-20241009210410433](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410092104546.png)

![image-20241009210451265](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410092104398.png)

![image-20241009210537613](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410092105693.png)

![image-20241009210630198](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410092106319.png)

![image-20241009210703511](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410092107624.png)

![image-20241009210742129](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410092107256.png)

![image-20241009210813761](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410092108853.png)

```cpp

    /*
    operator new：该函数实际通过malloc来申请空间，当malloc申请空间成功时直接返回；申请空间失败，
    尝试执行空间不足应对措施，如果更改应对措施用户设置了，则继续申请，否则抛异常。
    */
    void *__CRTDECL operator new(size_t size) _THROW1(_STD bad_alloc)
{
    // try to allocate size bytes
    void *p;
    while ((p = malloc(size)) == 0)
        if (_callnewh(size) == 0)
        {
            // report no memory
            // 如果申请内存失败了，这里会抛出bad_alloc 类型异常
            static const std::bad_alloc nomem;
            _RAISE(nomem);
        }
    return (p);
} 
 /*
  operator delete: 该函数最终是通过free来释放空间的
 */
        void operator delete(void *pUserData)
    {
        _CrtMemBlockHeader * pHead;
        RTCCALLBACK(_RTC_Free_hook, (pUserData, 0));
        if (pUserData == NULL)
            return;
        _mlock(_HEAP_LOCK); /* block other threads */
        __TRY
            /* get a pointer to memory block header */
            pHead = pHdr(pUserData);
        /* verify block type */
        _ASSERTE(_BLOCK_TYPE_IS_VALID(pHead->nBlockUse));
        _free_dbg( pUserData, pHead->nBlockUse );
        __FINALLY
            _munlock(_HEAP_LOCK); /* release other threads */
        __END_TRY_FINALLY
            return;
    } 
 /*
  free的实现
 */
 #define free(p) _free_dbg(p, _NORMAL_BLOCK)
```

对于`new type[num]`则会调用`operator new[]`，`operator new[]`会把`operator new`执行`num`次，同样的`delete[] pointer`则会调用`operator delete[]`，`operator delete[]`会把`operator delete`执行`num`次。

--------

接下来就要整活了。

```cpp
void test2()
{
	auto p = new int[10];
	delete p;
}

int main()
{
	test2();
	return 0;
}
```

这样写没有问题，首先内置类型没有析构函数，或者说析构函数是空的，执行析构之后，随后的`free`足以释放开辟内存，就像C那样。

```cpp
class A
{
public:
	A(int val = 5)
		:_i(1)
	{
		_i = val;
	}
private:
	int _i;
};


int main()
{
	auto p = new A[10];
	delete p;
	return 0;
}
```

虽说看着很危险，但没报错。

```cpp
class A
{
public:
	A(int val = 5)
		:_i(1)
	{
		_i = val;
	}
	~A()
	{
		std::cout << "===" << std::endl;
	}
private:
	int _i;
};


int main()
{
	auto p = new A[10];
	free(p);
	return 0;
}
```

报错

```cpp
// 加了析构函数
int main()
{
	auto p = new A[10];
	delete p;
	return 0;
}
```



为什么会报错呢？这和编译器的具体逻辑有关。对于VS系列IDE来说，使用`new A[10]`开辟内存时，原则上来说并不是开辟`sizeof(A)*10`个字节，而是`sizeof(A)*10 + sizeof(int)`，这里多出的四个字节其实是为`10`准备的，因为`operator delete[]`并没有参数，它是依靠这多出的四字节来判断`operator delete`到底要执行多少次的。所以对于`new A[10]`，`malloc`实际上会开辟`44`个字节，不过`new A[10]`返回的地址是`malloc`返回地址加上`sizeof(int)`字节后的地址（也就是略过了`10`这个值）；等到要`delete[]`的时候，`delete[]`会把接收到的指针往前偏移`sizeof(int)`字节，这样就知道有`10`个对象要被析构，然后从第一个`A`对象开始，执行`10`次析构函数，然后以已经偏移的指针开始把这`44`字节内存释放。

但上面只是原则上来说而已，当用户没有自己写析构函数时，编译器就会生成一个空的析构函数，等到要运行的时候，编译器发现这个析构函数是空的，就会进行优化：反正析构函数是空的，什么内容也没有，所以`new A[10]`的时候不需要再额外开辟`sizeof(int)`字节的空间，只要开辟`sizeof(A)*10`字节空间就行了，然后`new A[10]`返回的就是`malloc`开辟内存块的起始地址，所以使用`free`或者`delete`不会报错。

当用户写了析构函数，析构函数又有实际内容，编译器就不会优化，它会按照原则行事，所以此时返回的地址不是开辟内存块的起始地址，而C/C++的开辟内存都必须从起始地址处释放，`delete`里面也有`free`，于是它们就会报错。

上面想表达的是：`new`和`delete`一定要严格对照格式用，`new type[]`一定要用`delete[]`释放，`new type`一定要用`delete`释放，如果对不上，一方面，会有不同的情况，有的不报错，有的报错，如果报错了，错误还会非常奇怪，难以理解，而且它的最终结果还和具体的开发环境有关，上面说的都是针对`VS`系列开发环境来说的。较高版本的`VS`封装的太好了，看不到细节，即使看到了，细节也具有误导性，`VS2008`我亲自试过了，就是开辟`44`个字节。

![image-20241010100207033](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410101002279.png)

## 定位new表达式

在后续的学习中，我们可能要先自己从堆上开辟一处空间，然后再让构造函数在这处空间里实例化对象，此时就要用到定位new表达式，也称placement-new 。

使用格式是`new(pointer)type`，用中文来说就是：`new(指向动态开辟内存块中某处的指针)自定义类型`，如果可以传参，那也可以传。

```cpp
int main()
{
	// 建立内存池
	auto p = (void*)new char[44];
	// 写入一个整型
	*((int*)p) = 10;
	// 挪到未写入的起始位置
	A* q = (A*)((char*)p + sizeof(int));
	// 实例化对象
	new(q) A;
	// 移到未写入的起始位置
	auto m = q + sizeof(A);
	// 实例化对象
	new(m) A(6);
	// 手动调用析构
	m->~A();
	q->~A();
	free(p);
	return 0;
}
```

 内存池是个什么东西？这样吧，举个例子：在以前，有户人家把家建在一条小河边，最开始，他们需要用到水的时候，就拿一个盆去小河里取盆水，但要用到水的时候很多呀：洗漱，做饭，洗衣······都要用到水，用到水时都要临时拿个盆取水，太麻烦了，于是他们就在自家院子里建了一个池子，然后取个更大的容器，把这个池子填满，这样以后急着要水的时候就不用再去小河里取水了。

内存池同样如此，我嫌`new`自己开辟，实例化对象太慢了。干脆在运行程序之前，预估一下我要用到的内存，提前从堆那一次性申请出来，然后通过某种方法管理申请出的内存（上面是裸着管理的），这样更快。

不止内存，对于那些频繁用到的计算机资源，都有对应的池，我们统称为“池化技术”。

# C++内存分布（浅谈）

在Linux系统部分我们会详细说说计算机的内存分布，这里只是浅谈。

我们之前说过，C/C++程序主要涉及到四个内存部分：栈，堆，静态区（又称数据段），常量区（又称代码段）。

下面我们看一道题目：

```cpp
int globalVar = 1;
static int staticGlobalVar = 1;
void Test()
{
    static int staticVar = 1;
    int localVar = 1;
    int num1[10] = { 1, 2, 3, 4 };
    char char2[] = "abcd";
    const char* pChar3 = "abcd";
    int* ptr1 = (int*)malloc(sizeof(int) * 4);
    int* ptr2 = (int*)calloc(4, sizeof(int));
    int* ptr3 = (int*)realloc(ptr2, sizeof(int) * 4);
    free(ptr1);
    free(ptr3);
}

/*
选项: A.栈 B.堆 C.数据段(静态区) D.代码段(常量区)
globalVar在哪里？____ staticGlobalVar在哪里？____
staticVar在哪里？____ localVar在哪里？____
num1 在哪里？____
char2在哪里？____ *char2在哪里？___
pChar3在哪里？____ *pChar3在哪里？____
ptr1在哪里？____ *ptr1在哪里？____
*/
```

全局变量和静态变量都在静态区，所以`globalVar   staticGlobalVar   staticVar`都在静态区；普通的局部变量都放在栈中：`localVar   num1   char2   pChar3   ptr1`；`char2`是数组地址，或者说首元素地址，`*char2`是局部数组，仍是局部变量，所以还是位于栈中，不过要注意`"abcd"`还是在常量区的，是以`"abcd"`这个常量初始化了数组；`pChar`是一个字符指针，指向常量字符串`"abcd"`的第一个字符，`*pChar`是常量字符串本身，所以存在常量区；`*ptr1`是堆上的某处空间。

![image-20241010125650824](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410101256070.png)

# 内存泄露（略讲）

内存泄露对一般的程序来说其实没有什么大的影响，但对于长时间运行的程序来说，比如服务器上的程序，就是致命的。由于内存用了不还，系统手头剩下的内存就越来越小，这样程序和系统都会越来越卡，服务器还不能随便关机重启，服务器是能运行就继续运行的，但又卡得受不了，只能重启，重启之后服务还不能立刻上线，因为要一段时间初始化，用户得不到服务，搞出事故，不赔款就不错了。

# 完