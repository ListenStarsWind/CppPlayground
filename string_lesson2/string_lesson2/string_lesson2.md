# string_课时2

## 模版之问

我们知道标准库中的`string`实际是`basic_string`模版类关于`char`的实例化。而在《string》,也就是上篇文章里，官方文档其实已经说了`string`为模版的原因：

![image-20241017170223725](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410171702925.png)

一句话来说，这是为了让C++国际化，可以让不同国家和地区的字符语言需求都得到满足。本片文章的主要内容是实现一个基本的`string`类，但我们不会采用模版的方式，因为这涉及到一些我们还未学习的内容，再加上我们文档已经说了，对于多字节字符以及变长字符`string`都可以使用，所以我们就直接用`char`类型了，等以后对C++的学习更上一层楼后再回来真正地实现。

下面我们稍微过一过字符的主要编码模式：

当今计算机都是二进制的，为了让字符与二进制序列建立映射关系，就出现了ASCII码。ASCII码只有一个字节，它对于英语等拉丁字母语言差不多够用，但其它语言就不太够用了，所以就有人研究出了`Unicode`，其中最常用的就是`UTF-8`:

![image-20241017172651572](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410171726630.png)

如图所见`UTF-8`是一种变长编码，它的具体字节数并不确定，有一字节，两字节，三字节，四字节这四种。不过对于常用的汉字来说基本都在两字节。`UTF-8`的变长属性，可以使得它以更少的字节存储字符，但它的变长属性也使得它比较复杂，不易管理。不过它仍然是适用范围最广的编码格式。

为了让编码格式更适应于以汉字为基础的东亚文字字符系统，中国信息化技术标准委员会以`UTF-8`为基础，推出了`GBK`系列编码格式，以下为百度百科的相关描述：

![image-20241017182940363](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410171829406.png)

`Windows`系统主要是以GBK系列编码格式进行汉化的，微软的其它产品，例如VS，office他们的汉化也都主要用GBK系列。`Linux`系统则更喜欢使用`UTF-8`。

## 基本实现

我们的`string`其实就四个成员：字符串空间的索引指针，有效字符个数，可容纳个数，静态成员`npos`。不过我们先只写前三个成员，后续会用`npos`引出一些C++特别语法。

```cpp
namespace wind
{
	class string
	{
	public:
		
	private:
		char* _str;
		size_t _size;
		size_t _capacity;
	};
}
```

### string(const char* str)

我们在先前说过，对于构造函数来说，应尽可能使用初始化列表进行初始化，除此之外，我们还说了初始化列表的初始化顺序是依照声明顺序，而不是初始化列表顺序，这意味着，写初始化列表要以声明顺序来写，防止因顺序问题出现错误。

```cpp
wind::string::string(const char* str)
	:_str(nullptr)
	,_size(strlen(str))
	,_capacity(_size)
{
	// 注意，_capacity指的是可以容纳的有效字符个数
	// 它与开辟空间的大小不是同一概念
	// 为了兼容C语言，开辟空间的最后一个字符必须是'\0'
	// 而char* str身为C中的字符串最后一位就是'\0'
	// 所以_capacity的初始化是就是char* str的长度

	_str = new char[_capacity + 1];
	// 留一个成员空间，用来放`\0`

	strcpy(_str, str);
	// 严格来说，应该用memcpy，但既然确定
	// 不使用模版而使用char来写
	// 那就用C中的字符串相关函数
}

/*
// 因为初始化列表的初始化顺序是按照声明来写的
// 所以会先执行_str(new char[_capacity + 1])
// 但此时_size还未被定义
// 从而引发错误
wind::string::string(const char* str)
	:_size(strlen(str))
	,_capacity(_size + 1)
	,_str(new char[_capacity + 1])
{
	// 略
}
*/
```

### ~string()

```cpp
// 这真的没什么好说的
wind::string::~string()
{
	delete[] _str;
	_str = nullptr;
	_size = _capacity = 0;
}
```

### string()

```cpp
wind::string::string()
	:_str(new char[1] {0})
	,_size(0)
	,_capacity(0)
{
	// C语言规定字符串的最后一位是'\0'
	// 这对空字符串仍然使用，所以要再
	// 开辟一个成员空间存放'\0'
	
	// 前面说过，我们的STL是SGI版本的
	// 之前我们试过，P.J.版本的string
	// 无参构造是会开辟多个空间的
	// 很明显打印P.J.版本的空string
	// 对象是不会打印出任何东西的
	// 所以个人猜测P.J.版本的空string
	// 对象最起码开头也要上道保险性质的'\0'
	// 防止打印出其它内容
}
```

