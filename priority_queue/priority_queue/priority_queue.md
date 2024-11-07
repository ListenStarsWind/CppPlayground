[TOC]

# priority_queue

## feel

### [documentation](https://legacy.cplusplus.com/reference/queue/priority_queue/)

#### priority_queue

Priority queues are a type of container adaptors, specifically designed such that its first element is always the greatest of the elements it contains, according to some strict weak ordering criterion.

优先级队列是一种容器适配器类型，它依据某些`according to some `严格`strict`弱序`weak ordering`标准`criterion`，通过专门设计，使得其第一个元素总是其内部所有元素中最大的。

【严格性和弱序是数学中的两个概念，这里被引申到计算机科学中，二者都与对象之间的“关系”相关。严格性强调对象之间具有明确的关系，例如，`>=` 包含了两种可能性：`>` 和 `=`，因此它不具备严格性。而弱序则表明两个对象可能无法比较大小（如两个对象相等时）。弱序的言外之意是，当仿函数 `compare` 无法判断两个对象的大小时，应返回 `false`。具体细节将在 `realization` 部分进一步说明。】

This context is similar to a heap, where elements can be inserted at any moment, and only the max heap element can be retrieved (the one at the top in the priority queue).

在此种场景下（指的是上面一段对优先级队列的概括），优先级队列类似于堆。其中的元素可以随时插入，并且仅能检索堆中的最大元素，也就是优先级队列顶部的那个元素。

Priority queues `are`【被】 `implemented as`【实现为】 `container adaptors`【容器适配器】,`which are classes`【这些容器】 that use an `encapsulated`【封装】 object of a `specific`【特定的】 container class as `its`【其】 `underlying container`【底层容器】,`providing`【提供】 a specific `set of`【一组】 member functions `to`【用来】 access its elements. Elements are *popped* from the *"back"* of the specific container, `which is known as`【这被称为】 the *top* of the priority queue.

The underlying container `may be`【可以是】 `any of`【任何】 the standard container class templates or some other specifically designed container class. The container shall `be accessible`【可以访问】 `through`【通过】 `random access iterators` 【随机迭代器】and `support`【支持】 the `following`【以下】 operations:

- `empty()`
- `size()`
- `front()`
- `push_back()`
- `pop_back()`

