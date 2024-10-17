# string类

## 前言

虽然我们刚从STL简介中过来，但需要注意的是，`string` 并不是 STL 的一部分。`string` 类在 STL之前就已诞生，由 C++ 标准委员会编写。从 STL 的角度来看，`string` 应归类于容器部分，因为它是用于承载字符和字符串的数据结构。然而，由于 `string` 的风格与 STL 非常相似，因此在正式学习 STL 之前，我们先来学习 `string` 类。

## [string的文档主界面](https://legacy.cplusplus.com/reference/string/string/)

![image-20241012090353846](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410120903961.png)

文档刚开头，就描述了`string`是一个类`class`，位于`std`命名域中，它实际是由模版`basic_string`以`<char>`的形式实例化出的。

之后是简要概述。`string`是一个对象【Strings are objects】，是一个什么样的对象，是用来表示【represent】某种有序集合【sequences】的对象，这种有序集合的组成元素是什么？是字符【of characters】。

类`string`是C++标准的一部分【The standard `string` class】,它用来提供【provides】某种支持或者说接口【support】。以`string`类实例化出的对象【such objects】，与C++标准中【standard】的用以承载字节数据【bytes】的容器【container】的接口【interface】十分相似【similar】，除此之外【but】，它还具有一些额外的【adding】特性【features】，（我们）对该类进行了针对性地设计【specifically designed】，使得它也可以处理【operate】只有单个字符【single-byte characters】的字符串【strings】。

字符串类【class string】是基本字符串类模版【basic_string】的一个实例化【instantiation】，使用【char】作为它的字符类型【its character type】，你可以使用字符特性模版【char_traits】和空间配置器【allocator types】来对基本字符串类模版【basic_string】进行更多的实例化，以适应不同国家和地区的字符语言需求，详情请参考基本字符串类模版【see basic_string for more info on the template】。

注意【Note】，这个类是独立于【independently】字符编码格式【encoding used】处理【handles】字符的，或者说，它是以字节【bytes】为单位处理字符的，这意味着，如果你使用多字节字符【multi-byte】或可变长度字符【variable-length characters 】，例如UTF-8【such as UTF-8】，它的所有成员函数【all members of this class】例如`length`或`size`【such as length or size】，亦或者它的迭代器【as well as its iterators】，仍旧【still】以单个字节【terms of bytes】进行操作【operate】，而不是实际【actual】编码格式【encoded characters】（中的单个字符）。

------------------

成员类型【Member types】（列表）

- value_type：用于定义该数据结构或者容器容纳的数据类型，`string`是`basic_string`关于`char`的实例化，此处为char
- traits_type：用于定义容纳成员的特性，例如比较，复制，查找等操作，为成员的处理提供最基本的支持，此处为`char_traits`关于`char`的实例化
- allocator_type：用于提供内存分配和管理的方法，此处为`allocator`关于`char`的实例化
- reference：引用，此处为`char&`
- const_reference：常引用，此处为`const char&`
- pointer：指针，此处为`char*`
- const_pointer：常指针，此处为`const char*`
- iterator：用于定义容器中元素的遍历方式，此处为指向字符的【to char】随机访问迭代器【random access iterator】，也可转换成【convertible to】常量迭代器【const_iterator】
- const_iterator：常量迭代器，此处为`a random access iterator to const char`
- reverse_iterator：反向迭代器，用于倒着遍历元素，此处为`reverse_iterator<iterator>`
- const_reverse_iterator：常量反向迭代器，此处为`reverse_iterator<const_iterator>`
- difference_type：用于定义两个迭代器间的相对距离，此处为`ptrdiff_t`
- size_type：用于定义有效成员的个数，此处为`size_t`

----------------------

成员函数【Member functions】（列表）

默认函数：

- constructor：构造函数，`Construct string object (public member function )`
- destructor：析构函数，`String destructor (public member function )`
- operator=：赋值运算符重载，`String assignment (public member function )`

迭代器【Iterators】:

