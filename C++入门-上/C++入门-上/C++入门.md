# C++入门

## 前言

1982年，Bjarne Stroustrup博士在C语言的基础上引入并扩充了面向对象的概念，发明了一种新的程序语言。为了表达该语言与C语言的渊源关系，命名为C++。  C++最初的创建目的是为了解决C中一些悬而未决的问题，所以在C++入门的初期阶段，我们将会逐一分析C中的种种缺陷，并看看C++的应对方案。

## 命名冲突

在使用C语言开发设计时，常常会遇到这种情况：出现了相同的标识符，这些标识符可能指代不同的变量，类型，函数······，此时，编译器就会无法分辨它们，从而出现错误。

C++的应对策略是提出了一种叫“命名域私有化”的概念。其实，C中并没有“命名域”这个概念，不过，为了方便描述，我们现在把“命名域”的概念扩展到C中，我们说，C中的“命名域”是完全公有化的，不存在私有区域，这意味着所有的标识符都是公开裸露的，一旦标识符相同，就会存在冲突，比如下面的代码：

```c
// The header file "stdlib.h" contains the definition of the function rand.
#include<stdlib.h>
#include<stdio.h>

// Naming conflict when using "rand" to refer to a variable.
int rand = 0;

int main()
{
	printf("%d ",rand);
	return 0;
}
```

运行时，报错，提示：“rand”: 重定义；以前的定义是“函数”。

与标准库中的标识符冲突并不是致命的，致命的是，对于日后的工作来说，同一个项目常常需要多人协同工作，若是出现了命名冲突，就只能让团队中的某位成员牺牲一下，把与别人冲突的标识符进行修改。

C++则允许命名空间的私有化，处于私有化空间中的标识符没有公开裸露，如不进行说明，编译器不会进入该私有空间寻找标识符。

命名空间的定义，需要用到关键字`namespace` ，其后接命名空间的名字，一般是项目名，练习时，就用自己的名字；用于指代该命名空间，然后使用大括号"{}"界定命名空间的范围，"{}"内的标识符都处于命名空间内。

标准库中的标识符都位于"std"这个命名空间内，同名的命名空间会进行合并。注意，命名空间里不要有宏，宏在预处理阶段就会被替换，而命名空间是链接时用的。

```c++
#include<stdlib.h>
// The C++ header file "cmath" defines the absolute value function abs.
#include<cmath>

namespace Whisper
{
	int rand = 1;

	int abs(int x)
	{
		if (x < 0)
			return -x;
		else
			return x;
	}

	typedef struct Node
	{
		struct Node* pNext;
		int val;
	}Node, * pNode;

	// Namespaces can have nested definitions.
	namespace Wind
	{
		int rand = 2;

		int abs(int x)
		{
			if (x < 0)
				return x;
			else
				return -x;
		}

		typedef struct Node
		{
			struct Node* pNext;
			int val;
		}Node, * pNode;
	}
}
```

 对命名空间内标识符的使用有三种方法：特别指定，局部展开，完全展开。

特别指定：在使用的标识符前加上命名空间名和两个冒号，注意，若要对结构体这类需要使用关键字修饰的标识符，命名空间和两个冒号要写在标识符前，而不是关键字前。关键字的作用只是提示后面的标识符是什么，比如对于上面的`Node`，前面的`struct`只是提示后面的标识符是结构体而已，这个结构体的名字是`Node`而不是`struct Node`；当然，我这里用`typedef`进行类型重命名了，所以可以不加`struct`：

```c++
#include<stdio.h>

int main()
{
	printf("%d\n", Whisper::rand);
	printf("%d\n", Whisper::Wind::rand);
	int x = 4;
	printf("%d\n", Whisper::abs(x));
	printf("%d\n",Whisper::Wind::abs(x));
	printf("%d\n", std::abs(x));
	struct Whisper::Node a = { 0 };
	struct Whisper::Wind::Node b = { 0,1 };
	printf("%d\n", a.val);
	printf("%d\n", b.val);
	return 0;
}
```

![image-20240914105048567](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202409141050695.png)