The standard container classes [vector](https://legacy.cplusplus.com/vector) and [deque](https://legacy.cplusplus.com/deque) `fulfill`【满足】 these `requirements`【要求】. By default, if no container class is `specified`【指定的】 for a `particular`【特定的】 [priority_queue](https://legacy.cplusplus.com/priority_queue) class `instantiation`【实例化】, the standard container [vector](https://legacy.cplusplus.com/vector) is used.

`Support`【支持】 of *[random access iterators](https://legacy.cplusplus.com/RandomAccessIterator)* is `required`【必须的】 `to`【为了】 keep a heap `structure`【结构】 `internally`【在内部】 `at all times`【时刻】.This is `done`【完成】 `automatically`【自动】 by the container adaptor `by`【通过】 automatically `calling`【调用】 the algorithm functions [make_heap](https://legacy.cplusplus.com/make_heap), [push_heap](https://legacy.cplusplus.com/push_heap) and [pop_heap](https://legacy.cplusplus.com/pop_heap) `when needed`【当需要时】.

#### Template parameters

- T: Type of the elements. Aliased as member type priority_queue::value_type.
- Container: Type of the internal *underlying container* object where the elements are stored. Its value_type shall be T. Aliased as member type priority_queue::container_type.
- Compare: A `binary`【二元的(涉及两个元素的)】 `predicate`【谓语(通常是函数或其它功能性语句)】 that `takes`【接受】 two elements (of type T) `as arguments`【作为参数】 and returns a bool. The `expression`【表达式】 comp(a,b), `where`【其中】 comp is an object of `this`【compare】 type, and a and b are elements in the container, shall return true if a is `considered`【被认为】 `to go`【排在】 before b in the strict weak `ordering`【序列】 the function `defines`【所定义的】. The priority_queue uses this function to `maintain`【维持】 the elements sorted,  `in a way`【通过这种方式】 that `preserves`【保护】 heap `properties`【属性】 (i.e., that the element popped is the last , `according`【按照】 to this `strict weak ordering`【严格弱序列】). `This`【这个仿函数】 `can be`【可以是】 a `function pointer`【函数指针】 or a `function object`【函数对象】,  and `defaults to`【默认是】 less\<T>, `which returns`【其返回值】 `the same as`【与之相同】 `applying`【使用】 the `less-than operator`【小于运算符】 (a<b)【的结果】.

#### Member types

| member type    | definition                                | notes                                                        |
| -------------- | ----------------------------------------- | ------------------------------------------------------------ |
| value_type     | The first template parameter (T)          | Type of the elements                                         |
| container_type | The second template parameter (Container) | Type of the *underlying container*                           |
| size_type      | an unsigned integral type                 | usually the same as [size_t](https://legacy.cplusplus.com/size_t) |

#### Member functions

|                                                              |                                                           |
| ------------------------------------------------------------ | --------------------------------------------------------- |
| [**(constructor)**](https://legacy.cplusplus.com/reference/queue/priority_queue/priority_queue/) | Construct priority queue (public member function )        |
| [**empty**](https://legacy.cplusplus.com/reference/queue/priority_queue/empty/) | Test whether container is empty (public member function ) |
| [**size**](https://legacy.cplusplus.com/reference/queue/priority_queue/size/) | Return size (public member function )                     |
| [**top**](https://legacy.cplusplus.com/reference/queue/priority_queue/top/) | Access top element (public member function )              |
| [**push**](https://legacy.cplusplus.com/reference/queue/priority_queue/push/) | Insert element (public member function )                  |
| [**emplace** ](https://legacy.cplusplus.com/reference/queue/priority_queue/emplace/) | Construct and insert element (public member function )    |
| [**pop**](https://legacy.cplusplus.com/reference/queue/priority_queue/pop/) | Remove top element (public member function )              |
| [**swap** ](https://legacy.cplusplus.com/reference/queue/priority_queue/swap/) | Swap contents (public member function )                   |

#### Non-member function overloads

|                                                              |                                                              |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| [**swap (queue)** ](https://legacy.cplusplus.com/reference/queue/priority_queue/swap-free/) | Exchange contents of priority queues (public member function ) |

#### Non-member class specializations

|                                                              |                                                     |
| ------------------------------------------------------------ | --------------------------------------------------- |
| [**uses_allocator** ](https://legacy.cplusplus.com/reference/queue/priority_queue/uses_allocator/) | Uses allocator for priority queue (class template ) |

### using

就如文档所说的那样，priority_queue 的行为与 heap 非常相似，实际上，priority_queue 的底层逻辑就是 heap 。

```cpp
#include<queue>
#include<iostream>

using namespace std;

void using1()
{
	priority_queue<int> pq;

	pq.push(3);
	pq.push(7);
	pq.push(1);
	pq.push(8);
	pq.push(2);

	while (!pq.empty())
	{
		cout << pq.top() << " ";
		pq.pop();
	}
	cout << endl;
}

int main()
{
	using1();
	return 0;
}
```

![image-20241106192831066](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411061928288.png)

`Compare`缺省值为`less<T>`，此时它是大堆；若要使用小堆，第三个模版参数使用`greater<T>`即可

```cpp
void using1()
{
	priority_queue<int, vector<int>, greater<int>> pq;

	pq.push(3);
	pq.push(7);
	pq.push(1);
	pq.push(8);
	pq.push(2);

	while (!pq.empty())
	{
		cout << pq.top() << " ";
		pq.pop();
	}
	cout << endl;
}
```

![image-20241106192944536](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411061929581.png)

### example

#### [kth-largest-element-in-an-array](https://leetcode.cn/problems/kth-largest-element-in-an-array)

![image-20241106194411436](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411061944534.png)

## realization

priority_queue 的实现不是我们的重点，在C语言数据结构中，我们已经详细说明了 heap 的实现逻辑。下面我们只略微说说

```cpp
#pragma once

#include<vector>
#include<algorithm>
#include<assert.h>

namespace wind {

	template<class T, class container = std::vector<T>>
	class priority_queue
	{
		typedef priority_queue<T, container> self;

		size_t find_parent(size_t child)
		{
			return (child - 1) / 2;
		}

		size_t find_first_child(size_t parent)
		{
			return parent * 2 + 1;
		}

		size_t find_second_child(size_t parent)
		{
			return parent * 2 + 2;
		}

		void adjust_up(size_t child)
		{
			while (child > 0)
			{
				size_t parent = find_parent(child);
				if (_con[child] < _con[parent])
				{
					break;
				}
				else
				{
					std::swap(_con[child], _con[parent]);
					child = parent;
				}
			}
		}

		void adjust_down(size_t parent)
		{
			while (parent < _con.size())
			{
				size_t child = 0;
				size_t first_child = find_first_child(parent);
				size_t second_child = find_second_child(parent);

				if (!(first_child < _con.size()))
					break;
				else if (!(second_child < _con.size()))
					child = first_child;
				else
				{
					if (_con[first_child] < _con[second_child])
					{
						child = second_child;
					}
					else
					{
						child = first_child;
					}
				}

				if (_con[child] < _con[parent])
					break;
				else
				{
					std::swap(_con[child], _con[parent]);
					parent = child;
				}
			}
		}

	public:
		priority_queue() {};
		~priority_queue() {};

		void push(const T& val)
		{
			_con.push_back(val);
			adjust_up(_con.size() - 1);
		}

		void pop()
		{
			assert(_con.size());
			std::swap(_con[0], _con[_con.size() - 1]);
			_con.pop_back();
			adjust_down(0);
		}

		const T& top()
		{
			return _con[0];
		}

		size_t size()
		{
			return _con.size();
		}

		bool empty()
		{
			return _con.empty();
		}

	private:
		container _con;
	};

};
```

priority_queue 是一个容器适配器，其成员就是一个容器，一个自定义类型，所以不需要专门写构造和析构函数。下面随口说一说adjust_up and adjust_down，adjust_up 是向上调整，它的初始位置是子节点，通过对其父节点的层层比较，从而维持priority_queue 的 heap 属性，因是child，果是parent，也就是说，child 驱动着 parent 的迭代，因此循环变量应该以child为准；我们先找到父节点的位置，随后对父子节点进行比较，我们像标准库一样，默认建大堆，同时为了和下面的默认仿函数相适应，比较大小都以`<`为准；如果父子节点符合大堆的属性，那么就调整完成，break循环；如果不符合，就需要进行交换，把父子节点的数据相交换，从而最起码让当前层的父子节点符合大堆的属性，接着，child 继承 parent 的位置，对上一层的父子节点进行检查和修复。adjust_down 是向下调整，同理，parent 驱动着 child 的迭代，因此，循环变量应以 parent 为准；问题是，父节点可能有两个子节点，所以就需要对子节点进行检查，如果第一个子节点都失效了，那么自然没有第二个子节点，也就说找不到子节点了，调整到最底层了，所以就不用再继续了，于是break循环；如果第二个子节点失效，那么，被选中的child 自然是 first_child ；如果两个子节点都有效，那就让它们比较一下，因为我们默认是大堆，所以很明显，应该拿最大的子节点去和父节点比较，在选出比较的child 后，那就和父节点比较，如果符合大堆属性，那就break，不符合，就要交换数据修复它们的关系，然后向下一层继续迭代。迭代器构造就不说了，就是两个调整用来用去，当然，一个个插入也行。

```cpp
template <class InputIterator>
priority_queue(InputIterator begin, InputIterator end)
	:_con(begin, end)
{
	size_t parent = find_parent(_con.size() - 1);
	for( ; parent > 0 ; parent--)
	{
		adjust_down(parent);
	}
	if (parent == 0)
	{
		adjust_down(parent);
	}
}
```

size_t 无符号整型，要小心0的出现。

### functor

仿函数才是本节重点。仿函数是C++对函数指针的替代方案，就像文档所说那样，仿函数既可以是对函数指针的封装，也可以是一个具体的函数对象，不过既然我们开头就说仿函数是对函数指针的替代方案，我们下面只说使用具体函数对象实现仿函数。

在写出上面的priority_queue 后，如何快速替换 heap 的大小属性呢？在C语言数据结构《二叉树和堆》中，我们使用一个具体的函数来控制它，在返回值加个取反号来调整堆属性。

![image-20241106215601025](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411062156239.png)

![image-20241106215642232](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411062156486.png)

这样还是很麻烦，要改代码，C++怎么解决这个问题呢？答案就是伪函数。

伪函数，实际是某个类里的成员函数，为什么非要写成成员函数呢？这是为了利用C++的重载属性，我们对一个特殊的运算符进行重载——`()`

```cpp
template<class T>
struct less
{
	bool operator()(const T& val1, const T& val2)
	{
		return val1 < val2;
	}
};
```

为什么叫伪函数呢？用起来就像函数一样（好吧，底层其实也是函数）

```cpp
void using2()
{
	wind::less<int> cmp;
	cout << cmp(1, 2) << endl;
}
```

其中`cmp(1, 2)`会被转换成`cmp.operator()(1, 2)`，所以也可以写成

```cpp
void using2()
{
	wind::less<int> cmp;
	cout << cmp.operator()(1, 2) << endl;
}
```

就如文档所说，`cmp.operator()`的返回结果与使用小于号的结果相同。

那这怎么用到 priority_queue 呢？加个模版参数，再对局部区域修改即可。

```cpp
namespace wind {

	template<class T>
	struct less
	{
		bool operator()(const T& val1, const T& val2)
		{
			return val1 < val2;
		}
	};

	template<class T>
	struct greater
	{
		bool operator()(const T& val1, const T& val2)
		{
			return val1 > val2;
		}
	};

	template<class T, class container = std::vector<T>, class compare = less<T>>
	class priority_queue
	{
		typedef priority_queue<T, container, compare> self;

		size_t find_parent(size_t child)
		{
			return (child - 1) / 2;
		}

		size_t find_first_child(size_t parent)
		{
			return parent * 2 + 1;
		}

		size_t find_second_child(size_t parent)
		{
			return parent * 2 + 2;
		}

		void adjust_up(size_t child)
		{
			compare cmp;
			while (child > 0)
			{
				size_t parent = find_parent(child);
				if (cmp(_con[child], _con[parent]))
				{
					break;
				}
				else
				{
					std::swap(_con[child], _con[parent]);
					child = parent;
				}
			}
		}

		void adjust_down(size_t parent)
		{
			while (parent < _con.size())
			{
				size_t child = 0;
				size_t first_child = find_first_child(parent);
				size_t second_child = find_second_child(parent);

				compare cmp;
				if (!(first_child < _con.size()))
					break;
				else if (!(second_child < _con.size()))
					child = first_child;
				else
				{
					if (cmp(_con[first_child], _con[second_child]))
					{
						child = second_child;
					}
					else
					{
						child = first_child;
					}
				}

				if (cmp(_con[child], _con[parent]))
					break;
				else
				{
					std::swap(_con[child], _con[parent]);
					parent = child;
				}
			}
		}

	public:
		priority_queue() {};
		~priority_queue() {};

		void push(const T& val)
		{
			_con.push_back(val);
			adjust_up(_con.size() - 1);
		}

		void pop()
		{
			assert(_con.size());
			std::swap(_con[0], _con[_con.size() - 1]);
			_con.pop_back();
			adjust_down(0);
		}

		const T& top()
		{
			return _con[0];
		}

		size_t size()
		{
			return _con.size();
		}

		bool empty()
		{
			return _con.empty();
		}

	private:
		container _con;
	};

};
```

 ```cpp
 void using1()
 {
 	//priority_queue<int, vector<int>> pq;
 	wind::priority_queue<int, vector<int>> pq;
 
 	pq.push(3);
 	pq.push(7);
 	pq.push(1);
 	pq.push(8);
 	pq.push(2);
 
 	while (!pq.empty())
 	{
 		cout << pq.top() << " ";
 		pq.pop();
 	}
 	cout << endl;
 }
 ```

![image-20241107083318147](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411070833341.png)

```cpp
void using1()
{
	//priority_queue<int, vector<int>> pq;
	wind::priority_queue<int, vector<int>, greater<int>> pq;

	pq.push(3);
	pq.push(7);
	pq.push(1);
	pq.push(8);
	pq.push(2);

	while (!pq.empty())
	{
		cout << pq.top() << " ";
		pq.pop();
	}
	cout << endl;
}
```

![image-20241107083404363](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411070834447.png)

在`stl_alloc.h`里有这样一种函数

![image-20241107084335606](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411070843829.png)

```cpp
static void (* __set_malloc_handler(void (*__f)()))()
{
    void (* __old)() = __malloc_alloc_oom_handler;
    __malloc_alloc_oom_handler = __f;
    return(__old);
}
```

这个函数的名字是`__set_malloc_handler`，它返回一个函数指针`void (*)()`，它的参数也是一个函数指针`void(*_f)()`，或者这样看`void(*__set_malloc_handler)(function parameters)()`，其中`function parameters == void(*_f)()`。函数指针还是要略微了解的，虽然本来就用的少，C++又有了仿函数，但是面试时大概率会考的，毕竟其它指针没什么可考的。

-------------

再来看看算法库中的`sort`

![image-20241107090138011](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411070901287.png)

`sort`有两个版本，一个版本就两个参数，描述了一段迭代器区间；第二个版本，多了一个参数，用来描述 strict weak order criterion。

```cpp
void using3()
{
	int arr[] = {6, 5, 9, 4, 2};
	size_t sz = sizeof(arr) / sizeof(arr[0]);
	//sort(arr, arr + sz, greater<int>());
	sort(arr, arr + sz);
	for (auto e : arr)
	{
		cout << e << " ";
	}
	cout << endl;
}
```

![image-20241107091022039](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411070910148.png)

```cpp
void using3()
{
	int arr[] = {6, 5, 9, 4, 2};
	size_t sz = sizeof(arr) / sizeof(arr[0]);
	sort(arr, arr + sz, greater<int>());
	//sort(arr, arr + sz);
	for (auto e : arr)
	{
		cout << e << " ";
	}
	cout << endl;
}
```

![image-20241107091117162](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411070911236.png)

要注意，`sort`是function template，而`priority_queue`是class template，所以`priority_queue`的实例化形式是`priority_queue<int, vector<int>, greater<int>>`，而`sort`的实例化方式是`sort(begin, end, cmp)`；或者这样说function template传的是对象，而class template 传的是类型，`greater<int>()`是个匿名对象。

----------

来看下一个例子，回到我们学习类和模版时的`class Date`

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
```

```cpp
void test1()
{
	priority_queue<Date> q1;
	q1.push(Date(2018, 10, 29));
	q1.push(Date(2018, 10, 28));
	q1.push(Date(2018, 10, 30));
	cout << q1.top() << endl;
}
```

![image-20241107093932478](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411070939578.png)

class Date 重载了`> <`，因而可以比较大小，结果也是正确的。如果换一种形式呢？

```cpp
void test2()
{
	priority_queue<Date*> q1;
	q1.push(new Date(2018, 10, 29));
	q1.push(new Date(2018, 10, 28));
	q1.push(new Date(2018, 10, 30));
	cout << *q1.top() << endl;
}
```

![image-20241107094226215](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411070942343.png)

![image-20241107094251084](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411070942200.png)

![image-20241107094321314](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411070943457.png)

我们发现运行结果不一样。因为我们存放的是指针，所以在比较大小时，比较的是地址的大小，而非class Date的大小，而new开辟空间的原则是哪里有空开哪里，所以每次运行，三个Date都会存在不同的地方，其地址的相对大小关系不确定，所以运行结果也就不确定。

可以通过仿函数解决这个问题，自己实现一个仿函数，然后将其对象传入即可。

```cpp
struct pDate_less
{
	bool operator()(const Date* p1, const Date* p2)
	{
		return *p1 < *p2;
	}
};

struct pDate_greater
{
	bool operator()(const Date* p1, const Date* p2)
	{
		return *p1 > *p2;
	}
};


void test2()
{
	wind::priority_queue<Date*, vector<Date*>, pDate_greater> q1;
	q1.push(new Date(2018, 10, 29));
	q1.push(new Date(2018, 10, 28));
	q1.push(new Date(2018, 10, 30));
	cout << *q1.top() << endl;
}
```

functor是STL六大组件之一，我们之后还会见到它的更多用法。

# end