- begin：用于返回指向成员开头的迭代器，`Return iterator to beginning (public member function )`
- end：用于返回指向有效成员末尾的下一个字符的迭代器，`Return iterator to end (public member function )`
- rbegin：反向迭代器，返回一个指向反向开头位置的迭代器，`Return reverse iterator to reverse beginning (public member function )`
- rend：用于返回一个指向反向结尾的迭代器，`Return reverse iterator to reverse end (public member function )`
- cbegin(C++11后支持)：返回指向成员开头的常量迭代器，`Return const_iterator to beginning (public member function )`
- cend(C++11后支持)：返回指向有效成员结尾的下一字符的常量迭代器，`Return const_iterator to end (public member function )`
- crbegin(C++11后支持)：返回指向反向开头的常量迭代器，`Return const_reverse_iterator to reverse beginning (public member function )`
- crend(C++11后支持)：返回指向反向结尾的常量迭代器，`Return const_reverse_iterator to reverse end (public member function )`

容量【Capacity】：

- size：返回容器中有效元素的个数，`Return length of string (public member function )`
- length：返回字符串中的有效字符个数，和`size`功能实际相同，这是由于`string`写在`STL`之前，后续为了适配`STL`的风格，又写了`size`。`Return length of string (public member function )`
- max_size：用于返回当前平台理论上能开辟的最大的空间，不考虑当前平台的内存情况，因此饱受诟病，`Return maximum size of string (public member function )`
- resize：用于根据需要调整容量的大小，`Resize string (public member function )`
- capacity：返回当前开辟的空间大小，`Return size of allocated storage (public member function )`
- reserve：用于提前扩展容量的大小，避免频繁扩展降低效率，`Request a change in capacity (public member function )`
- clear：用于清空容量中的成员，以承接其它成员，`Clear string (public member function )`
- empty：判断容器是否为空，`Test if string is empty (public member function )`
- shrink_to_fit：调整容量，使其刚好能放下字符串中的所有字符，`Shrink to fit (public member function )`

元素访问【Element access】:

- operator[]：重载`[]`，使得字符串可以以数组的形式管理，`Get character of string (public member function )`
- at：同样是使字符串可以以数组的形式管理，但相比`[]`，增加了范围检查，防止越界访问，`Get character in string (public member function )`
- back(C++11后支持)：引用最后一个有效的字符，`Access last character (public member function )`
- front(C++11后支持)：引用第一个有效的字符，`Access first character (public member function )`

修饰符【Modifiers】：

- operator+=：重载`+=`，用于追加字符或字符串，会自动调整内存`Append to string (public member function )`
- append：和`+=`重载功能相同，只是形式上不同，`Append to string (public member function )`
- push_back：用于追加单个字符，`Append character to string (public member function )`
- assign：和`=`重载功能相同，只是形式不同，`Assign content to string (public member function )`
- insert：为当前字符串插入新的内容，`Insert into string (public member function )`
- erase：在字符串中删除指定字符，`Erase characters from string (public member function )`
- replace：替换字符串中的某处内容，`Replace portion of string (public member function )`
- swap：通过索引，比如指针，交换两个容器中的内容，不是真交换`Swap string values (public member function )`
- pop_back(C++11后支持)：删除字符串的最后一个有效字符，`Delete last character (public member function )`

字符串操作【String operations】：

- c_str：返回一个常字符类型指针，通常用于兼容某些C接口，`Get C string equivalent (public member function )`
- data：和`c_str`一样，还是历史遗留问题，最开始只有`data`，后来为了向STL风格靠拢，又写了`c_str`，`Get string data (public member function )`
- get_allocator：返回一个空间配置器，`Get allocator (public member function )`
- copy：将字符串的一部分拷贝到另一个容器里`Copy sequence of characters from string (public member function )`
- find：用于搜索字符串中的特定字符或字符串，`Find content in string (public member function )`
- rfind：从字符串的最后一个有效字符开始搜索特定字符或字符串，`Find last occurrence of content in string (public member function )`
- find_first_of：依据指定的，由目标字符构成的集合，在字符串里找第一个处于该集合的字符，`Find character in string (public member function )`
- find_last_of：依据指定的，由目标字符构成的集合，在字符串里找最后一个处于该集合的字符，`Find character in string from the end (public member function )`
- find_first_not_of：依据指定的，由目标字符构成的集合的补集，在字符串里找第一个处于该集合的字符，`Find absence of character in string (public member function )`
- find_last_not_of：依据指定的，由目标字符构成的集合的补集，在字符串里找最后一个处于该集合的字符，`Find non-matching character in string from the end (public member function )`
- substr：把字符串的一部分，复制，包装成新的对象返回，`Generate substring (public member function )`
- compate：比较两个字符串的大小，`Compare strings (public member function )`

