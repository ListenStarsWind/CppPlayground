# C++ 内存管理

在 C 语言中，我们使用 `malloc` 申请动态内存，使用完后再交给 `free` 释放。到了 C++，这套函数仍然可以使用，不过类的引入使动态内存管理多了一层工作：申请到空间之后，还需要在其中构造对象；归还空间之前，还需要析构对象。

例如，一个类可能在构造函数中建立初始状态，在析构函数中释放自己管理的资源。`malloc` 只负责申请空间，不会调用构造函数；`free` 只负责释放空间，也不会调用析构函数。将返回的 `void*` 转换成类指针后，还需要在这块空间中构造对象。

因此，C++ 提供了 `new` 和 `delete`，把空间管理与对象的构造、析构衔接起来。下面先看它们的用法，再拆开观察背后的过程。

## 一、new 和 delete 的基本用法

### 1. 创建单个对象和数组

`new` 和 `delete` 都是 C++ 关键字。常见的使用形式如下：

```cpp
T* p = new T;
delete p;

T* arr = new T[n];
delete[] arr;
```

`new T` 创建一个 `T` 对象，返回指向它的 `T*`；`new T[n]` 创建包含 `n` 个元素的数组，返回指向首元素的 `T*`。这里的对象既可以是类对象，也可以是 `int` 这样的内置类型对象。

两种形式返回的指针类型都是 `T*`。使用时要根据创建的是单个对象还是数组，选择对应的 `delete` 或 `delete[]`。

```cpp
int main()
{
    auto p1 = new int;
    auto p2 = new int[10];

    delete p1;
    delete[] p2;
    return 0;
}
```

在这两个没有提供初始化器的例子中，`int` 对象没有被初始化，读取前应先赋值。对于类对象，默认初始化会选择相应的默认构造函数；数组中的元素也会分别初始化。

`delete p1` 销毁单个对象并释放对应空间；`delete[] p2` 销毁整个数组并释放对应空间。类对象的销毁会调用析构函数，`int` 这类对象没有需要执行的析构逻辑。

这里说的“释放”，是把空间交还给内存管理器，由它安排后续复用或归还给操作系统。释放后，指针变量仍保留原来的地址值，成为悬空指针。

### 2. 创建时指定初始值

`new` 可以在创建对象时指定初始值：

```cpp
int main()
{
    auto p1 = new int(1);           // 初始化为 1
    auto p2 = new int();            // 初始化为 0
    auto p3 = new int{1};           // 初始化为 1，C++11 的列表初始化
    auto p4 = new int[10]{1, 2, 3}; // 前三个元素为 1、2、3，其余为 0
    auto p5 = new int[10]{};        // 所有元素为 0

    delete p1;
    delete p2;
    delete p3;
    delete[] p4;
    delete[] p5;
    return 0;
}
```

`new int(1)`、`new int()` 在 C++11 之前就已经存在。C++11 增加的是这里使用的花括号初始化形式，包括 `new int{1}` 和 `new int[10]{1, 2, 3}`。

对于类对象，初始化器参与构造函数的选择和参数传递。先用一个能打印构造、析构过程的类观察：

```cpp
#include <iostream>

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
}  // namespace wind

wind::A::A(int val)
    : _i(val)
{
    std::cout << "A(int val)" << std::endl;
}

wind::A::A(const A& obj)
    : _i(obj._i)
{
    std::cout << "A(const A& obj)" << std::endl;
}

wind::A::~A()
{
    std::cout << "~A()" << std::endl;
}

int main()
{
    auto p1 = new wind::A;
    auto p2 = new wind::A(6);
    auto p3 = new wind::A(*p2);
    auto p4 = new wind::A[3]{1, 2, 3};

    delete p1;
    delete p2;
    delete p3;
    delete[] p4;
    return 0;
}
```

`p1` 所指对象使用默认实参 `2`，`p2` 所指对象使用实参 `6`，`p3` 所指对象由 `*p2` 拷贝构造。

`p4` 对应三个元素。这里的 `A(int)` 没有用 `explicit` 修饰，整数初始化项可以用于隐式转换并初始化相应元素。若改为 `explicit A(int)`，这组直接写整数的数组初始化项就不能照用。有关构造函数、隐式转换和 `explicit` 的规则，与前面类和对象部分相同。

下面通过截图观察另外两组初始化示例，代码与对应输出放在一起：

