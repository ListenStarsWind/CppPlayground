# polymorphism  advanced

## preface

其实，本篇文章并不是真正的多态进阶。它只是一个多态的结尾罢了。多态最精华的，最重要的部分都在上篇文章中，本篇的绝大多数内容其实只需要了解即可。

## location_of_virtual_table

首先我们要详细说说虚函数表到底在哪里，虚函数对象本体肯定是存在代码段里的，我们现在想看看虚函数表存在何处？我们知道C/C++内存布局是这样的

![image-20241121140800880](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411211408090.png)

那这虚函数表到底在哪里呢？我们可以推理一下，首先它应该不在栈上，因为在之前的文章我们看到同样的对象使用的是同一张虚函数表，并且我们也可以看到多态是可以全局实现的，而栈上的数据都只在栈帧释放前有效，所以它应该不在栈上；全局变量和堆区上的数据可被修改，对于虚函数表来说似乎有些危险，所以它大概存在常量区。口说无凭，我们还是像进程地址空间那样写个程序来打印一下。

```cpp
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
		// 堆区
		void* p1 = new int;
		void* p2 = new int;
		void* p3 = new int;

		// 常量字符串
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

```

和进程地址空间一样，不要随意调整代码顺序，那样会触发编译器的优化机制，这种机制对项目工程来说是有益的，但它会影响我们的逻辑，不利于教学。

我们先说说`(function*)(*((void**)&t))`是什么，在上篇文章中，我们可以知道含有虚函数的类对象，其内部的第一个成员实际是个指针，这个指针指向着虚函数表，`&t`自然不比多说，就是取到对象`t`的地址，由于虚函数表指针是对象中的第一个成员，所以`t`的地址和这个虚函数表指针的地址都是一样的，这也好理解，毕竟我们都知道，对计算机来说，它其实并不认识`a, b, c, d`这些变量，它使用这些变量都是先找到这些变量的起始地址，然后根据类型去取字节，是`int`，那就从变量地址开始向后取四个字节，是`char`，那就只取一个字节，`(void**)&t`即是把`t`的地址强行转换成了二级泛型指针，我们也知道泛型指针在C中是用来适应类型转化的，如果函数参数使用具体指针那就容易出现类型不匹配的问题，但用泛型指针就不会出现匹配问题，不过我们这里使用的是二级泛型指针，这意味`(void**)&t`后的指针指向一处`void*`大小的空间，这处空间存着一个泛型指针，之后我们对`(void**)&t`解引用之后就能得到虚函数表指针了，不过此时指针的类型是`void*`，而虚函数表是一个函数指针数组，所以该数组的类型应该是函数指针的指针，所以我们又将其转化成了`(function*)`，顺便说一声，注意函数指针的使用，它和别的指针无论是类型重定义还是定义变量行为都不太一致。

我们接着说说`&base::functi`，指定类域或许可以理解，但为什么要加取地址号呢？这是为了向编译器强调我想找到成员函数的地址，因为不加取地址号的`base::functi`对编译器来说更像是函数调用，取地址能够避免歧义。

为了方便我们的观察，我们使用`x86`环境，运行结果如下。

![image-20241121155021159](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411211550313.png)

所以我们可以说，虚函数表是存储在常量区的。

现在让我们看看为什么要用`(function*)(*((void**)&t))`。

比如：在`x86`环境下，指针的大小是四字节，而`int`的大小也是四字节，为什么不直接`(int)t`?

因为类型转换是有限制的，只有类型相近的情况下，类型转换才可进行，`int`能转化成`char`或`long long`是因为它们都是整型，`int`能转成`double`是因为这两个类型都是表示数的，但这里不行，`base`是一个class, class 和int的差别可大了，转不动。另外这种转换仅能适用于`x86`环境，因为位数不同，指针大小不同，我们上面的代码哪个位数都可以跑。

![image-20241121155044280](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411211550334.png)

再如：为什么不使用`(function*)&t`的形式，因为这种写法就相当于把`t`自身当做虚函数表传过去，而不是`t`里的虚函数表指针传过去。

## Virtual function table in a single inheritance chain

