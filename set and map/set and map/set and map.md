# set and map

## associative container

C++的容器分为两类，一类是序列式容器，另一类是关联式容器。总的来说，序列式容器主要用于单纯地数据存储，比如`vector`，`list`，`deque`等，关联式容器则更侧重于数据管理，比如此处的`set`，`map`。

## [set](https://legacy.cplusplus.com/reference/set/set/)

class template

```cpp
template < class T,                        // set::key_type/value_type
           class Compare = less<T>,        // set::key_compare/value_compare
           class Alloc = allocator<T>      // set::allocator_type
           > class set;
```

可以看到`set`实际就是搜索树的`key`模型，`T`是`key`的类型，`compare`是仿函数，用于定义何为`<`，`Alloc`是分配器，不是我们现在要关注的。

Sets are containers that store `unique elements`【唯一的元素】 following a specific order.

In a `set`, the value of an element also `identifies`【标识为】 it (the value is itself the *key*, of type `T`), and `each`【每一个】 value must be unique. The value of the elements `in`【放入】 a `set` cannot `be modified once`【被修改一次】 in the container (the elements are always const), but they can be inserted or removed from the container.

`Internally`【在内部】, the elements in a `set` are always sorted following a specific *strict weak ordering* `criterion`【规则】 `indicated`【表明】 by `its`【其】 `internal`【内部】 [comparison object](https://legacy.cplusplus.com/set::key_comp) (of type `Compare`).

`set` containers are `generally`【通常】 `slower`【慢】 than [unordered_set](https://legacy.cplusplus.com/unordered_set) containers `to`【在】 access `individual`【各自】 elements by their *key*, but `they`【set containers】 `allow`【允许】 the `direct`【直接】 iteration on `subsets`【子集】 `based`【基于】 on their order.

Sets are `typically`【通常】 `implemented as`【实现为】 *binary search trees*.

### Container `properties`【属性】

- **Associative**【关联性】：Elements in associative containers are `referenced`【引用】 `by`【通过】 their *key* and not by their `absolute`【绝对】 position in the container.
- **Ordered**【有序性】：The elements in the container follow a strict order at all times. All inserted elements are `given`【已知的】 a position in this order.
- **Set**【统一性】：The value of an element is also the *key* used to identify it.【set是key模型，key就是value，value就是key，二者统一】
- **Unique keys**【唯一性】：No two elements in the container can have `equivalent`【相同的】 *keys*.
- **Allocator-aware**【感知分配】：The container uses an allocator object to `dynamically`【动态】 `handle`【处理】 its storage needs.

### Template parameters

- T ：Type of the elements. Each element in a `set` container is also uniquely identified by this value (each value is itself also the element's key). 
  `Aliased`【别名】 as member types `set::key_type` and `set::value_type`.
- Compare ：A `binary`【二元】 `predicate`【谓语函数】 that `takes`【接收】 two `arguments`【参数】 of the same type as the elements and returns a `bool`. The `expression`【表达式】 `comp(a,b)`, where *comp* is an object of `this`【this comp object】 type and *a* and *b* `are`【作为】 key values, `shall`【将】 return `true` if *a* is `considered`【被认为】 `to go before`【排在    之前】 *b* in the *strict weak ordering* the function defines.
  The `set` object uses this expression to `determine`【确定】 `both`【二者】 the order the elements follow in the container and `whether`【是否】 two element keys are `equivalent`【等价】 (by comparing them `reflexively`【反射性】: they are equivalent if `!comp(a,b) && !comp(b,a)`). No two elements in a `set` container can be equivalent.
  `This`【Compare】 can be a `function pointer`【函数指针】 or a `function object`【函数对象】 (see [constructor](https://legacy.cplusplus.com/set::set) for an example). This `defaults`【通常情况】 to `less<T>`, `which`【其】 returns the same as `applying`【应用】 the *less-than `operator`*【行为】 (`a<b`).
  Aliased as member types `set::key_compare` and `set::value_compare`.
- Alloc ：Type of the allocator object used to define the storage allocation model. By default, the [allocator](https://legacy.cplusplus.com/allocator) class template is used, which `defines`【定义】 the `simplest`【最简单的】 `memory`【内存】 allocation model `and`【并且】 is `value-independent.`【与值无关】
  Aliased as member type `set::allocator_type`.

### Member types

| **member type**        | **definition**                                               | **notes**                                                    |
| ---------------------- | ------------------------------------------------------------ | ------------------------------------------------------------ |
| key_type               | The first template parameter (`T`)                           |                                                              |
| value_type             | The first template parameter (`T`)                           |                                                              |
| key_compare            | The second template parameter (`Compare`)                    | defaults to: `less<key_type>`                                |
| value_compare          | The second template parameter (`Compare`)                    | defaults to: `less<value_type>`                              |
| allocator_type         | The third template parameter (`Alloc`)                       | defaults to: `allocator<value_type>`                         |
| reference              | allocator_type::reference                                    | for the default [allocator](https://legacy.cplusplus.com/allocator): `value_type&` |
| const_reference        | allocator_type::const_reference                              | for the default [allocator](https://legacy.cplusplus.com/allocator): `const value_type&` |
| pointer                | allocator_type::pointer                                      | for the default [allocator](https://legacy.cplusplus.com/allocator): `value_type*` |
| const_pointer          | allocator_type::const_pointer                                | for the default [allocator](https://legacy.cplusplus.com/allocator): `const value_type*` |
| iterator               | a [bidirectional iterator](https://legacy.cplusplus.com/BidirectionalIterator) to `value_type` | convertible to `const_iterator`                              |
| const_iterator         | a [bidirectional iterator](https://legacy.cplusplus.com/BidirectionalIterator) to `const value_type` |                                                              |
| reverse_iterator       | [reverse_iterator](https://legacy.cplusplus.com/reverse_iterator)\<iterator> |                                                              |
| const_reverse_iterator | reverse_iterator<const_iterator>                             |                                                              |
| difference_type        | a signed integral type, identical to: `iterator_traits<iterator>::difference_type` | usually the same as [ptrdiff_t](https://legacy.cplusplus.com/ptrdiff_t) |
| size_type              | an unsigned integral type that can represent any non-negative value of `difference_type` | usually the same as [size_t](https://legacy.cplusplus.com/size_t) |

可能有些东西似乎是重复多余的，这是出于通用性的考虑，划分这么细，是为了和其它关联容器保持一致。

其余相关内容在此就不一一列举了，我们直接进入使用阶段。

### using

```cpp
namespace set_using
{
	void test1()
	{
		set<int> s;
		s.insert(5);
		s.insert(2);
		s.insert(3);
		s.insert(6);
		set<int>::iterator it = s.begin();
		while (it != s.end())
		{
			cout << *it << " ";
			++it;
		}
		cout << endl;
	}
}
```

![image-20241202143037397](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202412021430542.png)

我们可以看到，`set`对其内部元素的迭代方式为中序遍历，所以打印出的数字是有序的。

![image-20241202143225924](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202412021432047.png)

```cpp
pair<iterator,bool> insert (const value_type& val);
iterator insert (iterator position, const value_type& val);	
template <class InputIterator>
  void insert (InputIterator first, InputIterator last);
```

我们可以看到，`insert`有三个重载版本。第一个是插入一个值，返回值先不看，最常用的就是这个，等会会说。第二个是指定一个迭代器位置进行插入，具有一定危险性，可能会破坏原先的搜索树结构。第三个是插入一段迭代器区间，也很少用。

```cpp
void test1()
{
	set<int> s;
	s.insert(6);
	s.insert(5);
	s.insert(2);
	s.insert(1);
	s.insert(1);
	s.insert(3);
	s.insert(2);
	s.insert(6);
	set<int>::iterator it = s.begin();
	while (it != s.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;
}
```

![image-20241202143950749](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202412021439850.png)

由于`set`中的元素都是唯一的，所以若要插入容器中已经存在的元素后，`insert`会无响应，并返回布尔类型为假的`pair`。

`pair`是一个模版类，被称之为键值对，其内部有两个元素，这两个元素具有一定的映射关系。`pair`的定义如下。

```cpp
template <class T1, class T2>
    struct pair
    {
        typedef T1 first_type;
        typedef T2 second_type;
        T1 first;
        T2 second;
        pair(): first(T1()), second(T2())
        {}
        pair(const T1& a, const T2& b): first(a), second(b)
        {}
    };
```

```cpp
void test1()
{
	set<int> s;

	pair<set<int>::iterator, bool> ret = s.insert(6);
	cout << ret.second << endl;

	s.insert(6);
	s.insert(5);
	s.insert(2);
	s.insert(1);
	s.insert(1);
	s.insert(3);
	s.insert(2);
	s.insert(6);

	ret = s.insert(6);
	cout << ret.second << endl;
	
	set<int>::iterator it = s.begin();
	while (it != s.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;
}
```

![image-20241202145554993](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202412021455115.png)

如果插入成功了，就返回真，失败就返回假。

接下来是`find`

```cpp
iterator find (const value_type& val) const;
```

返回的是迭代器，如果找到了，就返回对应的迭代器，如果找不到就返回`end`。

删除有三个重载版本

```cpp
void erase (iterator position);
size_type erase (const value_type& val);
void erase (iterator first, iterator last);
```

第一个就是直接用迭代器删除，第二个是用值删除，相当于先自己找一下，然后再删除，第三个是删除迭代器区间。

```cpp
void test1()
{
	set<int> s;

	pair<set<int>::iterator, bool> ret = s.insert(6);
	cout << ret.second << endl;

	s.insert(6);
	s.insert(5);
	s.insert(2);
	s.insert(1);
	s.insert(1);
	s.insert(3);
	s.insert(2);
	s.insert(6);

	ret = s.insert(6);
	cout << ret.second << endl;

	set<int>::iterator fd = s.find(6);
	if (fd != s.end())
		s.erase(fd);
	
	set<int>::iterator it = s.begin();
	while (it != s.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;

	s.erase(1);
	for (const auto& e : s)
		cout << e << " ";
	cout << endl;
}
```

![image-20241202151027385](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202412021510453.png)

注意，使用迭代器删除时，要确保迭代器是有效的，否则`erase`会崩溃。

第二个`erase`就是直接删除值的，其返回值`size_t`描述了删除的元素个数。如果容器里不存在这个值，那就返回0，为什么不用布尔作返回值呢？反正`set`中的元素是唯一的，这是为了和其它相关容器保持一致，稍后我们会说的。

除此之外，`set`的其它接口都很少使用，这里额外说一下`lower_bound`和`upper_bound`。如果参数在`set`中是存在的，那`lower_bound`返回的就是其迭代器，如果不存在，返回的就是下一序列的迭代器，或者说，返回最近大于参数元素的迭代器，`upper_bound`就是返回下一序列的迭代器，由于迭代器是左闭右开的，所以看上去就是把两个参数之间的，包括这两个参数本身(如果有的话)从容器中删除。

```cpp
void test2()
{
	std::set<int> myset;
	std::set<int>::iterator itlow, itup;

	for (int i = 1; i < 10; i++) myset.insert(i * 10); // 10 20 30 40 50 60 70 80 90

	itlow = myset.lower_bound(30);                //             ^
	itup = myset.upper_bound(60);                 //                         ^

	myset.erase(itlow, itup);                     // 10 20 70 80 90

	for (const auto& e : myset)
		cout << e << " ";
	cout << endl;
}
```

![image-20241202153049437](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202412021530555.png)

```cpp
void test2()
{
	std::set<int> myset;
	std::set<int>::iterator itlow, itup;

	for (int i = 1; i < 10; i++) myset.insert(i * 10); // 10 20 30 40 50 60 70 80 90

	itlow = myset.lower_bound(25);                //            ^
	itup = myset.upper_bound(65);                 //                         ^

	myset.erase(itlow, itup);                     // 10 20 70 80 90

	for (const auto& e : myset)
		cout << e << " ";
	cout << endl;
}
```

![image-20241202153152756](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202412021531855.png)

接下来来看看`equal_range`。

```cpp
pair<iterator,iterator> equal_range (const value_type& val) const;
```

`equal_range`返回一个键值对，该`pare`的两个成员都是迭代器，第一个成员是`>= val`的迭代器，第二个成员是`> val`的迭代器。

```cpp
void test3()
{
	std::set<int> myset;

	for (int i = 1; i <= 5; i++) myset.insert(i * 10);   // myset: 10 20 30 40 50

	std::pair<std::set<int>::const_iterator, std::set<int>::const_iterator> ret;
	ret = myset.equal_range(30);

	std::cout << "the lower bound points to: " << *ret.first << '\n';
	std::cout << "the upper bound points to: " << *ret.second << '\n';
}
```

![image-20241202155410279](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202412021554410.png)

```cpp
void test3()
{
	std::set<int> myset;

	for (int i = 1; i <= 5; i++) myset.insert(i * 10);   // myset: 10 20 30 40 50

	std::pair<std::set<int>::const_iterator, std::set<int>::const_iterator> ret;
	ret = myset.equal_range(35);

	std::cout << "the lower bound points to: " << *ret.first << '\n';
	std::cout << "the upper bound points to: " << *ret.second << '\n';
}
```

![image-20241202155453705](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202412021554823.png)

`count`用于返回容器内该值的个数，对于`set`来说，无非两种，`1`或者`0`，所以也有人把这个当做查找用，返回0那就是没有，返回1那就是有。

```cpp
size_type count (const value_type& val) const;
```

```cpp
void test1()
{
	set<int> s;

	pair<set<int>::iterator, bool> ret = s.insert(6);
	cout << ret.second << endl;

	if (s.count(6))
		cout << "6 in the container." << endl;
	else
		cout << "6 is not in the container." << endl;

	s.insert(6);
	s.insert(5);
	s.insert(2);
	s.insert(1);
	s.insert(1);
	s.insert(3);
	s.insert(2);
	s.insert(6);

	ret = s.insert(6);
	cout << ret.second << endl;

	set<int>::iterator fd = s.find(6);
	if (fd != s.end())
		s.erase(fd);

	if (s.count(6))
		cout << "6 in the container." << endl;
	else
		cout << "6 is not in the container." << endl;
	
	set<int>::iterator it = s.begin();
	while (it != s.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;

	s.erase(1);
	for (const auto& e : s)
		cout << e << " ";
	cout << endl;
}
```

![image-20241202160246647](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202412021602736.png)

最后要注意，`set`是`key`模型，所以其`key`不能被修改，体现就是迭代器解引用后不接受修改。

## [multiset](https://legacy.cplusplus.com/reference/set/multiset/)

![image-20241202160620850](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202412021606090.png)

`multi`是多种的意思，它与`set`基本相同。`multiset`和`set`的根本区别是，`multiset`允许多个等价的元素存储在容器中。

```cpp
namespace multiset_using
{
	void test1()
	{
		multiset<int> s;

		s.insert(6);
		s.insert(5);
		s.insert(2);
		s.insert(1);
		s.insert(1);
		s.insert(3);
		s.insert(2);
		s.insert(6);

		multiset<int>::iterator it = s.begin();
		while (it != s.end())
		{
			cout << *it << " ";
			++it;
		}
		cout << endl;
	}
}
```

![image-20241202161531743](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202412021615839.png)

当容器中已经有`value`了，就会在该`value`中序遍历的上一个或下一个位置插入新的`value`，习惯上，是插入到下一个位置。

![image-20241202162808129](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202412021628235.png)

![image-20241202162915039](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202412021629161.png)

迭代器返回的是最前面的（如果有的话）

```cpp
void test1()
{
	multiset<int> s;

	s.insert(6);
	s.insert(5);
	s.insert(2);
	s.insert(1);
	s.insert(1);
	s.insert(3);
	s.insert(2);
	s.insert(6);

	multiset<int>::iterator it = s.find(2);
	while (it != s.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;
}
```

![image-20241202163524654](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202412021635782.png)

接下来我们再来看看`equal_range`

```cpp
typedef std::multiset<int>::iterator It;
void test2()
{
	int myints[] = { 77,30,16,2,30,30 };
	std::multiset<int> mymultiset(myints, myints + 6);  // 2 16 30 30 30 77

	std::pair<It, It> ret = mymultiset.equal_range(30); //      ^        ^

	mymultiset.erase(ret.first, ret.second);

	for (const auto& e : mymultiset)
		cout << e << " ";
	cout << endl;
}
```

![image-20241202164015725](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202412021640867.png)

这样就可以获得一段迭代器区间，把所有的`val`全部删除。

`count`在`multiset`中用的更多，可以获知容器中某种元素的个数，`erase`也是如此。

```cpp
typedef std::multiset<int>::iterator It;
void test2()
{
	int myints[] = { 77,30,16,2,30,30 };
	std::multiset<int> mymultiset(myints, myints + 6);  // 2 16 30 30 30 77

	std::pair<It, It> ret = mymultiset.equal_range(30); //      ^        ^

	size_t count = mymultiset.erase(30);
	cout << count << endl;

	for (const auto& e : mymultiset)
		cout << e << " ";
	cout << endl;
}
```

此处可以知晓`erase`的删除个数。

![image-20241202164706039](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202412021647164.png)

## [map](https://legacy.cplusplus.com/reference/map/map/)

![image-20241202170627758](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202412021706969.png)

注意一下`value_type`，是一个键值对。

![image-20241202171032719](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202412021710804.png)

`value_type`是`pair<const key_type, mapped_type>`，那在插入的时候，理论上应该使用`pair<const key_type, mapped_type>`。比如

```cpp
namespace map_using
{
	void test1()
	{
		map<string, string> dict;
		dict.insert(pair<string, string> ("sort", "排序"));
	}
}
```

对于`map<string, string>`来说，其`value_type`应该是`pair<const string&, string>`，但我们看到`pair<string, string>`也是可以的，理论上不可以，因为很明显`pair<const string&, string>`和`pair<string, string>`不是同一类型，所以理论上是不能这样写的，但实际上是可以的，这涉及到`pair`的构造函数。

`pair`有三个构造函数

```cpp
pair();
template<class U, class V> pair (const pair<U,V>& pr);
pair (const first_type& a, const second_type& b);
```

第一个是空构造，第二个构造函数比较奇怪，第三个就是普普通通的有参构造，我们主要说第二个。

第二个构造函数长得像拷贝构造，实际上它确实是发挥了拷贝构造的功能，但除此之外，它也发挥着构造函数的功能。

在这里，`insert`输入的参数类型应该是`pair<const string&, string>`，但我们实际用的是`pair<string, string>`，类型对不上，所以这里就要构造出一个`pair<const string&, string>`，于是就会选用第二个构造函数。

```cpp
template<class U, class V> 
    pair (const pair<U,V>& pr)
    :first(pr.first)
    ,second(pr.second)
    {}

// 这里就相当于pair<const string&, string> pair(pair<string, string> ("sort", "排序"));
// 当然，实际没这种说法，但这种说法比较形象。insert使用的是新构造出的那个对象
```

这种机制使得插入的元素类型可以不用太过严格。

```cpp
void test1()
{
	map<string, string> dict;
	dict.insert(pair<string, string>("sort", "排序"));
	dict.insert(pair<const char*, string> ("insert", "插入"));

}
```

甚至可以这样

```cpp
void test1()
{
	map<string, string> dict;
	dict.insert(pair<string, string>("sort", "排序"));
	dict.insert(pair<const char*, string>("insert", "插入"));
	dict.insert(pair<const char*, const char*> ("left", "剩余"));

}
```

键值对的第一个成员不能修改，所以使用`const char*`可以理解，但第二个成员是可以修改的，怎么能也使用`const char*`呢？因为真正插入容器的根本不是`pair<const char*, const char*> ("left", "剩余")`，而是由此构造出的`pair<const string&, string> ("left", "剩余")`。

不过相较于提供一个匿名的`pair`对象，我们实际上用的更多的是`make_pair`。

```cpp
template <class T1,class T2>
    pair<T1,T2> make_pair (T1 x, T2 y)
{
    return ( pair<T1,T2>(x,y) );
}
```

这样只要提供参数就行了，不用给类型。

```cpp
void test1()
{
	map<string, string> dict;
	dict.insert(pair<string, string>("sort", "排序"));
	dict.insert(pair<const char*, string>("insert", "插入"));
	dict.insert(pair<const char*, const char*>("left", "剩余"));
	dict.insert(make_pair("right", "正确的"));
}
```

```cpp
void test1()
{
	map<string, string> dict;
	dict.insert(pair<string, string>("sort", "排序"));
	dict.insert(pair<const char*, string>("insert", "插入"));
	dict.insert(pair<const char*, const char*>("left", "剩余"));
	dict.insert(make_pair("right", "正确的"));

	map<string, string>::iterator it = dict.begin();
	while (it != dict.end())
	{
		cout << it->first << "::" << it->second << endl;
		++it;
	}
	cout << endl;
}
```

![image-20241202181001972](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202412021810110.png)

`map`的主要用途就是用来进行计数。

```cpp
void test2()
{
	// 统计水果出现的次数
	string arr[] = { "苹果", "西瓜", "苹果", "西瓜", "苹果", "苹果", "西瓜",
	"苹果", "香蕉", "苹果", "香蕉" };
	map<string, int> countMap;
	for (const auto& str : arr)
	{
		auto ret = countMap.find(str);
		if (ret == countMap.end())
			countMap.insert(make_pair(str, 1));
		else
			ret->second++;
	}

	for (const auto& e : countMap)
		cout << e.first << "::" << e.second << endl;
	cout << endl;
}
```

![image-20241202191642457](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202412021916537.png)

不过，真要计数的时候，一般这样写。

```cpp
void test2()
{
	// 统计水果出现的次数
	string arr[] = { "苹果", "西瓜", "苹果", "西瓜", "苹果", "苹果", "西瓜",
	"苹果", "香蕉", "苹果", "香蕉" };
	map<string, int> countMap;
	for (const auto& str : arr)
	{
		/*auto ret = countMap.find(str);
		if (ret == countMap.end())
			countMap.insert(make_pair(str, 1));
		else
			ret->second++;*/
		countMap[str]++;
	}

	for (const auto& e : countMap)
		cout << e.first << "::" << e.second << endl;
	cout << endl;
}
```

![image-20241202192303670](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202412021923737.png)

让我们来看看map中的operator[]

```cpp
// 调用这个函数等价于
mapped_type& operator[] (const key_type& k)
{
    return (*((this->insert(make_pair(k,mapped_type()))).first)).second;
}
// 可能不符合语法规则，但意思是到位的。
```

为此，我们需要看看`insert`

```cpp
pair<iterator,bool> insert (const value_type& val);
iterator insert (iterator position, const value_type& val);	
template <class InputIterator>
  void insert (InputIterator first, InputIterator last);
```

我们重点看第一个版本。在第一个版本中，`insert`返回一个键值对，该键值对的第一个成员是当前map类型对应的迭代器，如果原容器中没有等价的`key`，则第一个成员是新插入的键值对迭代器，如果原容器中存在等价的`key`，则插入失败，此时第一个成员是原先已经存在的键值对迭代器，第二个成员是布尔类型，当插入成功时，为真，否则为假。

首先来看`insert(make_pair(k,mapped_type())))`，很明显，这里用的是第一个`insert`，它试图插入一个键值对`make_pair(k,mapped_type()))`，如果`map`容器中之前没有`k`这个`key`，则就插入该键值对，注意该键值对的第二个成员是默认无参构造，对于`int`来说，其实就是0，如果`map`本来就有`k`这个`key`，则插入失败，`insert`无响应，无论是否插入成功，它所返回的键值对第一个成员都是`k`所对应元素的迭代器，之后再取该元素的第二个成员。

或者这样写

```cpp
mapped_type& operator[] (const key_type& k)
{
    pair<iterator, bool> ret = insert(make_pair(k, mapped_type()));
    return ret.first->second;
}
```

```cpp
void test1()
{
	map<string, string> dict;
	dict.insert(pair<string, string>("sort", "排序"));
	dict.insert(pair<const char*, string>("insert", "插入"));
	dict.insert(pair<const char*, const char*>("left", "剩余"));
	dict.insert(make_pair("right", "正确的"));

	dict["map"];           // 插入
	dict["map"] = "映射";  // 修改key映射的value

	map<string, string>::iterator it = dict.begin();
	while (it != dict.end())
	{
		cout << it->first << "::" << it->second << endl;
		++it;
	}
	cout << endl;
}
```

![image-20241202195950995](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202412021959319.png)

![image-20241202200035221](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202412022000273.png)

![image-20241202200124325](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202412022001765.png)

![image-20241202200200972](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202412022002026.png)

![image-20241202200218434](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202412022002874.png)

![image-20241202200234648](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202412022002701.png)

## [multimap](https://legacy.cplusplus.com/reference/map/multimap/)

![image-20241202200442987](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202412022004091.png)

multimap 不支持`[]`，也很好理解，多个`key`的时候到底返回谁的值，又是否要插入新的元素。

## example

### [TopK](https://leetcode.cn/problems/top-k-frequent-words)

![image-20241205160426136](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241205160426323.png)

我们先用`map`统计一下字符串的个数，由于`map`会自然而然地进行`key`比较，所以个数统计完后，`map`的中序遍历就是按照字典顺序排列的，但关键是我们想要的是频率最高的字符串，并且相同频率的字符串按照字典顺序排列，也就是说，我们的排序需要考虑到两个要素，首先是字符串的出现频率，其次是字符串本身的顺序。

这就为排序提出了要求，如果排序具有稳定性，那我们就可以直接比较键值对的第二个成员，就能得到一个符合题目要求的有序序列，不过我们要知道，键值对虽然也有比较重载，但它的比较都是依据第一个成员来说的，所以这意味这我们要自定义比较规则，也就是仿函数，随后再将其类型传入排序。而在算法库中，也确实含有稳定排序`stable_sort`

```cpp
class Solution {
public:

    struct less
    {
        bool operator()(const pair<string, int>& p1, const pair<const string, int>& p2)
        {
            if(p1.second > p2.second)
                return true;
            else
                return false;
        }
    };

    vector<string> topKFrequent(vector<string>& words, int k) {
        map<string, int> countMap;
        for(const auto& e : words)
        {
            countMap[e]++;
        }

        vector<pair<string, int>> sortV(countMap.begin(), countMap.end());

        stable_sort(sortV.begin(), sortV.end(), less());
        vector<string> ret;
        for(int i = 0; i < k; i++)
        {
            ret.push_back(sortV[i].first);
        }

        return ret;
    }
};
```

不过即使是非稳定排序，也可以通过丰富比较规则，而实现这里需要的排序。什么规则呢？首先看出现个数，个数多的频率高，所以要排在前面，如果个数相同，那么，字符串本身小谁就应该排在前面，于是就有了下面的代码

```cpp
class Solution {
public:
    struct less
    {
        bool operator()(const pair<string, int>& p1, const pair<string, int>& p2)
        {
            if(p1.second > p2.second || p1.second == p2.second && p1.first < p2.first)
                return true;
            else
                return false;
        }
    };
    vector<string> topKFrequent(vector<string>& words, int k) {
        map<string, int> hash;
        for(const auto& e : words)
        {
            hash[e]++;
        }

        vector<pair<string, int>> sortV(hash.begin(), hash.end());

        vector<string> ret;
        sort(sortV.begin(), sortV.end(), less());
        for(int i = 0; i < k; i++)
        {
            ret.push_back(sortV[i].first);
        }
        return ret;
    }
};
```

### [intersection-arrays](https://leetcode.cn/problems/intersection-of-two-arrays)

![image-20241205163108233](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241205163108309.png)

这个其实很简单，`set`过一遍然后比较一下就行了，可以对比较进行优化：如果都相等，那就直接保存，如果某个小，就让小的往后遍历。

```cpp
class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        set<int> s1(nums1.begin(), nums1.end());
        set<int> s2(nums2.begin(), nums2.end());
        auto it1 = s1.begin();
        auto it2 = s2.begin();
        vector<int> ret;
        while (it1 != s1.end() && it2 != s2.end()) {
            int e1 = *it1;
            int e2 = *it2;
            if (e1 == e2) {
                ret.push_back(e1);
                ++it1;
                ++it2;
            } else if (e1 < e2)
                ++it1;
            else
                ++it2;
        }
        return ret;
    }
};
```

# end