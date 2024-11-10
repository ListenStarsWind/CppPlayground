# myList

## `Feel`【感受】

### `documentation`【[文档](https://legacy.cplusplus.com/reference/list/list/)】

#### `List`【链表】

Lists are `sequence`【序列】（以某种特定顺序存储元素的）`containers`【容器】。`allow`【允许】`within the sequence`【在序列的】`anywhere`【任意位置】进行`constant time`【常量时间】的insert and erase`operations`【操作】。

List containers are `implemented as`【实现为】`doubly-linked`【双向链接】lists; Doubly linked lists can`contain in`【其包含的】`each of the elements`【每个元素】`store`【存储在】`different and unrelated`【不同且不相关的】`storage locations`【存储位置】。`ordering`【顺序】`is`【是通过】`each element`【每个元素】`of`【与其】`element preceding `【前一个元素】和`element following`【后一个元素】的` link`【链接】来`kept`【保持】的，这种`association`【关联】`internally`【在内部】进行。

They are `very similar to`【非常相似】forward_list: `main difference being`【主要的区别在于】，forward_list objects are `single-linked lists`【单向链表】，`and thus`【因此】，they can only `forwards`【向前】`be iterated`【迭代】。`in exchange for being`【但相对而言】`somewhat`【它们】`more smaller`【更小】`more efficient`【更高效】。

`to other base standard sequence containers`【与其他基本标准序列容器】（array, vector, `deque`【双端队列】）`compared`【相比】, lists `generally`【通常】`in`【在】`within the container`【容器中】`any position`【任意位置】`inserting`【插入】`extracting `【提取】`moving`【移动】`elements`【元素】方面`perform`【表现得】`better`【更好】，尤其是在`iterator`【迭代器】`already been obtained`【已经获得】`which`【的情况下】。`therefore`【因此】`of`【对于】那些`intensive`【频繁】`use`【使用】`these`【这些操作】的`algorithm`【算法】（`like sorting algorithms`【比如排序】）来说，lists also 表现得更出色。

`to these other sequence containers`【与其他序列容器】`compared`【相比】，`lists and forward_lists`【双向链表和单向链表】`of`【的】`main drawback`【主要缺点】是，they `lack`【缺乏】`direct`【直接】`by their position`【按照顺序】`access`【访问】`elements`【元素】的能力。`For example`【例如】，`to access the sixth element in a list`【当要访问链表中第六个元素的时候】，`has to`【必须】`from a known position`【从一个已知的位置】`like the beginning or the end`【如开头和结尾】`iterate`【迭代到】`that position`【该位置】，当起始位置到目标位置`between`【之间的】`distance`【距离】较远时，就需要`takes`【耗费】`linear time`【线性时间】，此外，they also `consume`【消耗】some `extra memory`【额外的内存】`keep`【来存储】`each element `【每个元素】`associated`【相关的】`linking information`【链接信息】。这对于包含`large`【大量】`small-sized elements`【小型元素】的lists来说是个`important`【重要】`factor`【因素】。

#### `Container properties`【容器属性】

- `sequence`【顺序结构】：`sequence containers`【序列容器】`in`【中的】`elements`【元素】以`strict`【严格的】`linear sequence`【线性顺序】`ordered`【排列】，可以`by their`【通过其在】`position in this sequence`【序列中的位置】`accessed`【访问】`individual elements`【单个元素】。
- `Doubly-linked list`【双向链表】：`each element`【每个元素】都保存着`how to locate the next and the previous elements`【如何定位上下元素的】`information`【信息】，`allowing`【允许】在`a specific element`【特定元素】`even of`【甚至是】`entire`【整个】`ranges`【范围】`before or after`【之前或之后】`constant time`【以恒定的时间】进行`insert and erase operations`【插入和删除操作】，`but no`【但是不能】`direct`【直接】`random`【随机】`access`【访问】。
- `Allocator-aware`【分配感知器】：The container uses an allocator object to `dynamically`【动态地】`handle`【处理】`its `【其】`storage needs`【存储需求】。

#### `Template parameters`【模版参数】

- T：Type of the elements. `member type `【成员类型】`list::value_type`是它的`Aliased`【别名】
- Alloc：`allocator object`【分配器对象】`of`【的】`Type`【类型】，`used to`【用于】`define`【定义】`storage allocation model`【存储分配的模型】。`By default`【一般情况下】，`used`【使用】`allocator class template`【默认的分配器模版】，它`defines`【定义了】`simplest`【最简单的】`memory allocation model`【内存分配模型】，`and`【并且】`is value-independent`【与值无关】。`member type`【成员类型】`list::allocator_type`是它的`Aliased`【别名】