-------------------------

成员常量【Member constants】

- npos：`size_t`类型的`-1`，但`size_t`是无符号的，所以会被识别为`size_t`的最大值

--------------

非成员函数【Non-member function overloads】：

- operator+：重载`+`，返回一个新的字符串，`Concatenate strings (function )`
- relational operators：关系运算符重载，例如`>=`,`==`,`<=`等，`Relational operators for string (function )`
- swap：并非swap模版的实例化，实际是复用成员swap`Exchanges the values of two strings (function )`
- operator>>：流提取重载函数，`Extract string from stream (function )`
- operator<<：流插入重载函数，`Insert string into stream (function )`
- getline：从标准输入流中读取整行数据，`Get line from stream into string (function )`

## 使用

### 对象实例化

在`constructor`中可以看到该类的实例化方式。

![image-20241012165510456](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410121655654.png)

```cpp
void test1()
{
	// 以无参的形式实例化
	std::string s1;
	// 以常量字符串的形式实例化
	std::string s2("string");

	// 容量不够会自己扩容

	// 支持流插入
	std::cout << s2 << std::endl;
	// 支持流提取
	std::cin >> s1;
	std::cout << s1 << std::endl;
}
```

![image-20241012170616516](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410121706589.png)

### 字符串拼接

![image-20241012170918517](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410121709659.png)

```cpp
void test2()
{
	std::string s1("class");
	std::string s2(" string");
	std::string s3 = s1 + s2;
	std::cout << s3 << std::endl;
	std::cout << "std::" + s3 << std::endl;
}
```

![image-20241012171435552](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410121714636.png)

### 字符串遍历

```cpp
void test3()
{
	std::string s1("abcd");
	std::string s2("-----------------");

	// 使用`[]`重载遍历字符串
	int i = 0;
	for (; i < s1.size(); i++)
	{
		++s1[i];
	}
	std::cout << s1 << std::endl;
	// 注意，`[]`没有范围检查，可能会越界访问
	// 可以用成员函数`at`替代
	for (i = 0; i < s1.size(); i++)
	{
		--s1.at(i);
	}

	std::cout << s2 << std::endl;
	// 使用迭代器遍历字符串
	// 迭代器是对容器中元素遍历的通用方案
	std::string::iterator it = s1.begin();
	while (it != s1.end())
	{
		std::cout<<*it;
		++it;
	}
	// begin返回指向第一个有效字符的迭代器
	// end返回指向最后一个有效字符的下一字符的迭代器
	// s1存储的是"abcd\0",一共五个字符，最后一个有效字符是'd'
	// 即，end返回的迭代器指向'\0'
	// 迭代器行为很像指针，甚至它本身就是指针
	std::cout << std::endl;
	// 注意，循环条件不要用`<`比较
	// 因为迭代器是通用的，而某些容器中的成员没有先后概念
	// 比如树状结构，环装结构，但对于这些容器成员来说，是否等于的
	// 概念仍是确定的
	std::cout << s2 << std::endl;
	// 除此之外，还有反向迭代器
	// rbegin返回一个反向的迭代器，具体指向字符串的最后一个有效字符
	// rend返回一个指向第一个有效字符前一字符的迭代器
	// “第一个有效字符前一字符”只是一个概念上的位置，实际并不存在
	std::string::reverse_iterator rit = s1.rbegin();
	while (rit != s1.rend())
	{
		std::cout << *rit;
		++rit;
	}
	std::cout << std::endl << s2 << std::endl;
	// 迭代器的++都是重载过的，表示方向，朝终止位`end`迭代
	// 对反向迭代器仍是如此，++表示朝终止位`rend`迭代
	// 迭代器也有--重载，不过用的人不多

	// 范围for其实是对迭代器的进一步封装
	// 由于迭代器的类型挺长的，所以直接用auto占位
	for (auto ch : s1)
	{
		std::cout << ch;
	}
	std::cout << std::endl;
	// 修改用引用
	for (auto& ch : s1)
	{
		++ch;
	}
	std::cout << s1 << std::endl;
}
```

### 常迭代器

为了适应常对象，begin和end或者rbegin和rend都有两个重载版本，一个是普通对象，一个常对象

![image-20241012195442259](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410121954516.png)

![image-20241012195511649](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410121955819.png)

C++11后，又添加了`cbegin  cend   crbegin  crend`，它们没重载版本，就是专门用于常对象的。

