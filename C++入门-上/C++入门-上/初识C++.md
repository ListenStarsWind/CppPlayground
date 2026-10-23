# 初识C++

## 前言

C++的前身是Bjarne Stroustrup从1979年开始开发的“带类的C”，1983年采用了C++这个名字。这个名字也很直观：在C的基础上，再往前走一步。

对于已经学过C的人来说，学习C++有一个很自然的切入点：过去写代码时遇到过哪些麻烦，C++又提供了哪些新工具？比如多人协作时的命名冲突，为不同类型编写相似函数时的重复，以及通过函数访问、修改原对象时的表达方式。

这篇文章就沿着这些问题展开，结合代码和反汇编，看看C++提供的新工具怎样使用，又解决了哪些具体问题。

本文使用Windows下的VS2022和Linux下的Clang 21展示实验现象，其中Linux实验采用C++17。各段反汇编与诊断会结合对应环境解释；具体的寄存器分配、符号编码和优化结果可能随编译器与配置变化。本节主要介绍基本用法，更深入的规则留到实际用到时继续讨论。

## 命名冲突

在使用C语言开发设计时，常常会遇到同名标识符的问题。不同模块可能都需要一个叫`Node`的类型、一个叫`Init`的函数，甚至项目自己选择的名称也可能撞上标准库。

在C中，作用域已经能区分一部分同名标识符，例如不同函数里可以各有一个局部变量`i`；不同源文件也可以各自定义具有内部链接的`static`函数。模块对外提供的名称，则经常需要依靠统一前缀来区分。

真正让人头疼的是：当不同模块需要对外提供名称，而这些名称又进入了会发生冲突的范围时，怎样把它们清楚地区分开？先看一个最直接的例子：

```c
// 头文件stdlib.h中包含伪随机数生成函数rand的声明。
// C++还提供对应的<cstdlib>，后面会继续说明。
#include<stdlib.h>
#include<stdio.h>

// 现在定义一个与标准库函数重名的全局变量。
int rand = 0;

int main()
{
	printf("%d ",rand);
	return 0;
}
```

这份代码在编译阶段就会报错。`stdlib.h`已经声明了函数`rand`，这里又在同一作用域中用`rand`定义全局变量，产生了冲突。

下面是在Linux下使用Clang 21编译时的诊断，部分提示已翻译成中文：

```bash
[wind@ubuntu-asus build]$ cmake --build .
[0/2] 重新检查 glob 匹配的目录...
[1/4] 编译 CXX 目标文件 CMakeFiles/main.dir/src/main.cpp.o
失败: CMakeFiles/main.dir/src/main.cpp.o
/usr/bin/clang++-21 -I/home/wind/CS-Rebuild/04-CPP-Language-Basics/初识C++/include -I/opt/libcxx-pkgs/include -g -std=c++17 -Wall -Wextra -Wpedantic -g3 -O0 -fno-omit-frame-pointer -stdlib=libc++ -MD -MT CMakeFiles/main.dir/src/main.cpp.o -MF CMakeFiles/main.dir/src/main.cpp.o.d -o CMakeFiles/main.dir/src/main.cpp.o -c '/home/wind/CS-Rebuild/04-CPP-Language-Basics/初识C++/src/main.cpp'
/home/wind/CS-Rebuild/04-CPP-Language-Basics/初识C++/src/main.cpp:4:5: 错误: 'rand' 被重新定义为另一种类型的符号
    4 | int rand = 0;
      |     ^
/usr/include/stdlib.h:573:12: 提示: 此前的声明位于此处
  573 | extern int rand (void) __THROW;
      |            ^
/home/wind/CS-Rebuild/04-CPP-Language-Basics/初识C++/src/main.cpp:8:20: 警告: 格式说明符要求参数类型为 'int'，但实际参数类型为 'int (*)() noexcept(true)' [-Wformat]
    8 |     printf("%d\n", rand);
      |             ~~     ^~~~
生成了 1 个警告和 1 个错误。
[2/4] 编译 CXX 目标文件 CMakeFiles/main_sanitize.dir/src/main.cpp.o
失败: CMakeFiles/main_sanitize.dir/src/main.cpp.o
/usr/bin/clang++-21 -I/home/wind/CS-Rebuild/04-CPP-Language-Basics/初识C++/include -I/opt/libcxx-pkgs/include -g -std=c++17 -Wall -Wextra -Wpedantic -g3 -O0 -fno-omit-frame-pointer -stdlib=libc++ -fsanitize=address,undefined -MD -MT CMakeFiles/main_sanitize.dir/src/main.cpp.o -MF CMakeFiles/main_sanitize.dir/src/main.cpp.o.d -o CMakeFiles/main_sanitize.dir/src/main.cpp.o -c '/home/wind/CS-Rebuild/04-CPP-Language-Basics/初识C++/src/main.cpp'
/home/wind/CS-Rebuild/04-CPP-Language-Basics/初识C++/src/main.cpp:4:5: 错误: 'rand' 被重新定义为另一种类型的符号
    4 | int rand = 0;
      |     ^
/usr/include/stdlib.h:573:12: 提示: 此前的声明位于此处
  573 | extern int rand (void) __THROW;
      |            ^
/home/wind/CS-Rebuild/04-CPP-Language-Basics/初识C++/src/main.cpp:8:20: 警告: 格式说明符要求参数类型为 'int'，但实际参数类型为 'int (*)() noexcept(true)' [-Wformat]
    8 |     printf("%d\n", rand);
      |             ~~     ^~~~
生成了 1 个警告和 1 个错误。
ninja: 构建已停止，子命令执行失败。
[wind@ubuntu-asus build]$
```