下面说说单继承链中的虚函数表，所谓单继承链就是多个连续的单继承。比如B继承A，C继承B，为了方便描述，我们把这里的A称之为顶层，把这里的C称之为底层，其余的称为中间层。

接下来我们看这份代码

```cpp
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

	void func()
	{
		I i;
		J j;
		K k;
	}
}
```

![image-20241121162506881](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411211625376.png)

我们看到`j`的监视窗口中的虚函数表只有两个，它真的只有两个吗？

![image-20241121162622192](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411211626247.png)

![image-20241121162639675](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411211626714.png)

其实不然，我们看一下内存窗口

![image-20241121162856026](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411211628080.png)

这里我要额外说一声，VS虚函数表的最后一个成员为`nullptr`，表示停止，意思是虚函数表到这里就停止了，后面的数据都不是虚函数表里的内容。不过要注意的是，G++没有这套机制，它虚函数表的最后一个成员就是函数指针。

所以我们就能看到`j`的虚函数表中实际有4个元素，除了最后一个是空指针外其它的元素都是有效的，也就是说，只要是虚函数，它的指针就必定会存在虚函数表中，为什么监视窗口只显示了两个元素呢？因为监视窗口不是原始数据，而是微软的工程师们按照自己的逻辑优化显示的，这些工程师们可能出于某些方面的考虑，认为不把虚函数表中的数据全显示出来会比较好。总而言之，VS的监视窗口对虚函数表中的数据不是完全显示的，如果真的想要看虚函数表一定要从内存窗口看。

接下来看看`k`

![image-20241121165305045](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411211653077.png)

![image-20241121165321642](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411211653676.png)

同样的，监视窗口并不完全显示虚函数表，而内存窗口的显示是完全的。

接下来我们换个更方式看虚函数表，通过打印的方式。

```cpp
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
```

我们利用VS虚函数表最后一个元素是空指针的特点，可以直接打印虚函数表，同时，我们也可以再用函数指针调用一下它们。

![image-20241121171947746](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411211719804.png)

## Virtual function table in multiple inheritance

在多继承中，虚函数表又是怎么样的呢？

```cpp
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
		virtual void func() { cout << "base2::func" << endl; }
	private:
		int _n = -1;
	};

	class derive : public base1, public base2
	{
	public:
		virtual void func2() { cout << "derive::func2" << endl; }
		virtual void func3() { cout << "derive::func3" << endl; }
		virtual void func() { cout << "derive::func" << endl; }
	private:
		int _i = 0;
	};

	void func()
	{
		derive d;

		VFTPprint((function*)(*((void**)&d)));
		VFTPprint((function*)(*((void**)((char*)&d + sizeof(base1)))));
	}
}
```

由于没有使用虚拟继承，所以对象`d`中的虚函数表只是简单分立，并且由于`derive`中的虚函数全部实现了重写，所以监视窗口倒也算是全部显示了。

![image-20241121191051692](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411211910051.png)

![image-20241121191117995](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411211911038.png)

![image-20241121191407716](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411211914753.png)

![image-20241121191516743](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411211915778.png)

![image-20241121191456520](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411211914559.png)

![image-20241121191624052](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411211916091.png)

现在看起来好像还没什么问题，接下来看看我们的两个`VFTprint`

![image-20241121192203959](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411211922018.png)

你看那两个`derive::func`，是不是前面地址不一样。一个函数怎么会有两个指针？

怎么回事呢？接下来我们看看汇编，VS2022我试过了，它的汇编代码不太好看，所以用VS2019。

![image-20241121214329283](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411212143421.png)

![image-20241121214440320](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411212144417.png)

前面那些汇编我们就不看了，总结来说，就是把虚函数表中的指针加载到`eax`中，然后`call eax`，我们直接来到这一行。

![image-20241121214948499](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411212149590.png)

![image-20241121214930710](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411212149835.png)

`F11`

![image-20241121215045527](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411212150634.png)

我们就来到了`eax`存储的地址处，或者虚函数表指针所指向的位置，接着继续`F11`

![image-20241121215255723](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411212152819.png)

现在才来到了`func`中的第一行指令前，所以前面我说过，虚函数表中的指针不是直接指向函数对象本体的。