可以把`string(const char* str)`和`string()`使用缺省值进行合并，`string(const char* str = "")`，由于C语言规定常量字符串必须以`\0`结尾，所以空字符串`""`其实并不完全空，后面还有一个`\0`，但这里就不合并了，因为合并之后会让文章逻辑不够顺畅。而且我还要重新排版。

### size_t size()const

```cpp
size_t wind::string::size()const
{
	return _size;
}
```

### size_t capacity()const

```cpp
size_t wind::string::capacity()const
{
	return _capacity;
}
```

### operator[]

```cpp
char& wind::string::operator[](size_t pos)
{
	assert(pos < _size);
	return _str[pos];
}

const char& wind::string::operator[](size_t pos)const
{
	assert(pos < _size);
	return _str[pos];
}
```

### iterator

```cpp
namespace wind
{
	class string
	{
	public:
		typedef char* iterator;
		typedef const char* const_iterator;
		iterator begin();
		iterator end();
		const_iterator begin()const;
		const_iterator end()const;
		string(const char* str);
		string();
		~string();
		char& operator[](size_t pos);
		const char& operator[](size_t pos)const;
		size_t size()const;
		size_t capacity()const;
	private:
		char* _str;
		size_t _size;
		size_t _capacity;
	};
}

wind::string::iterator wind::string::begin()
{
	return _str;
}

wind::string::iterator wind::string::end()
{
	return _str + _size;
}

wind::string::const_iterator wind::string::begin()const
{
	return _str;
}

wind::string::const_iterator wind::string::end()const
{
	return _str + _size;
}
```

### reserve

```cpp
void wind::string::reserve(size_t n)
{
	// 以前试过的，对于小于当前容量的参数
	// SGI和P.J.函数都不作处理
	if (n > _capacity)
	{
		// 注意，_capacity指的是可容纳的有效数据个数
		// 不是开辟空间的成员个数，要额外加一存'\0'

		// C++没原地扩容
		// 所以就new出来一个新空间
		// 然后再从原空间里拷贝内容

		auto p = new char[n + 1];
		strcpy(p, _str);
		delete[] _str;
		_str = p;
		_capacity = n;
	}
}
```

### push_back

```cpp
void wind::string::push_back(const char ch)
{
	if (_size == _capacity)
	{
		reserve(_capacity * 2);
	}
	_str[_size++] = ch;
	_str[_size] = '\0';
}
```

### append

```cpp
void wind::string::push_back(const char ch)
{
	if (_size == _capacity)
	{
		// 为了防止_capacity初始值为0
		if (_capacity == 0)
		{
			reserve(1);
		}
		else
		{
			reserve(_capacity * 2);
		}
	}
	_str[_size++] = ch;
	_str[_size] = '\0';
}
```

### operator+=

```cpp
wind::string& wind::string::operator+=(const char ch)
{
	this->push_back(ch);
	return *this;
}

wind::string& wind::string::operator+=(const char* str)
{
	this->append(str);
	return *this;
}
```

### npos

这是第四个成员变量，它是一个静态无符号整型变量。我们前面说过，静态成员变量是类共用的，所以不会定义在初始化列表中，因此声明中不能给缺省值，理论上应该都定义在声明外，就像这样：

```cpp
// .h
namespace wind
{
	class string
	{
	public:
		typedef char* iterator;
		typedef const char* const_iterator;
		iterator begin();
		iterator end();
		const_iterator cbegin()const;
		const_iterator cend()const;
		string(const char* str);
		string();
		~string();
		void reserve(size_t n);
		char& operator[](size_t pos);
		string& operator+=(const char ch);
		string& operator+=(const char* str);
		const char& operator[](size_t pos)const;
		void push_back(const char ch);
		void append(const char* str);
		size_t size()const;
		size_t capacity()const;
		string& insert(size_t pos, const char* str);
		string& insert(size_t pos, const string& s);
		string& erase(size_t pos = 0, size_t len = npos);
	private:
		char* _str;
		size_t _size;
		size_t _capacity;
		const static size_t npos = -1;
	};
}


// .cpp
const size_t wind::string::npos = -1;
```

但C++标准委员会对静态整型成员变量开了一个特例：它可以在声明中给缺省值。之所以说是特例，是因为静态整型成员变量才能这样做，静态浮点型，静态字符型等都不能给声明缺省，而必须在声明外定义，之前不说这个，是因为这个特例是反逻辑的，会干扰我们的学习逻辑。