局部展开，提示编译器下文使用的标识符都默认为某个命名空间里的标识符

 ```c++
 using Whisper::Wind::Node;
 
 int main()
 {
 	printf("%d\n", Whisper::rand);
 	printf("%d\n", Whisper::Wind::rand);
 	int x = 4;
 	printf("%d\n", Whisper::abs(x));
 	printf("%d\n",Whisper::Wind::abs(x));
 	printf("%d\n", std::abs(x));
 	struct Node a = { 0 };
 	struct Node b = { 0,1 };
 	printf("%d\n", a.val);
 	printf("%d\n", b.val);
 	return 0;
 }
 ```

全局展开，将命名域公有化，使其中的成员完全裸露

```c
using namespace Whisper;

int main()
{
	struct Node a = { 0 };
	struct Node b = { 0,1 };
	printf("%d\n", a.val);
	printf("%d\n", b.val);
	return 0;
}
```

前面加上会命名冲突，所以不加了。

所以尽量不要全局展开，全局展开非常危险，尽量全用特别指定，特别指定是最安全的。而且C++代码最好都引用C++头文件，C头文件中的标识符都是公开裸露的。

## 输入输出

在C中，输入输出都需要手动控制格式，而在C++中，编译器将自动识别数据类型，不需要手动控制。

```c++
// To better distinguish between C and C++ header files, none of the C++ header files have ".h".
#include<iostream>

int main()
{
	std::cout << "hello world" << std::endl;
	int i, j;
	std::cin >> i >> j;
	std::cout << i << std::endl;
	std::cout << j << std::endl;
	return 0;
}
```

其中，`cout`和`cin`用于描述流对象，`cout`指标准输出对象（控制台），`cin`指标准输入对象（键盘）；`<<`叫做流插入运算符，`>>`叫做流提取运算符，它们形象地表示了信息的流向，它们的优先级都是先左后右，`endl`就是换行号。

![image-20240914125749518](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202409141257725.png)

C++的输入输出还有很多内容，但这里毕竟只是入门，所以就不说了。如果对输入输出有更多要求，就先用C吧。

## 缺省参数

在C++中，可以为函数参数提供一个默认值，当调用者未输入参数时，则使用该默认值。为了明确形参与实参之间的对应关系，缺省参数必须从由往左连续设置，使用含有缺省参数的函数时，参数的输入必须是从左往右连续输入。

```c++
#include<iostream>

namespace Whisper
{
	void Func1(int a = 10);

	void Func2(int a, int b = 3, int c = 7);

	void Func3(int a = 1, int b = 2, int c = 3);
}

namespace Whisper
{
	void Func1(int a)
	{
		std::cout << a << std::endl;
		return;
	}

	void Func2(int a, int b, int c)
	{
		std::cout << a << std::endl;
		std::cout << b << std::endl;
		std::cout << c << std::endl;
		return;
	}

	void Func3(int a, int b, int c)
	{
		std::cout << a << std::endl;
		std::cout << b << std::endl;
		std::cout << c << std::endl;
		return;
	}
}

int main()
{
	Whisper::Func1();
	Whisper::Func1(15);
	Whisper::Func2(1);
	Whisper::Func2(1, 2);
	Whisper::Func2(1, 2, 5);
	Whisper::Func3();
}
```

当函数既有定义，又有声明时，缺省参数必须在声明处设置。

![image-20240914142459073](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202409141424184.png)

## 函数重载

在上面的输入输出过程中，我们发现C++可以自动进行类型识别，这是怎么做到的呢？其实这就是用函数重载实现的。计算机学中的重载是从语言学中延伸出的概念。重载，指的是一个词或表达在不同语境中具有多重意义或用法的现象；或者说，一词多义。在程序开发的过程中，常常会遇到这种情况：有一系列函数，它们的功能其实都一样，比如在屏幕上打印某些信息，但由于输入的数据不同，在C中，它们必须拆成完全不同的函数，比如，下面这样：

```c
// In C, functions with the same name are not allowed.
void Swap(int* x, int* y)
{
	int tem = *x;
	*x = *y;
	*y = tem;
}

void Swap(double* x, double* y)
{
	double tem = *x;
	*x = *y;
	*y = tem;
}
```

