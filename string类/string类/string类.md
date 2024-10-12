# string类

## 前言

虽然我们刚从STL简介中过来，但需要注意的是，`string` 并不是 STL 的一部分。`string` 类在 STL之前就已诞生，由 C++ 标准委员会编写。从 STL 的角度来看，`string` 应归类于容器部分，因为它是用于承载字符和字符串的数据结构。然而，由于 `string` 的风格与 STL 非常相似，因此在正式学习 STL 之前，我们先来学习 `string` 类。

## [STL的文档主界面](https://legacy.cplusplus.com/reference/string/string/)

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
- swap：真 - 内容交换函数，`Exchanges the values of two strings (function )`
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

# 完