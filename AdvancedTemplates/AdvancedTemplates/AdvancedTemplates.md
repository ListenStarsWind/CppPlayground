# AdvancedTemplates

下面我们说说模版的进阶用法。

## Non-Type Template Parameters

我们先写一个静态栈

```cpp
#define N 10

template<class T>
class stack
{
public:
	T _a[N];
};
```

这样写肯定是不行的，比如现在要实现两个 static stack 【静态栈】，一个要求可以容纳1000个元素，另一个只要10个元素。为此，C++允许模版参数可以是非类型的常整型家族对象。

```CPP
template<class T, size_t N>
class stack
{
public:
	T _a[N];
};

int main()
{
	stack<int, 10>s1;
	stack<double, 1000>s2;
	return 0;
}
```

注意，前面也说了，必须传常量，或者常属性的量，理由也很明显，变量编译时是不确定的，那怎么实例化这个类模版？

本来，非类型模版参数只能是整型家族里的：无符号整型，短整型，长整型，整型······，但C++20放开了标准，使得其可以支持其它类型的模版参数。

现在我使用的是C++14。可以通过【右键项目】->【属性】->【配置】查看并修改，不建议使用过新的标准，可能会产生适配问题。

![image-20241107111930501](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411071119128.png)

![image-20241107111952988](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411071119485.png)

![image-20241107112133880](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411071121287.png)

![image-20241107112151463](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411071121514.png)

![image-20241107112220007](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411071122497.png)

![image-20241107112245297](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411071122333.png)

-------------

顺便说说容器array。

![image-20241107112827142](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411071128197.png)

array是一个没什么用的静态数组，其设计目的似乎是为了解决C中数组的越界问题

```cpp
int arr[10] = {0};
arr[15] = 6;
```

C没有强制规定编译器对数组进行范围检查，因此有些编译器可能真的能把这段代码编译成功。

C++强制规定array，可以进行范围检查，比如在`[]`重载的时候。不过没什么用，因为array似乎也就这一个优点了。而且，既然都有vector了，为什么要有array。

我们在位图将会重新遇到非类型模版参数。

## Class Template Specialization

模版可以进行特化，所谓特化，就是针对某些类型，对模版进行特别处理。

模版特化分为两种，完全特化和偏特化。

所谓完全特化就是完全针对某个类型，语法格式如下

```cpp
#include<iostream>

using namespace std;

template<class T1, class T2>
class Date
{
public:
	Date() { cout << "T1 and T2" << endl; };
private:
	T1 _a;
	T2 _b;
};

template<>
class Date<int, double>
{
public:
	Date() { cout << "int and double" << endl; };
};

int main()
{
	Date<double, int>();
	Date<int, double>();

	return 0;
}
```

![image-20241107120026124](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411071200236.png)

接下来我们回顾一个问题，当容器内的元素为指针时，我们期望其元素进行大小比较时，比较指针指向的数据

```cpp
#include<iostream>
#include<queue>

using namespace std;


class Date
{
public:
	Date(int year = 1900, int month = 1, int day = 1)
		: _year(year)
		, _month(month)
		, _day(day)
	{}
	bool operator<(const Date& d)const
	{
		return (_year < d._year) ||
			(_year == d._year && _month < d._month) ||
			(_year == d._year && _month == d._month && _day < d._day);
	}
	bool operator>(const Date& d)const
	{
		return (_year > d._year) ||
			(_year == d._year && _month > d._month) ||
			(_year == d._year && _month == d._month && _day > d._day);
	}

	friend ostream& operator<<(ostream& _cout, const Date& d);

private:
	int _year;
	int _month;
	int _day;
};

ostream& operator<<(ostream& _cout, const Date& d)
{
	_cout << d._year << "-" << d._month << "-" << d._day;
	return _cout;
}


void test2()
{
	priority_queue<Date*, vector<Date*>, greater<Date*>> q1;
	q1.push(new Date(2018, 10, 29));
	q1.push(new Date(2018, 10, 28));
	q1.push(new Date(2018, 10, 30));
	cout << *q1.top() << endl;
}

int main()
{
	test2();
	return 0;
}
```

在priority_queue里，我们用仿函数解决了这个问题，其实用模版完全特化也可以这样解决。

```cpp
template<>
class greater<Date*>
{
public:
	bool operator()(const Date* p1, const Date* p2)
	{
		return *p1 > *p2;
	}
};

void test2()
{
	priority_queue<Date*, vector<Date*>, greater<Date*>> q1;
	q1.push(new Date(2018, 10, 29));
	q1.push(new Date(2018, 10, 28));
	q1.push(new Date(2018, 10, 30));
	cout << *q1.top() << endl;
}
```