但在C++中，就允许出现上面的同名函数。回到重载的定义，重载只是看似相同，但结合上下文，可以知道它们的实际意义是不相同的。比如，对于中国乒乓球和足球来说，都可以用“谁也赢不了”来形容，但很明显，意思是不相同的。

那在C++中，这上下文到底指的是函数的哪部分呢？指的是函数的类型。这有两层含义：一，参数个数都不同，比如，两份同名函数，一个有两个参数，另一个有一个参数；二是，参数的类型顺序不同，同样都有两个参数，类型都是整型和浮点型；不同的是，这个函数从左往右是先整型再浮点，那个函数是先浮点再整型。注意，不要看形参名。而是要看形参的类型，形参名只是指代这个形参而已，就像数学里的函数，判断它们相同的两个准则是对应关系和定义域，而不是变量名。

函数重载的实现原理并不难。在C中，对于一个函数的描述只有函数名字，所以当出现同名函数时，链接过程中，符号表中就会出现两个相同的标识符，而且，这两个标识符指向的函数是具有实际内容的，此时就会发生冲突，编译器无法分清到底谁是谁。而在C++中，我们对于函数的描述扩展了，不仅仅有函数的名字，而且还有对参数类型的描述。

```c
void Swap(int* x, int* y)
{
	int tem = *x;
	*x = *y;
	*y = tem;
}

// void Swap(double* x, double* y)
// {
// 	double tem = *x;
// 	*x = *y;
// 	*y = tem;
// }

int main()
{
    int i = 1;
    int j = 0;
    Swap(&i, &j);
}
```

对于这份.c文件，我们使用gcc看一看汇编。

![image-20240918180208939](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202409181802193.png)

可以看到，它是直接拿函数名进行调用的。

改成C++后再试一试

![image-20240918180630580](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202409181806769.png)

前面的“4”是什么意思，这个“4”用来描述函数名的字符数，"Swap"是不是有四个字符呢？后面的部分就是在描述参数类型了，"p"表示指针，"i""d"分别代表"int"和"double"，再后面的"s"代表有两个参数。此时在符号表里进行链接时，用的就不只是函数名了。

其它编译器也是如此，只不过它们在函数名和类型之间的划分以及类型的指代存在一些不同，总体上都是一样的。

注意，返回值不是函数重载的判断因素。原因也很简单，调用的时候分不清到底用这个返回类型的函数，还是那个类型的函数。当然，也可以强行改变C++的函数调用规则，但那样的话，本来C的调用规则还是很简洁的，这样一改，得不偿失。

## 引用

在C中，对变量进行跨栈帧操作时，就必须使用指针对其进行指代，而且是间接指代。而在C++中，有一个名叫“引用”的语法，引用是直接指代，相当于为变量取别名，而且由于这个别名是种类型，所以可以跨栈帧传递。

由于是取别名，所以它们指向的地址都是一样的，换言之，它们指向相同的内存块。

```c++
int main()
{
	int n = 0;
	int& a = n;
	int& b = n;
	int& c = a;

	std::cout << &n << std::endl;
	std::cout << &a << std::endl;
	std::cout << &n << std::endl;
	std::cout << &c << std::endl;
	return 0;
}
```

![image-20240918203538630](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202409182035745.png)

或许可以再看看汇编：

![image-20240918203713706](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202409182037921.png)

mov dword ptr [n],0    就是把0赋给以n为起始地址的四个字节

lea rax, [n]   就是把n的地址加载到（拷贝一份）到rax这个寄存器里

mov qword ptr [a], rax    是以rax中存储的，向后qword ptr（8个字节【因为x64的地址是八个字节】）的数据（就是n的地址），存到a的地址处

mov rax, qword ptr ptr [a]   就是把a地址指向的八字节内存快中存储的地址（其实就是n的地址）,加载到rax这个寄存器中

mov qword ptr [c], rax   就是把rax中存储的地址赋到c的地址处

![image-20240918210320085](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202409182103201.png)

所以虽然我们日常说引用类型的变量与引用的对象共用一个内存块，但从汇编底层来说，引用变量确实是有空间消耗的，实际上，引用底层上还是借助于指针实现的，只不过包装地更好看了。

有了引用之后，交换函数就可以写成这样了：