接下来我们看`p2`

![image-20241121215510020](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411212155104.png)

也是直接来到`call`

![image-20241121215605172](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411212156268.png)

![image-20241121215627533](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411212156566.png)

`F11`

![image-20241121215718229](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411212157326.png)

我们就来到了虚函数表指针指向的位置，接着我们`F11`，这样就能跳转到`06C2E70h`

![image-20241121215916319](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411212159404.png)

然后就能跳转到`06C1037h`，你看这个界面熟不熟悉。

![image-20241121220020577](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411212200676.png)

跳转到`06C2DF0h`

![image-20241121220103890](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411212201984.png)

这就来到了`func`中，也就是说对于`p2`来说，它通过一系列中间层又来到了`p1`走过的路径，之后自然能找到`func`。

为什么`base2`中的`func`比`base1`中的`func`多绕几层？这和成员函数的`this`指针有关。

由于`derive::func`是`class derive`中的函数，所以它理应支持`this->_i`这种访问`derive`成员变量的行为，所以`func`中的`this`指针应该指向`derive`对象，或者说，`this`的值应该是`derive`对象的起始地址，让我们看看`base1`对象是怎么传参的。

在这里，它其实是通过寄存器`ecx`进行`this`传参的

![image-20241121214948499](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411212149590.png)

由于`p1`是`base1`，`base1`是先被继承的，所以`p1`的值和`derive`对象的起始地址相同，并且我们可以看到`mov ecx, dword ptr [p1]`，这条指令的作用就是把`p1`这个指针的值赋给`eax`。

而在`base2`中

![image-20241121215510020](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411212155104.png)

`mov ecx, dword ptr [p2]`同样是先把`p2`这个指针的值赋给`eax`。

![image-20241121215916319](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411212159404.png)

接着把`ecx`的值减去8，这样，就来到了`derive`对象的首地址处。也就是说`base2`中间又转那么多层不是白转的，它是为了对`ecx`中的地址进行修正，以使得其指向对象的起始地址。

## Virtual function table in virtual inheritance

普通多继承我们已经看过了，接下来看看虚继承和虚函数合在一块。

```cpp
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
```

直接看内存窗口

![image-20241122102539527](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411221025725.png)

因为`B and C`都对`A`中的`funci`进行了各自的重写，加上它们有各自的`functio1 and functio2`虚函数，所以它俩的虚表不能合并。

虚基表中的第一个偏移量描述的是虚基表的间接位置，第二个偏移量描述的是成员变量的间接位置。

## others

下面我们谈几个主观题就可以结束了。

问题一：什么是多态？

多态分为两种。一种是静态多态，它在编译链接时就已经确定了，从汇编来说就是直接`call`某某函数，静态多态就是函数重载；除此之外还有动态多态，只有在运行时才确定通过虚函数表确定到底调用什么函数，我们平时说的多态主要指动态多态。

问题二：inline，也就是内联函数，可以成为虚函数并被重写吗？

内联是一种请求，编译器处于自身逻辑的考虑，可以无视该请求，多态的实现原理是虚函数表，虚函数表中存储的是虚函数对象的指针，当将一个内联函数作为虚函数并重写时，编译器就会无视内联请求，不把内联函数展开使用，而是调用使用。

问题三：构造函数可以是虚函数吗？

不行，虚函数表的覆写修改发生在构造函数的初始化列表阶段，既然连覆盖都没有完成，自然无法实现虚函数。

问题四：析构函数可以是虚函数吗？

不仅可以，而且最好是，以防止出现错误析构。

问题五：对象访问普通函数快还是虚函数快？

在构成多态条件的情况下，当然是普通函数更快，毕竟虚函数访问要经过更多的中间层；在不构成多态的条件下，无论是普通函数还是虚函数都是直接`call`，所以一样快。

问题六：静态成员函数可以为虚函数吗？

不可以，静态成员函数没有`this`指针，不是真正的成员函数，不能作为虚函数；从另一种角度来说，静态成员函数就是针对特定类型进行调用的，而虚函数是针对特定对象调用的，二者在逻辑上是就是冲突的，不兼容。

# end