![image-20241107121414138](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411071214196.png)

偏特化就是不完全特化，它分两种，一是模版参数有多个时，把其中的一个参数完全固定；二是将参数限制在某些类型中，比如指针，引用，亦或者多个参数前一个是指针，后一个是引用。

```cpp
template<>
class greater<Date*>
{
public:
	bool operator()(const Date* p1, const Date* p2)
	{
		return *p1 > *p2;
	}
};

template<class T>
class greater<T*>
{
public:
	bool operator()(const T* p1, const T* p2)
	{
		return *p1 > *p2;
	}
};

void test2()
{
	priority_queue<Date*, vector<Date*>, greater<Date*>> q1;
	q1.push(new Date(2018, 10, 29));
	q1.push(new Date(2018, 10, 28));
	q1.push(new Date(2018, 10, 30));
	cout << *q1.top() << endl;

	priority_queue<int*, vector<int*>, greater<int*>> q2;
	q2.push(new int(5));
	q2.push(new int(2));
	q2.push(new int(7));
	cout << *q2.top() << endl;

}
```

![image-20241107122431497](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411071224560.png)

```cpp
#include<iostream>

using namespace std;

template<class T1, class T2>
class Date
{
public:
	Date() { cout << "T1 and T2" << endl; };
private:
	T1 _a;
	T2 _b;
};

template<>
class Date<int, double>
{
public:
	Date() { cout << "int and double" << endl; };
};

template<class T>
class Date<T, double>
{
public:
	Date() { cout << "T and double" << endl; };
};


int main()
{
	Date<double, int>();
	Date<int, double>();
	Date<double, double>();
	return 0;
}
```

![image-20241107123001147](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411071230198.png)

------------

我们上面所说的特化都是针对类模版的，接下来我们稍微提及一下函数模版的特化，之所以说是提及，是因为它有些缺陷，因此在实践中很少使用。

```cpp
template<class T>
bool Less(T left, T right)
{
	return left < right;
}

template<>
bool Less<Date*>(Date* left, Date* right)
{
	return *left < *right;
}

void test3()
{
	Date* p1 = new Date(2024, 11, 10);
	Date* p2 = new Date(2024, 11, 9);
	std::cout << Less(p1, p2) << std::endl;
}
```

![image-20241110093006727](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411100930790.png)

为什么说有缺陷呢？因为函数模版一般都不是上面的写法，而是下面的写法

```cpp
template<class T>
bool Less(const T& left, const T& right)
{
	return left < right;
}
```

在这种情况下，模板参数使用常引用来避免拷贝并保护对象不被修改。然而，这样的实现导致了模板特化时的问题：

```cpp
template<>
bool Less<Date*>(const Date*& left, const Date*& right)
{
	return *left < *right;
}
```

指针也可以被引用，所以编译器认为`const Date*&`是一个引用，它引用了`const Date*`；换言之，`const`被错误修饰了，编译器误认为`const`修饰的是指针，而不是我们所期望的引用。此时就会产生一些问题：比如`Less`前面特化的类型是`Date*`，但后面引用的类型是`const Date*`，也就是说`const Date*`充当了`T`的位置，但原模版的`T`前面还要有`const`，模版特化和模版原型对不上了。

需要这样写

```cpp
template<>
bool Less<Date*>(Date* const & left, Date* const & right)
{
	return *left < *right;
}
```

太难看了，所以我们很少会用函数模版特化，特别是在涉及到指针和引用的组合时。

-----------------------------------

当然，函数模板特化的问题是有解决方案的。实际上，我们完全可以通过编写具体的函数来避免这些问题。编译器在解析函数调用时，会优先查找匹配的具体函数，只有在没有找到合适的具体函数时，才会尝试实例化模板。因此，编写一个具体的函数可以解决特化时的匹配问题。

例如，我们可以直接定义如下具体函数：

```cpp
bool Less(Date* & left, Date* & right)
{
	return *left < *right;
}
```

在这里，我们直接去掉了 `const` 修饰，因为这是一个具体函数，不需要遵循模板函数的形式。这样，编译器在调用 `Less` 时会优先匹配此具体实现，而不会再实例化模板版本。这种方式不仅避免了模板特化带来的复杂性，还能保持代码的清晰和易于维护。

# end