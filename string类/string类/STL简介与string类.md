# STL 简介与 string 类

## 从 STL 说起

前面我们已经学过模板：借助模板，一份代码可以适用于不同类型。C++ 标准库中有一组基于这种思想设计的组件，通常称为 STL，即标准模板库（Standard Template Library）。它为我们提供了容器、算法等工具，也提供了把这些工具组合起来的方式。

STL 最初由 Alexander Stepanov 和 Meng Lee 等人在惠普实验室开发，后来被纳入 C++ 标准化工作。此后，各家标准库实现都在不断发展。我们平时说的 STL，既可能指早期的标准模板库，也可能泛指标准库中延续了这种设计风格的组件。

### STL 的组成

学习时常把 STL 的组件分为六类：容器、算法、迭代器、函数对象、适配器和分配器。

容器负责组织和保存数据，算法负责对数据进行查找、排序等操作；迭代器连接两者，让算法能以统一的方式访问不同容器中的元素。函数对象可以为算法提供操作或判断规则，适配器用来调整已有组件的接口，分配器负责提供内存分配相关的支持。

![image-20241012084251340](https://img.mdwind.online/md/202410120842503.png)

这些名称现在先有个印象即可。后面我们会先使用标准库，观察它提供了什么功能，再通过自己实现一些组件来理解其中的设计。

### 常见的标准库实现

C++ 标准规定了标准库提供的接口和行为，而具体代码由不同的实现提供。常见的实现有 GCC 项目中的 libstdc++、LLVM 项目中的 libc++，以及 Microsoft 的 C++ 标准库实现。

libstdc++ 的一部分代码有 SGI STL 的历史渊源，但今天的 libstdc++ 已经经过长期发展。编译器和标准库也需要分开看：例如 Clang 可以根据环境和配置使用 libc++ 或 libstdc++。本文的实验分别使用 MSVC STL、GNU libstdc++ 和 LLVM libc++，借助运行结果观察不同实现的行为。

## 从 STL 到 string

接下来先学习 `std::string`。它属于 C++ 标准库，用来保存和操作字符序列；它也提供了与标准库容器相近的接口，比如迭代器、`size` 和 `begin`，因此适合作为接触标准库的起点。

`std::string` 是 `std::basic_string<char>` 的类型别名，使用时需要包含 `<string>`。它按 `char` 元素管理内容：如果存放的是 UTF-8 编码的中文，一个汉字通常占多个字节，`size()` 返回的是 `char` 元素的数量，不能直接当作汉字个数。

[String 文档](https://legacy.cplusplus.com/reference/string/string/)列出了它的成员类型、成员函数和非成员函数。下面先把常见接口分组看一遍，后面再结合例子使用。

![image-20241012090353846](https://img.mdwind.online/md/202410120903961.png)

### 成员类型与迭代器

`value_type` 表示元素类型，对 `std::string` 来说是 `char`；`size_type` 用于表示长度和位置；`reference` 与 `const_reference` 分别对应字符引用和常量字符引用。`traits_type` 和 `allocator_type` 分别提供字符操作和内存分配相关的支持。

迭代器可以理解为访问序列元素的工具，使用方式与指针相似：解引用访问当前元素，递增移动到下一个位置。`iterator` 可用于读写字符，`const_iterator` 用于只读访问；`reverse_iterator` 和 `const_reverse_iterator` 用于反向遍历。具体写法会在字符串遍历中看到。

### 常用接口

- 构造、析构与赋值：构造函数创建字符串对象，析构函数负责清理，`operator=` 和 `assign` 用于赋值。
- 遍历：`begin`、`end` 给出正向遍历的起点和终点；`rbegin`、`rend` 用于反向遍历；`cbegin`、`cend`、`crbegin`、`crend` 返回只读迭代器。
- 长度和容量：`size` 与 `length` 返回字符数量，`empty` 判断是否为空，`capacity` 返回当前容量，`max_size` 给出实现允许的最大长度。`reserve` 请求预留容量，`resize` 调整长度，`clear` 清空内容，`shrink_to_fit` 请求减少多余容量。
- 元素访问：`operator[]` 和 `at` 按下标访问，`front` 和 `back` 访问首尾字符。
- 修改：`operator+=`、`append`、`push_back` 用于追加；`insert`、`erase`、`replace` 分别用于插入、删除和替换；`pop_back` 删除末尾字符，`swap` 交换两个字符串的值。
- 字符串操作：`c_str` 和 `data` 提供字符数据的指针；`copy` 复制指定范围；`find`、`rfind` 及 `find_first_of` 等用于查找；`substr` 生成子串；`compare` 比较内容。
- 非成员操作：`operator+` 拼接字符串，关系运算符用于比较，`swap` 交换字符串，`operator>>`、`operator<<` 与 `getline` 用于输入输出。

还有一个特殊值 `std::string::npos`，常用于表示查找失败，也常作为长度参数的默认值，具体含义放到下面的例子中讨论。

## 使用

### 对象实例化

在文档的构造函数部分，可以看到创建字符串对象的多种方式。

![image-20241012165510456](https://img.mdwind.online/md/202410121655654.png)

```cpp
#include <iostream>
#include <string>

int main() {
    // 以无参形式实例化
    std::string s1;
    // 以常量字符串形式实例化
    std::string s2("hello string!");

    // 容量不够会自己扩容

    // 支持流插入, 流提取
    std::cout << s2 << std::endl;
    std::cin >> s1;
    std::cout << s1 << std::endl;
    return 0;
}
```

文中的截图来自不同时期的实验，部分截图中的代码在命名或输出格式上与正文略有不同。

带随机背景的 Visual Studio 截图使用的是 VS 2022；本文中默认外观的 Visual Studio 截图使用 VS 2026，个别实验也会使用界面较早的版本。VS Code 截图展示的是编辑器界面，实际编译运行的环境可能是远程 Linux，也可能是本地 Windows，需要结合旁边的实验说明和终端输出来判断。

![image-20241012170616516](https://img.mdwind.online/md/202410121706589.png)

```bash
[wind@ubuntu-asus build]$ ./main-debug
hello string!
hello STL!
hello
[wind@ubuntu-asus build]$ # 输入截断和流提取有关, 我们现在不去关注
```

### 字符串拼接

![image-20241012170918517](https://img.mdwind.online/md/202410121709659.png)

```cpp
#include <iostream>
#include <string>

int main() {
    std::string s1("hello ");
    std::string s2("string");
    std::string s3 = s1 + s2;
    std::cout << s3 << std::endl;
    std::cout << "std::" << s2 << std::endl;
    return 0;
}
```

```bash
[wind@ubuntu-asus build]$ ./main-debug
hello string
std::string
[wind@ubuntu-asus build]$ 
```

### 字符串遍历

```cpp
#include <iostream>
#include <string>

int main() {
    std::string s1("abcd");
    std::string s2("=====================");

    // 使用 operator[] 重载遍历字符串
    int i = 0;
    int len = s1.size();
    for (; i < len; i++) {
        ++s1[i];
    }
    std::cout << s1 << std::endl;

    // 注意, `[]`没有范围检查, 可能会越界访问
    // 可以使用成员函数 `at` 来替代
    for (i = 0; i < len; i++) {
        --s1[i];
    }
    std::cout << s1 << std::endl;

    // 使用迭代器遍历字符串
    // 迭代器是访问 STL 容器中元素的通用方式
    std::string::iterator it = s1.begin();
    while (it != s1.end()) {
        std::cout << *it;
        ++it;
    }
    // begin 返回指向第一个有效字符的迭代器
    // end 返回指向最后一个元素下一元素的迭代器
    // 对于 "abcd\0"来说, begin 返回的迭代器指向a
    // end 表示字符序列的末尾位置
    // 迭代器本身的设计目标就是像指针一样使用
    // 甚至有些底层就是指针
    std::cout << std::endl;
    // 因为有些容器中元素的序列没有明确的大小及线性关系
    // 所以不建议使用 <= 这种比较运算符
    // 而是都使用 == 或者 !=
    std::cout << s2 << std::endl;

    // 除此之外, 也有反向迭代器
    // rbegin 返回指向最后一个有效元素的迭代器
    // rend 表示反向遍历的结束位置，不能解引用
    std::string::reverse_iterator rit = s1.rbegin();
    while (rit != s1.rend()) {
        std::cout << *rit;
        ++rit;
    }
    std::cout << std::endl;
    // 迭代器的 ++ 经过特殊重载
    // 表示以各自 end 为目标的下一元素序列位置
    // iterator ++ 就是 begin -> end
    // reverse_iterator(为了看得清楚, 上面故意不用auto)
    // 就是 rbegin -> rend
    // -- 看情况, 有的容器迭代器可能不提供

    // C++ 的一个新语法(其实已经很旧了)
    // (只是对刚看到的我们比较新)
    // 叫做范围 for, 其实就是对普通迭代器
    // 的一种再封装, 让我们少写点东西
    for (auto ch : s1) {
        std::cout << ch;
    }
    std::cout << std::endl;

    // 当然也可以使用引用的方式
    // 对这些元素进行读写操作
    // 或者优化效率(看情况)
    for (auto& ch : s1) {
        std::cout << ch;
    }
    std::cout << std::endl;

    return 0;
}
```

```bash
[wind@ubuntu-asus build]$ ./main-debug
bcde
abcd
abcd
=====================
dcba
abcd
abcd
[wind@ubuntu-asus build]$ 
```

### 常迭代器

为了适应常对象，begin和end或者rbegin和rend都有两个重载版本，一个索引普通对象，一个索引常对象

![image-20241012195442259](https://img.mdwind.online/md/202410121954516.png)

![image-20241012195511649](https://img.mdwind.online/md/202410121955819.png)

C++11 增加的 `cbegin`、`cend`、`crbegin` 和 `crend` 返回常量迭代器；普通对象和常对象都可以调用它们。

### npos

在上面的文档中我们看到一个被特别标注的值：npos

![image-20241012200348416](https://img.mdwind.online/md/202410122003574.png)

`static const size_t npos = -1;`

`npos` 的类型是 `string::size_type`，它由 `-1` 转换而来，对应这个无符号类型所能表示的最大值。它常作为一个特殊标记使用，具体含义由接口决定。

例如，子串构造函数可以从 `pos` 开始，最多取 `len` 个字符：

```cpp
string(const string& str, size_t pos, size_t len = npos);
```

这里的 `len` 表示数量。如果剩余字符不足 `len` 个，就取到末尾；省略 `len` 时，默认的 `npos` 表示从 `pos` 一直取到末尾。后面的 `find` 则用 `npos` 表示没有找到。

### 容量

```cpp
#include <iostream>
#include <string>

int main() {
    std::string s;
    size_t prev = s.capacity();
    std::cout << "初始容量: " << prev << std::endl;
    int cir = 0;
    for (; cir < 100; cir++) {
        s.push_back('c');
        size_t curr = s.capacity();
        if (prev != curr) {
            std::cout << "触发扩容, 新的容量是: ";
            std::cout << curr << std::endl;
            prev = curr;
        }
    }

    return 0;
}
```

MSVC STL（VS 2022）的运行结果为：

![image-20241014133109574](https://img.mdwind.online/md/202410141331751.png)

GNU libstdc++ 的历史输出：

```shell
[wind@starry-sky SGI版本string]$ ls
main.cpp  makefile  out
[wind@starry-sky SGI版本string]$ ./out
initial capacity:0
trigger expansion,The new capacity is:1
trigger expansion,The new capacity is:2
trigger expansion,The new capacity is:4
trigger expansion,The new capacity is:8
trigger expansion,The new capacity is:16
trigger expansion,The new capacity is:32
trigger expansion,The new capacity is:64
trigger expansion,The new capacity is:128
[wind@starry-sky SGI版本string]$
```

LLVM libc++ 的输出如下：

```bash
[wind@ubuntu-asus build]$ ./main-debug
初始容量: 22
触发扩容, 新的容量是: 47
触发扩容, 新的容量是: 95
触发扩容, 新的容量是: 191
[wind@ubuntu-asus build]$ 
```

三组结果采用了不同的容量增长方式，扩容策略由具体的标准库实现决定。`capacity()` 表示无需重新分配即可容纳的 `char` 元素数量，不把末尾额外的终止符计入其中。GNU libstdc++ 的历史终端记录中，目录名“SGI版本string”沿用了当时的称呼。

---------------------------

让我们来看看`reserve`，为了避免多次扩容而导致的效率低下，可以先预估字符串的大小，一次性提前开辟。

```cpp
#include <iostream>
#include <string>

int main() {
    std::string s;
    s.reserve(100);
    size_t prev = s.capacity();
    std::cout << "初始容量: " << prev << std::endl;
    int cir = 0;
    for (; cir < 100; cir++) {
        s.push_back('c');
        size_t curr = s.capacity();
        if (prev != curr) {
            std::cout << "触发扩容, 新的容量是: ";
            std::cout << curr << std::endl;
            prev = curr;
        }
    }

    return 0;
}
```

MSVC STL 的运行结果：

![image-20241014141338203](https://img.mdwind.online/md/202410141413311.png)

GNU libstdc++ 的历史输出：

```shell
[wind@starry-sky SGI版本string]$ vim main.cpp
[wind@starry-sky SGI版本string]$ make
[wind@starry-sky SGI版本string]$ ./out
initial capacity:100
[wind@starry-sky SGI版本string]$
```

LLVM libc++ 的运行结果：

```bash
[wind@ubuntu-asus build]$ ./main-debug
初始容量: 103
[wind@ubuntu-asus build]$ 
```

三组实验都为 100 个字符预留了足够的容量，其中 GNU libstdc++ 的结果恰好为 100，另外两种实现给出了更大的容量。

`reserve` 能不能缩容呢？这与标准版本有关：旧版接口曾允许把小于当前容量的请求作为非强制的缩容请求；从 C++20 起，带参数的 `reserve(n)` 在 `n` 不大于当前容量时不进行重新分配。需要请求收缩时，可以使用 `shrink_to_fit()`，实际是否收缩由实现决定。

下面先预留容量，再尝试请求更小的容量，观察结果：

```cpp
#include <iostream>
#include <string>

int main() {
    std::string s;
    s.reserve(100);
    size_t prev = s.capacity();
    std::cout << "初始容量: " << prev << std::endl;
    int cir = 0;
    for (; cir < 100; cir++) {
        s.push_back('c');
        size_t curr = s.capacity();
        if (prev != curr) {
            std::cout << "触发扩容, 新的容量是: ";
            std::cout << curr << std::endl;
            prev = curr;
        }
    }
    s.reserve(10);
    std::cout << "当前容量: " << s.capacity() << std::endl;

    return 0;
}
```

MSVC STL 的运行结果：

![image-20241014144657536](https://img.mdwind.online/md/202410141446640.png)

LLVM libc++ 的运行结果：

```bash
[wind@ubuntu-asus build]$ ./main-debug
初始容量: 103
当前容量: 103
[wind@ubuntu-asus build]$ 
```

这两次实验中，请求更小的容量后，字符串的容量都没有缩小。

---------------

`resize`可以调整当前字符串的长度

```cpp
void resize (size_t n);
void resize (size_t n, char c);
```

如果参数`n`小于当前字符串的长度，字符串的当前值将被缩短到前n个有效字符，也就是说，超出n的字符将被删除。

如果参数`n`大于当前字符串的长度，就会通过在当前内容的尾部插入一定数目字符的方式，把字符串的长度扩展到`n`；如果指定了参数`c`，就会把新增加的字符初始化为`c`，如果没有指定，新增加的字符就会被初始化为空字符，也就是`\0`。

```cpp
void test5()
{
	std::string s("hello world");
	std::cout << "Current capacity:" << s.capacity() << std::endl;
	std::cout << "Current size:" << s.size() << std::endl;
	s.resize(s.capacity());
	std::cout << "Current capacity:" << s.capacity() << std::endl;
	std::cout << "Current size:" << s.size() << std::endl;
}
```

![image-20241014151801601](https://img.mdwind.online/md/202410141518423.png)

![image-20241014151833674](https://img.mdwind.online/md/202410141518452.png)

![image-20241014151901361](https://img.mdwind.online/md/202410141519537.png)

![image-20241014152114545](https://img.mdwind.online/md/202410141521250.png)

缩小长度后，末尾超出新长度的字符会被移除：

![image-20241014152352323](https://img.mdwind.online/md/202410141523107.png)

### 元素访问

`at`和`operator[]`对于越界的处理。

`operator[]` 的下标可以访问 `0` 到 `size() - 1` 的字符；下标等于 `size()` 时可访问终止符。大于 `size()` 就越界了：

![image-20241014154334129](https://img.mdwind.online/md/202410141543268.png)

未定义的行为，也不知道会发生什么。

`at`的越界逻辑：

![image-20241014154612100](https://img.mdwind.online/md/202410141546258.png)

如果越界，会抛出异常。

### 追加

`append`比`operator+=`多了一些功能：

![image-20241014155201886](https://img.mdwind.online/md/202410141552045.png)

`operator+=`的参数可以是其他对象，另一个字符串，字符。

![image-20241014155358942](https://img.mdwind.online/md/202410141553101.png)

`append`多了追加部分字符串的功能。

`push_back`只能追加字符。

此外，非成员函数 `operator+` 会产生拼接后的字符串，而 `+=` 和 `append` 修改现有对象。连续拼接时可以结合实际情况预留容量，具体开销还与实现和使用方式有关。

### 赋值

`assign`和`operator=`都有赋值功能。

![image-20241014160546177](https://img.mdwind.online/md/202410141605356.png)

![image-20241014160628414](https://img.mdwind.online/md/202410141606577.png)

可以看到`assign`比`operator=`稍微多一点功能，主要是选取部分内容赋值的。

### 插入

![image-20241014160858733](https://img.mdwind.online/md/202410141608885.png)

插入位置可以用下标或迭代器指定：

```cpp
#include <iostream>
#include <string>

int main() {
    // 1. 指定下标，插入 C 风格字符串
    {
        std::string str = "Hello world";

        str.insert(6, "beautiful ");

        std::cout << str << '\n';  // Hello beautiful world
    }

    // 2. 指定下标，插入 std::string 对象
    {
        std::string str = "New York";

        str.insert(8, std::string(" City"));

        std::cout << str << '\n';  // New York City
    }

    // 3. 指定下标，插入指定数量的相同字符
    {
        std::string str = "Go";

        str.insert(2, 3, '!');

        std::cout << str << '\n';  // Go!!!
    }

    // 4. 指定下标，插入 C 风格字符串的前 n 个字符
    {
        std::string str = "The cat sleeps";

        str.insert(4, "black sheep", 6);

        std::cout << str << '\n';  // The black cat sleeps
    }

    // 5. 使用迭代器，插入指定字符区间
    {
        std::string str = "I code";
        std::string extra = "write ";

        str.insert(str.begin() + 2, extra.begin(), extra.end());

        std::cout << str << '\n';  // I write code
    }

    // 6. 使用迭代器，插入初始化列表中的字符
    {
        std::string str = "Rain";

        str.insert(str.end(), {'b', 'o', 'w'});

        std::cout << str << '\n';  // Rainbow
    }

    return 0;
}
// string 的迭代器支持加减，使用时需要保证结果处于有效范围内
```

```text
[wind@ubuntu-asus build]$ ./main-debug
Hello beautiful world
New York City
Go!!!
The black cat sleeps
I write code
Rainbow
[wind@ubuntu-asus build]$ 
```

### 删除

![image-20241014162242962](https://img.mdwind.online/md/202410141622123.png)

可以指定下标位置连续删除，也可以用迭代器单个删除。由于使用下标索引位置的重载函数有缺省值，所以不提供参数就会把字符串全删除。

### 替换

![image-20241014162647001](https://img.mdwind.online/md/202410141626174.png)

一般来说，`replace`有三个主要的参数，用于指示替换起始位置的索引，用于描述被替换字符的数目，用于描述替换的内容。

```cpp
#include <iostream>
#include <string>

int main() {
    // 1. 指定下标和替换长度，使用 C 风格字符串替换
    {
        std::string str = "Hello Mars";

        str.replace(6, 4, "World");

        std::cout << str << '\n';  // Hello World
    }

    // 2. 指定下标和替换长度，使用 std::string 对象替换
    {
        std::string str = "Good night";

        str.replace(5, 5, std::string("morning"));

        std::cout << str << '\n';  // Good morning
    }

    // 3. 指定下标和替换长度，使用指定数量的相同字符替换
    {
        std::string str = "Wait?";

        str.replace(4, 1, 3, '!');

        std::cout << str << '\n';  // Wait!!!
    }

    // 4. 指定下标和替换长度，使用 C 风格字符串的前 n 个字符替换
    {
        std::string str = "I love tea";

        str.replace(7, 3, "coffee beans", 6);

        std::cout << str << '\n';  // I love coffee
    }

    // 5. 使用迭代器区间，替换为另一个字符串的指定区间
    {
        std::string str = "red fox";
        std::string extra = "blue";

        str.replace(str.begin(), str.begin() + 3, extra.begin(), extra.end());

        std::cout << str << '\n';  // blue fox
    }

    // 6. 使用迭代器区间，替换为初始化列表中的字符
    {
        std::string str = "sunrise";

        str.replace(str.begin() + 3, str.end(), {'s', 'e', 't'});

        std::cout << str << '\n';  // sunset
    }

    return 0;
}
```

```text
[wind@ubuntu-asus build]$ ./main-debug
Hello World
Good morning
Wait!!!
I love coffee
blue fox
sunset
[wind@ubuntu-asus build]$ 
```

### 交换

如果要把某句话中的特定字符替换成其它字符串，该怎么做呢？

```cpp
// 替换空格

std::string& replaceSpaces(std::string& s, const char* c)
{
	auto p = new std::string;
	p->reserve(s.size());
	for (auto ch : s)
	{
		if (ch != ' ')
		{
			p->operator+=(ch);
		}
		else
		{
			p->operator+=(c);
		}
	}
	return *p;
}

int main()
{
	std::string s("The quick brown fox jumps over a lazy dog.");
	auto& r = replaceSpaces(s, "%#@");
	std::cout << r << std::endl;
	return 0;
}
```

![image-20241014170404304](https://img.mdwind.online/md/202410141704369.png)

但这样写有些多余，而且造成了内存泄漏，能不能直接返回对象本身呢？

```cpp
// 替换空格
std::string& replaceSpaces(std::string& s, const char* c)
{
	std::string r;
	r.reserve(s.size());
	for (auto ch : s)
	{
		if (ch != ' ')
		{
			r += ch;
		}
		else
		{
			r += c;
		}
	}
	swap(r, s);
	return s;
}

int main()
{
	std::string s("The quick brown fox jumps over a lazy dog.");
	auto& r = replaceSpaces(s, "%#@");
	std::cout << r << std::endl;
	std::cout << s << std::endl;
	return 0;
}
```

![image-20241014170950310](https://img.mdwind.online/md/202410141709424.png)

这里的`swap`可就有讲究了。

C++ 标准库还提供了通用的交换模板。

![image-20241014171353084](https://img.mdwind.online/md/202410141713273.png)

通用 `swap` 通过移动或复制对象来交换值；对于管理动态资源的类型，专门的交换操作往往可以直接交换资源的管理信息。

那么前面调用的 `swap` 是怎样工作的？先看看通用 `swap` 的说明：

![image-20241014171827908](https://img.mdwind.online/md/202410141718078.png)

标准库为不同类型提供了相应的交换操作，可以利用类型自身的特点完成交换。对于字符串，具体实现还与数据的存储方式有关。

`string` 有成员 `swap`，标准库也提供了适用于 `basic_string` 的非成员 `swap`。前面写的 `swap(r, s)` 通过实参相关查找找到适用的交换函数，最终交换两个字符串的值。下面观察一次具体实现中的交换过程：

![image-20241014173220038](https://img.mdwind.online/md/202410141732204.png)

```cpp
#include <cstdio>
#include <iostream>
#include <string>

int main() {
    std::string s1("The stars outlive their names.");  // 星辰犹在，其名已湮。
    std::string s2("Even ruins bloom again.");         // 废墟之上，仍有花开。
    std::cout << "s1本身的对象地址: " << &s1 << std::endl;
    std::cout << "s2本身的对象地址: " << &s2 << std::endl;
    printf("s1字符串的原始地址: %p\n", static_cast<const void*>(s1.c_str()));
    printf("s2字符串的原始地址: %p\n", static_cast<const void*>(s2.c_str()));
    std::cout << "====================================" << std::endl;

    s1.swap(s2);

    std::cout << "s1本身的对象地址: " << &s1 << std::endl;
    std::cout << "s2本身的对象地址: " << &s2 << std::endl;
    printf("s1字符串的原始地址: %p\n", static_cast<const void*>(s1.c_str()));
    printf("s2字符串的原始地址: %p\n", static_cast<const void*>(s2.c_str()));

    return 0;
}
```

```text
[wind@ubuntu-asus build]$ ./main-debug
s1本身的对象地址: 0x7fffa70eec20
s2本身的对象地址: 0x7fffa70eec08
s1字符串的原始地址: 0x5c4fbcbc92a0
s2字符串的原始地址: 0x5c4fbcbc92d0
====================================
s1本身的对象地址: 0x7fffa70eec20
s2本身的对象地址: 0x7fffa70eec08
s1字符串的原始地址: 0x5c4fbcbc92d0
s2字符串的原始地址: 0x5c4fbcbc92a0
[wind@ubuntu-asus build]$ 
```

对于短字符串，标准库实现还可以采用不同的存储方式： 

为了提高短字符串的存储效率，`std::string` 通常采用小字符串优化（SSO），在对象内部设置一块固定大小的缓冲区。

当字符串较短时，字符可以直接存储在这块缓冲区中，从而避免额外的堆内存分配；当字符串较长时，则使用独立的堆内存存储字符。

这种设计也影响了 `swap` 的实现。对于使用堆内存的长字符串，由于资源与对象本身相对独立，可以通过交换指针及相关管理信息完成资源交换；而对于短字符串，字符直接存放在对象内部，无法简单地通过交换指针来转移资源，因此需要交换内置缓冲区中的数据。

内置缓冲区的容量是固定的，交换其中的字符时需要处理的数据量也有上限。`string::swap` 要求常数时间复杂度。

```cpp
#include <iostream>
#include <string>

int main() {
    std::string s1 = "Kingdoms fade.";  // 王朝已逝
    std::string s2 = "Stars remain.";   // 群星依旧

    const void* p1 = s1.data();
    const void* p2 = s2.data();

    s1.swap(s2);

    std::cout << s1 << '\n';
    std::cout << s2 << '\n';

    std::cout << std::boolalpha;  // 要求以布尔形式输出
    std::cout << (s1.data() == p1) << '\n';
    std::cout << (s2.data() == p2) << '\n';
    std::cout << std::noboolalpha;  // 取消特殊格式要求

    return 0;
}
```

MSVC STL（VS 2026）的运行结果：

![](https://img.mdwind.online/img/20261102004356802.png)

LLVM libc++ 的运行结果：

```text
[wind@ubuntu-asus build]$ ./main-debug
Stars remain.
Kingdoms fade.
true
true
[wind@ubuntu-asus build]$ 
```

### 查找

![image-20241014175418328](https://img.mdwind.online/md/202410141754564.png)

查找文件后缀

```cpp
void test10()
{
	std::string s("main.cpp");
	size_t i = s.find('.');
	auto j = s.substr(i);
	std::cout << j << std::endl;
}
```

![image-20241014180318988](https://img.mdwind.online/md/202410141803118.png)

不过这样写还不行，因为有些文件名不止一个点。

```shell
[wind@ubuntu-asus build]$ ls -al ~/Boost/
total 200556
drwxrwxr-x  3 wind wind      4096 11月  4  2025 .
drwxr-x--- 34 wind wind      4096 11月  1 16:34 ..
drwxr-xr-x 10 wind wind      4096 11月  4  2025 boost-1.89.0
-rw-rw-r--  1 wind wind 134857488 11月  4  2025 boost-1.89.0-cmake.tar_2.gz
-rw-rw-r--  1 wind wind  70491419 11月  4  2025 boost-package-1.89.0.tar.gz
[wind@ubuntu-asus build]$ 
```

`.tar` 表示归档，`.gz` 表示压缩。如果要取最后一段扩展名 `.gz`，可以用 `rfind` 从后往前查找点；如果要识别复合扩展名，则可以把 `.tar.gz` 一起作为后缀处理。

![](https://img.mdwind.online/img/20261102005816827.png)

下面通过一个固定格式的网址练习查找和截取：`https://legacy.cplusplus.com/reference/string/string/find/` 中，`https` 是协议名，`legacy.cplusplus.com` 是域名，后面的部分是资源路径。

```cpp
#include <iostream>
#include <string>

int main() {
    std::string url("https://legacy.cplusplus.com/reference/string/string/find/");
    // 本例按“协议://域名/路径”的格式拆分
    size_t schemeEnd = url.find("://");
    if (schemeEnd == std::string::npos) {
        std::cerr << "网址缺少协议分隔符" << std::endl;
        return 1;
    }

    size_t hostBegin = schemeEnd + 3;
    size_t pathBegin = url.find('/', hostBegin);
    if (pathBegin == std::string::npos) {
        std::cerr << "网址缺少资源路径" << std::endl;
        return 1;
    }

    auto scheme = url.substr(0, schemeEnd);
    auto hostname = url.substr(hostBegin, pathBegin - hostBegin);
    auto path = url.substr(pathBegin + 1);
    std::cout << "协议种类: " << scheme << std::endl;
    std::cout << "域名: " << hostname << std::endl;
    std::cout << "资源路径: " << path << std::endl;

    return 0;
}
```

运行结果：

![](https://img.mdwind.online/img/20261102012307010.png)

------------------

`find_first_of`和`find_last_of`

这是文档给的示例代码：

```cpp
#include <cstddef>  
void test12()
{
	
	std::string str("Please, replace the vowels in this sentence by asterisks.");
	std::size_t found = str.find_first_of("aeiou");
	while (found != std::string::npos)
	{
		str[found] = '*';
		found = str.find_first_of("aeiou", found + 1);
	}
	std::cout << str << '\n';
}
```

![image-20241014194528323](https://img.mdwind.online/md/202410141945451.png)

它找的不是第一个参数那个字符串，而是第一个参数里出现的所有字符，可以指定查找的起始位置。

`find_first_of`是从前往后找，`find_last_of`是从后往前找。

`not`是找补集，找没有出现在第一个参数的

![image-20241014200619394](https://img.mdwind.online/md/202410142006014.png)

### getline

使用 `operator>>` 提取字符串时，流会跳过前导空白，并在接下来的空白处停止。

![image-20241014205544600](https://img.mdwind.online/md/202410142055254.png)

在上述的代码中，我们输入了"hello world"，流提取操作将这两个单词间的空格视为了分隔符，于是`s`只提取到了`hello`，而`world`仍旧处于缓冲区中。

这对多个对象的流提取无疑是有益的，但若是想把包括空格的一句话提取到一个对象中，这种机制就有问题了。

![image-20241014205911517](https://img.mdwind.online/md/202410142059444.png)

为此，我们有了`getline`，`getline`有两个版本：

```cpp
istream& getline (istream& is, string& str, char delim);
istream& getline (istream& is, string& str);
```

第一个版本中的第三个参数`delim`描述了遇到什么字符才会停止提取，第二个版本默认以换行符为分隔符，提取该行内容；分隔符本身会被取走，但不会写入字符串。

![image-20241014210659512](https://img.mdwind.online/md/202410142107482.png)