```c++
void Swap(int& a, int& b)
{
    int tem = a;
    a = b;
    b = tem;
}

void Swap(double& a, double& b)
{
    double tem = a;
    a = b;
    b = tem;
}

int main()
{
    int i = 1;
    int j = 0;
    double m = 2.4;
    double n = 1.4;
    Swap(i, j);
    Swap(m, n);
}
```

引用的注意点：

引用类型的变量在定义时必须要初始化，不然怎么知道引用的是谁；

引用变量不能更改自身引用的对象，这是因为，引用类型的变量在初始化确认引用对象后，其行为就和所引用的对象相同，所以无法更改自身的引用对象。

下面说说引用的具体应用场景。

1. 像返回指针那样，返回非调用函数栈帧内的变量

   ```c++
   int& SeqListReadFront(PSeqList ps)
   {
       assert(ps->valid);
   	return ps->p[0];    
   }
   ```

2. 修改返回值。在C中，函数的返回值并不是函数return的那个值，而是那个值的拷贝，所以C中函数的返回值具有常数属性，不能用函数返回值修改return的值；而在C++中，若返回的变量是引用类型，则返回的就是调用函数内return的那个值，此时返回的是个变量，而不是常数，所以可以修改。

   ```c++
   #include<assert.h>
   
   typedef struct SeqList
   {
   	int* _P;
   	int _Size;
   	int _Capacity;
   }SeqList, *pSeqList;
   
   
   // Modify the value at position i in the order table.
   int& SeqListModI(pSeqList ps, int i)
   {
   	assert(ps->_Size > i);
   	return ps->_P[i];
   }
   
   pSeqList Init(void)
   {
   	int* p = (int*)malloc(sizeof(int) * 10);
   	if (p == NULL)
   		return NULL;
   	pSeqList ps = (pSeqList)malloc(sizeof(SeqList));
   	if (ps == NULL)
   		return NULL;
   	ps->_Capacity = ps->_Size = 10;
   	ps->_P = p;
   	int cir = 0;
   	for (; cir < 10; cir++)
   	{
   		ps->_P[cir] = cir;
   	}
   	return ps;
   }
   
   void SeqListPrint(pSeqList ps)
   {
   	int cir = 0;
   	for (; cir < ps->_Size; cir++)
   	{
   		std::cout << ps->_P[cir] << " ";
   	}
   	std::cout << std::endl;
   }
   
   int main()
   {
   	pSeqList ps = Init();
   	SeqListPrint(ps);
   	SeqListModI(ps, 2) = 20;
   	SeqListModI(ps, 5) = 23;
   	SeqListModI(ps, 7) = 25;
   	SeqListPrint(ps);
   	return 0;
   }
   ```

   ![image-20240919090712592](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202409190907826.png)

   注意，上面的不过是示例而已，展示一下效果，实际不这样写（上面的写法有种既不是C又不是C++的感觉，是种不伦不类的写法）；实际怎么写呢？那要后面说，还有没学到的内容。

   ----


### 常引用

常引用（也称`const`引用）是C++中的一种保护机制，可以对引用对象进行保护。此时的引用类型变量（或者说被引用的对象）是无法被修改的，强行修改，编译器会主动报错。

```c++
void f(const int& val)
{
    val = 8;
}

int main()
{
    int i = 0;
    f(i);
    return 0;
}
```

比如上面的代码就是无法编译通过的。

说到常引用，还要说到引用的权限要求：

- 权限可以被传递
- 权限可以被缩小
- 权限不能被放大

对于一个本来就是被`const`修饰的变量，因其具有常属性，所以引用时也必须使用常引用，否则会报错；对于普通变量，既可以用普通引用，也可以用常引用。

除此之外，常引用还可以用于锚定临时变量，延长被引用对象的生命周期。

```c++
int main()
{
	int i = 1;
	double& j = i;
	return 0;
}
```

上面的代码无法通过编译，是因为这实际是一种权限的放大。让我们先看下面的代码：

```c++
int main()
{
	int i = 0;
	double j = i;
	return 0;
}
```