编辑器中的语法分析器也能提前显示诊断：

![image-20261024003138998](https://img.mdwind.online/img/image-20261024003138998.png)

在多人协作中，这类问题会更常见。C项目通常通过统一的前缀约定来区分模块，例如`SL_Init`、`DL_Init`。这种方式可以工作，只是前缀本身也要靠项目约定和团队维护。

C++提供了命名空间，让我们能够直接建立带名字的作用域。例如，把一个模块的名称放进`Whisper`，另一个模块的名称放进`Other`，即使里面都有`Node`，也能通过`Whisper::Node`和`Other::Node`明确区分。

命名空间中的名称仍然可以供外部使用，关键在于用限定名称说明它属于哪个作用域。例如`Whisper::Node`已经明确指定了目标，即使其他模块也定义了`Node`，两者也能分别使用。

定义命名空间需要用到关键字`namespace`，后面接命名空间的名字，再用大括号界定范围。项目中通常按项目或模块命名；练习时，也可以用自己的名字。

同一作用域中的同名具名命名空间可以在不同位置继续添加声明，这些声明都属于同一个命名空间。标准库的大量名称就放在`std`中，后面会经常见到`std::cout`、`std::cin`这样的写法。

宏替换发生在预处理阶段，不受命名空间约束。即使把`#define`写进命名空间的大括号中，也不能用`Whisper::宏名`来限定它。命名空间里的普通变量、类型和函数则由后续的C++编译过程处理。

```cpp
#include <cstdlib>
#include <cmath>
#include <cstdio>

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

	// 命名空间可以嵌套定义。
	namespace Wind
	{
		int rand = 2;

		// 演示同名函数可以有不同实现；这里计算绝对值的相反数。
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

这里用两个同名的`abs`演示名称的区分，内层函数故意返回绝对值的相反数。下面传入4，观察这两个同名函数怎样分别使用。

对命名空间内名称的使用，下面介绍三种常见写法：限定名称、`using`声明和`using`指令。

限定名称的写法最直接：在名称前加上命名空间名和作用域解析运算符`::`。对于嵌套命名空间，就沿着层次写下去。

类型也一样，例如`Whisper::Node`。C++中声明了`struct Node`以后，通常已经可以直接用`Node`作为类型名，不需要像C那样依靠`typedef`才能省略`struct`。下面保留带`struct`的写法，以便观察限定名称的位置：

```cpp
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

![image-20240914105048567](https://img.mdwind.online/md/202409141050695.png)

`using`声明可以把指定名称引入当前作用域。例如下面只引入`Whisper::Wind::Node`，随后直接写`Node`就能使用这个类型，其余名称仍然分别限定。这里两个对象都是内层的`Node`类型。

 ```cpp
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

`using`指令会影响后续的未限定名称查找，使指定命名空间中的名称也参与查找。它并没有改变成员的访问权限，也没有把这些成员搬到全局命名空间。

```cpp
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

上面只访问`Node`。如果再直接写`rand`或`abs`，标准库与自定义命名空间中的名称就可能共同参与查找，产生冲突或歧义。因此，`using namespace`并没有让同名问题消失，它只是让我们省略了部分限定名称。

这两种`using`写法都可以出现在函数内部，其影响范围与所在作用域有关。实际编写头文件时，尽量避免在全局作用域写`using namespace`，以免影响包含该头文件的代码。只需要少量名称时，可以使用`using`声明；直接写限定名称，则能让名称来源更清楚。

C++代码可以选用`<cstdio>`、`<cstdlib>`等对应头文件，并使用`std::printf`、`std::malloc`。这些名称也可能同时由实现提供在全局命名空间中；明确写出`std::`可以表达我们准备使用的接口来源。

还有两种写法可以放在一起看：`std::name`和`::name`。前者从`std`中查找名称；开头直接写`::`，表示从全局命名空间开始限定查找。例如`::printf`会明确指向全局命名空间中的`printf`，前提是相应声明已经在那里可见。

全局命名空间包含那些直接声明在全局的名称。使用一些C接口或系统接口时，常见的`::name`就能明确从这里开始查找。

## 输入输出

使用C的`printf`、`scanf`时，我们需要通过格式字符串描述数据类型。C++的标准流提供了另一套接口，常见类型可以直接交给流插入、流提取运算符处理，不必为每个值写转换说明。格式控制仍然存在，只是简单输入输出时可以暂时不写。

```cpp
// 为了与 C 语言的头文件命名方式加以区分，C++ 标准库通常采用不带文件
// 扩展名的头文件，例如 <iostream>、<vector> 和 <string>。

// 对于继承自 C 标准库的功能，C++ 通常提供以 c 开头、去掉 .h 后缀的头
// 文件，例如 <cstdio> 和 <cstdlib>，同时保留传统的 <stdio.h> 和 
// <stdlib.h> 以兼容旧代码。

// 需要说明的是，这只是标准库对外提供的接口命名约定，并不意味着其内部实现
// 文件一定没有扩展名。实际开发中，自定义 C++ 头文件仍然经常使用 .h 或 .hpp 
// 后缀。至于标准库内部如何组织头文件、是否包含其他 .h 或 .hpp 文件，则由
// 具体实现决定。

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

其中，`std::cout`和`std::cin`分别是与标准输出、标准输入关联的流对象。交互运行时，它们通常连接到终端和键盘，也可以通过重定向连接到文件或管道。

这里的`<<`叫流插入运算符，`>>`叫流提取运算符。它们形象地表示了信息流向，并且都是左结合。例如`std::cout << i << j`按`(std::cout << i) << j`结合，前一步返回流的引用，后一步就能继续操作同一个流。

`std::endl`会插入换行并刷新输出流。只需要换行时可以写`'\n'`；需要立即刷新时再使用`std::endl`，两者的作用并不完全相同。

![image-20240914125749518](https://img.mdwind.online/md/202409141257725.png)

C++的输入输出还有很多内容，但这里毕竟只是初识，所以就不说了。如果暂时还不熟悉流的格式控制，也可以继续使用已经掌握的`printf`等接口，后面再逐步补充流的用法。

## 缺省参数

在C++中，可以为函数参数提供一个默认值，当调用者未输入参数时，则使用该默认值。为了明确形参与实参之间的对应关系，对这里的普通函数，缺省参数必须从右往左连续设置，使用含有缺省参数的函数时，参数的输入必须是从左往右连续输入。

```cpp
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

缺省参数需要在调用处可见，调用者才知道省略的实参应该补成什么。采用头文件声明、源文件定义的组织方式时，通常把默认值写在头文件声明中，定义处不再重复指定。这样，调用者看到的接口与实际使用的默认值就放在一起，维护时也更清楚。

例如，上面的`Func2(1)`相当于传入`1、3、7`，`Func2(1, 2)`则相当于传入`1、2、7`。调用时可以省略尾部实参，但不能跳过中间的参数，只给更右边的参数赋值。

![image-20240914142459073](https://img.mdwind.online/md/202409141424184.png)

## 函数重载

前面的流输入输出可以根据数据类型选择相应操作，这与重载有关。先从普通函数看起：有时一组函数完成相似任务，只是处理的数据类型不同，我们希望给它们取同一个名字，例如都叫`Swap`。

在C中，需要通过不同名称区分这样的函数。下面把两个交换函数都命名为`Swap`，就无法作为同一份C代码编译：

```c
// 在C语言中, 不允许存在同名函数
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

在C++中，这两个函数可以使用相同名称。调用`Swap`时，编译器根据实参选择应当使用的函数：传入两个`int*`，选择交换整数的版本；传入两个`double*`，选择交换浮点数的版本。这就是函数重载。

那么，哪些区别能让同名函数构成重载？

参数个数可以不同，参数类型可以不同，参数类型的排列顺序也可以不同。例如`f(int, double)`和`f(double, int)`可以构成重载；只把形参名从`x`换成`y`则没有用，名称没有改变调用者需要提供的参数类型。

编译器会先找到可能参与调用的函数，再结合实参判断哪些函数可用、哪个匹配得更好。这个选择过程叫重载决议。如果存在多个同样合适的候选，编译器就会报告调用有歧义，函数重载并不保证每一种调用都能得到唯一答案。

至于这些同名函数如何在目标文件和链接阶段被区分，就要看看具体实现。常见C++实现会把函数名、所属作用域、形参类型等信息编码进链接符号，这叫名称修饰。编译期间选好重载以后，生成的代码就可以引用对应的符号。

对上面的C代码，两个`Swap`的声明就已经发生冲突，编译器会在编译阶段诊断。C++则允许它们构成重载，并在目标代码中区分相应函数。

下面观察两种语言所生成的符号：

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

![image-20240918180208939](https://img.mdwind.online/md/202409181802193.png)

可以看到，它是直接拿函数名进行调用的。

改成C++后再试一试

![image-20240918180630580](https://img.mdwind.online/md/202409181806769.png)

前面的“4”用来描述函数名的字符数，`Swap`正好有四个字符。图中使用的这套名称修饰规则中，`P`表示指针，`i`、`d`分别表示`int`、`double`。

如果看到的是`_Z4SwapPiS_`，可以分成`_Z`、`4Swap`、`Pi`和`S_`理解：前缀标记名称修饰，随后是函数名称，再往后描述形参类型。`S_`是替代编码，复用此前已经记录的`int*`类型。因此，这个符号对应`Swap(int*, int*)`。

这套规则属于Itanium C++ ABI。ABI是应用二进制接口，约定编译后的代码怎样彼此配合，函数的符号名称就是其中一部分。Linux上常见的GCC、Clang环境采用这套名称修饰规则，MSVC通常采用另一套编码，所以在不同工具链里看到的符号拼写可能不同。

在Linux下使用Clang编译`Add`系列函数，也能观察到相同规律。第一组是`nm`显示的修饰名称，第二组使用`nm -C`把它们还原成便于阅读的形式：

```bash
[wind@ubuntu-asus build]$ nm main-debug | grep Add
0000000000001160 T _Z3Adddd
0000000000001140 T _Z3Addii
0000000000001180 T _Z3Addiii
00000000000011a0 T _Z9AddResultii
[wind@ubuntu-asus build]$ nm -C main-debug | grep Add
0000000000001160 T Add(double, double)
0000000000001140 T Add(int, int)
0000000000001180 T Add(int, int, int)
00000000000011a0 T AddResult(int, int)
[wind@ubuntu-asus build]$ 
```

例如`_Z3Addii`对应`Add(int, int)`，`_Z3Adddd`对应`Add(double, double)`，`_Z3Addiii`对应三个`int`形参。调用时，编译器选好具体重载；生成的代码再使用相应符号，让链接器找到对应定义。

返回类型不能单独用来区分这里的函数重载：

```cpp
int Read();
// double Read();  // 错误：仅返回类型不同
```

为什么这样规定？看`Read();`就很直观：调用者完全可以忽略结果，此时无法根据接收结果的类型决定调用哪个函数。C++对这类普通函数的重载决议也不会反过来依靠接收变量来选择返回类型。


## 引用

在C中，如果希望被调用函数修改调用者的局部变量，通常要把变量地址传进去，再通过指针间接访问。C++提供了另一种表达方式：引用。

先把引用理解成对象的别名。例如`int& a = n;`声明了一个`int`的左值引用`a`，并让它绑定到`n`。之后使用`a`，就能访问`n`这个对象。引用可以作为函数参数类型，因此也能用来表达跨函数的访问。

由于是取别名，所以它们指向的地址都是一样的，换言之，它们指向相同的内存块。

```cpp
int main()
{
	int n = 0;
	int& a = n;
	int& b = n;
	int& c = a;

	std::cout << &n << std::endl;
	std::cout << &a << std::endl;
	std::cout << &b << std::endl;
	std::cout << &c << std::endl;
	return 0;
}
```

![image-20240918203538630](https://img.mdwind.online/md/202409182035745.png)

或许可以再看看汇编：

![image-20240918203713706](https://img.mdwind.online/md/202409182037921.png)

这份反汇编可以按下面的顺序理解。这里的`[n]`、`[a]`等是调试器对相应存储位置的符号化显示。

`mov dword ptr [n], 0`把整数0写入保存`n`的四字节位置。

`lea rax, [n]`计算`n`的地址，并把该地址放入`rax`。

`mov qword ptr [a], rax`把`rax`中的八字节内容写入编译器为引用`a`安排的存储位置。此时`rax`存的是`n`的地址，所以保存下来的是地址。`qword ptr`说明这次内存操作的宽度，并不表示去读取`rax`所指向的八字节数据。

后面的`mov rax, qword ptr [a]`再取出保存的地址，`mov qword ptr [c], rax`把它保存到引用`c`对应的位置。于是，`c`最终也指代`n`。

![image-20240918210320085](https://img.mdwind.online/md/202409182103201.png)

从这次实验可以看到，编译器借助保存地址实现了引用的绑定与访问。这也解释了为什么引用参数在底层经常呈现出与指针参数相似的形式。

不过，这里要把两件事分开看。语言层面，`&a`取得的是被引用对象`n`的地址；调试反汇编中的`[a]`则是这次编译给引用安排的实现用存储位置，不能把它当成可以通过普通的`&a`取得的另一个对象地址。

在这份反汇编中，引用通过保存地址实现，所以相应位置确实占用了存储空间。沿着保存的地址访问目标对象，也与指针间接访问的实现方式相似。后面观察引用参数时，还会看到这种对应关系。

有了引用之后，交换函数就可以写成这样了：

```cpp
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

### 引用参数与引用返回值

前面的`Swap`展示了引用参数。它使函数能够直接通过形参名修改调用者的对象，调用处也不用显式取地址。

引用同样可以作为返回类型。先把普通的按值返回和引用返回放在一起比较：

```cpp
#include <iostream>

int value = 0;

int GetValue()
{
    return value;
}

int& GetRef()
{
    return value;
}

int main()
{
    int copy = GetValue();
    copy = 10;
    std::cout << value << '\n';  // 0

    // GetValue() = 20;          // 错误
    GetRef() = 20;
    std::cout << value << '\n';  // 20
}
```

`GetValue()`按值返回`int`，调用者获得的是`value`的数值。用这个值初始化`copy`以后，`copy`是另一个对象，修改它不会影响原来的`value`。

`GetRef()`返回`int&`，调用表达式会指代`value`本身。因此，`GetRef() = 20`可以直接对原对象赋值。调用函数的写法没有变，但返回类型决定了调用者得到的是一个值，还是对已有对象的引用。

像`GetRef()`这样能够指代对象的调用表达式是左值，所以这里能把它放在赋值号左边。`GetValue()`按值返回`int`，它的调用表达式则不能作为内建赋值运算的左操作数。先记住这一组对比，后面再详细讨论值类别。

返回引用还需要考虑对象能活多久。这里的`value`是全局变量，调用结束后依然存在，因此调用者可以继续使用返回的引用。如果返回的是函数内部普通局部变量的引用，情况就不同了：

```cpp
int& Wrong()
{
    int local = 1;
    return local;  // 返回后local的生命周期结束，引用失效
}
```

即使返回时还能取得`local`的地址，也无法让它在函数退出后继续存活。调用者使用引用时，被引用对象必须仍然存在。这个要求与返回指针时需要考虑的生命周期问题是一致的。

### 常引用

常引用通常指指向`const`类型的引用，例如`const int&`。它可以提供一条只读的访问路径，限制通过这条路径进行修改。

```cpp
void f(const int& val)
{
    // val = 8;  // 错误：不能通过val修改对象
}

int main()
{
    int i = 0;
    f(i);
    return 0;
}
```

把注释去掉，编译器就会报错。`val`提供了只读的访问路径；原对象如果本来是普通变量，仍然可以通过原变量名修改：

```cpp
int i = 1;
const int& r = i;

i = 2;
std::cout << r << '\n';  // 2
```

这里的`r`始终引用`i`，所以`i`改变以后，通过`r`读到的值也会变化。`const`约束了这条访问路径，没有把`i`重新定义成常量。

绑定引用时，可以用“权限可以传递、可以缩小，不能随意放大”来帮助记忆：

```cpp
int i = 1;
int& a = i;          // 保留可写访问
const int& b = i;    // 只读访问

const int c = 2;
const int& d = c;    // 可以
// int& e = c;       // 错误：不能丢掉const限定
```

这些例子中，引用与对象的基本类型相同，只涉及是否允许通过引用修改对象。接下来再看一个需要类型转换的情况。

### 类型转换以后，引用的是谁？

看下面这段代码：

```cpp
int i = 1;
// double& j = i;  // 错误
```

`i`是`int`对象，而`j`要求引用`double`对象。我们不能因为整数1可以转换成浮点数1.0，就把原来的`int`对象当成`double`对象直接访问。数值能转换，与对象类型可以直接混用，是两件事。

为了看清转换这一步，先观察普通变量初始化：

```cpp
int i = 0;
double j = i;
```

在VS2022中，这部分对应下面的汇编：

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

`cvtsi2sd`读取`i`中的四字节整数，把它转换成双精度浮点数，并将结果放入`xmm0`。后面的`movsd`再把该浮点数写入普通变量`j`对应的存储位置。这里确实产生了新的浮点数表示，原来的`i`没有被改成`double`。

这两条指令把整数转换成了浮点数，再保存到`j`的位置。转换得到了新的数值表示，`i`仍然是原来的`int`对象。

引用初始化也可能需要这种数值转换。看下面的写法：

```cpp
int i = 1;
const double& j = i;
```

在这个初始化中，`i`先经过数值转换，得到`double`类型的结果，再由一个临时`double`对象承载这个结果，`j`绑定到这个临时对象。由于这里局部引用的直接初始化满足生命周期延长规则，这个临时对象可以持续存在到`j`的生命周期结束。

因此，`j`引用的是一个独立的`double`对象，它的初始值来自`i`。临时对象在这里有多长的生命周期，取决于引用初始化规则；具体实现把数据放到哪里，则可以通过相应反汇编继续观察。

为什么前面的`double& j = i`不行？因为它无法直接绑定这个`int`对象，而非`const`左值引用又不能绑定这里转换得到的临时对象。`const double&`允许这种绑定，并在当前局部初始化形式下延长临时对象的生命周期。

从使用上的直觉看，还可以追问一步：假如允许`double& j = i`，然后执行`j = 3.5`，原来的`i`应不应该一起改变？

顺着“引用是别名”去想，很容易期待`j`改了，`i`也跟着改；但顺着数值转换去想，又会发现转换结果已经由另一个`double`对象承载，修改它可以不影响原来的整数。这正是这类写法容易造成的对象身份混淆：看起来在引用原变量，实际需要先得到另一个类型的对象。

`const double&`把使用范围限制为只读。通过`j`可以取得转换后的值，但不能执行`j = 3.5`，也就不会通过这条路径产生“应该修改哪一个对象、要不要回写”的困惑。这个角度可以帮助理解只读限制；判断代码是否合法时，则按照上面的绑定规则。

不过，不能写`j`，我们还可以写`i`。如果把`i`改成2，`j`会跟着变吗？把同类型引用放在旁边对照，就能看清区别：

```cpp
#include <iostream>

int main()
{
    int i = 1;
    const int& a = i;
    const double& b = i;

    i = 2;

    std::cout << a << '\n';  // 2
    std::cout << b << '\n';  // 1
}
```

`a`直接引用`i`，所以读到的是`i`当前的值。`b`引用的是初始化时转换得到的临时`double`对象，这个对象保存了当时的1.0，与`i`之间没有持续同步的关系。因此，`i`变化后，`b`读到的值保持不变。

还可以打印地址来观察这个区别。下面只保留需要转换的引用：

```cpp
#include <iostream>

int main()
{
    int i = 0;
    const double& j = i;
    std::cout << &i << std::endl;
    std::cout << &j << std::endl;
    return 0;
}
```

![image-20240920172029211](https://img.mdwind.online/md/202409201720400.png)

两个地址不同，分别对应`int`对象与临时`double`对象。这里再用“别名”理解引用，就需要说完整：`j`是这个临时对象的别名，初始数值来自`i`。

对于不涉及类型转换的`const int& a = i`，引用直接绑定原对象，`i`变化后自然读到新值。所以，常引用中的`const`说明能否通过引用写入，引用绑定到谁则决定了它访问哪个对象。

这一节讨论的是局部引用直接绑定临时对象的形式。函数参数等其他位置也可以使用常引用，其生命周期边界在遇到相应代码时再继续说明。

## 内联函数

对于用宏模拟的小函数，C++的函数和内联优化常常能提供更合适的写法。在学`inline`之前，让我们先看看这类宏有哪些麻烦。C也有`inline`，这里讨论的是C++中的规则。

用宏模拟函数时，麻烦通常出在文本替换上。替换过程本身没有函数参数的类型检查，参数还可能被重复求值。例如：

```cpp
#define SQUARE(x) ((x) * (x))
```

括号保护了表达式的结合方式，但如果传入`i++`，展开后就会出现两次`i++`。把宏参数全部加上括号，也无法消除重复求值的问题。

括号还需要结合宏的用途处理。对于表达式参数，括号经常有用；如果某个参数准备被替换成类型名或声明的一部分，就要看替换后的语法是否成立。下面的例子尝试用宏模拟`offsetof`，其中的`m`要替换成成员名，接在`->`后面。若把它写成`->(m)`，展开后会得到`->(i)`这样的形式，不符合成员访问的语法。这里就能看到，宏参数的用途不同，加括号的方法也要跟着变。

![image-20240922125216736](https://img.mdwind.online/md/202409221252007.png)

因此，需要普通函数的类型检查、参数求值和作用域规则时，直接写函数通常更清楚。如果还希望减少小函数的调用开销，可以继续了解内联展开。

在函数声明中使用`inline`，可以把函数声明为内联函数。这里有个容易绕进去的地方：函数被声明为内联函数，与它在某个调用点是否真正被展开，需要分别讨论。

`inline`表达了优先考虑内联替换的意图，但编译器不必执行这种优化；没有写`inline`的普通函数，也可能被编译器展开。另外，`inline`还涉及多翻译单元中的定义规则，后面会结合头文件解释。

当编译器实施内联展开时，会把函数操作整合进调用处生成的代码，从而有机会省去调用开销。但类型检查、参数求值等仍然遵循函数调用语义。宏是预处理阶段的文本替换，内联优化发生在后续编译处理中，程序执行时并没有再进行一轮源码替换。

例如下面的函数：

```cpp
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

使用VS2022观察反汇编，调用处仍然可以看到`call add`。这说明在当前配置下，该调用点没有进行内联展开，函数按调用、返回的方式执行。

调试配置通常会限制优化，以便保留容易单步跟踪的调用和变量。下面调整VS的相关配置，再观察同一份代码：

![image-20240922131056118](https://img.mdwind.online/md/202409221310345.png)

![image-20240922131424722](https://img.mdwind.online/md/202409221314415.png)

![image-20240922131540034](https://img.mdwind.online/md/202409221315169.png)

![image-20240922131848350](https://img.mdwind.online/md/202409221318446.png)

![image-20240922132114064](https://img.mdwind.online/md/202409221321154.png)

别忘了实验之后再改回去。

调整配置以后，相应调用处可以观察到内联展开，加法直接进入了调用者的代码：

![image-20240922132542370](https://img.mdwind.online/md/202409221325576.png)

这个调用点不再需要为`add`执行独立的调用与返回过程，加法被整合进调用者的机器码。相关数据可以继续放在寄存器中，也可以使用调用者的栈空间，具体取决于代码生成。

这样就省去了这个调用点的调用与返回开销。编译器还能结合调用处已知的信息，继续简化展开后的运算。

那么，编译器为什么可能保留调用？展开可以减少调用开销，也可能把同一份函数代码复制到许多调用点，导致代码体积增加。编译器会结合函数规模、调用位置、优化选项等因素权衡。

例如，一个函数生成了约100条指令，项目中有100个调用点。如果每处都保留一份完整展开结果，又没有进一步简化，就可能形成约10000条指令。保留一份函数体，再加各处调用与参数准备，通常会小得多。

这只是为了比较量级。实际展开以后，某些运算可能因为实参已知而被简化，无用代码也可能被删除，最终体积需要看生成结果。另一方面，如果大量展开导致代码体积增大，也可能增加指令缓存压力。

因此，编译器会权衡省去调用的收益与代码增长的代价。`inline`函数可以保留调用，普通函数也可以被展开，具体结果要结合调用位置与优化配置观察。

### 内联函数为什么通常定义在头文件中？

还有一个与性能不同的问题：`inline`函数应该怎样组织声明和定义？先看下面的文件划分：

```cpp
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

在VS2022的相应配置下，这种写法出现了上面的链接错误。问题出在`main.cpp`使用了内联函数，却没有看到它的定义。

内联函数可以保留独立的函数实体与链接符号，`inline`也不会自行改变函数的链接属性。例如，某个调用点未被展开，或者程序需要取得函数地址，实现就可能需要提供可调用的函数代码。

`main.cpp`包含`F.h`后，只得到`add`的声明，函数体仍然位于单独编译的`F.cpp`中。对于这里被调用的内联函数，定义需要在使用它的翻译单元中可见。

翻译单元可以暂时理解成一份源文件经过预处理、包含相关头文件以后形成的编译输入。头文件里的声明会进入`main.cpp`的翻译单元，`F.cpp`里的函数体却不会自动跟进来。

这种写法的表现还可能随配置改变：如果`F.cpp`恰好输出了独立的`add`代码，链接器可能解析到相应符号；如果没有输出，就可能报告找不到符号。为了让代码满足内联函数的定义要求，仍然应该把函数体提供给使用它的翻译单元。

如果把`main`改成调用普通函数`f`：

```cpp
int main()
{
    int i = 3;
    int j = 3;
    int k = f(i, j);
    return k == 6 ? 0 : 1;
}
```

这时`main.cpp`只需要看到`f`的声明，链接器可以把调用与`F.cpp`中的`f`定义对应起来。`f`对`add`的使用则发生在`F.cpp`中，这个翻译单元已经包含了`add`的完整定义。至于`f`内部到底展开`add`还是保留调用，可以继续由编译器决定。

这样，`main.cpp`负责调用`f`，`F.cpp`负责实现`f`并使用`add`，链接器再把相应目标代码连接起来。

要让两个源文件都能正确使用`add`，可以把它的完整定义放进头文件：

```cpp
// F.h
#pragma once

inline int add(int a, int b)
{
    return a + b;
}

int f(int a, int b);
```

`F.cpp`中只保留`f`的定义，不再另写一份`add`的定义。这样，无论哪个源文件包含`F.h`，都能看到`add`的函数体。

那头文件被多份源文件包含，岂不会产生多份定义？这正是`inline`在定义规则上的作用：在满足单一定义规则的条件下，同一个具有外部链接的内联函数可以定义在多个翻译单元中，仍然表示同一个实体。通常把相同的定义写在头文件里，可以让各处得到一致的函数体；函数体中名称的查找结果等也要满足一致性要求。

实际使用时，可以把这两件事分别记住：把内联函数的定义放在头文件中，让使用者能看到函数体；至于某个调用点是否展开，由编译器决定。

## auto

写C++代码时，有些类型会比较长，重复写出来不够方便。`auto`可以让编译器根据初始化表达式推导类型，我们先从最简单的变量声明看起：

```cpp
int main()
{
    int i = 0;
    auto j = i;
    auto& k = i;
    return 0;
}
```

`auto j = i`让编译器推导出`j`的类型为`int`，并用`i`的值初始化它。`auto& k = i`则明确要求引用，最后得到的类型是`int&`。

两者的差别可以直接通过赋值观察：

```cpp
int i = 0;
auto j = i;
auto& k = i;

j = 1;  // 修改j，i仍为0
k = 2;  // 修改i，j仍为1
```

`auto`是类型占位符，类型在编译期间就会确定。它省去了一部分类型拼写，得到的变量仍然有确定类型。

可以使用`typeid(...).name()`观察类型信息：

```cpp
#include <iostream>
#include <typeinfo>

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

![image-20240922163619653](https://img.mdwind.online/md/202409221636933.png)

这里三个输出相同，是因为`typeid`在这个例子中提供的是所指代的`int`对象的类型信息，不能显示变量声明中的引用区别。`j`的声明类型仍然是`int`，`k`则是`int&`。输出文本的具体形式也与编译器实现有关。

编辑器中的语法分析器可以直接显示推导出的声明类型：

![image-20261024022932951](https://img.mdwind.online/img/image-20261024022932951.png)

图中的`(void)variable`用来表示有意弃用变量的值，从而抑制常见的未使用变量警告。它不会改变类型推导结果。

本节先使用带初始化表达式的普通变量声明。需要引用时写出`auto&`；只写`auto`时，上面这样的初始化会得到独立的变量。其他位置的类型推导规则，在遇到相应语法时再介绍。

## 范围for

在C++11之前，遍历一个数组要这样做：

```cpp
int main()
{
	int Array[] = { 2,4,6,8 };
	std::size_t sz = sizeof(Array) / sizeof(Array[0]);
	int tem;
	for (std::size_t i = 0; i < sz; i++)
	{
		tem = Array[i];
		std::cout << tem << " ";
	}
	std::cout << std::endl;
	return 0;
}
```

C++11引入了范围`for`，可以用来遍历一个范围。数组是最容易上手的例子，后面学到的许多容器也支持这种写法。

```cpp
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

![image-20240922165715032](https://img.mdwind.online/md/202409221657209.png)

每轮循环都会用当前元素初始化循环变量。`auto tem`得到一份元素值，修改`tem`不会修改原数组；`auto& mem`则绑定当前元素，所以`mem *= 2`会改变数组中的值。如果希望避免复制，又只允许读取，可以写`const auto& mem`。对于这里的`int`数组，按值复制本身也很轻量。

因此，范围`for`省去了手写下标与循环边界，但“复制元素还是引用元素”仍然由循环变量的声明决定。

这里还有一个与数组传参有关的边界。如果函数形参写成`int a[]`，它会被调整为`int*`，函数只得到指针，无法单凭这个指针确定数组终点，因此不能直接对`a`使用范围`for`。

```cpp
void Print(int a[], int size)
{
    for (int i = 0; i < size; ++i)
        std::cout << a[i] << ' ';
}
```

使用数组引用传参，则可以保留数组类型：

```cpp
void DoubleElements(int (&a)[4])
{
    for (auto& element : a)
        element *= 2;
}
```

这里接收的是四元素数组的引用，所以函数内部仍知道边界。后面学模板时，还可以把长度写成可推导的参数，不必为每种长度各写一个函数。当前只要知道：范围`for`需要能够确定遍历的起点和终点，单独一个普通指针没有提供这些信息。

## 空指针nullptr

在C里，我们经常用`NULL`表示空指针。它是由实现提供的宏，常见定义包括整数零或`((void*)0)`等空指针常量形式。在C++中，`NULL`的定义同样依赖实现，常见形式与整数零有关。

过去没有重载时，我们主要关心它能否正确用于指针初始化。进入C++以后，“它本身是什么类型”还会影响重载选择：

```cpp
#include <cstddef>
#include <iostream>

void f(int)
{
    std::cout << "f(int)" << '\n';
}

void f(int*)
{
    std::cout << "f(int*)" << '\n';
}

int main()
{
    f(0);
    // f(NULL);  // 结果与NULL的具体定义有关，也可能发生歧义
    f(static_cast<int*>(nullptr));
    f(nullptr);
    return 0;
}
```

`f(0)`会选择`f(int)`。虽然整数零可以充当空指针常量，但在当前重载集合里，与`int`直接匹配比转换成`int*`更合适。

如果实现将`NULL`展开为整数0，`f(NULL)`也会选择整数重载；其他定义还可能使调用产生歧义。下面是VS2022中的观察结果：

![image-20240922173833232](https://img.mdwind.online/md/202409221738481.png)

这里的`void f(int)`省略了形参名称，因为函数体没有使用参数值。形参类型仍然是`int`，调用时仍需要提供一个相应实参。

C++11引入了`nullptr`，专门表达空指针的意图。它的类型是`std::nullptr_t`。这个类型本身不属于指针类型，但它的值可以转换成相应的空指针值：

```cpp
int* p = nullptr;
double* q = nullptr;
```

因此，在前面的重载集合中，`f(nullptr)`可以匹配`f(int*)`，不会像整数0那样直接匹配`f(int)`。

当然，`nullptr`也不会替我们确定所有指针重载。例如同时存在`f(int*)`和`f(double*)`时，`f(nullptr)`仍然可能有歧义，因为两种指针都能接收空指针值。此时需要明确指定目标指针类型。

为什么另加一个`nullptr`，没有简单要求所有旧代码里的`NULL`都采用新的含义？旧代码可能已经依赖`NULL`原有的类型与重载行为，直接改变它会影响兼容性。新增一个表达明确意图的字面量，让新代码可以使用更合适的写法，也给旧代码保留了原来的适配空间。

## 参考资料

本文涉及的语言规则与符号编码，可以结合以下资料继续查阅：

- [Stroustrup关于C++起源与名称的说明](https://www.stroustrup.com/bs_faq.html)
- [命名空间的using指令](https://eel.is/c++draft/namespace.udir)
- [引用类型](https://eel.is/c++draft/dcl.ref)与[引用初始化](https://eel.is/c++draft/dcl.init.ref)
- [临时对象与生命周期](https://eel.is/c++draft/class.temporary)
- [inline说明符](https://eel.is/c++draft/dcl.inline)与[单一定义规则](https://eel.is/c++draft/basic.def.odr)
- [默认参数](https://eel.is/c++draft/dcl.fct.default)
- [typeid](https://eel.is/c++draft/expr.typeid)与[auto占位类型](https://eel.is/c++draft/dcl.spec.auto)
- [范围for](https://eel.is/c++draft/stmt.ranged)与[nullptr](https://eel.is/c++draft/lex.nullptr)
- [Itanium C++ ABI的名称修饰规则](https://itanium-cxx-abi.github.io/cxx-abi/abi.html#mangling)

# 完