![动态对象初始化示例](https://img.mdwind.online/md/202410091655856.png)

![类对象初始化与参数传递示例](https://img.mdwind.online/md/202410091732189.png)

### 3. 申请失败与异常

`malloc` 申请失败时返回空指针；普通的 `new` 申请失败时，会抛出 `std::bad_alloc` 异常。

异常是 C++ 处理错误情况的一种机制。我们可以把可能发生异常的操作放在 `try` 中，并在后面用 `catch` 接收和处理异常。某条语句抛出异常后，程序会沿调用关系寻找匹配的 `catch`，转入其中执行；原先执行路径中尚未执行的语句会被跳过。

```cpp
#include <exception>
#include <iostream>
#include <new>

void f()
{
    auto p = new char[0x7fffffff];
    std::cout << "----------" << std::endl;
    delete[] p;
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

如果 `f()` 中的分配抛出异常，两条分隔线都会被跳过，程序进入 `catch`。这里先记住一种接收标准异常的常用写法：`catch (const std::exception& e)`。它可以接收本例中的 `std::bad_alloc` 异常，再通过 `e.what()` 取得异常说明。具体的类型关系和匹配规则，留到后面学习继承与异常机制时展开。

如果分配成功，程序输出两条分隔线，并跳过 `catch`。示例中的 `delete[] p` 用于释放成功分配的数组。

在 32 位 x86 环境中，申请 `0x7fffffff` 个 `char`，约为 2 GiB，比较容易遇到分配失败。下面的截图记录了这样的失败结果，其中 `bad allocation` 表示内存分配失败。

![较大内存申请失败时捕获异常](https://img.mdwind.online/md/202410092022007.png)

在 64 位环境中，这次申请也可能成功，进入上面所说的正常执行路径。

现阶段的教学示例主要沿正常执行路径讨论，经常省略 `try`、`catch`，以便集中观察当前机制。实际发生异常时，程序会向外寻找匹配的 `catch`；如果始终找不到，就会终止运行。

## 二、把空间管理与对象生命周期拆开

### 1. new 表达式与 operator new

写下 `new T(args)` 时，通常可以分成两步理解：

1. 调用分配函数，取得足够且满足对齐要求的空间。
2. 在取得的空间中初始化对象；对于类对象，这一步会调用相应构造函数。

写下 `delete p` 时，顺序相反：先销毁对象，再调用释放函数归还空间。

对应的空间管理函数与对象处理过程如下：

| 表达式        | 空间管理函数        | 对象处理               |
| ------------- | ------------------- | ---------------------- |
| `new T(args)` | `operator new`      | 初始化一个对象         |
| `delete p`    | `operator delete`   | 销毁一个对象           |
| `new T[n]`    | `operator new[]`    | 初始化数组中的各个元素 |
| `delete[] p`  | `operator delete[]` | 销毁数组中的各个元素   |

`new` 表达式负责组织整个创建过程，其中 `operator new` 提供空间，随后进行对象初始化。相应地，`delete` 表达式先安排对象析构，再由 `operator delete` 释放空间。

这些函数使用 `operator` 形式的名称，可以进行重载，部分全局版本还允许由程序提供替换实现。因此，程序可以在空间管理这一层接入自己的实现或第三方内存管理器，而对象的构造和析构仍由相应表达式衔接。

### 2. 运行库怎样申请和释放空间

下面这组 Windows 运行库调试截图展示了分配、构造、析构和释放之间的衔接。其中，`operator new` 通过 `malloc` 申请空间，`operator delete` 最终通过 `free` 释放空间；其他运行库的底层实现可以有所不同。

![Windows 运行库分配与释放过程的调试记录](https://img.mdwind.online/md/202410092103687.png)

![Windows 运行库分配与释放过程的调试记录](https://img.mdwind.online/md/202410092104546.png)

![Windows 运行库分配与释放过程的调试记录](https://img.mdwind.online/md/202410092104398.png)

![Windows 运行库分配与释放过程的调试记录](https://img.mdwind.online/md/202410092105693.png)

![Windows 运行库分配与释放过程的调试记录](https://img.mdwind.online/md/202410092106319.png)

![Windows 运行库分配与释放过程的调试记录](https://img.mdwind.online/md/202410092107624.png)

![Windows 运行库分配与释放过程的调试记录](https://img.mdwind.online/md/202410092107256.png)

![Windows 运行库分配与释放过程的调试记录](https://img.mdwind.online/md/202410092108853.png)

把源码中辅助管理和调试的部分略去，保留与分配有关的逻辑，可以整理成下面的示意函数：

```cpp
// 以 malloc 为底层分配方式，展示申请失败后的处理流程。
void* allocateMemory(std::size_t size)
{
    for (;;)
    {
        void* p = std::malloc(size);
        if (p != nullptr)
        {
            return p;
        }

        std::new_handler handler = std::get_new_handler();
        if (handler == nullptr)
        {
            throw std::bad_alloc();
        }

        handler();
    }
}
```

每次先尝试分配，成功就返回。失败后，检查是否设置了内存不足处理函数。没有处理函数就抛出 `std::bad_alloc`；有则调用它。如果处理函数正常返回，循环会再次尝试分配。原先源码中的 `_callnewh(size)` 就与这类处理过程有关。

这就把两种失败处理方式衔接起来了：底层 `malloc` 返回空指针，上层分配函数尝试处理，无法继续时再抛出异常。

释放端的主线则可以简化理解为：

```cpp
void releaseMemory(void* p)
{
    std::free(p);
}
```

分配与释放函数负责空间的取得和归还，对象的构造、析构则衔接在它们之间。

### 3. 数组的分配与逐个构造

`new T[n]` 先调用一次 `operator new[]`，取得容纳整个数组的连续空间，然后在其中逐个初始化元素。

`delete[] p` 按与构造相反的顺序逐个销毁元素，随后调用一次 `operator delete[]`，归还整块空间。

如果数组构造到一半时某个元素的构造函数抛出异常，已经构造成功的元素也需要被销毁，然后释放整块空间。后面的反汇编中会出现为这种情况准备的清理分支。

## 三、从反汇编观察数组分配与释放

前面的用法要求单个对象与数组分别匹配 `delete`、`delete[]`。接下来故意使用不匹配的形式，观察它在具体环境中为什么表现不同。

下面使用 Ubuntu、Clang、LLDB 的 x86-64 环境，分别观察 `int` 数组和两种类数组，调试的可执行文件均命名为 `main-debug`。记录中行末的中文是阅读注释，命令、符号、地址和数值保持原样。

这三组示例都将 `new[]` 与 `delete` 搭配使用，属于未定义行为。下面结合生成的机器码，分析各次运行中的具体表现。

### 1. int 数组：一次申请 40 字节

```cpp
int main()
{
    auto p = new int[10];
    (void)p;
    delete p;
}
```

Clang 给出了如下警告：

```bash
[wind@ubuntu-asus build]$ cmake --build .
[0/2] Re-checking globbed directories... 〔重新检查自动收集源文件的目录。〕
[1/4] Building CXX object CMakeFiles/main.dir/src/main.cpp.o 〔正在编译 C++ 源文件。〕
/home/wind/CS-Rebuild/04-CPP-Language-Basics/C++内存管理/src/main.cpp:6:5: warning: 'delete' applied to a pointer that was allocated with 'new[]'; did you mean 'delete[]'? [-Wmismatched-new-delete] 〔警告：对由 new[] 分配的指针使用了 delete，是否应写为 delete[]？〕
    6 |     delete p;
      |     ^
      |           []
/home/wind/CS-Rebuild/04-CPP-Language-Basics/C++内存管理/src/main.cpp:4:14: note: allocated with 'new[]' here 〔提示：此处使用 new[] 分配。〕
    4 |     auto p = new int[10];
      |              ^
1 warning generated. 〔共生成 1 条警告。〕
[2/4] Building CXX object CMakeFiles/main_sanitize.dir/src/main.cpp.o 〔正在编译 C++ 源文件。〕
/home/wind/CS-Rebuild/04-CPP-Language-Basics/C++内存管理/src/main.cpp:6:5: warning: 'delete' applied to a pointer that was allocated with 'new[]'; did you mean 'delete[]'? [-Wmismatched-new-delete] 〔警告：对由 new[] 分配的指针使用了 delete，是否应写为 delete[]？〕
    6 |     delete p;
      |     ^
      |           []
/home/wind/CS-Rebuild/04-CPP-Language-Basics/C++内存管理/src/main.cpp:4:14: note: allocated with 'new[]' here 〔提示：此处使用 new[] 分配。〕
    4 |     auto p = new int[10];
      |              ^
1 warning generated. 〔共生成 1 条警告。〕
[4/4] Linking CXX executable main-debug-sanitize 〔正在链接可执行文件。〕
[wind@ubuntu-asus build]$
```

构建日志中的两个目标都编译了这个文件，因此相同警告出现了两遍，本次构建仍然完成。

下面进入 LLDB，查看生成的指令：

```text
[wind@ubuntu-asus build]$ lldb ./main-debug
(lldb) target create "./main-debug"
Current executable set to '/home/wind/CS-Rebuild/04-CPP-Language-Basics/C++内存管理/build/main-debug' (x86_64). 〔已设置当前调试的可执行文件。〕
(lldb) breakpoint set --name main
Breakpoint 1: where = main-debug`main + 15 at main.cpp:4:14, address = 0x000000000000115f 〔断点位置、源码位置与地址。〕
(lldb) run
Process 985043 launched: '/home/wind/CS-Rebuild/04-CPP-Language-Basics/C++内存管理/build/main-debug' (x86_64) 〔进程已启动。〕
Process 985043 stopped 〔进程已停止。〕
* thread #1, name = 'main-debug', stop reason = breakpoint 1.1 〔当前线程，停止原因为命中断点。〕
    frame #0: 0x000055555555515f main-debug`main at main.cpp:4:14 〔当前栈帧的指令地址与源码位置。〕
   1   	
   2   	
   3   	int main(){
-> 4   	    auto p = new int[10];
   5   	    (void)p;
   6   	    delete p;
   7   	}
(lldb) settings set stop-disassembly-display always
(lldb) settings set stop-line-count-before 0
(lldb) settings set stop-line-count-after 0
(lldb) disassemble --frame
main-debug`main:
    0x555555555150 <+0>:  pushq  %rbp
    0x555555555151 <+1>:  movq   %rsp, %rbp
    0x555555555154 <+4>:  subq   $0x20, %rsp
    0x555555555158 <+8>:  movl   $0x0, -0x4(%rbp)
->  0x55555555515f <+15>: movl   $0x28, %edi
    0x555555555164 <+20>: callq  0x555555555030 ; 符号桩： operator new[](unsigned long)
    0x555555555169 <+25>: movq   %rax, -0x10(%rbp)
    0x55555555516d <+29>: movq   -0x10(%rbp), %rax
    0x555555555171 <+33>: movq   %rax, -0x18(%rbp)
    0x555555555175 <+37>: cmpq   $0x0, %rax
    0x555555555179 <+41>: je     0x555555555189 ; <+57> at main.cpp:7:1
    0x55555555517b <+43>: movq   -0x18(%rbp), %rdi
    0x55555555517f <+47>: movl   $0x4, %esi
    0x555555555184 <+52>: callq  0x555555555040 ; 符号桩： operator delete(void*, unsigned long)
    0x555555555189 <+57>: movl   -0x4(%rbp), %eax
    0x55555555518c <+60>: addq   $0x20, %rsp
    0x555555555190 <+64>: popq   %rbp
    0x555555555191 <+65>: retq   
(lldb)
```

这里设置的三条 `settings` 命令用于让停止位置显示反汇编，并隐藏前后的源码行；`disassemble --frame` 列出当前栈帧对应函数的反汇编。

本组记录中，`sizeof(int) == 4`。调用前的 `movl $0x28, %edi` 把 `40` 放入第一个整数参数寄存器，随后调用 `operator new[](unsigned long)`。这次申请的大小就是 `10 × 4 = 40` 字节。

调用返回后，`%rax` 中的地址被保存在 `-0x10(%rbp)`，也就是局部指针 `p` 的位置。

释放部分调用的却是 `operator delete(void*, unsigned long)`，这是带大小参数的单对象释放函数。记录中传入的指针来自 `p`，第二个参数为 `0x4`，即一个 `int` 的大小。这也能直接看出，编译器正在按照单对象 `delete` 的形式生成代码。

本组生成代码中，数组分配函数返回的地址直接存入 `p`，释放时也直接传出这个地址。接下来换成类对象，观察构造和析构会给这条路径带来什么变化。

### 2. 有构造函数、没有自定义析构函数的类

把元素换成只含一个 `int` 成员的类：

```cpp
// A.hpp
#pragma once

namespace wind {
class A {
   public:
    A(int val = 5) : _i(1) {
        _i = val;
    }

   private:
    int _i;
};

}  // namespace wind

// main.cpp
#include "A.hpp"

int main(){
    auto p = new wind::A[10];
    (void)p;
    delete p;
}
```

构造函数将 `_i` 的最终值设为 `val`；默认实参为 `5`。

```text
(lldb) run
Process 1007672 launched: '/home/wind/CS-Rebuild/04-CPP-Language-Basics/C++内存管理/build/main-debug' (x86_64) 〔进程已启动。〕
Process 1007672 stopped 〔进程已停止。〕
* thread #1, name = 'main-debug', stop reason = breakpoint 1.1 〔当前线程，停止原因为命中断点。〕
    frame #0: 0x000055555555517f main-debug`main at main.cpp:4:14 〔当前栈帧的指令地址与源码位置。〕
   1   	#include "A.hpp"
   2   	
   3   	int main(){
-> 4   	    auto p = new wind::A[10];
   5   	    (void)p;
   6   	    delete p;
   7   	}
(lldb) disassemble --frame
main-debug`main:
    0x555555555170 <+0>:   pushq  %rbp
    0x555555555171 <+1>:   movq   %rsp, %rbp
    0x555555555174 <+4>:   subq   $0x50, %rsp
    0x555555555178 <+8>:   movl   $0x0, -0x4(%rbp)
->  0x55555555517f <+15>:  movl   $0x28, %edi
    0x555555555184 <+20>:  callq  0x555555555030 ; 符号桩： operator new[](unsigned long)
    0x555555555189 <+25>:  movq   %rax, -0x38(%rbp)
    0x55555555518d <+29>:  movq   %rax, %rcx
    0x555555555190 <+32>:  addq   $0x28, %rcx
    0x555555555194 <+36>:  movq   %rcx, -0x30(%rbp)
    0x555555555198 <+40>:  movq   %rax, -0x28(%rbp)
    0x55555555519c <+44>:  movq   -0x28(%rbp), %rdi
    0x5555555551a0 <+48>:  movq   %rdi, -0x40(%rbp)
    0x5555555551a4 <+52>:  movl   $0x5, %esi
    0x5555555551a9 <+57>:  callq  0x555555555220 ; wind::A::A at A.hpp:6
    0x5555555551ae <+62>:  jmp    0x5555555551b0 ; <+64> at main.cpp
    0x5555555551b0 <+64>:  movq   -0x30(%rbp), %rcx
    0x5555555551b4 <+68>:  movq   -0x40(%rbp), %rax
    0x5555555551b8 <+72>:  addq   $0x4, %rax
    0x5555555551bc <+76>:  cmpq   %rcx, %rax
    0x5555555551bf <+79>:  movq   %rax, -0x28(%rbp)
    0x5555555551c3 <+83>:  jne    0x55555555519c ; <+44> at main.cpp
    0x5555555551c5 <+85>:  movq   -0x38(%rbp), %rax
    0x5555555551c9 <+89>:  movq   %rax, -0x10(%rbp)
    0x5555555551cd <+93>:  movq   -0x10(%rbp), %rax
    0x5555555551d1 <+97>:  movq   %rax, -0x48(%rbp)
    0x5555555551d5 <+101>: cmpq   $0x0, %rax
    0x5555555551d9 <+105>: je     0x5555555551e9 ; <+121> at main.cpp:7:1
    0x5555555551db <+107>: movq   -0x48(%rbp), %rdi
    0x5555555551df <+111>: movl   $0x4, %esi
    0x5555555551e4 <+116>: callq  0x555555555060 ; 符号桩： operator delete(void*, unsigned long)
    0x5555555551e9 <+121>: movl   -0x4(%rbp), %eax
    0x5555555551ec <+124>: addq   $0x50, %rsp
    0x5555555551f0 <+128>: popq   %rbp
    0x5555555551f1 <+129>: retq   
    0x5555555551f2 <+130>: movq   -0x38(%rbp), %rdi
    0x5555555551f6 <+134>: movq   %rax, %rcx
    0x5555555551f9 <+137>: movl   %edx, %eax
    0x5555555551fb <+139>: movq   %rcx, -0x18(%rbp)
    0x5555555551ff <+143>: movl   %eax, -0x1c(%rbp)
    0x555555555202 <+146>: movl   $0x28, %esi
    0x555555555207 <+151>: callq  0x555555555040 ; 符号桩： operator delete[](void*, unsigned long)
    0x55555555520c <+156>: movq   -0x18(%rbp), %rdi
    0x555555555210 <+160>: callq  0x555555555050 ; 符号桩： _Unwind_Resume
(lldb)
```

这次传给 `operator new[]` 的仍然是 `0x28`，即 `40` 字节。分配之后，多了一段循环调用构造函数的过程：

```asm
0x55555555519c <+44>:  movq   -0x28(%rbp), %rdi
0x5555555551a4 <+52>:  movl   $0x5, %esi
0x5555555551a9 <+57>:  callq  0x555555555220 ; wind::A::A
...
0x5555555551b8 <+72>:  addq   $0x4, %rax
0x5555555551bc <+76>:  cmpq   %rcx, %rax
0x5555555551c3 <+83>:  jne    0x55555555519c
```

`%rdi` 接收当前元素的地址，作为构造函数的 `this`；`%esi` 接收默认实参 `5`。每构造完一个元素，当前地址前进 `4` 字节，直到走完 `40` 字节的元素区域。

这正好对应“整块申请、逐个构造”。

这个类没有自定义析构函数，唯一的数据成员是 `int`，销毁它时没有需要执行的清理工作。它的隐式析构函数属于平凡析构函数（trivial destructor），在这里可以先理解为：编译器按类型规则判定，销毁对象无需执行析构操作。

因此，本组生成代码中省去了逐个析构的步骤，也没有保存数组元素个数。`p` 与分配函数返回的地址相同，直接传给释放函数时仍然是整块空间的起点。这解释了本次运行没有出现明显错误的现象。

反汇编在 `retq` 后面还列出了 `operator delete[]` 和 `_Unwind_Resume`。这是为构造失败准备的清理分支：构造函数抛出异常时，先释放已申请的空间，再继续向外传递异常。

### 3. 加入自定义析构函数

现在为同一个类加入析构函数：

```cpp
// A.hpp
#pragma once

#include <iostream>

namespace wind {
class A {
   public:
    A(int val = 5) : _i(1) {
        _i = val;
    }

    ~A() {
        std::cout << "===" << std::endl;
    }

   private:
    int _i;
};

}  // namespace wind

// main.cpp
#include "A.hpp"

int main(){
    auto p = new wind::A[10];
    (void)p;
    delete p;
}
```

运行结果与随后进行的调试记录如下：

```text
[wind@ubuntu-asus build]$ ./main-debug
===
munmap_chunk(): invalid pointer 〔内存管理器收到无效指针。〕
Aborted (core dumped) 〔程序已中止，并报告核心转储。〕
[wind@ubuntu-asus build]$ lldb ./main-debug
(lldb) target create "./main-debug"
Current executable set to '/home/wind/CS-Rebuild/04-CPP-Language-Basics/C++内存管理/build/main-debug' (x86_64). 〔已设置当前调试的可执行文件。〕
(lldb) breakpoint set --name main
Breakpoint 1: where = main-debug`main + 15 at main.cpp:4:14, address = 0x000000000000126f 〔断点位置、源码位置与地址。〕
(lldb) run
Process 1014940 launched: '/home/wind/CS-Rebuild/04-CPP-Language-Basics/C++内存管理/build/main-debug' (x86_64) 〔进程已启动。〕
Process 1014940 stopped 〔进程已停止。〕
* thread #1, name = 'main-debug', stop reason = breakpoint 1.1 〔当前线程，停止原因为命中断点。〕
    frame #0: 0x000055555555526f main-debug`main at main.cpp:4:14 〔当前栈帧的指令地址与源码位置。〕
   1   	#include "A.hpp"
   2   	
   3   	int main(){
-> 4   	    auto p = new wind::A[10];
   5   	    (void)p;
   6   	    delete p;
   7   	}
(lldb) disassemble --frame
main-debug`main:
    0x555555555260 <+0>:   pushq  %rbp
    0x555555555261 <+1>:   movq   %rsp, %rbp
    0x555555555264 <+4>:   subq   $0x60, %rsp
    0x555555555268 <+8>:   movl   $0x0, -0x4(%rbp)
->  0x55555555526f <+15>:  movl   $0x30, %edi
    0x555555555274 <+20>:  callq  0x555555555050 ; 符号桩： operator new[](unsigned long)
    0x555555555279 <+25>:  movq   %rax, -0x40(%rbp)
    0x55555555527d <+29>:  movq   $0xa, (%rax)
    0x555555555284 <+36>:  addq   $0x8, %rax
    0x555555555288 <+40>:  movq   %rax, -0x38(%rbp)
    0x55555555528c <+44>:  movq   %rax, %rcx
    0x55555555528f <+47>:  addq   $0x28, %rcx
    0x555555555293 <+51>:  movq   %rcx, -0x30(%rbp)
    0x555555555297 <+55>:  movq   %rax, -0x28(%rbp)
    0x55555555529b <+59>:  movq   -0x28(%rbp), %rdi
    0x55555555529f <+63>:  movq   %rdi, -0x48(%rbp)
    0x5555555552a3 <+67>:  movl   $0x5, %esi
    0x5555555552a8 <+72>:  callq  0x555555555350 ; wind::A::A at A.hpp:8
    0x5555555552ad <+77>:  jmp    0x5555555552af ; <+79> at main.cpp
    0x5555555552af <+79>:  movq   -0x30(%rbp), %rcx
    0x5555555552b3 <+83>:  movq   -0x48(%rbp), %rax
    0x5555555552b7 <+87>:  addq   $0x4, %rax
    0x5555555552bb <+91>:  cmpq   %rcx, %rax
    0x5555555552be <+94>:  movq   %rax, -0x28(%rbp)
    0x5555555552c2 <+98>:  jne    0x55555555529b ; <+59> at main.cpp
    0x5555555552c4 <+100>: movq   -0x38(%rbp), %rax
    0x5555555552c8 <+104>: movq   %rax, -0x10(%rbp)
    0x5555555552cc <+108>: movq   -0x10(%rbp), %rax
    0x5555555552d0 <+112>: movq   %rax, -0x50(%rbp)
    0x5555555552d4 <+116>: cmpq   $0x0, %rax
    0x5555555552d8 <+120>: je     0x5555555552f1 ; <+145> at main.cpp:7:1
    0x5555555552da <+122>: movq   -0x50(%rbp), %rdi
    0x5555555552de <+126>: callq  0x555555555370 ; wind::A::~A at A.hpp:12
    0x5555555552e3 <+131>: movq   -0x50(%rbp), %rdi
    0x5555555552e7 <+135>: movl   $0x4, %esi
    0x5555555552ec <+140>: callq  0x555555555140 ; 符号桩： operator delete(void*, unsigned long)
    0x5555555552f1 <+145>: movl   -0x4(%rbp), %eax
    0x5555555552f4 <+148>: addq   $0x60, %rsp
    0x5555555552f8 <+152>: popq   %rbp
    0x5555555552f9 <+153>: retq   
    0x5555555552fa <+154>: movq   -0x38(%rbp), %rcx
    0x5555555552fe <+158>: movq   %rax, %rsi
    0x555555555301 <+161>: movq   -0x48(%rbp), %rax
    0x555555555305 <+165>: movq   %rsi, -0x18(%rbp)
    0x555555555309 <+169>: movl   %edx, -0x1c(%rbp)
    0x55555555530c <+172>: cmpq   %rax, %rcx
    0x55555555530f <+175>: movq   %rax, -0x58(%rbp)
    0x555555555313 <+179>: je     0x555555555337 ; <+215> at main.cpp
    0x555555555315 <+181>: movq   -0x58(%rbp), %rdi
    0x555555555319 <+185>: addq   $-0x4, %rdi
    0x55555555531d <+189>: movq   %rdi, -0x60(%rbp)
    0x555555555321 <+193>: callq  0x555555555370 ; wind::A::~A at A.hpp:12
    0x555555555326 <+198>: movq   -0x38(%rbp), %rcx
    0x55555555532a <+202>: movq   -0x60(%rbp), %rax
    0x55555555532e <+206>: cmpq   %rcx, %rax
    0x555555555331 <+209>: movq   %rax, -0x58(%rbp)
    0x555555555335 <+213>: jne    0x555555555315 ; <+181> at main.cpp
    0x555555555337 <+215>: movq   -0x40(%rbp), %rdi
    0x55555555533b <+219>: movl   $0x30, %esi
    0x555555555340 <+224>: callq  0x5555555550d0 ; 符号桩： operator delete[](void*, unsigned long)
    0x555555555345 <+229>: movq   -0x18(%rbp), %rdi
    0x555555555349 <+233>: callq  0x555555555130 ; 符号桩： _Unwind_Resume
(lldb) breakpoint set --file main.cpp --line 6
Breakpoint 2: where = main-debug`main + 108 at main.cpp:6:12, address = 0x00005555555552cc 〔断点位置、源码位置与地址。〕
(lldb) continue
Process 1014940 resuming 〔进程继续运行。〕
Process 1014940 stopped 〔进程已停止。〕
* thread #1, name = 'main-debug', stop reason = breakpoint 2.1 〔当前线程，停止原因为命中断点。〕
    frame #0: 0x00005555555552cc main-debug`main at main.cpp:6:12 〔当前栈帧的指令地址与源码位置。〕
   3   	int main(){
   4   	    auto p = new wind::A[10];
   5   	    (void)p;
-> 6   	    delete p;
   7   	}
(lldb) expression -- *(void**)($rbp - 0x40)
(void *) $0 = 0x00005555555592a0
(lldb) expression -- *(void**)($rbp - 0x10)
(void *) $1 = 0x00005555555592a8
(lldb) expression -- (char*)*(void**)($rbp - 0x10) - (char*)*(void**)($rbp - 0x40)
(long) $2 = 8
(lldb) memory read --format d --size 8 --count 1 0x5555555592a0
0x5555555592a0: 10
(lldb)
```

先看发生变化的分配部分：

```asm
0x55555555526f <+15>: movl   $0x30, %edi
0x555555555274 <+20>: callq  0x555555555050 ; operator new[](unsigned long)
0x555555555279 <+25>: movq   %rax, -0x40(%rbp)
0x55555555527d <+29>: movq   $0xa, (%rax)
0x555555555284 <+36>: addq   $0x8, %rax
```

申请大小从 `0x28` 变成了 `0x30`，也就是从 `40` 字节变成 `48` 字节。分配函数返回后，程序先在起始地址写入八字节的 `10`，随后把地址向后移动八字节，再从这里开始构造数组元素。

这里的两个步长分别服务于不同目的：向后移动八字节是越过计数前缀；构造循环中每次前进四字节，仍然是移动到下一个 `A` 对象。

在执行 `delete p` 之前，LLDB 读到了两个地址：

| 栈中位置      | 本次记录中的值       | 含义                                          |
| ------------- | -------------------- | --------------------------------------------- |
| `-0x40(%rbp)` | `0x00005555555592a0` | `operator new[]` 返回的整块空间起始地址       |
| `-0x10(%rbp)` | `0x00005555555592a8` | `new wind::A[10]` 返回并存入 `p` 的首元素地址 |

将两个地址转成 `char*` 相减，得到 `8`；再从 `0x5555555592a0` 处读取一个八字节整数，结果为 `10`。因此，这次观察到的布局可以写成：

| 相对整块空间起点的偏移 | 大小    | 内容                      |
| ---------------------- | ------- | ------------------------- |
| `0`                    | 8 字节  | 数组元素个数 `10`         |
| `8`                    | 40 字节 | 连续存放的 10 个 `A` 对象 |

![本次 x86-64 实验中的数组计数前缀与元素区域](https://img.mdwind.online/img/20261101134511787.png)

这段放在数组元素之前的隐藏信息通常称为数组 cookie。它让编译器生成的数组销毁代码能够恢复元素个数，从而逐个析构，再找回整块空间的起点。

这类布局由应用二进制接口（ABI）约定。在本例中，计数占八字节，与该环境中的 `std::size_t` 大小一致；前缀的具体大小还与平台和元素类型的对齐要求有关。

### 4. 为什么只打印一次析构信息就崩溃

对照本组的释放指令：

```asm
0x5555555552da <+122>: movq   -0x50(%rbp), %rdi
0x5555555552de <+126>: callq  0x555555555370 ; wind::A::~A
0x5555555552e3 <+131>: movq   -0x50(%rbp), %rdi
0x5555555552e7 <+135>: movl   $0x4, %esi
0x5555555552ec <+140>: callq  0x555555555140 ; operator delete(void*, unsigned long)
```

源码写的是 `delete p`，编译器生成的正常路径就只对 `p` 所指的一个对象调用析构函数，因此只打印了一次 `===`。随后，它直接把 `p`，也就是 `0x5555555592a8`，交给单对象释放函数。

但这块空间的分配起点是 `0x5555555592a0`。现在送去释放的地址已经落在块内部，运行库于是报告无效指针。

这里能同时看到两项不匹配：只安排了一个对象的析构，并且没有按数组布局恢复分配起点。错误路径还传入了大小 `4`，而本组实际申请了 `48` 字节。

按这个布局推导，改用 `delete[] p` 后，数组删除过程会读取前面的元素个数，按逆序析构十个对象，再从首元素地址向前恢复出整块空间的起点，交给数组释放函数。

本组 `retq` 后面从 `<+154>` 开始的指令，仍然是在构造失败时才进入的清理分支。它会逆序析构已完成构造的元素，然后取出保存在 `-0x40(%rbp)` 的原始地址，释放整块空间。

### 5. 平凡析构与不同平台的记录

前一个类的隐式析构函数是平凡的；加入用户提供的析构函数后，析构函数就成为非平凡的，本例的数组布局也随之增加了元素计数。

这里的“平凡”是语言规则对类型性质的分类。用户提供的 `~A() {}` 即使函数体为空，也属于非平凡析构函数。编译器随后是否消除某次空函数调用，则属于生成代码时的优化。

再看一份 VS2008 环境中的记录：十个四字节对象共申请了 `44` 字节，其中前四字节用于计数。与上面的 Ubuntu x86-64 实验对照，可以看到相同的组织思路：前面保存计数，后面连续存放元素，只是计数前缀的大小不同。

![VS2008 环境中的数组分配记录](https://img.mdwind.online/md/202410101002279.png)

从这几组实验中，可以把数组管理过程串起来：申请连续空间，按需保存元素个数，逐个构造；删除时逐个析构，再归还整块空间。单对象和数组对应的处理过程不同，使用时也就分别匹配 `delete` 与 `delete[]`。

## 四、定位 new 表达式

### 1. 在已有空间中构造对象

既然空间申请与对象构造可以拆开，我们就可以先取得一块空间，再指定构造位置。完成后一项工作的语法称为定位 `new` 表达式（placement new）：

```cpp
new (address) T(args);
```

使用标准库提供的这种形式，需要包含 `<new>`。`address` 指定已有空间的位置，后面的 `T(args)` 指定要在这里构造的类型和参数。返回值是指向所构造对象的 `T*`。

标准定位分配函数直接返回传入的地址，随后由 `new` 表达式在该位置初始化对象。已有空间可以来自动态申请，也可以是预先准备好的局部存储；使用前要为对象留出足够大小和合适的对齐，并让这块存储在对象使用期间保持有效。

### 2. 分别管理空间和对象

下面申请一块容纳两个 `A` 对象的原始空间，再分别在两个位置构造对象：

```cpp
#include <cstddef>
#include <iostream>
#include <new>

namespace wind
{
class A
{
public:
    A(int val = 5)
        : _i(val)
    {
    }

    ~A()
    {
        std::cout << "~A(): " << _i << std::endl;
    }

private:
    int _i;
};
}  // namespace wind

int main()
{
    // 先取得原始空间；此时还没有构造 A 对象。
    void* storage = ::operator new(2 * sizeof(wind::A));
    auto bytes = (unsigned char*)(storage);

    // 分别在两个位置构造对象，并保留定位 new 返回的指针。
    wind::A* first = new (storage) wind::A;
    wind::A* second = new (bytes + sizeof(wind::A)) wind::A(6);

    // 先销毁对象，再释放整块原始空间。
    second->~A();
    first->~A();
    ::operator delete(storage);
    return 0;
}
```

`storage` 保存整块空间的起点，`bytes` 用于按字节计算位置。第一个对象从起点开始，第二个对象放在 `bytes + sizeof(wind::A)` 处，两个对象依次占用各自的空间。这个 `A` 只包含一个 `int`，上述分配和偏移也满足它的对齐要求。

定位 `new` 让我们可以显式开始一个对象的生命周期，而 `first->~A()`、`second->~A()` 显式结束对应对象的生命周期。显式析构不会释放外面的整块空间，因此后面仍需调用 `::operator delete(storage)`。

最后，使用保存的起点 `storage` 调用 `::operator delete`，归还最初申请的空间。若采用 `malloc` 取得原始空间，则相应使用 `free` 归还。

这里使用 `unsigned char*` 计算位置，每加 `1` 就前进一个字节，因此 `bytes + sizeof(wind::A)` 正好越过第一个对象所占的空间。指针运算的步长由所指类型决定：对于 `A*`，加 `1` 才表示前进一个 `A` 的大小。

### 3. 为什么会需要内存池

假设有户人家住在河边，每次用水都拿盆去河里取。洗漱、做饭、洗衣都要用水，来回取水就会很麻烦。于是，他们在院子里建一个池子，提前装满，后面用水时直接从池子里取。

内存池的思路与此相似：对于频繁创建、销毁的小对象，可以先从底层申请一块较大的空间，再由程序管理其中哪些位置空闲、哪些位置正在使用。需要对象时，在合适的位置构造；对象使用完后，析构它，并把位置交回池中，供后续复用。

池子可以在一批对象创建之前建立，并随着程序运行按需扩充。对象创建和销毁时，优先在池中分配、复用位置，从而减少向底层申请和释放空间的次数。

定位 `new` 负责在指定位置构造对象；内存池则在此基础上，继续管理空闲位置、容量、对齐和空间复用。上面的示例展示了其中最基本的动作：先取得空间，再在选定位置构造，使用完后分别处理对象销毁与空间归还。

对于连接、线程等经常复用的资源，也有类似的资源池设计，通常统称为池化技术。

## 五、C++ 程序中的内存分布

后续学习 Linux 时会更详细地讨论进程地址空间。这里先沿用常见的栈、堆、静态存储区域等概念，区分“变量本身”与“变量所指向的数据”。

在常见实现中，普通局部对象通常放在栈上，动态申请的空间通常由堆分配器管理，全局对象与静态局部对象具有静态存储期。静态存储区域还会根据是否初始化、是否只读等继续划分。

代码段主要存放机器指令，只读数据区域通常存放字符串字面量等数据。下面就按这些常见区域，观察示例中的变量与它们所指向的数据。

### 1. 先看题目

```cpp
#include <cstdlib>

int globalVar = 1;
static int staticGlobalVar = 1;

void Test()
{
    static int staticVar = 1;
    int localVar = 1;
    int num1[10] = {1, 2, 3, 4};
    char char2[] = "abcd";
    const char* pChar3 = "abcd";

    int* ptr1 = static_cast<int*>(std::malloc(sizeof(int) * 4));
    int* ptr2 = static_cast<int*>(std::calloc(4, sizeof(int)));
    int* ptr3 = static_cast<int*>(std::realloc(ptr2, sizeof(int) * 4));

    std::free(ptr1);
    if (ptr3 != nullptr)
    {
        std::free(ptr3);
    }
    else
    {
        std::free(ptr2);
    }
}
```

这里用 `ptr3` 接收 `realloc` 的结果。成功时，释放返回的新指针；失败时，原块仍然有效，因此释放 `ptr2`。

### 2. 区分指针变量与所指对象

| 名称或表达式      | 所讨论的对象                              | 常见实现中的区域 |
| ----------------- | ----------------------------------------- | ---------------- |
| `globalVar`       | 全局 `int` 对象                           | 静态存储区域     |
| `staticGlobalVar` | 文件作用域的静态 `int` 对象               | 静态存储区域     |
| `staticVar`       | 静态局部 `int` 对象                       | 静态存储区域     |
| `localVar`        | 普通局部 `int` 对象                       | 栈               |
| `num1`            | 局部整型数组                              | 栈               |
| `char2`           | 局部字符数组                              | 栈               |
| `*char2`          | `char2` 的第一个字符元素                  | 栈               |
| `pChar3`          | 局部指针变量                              | 栈               |
| `*pChar3`         | 字符串字面量中的第一个字符                | 只读数据区域     |
| `ptr1`            | 局部指针变量                              | 栈               |
| `*ptr1`           | 申请成功时，动态空间中的第一个 `int` 对象 | 堆               |

`char2` 是局部数组，在多数表达式中会转换为首元素指针，`*char2` 则表示它的第一个字符元素。

`char char2[] = "abcd";` 用字符串字面量初始化局部数组，数组中存放着 `a`、`b`、`c`、`d` 和末尾的 `\0`，这些字符可以通过 `char2` 修改。

`const char* pChar3 = "abcd";` 中，局部指针变量 `pChar3` 通常位于栈上，它指向的字符串字面量具有静态存储期，通常位于只读数据区域。`*pChar3` 表示其中的首字符 `a`。

同样，局部指针变量 `ptr1` 通常位于栈上，申请成功后它指向堆上的动态空间。

结合下面的示意图，可以进一步观察这些对象与区域之间的关系。

![变量、指针与所指数据的内存分布示意](https://img.mdwind.online/md/202410101256070.png)

## 六、内存泄漏

动态申请的空间使用完后，如果没有释放，就会造成内存泄漏。常见情况是丢失了唯一保存地址的指针，或者某条执行路径漏掉了释放操作，导致这块空间在后续运行中无法再被正常回收和复用。

```cpp
void f()
{
    auto p = new int[100];
    // 使用 p 所指的数组……
} // p 这个局部指针消失了，动态数组仍未释放。
```

指针变量的生命周期结束，不会自动执行 `delete[]`。上面的函数每调用一次，就留下一个未释放的数组。对应的基本修正是，在不再需要数组时执行 `delete[] p`。

对于短时间运行、分配量很小的程序，一次泄漏可能不容易观察出来；对于长期运行的服务，反复泄漏会使进程占用不断累积，增加内存压力，严重时造成分配失败或进程被系统终止。因此，持续运行的程序需要在运行过程中及时回收不再使用的空间。

实际代码的难点在于：函数可能有多个返回位置，还可能抛出异常，申请与释放不一定紧挨着出现。单靠每个分支都手动记住释放，规模一大就容易遗漏。

前面已经知道，局部类对象离开作用域时会自动析构。后续会把这条规则与资源管理结合起来：由对象保存资源，并在析构时释放，这就是 RAII（资源获取即初始化）所采用的基本思路。智能指针等 C++ 工具会进一步帮助管理动态对象。本节先建立分配、构造、析构和释放之间的关系，具体技术留到后面展开。

## 参考资料

- [C++ 标准草案：new 表达式](https://eel.is/c++draft/expr.new)
- [C++ 标准草案：delete 表达式](https://eel.is/c++draft/expr.delete)
- [C++ 标准草案：单对象分配函数与释放函数](https://eel.is/c++draft/new.delete.single)
- [C++ 标准草案：标准定位分配形式](https://eel.is/c++draft/new.delete.placement)
- [Itanium C++ ABI：数组 cookie](https://itanium-cxx-abi.github.io/cxx-abi/abi.html#array-cookies)