```assembly
int main()
{
00007FF783E81C30  push        rbp  
00007FF783E81C32  push        rdi  
00007FF783E81C33  sub         rsp,128h  
00007FF783E81C3A  lea         rbp,[rsp+20h]  
00007FF783E81C3F  lea         rcx,[__A963CB2B_C++入门-上\C++入门-上\test@cpp (07FF783E93069h)]  
00007FF783E81C46  call        __CheckForDebuggerJustMyCode (07FF783E813A2h)  
00007FF783E81C4B  nop  
	int i = 0;
00007FF783E81C4C  mov         dword ptr [i],0  
	double j = i;
00007FF783E81C53  cvtsi2sd    xmm0,dword ptr [i]  
00007FF783E81C58  movsd       mmword ptr [j],xmm0  
	return 0;
00007FF783E81C5D  xor         eax,eax  
}
```

观察汇编，我们发现，在C/C++中，若发生了类型转换，编译器会先把变量转换成需要的类型，然后存储在某个地方，然后再从这个地方，把数据拷贝过来。比如上面的汇编代码，`cvtsi2sd    xmm0,dword ptr [i]`意为将内存地址 `i` 中的 4字节整数值转换为双精度浮点数，并存储到 `xmm0` 寄存器中。`movsd       mmword ptr [j],xmm0`意为将 `xmm0` 寄存器中的双精度浮点数值移动到内存地址 `j` 所指向的位置。所以引用的实际是寄存器`xmm0`中的值，这是一个常量，所以引用需要用常引用；不过这个常引用锚定的不是寄存器`xmm0`本身，不是说这个寄存器被锁定了，不能再写入了，它真正锚定的是地址[j]处的那处空间；还记得上面我们说过引用实际上底层是有空间消耗的。我们看上面的例子，它拷贝的是寄存器rax里的数据，rax里的是地址，所以引用的底层消耗就是被用来存储这个地址了；那这里为什么是拷贝值呢？因为本来，它确实应该找个地方，存一下数值，然后再找个地方，去存个地址，这个地址指向的就是那个拷贝数值的地方，但这样做非常啰嗦，所以被优化成一步了，只拷贝数据，此时就相当于真的重新建立了一个变量，你可以打印打印地址看看。

```c
int main()
{
	int i = 0;
	const double& j = i;
	std::cout << &i << std::endl;
	std::cout << &j << std::endl;
	return 0;
}
```

![image-20240920172029211](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202409201720400.png)

## 内联函数

C++的内联函数是C中宏的上位替代。在学内联函数之前，让我们先来看看宏的缺点。

宏有很多缺点，具体我就不一一罗列了。大致说一下，宏没有类型检查，宏会破坏代码原有的执行顺序，宏的作用范围不好控制等等。其中特别是第二条，宏会破坏代码的原有顺序，学过宏之后，宏参数我都是无脑加括号的，直到有一天，我遇到了这个（取自预处理详解那篇文章）：

![image-20240922125216736](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202409221252007.png)

对于这个代码，加括号反而会出错，至此之后，我对宏的好感度就一落千丈，几乎不用了，唯一用的场景是用宏写函数。

C++引入了内联函数的概念。对于某个函数来说，可以使用C++关键字`inline`来对其进行修饰，此时这个函数就具有了成为内联函数的可能。这里为什么会说是“可能”呢？别着急，我后面会说的。

内联函数兼具宏和函数的优点，在代码执行的过程中，它会像宏那样被替换，执行顺序却是以函数的执行顺序进行的，比如，下面的这份代码：

```c++
inline int add(int a, int b)
{
	return a + b;
}

int main()
{
	int i = 3;
	int j = 6;
	int k = add(i, j);
	return 0;
}
```

我们使用VS2022观察汇编时，发现add是被call的，也就是被调用的，这也不是替换呀。VS这样做是为了解决宏无法被调试的缺点，此时内联函数就像普通函数一样，可以被调试。不过底层上还是被替换的，如何看底层呢？需要对VS进行一些配置。

![image-20240922131056118](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202409221310345.png)

![image-20240922131424722](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202409221314415.png)

![image-20240922131540034](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202409221315169.png)

![image-20240922131848350](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202409221318446.png)

![image-20240922132114064](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202409221321154.png)

别忘了实验之后再改回去。

此时再看反汇编就会发现这个函数被展开而不是被调用了。

![image-20240922132542370](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202409221325576.png)