```cpp
char* _str;
size_t _size;
size_t _capacity;
const static size_t npos = -1;
```

### insert

```cpp
wind::string& wind::string::insert(size_t pos, const char* str)
{
	// 插入位置合法性检查
	assert(pos <= _size);
	size_t len = strlen(str);
	if (_size + len > _capacity)
	{
		reserve(_size + len);
	}
	size_t source = _size;
	size_t destination = _capacity;

	// 因为下标使用无符号整型
	// 所以很容易出现((size_t)-1) > ((size_t)others)

	// 强制类型转换或者把sour和dest用int类型也不行
	// 一是可能存在int溢出危险
	// 二是C++和C都有一个“算数转换”的说法：
	// 如果某个操作符的各个操作数属于不同的类型，那么
	// 除⾮其中⼀个操作数的转换为另⼀个操作数的类型
	// 否则操作就⽆法进⾏
	// 当int与size_t作比较时，int会被自动强转为size_t

	// 亦不能使用strcpy，因为待填充的空间可能与有限成员空间重叠
	while (source != 0 && source >= pos)
	{
		_str[destination--] = _str[source--];
	}
	// 退出循环，无非是两种情况：
	// source == 0：source已经处于临界值，再减就要变成最大值了
	// source < pos：不用再拷贝了
	if (source >= pos)
	{
		_str[destination--] = _str[source--];
	}
	// strcpy有'\0'，所以不能用
	memcpy(_str + pos, str, strlen(str));


	_size += len;

	return *this;
}

wind::string& wind::string::insert(size_t pos, const string& s)
{
	this->insert(pos, s._str);
	return *this;
}

wind::string& wind::string::insert(size_t pos, const char ch)
{
	assert(pos <= _size);
	if (_size == _capacity)
	{
		if (_capacity == 0)
		{
			reserve(1);
		}
		else
		{
			reserve(_capacity * 2);
		}
	}
	size_t source = _size;
	size_t destination = source + 1;
	while (source != 0 && source >= pos)
	{
		_str[destination--] = _str[source--];
	}
	if (source >= pos)
	{
		_str[destination--] = _str[source--];
	}
	_str[pos] = ch;
	_size++;
	return *this;
}
```

### relational

逻辑运算符在标准库中是以非成员函数的形式出现的，这是为了让运算符使用的更加灵活，第一个参数也可以不是对象，而是一个C中的字符串。

```cpp
const char* wind::string::c_str()
{
	return _str;
}

const char* wind::string::c_str()const
{
	return _str;
}

bool wind::operator>(const wind::string& s1, const wind::string& s2)
{
	// 模版当然不是这样写的，可能是以迭代器或者[]重载的形式
	// 一个个比较成员，但我们这里不是用模版的，所以就直接用
	if (strcmp(s1.c_str(), s2.c_str()) > 0)
		return true;
	else
		return false;
}

bool wind::operator>(const wind::string& s, const char* str)
{
	if (strcmp(s.c_str(), str) > 0)
		return true;
	else
		return false;
}

bool wind::operator>(const char* str, const string& s)
{
	if (strcmp(str, s.c_str()) > 0)
		return true;
	else
		return false;
}


bool wind::operator==(const wind::string& s1, const wind::string& s2)
{
	if (strcmp(s1.c_str(), s2.c_str()) == 0)
		return true;
	else
		return false;
}

bool wind::operator==(const wind::string& s, const char* str)
{
	if (strcmp(s.c_str(), str) == 0)
		return true;
	else
		return false;
}

bool wind::operator==(const char* str, const string& s)
{
	if (strcmp(str, s.c_str()) == 0)
		return true;
	else
		return false;
}


bool wind::operator<(const wind::string& s1, const wind::string& s2)
{
	if (s1 > s2 || s1 == s2)
		return false;
	else
		return true;
}

bool wind::operator<(const wind::string& s, const char* str)
{
	if (s > str || s == str)
		return false;
	else
		return true;
}

bool wind::operator<(const char* str, const string& s)
{
	if (str > s || str == str)
		return false;
	else
		return true;
}
// 其它就先不写了
```

### IO

```cpp

```

![image-20241018132134218](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410181321367.png)

```cpp
int main()
{
	std::string s;
	// 输入"hello string"
	std::cin >> s;
	// 只会提取"hello"
	// "string"还留在缓冲区
	std::cout << s;
	return 0;
}
```

![image-20241018132034411](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410181320680.png)



### erase





# 完