### npos

在上面的文档中我们看到一个被特别标注的值：npos

![image-20241012200348416](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410122003574.png)

`static const size_t npos = -1;`

`-1`的补码是全1，size_t是无符号的，原码和补码相同，所以此处的`npos`其实就是`size_t`的最大值，`size_t`在32位平台是32位的，大概是4G，很大，动态开辟都不一定能开辟出来，有什么用呢？

在构造函数里，提供了一个实例化方案，可以用字符串的一部分实例化出另一个字符串

`string (const string& str, size_t pos, size_t len = npos);`根据文档描述，我们知道，这一部分是从`pos`开始，从`len`结束的，当`len`比`obj.size()`还大时，只会取到`obj.size()`这一位。而`len`有个缺省值`npos`，所以不写第三个参数实际上就会把剩下的部分全都取用。

### 容量

```cpp
void test4()
{
	std::string s;
	std::cout << "initial capacity:";
	size_t old = s.capacity();
	std::cout << old << std::endl;
	int cir = 0;
	for (; cir < 100; cir++)
	{
		s.push_back('c');
		size_t n = s.capacity();
		if (n != old)
		{
			std::cout << "trigger expansion,The new capacity is:";
			std::cout << n << std::endl;
			old = n;
		}
	}
}

int main()
{
	test4();
	return 0;
}
```

VS2022的运行结果为：

![image-20241014133109574](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410141331751.png)

g++的运行结果是：

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

我们看到SGI版本的string是很规规矩矩地二倍扩容的，P.J.版本的string就有自己的一套，C++标准没有规定扩容机制，所以各个编译器厂商有自己的逻辑。除此之外，我们还可以看出，最起码SGI版本的容量参数是不包括`\0`的，最开始的容量就是0，它的容量参数就是可容纳有效字符的个数。

---------------------------

让我们来看看`reserve`，为了避免多次扩容而导致的效率低下，可以先预估字符串的大小，一次性提前开辟。

```cpp
void test4()
{
	std::string s;
	s.reserve(100);
	std::cout << "initial capacity:";
	size_t old = s.capacity();
	std::cout << old << std::endl;
	int cir = 0;
	for (; cir < 100; cir++)
	{
		s.push_back('c');
		size_t n = s.capacity();
		if (n != old)
		{
			std::cout << "trigger expansion,The new capacity is:";
			std::cout << n << std::endl;
			old = n;
		}
	}
}

int main()
{
	test4();
	return 0;
}
```

![image-20241014141338203](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410141413311.png)

我们可以看到，微软还是有自己的逻辑，它可能出于内存对齐的考虑，不是直接扩容到100的，而是比100多。

g++还是一如既往的规整：

```shell
[wind@starry-sky SGI版本string]$ vim main.cpp
[wind@starry-sky SGI版本string]$ make
[wind@starry-sky SGI版本string]$ ./out
initial capacity:100
[wind@starry-sky SGI版本string]$
```

`reserve`能不能缩容呢？文档的描述是："In all other cases, it is taken as a non-binding request to shrink the string capacity: the container implementation is free to optimize otherwise and leave the string with a capacity greater than *n*."

“non-binding request”（非约束性请求）是什么意思，它的意思是对于缩小容量的请求（也就是参数设置地比现在容量小），系统可以出于自己的策略灵活响应，这个请求不具有强制性。

对于上文的其它情况，也就是缩小字符串的容量，将被视为一种非约束请求：容器的具体实现可以出于优化的考虑，自由地做出其它选择，使得字符串的容量依旧比参数n大。

```cpp
void test4()
{
	std::string s;
	s.reserve(100);
	std::cout << "initial capacity:";
	size_t old = s.capacity();
	std::cout << old << std::endl;
	int cir = 0;
	for (; cir < 100; cir++)
	{
		s.push_back('c');
		size_t n = s.capacity();
		if (n != old)
		{
			std::cout << "trigger expansion,The new capacity is:";
			std::cout << n << std::endl;
			old = n;
		}
	}
	s.reserve(10);
	std::cout << "Current capacity:" << s.capacity() << std::endl;
}
```

![image-20241014144657536](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410141446640.png)

我们看到，VS直接无视了请求。

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

![image-20241014151801601](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410141518423.png)

![image-20241014151833674](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410141518452.png)

![image-20241014151901361](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410141519537.png)