可以看到，内联函数像宏一样，没有再建立新的函数栈帧，或者说，没有函数栈帧的开辟和函数调用完后的善后（回收），它的函数内部操作过程是在原函数（在这里指的是main函数）的栈帧上进行的。

接下来就要填坑了，上面我们说过，被`inline`修饰的函数具有成为内联函数的可能，为什么要说可能呢？这是因为，内联函数对编译器来说是建议而非命令，如果编译器认为这个函数不适合作内联函数，那它仍然会把这个函数当做普通函数来处理。

```c
inline int add(int a, int b)
{
	return a + b;
}

inline int f(int m, int n)
{
	int x = m + n;
	x++;
	x *= m;
	x *= n;
	x--;
	x += 2;
	x--;
	x *= 2;
	x *= 1;
	x *= 4;
	x *= 5;
	x *= 7;
	x *= 4;
	x *= 3;
	x *= 2;
	x *= 9;
	x--;
	x++; 
	x--;
	x++;
	x *= 4;
	x *= 3;
	x *= 2;
	x *= 9;
	return x;
}

int main()
{
	int i = 3;
	int j = 6;
	int k = add(i, j);
	int x = f(i, j);
	return 0;
}
```

观察反汇编可以看到，f是被call（调用）的。

![image-20240922134447813](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202409221344031.png)

为什么长代码会被认为不适合做“内联函数”呢？我们粗略比较一下，假如一个代码转换成汇编之后是100行，整个项目里有100个地方调用它，如果都以内联的方式去使用，有10000行汇编，如果以调用的方式去使用，行数的量级是百，首先至少要去调用，有那行call，于是就有100行了，然后要看看有几个参数，有没有返回值，比如上面那个f，有两个参数，也有两个返回值，于是就要另外再加300行，不过再怎么说，这量级还是百，跟10000比，还是少了不少。

行数多会出什么问题呢？最明显的，就是程序本身变大了，此外还有一些问题，在这里就不展开了。

不过内联函数也不是什么问题都没有。当内联函数的声明和定义分立在不同的文件中时，内联函数会出现链接错误。

```c++
// F.h
#pragma once

inline int add(int a, int b);

int f(int a, int b);

// F.cpp
#include"F.h"

inline int add(int a, int b)
{
	return a + b;
}

int f(int a, int b)
{
	return add(a, b);
}

// main.cpp
#include"F.h"

int main()
{
	int i = 3;
	int j = 3;
	int k = add(i, j);
	return 0;
}
```

`error LNK2019: 无法解析的外部符号 "int __cdecl add(int,int)" (?add@@YAHHH@Z)，函数 main 中引用了该符号`

为什么会出现链接错误呢？之前我们说过，链接是通过符号表让多个文件建立联系的，但对于内联函数来说，由于它不是通过调用来实现的，或者说，它的行为和宏有相似之处，所以它不会被收录到符号表里，于是多个文件就不会建立起有效联系，就出现了链接错误。

当编译器在`main.cpp`中看到标识符`add`时，它会向前搜索，根据`main.cpp`中头文件`F.h`的展开意识到`add`是一个内联函数，于是它就会尝试把`add`展开，但这里只是`add`的声明，而无`add`的定义，所以无法展开。如果`F.h`中`add`不加`inline`，那编译器向前搜索就会认为`add`是个函数，于是就会在符号表中进行寻找，但在`F.cpp`中，`add`是内联函数，所以不在符号表上，编译器在符号表上无法找到`add`的定义，于是链接失败。

我们把代码稍微修改一下：

````c++
int main()
{
	int i = 3;
	int j = 3;
	int k = f(i, j);
	return 0;
}
````

然后发现就可以运行了。当编译器在`main.cpp`中看到标识符`f`时，它会向前搜索，根据`main.cpp`中头文件`F.h`的展开意识到`f`是一个函数，于是就会在符号表上对`f`进行寻找，然后它就会在`F.cpp`的符号表里找到`f`，于是进入到`F.cpp`中的`f`函数里，然后在`f`里，编译器发现了标识符`add`，它向前搜索，根据`F.h`的展开，意识到`add`是内联函数，于是就会尝试把`add`展开，然后因为它们在同一个文件里，所以就找到了`add`的定义，于是展开成功了。链接成功，程序可以正常运行。