#### `Member types`【成员类型】

| `member type`【成员类型】 | `definition`【定义】                                         | `notes`【备注】                                              |
| ------------------------- | ------------------------------------------------------------ | ------------------------------------------------------------ |
| value_type                | The first template parameter (`T`)                           |                                                              |
| allocator_type            | The second template parameter (`Alloc`)                      | `defaults to`【默认】: `allocator<value_type>`               |
| reference                 | allocator_type::reference                                    | for the default [allocator](https://legacy.cplusplus.com/allocator): `value_type&` |
| const_reference           | allocator_type::const_reference                              | for the default [allocator](https://legacy.cplusplus.com/allocator): `const value_type&` |
| pointer                   | allocator_type::pointer                                      | for the default [allocator](https://legacy.cplusplus.com/allocator): `value_type*` |
| const_pointer             | allocator_type::const_pointer                                | for the default [allocator](https://legacy.cplusplus.com/allocator): `const value_type*` |
| iterator                  | a [bidirectional iterator](https://legacy.cplusplus.com/BidirectionalIterator) 【双向迭代器】to `value_type` | `convertible to`【可转换为】 `const_iterator`                |
| const_iterator            | a [bidirectional iterator](https://legacy.cplusplus.com/BidirectionalIterator) to `const value_type` |                                                              |
| reverse_iterator          | reverse_iterator\<iterator>                                  |                                                              |
| const_reverse_iterator    | [reverse_iterator](https://legacy.cplusplus.com/reverse_iterator)<const_iterator> |                                                              |
| difference_type           | a signed integral type, `identical` 【相同】to: `iterator_traits<iterator>::difference_type` | usually the same as [ptrdiff_t](https://legacy.cplusplus.com/ptrdiff_t) |
| size_type                 | an unsigned integral type that can `represent`【表示】 any non-negative value of `difference_type` | usually the same as [size_t](https://legacy.cplusplus.com/size_t) |

#### `Member functions`【成员函数】

|                                                              |                                           |
| ------------------------------------------------------------ | ----------------------------------------- |
| [**(constructor)**](https://legacy.cplusplus.com/reference/list/list/list/) | Construct list (public member function )  |
| [**(destructor)**](https://legacy.cplusplus.com/reference/list/list/~list/) | List destructor (public member function ) |
| [**operator=**](https://legacy.cplusplus.com/reference/list/list/operator=/) | Assign content (public member function )  |

**Iterators**:

|                                                              |                                                              |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| [**begin**](https://legacy.cplusplus.com/reference/list/list/begin/) | Return iterator to beginning (public member function )       |
| [**end**](https://legacy.cplusplus.com/reference/list/list/end/) | Return iterator to end (public member function )             |
| [**rbegin**](https://legacy.cplusplus.com/reference/list/list/rbegin/) | Return reverse iterator to reverse beginning (public member function ) |
| [**rend**](https://legacy.cplusplus.com/reference/list/list/rend/) | Return reverse iterator to reverse end (public member function ) |
| [**cbegin** ](https://legacy.cplusplus.com/reference/list/list/cbegin/)【C++11】 | Return const_iterator to beginning (public member function ) |
| [**cend** ](https://legacy.cplusplus.com/reference/list/list/cend/)【C++11】 | Return const_iterator to end (public member function )       |
| [**crbegin** ](https://legacy.cplusplus.com/reference/list/list/crbegin/)【C++11】 | Return const_reverse_iterator to reverse beginning (public member function ) |
| [**crend** ](https://legacy.cplusplus.com/reference/list/list/crend/)【C++11】 | Return const_reverse_iterator to reverse end (public member function ) |

**Capacity**:

|                                                              |                                                           |
| ------------------------------------------------------------ | --------------------------------------------------------- |
| [**empty**](https://legacy.cplusplus.com/reference/list/list/empty/) | Test whether container is empty (public member function ) |
| [**size**](https://legacy.cplusplus.com/reference/list/list/size/) | Return size (public member function )                     |
| [**max_size**](https://legacy.cplusplus.com/reference/list/list/max_size/) | Return maximum size (public member function )             |

**Element access**:

|                                                              |                                                |
| ------------------------------------------------------------ | ---------------------------------------------- |
| [**front**](https://legacy.cplusplus.com/reference/list/list/front/) | Access first element (public member function ) |
| [**back**](https://legacy.cplusplus.com/reference/list/list/back/) | Access last element (public member function )  |

`Modifiers`【修饰符】:

|                                                              |                                                              |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| [**assign**](https://legacy.cplusplus.com/reference/list/list/assign/) | Assign new content to container (public member function )    |
| [**emplace_front** ](https://legacy.cplusplus.com/reference/list/list/emplace_front/)【C++11】 | Construct and insert element at beginning (public member function ) |
| [**push_front**](https://legacy.cplusplus.com/reference/list/list/push_front/) | Insert element at beginning (public member function )        |
| [**pop_front**](https://legacy.cplusplus.com/reference/list/list/pop_front/) | Delete first element (public member function )               |
| [**emplace_back** ](https://legacy.cplusplus.com/reference/list/list/emplace_back/)【C++11】 | Construct and insert element at the end (public member function ) |
| [**push_back**](https://legacy.cplusplus.com/reference/list/list/push_back/) | Add element at the end (public member function )             |
| [**pop_back**](https://legacy.cplusplus.com/reference/list/list/pop_back/) | Delete last element (public member function )                |
| [**emplace** ](https://legacy.cplusplus.com/reference/list/list/emplace/)【C++11】 | Construct and insert element (public member function )       |
| [**insert**](https://legacy.cplusplus.com/reference/list/list/insert/) | Insert elements (public member function )                    |
| [**erase**](https://legacy.cplusplus.com/reference/list/list/erase/) | Erase elements (public member function )                     |
| [**swap**](https://legacy.cplusplus.com/reference/list/list/swap/) | Swap content (public member function )                       |
| [**resize**](https://legacy.cplusplus.com/reference/list/list/resize/) | Change size (public member function )                        |
| [**clear**](https://legacy.cplusplus.com/reference/list/list/clear/) | Clear content (public member function )                      |

**Operations**:

|                                                              |                                                              |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| [**splice**](https://legacy.cplusplus.com/reference/list/list/splice/) | `Transfer`【转移】 elements from list to list (public member function ) |
| [**remove**](https://legacy.cplusplus.com/reference/list/list/remove/) | `Remove`【移除】 elements with `specific`【特定】 value (public member function ) |
| [**remove_if**](https://legacy.cplusplus.com/reference/list/list/remove_if/) | Remove elements `fulfilling`【满足】 `condition`【条件】 (public member function template ) |
| [**unique**](https://legacy.cplusplus.com/reference/list/list/unique/) | Remove `duplicate`【重复的】 values (public member function ) |
| [**merge**](https://legacy.cplusplus.com/reference/list/list/merge/) | `Merge`【合并】 `sorted`【有序】 lists (public member function ) |
| [**sort**](https://legacy.cplusplus.com/reference/list/list/sort/) | Sort elements in container (public member function )         |
| [**reverse**](https://legacy.cplusplus.com/reference/list/list/reverse/) | `Reverse`【逆置】 the `order`【顺序】 of elements (public member function ) |

**Observers**:

|                                                              |                                         |
| ------------------------------------------------------------ | --------------------------------------- |
| [**get_allocator**](https://legacy.cplusplus.com/reference/list/list/get_allocator/) | Get allocator (public member function ) |

#### Non-member function overloads

|                                                              |                                                           |
| ------------------------------------------------------------ | --------------------------------------------------------- |
| [**relational operators (list)**](https://legacy.cplusplus.com/reference/list/list/operators/) | `Relational operators`【关系运算符】 for list (function ) |
| [**swap (list)**](https://legacy.cplusplus.com/reference/list/list/swap-free/)[**swap (list)**](https://legacy.cplusplus.com/reference/list/list/swap-free/) | Exchanges the contents of two lists (function template )  |

### `using`【使用】

#### 迭代器的分类·性质角度

与`vector`不同，`list`有一个自己专属的排序接口，这牵扯到容器底层实现的逻辑。算法库中的`sort`使用的是`randomAccess iterator`【随机访问迭代器】，而`list`使用的是`bidirectional iterator`【双向迭代器】。随机访问迭代器可以进行诸如`++ -- + -`等运算，而双向迭代器只支持`++ --`，除此之外，还有`forward iterator`【单向迭代器】，它只支持`++ 或 --`。迭代器的具体分类和容器的底层实现有关，对于`vector`，它使用的迭代器其实就是指针，因此自然而然的支持种种操作，而`list`是链表，是由一个个分立的节点构成的，节点的地址并不连续，所以`list`的迭代器其实是另一个自定义类型，实现的时候我们会细说的。

这三种迭代器之间是层层包含的关系，随机迭代器支持`+ - ++ --`，这意味着它必然也是双向迭代器(支持`++ --`)，同理，双向迭代器也是单向迭代器。

```cpp
void using1()
{
	std::list<int> lt;
	lt.push_back(5);
	lt.push_back(3);
	lt.push_back(2);
	lt.push_back(4);
	lt.push_back(1);

	lt.sort();

	std::list<int>::iterator it = lt.begin();
	while (it != lt.end())
	{
		std::cout << *it << " ";
		++it;
	}
	std::cout << std::endl;
}
```

![image-20241029141112532](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410291411742.png)

```cpp
void using1()
{
	std::list<int> lt;
	lt.push_back(5);
	lt.push_back(3);
	lt.push_back(2);
	lt.push_back(4);
	lt.push_back(1);

	// 默认是升序 less
	// 降序是 greater
	// 使用仿函数降序排列
	// 仿函数之后会详细说
	std::greater<int> gt;
	lt.sort(gt);
    // or 
    //lt.sort(std::greater<int>());

	std::list<int>::iterator it = lt.begin();
	while (it != lt.end())
	{
		std::cout << *it << " ";
		++it;
	}
	std::cout << std::endl;
}
```

![image-20241029141656613](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410291416725.png)

`list`里的`sort`日常用的不多，它的效率比较低，实际上我们一般先用`list`里的迭代器区间实例化出一个`vector`，然后再用算法库里的`sort`，之后再写回来。

下面我们切换到`release`，进行性能测试。`debug`会增加许多调试信息从而干扰测试。

```cpp
void using2(const int N)
{
	srand(time(0));
	std::vector<int> v;
	v.reserve(N);

	std::list<int> l;
	for (int i = 0; i < N; i++)
	{
		int e = rand();
		l.push_back(e);
		v.push_back(e);
	}

	int begin1 = clock();
	std::sort(v.begin(), v.end());
	int end1 = clock();

	int begin2 = clock();
	l.sort();
	int end2 = clock();

	std::cout << "vector:" << end1 - begin1 << "ms." << std::endl;
	std::cout << "list:" << end2 - begin2 << "ms." << std::endl;
}
```

```cpp
int main()
{
	using2(100000);
	return 0;
}
```

![image-20241029143527291](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410291435412.png)

```cpp
int main()
{
	using2(1000000);
	return 0;
}
```

![image-20241029144131762](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410291441832.png)

实际上一般这样进行链表排序

```cpp
void using2(const int N)
{
	srand(time(0));
	
	std::list<int> l1, l2;
	for (int i = 0; i < N; i++)
	{
		int e = rand();
		l1.push_back(e);
		l2.push_back(e);
	}

	int begin1 = clock();
	std::vector<int> v(l1.begin(), l1.end());
	std::sort(v.begin(), v.end());
	l1.assign(v.begin(), v.end());
	int end1 = clock();

	int begin2 = clock();
	l2.sort();
	int end2 = clock();

	std::cout << "list->vector->list:" << end1 - begin1 << "ms." << std::endl;
	std::cout << "list:" << end2 - begin2 << "ms." << std::endl;
}

int main()
{
	using2(1000000);
	return 0;
}
```

![image-20241029144950547](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410291449665.png)

#### 归并

`merge`【归并】可以将两个有序`list`合并到一起。

#### 去重

`unique`【去重】的前提仍然是有序。它实际就是前后指针的思路：定义两个索引，只有第二个索引与第一个索引指向的元素不相同，第一个索引才会向后迭代一次，然后删除该索引区间。

```cpp
void using3()
{
	std::list<int> l;
	l.push_back(1);
	l.push_back(1);
	l.push_back(1);
	l.push_back(4);
	l.push_back(2);
	l.push_back(2);

	// 数据量不大时，比如几万个以内
	// 为了方便可以直接用list::sort
	l.sort();
	l.unique();

	for (auto e : l)
	{
		std::cout << e << " ";
	}
	std::cout << std::endl;
}
```

![image-20241029150607724](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410291506808.png)

#### 移除特定元素

```cpp
void using3()
{
	std::list<int> l;
	l.push_back(1);
	l.push_back(1);
	l.push_back(1);
	l.push_back(4);
	l.push_back(2);
	l.push_back(2);

	l.remove(1);

	for (auto e : l)
	{
		std::cout << e << " ";
	}
	std::cout << std::endl;
}
```

![image-20241029150824375](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410291508472.png)

`remove_if`也涉及到仿函数，所以先不说。

#### 转移

`splice`【拼接】可以在`lists`之间转移元素。

```cpp
void using4()
{
	std::list<int> list1, list2;
	list1.push_back(1);
	list1.push_back(2);
	list1.push_back(3);
	list1.push_back(4);
	list1.push_back(5);

	list2.push_back(10);
	list2.push_back(20);
	list2.push_back(30);
	list2.push_back(40);
	list2.push_back(50);

	// 把单个元素转移
	list1.splice(++list1.begin(), list2, ++list2.begin());
	std::cout << "list1->";
	for (auto e : list1)
	{
		std::cout << e << " ";
	}
	std::cout << std::endl;
	std::cout << "list2->";
	for (auto e : list2)
	{
		std::cout << e << " ";
	}
	std::cout << std::endl;

	// 转移区间
	list1.splice(++list1.begin(), list2, ++list2.begin(), --list2.end());
	std::cout << "list1->";
	for (auto e : list1)
	{
		std::cout << e << " ";
	}
	std::cout << std::endl;
	std::cout << "list2->";
	for (auto e : list2)
	{
		std::cout << e << " ";
	}
	std::cout << std::endl;

	// 转移全部元素
	list1.splice(++list1.begin(), list2);
	std::cout << "list1->";
	for (auto e : list1)
	{
		std::cout << e << " ";
	}
	std::cout << std::endl;
	std::cout << "list2->";
	for (auto e : list2)
	{
		std::cout << e << " ";
	}
	std::cout << std::endl;
}
```

![image-20241029152658676](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410291526734.png)



## `realization`【实现】
接下来让我们看看源代码，双向链表之前我们已经用C语言实现过，`list`实现重点在迭代器。

节点结构：

![image-20241029171442165](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410291714654.png)

`list`本体

![image-20241029171718904](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410291717321.png)

可以看出来，这应该是个带头的链表

![image-20241029181820323](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410291818767.png)

`_M_node`就是那个头结点，从初始化列表里可以看出来

![image-20241029181954951](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410291819273.png)

`_M_get_node()`就是通过空间分配器获得一个节点。

-------------

好现在我们来写了

首先，我们要先创建一个节点模板。然后，在`list`里通过`typedef`和模板实例化来使用这个节点模板。这样做的好处是，节点结构可以独立于`list`存在，因此这个节点模板也能被其他类似的容器使用。相比之下，内部类的耦合度就太高了。

因为节点模板中的数据需要被`list`访问，所以我们选择用`struct`而不是`class`，这样节点的内容就能完全对外公开。

我们实现的是带头的双向链表，所以每个节点应该包含三个成员：数据、指向上一节点的指针和指向下一节点的指针。接下来，我们还需要定义节点的默认构造函数。考虑到`T`可能不是内置类型，我们的默认值设为`T()`。至于析构函数就不需要写了，因为指针是内置类型，不用我们操心，而`T`有自己的析构函数，也无需考虑。其他成员函数也没有特别需要的。

```cpp
template<class T>
struct __list_node_base {
	T _val;
	__list_node_base<T>* _prev;
	__list_node_base<T>* _next;

	__list_node_base(const T& val = T())
		:_val(val)
		, _prev(nullptr)
		, _next(nullptr)
	{}
};
```

早在C阶段，我们就写过双向链表，所以链表的操作逻辑并不是这次实现的重点，重点在于迭代器。与`vector`不同，`list`的结构决定它不能直接用原生指针来包装成迭代器，而是需要专门为迭代器创建一个类模板（为了适应`list`的模板类型，迭代器也要写成模板）。我们会通过运算符重载，让迭代器表现得像指针一样。

我们的步骤是先在没有迭代器的情况下实现`push_back`，然后写一个普通的迭代器。接着，我们会完善`list`，因为没有常迭代器的情况下，有些地方可能会不太规范。最后，我们再实现常迭代器，至于反向迭代器暂时先不考虑。

```cpp
	template<class T>
	class list {
		typedef __list_node_base<T> node;
		node* __init_head_node()
		{
			node* head = new node();
			head->_prev = head;
			head->_next = head;
			head->_val = T();
			return head;
		}
	public:
		typedef __list_iterator_base<T> iterator;

		list()
			:_head(__init_head_node())
			, _size(0)
		{}

		void push_back(const T& val)
		{
			node* oldTail = _head->_prev;
			node* newNode = new node(val);
			newNode->_next = _head;
			newNode->_prev = oldTail;
			oldTail->_next = newNode;
			_head->_prev = newNode;
			_size++;
		}
        
	private:
		node* _head;
		size_t _size;
	};
}
```

因为每次构造`list`都需要生成一个哨兵节点或头节点，所以我们单独实现了这个头节点的生成函数。然后，通过初始化列表来初始化成员变量`_head`。至于成员变量`_size`，在`list`的实现中并没有太大作用，主要是在实现成员函数`size`时，可以以常数时间获取链表的大小。

我们的迭代器只有一个成员变量，即指向节点的指针，这个指针是访问节点内部数据的通道。迭代器的功能是为容器中的数据提供一个标准的访问方式，因此数据的存在是迭代器有意义的前提。为了这个原因，我们的迭代器没有无参构造函数；但考虑到迭代器在使用时一定会有传参过程，所以拷贝构造函数是必不可少的。

`list`的迭代器是双向迭代器，因此我们只需要重载`++`和`--`操作。这两者又分为前置和后置，由于后置需要进行拷贝构造，所以建议在使用迭代器时优先选择前置版本。接下来，我们需要实现迭代器的相等与否的判断。

重点在于`*`和`->`这两种运算符的重载，因为它们体现了迭代器最重要的功能——访问数据。迭代器的设计目的是提供一套通用的方式来访问容器中的数据，通过一系列运算符重载，使其能像指针一样工作。

对于内置数据类型，我们可以直接用`*ptr`来获取值。而对于自定义类型，使用`(*ptr).member`会显得繁琐，所以我们有了`ptr->member`这种更简洁的方式。既然迭代器模仿指针，自然也需要重载`*`和`->`。

重载`*`很简单，只需返回模板类型的引用即可。至于`->`，需要特别说明的是，因为我们使用的是类模板，所以无法确定`T`是什么自定义类型，也无法知道它有哪些成员和成员的类型。因此，不能直接使用`T->member`的方式。

那么，当我们重载迭代器的`->`操作时，如何获取成员呢？C++对此做了特别处理：在重载`->`时，只需返回`T`的指针。然后编译器会根据这个指针找到对应的成员。例如，如果`T`是一个结构体 `{int a; int b};`，当有人写`iterator->a`时，编译器会将其理解为`T*->a`，而这个`T*`就是通过`->`重载获得的。

```cpp
template<class T>
struct __list_iterator_base {
	typedef __list_node_base<T> node;
	node* _ptr;
	__list_iterator_base(node* ptr)
		:_ptr(ptr)
	{}

	__list_iterator_base(const __list_iterator_base& obj)
		:_ptr(obj._ptr)
	{}
    
	// 迭代器的主要作用是访问数据，而不是管理数据（这是`list`的职责）。
	// 所以，我们不需要为迭代器写析构函数。
	// 另一个原因是，指针是内置类型，自然不需要析构。
    
	__list_iterator_base& operator++()
	{
		_ptr = _ptr->_next;
		return *this;
	}

	__list_iterator_base& operator++(int)
	{
		__list_iterator_base ret = *this;
		_ptr = _ptr->_next;
		return ret;
	}

	__list_iterator_base& operator--()
	{
		_ptr = _ptr->_prev;
		return *this;
	}

	__list_iterator_base& operator--(int)
	{
		__list_iterator_base ret = *this;
		_ptr = _ptr->_prev;
		return ret;
	}

	T& operator*() const
	{
		return _ptr->_val;
	}

	T* operator->()const
	{
		return &(_ptr->_val);
	}

	bool operator!=(const __list_iterator_base& obj)const
	{
		if (_ptr != obj._ptr)
			return true;
		else
			return false;
	}

	bool operator==(const __list_iterator_base& obj)const
	{
		if (*this != obj)
			return false;
		else
			return true;
	}
};
```

链表的具体实现很简单，因此我们就不细说了，实在觉得有困难，可以看我之前使用C语言实现《双向带头循环链表》的，里面也具有对应的学习笔记，详细说明了链表的实现逻辑。

```cpp
iterator begin()
{
	// 隐式类型转换
	return _head->_next;
}

iterator end()
{
	return _head;
}

bool empty()
{
	if (begin() == end())
		return true;
	else
		return false;
}

size_t size()
{
	return _size;
}

iterator insert(iterator pos, const T& val)
{
	// iterator全公开直接访问
	node* curr = pos._ptr;
	node* prev = curr->_prev;
	node* newNode = new node(val);
	newNode->_prev = prev;
	newNode->_next = curr;
	curr->_prev = newNode;
	prev->_next = newNode;
	_size++;
	return newNode;
}

iterator erase(iterator pos)
{
	assert(!empty());
	node* curr = pos._ptr;
	node* prev = curr->_prev;
	node* next = curr->_next;
	prev->_next = next;
	next->_prev = prev;
	delete curr;
	_size--;
	// 修正外部失效迭代器
	return next;
}

void pop_back()
{
	erase(--end());
}

void push_front(const T& val)
{
	insert(begin(), val);
}

void pop_front()
{
	erase(--end());
}

void clean()
{
	list::iterator it = begin();
	while (it != end())
	{
		// 连着删除，迭代器失效
		// 使用返回值修正迭代器
		it = erase(it);
	}
}

~list()
{
	clean();
	delete _head;
}

// 理论上应该用const list& l
// 但还没写const_iterator 
list(list& l)
	:_head(__init_head_node())
	, _size(0)
{
	// 常引用提升效率
	for (const auto& e : l)
	{
		push_back(e);
	}
}

// 与拷贝构造同理，暂时用list& l
list& operator=(list& l)
{
	if (this != &l)
	{
		clean();
		for (auto& e : l)
		{
			push_back(e);
		}
	}
	return *this;
}

void swap(const list& l)
{
	std::swap(_head, l._head);
	std::swap(_size, l._size);
}
```

接下来我们实现常迭代器。还记得我们一般迭代器的两个关键重载吗？`*` 和 `->`。这两个运算符是访问容器内部元素的手段，其中 `*` 返回元素的引用，因此可以被修改；而 `->` 返回元素的指针，同样可以被修改。

设计常迭代器的目的是保护容器内部的元素不被修改。在实现某些不修改元素的函数时，为了提高效率并保护元素，通常会传递容器的常引用，这时常迭代器就发挥了重要作用。

既然普通引用和普通指针指向的内容可以被修改，那么我们可以用常引用和常指针替代。这就是常迭代器的实现思路：让 `*` 返回常引用，`->` 返回常指针。至于基础迭代器模板的其他部分，它们与元素访问无关，主要是为了遍历元素，因此无需修改。

```cpp
template<class T>
struct __list_const_iterator_base {
	typedef __list_node_base<T> node;

	// 为了方便，这里再对它自己重命名一下
	typedef __list_const_iterator_base<T> self;

	node* _ptr;

	__list_const_iterator_base(node* ptr)
		:_ptr(ptr)
	{}

	__list_const_iterator_base(const self& obj)
		:_ptr(obj._ptr)
	{}

	self& operator++()
	{
		_ptr = _ptr->_next;
		return *this;
	}

	self& operator++(int)
	{
		self ret = *this;
		_ptr = _ptr->_next;
		return ret;
	}

	self& operator--()
	{
		_ptr = _ptr->_prev;
		return *this;
	}

	self& operator--(int)
	{
		self ret = *this;
		_ptr = _ptr->_prev;
		return ret;
	}

	const T& operator*() const
	{
		return _ptr->_val;
	}

	const T* operator->()const
	{
		return &(_ptr->_val);
	}

	bool operator!=(const self& obj)const
	{
		if (_ptr != obj._ptr)
			return true;
		else
			return false;
	}

	bool operator==(const self& obj)const
	{
		if (*this != obj)
			return true;
		else
			return false;
	}
};
```

```cpp
public:
	// 迭代器要被外部使用，因而放在公共域
	typedef __list_iterator_base<T> iterator;
	typedef __list_const_iterator_base<T> const_iterator;

const_iterator begin()const
{
	return _head->_next;
}


const_iterator end()const
{
	return _head;
}

list(const list& l)
	:_head(__init_head_node())
	, _size(0)
{
	for (const auto& e : l)
	{
		push_back(e);
	}
}

list& operator=(const list& l)
{
	if (this != &l)
	{
		clean();
		for (auto& e : l)
		{
			push_back(e);
		}
	}
	return *this;
}
```

不过这样有个问题，`__list_iterator_base`和`__list_const_iterator_base`绝大多数都是一样的，太冗余了。所以就有了第二种方案，再添加两个模版参数，一个是`reference`【引用】，一个是`pointer`【指针】，对于普通迭代器，实例化的参数是`T T& T*`，而对于常迭代器，参数是`T const T& const T*`。

```cpp
template<class T, class ref, class ptr>
struct __list_iterator_base {
	typedef __list_node_base<T> node;
	typedef __list_iterator_base<T, ref, ptr> self;

	node* _ptr;

	__list_iterator_base(node* ptr)
		:_ptr(ptr)
	{}

	__list_iterator_base(const self& obj)
		:_ptr(obj._ptr)
	{}

	self& operator++()
	{
		_ptr = _ptr->_next;
		return *this;
	}

	self& operator++(int)
	{
		self ret = *this;
		_ptr = _ptr->_next;
		return ret;
	}

	self& operator--()
	{
		_ptr = _ptr->_prev;
		return *this;
	}

	self& operator--(int)
	{
		self ret = *this;
		_ptr = _ptr->_prev;
		return ret;
	}

	ref operator*() const
	{
		return _ptr->_val;
	}

	ptr operator->()const
	{
		return &(_ptr->_val);
	}

	bool operator!=(const self& obj)const
	{
		if (_ptr != obj._ptr)
			return true;
		else
			return false;
	}

	bool operator==(const self& obj)const
	{
		if (*this != obj)
			return true;
		else
			return false;
	}
};
```

```cpp
public:
	// 迭代器要被外部使用，因而放在公共域
	typedef __list_iterator_base<T, T&, T*> iterator;
	typedef __list_iterator_base<T, const T&, const T*> const_iterator;
```

SGI的原码用的就是这种方案。

------------------

# 模版参数`typename`

下面我们写一下`print_list`，其实这个函数没什么实际价值，写这个主要是为了引出模版参数中`typename class`的区别

```cpp
void print_list(const wind::list<int> l)
{
	wind::list<int>::const_iterator it = l.begin();
	while (it != l.end())
	{
		std::cout << *it << " ";
		++it;
	}
	std::cout << std::endl;
}
```

这个函数有一个缺陷：只适用于`wind::list<int>`，所以，下面我们要把它写成模版函数。

```cpp
template<class T>
void print_list(const wind::list<T> l)
{
	wind::list<T>::const_iterator it = l.begin();
	while (it != l.end())
	{
		std::cout << *it << " ";
		++it;
	}
	std::cout << std::endl;
}
```

然后我们发现就编译不通过了，同时编译器输出了一条错误信息：`error C7510: “const_iterator”: 类型 从属名称的使用必须以“typename”为前缀`

这是因为语法检查的时候出现了问题：由于`T`不确定，所以语法检查的时候编译器无法实例化出一个具体的`list`模版，因此它无法确定`const_iterator`到底是个什么东西，尽管它大致猜出来是个类型，但它不敢确定，所以它提示`error C7510: “const_iterator”: 类型 从属名称的使用必须以“typename”为前缀`，这条信息的意思就是，你加个`typename`前缀的时候，编译器就不会提前对该模版函数进行语法检查，它会直接跳过，等到你真正调用`print_list`的时候，有了确定的`T`后，编译器才回过头来依据这个具体的`T`对该模版函数进行检查，并且检查完后再实例化一下，此时`T`就是确定的了，`wind::list<T>`就是一个确定的类型，编译器就可以真正地进入类域确定`const_iterator`到底是个什么东西。

```cpp
template<typename T>
void print_list(const wind::list<T> l)
{
	typename wind::list<T>::const_iterator it = l.begin();
	while (it != l.end())
	{
		std::cout << *it << " ";
		++it;
	}
	std::cout << std::endl;
}
```

还可以进一步优化：

```cpp
template<typename container>
void print_containers(const container obj)
{
	typename container::const_iterator it = obj.begin();
	while (it != obj.end())
	{
		std::cout << *it << " ";
		++it;
	}
	std::cout << std::endl;
}

void test5()
{
	std::list<int> l;
	std::vector<std::string> v;
	l.push_back(1);
	l.push_back(2);
	l.push_back(3);
	l.push_back(4);
	l.push_back(5);

	v.push_back("abc");
	v.push_back("def");
	v.push_back("ghi");
	v.push_back("jkl");
	v.push_back("mno");

	print_containers(l);
	print_containers(v);
}
```

![image-20241101120727147](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411011207255.png)

以后我们会学仿函数，就可以让本不支持io重载的`*it`变得可以被流插入，流提取，这样就真的什么都可以用了。

# 后日谈

我们写`vector`的时候有一个名叫“深层次的浅拷贝”问题，这在`list`中是不存在的，`vector`有这个问题是因为它扩容时需要挪动数据，此时使用`memcpy`只拷贝对象就会发生这个问题，`list`扩容时不会挪动数据，所以没有这方面的困扰。

# end