![image-20241014152114545](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410141521250.png)

接下来是删除

![image-20241014152352323](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410141523107.png)

### 元素访问

`at`和`operator[]`对于越界的处理。

`operator[]`的越界逻辑：

![image-20241014154334129](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410141543268.png)

未定义的行为，也不知道会发生什么。

`at`的越界逻辑：

![image-20241014154612100](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410141546258.png)

如果越界，会抛出异常。

### 追加

`append`比`operator+=`多了一些功能：

![image-20241014155201886](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410141552045.png)

`operator+=`的参数可以是其他对象，另一个字符串，字符。

![image-20241014155358942](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410141553101.png)

`append`多了追加部分字符串的功能。

`push_back`只能追加字符。

除此之外，还有一个类外函数`operator+`，很明显，为了不改变对象，它需要多次拷贝构造，所以效率可以预料到比较低。

### 赋值

`assign`和`operator=`都有赋值功能。

![image-20241014160546177](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410141605356.png)

![image-20241014160628414](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410141606577.png)

可以看到`assign`比`operator=`稍微多一点功能，主要是选取部分内容赋值的。

### 插入

![image-20241014160858733](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410141608885.png)

头插，使用下标或者迭代器

```cpp
void test6()
{
	std::string s("hello world");
	s.insert(0, 1, 'x');
	std::cout << s << std::endl;
	s.insert(s.begin(), 'x');
	std::cout << s << std::endl;
}
```

![image-20241014161608900](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410141616987.png)

使用下标指定时，还必须再加一个参数，用来表示插入次。

### 删除

![image-20241014162242962](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410141622123.png)

可以指定下标位置连续删除，也可以用迭代器单个删除。由于使用下标索引位置的重载函数有缺省值，所以不提供参数就会把字符串全删除。

### 替换

![image-20241014162647001](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410141626174.png)

一般来说，`replace`有三个主要的参数，用于指示替换起始位置的索引，用于描述被替换字符的数目，用于描述替换的内容。

```cpp
void test7()
{
	std::string s1("hello world");
	// 把空格【下标为5】的那一个字符替换成%?
	s1.replace(5, 1, "%?");
	std::cout << s1 << std::endl;
	// 此时很明显有数据挪动
	// 如果第二个参数就是第三个参数的有效字符个数
	// 那就只是单纯平替，没有挪动数据
	std::string s2("hello world");
	s2.replace(5, 2, "%x");
	std::cout << s2 << std::endl;
}
```

![image-20241014164133303](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410141641407.png)

### 交换

如果要把某句话中的特定字符替换成其它字符串，该怎么做呢？

```cpp
// 替换空格
std::string& test8(std::string& s, const char* c)
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
	auto r = test8(s, "%#@");
	std::cout << r << std::endl;
	return 0;
}
```

![image-20241014170404304](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410141704369.png)

但这样写有些多余，而且容易内存泄漏，能不能直接返回对象本身呢？

```cpp
// 替换空格
std::string& test8(std::string& s, const char* c)
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
	auto r = test8(s, "%#@");
	std::cout << r << std::endl;
	std::cout << s << std::endl;
	return 0;
}
```

![image-20241014170950310](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410141709424.png)

这里的`swap`可就有讲究了。

我们知道，在C++中，有个通用交换模版。

![image-20241014171353084](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410141713273.png)

光就这模版来说，swap要深拷贝，所以对于容器来说，这种交换往往会非常低效。

那我们上面调的是这个`swap`吗？我们看看模版`swap`的说明：

![image-20241014171827908](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410141718078.png)

第一段话说明了模版`swap`非常不适合容器的交换。第二段则说，对于所有特定的容器，`swap`都已经特定化地实现了，使得它们只交换少量指针，而不是真正地交换内容。

我们看到`string`文档里，有两个`swap`，一个是成员函数，另一个是非成员函数，它们都不是实际内容的交换。而之前我们也说过，对于已经实现的函数，编译器不会再实例化出一个模版函数，所以我们上面调的就是`string`文档里的非成员函数`swap`，而不是由`swap`通用模版实例化出的模版函数。

![image-20241014173220038](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410141732204.png)