不过如果把VS的配置改回来，即使使用`add`，仍可以正常运行，这是因为VS此时认为`add`不适合成为内联函数，于是以正常函数的方式与使用。

怎么解决呢？既然声明和定义分离会出问题，那干脆直接把声明和定义全放在头文件里，而且由于定义本身就是一种声明，所以头文件里直接写定义就行。

## auto

这里说的是C++11后的auto，C++11前也有一个auto，不过由于没什么用，已经被彻底弃用了。我们只需要知道C++11的auto就行了。

在C++后续的学习过程中，我们会遇到一些很长的类型，此时就可以用auto进行替代。auto不是类型，而是类型的占位符，有的游戏场景在进行内部测试时，场景中的人物可能不是真的用对话的人物模型，而是用一个已经公开的人物模型进行替代，这可能出于对人物形象的保密以及人物模型还未优化完毕等方面的考虑。编译器会根据上下文信息，推导出auto的类型，在编译时把auto替换成应有的类型。

```c++
int main()
{
    int i = 0;
    auto j = i;
    auto& k = i;
    return 0;
}
```

比如在上面的代码中，编译器会根据赋值号右边的数据类型，自动推导出j和k的类型。

在C++中，可以通过typeid().name()查看变量类型。

```c++
int main()
{
	int i = 0;
	auto j = i;
	auto& k = i;
	std::cout << typeid(i).name() << std::endl;
	std::cout << typeid(j).name() << std::endl;
	std::cout << typeid(k).name() << std::endl;
	return 0;
}
```

![image-20240922163619653](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202409221636933.png)

当然，引用严格来说不是类型，这里显示的是被引用对象的类型。

auto也不是什么地方都能用的。比如auto不能用于函数参数或返回值，以及不能用于数组类型。为什么不能用也很简单，因为在这些场景下根据上下文推导不出应有类型。

auto还有一些其它应用，等用到再说。

## 范围for

在C++11之前，遍历一个数组要这样做：

```c++
int main()
{
	int Array[] = { 2,4,6,8 };
	size_t sz = sizeof(Array) / sizeof(Array[0]);
	int i = 0, tem;
	for (i = 0; i < sz; i++)
	{
		tem = Array[i];
		std::cout << tem << " ";
	}
	std::cout << std::endl;
	return 0;
}
```

C++11中引入了范围for的用法，专门用于对数组的遍历。

```c++
int main()
{
	int Array[] = { 2,4,6,8 };
	for (auto& mem : Array)
	{
		std::cout << mem << " ";
		mem *= 2;
	}
	std::cout << std::endl;
	for (auto tem : Array)
	{
		std::cout << tem << " ";
	}
	std::cout << std::endl;
	return 0;
}
```

![image-20240922165715032](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202409221657209.png)

每轮循环，范围for都会依据数组成员类型创建一个变量，这个变量用来接收数组内的各个成员。在上面的代码中，第一个范围for使用了引用，因此可以修改数组成员，第二个范围for就是纯粹接收，然后打印各个成员。

注意，由于C/C++的数组传参实际是传数组首元素指针，所以经过传参的数组是不能用范围for遍历的，还是要按照以前的方式去遍历。

## 空指针nullptr

我们知道，在C中，NULL实际上是一个宏`#define NULL ((void*)0)`，而在C++中，NULL被定义为`#define NULL 0`，结合C++中的函数重载语法，就可能造成类型歧义的问题：

```c++
void f(int)
{
    std::cout<<"f(int)"<<std::endl;
}

void f(int*)
{
    std::cout<<"f(int*)"<<std::endl;
}

int main()
{
    f(0);
    f(NULL);
    f((int*)NULL);
    return 0;
}
```

C++中允许函数只进行类型检查，而不传参，C就不行了。

![image-20240922173833232](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202409221738481.png)

为此，从C++11开始，C++引入了关键字`nullptr`用来表示空指针。为什么不直接改`NULL`呢？因为有些人可能正是用这个“特性”来运行项目的，考虑到向前兼容，C++委员会没有直接在`NULL`上动手。其实`nullptr`底层就是`void*类型的0`，然后可能根据实际情况再去调整成具体的指针类型。

# 完