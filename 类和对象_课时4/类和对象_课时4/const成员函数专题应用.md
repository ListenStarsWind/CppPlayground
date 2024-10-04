# const成员函数专题应用

在《类和对象_课时3》中，我们稍微提及了const成员函数。接下来，我们就以顺序表为例，展示一下const成员函数的应用。

## 搭建框架

因为这里主要是展示一下const成员函数的应用，所以就快速搭建一个静态顺序表，这个静态顺序表是不全的，比如没有析构，所以它不严谨。

```cpp
namespace wind
{
	typedef int SLDate, * pSLDate;
	class SeqList
	{
	public:
		void Push(const SLDate& val);
		void Print();
	private:
		pSLDate _pVal = (pSLDate)malloc(sizeof(SLDate) * 10);
		size_t _Size = 0;
		size_t _Capacity = 10;
	};
}

void wind::SeqList::Push(const SLDate& val)
{
	_pVal[_Size++] = val;
}

void wind::SeqList::Print()
{
	size_t i = 0;
	for (; i < _Size; i++)
	{
		std::cout << _pVal[i] << " ";
	}
	std::cout << std::endl;
}

void SLTest1()
{
	wind::SeqList s1;
	s1.Push(1);
	s1.Push(2);
	s1.Push(3);
	s1.Push(4);
	s1.Print();
}

int main()
{
	SLTest1();
	return 0;
}
```

![image-20241004105005509](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410041050744.png)

## 优化

我们知道，顺序表本质上就是数组，那有没有方法让顺序表像数组那样使用呢？当然是有的，对`[]`进行运算符重载即可。

```cpp
size_t wind::SeqList::Size()
{
	return _Size;
}

wind::SLDate& wind::SeqList::operator[](size_t location)
{
	assert(location < _Size);
	return _pVal[location];
}

void SLTest2()
{
	wind::SeqList s1;
	s1.Push(1);
	s1.Push(2);
	s1.Push(3);
	s1.Push(4);
	size_t i = 0, j = s1.Size();
	for (; i < j; i++)
	{
		std::cout << s1[i]++ << " ";
	}
	std::cout << std::endl;
	for (i = 0; i < j; i++)
	{
		std::cout << s1[i] << " ";
	}
	std::cout << std::endl;
}
```

![image-20241004112616476](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410041126619.png)

## 出现问题

```cpp
// 为了提高效率，使用引用传参
// 为了避免被改，使用静态引用
void SLTest3_1(const wind::SeqList& s)
{
	size_t i = 0, j = s.Size();
	for (i = 0; i < j; i++)
	{
		std::cout << s[i] << " ";
	}
	std::cout << std::endl;
}

void SLTest3()
{
	wind::SeqList s1;
	s1.Push(1);
	s1.Push(2);
	s1.Push(3);
	s1.Push(4);
	SLTest3_1(s1);
	s1.Print();
}
```

我们发现这段代码跑不起来，一看，小问题，不就运算符重载函数`[]`没给`this`加`const`吗，加上就好了。

```cpp
namespace wind
{
	typedef int SLDate, * pSLDate;
	class SeqList
	{
	public:
		void Push(const SLDate& val);
		void Print()const;
		size_t Size()const;
		SLDate& operator[](size_t location)const;
	private:
		pSLDate _pVal = (pSLDate)malloc(sizeof(SLDate) * 10);
		size_t _Size = 0;
		size_t _Capacity = 10;
	};
}
```

![image-20241004113917023](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410041139162.png)

然后就发现一个令人匪夷所思的现象

```cpp
// 为了提高效率，使用引用传参
// 为了避免被改，使用静态引用
void SLTest3_1(const wind::SeqList& s)
{
	size_t i = 0, j = s.Size();
	for (i = 0; i < j; i++)
	{
		std::cout << s[i] << " ";
	}
	std::cout << std::endl;
	for (i = 0; i < j; i++)
	{
		s[i]*=2;
	}
}

void SLTest3()
{
	wind::SeqList s1;
	s1.Push(1);
	s1.Push(2);
	s1.Push(3);
	s1.Push(4);
	SLTest3_1(s1);
	s1.Print();
}
```

![image-20241004114344747](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410041143830.png)

一眼就可以看出问题，`[]`的重载函数引用返回没加const：

```cpp
wind::SLDate& wind::SeqList::operator[](size_t location)const
{
	assert(location < _Size);
	return _pVal[location];
}
```

那要直接加吗？不行，直接加就无法修改普通对象的数组值了。这里我们结合重载函数，让普通对象和被const修饰的对象使用不同的`[]`重载函数：

```cpp
namespace wind
{
	typedef int SLDate, * pSLDate;
	class SeqList
	{
	public:
		void Push(const SLDate& val);
		void Print()const;
		size_t Size()const;
		const SLDate& operator[](size_t location)const;
		SLDate& operator[](size_t location);
	private:
		pSLDate _pVal = (pSLDate)malloc(sizeof(SLDate) * 10);
		size_t _Size = 0;
		size_t _Capacity = 10;
	};
}

const wind::SLDate& wind::SeqList::operator[](size_t location)const
{
	assert(location < _Size);
	return _pVal[location];
}

wind::SLDate& wind::SeqList::operator[](size_t location)
{
	assert(location < _Size);
	return _pVal[location];
}

// 为了提高效率，使用引用传参
// 为了避免被改，使用静态引用
void SLTest3_1(const wind::SeqList& s)
{
	size_t i = 0, j = s.Size();
	for (i = 0; i < j; i++)
	{
		std::cout << s[i] << " ";
	}
	std::cout << std::endl;
	/*for (i = 0; i < j; i++)
	{
		s[i]*=2;
	}*/
}

void SLTest3()
{
	wind::SeqList s1;
	s1.Push(1);
	s1.Push(2);
	s1.Push(3);
	s1.Push(4);
	SLTest3_1(s1);
	s1.Print();
}

int main()
{
	SLTest2();
	SLTest3();
	return 0;
}
```

![image-20241004115121608](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410041151696.png)

# 完