```cpp
void test9()
{
	std::string s1("hello worldtyuggvghgvvhvbghg");
	std::string s2("hello linuxhgvvhyubgjhbjhkjij");
	std::cout << &s1 << std::endl;
	std::cout << &s2 << std::endl;
	printf("%p\n", s1.c_str());
	printf("%p\n", s2.c_str());
	std::cout << "================" << std::endl;
	s1.swap(s2);
	std::cout << &s1 << std::endl;
	std::cout << &s2 << std::endl;
	printf("%p\n", s1.c_str());
	printf("%p\n", s2.c_str());
}
```

![image-20241017081426134](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410170814321.png)

注意，VS的某些较高版本对交换逻辑进行了特殊优化。实际上，VS会动态分析深拷贝交换和索引交换的优劣，当字符串长度较短时，深拷贝交换代价将小于索引交换代价，此时VS会进行真正的值交换。比如下面的代码：

```cpp
void test9()
{
	std::string s1("hello world");
	std::string s2("hello linux");
	std::cout << &s1 << std::endl;
	std::cout << &s2 << std::endl;
	printf("%p\n", s1.c_str());
	printf("%p\n", s2.c_str());
	std::cout << "================" << std::endl;
	s1.swap(s2);
	std::cout << &s1 << std::endl;
	std::cout << &s2 << std::endl;
	printf("%p\n", s1.c_str());
	printf("%p\n", s2.c_str());
}
```

![image-20241017081833884](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410170818003.png)

### 查找

![image-20241014175418328](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410141754564.png)

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

![image-20241014180318988](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410141803118.png)

不过这样写还不行，因为有些文件名不止一个点。

```shell
[wind@starry-sky ~]$ sudo ls /root
[sudo] password for wind: 
one  wind_backup.tar.gz
[wind@starry-sky ~]$
```

`wind_backup.tar.gz`是我这个账号的备份，因为不久之前，我这个账号不知道怎么回事，有些配置出问题了，然后就注销了这个用户，现在这个是新创建了，于是就把这个新账号整个备份了一个。

`.tar`是打包，`.gz`是压缩，真正的后缀是`.gz`，这时，就要用`rfind`了，它是倒着找的，不是从前往后找的。

![image-20241014181502306](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410141815141.png)

网址分类：协议，域名，资源名。比如`https://cplusplus.com/reference/string/string/find/`，其中`https`是协议，`cplusplus.com`是域名，`reference/string/string/find/`是资源名。

```cpp
void test11()
{
	std::string s("https://cplusplus.com/reference/string/string/find/");
	size_t n = s.find(':');
	if (n != std::string::npos)
	{
		auto i = s.substr(0, n);
		std::cout << i << std::endl;
	}
	else
	{
		std::cout << "URL error!" << std::endl;
	}
	// 第二个参数规定了查找的起始位置，缺省值为0
	size_t m = s.find('/', n + 3);
	if (m != std::string::npos)
	{
		auto j = s.substr(n + 3, m - (n + 3));
		std::cout << j << std::endl;
	}
	else
	{
		std::cout << "URL error!" << std::endl;
	}
	n = s.find('/', m + 1);
	if (n != std::string::npos)
	{
		auto k = s.substr(m + 1);
		std::cout << k << std::endl;
	}
	else
	{
		std::cout << "URL error!" << std::endl;
	}
}
```

![image-20241014193442128](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410141934278.png)

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

![image-20241014194528323](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410141945451.png)

它找的不是第一个参数那个字符串，而是第一个参数里出现的所有字符，可以指定查找的起始位置。

`find_first_of`是从前往后找，`find_last_of`是从后往前找。

`not`是找补集，找没有出现在第一个参数的

![image-20241014200619394](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410142006014.png)

### getline

为了对多个对象进行流提取，C++在默认情况下会把输入的信息以空格或者换行作为分隔符。

![image-20241014205544600](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410142055254.png)

在上述的代码中，我们输入了"hello world"，编译器将这两个单词间的空格视为了分隔符，于是`s`只提取到了`hello`，而`world`仍旧处于缓冲区中。

这对多个对象的流提取无疑是有益的，但若是想把包括空格的一句话提取到一个对象中，这种机制就有问题了。

![image-20241014205911517](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410142059444.png)

为此，我们有了`getline`，`getline`有两个版本：

```cpp
istream& getline (istream& is, string& str, char delim);
istream& getline (istream& is, string& str);
```

第一个版本中的第三个参数`delim`描述了遇到什么字符才会停止提取，第二个版本则会把整行内容全部提取。

![image-20241014210659512](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410142107482.png)



# 完