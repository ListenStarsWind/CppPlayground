[TOC]

# myVector

## `Feel`【感受】

### `documentation`[【文档】](https://cplusplus.com/reference/vector/vector/)

#### `Vector`【向量】

这些英文翻译完全有保留的价值, 但是我们就不再保存英文原文了, 而仅仅保存翻译后的, 连贯自然的中文.

`template < class T, class Alloc = allocator<T> > class vector; // generic template`告诉我们`vector`是一个类模版，它的模版参数有两个——一是数据类型`T`，二是空间配置器`Alloc`；空间配置器是用来进行内存管理的——通过内存池的方式(这话说的不对, 应该是让具体的空间操作与容器本身解耦合, 至于具体底层用什么方式, 我们不得而知)，内存池我们之后会专门去说，所以这次的`vector`实现我们都是直接`new delete`的。

`Vectors are sequence containers representing arrays that can change in size.`【vectos是用来表示大小可被修改数组（动态数组）的顺序容器】

`Just like arrays, vectors use contiguous storage locations for their elements, which means that their elements can also be accessed using offsets on regular pointers to its elements, and just as efficiently as in arrays. But unlike arrays, their size can change dynamically, with their storage being handled automatically by the container.`【就像数组一样，vectors使用连续的存储位置存放自己的元素，这意味着它们的元素也可以通过常规指针的偏移量来访问，这使得它们就像数组一样高效。与数组不同的是，它们的大小可以动态改变，其元素的存储可以交给容器自动处理】

`Internally`【在内部】，vectors`use`【通过】a`dynamically`【动态】`allocated`【分配】的`array`【数组】`to store`【去存储】`their elements`【自己的元素】。This array`may need`【可能需要】`reallocated`【重新分配内存】，`in order to`【以便于】`when new elements are inserted`【在插入新元素时】`grow in size`【增大大小】；`which implies `【这意味着】需要`allocating`【分配】a new array，`and`【并】将原有的all elements`moving`移入其中`it`。`In terms of processing time`【就处理时间而言】,this is a`relatively`【相对】`expensive`【昂贵】的`task`【任务】，`and thus`【因此】，`each`【每次】向`container`【容器】added an element`time`的时候，vectos `do not`【不都会】 `reallocate`【重新分配内存】。

`Instead`【例如】，vector`containers`【容器】may会`allocate`【分配】some `extra`【额外的】 `storage`【存储空间】,to `accommodate`【适应】`possible`【可能的】`growth`【增长】，`thus`【因此】，container的`actual capacity `【实际容量】 `may`【可能】会`greater`【大于】`strictly needed`【严格需要】`contain`【容纳】`its elements`【其元素】的`storage`【存储空间】大小。`Libraries`【库】 can `implemen`【实施】different` growth`【增长】`strategies`【策略】，for`memory usage`【内存使用】and`reallocations`【重新分配】`between`【之间】取得`balance`【平衡】。`but in any case`【但无论如何】，reallocations`should only happen at`【应仅在】`size`【大小】以` logarithmically`【对数方式】`growing`【增长】的`intervals`【间隔】发生，`so that`【以便于】在`individual`【单个】`elements`【元素】`insertion`【插入】时，can `provided`【提供】`constant `【常数】级别的`Amortized`【平均】`time complexity`【时间复杂度】,`see push_back`【详见push_back】——大小以对数方式增长：对于相同大小的空间，要减少扩容的次数，以减少将元素从原空间拷贝到新空间的频率，从而提升效率。

`Therefore`【因此】，`compared to arrays`【与数组相比】,vectos`consume`【消耗】`more`【更多】`memory`【内存】，`in an efficient way`【以更高效的方式】`exchange`【换取】，其在`manage storage`【存储管理】and `grow dynamically`【动态增长】方面的`ability`【能力】

与`other dynamic sequence containers`【其它动态序列容器】`deques, lists and forward_lists`【如双端队列、链表和前向链表】`Compared`【相比】，vectors 在随机`accessing`【访问】elements 方面 very `efficient`【高效】just like arrays，`and`【并且】在`end`【末尾】`adding or removing elements`【添加或删除元素】`relatively efficient`【相对高效】。对于在end`other`【以外】的`positions`【位置】adding or removing elements的`operations `【操作】，vectors的` perform`【性能】`worse than the others`【较差】，`and`【并且】相比`lists and forward_lists`【链表和向前链表】，vectors的`iterators and references`【迭代器和引用】的`consistent`【一致性】也表现较差。

#### `Container properties`【容器属性】

- `Sequence`【有序性】：`sequence containers`【序列容器】中的`Elements`【元素】，以`strict`【严格】的`linear`【线性】` ordered`【有序】方式排列，`Individual elements`【单个元素】`by`【通过】`their position in this sequence`【它们在序列中的位置】进行`accessed`【访问】
- `Dynamic array`【动态数组】：`even through`【即使】是通过`pointer arithmetics`【指针算数】的操作（比如`data`）,也`access`【允许】`direct`【直接】`Allows`【访问】`in the sequence`【序列中的】`any element`【任何元素】;`and`【并且】使得`at the end of the sequence`【在序列末尾】`addition/removal`【添加或删除】`elements`【元素】的操作具有`relatively fast `【较快的速度】
- `Allocator-aware`【分配感知器】：The container uses an allocator object to`dynamically`【动态地】`handle`【处理】`its storage needs`【其存储需求】

#### `Template parameters`【模版参数】

- T：`Type of the elements`【元素的类型】。当可以`guaranteed`【保证】【T】`while moving`【在移动期间】` not throw`【不抛出异常】，就能把vectors`reallocations`【重新分配】的`implementations`【实现】` optimize to`【优化为】`move elements`【移动元素】`instead of`【而不是】（以往的）`copying them`【复制元素】*详见《string_lesson2》::SGI版本string组织形式*。`member type`【成员类型】`vector::allocator_type`是T的`Aliased`【别名】(移动语义我们还没讲, 这里直接平铺直叙, 不需要再介绍移动语义了)

- `Alloc`【分配】：这是一个用于内存管理`allocator object`【分配器对象】的`type`【类型】，它为`storage allocation`【内存的分配与管理】提供了一个`model`【模型】。` By default`【在没有特别指定的情况下】，会使用默认的`allocator class template`【分配器类模版】，它实现了`Simplest`【最基本的】`memory allocation`【内存管理】功能；并且不依赖于`Value-independent`具体的数据（类型）；` member type`【成员类型】`vector::allocator_type`是它的`Aliased`【别名】

#### `Member types`【成员类型】

考虑到空间配置器与其对应的适配器讲起来需要很多背景知识, 并且有些背景知识我们还没有说过, 所以我们这里的文章视角是略过他们来看的, 这里的某些点, 如果直接看, 会令人疑惑, 比如, 引用或者常引用还有指针什么的, 是怎么取出来的, 我们要么说之后再说, 或者干脆不讲. 部分翻译需要调整, 我不清楚迭代器间隔类型这种翻译到底对不对.

| `member type`【成员类型】                | ` definition`【定义】                                                                                                              | ` notes`【注释】                                                                                |
| ---------------------------------------- | ---------------------------------------------------------------------------------------------------------------------------------- | ----------------------------------------------------------------------------------------------- |
| `value_type`【数据类型】                 | The first template parameter (`T`)                                                                                                 |                                                                                                 |
| `allocator_type`【分配器类型】           | The second template parameter (`Alloc`)                                                                                            | `defaults to`【默认】: `allocator<value_type>`                                                  |
| `reference`【引用】                      | allocator_type::reference                                                                                                          | for the default [allocator](https://legacy.cplusplus.com/allocator): ` value_type&`             |
| `const_reference`【常引用】              | allocator_type::const_reference                                                                                                    | for the default [allocator](https://legacy.cplusplus.com/allocator): `const value_type&`        |
| `pointer`【指针】                        | allocator_type::pointer                                                                                                            | or the default [allocator](https://legacy.cplusplus.com/allocator): `value_type*`               |
| `const_pointer`【常指针】                | allocator_type::const_pointer                                                                                                      | for the default [allocator](https://legacy.cplusplus.com/allocator): `const value_type*`        |
| `iterator`【迭代器】                     | a [random access iterator](https://legacy.cplusplus.com/RandomAccessIterator)【随机访问迭代器】 to `value_type`                    | `convertible to `【可转换为】`const_iterator`                                                   |
| `const_iterator`【常迭代器】             | a [random access iterator](https://legacy.cplusplus.com/RandomAccessIterator) to `const value_type`                                |                                                                                                 |
| `reverse_iterator`【反向迭代器】         | reverse_iterator\<iterator>                                                                                                        |                                                                                                 |
| `const_reverse_iterator`【反向常迭代器】 | reverse_iterator<const_iterator>                                                                                                   |                                                                                                 |
| `difference_type`【迭代器间隔类型】      | `a signed integral type`【一种有符号整数类型】, `identical to`【等同于】: `iterator_traits<iterator>::difference_type`             | `usually`【通常】 `the same as` [ptrdiff_t](https://legacy.cplusplus.com/ptrdiff_t)【与之相同】 |
| `size_type`【大小类型】                  | an `unsigned integral`【无符号整型】 type that can `represent`【表示】 `any non-negative value`【任何非负值】 of `difference_type` | usually the same as [size_t](https://legacy.cplusplus.com/size_t)                               |

#### `Member functions`【成员函数】

*已在《string_lesson1》::文档部分说过大致功能，在此不作赘述*

|                                                                                   |                                                        |
| --------------------------------------------------------------------------------- | ------------------------------------------------------ |
| [**(constructor)**](https://legacy.cplusplus.com/reference/vector/vector/vector/) | Construct vector (public member function )             |
| [**(destructor)**](https://legacy.cplusplus.com/reference/vector/vector/~vector/) | Vector destructor (public member function )            |
| [**operator=**](https://legacy.cplusplus.com/reference/vector/vector/operator=/)  | `Assign content`【内容赋值】 (public member function ) |

##### **Iterators**:

|                                                                                        |                                                                              |
| -------------------------------------------------------------------------------------- | ---------------------------------------------------------------------------- |
| [**begin**](https://legacy.cplusplus.com/reference/vector/vector/begin/)               | Return iterator to beginning (public member function )                       |
| [**end**](https://legacy.cplusplus.com/reference/vector/vector/end/)                   | Return iterator to end (public member function )                             |
| [**rbegin**](https://legacy.cplusplus.com/reference/vector/vector/rbegin/)             | Return reverse iterator to reverse beginning (public member function )       |
| [**rend**](https://legacy.cplusplus.com/reference/vector/vector/rend/)                 | Return reverse iterator to reverse end (public member function )             |
| [**cbegin** ](https://legacy.cplusplus.com/reference/vector/vector/cbegin/)【C++11】   | Return const_iterator to beginning (public member function )                 |
| [**cend** ](https://legacy.cplusplus.com/reference/vector/vector/cend/)【C++11】       | Return const_iterator to end (public member function )                       |
| [**crbegin** ](https://legacy.cplusplus.com/reference/vector/vector/crbegin/)【C++11】 | Return const_reverse_iterator to reverse beginning (public member function ) |
| [**crend** ](https://legacy.cplusplus.com/reference/vector/vector/crend/)【C++11】     | Return const_reverse_iterator to reverse end (public member function )       |

##### **Capacity**:

|                                                                                                    |                                                                            |
| -------------------------------------------------------------------------------------------------- | -------------------------------------------------------------------------- |
| [**size**](https://legacy.cplusplus.com/reference/vector/vector/size/)                             | Return size (public member function )                                      |
| [**max_size**](https://legacy.cplusplus.com/reference/vector/vector/max_size/)                     | Return maximum size (public member function )                              |
| [**resize**](https://legacy.cplusplus.com/reference/vector/vector/resize/)                         | `Change`【更改】 size (public member function )                            |
| [**capacity**](https://legacy.cplusplus.com/reference/vector/vector/capacity/)                     | Return size of allocated storage capacity (public member function )        |
| [**empty**](https://legacy.cplusplus.com/reference/vector/vector/empty/)                           | Test `whether`【是否】 vector is `empty`【为空】 (public member function ) |
| [**reserve**](https://legacy.cplusplus.com/reference/vector/vector/reserve/)                       | `Request`【请求】 a change in capacity (public member function )           |
| [**shrink_to_fit** ](https://legacy.cplusplus.com/reference/vector/vector/shrink_to_fit/)【C++11】 | `Shrink to fit` 【收缩以适应】(public member function )                    |

##### `Element access`【元素访问】:

|                                                                                               |                                                |
| --------------------------------------------------------------------------------------------- | ---------------------------------------------- |
| <a href="https://legacy.cplusplus.com/reference/vector/vector/operator[]/">**operator[]**</a> | Access element (public member function )       |
| [**at**](https://legacy.cplusplus.com/reference/vector/vector/at/)                            | Access element (public member function )       |
| [**front**](https://legacy.cplusplus.com/reference/vector/vector/front/)                      | Access first element (public member function ) |
| [**back**](https://legacy.cplusplus.com/reference/vector/vector/back/)                        | Access last element (public member function )  |
| [**data** ](https://legacy.cplusplus.com/reference/vector/vector/data/)【C++11】              | Access data (public member function )          |

##### `Modifiers`【修饰符】：

*emplace和emplace_back以后会专门说，现在先跳过。*

|                                                                                                  |                                                                            |
| ------------------------------------------------------------------------------------------------ | -------------------------------------------------------------------------- |
| [**assign**](https://legacy.cplusplus.com/reference/vector/vector/assign/)                       | `Assign`【赋值】 vector `content`【内容】 (public member function )        |
| [**push_back**](https://legacy.cplusplus.com/reference/vector/vector/push_back/)                 | Add element at the end (public member function )                           |
| [**pop_back**](https://legacy.cplusplus.com/reference/vector/vector/pop_back/)                   | Delete last element (public member function )                              |
| [**insert**](https://legacy.cplusplus.com/reference/vector/vector/insert/)                       | Insert elements (public member function )                                  |
| [**erase**](https://legacy.cplusplus.com/reference/vector/vector/erase/)                         | `Erase`【删除】 elements (public member function )                         |
| [**swap**](https://legacy.cplusplus.com/reference/vector/vector/swap/)                           | Swap content (public member function )                                     |
| [**clear**](https://legacy.cplusplus.com/reference/vector/vector/clear/)                         | `Clear`【清空】 content (public member function )                          |
| [**emplace** ](https://legacy.cplusplus.com/reference/vector/vector/emplace/)【C++11】           | `Construct`【构造】 and `insert`【插入】 element (public member function ) |
| [**emplace_back** ](https://legacy.cplusplus.com/reference/vector/vector/emplace_back/)【C++11】 | Construct and insert element at the end (public member function )          |

##### **Allocator**:

|                                                                                          |                                         |
| ---------------------------------------------------------------------------------------- | --------------------------------------- |
| [**get_allocator**](https://legacy.cplusplus.com/reference/vector/vector/get_allocator/) | Get allocator (public member function ) |

#### `Non-member function overloads`【非成员函数重载】

|                                                                                             |                                                                      |
| ------------------------------------------------------------------------------------------- | -------------------------------------------------------------------- |
| [**relational operators**](https://legacy.cplusplus.com/reference/vector/vector/operators/) | `Relational operators`【关系运算符】 for vector (function template ) |
| [**swap**](https://legacy.cplusplus.com/reference/vector/vector/swap-free/)                 | `Exchange contents`【交换内容】 of vectors (function template )      |

#### `Template specializations`【模版的特别实例化】

*为了满足某些特别的需求，特别实现的vector版本，就像通用交换模版和容器内交换函数的关系。*

|                                                                                 |                                                 |
| ------------------------------------------------------------------------------- | ----------------------------------------------- |
| [**vector\<bool>**](https://legacy.cplusplus.com/reference/vector/vector-bool/) | Vector of bool (class template specialization ) |

### `using`【使用】

```cpp
#include<vector>
#include<string>
#include<iostream>

// construct https://legacy.cplusplus.com/reference/vector/vector/vector/
void using1()
{
    // 这注释是错误的, 缺省空间分配器效率应该是较高的
    // 这里的"自己实现"我猜测当时可能是想要表示用内存池
    // 但内存池并不是完全负责解决效率问题的
	// 如果觉得缺省分配器的效率较低，可以自
	// 己实现一个，然后传给参数`alloc`

	// 基本构造
	std::vector<int> v1;

	// 将其中10个元素全部初始化为0
	std::vector<int> v2(10, 0);

	// 使用容器的迭代器区间进行初始化
	std::vector<int> v3(v2.begin(), v2.end());
	std::string s("hello world");
	std::vector<char> v4(s.begin(), s.end());
	
	// 类型强转 char·ASCII码形式 -> int
	std::vector<int> v5(s.begin(), s.end());

	// 构造一个二维数组
	std::vector<std::vector<int>> v;
	v.push_back(v1);
	v.push_back(v2);
	v.push_back(v3);
	v.push_back(v5);


	// 遍历

	// 下标
	size_t begin = 0;
	for (; begin < v5.size(); begin++)
	{
		std::cout << v5[begin] << " ";
	}
	std::cout << std::endl;

	// 迭代器
	std::vector<char>::iterator it = v4.begin();
	while (it != v4.end())
	{
		std::cout << *it;
		++it;
	}
	std::cout << std::endl;

	// 范围for
	for (auto& n : v5)
	{
		std::cout << ++n << " ";
	}
	std::cout<<std::endl;
}
```

这是新的代码(在处理新旧代码时, 应该尽可能融合, 最后只写一份代码, 而不是分别孤立地写到文章中)

```cpp
#include <iostream>
#include <string>
#include <vector>

#include "allocator.hpp"

// 模板重命名
template <class T>
using vector = std::vector<T, wind::allocator<T>>;

int main() {
    // 基本无参构造
    vector<int> v1;

    // 定义10个元素, 并将其都初始化为0
    vector<int> v2(10, 0);

    // 使用容器的迭代器区间进行初始化
    vector<int> v3(v2.begin(), v2.end());
    std::string s("Hello World!");
    vector<char> v4(s.begin(), s.end());

    // 类型强转 char ASCII 码形式 -> int
    vector<int> v5(s.begin(), s.end());

    // 构造一个二维数组
    vector<vector<int>> v;
    v.push_back(v1);
    v.push_back(v2);
    v.push_back(v3);
    v.push_back(v5);

    // 遍历

    // 下标
    size_t begin = 0;
    for (; begin < v5.size(); begin++) {
        std::cout << v5[begin] << " ";
    }
    std::cout << std::endl;

    // 迭代器
    vector<char>::iterator it = v4.begin();
    while (it != v4.end()) {
        std::cout << *it;
        ++it;
    }
    std::cout << std::endl;

    // 范围for
    for (auto& n : v5) {
        std::cout << ++n << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

和对应的运行结果

```bash
[wind@ubuntu-asus build]$ ./main-debug
72 101 108 108 111 32 87 111 114 108 100 33 
Hello World!
73 102 109 109 112 33 88 112 115 109 101 34 
[wind@ubuntu-asus build]$ 
```

------------

```cpp
// P.J.vector`storage allocation mechanism`【内存分配机制】
void using2()
{
	size_t sz;
	std::vector<int> v;
	sz = v.capacity();
	std::cout << "making v grow:\n";
	for (int i = 0; i < 100; ++i)
	{
		v.push_back(i);
		if (sz != v.capacity())
		{
			sz = v.capacity();
			std::cout << "capacity changed: " << sz << '\n';
		}
	}
}
```

![image-20241023111438888](https://img.mdwind.online/md/202410231114993.png)

这是后来重复的实验, 只不过用了code做前端, MSCV 工具链做后端, 跳过了 VS

```cpp
#include <iostream>
#include <vector>

int main() {
    size_t sz;
    std::vector<int> v;
    sz = v.capacity();
    std::cout << "vector 的内存增长:\n";
    for (int i = 0; i < 100; ++i) {
        v.push_back(i);
        if (sz != v.capacity()) {
            sz = v.capacity();
            std::cout << "容量变化: " << sz << '\n';
        }
    }
    return 0;
}
```

看来VS迭代(上图是2022, 这是2026的工具链)没有在这方面造成影响

```bash
[wind@star-field build]$ ./main-debug.exe 
vector 的内存增长:
容量变化: 1
容量变化: 2
容量变化: 3
容量变化: 4
容量变化: 6
容量变化: 9
容量变化: 13
容量变化: 19
容量变化: 28
容量变化: 42
容量变化: 63
容量变化: 94
容量变化: 141
[wind@star-field build]$ 
```

之后是 clang 的

```bash
[wind@ubuntu-asus build]$ ./main-debug
vector 的内存增长:
容量变化: 1
容量变化: 2
容量变化: 4
容量变化: 8
容量变化: 16
容量变化: 32
容量变化: 64
容量变化: 128
[wind@ubuntu-asus build]$ 
```

```cpp
#include<vector>
#include<iostream>

// SGI vector storage allocation mechanism
int main()
{
  size_t sz;
  std::vector<int> v;
  sz = v.capacity();
  std::cout << "making v grow:\n";
  for (int i = 0; i < 100; ++i)
  {
	  v.push_back(i);
	  if (sz != v.capacity())
	  {
		  sz = v.capacity();
		  std::cout << "capacity changed: " << sz << '\n';
	  }
  }
  return 0;
}
```

```shell
[wind@starry-sky myVector]$ g++ main.cpp -o out
[wind@starry-sky myVector]$ ./out
making v grow:
capacity changed: 1
capacity changed: 2
capacity changed: 4
capacity changed: 8
capacity changed: 16
capacity changed: 32
capacity changed: 64
capacity changed: 128
```

### `example`【例题】

#### [二叉树的前序遍历](https://leetcode.cn/problems/binary-tree-preorder-traversal/)

先让我们回顾一下——《链式二叉树——初级》::README.md::前序遍历

![image-20241023105048189](https://img.mdwind.online/md/202410231050612.png)

```c
int BTSize(struct TreeNode* root)
{
    if(root == NULL)
    return 0;
    return BTSize(root->left) + BTSize(root->right) + 1;
}

void _preorderTraversal(struct TreeNode* root, int** pCurrent)
{
	if (root == NULL)
		return;
	int* p = *pCurrent;
	(*pCurrent)++;
	p[0] = root->val;
	_preorderTraversal(root->left, pCurrent);
	_preorderTraversal(root->right, pCurrent);
}

int* preorderTraversal(struct TreeNode* root, int* returnSize) {
	*returnSize = BTSize(root);
	int* pArray = (int*)malloc(*returnSize * sizeof(int));
	int* ret = pArray;
	int** pCurrent = &pArray;
	_preorderTraversal(root, pCurrent);
	return ret;
}
```

为了确定动态开辟数组的大小，我们先求出了二叉树的节点个数，然后通过二级指针的方式控制数据的写入。

而现在, 因为 vector 是动态的, 所以前序遍历和插入可以并行进行

:::comment
这个例子并不好, 就目前来说, 我推测这个例子的意图可能是突出 vector 可以自己扩容的特点.. 但是就目前来说, 我是跨过 C 的数据结构直接写 C++数据结构的, 所以对于读者来说, 我之前没写过这个文章, 这里的接口形式应该是力扣风格, 输出参数返回数组大小, 返回值返回数组, 变成 C++ 只返回 vector 就行. 这还有语言间的差别.
:::

```cpp
class Solution {
public:
    void _preorderTraversal(TreeNode* root, vector<int>& Container) {
        if (root == nullptr)
            return;
        else
            Container.push_back(root->val);
        _preorderTraversal(root->left, Container);
        _preorderTraversal(root->right, Container);
    }

    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> v;
        _preorderTraversal(root, v);
        return v;
    }
};
```

#### [只出现一次的数字](https://leetcode.cn/problems/single-number/)

这没什么好说的，就是异或，我之前好像写过[进阶版本](https://leetcode.cn/problems/shu-zu-zhong-shu-zi-chu-xian-de-ci-shu-lcof)，我把这个进阶版叫做《找两个单身狗》。

```cpp
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int val = 0;
        for(auto curr : nums)
        {
            val ^= curr;
        }
        return val;
    }
};
```

#### [杨辉三角](https://leetcode.cn/problems/pascals-triangle)

这题如果用C的话，首先要建立一个二维数组：先建立一个指针数组array<int*>【这里用模版的方式表述一下】，然后再建立多个普通数组array\<int>，再把普通数组的首元素地址写入指针数组中，于是一个二维数组就建立完成了。因为要使用二维数组作容器，所以返回的是二级指针，又为了对二维数组进行遍历，所以需要`returnSize`and`returnColumnSizes`描述一下行和列，`*returnSize`实际就应该被赋值为`numRows`，`returnColumnSizes`则是一个一维数组的指针，他让你通过操作这个一维数组描述每一行有多少个元素。

用C++的话，就可以直接`vector<vector<int>>`，这样就可以直接建立一个二维数组，而且它的空间分配不用我们操心。C如果要访问二维数组就要连着解引用了，C++其实底层也是解引用，但对于用户来说，直接`[]`重载就行了。

我们首先通过`resize`为二维数组进行初始化，由于我们没有输入第二个参数，所以第二个参数实际上就是缺省值，根据文档，如果元素类型为自定义类型，就会调用它的默认构造函数，然后它的默认构造是使用分配器的，分配器还没学所以就不继续深究了(这里可能是在指空间配置器)，但我们现在可以大致猜一下，应该是空的vector\<int>。经过`resize`操作之后，vector<vector\<int>> v就有了`numRows`个元素，这样就已经搭好了二维数组的基本框架。

接下来我们对vector\<vector\<int>>中的每一个vector\<int>元素再进行初始化，观察杨辉三角，我们发现每一行的元素个数等于其所在行数：第一行有一个数，第二行有两个数，第三行有三个数······但要注意的是，我们是使用下标访问vector\<vector\<int>>的每个元素的，而下表是从0开始，所以要加一。因为这次我们还是没有输入第二个参数，所以它会使用缺省值，虽然文档没有具体说，但大概可以认为是(int)0。此时的缺省值其实就起到了占位符的作用，这使得我们可以直接通过`[]`重载访问二维数组中的int元素；然后我们看到每行的首尾数字都是1，所以此时就顺手修改一下。

接下来进行最后一次遍历，观察杨辉三角，我们发现，除去首尾的数字之外，其它的数字都是上一行同下标的数字与上一下标的数字相加得到的，比如第三行的第二个数字2【下标为1】，它就是第二行的第二个数字【下标为1】和第二行的第一个数字【下标为0】相加得到的。

最后别忘了返回。

```cpp
class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> v;
        v.resize(numRows);
        int i = 0, j = 0;
        for (; i < v.size(); i++) {
            v[i].resize(i + 1);
            v[i][0] = 1;
            v[i][i] = 1;
        }
        for (i = 0; i < v.size(); i++) {
            for (j = 0; j < v[i].size(); j++) {
                if (v[i][j] != 1) {
                    v[i][j] = v[i - 1][j] + v[i - 1][j - 1];
                }
            }
        }
        return v;
    }
};
```

## `realization`【实现】

我们先去瞅瞅源代码，在\<vector>头文件中，只有寥寥数十行：

![image-20241023171844217](https://img.mdwind.online/md/202410231718830.png)

我们真正要看的内容，估计在\<stl_vector.h>里：

建议把`STL`的文件夹直接用VS打开，这样方便显示。

比如，如果直接把\<stl_vector.h>扔到某个项目里，那它就是杂项文件，有些东西看不到：

你看它无法识别这个宏：

![image-20241023172916746](https://img.mdwind.online/md/202410231729217.png)

但如果直接打开文件夹，就能看到了：

![image-20241023173002384](https://img.mdwind.online/md/202410231730430.png)

![image-20241023173046680](https://img.mdwind.online/md/202410231730771.png)

`gcc-master`是我直接从github上拷下来的源代码，但太新了，看原码要看旧的，新的版本封装得比较好，所以可读性低。

由于它们都在同一个文件夹下，所以就可以识别了：

![image-20241023173418296](https://img.mdwind.online/md/202410231734752.png)

![image-20241023173456452](https://img.mdwind.online/md/202410231734836.png)

这样就可以看到了，这实际是命名空间。命名空间不是关键内容，那就跳过。什么是关键内容，比如成员变量就是关键内容，还有什么构造插入什么的，这才是体现代码核心逻辑的地方：

![image-20241023174115364](https://img.mdwind.online/md/202410231741813.png)

这个就是我们的成员变量，是三个指针。大致可以猜出它们三个是干什么的：`_M_start`可能是存储元素空间的起始地址，其它两个应该一个是最后一个有效元素的下一元素地址，一个是存储空间末元素下一元素的地址。从名字上来看，`_M_end_of_storage`应该是存储空间的末尾地址，这样的话，`_M_finish`应该是有效元素的末尾。

接下来就是找成员函数去确认一下猜想，比如从`begin`and`end`，`size`，`capacity`大致可以证明我们的猜想：

![image-20241023182919380](https://img.mdwind.online/md/202410231829059.png)

首先为了和标准库中的`vector`作区分，我们把整个模版包进我们自己的命名域中，对于我个人而言，我的英文名一般是`wind`，所以我就用这个名字做命名域的名字啦。之后，我们把模版类型`T`包装一下，把它的指针重命名为迭代器，为了适应常对象，我们又添加了常迭代器。注意，迭代器在类外也是要能被使用的，所以一定要放在公共区中，别放私有里了。

:::comment
```cpp
#pragma once

#include <type_traits>

#include "allocator.hpp"
#include "allocator_traits.hpp"

namespace wind {
template <class T, class Alloc = wind::allocator<T>>
    requires(std::is_object_v<T>)  // 约束: 这应该是个对象类型, 而不是引用, 函数什么其他类型
class vector {
   public:
    using value_type = T;
    using allocator_type = Alloc;

   private:
    using allocator_traits_type = wind::allocator_traits<allocator_type>;

    static_assert(std::is_same_v<value_type, typename allocator_traits_type::value_type>,
                  "wind::vector: allocator_traits value_type must match T");

   public:
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = typename allocator_traits_type::pointer;
    using const_pointer = typename allocator_traits_type::const_pointer;
    using iterator = pointer;
    using const_iterator = const_pointer;
    using difference_type = typename allocator_traits_type::difference_type;
    using size_type = typename allocator_traits_type::size_type;

    private:

};
}  // namespace wind
```

让我们来看看类型接口, 以往我们说的接口往往是指函数接口, 但现在我们可以吧接口的概念在进行扩宽, 能取出来什么类型, 同样是一个类的重要行为, 并且, 这种特性的激发不需要依赖于某个已经存在的对象或者静态成员, 只要接口公开了, 我们就可以随时随地的取出他们, 这使得他们在某些场景下发挥着独特的作用, 但是今天我们就不讨论他们了, 在这里, 由于我写了一个实验性质的空间配置器及其对应的适配器, 所以部分类型我直接通过取适配器的类型接口的这种方式获得, 如果你们想要实现 vector, 就直接以 T 为基础定义这些类型就好了, 值得注意的是, 其中的两个引用类型在不同的 C++ 标准中有所差异, 在 C++11 之前, 两个引用类型一般还是从空间配置适配器`allocator_traits_type`类型中取出来, 但在那之后, 适配器对这一公开接口不再做要求, 所以变成了继续使用 value_type. 另外我们还增加了一处静态断言, 用来在编译期检查空间配置适配器中取出的核心数据类型是否和T相同, 如果不相同, 肯定有问题, 那我们就直接报错.

这里应该以旁注的形式简要的插入有关容器, 空间配置适配器, 空间配置器之间的分层关系, 就像我之前说的, 考虑到空间配置器及其对应的适配器利用了很多C++ 的各类知识, 而且用的很灵活, 所以在这篇文章的视角定为是略过他们来实现 vector, 但我们也不能完全不讲, 所以这里应该稍微画张图片, 用图片的方式简要描述他们之间的关系, 特别是这些类型接口, 他们有的是从空间配置器里面一路取出来的, 有些可能是空间配置器没有提供, 依靠适配器适应自己想办法配出来的

这里我用适配器只是写着玩, 你们不需要在意, 为了便于理解, 下表解构了这些封装, 提供一个确切的类型(假设T为int)

## `wind::vector` **类型封装关系**

| 类型别名                | 定义来源                                 | 展开后的具体类型                               | 说明                                                 |
| ----------------------- | ---------------------------------------- | ---------------------------------------------- | ---------------------------------------------------- |
| `value_type`            | `T`                                      | `int`                                          | 容器存储的元素类型                                   |
| `allocator_type`        | `Alloc`                                  | `wind::allocator<int>`                         | 容器使用的空间配置器类型                             |
| `allocator_traits_type` | `wind::allocator_traits<allocator_type>` | `wind::allocator_traits<wind::allocator<int>>` | 配置器适配器，统一提供类型及操作接口                 |
| `reference`             | `value_type&`                            | `int&`                                         | 元素的可修改左值引用                                 |
| `const_reference`       | `const value_type&`                      | `const int&`                                   | 元素的只读左值引用                                   |
| `pointer`               | `allocator_traits_type::pointer`         | `int*`                                         | 默认配置器提供原始指针；自定义配置器可能提供花式指针 |
| `const_pointer`         | `allocator_traits_type::const_pointer`   | `const int*`                                   | 指向只读元素的指针类型                               |
| `iterator`              | `pointer`                                | `int*`                                         | 当前实现直接将指针作为迭代器                         |
| `const_iterator`        | `const_pointer`                          | `const int*`                                   | 当前实现使用指向只读元素的指针作为迭代器             |
| `difference_type`       | `allocator_traits_type::difference_type` | `std::ptrdiff_t`                               | 表示迭代器之间的距离，可为负数                       |
| `size_type`             | `allocator_traits_type::size_type`       | `std::size_t`                                  | 表示容器大小、容量及元素数量                         |
:::

接下来, 我们依据之前看的源码, 给 vector 加上三个私有的成员

![](https://img.mdwind.online/img/20261113171525485.png)

![](https://img.mdwind.online/img/20261113171750544.png)

还有第四个私有成员--空间配置器对象, 负责与适配器配合执行各类任务, 如果是直接用 new, delete来操作, 则完全不需要他.

```cpp
namespace wind {
	template<class T>
	class vector {
	public:
		typedef T* iterator;
		typedef const T* const_iterator;

	private:
		iterator _start = nullptr;
		iterator _finish = nullptr;
		iterator _endofstarage = nullptr;
	};
}// 这是历史写法, 我对这种用迭代器做类型声明的写法感觉非常不妥, 应该就用指针
```

之后我们先写一个基本的默认构造函数，其它构造函数先不写，因为它们有坑，过一会再写。由于这是模版，所以定义和声明不能分离，分离会出问题的，所以我们的定义就写在这个文件中。之后，重复的内容我就会省略了。

```cpp
namespace wind {
    template<class T>
        class vector {
            public:
            typedef T* iterator;
            typedef const T* const_iterator;

            vector()
                :_start(nullptr)
                , _finish(nullptr)
                , _endofstarage(nullptr)
                {}

            private:
            iterator _start = nullptr;
            iterator _finish = nullptr;
            iterator _endofstarage = nullptr;
        };
}
```

这默认构造看起来什么都不干，只是把成员变量初始化为空指针而已，而且我们也看到声明中的成员变量是写了缺省值的，这样的话，其实不写初始化列表，直接写成`vector{}`就行了，不过，由于我是把`vector`基本写完之后才写上声明缺省值的，也就是说，在我写这些构造函数的时候，还没有缺省值，所以这里给出的代码都是有初始化列表的。那现在问题来了，既然编译器自己能生成默认构造函数，能不能直接不写呢？就目前来说，是可以的，因为编译器的逻辑是当用户一个默认构造函数也不写的时候，编译器才会兜底，自己实现一个，但我们过会儿要写其它构造函数，编译器看到用户写构造函数了，就不会自己生成了，此时若我们省略`vector{}`，那我们的`vector`就没有默认构造了，所以还是保留最好。

由于我们还未系统地学习内存池，所以在我们的`vector`中，内存都是直接使用`new delete`进行管理的。

```cpp
~vector() {
	delete[] _start;
	_start = _finish = _endofstarage = nullptr;
}
```

(now)现在我们先不着急实现析构函数, 我们可以先把那些表示容器状态的函数接口给写上去

接下来我们实现一下`size  capacity  begin  end  empty`函数，注意这些函数都没有修改成员变量，为了适配常对象，它们都要有对应的`const`版本

```cpp
size_t size() {
	return _finish - _start;
}

size_t capacity() {
	return _endofstarage - _start;
}

size_t size()const {
	return _finish - _start;
}

size_t capacity()const {
	return _endofstarage - _start;
}

iterator begin() {
	return _start;
}

iterator end() {
	return _finish;
}

const_iterator begin()const {
	return _start;
}

const_iterator end()const {
	return _finish;
}

bool empty() {
	if (begin() == end())
		return true;
	else
		return false;
}

bool empty()const {
	if (begin() == end())
		return true;
	else
		return false;
}
```

接下来我们写一下`push_back`吧，很明显`push_back`很可能涉及到扩容，所以我们先写`reserve`

```cpp
/*void reserve(size_t newCapacity) {
	if (newCapacity > capacity()) {
		size_t oldSize = size();
		iterator ptr = new T[newCapacity];
		memcpy(ptr, _start, sizeof(T) * oldSize);
		delete[] _start;
		_start = ptr;
		_finish = _start + oldSize;
		_endofstarage = _start + newCapacity;
	}
}*/
```

`reserve`中文译作“后备”，后备，也就是扩容，所以我们首先加了参数判断，如果目标大小小于等于当前容量，就不进行任何操作，文档上也说了，`reserve`对容量的调整是一种请求，而不是命令，如果输入参数小于当前容量，`reserve`可以出于提升效率的考虑（因为扩容要异地扩容）不执行请求。

再把数据从旧空间拷贝到新空间，之后通过一系列指针操作，让`vector`对象与新空间建立联系；由于要改动指针，而`size  capacity`它们都是通过指针运算得到结果的，为了避免指针操作之后干扰`size capacity`的计算，在对指针进行修改之前，先存一下之前的大小，然后再依据`oldSize`调整`_finish`。

为什么被注释掉了呢？因为`reserve`涉及到`vector`的第一个大坑，我们先将就用，把`push_back`实现，然后演示一下问题。

```cpp
void push_back(const T& val) {
	if (size() == capacity()) {
		size_t newCapacity = capacity() * 2;
		if (empty()) {
			newCapacity = 4;
		}
		reserve(newCapacity);
	}
	*_finish = val;
	++_finish;
}
```

`push_back`，若空间不够，就去扩容，为了避免容量大小为0导致乘二失效，所以当对象为空时，需修正扩容大小。

接下来我们看看问题：（此处的`insert`是正确的）如果自己实现的`insert`崩溃请往下看

```cpp
void realization3()
{
	wind::vector<std::string> str_arry;
	auto& v = str_arry;
	v.push_back("1111");
	v.push_back("11111111111111111111111111");
	v.push_back("xxxxxxxxxxxxxxxxxxxxxxxxxx");
	v.push_back("11111111111111111111111111");
	wind::vector<std::string>::iterator it = v.end();
	v.insert(it, "hello word");
	for (auto m : v)
	{
		std::cout<<m<<std::endl;
	}
}
```

![image-20241025151637581](https://img.mdwind.online/md/202410251516740.png)

问题出在`reserve`上，`reserve`是一种深层次的浅拷贝，这种浅拷贝藏得很深，第一次写不一定能想到，我们在`reserve`中使用的是`memcpy`进行拷贝，`memcpy`只拷贝对象本体，而不拷贝与对象联系内存块中的数据。

![image-20241025084603788](https://img.mdwind.online/md/202410250846886.png)

![image-20241025085019556](https://img.mdwind.online/md/202410250850708.png)

![image-20241025085315439](https://img.mdwind.online/md/202410250853574.png)

delete会先调用析构函数，然后再释放内存，于是新拷贝的对象所指向的内存块中的数据被析构，并被释放，所以打印出了乱码。那为什么第一个没事呢？因为标准库中的string对象还有一个静态数组`buff`，这个数组就在对象中，当字符个数小于16时，string会使用`buff`作为字符的承载容器，当字符个数过多时，才会动态开辟内存。

此时就能体现上节课《string_lesson2》中所说的“引用计数”的好处了，当使用“引用计数时”，只要不修改对象，那就不用深拷贝，同样内容对象共用一处动态开辟的空间，析构时也不直接析构，而是先看看这个内存块还有没有对象使用，没有时才真析构。

不过我们用的不是引用计数所以只能深拷贝了，之后我们会学一个叫“移动构造”的语法，它能缓解一下效率问题，不过作为初学者，那就不用考虑效率了。

下面有两种写法，它们本质都是一样的，只是表现方式不同。

```cpp
//void reserve(size_t newCapacity) {
//	if (newCapacity > capacity()) {
//		size_t oldSize = size();
//		iterator ptr = new T[newCapacity];
//		iterator constructor = ptr;
//		for (auto& v : *this) {
//			// 使用构造函数构造
//			new(constructor) T(v);
//			++constructor;
//		}
//		delete[] _start;
//		_start = ptr;
//		_finish = _start + oldSize;
//		_endofstarage = _start + newCapacity;
//	}
//}

void reserve(size_t newCapacity) {
	if (newCapacity > capacity()) {
		const size_t oldSize = size();
		iterator ptr = new T[newCapacity];
		for (size_t transport = 0; transport < oldSize; transport++) {
			// 使用operator=重载深拷贝
			ptr[transport] = _start[transport];
		}
		delete[] _start;
		_start = ptr;
		_finish = _start + oldSize;
		_endofstarage = _start + newCapacity;
	}
}
```

![image-20241025160138382](https://img.mdwind.online/md/202410251601470.png)

上面的 reserve 及其配套文字都是历史版本, 现在我们看点厉害的现在版本

```cpp
void reserve(size_type minCapacity) {
        // 取出适配器提供的最大数目, 作为检查的判断依据
        const size_type maxCapacity = allocator_traits_type::max_size(_alloc);

        if (minCapacity > maxCapacity) throw std::length_error("wind::vector::reserve");

        size_type oldSize = size();
        size_type oldCapacity = capacity();

        if (oldCapacity >= minCapacity) return;

        // 小于等于1时, 为了避免 / 2 仍旧为0, 预选容量定为4
        size_type increment = oldCapacity <= 1 ? 4 : oldCapacity / 2;
        // 对当前容量进行审议, 在确保加上0.5不超过上限情况下才加上0.5
        // 但 maxCapacity 极小时, 4 可能会大于它, 造成 increment 大于上限的情况
        // 所以 increment 不能参与加减计算
        size_type newCapacity =
            increment >= maxCapacity - oldCapacity ? maxCapacity : oldCapacity + increment;

        newCapacity = std::max(newCapacity, minCapacity);
        pointer ptr = allocator_traits_type::allocate(_alloc, newCapacity);
        pointer curr = ptr;

        size_type idx = 0;
        try {
            for (; idx < oldSize; idx++) {
                // 使用原来的对象参与新对象的构造
                // std::move_if_noexcept: 如果移动语义构造保证不抛异常, 则转为右值, 匹配移动语义构造
                // 移动构造可能抛异常且允许拷贝时，优先使用拷贝构造,不支持拷贝构造时，仍然尝试移动
                allocator_traits_type::construct(_alloc, curr + idx,
                                                 std::move_if_noexcept(_start[idx]));
            }
        } catch (...) {
            // 如果中途拷贝构造抛出异常, 析构之前已经成功构造的新元素, 并释放新空间
            size_type firefighter = 0;
            for (; firefighter < idx; firefighter++) {
                allocator_traits_type::destroy(_alloc, curr + firefighter);
            }
            allocator_traits_type::deallocate(_alloc, ptr, newCapacity);
            // 向上交接异常
            throw;
        }

        // 为了能够进行回退, 我们必须在新元素全部构造完成之后, 再析构原先对应的旧元素
        for (idx = 0; idx < oldSize; idx++) {
            allocator_traits_type::destroy(_alloc, _start + idx);
        }
        // 释放原先的旧空间(在他们确实存在的情况下)
        if (_start != nullptr) {
            allocator_traits_type::deallocate(_alloc, _start, oldCapacity);
        }

        // 三指针进行状态更新
        _start = ptr;
        _finish = ptr + oldSize;
        _endofstorage = _start + newCapacity;
        return;
    }
```

我不清楚这种代码能不能交给读者, 对于初学者来说,它可能是十分复杂的, 并且还涉及到我们还没有系统说, 但是已经用过几次的异常体系, 还有移动语义, 我是之前完全没说过, 原先打算之后系统再说的, 所以我们需要把握好写文章的度

第一个较为难理解的, 可能就是有关新容量的审议逻辑--因为某些原因(比如类型的数据范围, 这里就是, 但是可能还有其他原因, 所以我在注释中使用的是"上限"而非防溢出, 没有在具体原因的层面去说), 我们对于新空间的大小申请(大小是以元素单位来计量的), 存在一个上限, 在此之前我们已经对最小容量参数进行了检查, 如果不通过, 会直接抛异常. 而现在我们要做的是按照1.5的系数基础进行扩容, 这里为了防止乘上1.5导致超出上限, 所以我们先除以2, 获得那0.5, 然后再准备加上. 对于这个除以2来说, 还有一个问题, 那就是在原先旧容量为0或者1的情况下, 除以2还是0. 所以我们为这种情况定了常量4, 但是这种定常量的行为还可能会引发一个非常小概率的另一个问题, 那就是 4 本身是存在超过上限这种情况的可能的--尽管实际上那不太可能, 所以我说这是小概率, 这为下一步埋了一个坑.

下一步是让旧容量加上上一步算出来的一半.并且为了防止加上这一半超出上限, 我们还需要进行审议, 如果加上一半会超出上限, 那么我就直接先选择上限, 如果不会超出, 那么我们就加上, 接下来的问题是如何判断有没有超出, 一种方法是让上限容量减去一半, 看看接下来还够不够放当前容量, 另一种方法是让上限容量减去当前容量, 还是看看剩下来的够不够放那一半, 我们这里选择后者, 因为前者可能会触发上一段我们说的那个坑. 这个一半是可能超出上限的, 所以你不能拿上限容量减去这一半, 但是当前容量绝对没有超过上限, 所以后者可以, 如果一半超出上限, 从逻辑上来说, 容量或者说大小是非负数的, 所以 size_type 是无符号, 因此如果如果拿小的减去大的, 那肯定不是一个正确的数, 这使得比较失去了可靠性.

第二个难理解的是`pointer ptr = allocator_traits_type::allocate(_alloc, newCapacity);`, 这也是本文乃至之后我们需要经常面对的一个问题, 那就是现在还完全不能说空间配置器以及对应适配器, 但是我个人是肯定要写的, 在这里, 可以说这个适配器静态方法在内部会调用空间配置器`_alloc`, 最后为我们申请一份严格遵循第二参数的单位所需要的空间大小, 注意, 只是申请空间, 这里可以理解为之前C++内存中所提到的 operator new 方法, 只是申请空间, 不在这片空间上构造对象

接下来的内容是让新空间中的对象所存储数据信息和旧空间对应逻辑位置对象的数据信息做到等价(通过复制移动或者共享的方法, 移动语义需要系统地说, 不能零散讲, 这里可以简单理解成将承载信息的数据载体的所有权以及管理权什么东西的进行移交, 而不是拷贝一份相同的数据载体)

然后是 try catch 结构, 这又是一个很大的难点, 这个结构的根本目的是为了尽可能减少构造中途抛出异常, 导致容器卡在一个中间状态, 造成逻辑混乱和空间丢失. 构造函数是可能抛出异常的, 如果我们的旧空间中有五个有效元素, 在进行信息等价处理的过程中, 前两个处理成功, 第三个处理失败, 构造函数抛出异常, 此时我们就需要进行状态回退: 由于我们之前没有析构对象--我们看到, 是在信息等效性处理完成之后, 才析构旧对象, 所以目前我们要做的是把这个半路错误的新空间及其中已经构造的新对象处理掉. try catch 结构用于进行异常的捕获, 从行为上来说, 捕获就是, 如果 try 中的代码抛出异常, 那么执行流就会直接跳转到 catch 当中, 执行其中的异常应对代码, 在这里他们的工作就是之前说的, 析构新空间中构造成功的对象, 再释放新空间, 最后一个throw, 意思是说, 本层无法解决这个异常, 但我们已经做了能做的, 现在我收到的这个异常继续向上层传递, 用来给用户进行错误分析, 看看可能是干了什么事, 导致构造中途出现问题.

另一个问题有关效率和安全方面的平衡, `move_if_noexcept`负责应对. 就像我们之前说的, 进行信息等效化处理有三个方式, 复制移动或者共享. 我们举一个例子, 我们现在需要提交一份承载特殊信息的文档, 比如什么市场调查, 用户建议, 或者对于学生来说的化, 可能是电子作业, 恰好, 我们不知道用了什么手段, 获得了可以满足要求的参考文档, 既然我们手头有参考文档, 我们当然就需要利用, 一种方式提取其中的有效信息, 然后自己重新组织, 再把他以可传递的方式, 比如文字, 图片, 表格什么东西重新表达, 写到新文档里面, 这旧类似于复制(实际上容器中的复制对于重组织的方式往往是机械的, 他可能不会引入新的表达方式, 而是照抄原先的表达方式), 另一种更加省事, 你将参考文档中原先的作者信息抹去, 换成自己的, 宣称改文档的所有权在你的手里, 这就相当于移动. 共享要换一个例子, 但字面上也好理解, 就是大家一起用, 比如之前说过的有关部分标准库中的 string 的引用计数方案.

在这三种方式中, 更加通用的还是前两个, 复制和移动(有的特殊对象可能只支持移动), 与之相对应的就有拷贝构造和移动构造, 但是我们也必须要知道, 移动是一个所有权转交的过程, 这意味着原先的对象不再拥有这份承载信息的数据载体, 因此他必须建立在一个前提之上--那就是确定原先的对象已经不再需要这份载体了, 这份载体对于原对象来说有没有无所谓了, 但是是否有所谓是一个主观的说法, 只有在一些特定的位置上, 编译器才可以肯定某个对象已经无所谓了, 进而允许别人把所有权拿过去, 无所谓可能有很多原因, 原对象的生命周期即将结束就是很普遍的一种--反正我都快没了, 那这个所有权要不要自然都无所谓了, 上述所说的特定位置也主要指的这种情况--即使是编译器也可以看出, 这个对象马上就要没了, 所以我认为别的对象是可以移动其中的所有权的, 我们把这种可以移动所有权的原对象统称为右值

我们可以看出, 移动比复制更加省事, 其效率往往就更高. 但是除非特别明显, 否则编译器无法判断原对象还有没有所谓, 这时就需要我们进行显式的说明, 向编译器强调, 这个是右值, 可以移动的, 你应该去匹配对应的具有移动语义的函数接口, std::move 就是这样的操作符. 而在我们这里, 我们认为他目前来说是无所谓的(如果一切正常的话), 毕竟我们这里是扩容, 我们需要给数据换个地方存, 而不应该继续在这里存储, 也可以看到, 按照正常流程, 他们很快就会被析构. 

不过我们这里并没有用 std::move, 这是因为 std::move 会引入新的问题. 让我们设想一下,  移动构造也是有可能抛出异常的, 但问题并不是他会抛出异常, 而是移动语义会将原对象中的数据载体所有权进行移交, 也就是说, 现在如果要回退, 我还要想办法把把已经移交过的再移动回去, 这意味这我们需要再增加 catch 中的逻辑. 所以这里使用了`move_if_noexcept`, 就如注释所说, 这时一个有条件的 std::move, 如果移动构造自己保证本身不抛异常, 那我们就直接采用移动构造, 如果他可能抛异常, 那么这个 move 将不生效, 将会命中拷贝构造--从而保留原对象中的数据, 让回退的逻辑更加简单, 不过注释也说了, 如果只有移动构造, 就没有拷贝构造, 即使拷贝构造不保证不抛出异常, 那我们也只能用它, 再加上保证不抛出异常, 和实际到底是否会抛出异常, 不能完全画等号, 所以我们目前的逻辑仍旧是有漏洞的, 所以之前我用的词是"尽量", 而非规避, 我们已经做了所有能做的事, 再出问题我也没有办法, 让他见鬼去吧.

(now)接下来我们来写插入, 因为插入写好了, 其他有关写的接口就比较好写--直接复用了

首先我们要意识到的问题, 就是有关参数的合法性和可靠性: 参数 pos 可能不在合法区间里, 我们所说的合法区间是 [0, size], 当为 size 的时候, 就相当于尾插. 除此之外, 为了容纳新的元素, 我们或许要进行扩容, 一旦扩容, 空间位置就会发生变动, 因此造成之前的迭代器不可用, 为此, 在正式扩容之前, 我们需要以偏移量的方式记录插入的逻辑位置, 以备之后的重新定位.

对于  count 就为 0 的情况下, 我们直接返回, 这里的一个要点是 pos 是常迭代器, 需要返回的却是普通迭代器--因此我们需要用 const_cast操作符来去除 const 返回

接下来有关 count 次数合法性的检查, 显然这个 count 不能太大, 不能超过底层所允许的最大容量, 我们在 reserve 那里也见过类似操作

接着是对于填充元素的可靠性保证: 我们担心出现这种情况: value 可能就是本 vector 对象之前所存储的一个元素, 如果扩容, 空间位置发生变化, 这个 value 因为采用了常引用的形式, 自然也会失效, 所以在这里我们选择一个简单有效的方法, 那就是对 value 拷贝出一份独立的副本, 之后就不再管他, 这就使得 fill_value 的可靠性得到保证, 注释上写: 这里要求使用拷贝构造, 所以对于 value_type 来说, 其必须支持拷贝构造--却是存在一些具有特殊功能的对象, 他们可能确实不支持拷贝构造, 你也可以看到, 在函数开头, 我写了一段编译期检查, 要求 value_type 必须支持一些接口才行, -- 拷贝构造正是其中的一员

在做完前期的准备工作之后, 我们开始扩容, 让容量可以容纳下将要加入的新元素

好, 在进行进一步的操作之前, 我们必须先理清当前底层动态数组的空间关系: 目前数组的具体容量不清楚, 但是足以容纳新加入的元素, 这里我们不需要太担心, 以 _start 为基地址, [0, oldSzie) 的区间内放着有效的对象. 现在显然我们需要先对原来的区间进行划分, 将后半部分进行挪动, 给新插入的元素空出空间, 然后再把填充元素再给填进去, 主要流程就是这样. 在理想情况下, 最后的空间状态, 仍旧是以 _start 为基地址, [0, insert_offset) 为之前的前半部分, [insert_offset, insert_offset+count)为第二部分, 他们是新加入的元素, [insert_offset+count, oldSize + count) 是第三部分, 他们是之前原来的后半部分.

由此我们得出了三个指针, 分别表示插入的基地址, 原来后半部分(需要挪动)的源地址, 以及最后理想状态下, 第三部分的基地址. 我们还需要清楚, 要挪动的部分是原来的后半部分, 原来的前半部分有 insert_offset 个元素, 而原来一共有 oldSize 个元素, 所以不难得到, 需要挪动 oldSize - insert_offset 个元素. 而理想状态下的第二部分--那个新加入的元素区间, 有 count 个元素. 我为什么非常在意他们的元素数目呢? 这是因为通过这些元素数目可以判断在将原来的第二部分进行挪动时, 是否存在重叠的空间--明确这一点, 在后面是会派上大用场的. 让我们来想一下, 与旧区间相比, 显然新区间多了 count 个元素, 这显而易见, 毕竟我们要在中间插入 count 个元素, 然后我们也知道需要挪动元素的数目, 那么如果挪动元素的数目大于这个 count, 这意味着, 被挪动部分的前缀和原区间的部分后缀是重叠的, 具体的重叠数目就是把他们再给减一下

![](https://img.mdwind.online/img/20261114223025449.png)

![](https://img.mdwind.online/img/20261114223042557.png)

在示意图中, 提出了在乎重叠的一个重要理由: 让我们想一下, 对于这种源空间后缀和目标空间前缀重叠的情况, 我们在进行挪动的时候, 是一定不能从前完后挪动的, 这会把我们之后要挪动的源数据给覆写掉, 所以我们应该采取从后往前的挪动方法, 并且, 从后往前的这种挪动方法, 对于不重叠的情况自然是有效的-- 不重叠怎么移动都行, 我们在乎重叠还有另一个原因, 说到的时候再讲.

这里也有一些小细节需要注意, 比如移动个数和下标变量用的都是有符号的 difference_type, 而不是用 size_type, 这是故意的, 在接下来我们会经常进行一些减法运算, 所以需要负数支持, 防止下溢出, 比如假设之前容器完全是空的, 所以这次偏移量必然是0, 0 - 0  得 0, 关键那个挪动的代码, 采用从后往前的策略, 最开始的 idx 被初始化为移动个数减去1, 所以旧变成负数了, 而对于 idx 本身来说, 他作为基地址的偏移量, 也是平方的需要迭代到0(包括0)位置再停下, 所以也一定要是有符号的.

接下来的代码乍看起来可能很怪, 他在原来的区间后面填充了 count 个无参构造的默认元素进行占位, `allocator_traits_type::construct(_alloc, _finish + idx);`完美转发现在还不能说--他又很多前置知识, 这些知识目前我大多没说, 总之这段代码就是在 第二个参数所指向的空间里进行无参构造, 使得他成为一个真正有效的元素, 而不是完全的空的空间, 我这样做的目的是为了让元素对象的生命周期管理和之后的数据等效化处理相解耦, 避免互相干扰, 使得逻辑混乱.--如果把容器比作水杯, 其中存储的有效数据比作水, 那么在把水放在这里之前, 我们需要先在这里放一个空杯子, 否则水是无法放在这里的.

之后还是有关异常的安全性处理: 如果填充空对象的过程抛出了异常, 我们需要把已经构造的进行析构, 然后继续向上抛出异常

接下来就引入数据挪动的过程

与 reserve 类似, 这里如果可以的话, 我们当然也想要基于移动语义的赋值, 但我看了一下, 没有像之前`move_if_noexcept`那样直接用的操作符--他只能检查移动构造有没有保证不抛异常, 无法检查别的基于移动语义的其他接口有没有保证不抛异常, 因此这里我们采用了编译期代码进行手动实现, `if constexpr`是在编译期就确定所命中分支的条件判断, 我们写, 如果保证移动赋值不抛异常, 那我们就直接为src 加上 std::move , 向编译器强调, 这个是右值, 你应当为他匹配基于移动语义的接口, 其他情况, 也就是移动赋值不保证不会抛异常, 那么就使用平常的拷贝赋值

接下来仍旧是异常安全逻辑. 如果抛出异常, 只有两种可能, 一种就是使用的是拷贝赋值, 抛出异常了, 另一种就是使用的是移动赋值, 但是那边代码有问题, 明明保证不抛异常, 最后还是抛异常了, 这不是我们的责任, 所以我们不考虑, 当然还有第三种, 那就是只支持移动赋值, 压根没有拷贝赋值, 此时当然只能用移动赋值, 然后抛出了异常, 不过这种情况不会出现, 在代码开头, 我们就明确要求, value_type 必须要支持拷贝赋值, 所以真的要考虑的只有第一点.

![](https://img.mdwind.online/img/20261115010703268.png)

对于这种情况来说，有没有重叠就是一个需要在意的点，因为一旦出现重叠，向目标位置进行赋值时，就可能把原来后半部分的某些元素给覆写掉。如果此时中途抛出了异常，那么即使我们已经停止挪动，原来的数据也未必还是完整的，所以需要考虑把被覆写的部分恢复回来。

但是，仔细想一下，**即使存在重叠，也不意味着只要发生异常，就必须把整个后半部分重新写一遍。**

之前我们已经确定了，挪动操作是从后往前进行的。假设一共需要挪动 `move_count` 个元素，向右挪动的距离为 `count`，而真正发生重叠的元素数量为：

```
overlap_count = move_count - count;
```

这里先假设 `move_count > count`，也就是确实存在重叠的情况。

由于我们从后往前挪动，最开始处理的其实是源区间最后面的 `count` 个元素。而这些元素的目标位置已经超出了原来的源区间，因此在这一阶段，即使拷贝赋值抛出异常，也不会因为目标位置的写入而破坏原先的源数据。

那么，什么时候才会真正开始覆写呢？

我们知道，源区间最后一个元素的下标是 `move_count - 1`，而最开始可能发生覆写的位置，恰好对应源区间前面 `overlap_count` 个元素中的最后一个。

所以，当：

```
idx >= overlap_count
```

目标位置还没有进入源区间；只有当：

```
idx < overlap_count
```

才意味着我们已经进入了可能覆写原数据的阶段。

不过，还可以继续往下推导。既然我们已经知道发生异常时的 `idx`，那么有没有办法进一步确定，究竟是哪些元素可能被覆写了呢？

当然可以。

我们原来的目标地址就是在源地址的基础上向后偏移 `count` 个元素：

```
move_dst = move_src + count;
```

因此，对于下标为 `idx` 的源元素，它对应的目标位置就是：

```
move_dst[idx] == move_src[idx + count]
```

假设这一次赋值抛出了异常。由于我们是从后往前执行的，那么下标大于 `idx` 的迁移操作都已经完成，下标小于 `idx` 的迁移操作则还没有开始。

这意味着，**可能已经被覆写的源数据，一定集中在原区间的后缀部分，其起点就是** `**idx + count**`**。**

至于为什么要把当前失败的这一次赋值也考虑进去，是因为拷贝赋值并不保证在抛出异常之前完全没有修改目标对象。即使赋值最终失败，它也可能已经改变了目标位置的数据。

那么，恢复区间就可以确定为：

```
[idx + count, move_count)
```

这里使用的都是相对于 `move_src` 的下标。

恢复时，我们从前往后遍历，把之前已经搬到目标区间中的副本重新写回原来的位置：

```cpp
if (idx < overlap_count) {
                for (difference_type i = idx + count; i < move_count; ++i) {
                    if constexpr (std::is_nothrow_move_assignable_v<value_type>) {
                        move_src[idx] = std::move(move_dst[idx]);
                    } else {
                        move_src[idx] = move_dst[idx];
                    }
                }
            }
```

这里为什么可以从前往后恢复呢？因为 `move_dst` 始终位于 `move_src` 的右侧。我们现在是在把数据向左写回去，所以只要从前往后进行，就不会提前覆写后面仍然需要读取的副本。这与之前向右挪动时必须从后往前进行，恰好是相反的。

这样一来，异常处理就可以分成两种情况：

如果 `idx >= overlap_count`，说明还没有进入重叠区域，原来的源数据没有因为目标写入而被覆写，我们直接清理尾部额外构造的对象即可。

如果 `idx < overlap_count`，说明已经有部分目标位置进入了原区间。我们只需要恢复 `[idx + count, move_count)` 这一段后缀，然后再清理尾部对象。

由此可见，之前判断源区间与目标区间是否重叠，只是第一步。现在结合挪动方向、当前下标以及两个区间之间的偏移量，我们还能进一步确定异常发生时真正需要恢复的范围。

当然，这里分析的是拷贝赋值过程中，由目标位置覆写源区间造成的数据变化。我们暂时沿用前面的实现约定，假设恢复赋值能够成功。至于恢复操作本身再次抛出异常的情况，先不在这一节展开。

![](https://img.mdwind.online/img/20261115011103461.png)

原来的数据恢复之后, 我们就把之前从 _finish, 新构造的那些对象析构.

如果理想的话, 没有抛出异常, 下一步就来到了填充逻辑, 具体填充肯定是要用拷贝赋值的, 要保证我们之前又拷贝出的副本不变.

如果在填充的过程中又抛出异常, 考虑到有填充的干扰, 我们就不考虑那么细了, 就简单粗暴的把元素再给写回来, 然后还是把额外的析构

如果不抛出异常, 那么就大功告成, 更新一下 _finish, 就可以返回了.

```cpp
// 在指定位置填充若干对象
    iterator insert(const_iterator pos, size_type count, const_reference value) {
        static_assert(std::is_default_constructible_v<value_type> &&
                          std::is_copy_constructible_v<value_type> &&
                          std::is_copy_assignable_v<value_type>,
                      "wind::vector::insert: value_type must support default construction, "
                      "copy construction and copy assignment");

        // 检查位置是否处于合法区间
        size_type oldSize = size();
        difference_type insert_offset = pos - _start;
        if (insert_offset < 0 || insert_offset > oldSize)
            throw std::out_of_range("wind::vector::insert: invalid iterator position");

        // 如果数目为0, 直接退出
        // 另外为了和返回值契合, 再取消 const
        if (count == 0) return const_cast<iterator>(pos);

        // 取出允许的最大容量上限, 检查是否存在溢出的可能
        const size_type maxSize = allocator_traits_type::max_size(_alloc);
        if (count > maxSize - oldSize)
            throw std::length_error("wind::vector::insert(iterator, size_type, const_reference)");

        // 拷贝填充元素, 避免出现自依赖问题
        // 此处强制要求存在拷贝构造
        value_type fill_value = value;

        // 要求拥有足够的容量
        reserve(oldSize + count);

        // 理想填充之后的情况
        // [0,insert_offset) 不变
        // [insert_offset, insert_offset + count) 新填充区间
        // [insert_offset + count, oldSize + count ) 新移动出的区间

        pointer insert_pos = _start + insert_offset;  // 填充区间起点
        pointer move_src = insert_pos;                // 移动源区间起点
        pointer move_dst = insert_pos + count;        // 移动目标区间起点
        // 注意这里可以尾插, 存在 0 的可能 之后 -1 可为负数
        difference_type move_count = oldSize - insert_offset;  // 需要移动的元素个数
        const difference_type overlap_count =
            move_count > count ? move_count - count : 0;  // 重叠的个数

        // 使用有符号, 防止下溢出
        difference_type idx = 0;

        // 确保理想填充的合法区间中都是有效对象
        try {
            for (; idx < count; ++idx) {
                // 不输入第三参数, 完美转发后命中无参构造
                allocator_traits_type::construct(_alloc, _finish + idx);
            }
        } catch (...) {
            // 空构造失败进行状态回退, 对已经构造的进行析构
            for (--idx; idx >= 0; --idx) {
                allocator_traits_type::destroy(_alloc, _finish + idx);
            }
            throw;
        }

        idx = move_count - 1;
        // 抛出异常进行回退
        try {
            // 类型特征
            // std::is_nothrow_move_assignable_v<T> : 判断类型 T 的移动赋值操作是否保证不抛异常
            // std::is_copy_assignable_v<T> : 判断类型 T 是否支持拷贝赋值

            // 如果移动赋值保证不抛异常, 优先选择移动赋值
            // 如果没有拷贝赋值, 即使可能抛出异常, 也被迫使用移动赋值

            // 由于可能是重叠空间, 需要从后往前挪动
            // 进行数据载体的等效化处理
            for (; idx >= 0; --idx) {
                if constexpr (std::is_nothrow_move_assignable_v<value_type>) {
                    move_dst[idx] = std::move(move_src[idx]);
                } else {
                    move_dst[idx] = move_src[idx];
                }
            }
        } catch (...) {
            // 回退
            // 1) 源数据恢复

            // 如果抛出异常, 只有一种情况
            // 1. 拷贝赋值抛出异常, 原先的数据载体没有被移动
            // 2. 对方的保证有问题, 实际抛出异常, 这不是我们的问题, 不考虑
            // 3. 没有拷贝赋值, 使用移动赋值抛出异常, 但是不可能, 这样通不过编译器判断, 不考虑

            // 如果中途出现异常, 进行状态回退

            // 1. 如果是移动语义, 源后缀数据被移动, 需要移回(不考虑)
            // 2. 如果是拷贝赋值, 除非因为源后缀和目的前缀重叠, 否则源数据不会丧失

            if (idx < overlap_count) {
                for (difference_type i = idx + count; i < move_count; ++i) {
                    if constexpr (std::is_nothrow_move_assignable_v<value_type>) {
                        move_src[i] = std::move(move_dst[i]);
                    } else {
                        move_src[i] = move_dst[i];
                    }
                }
            }

            // 2) 将额外构造的, 原先准备被赋值的新元素析构
            for (idx = 0; idx < count; ++idx) {
                allocator_traits_type::destroy(_alloc, _finish + idx);
            }
            throw;
        }

        // 开始填充
        // 抛出异常同样回退
        try {
            for (idx = 0; idx < count; ++idx) {
                // 强制要求支持拷贝赋值
                insert_pos[idx] = fill_value;
            }
        } catch (...) {
            // 抛出异常开始回退

            // 1. 让原来的元素恢复原先是数据状态
            for (idx = 0; idx < move_count; ++idx) {
                if constexpr (std::is_nothrow_move_assignable_v<value_type>) {
                    move_src[idx] = std::move(move_dst[idx]);
                } else {
                    move_src[idx] = move_dst[idx];
                }
            }

            // 2.析构额外构造出的新元素
            for (idx = 0; idx < count; ++idx) {
                allocator_traits_type::destroy(_alloc, _finish + idx);
            }
            throw;
        }

        _finish += count;
        return insert_pos;
    }
```

接下来我们来写插入迭代器区间的接口, 其实和填充相同元素差不了多少, 但是有一个很大的问题是, 对于迭代器区间来说, 我们完全没有办法判断它有没有自引用--它可能是别的类型的迭代器, 别的类型的迭代器也有可能指向我们, 所以最后我们选择的方案是再找一个容器, 先把迭代器区间中的内容拷贝一下再说其他的, 注意我们不能选择自己, 因为我本来就打算迭代器区间构造还是底层复用迭代器区间插入, 我们也不能选择标准库里的 vector , 那就很奇怪, 毕竟我们自己就在实现 vector, 而且标准库里插入自引用迭代器区间是未定义的, 最后, 我们选择接下来马上要实现的下一个容器, 双向链表, list, 不过由于现在还没有实现, 所以我们就用标准库里面的了, 但大致和上面的插入差不多, 所以我就不列代码了

![](https://img.mdwind.online/img/20261115165555259.png)

![](https://img.mdwind.online/img/20261115165613803.png)

单元素插入也差不多, 所以也跳过

接下来说迭代器区间的删除, 思路也差不多, 唯一的区别可能是他的重叠模型不同了, 这也导致 if 和 for 可以融为一体, 所以这里只写了 for 

![](https://img.mdwind.online/img/20261115171428205.png)

```cpp
 iterator erase(const_iterator first, const_iterator last) {
        if (first < _start || first > _finish)
            throw std::out_of_range("wind::vector::erase(range)");

        if (first > last || last > _finish) throw std::out_of_range("wind::vector::erase(range)");

        if (first == last) return const_cast<iterator>(first);

        pointer move_dst = const_cast<pointer>(first);
        pointer move_src = const_cast<pointer>(last);
        difference_type erase_count = last - first;
        difference_type move_count = _finish - last;
        pointer dest_pos = _finish - erase_count;

        difference_type idx = 0;
        try {
            for (; idx < move_count; ++idx) {
                if constexpr (std::is_nothrow_move_assignable_v<value_type>) {
                    move_dst[idx] = std::move(move_src[idx]);
                } else {
                    move_dst[idx] = move_src[idx];
                }
            }
        } catch (...) {
            for (difference_type i = idx - erase_count; i >= 0; --i) {
                if constexpr (std::is_nothrow_move_assignable_v<value_type>) {
                    move_src[i] = std::move(move_dst[i]);
                } else {
                    move_src[i] = move_dst[i];
                }
            }
            throw;
        }

        for (idx = 0; idx < erase_count; ++idx) {
            allocator_traits_type::destroy(_alloc, dest_pos + idx);
        }

        _finish = dest_pos;
        return move_dst;
    }
```

指定位置的删除直接复用, 下面两个 emplace 和原地构造有关, 我打算先略过不讲

![](https://img.mdwind.online/img/20261115171621282.png)

(now) 接下来我们来写 push_back, 其实非常好写, 直接复用现成的插入接口就行了

![](https://img.mdwind.online/img/20261115172658490.png)

他们两个分别复用自己对应的左右值接口, 我们之前只介绍过右值的概念, 没有说详细用法, 如果说的话, 又要讲一大堆, 所以我就不说了, 留着后面说

接下来写 resize , 有两个接口

![](https://img.mdwind.online/img/20261115173217295.png)

C++98 那边通过缺省的方式把他们结合在一起了, 那为什么 C++11 这边又拆开了呢? 这主要是从类型特征的角度来说的, 如果是 C++98 的缺省实现, 就相当于给了一个填充元素, 然后如果要插入多个元素, 必然要以拷贝填充元素的方式, 把他们插入进去, 而在 C++11 这边, 第一个接口如果需要进行默认元素的增加, 我说的这种默认元素的增加底层就是无参构造, 在表现上就相当于之前每次实现 insert 在末尾调用空间配置适配器进行无参构造, `allocator_traits_type::construct(_alloc, _finish + idx);`, 区别在于这并非是通过拷贝的形式进行插入的, 而是直接无参构造--他不需要类型拥有拷贝的相关接口, 写到这里, 我也意识到, 我们目前的接口实现顺序以及分工不太对, insert 都需要进行默认元素的增加, 这些代码逻辑不应该在 insert 里面, 而应该在 resize 里面, 下个容器的实现再调整一下顺序. 第二个 resize 其实就是在强调, 这个接口需要存储类型支持拷贝构造或者拷贝赋值什么东西的.

我们先写两个私有接口, 一个表示默认追加指定数目元素, 另一个标志析构并弹出末尾指定元素

```cpp
// 默认追加指定数目元素 _finish 会进行适应性调整
    void append_default(size_type count) {
        if (count == 0) return;

        const size_type maxSize = allocator_traits_type::max_size(_alloc);

        size_type oldSize = size();
        if (count > maxSize - oldSize) throw std::length_error("wind::vector::append_default");

        reserve(oldSize + count);

        size_type idx = 0;

        try {
            for (; idx < count; ++idx) {
                allocator_traits_type::construct(_alloc, _finish + idx);
            }
        } catch (...) {
            while (idx > 0) {
                --idx;
                allocator_traits_type::destroy(_alloc, _finish + idx);
            }
            throw;
        }

        _finish += count;
    }

    // 析构并溢出末尾指定元素
    void pop_back_n(size_type count) noexcept {
        if (count == 0) return;

        size_type oldSize = size();
        if (count > oldSize) count = oldSize;
        pointer curr = _finish - count;
        while (curr != _finish) {
            allocator_traits_type::destroy(_alloc, curr);
            ++curr;
        }
        _finish -= count;
    }
```

两个 resize 复用他们, 前面那些什么 insert , 也可以复用他们, 但这里我们就不改了

```cpp
void resize(size_type n, const_reference val) {
        const size_type oldSize = size();

        if (n < oldSize) {
            pop_back_n(oldSize - n);
            return;
        }

        if (n == oldSize) return;

        const size_type count = n - oldSize;

        // 提前保存副本，避免扩容导致 val 引用失效
        value_type fill_value = val;

        // 默认构造新增对象，并更新 _finish
        append_default(count);

        try {
            pointer curr = _finish - count;

            while (curr != _finish) {
                *curr = fill_value;
                ++curr;
            }
        } catch (...) {
            // 移除本次新增的所有对象
            pop_back_n(count);
            throw;
        }
    }
```

既然`reserve`写了，那就顺手写写`resize`吧.

```cpp
void resize(size_t n, const T& val = T()) {
	if (size() < n) {
		// 保证有足够的空间
		reserve(n);
		while (size() != n) {
			push_back(val);
		}
	}
	else {
		_finish = _start + n;
	}
}
```

如果参数小于当前元素个数，那就是删除，其实不用真删除，直接把元素终止指针`_finish`移过去就行了(这肯定是不对的, 以前水平不太够, 现在, 特别是用上空间配置器以及适配器之后, 对象的生命周期, 和其中存储的数据, 分得很清楚, 直接把指针往前移动是肯定不对的, 历史代码可以进行稍微的变更, 写成作为错误示范的伪代码)。元素个数大于当前个数，那就是追加，注意，模版里的元素不一定都是内置类型，所以不能用0做缺省值，而是应用默认构造做缺省值，为了提高效率，我们使用了常引用，常引用可以延长对象的生命周期，这样，匿名对象就会在`val`生命周期结束后再被析构，而不是在这行之后就被析构。另外说一下，之前为了逻辑自洽我们说内置类型没有构造函数，实际上，内置类型是有默认构造函数的。

同样的, 下面这份本来就故意写错的代码也可以作为错误示范

接下来我们写一下`insert erase`

```cpp
/*iterator insert(iterator pos, const T& val) {
	assert(pos >= _start && pos <= _finish);
	if (empty()) {
		push_back(val);
		return pos;
	}
	else {
		if (size() == capacity()) {
			size_t newCapacity = capacity() * 2;
			reserve(newCapacity);
		}
		iterator transport = _finish - 1;
		while (pos <= transport) {
			*(transport + 1) = *transport;
			--transport;
		}
		*pos = val;
		++_finish;
		return pos;
	}
}*/
```

我们首先进行一下范围检查，防止对未知区域进行操作。如果为空的话，就直接调用尾插。如果不为空，容量不够则扩容，然后把数据搬运一下，再在指定位置插入数据即可。返回值我们先不考虑。为什么注释呢？因为这涉及到`vector`中的第二个大坑。

还是这个，不过这里的`insert`用的是上面的代码，是有问题的。

```cpp
void realization3()
{
	wind::vector<std::string> str_arry;
	auto& v = str_arry;
	v.push_back("1111");
	v.push_back("11111111111111111111111111");
	v.push_back("xxxxxxxxxxxxxxxxxxxxxxxxxx");
	v.push_back("11111111111111111111111111");
	wind::vector<std::string>::iterator it = v.end();
	v.insert(it, "hello word");
	for (auto m : v)
	{
		std::cout<<m<<std::endl;
	}
}
```

直接崩了：

![image-20241025163333567](https://img.mdwind.online/md/202410251633611.png)

调试一下，就可以找到问题了。

![image-20241025163926799](https://img.mdwind.online/md/202410251639146.png)

![image-20241025163946217](https://img.mdwind.online/md/202410251639258.png)

![image-20241025164037994](https://img.mdwind.online/md/202410251640354.png)

![image-20241025164052910](https://img.mdwind.online/md/202410251640951.png)

`pos`是以原内存块为参考的，现在扩容了，扩容是异地扩容，`pos`没有被修正，还指向原内存块而不是新内存块的某处，它已经处于非法位置了。挪动数据时会越界。

所以修正一下就行了

```cpp
// 为空时，transport也能兼容
iterator insert(iterator pos, const T& val) {
	assert(pos >= _start && pos <= _finish);
	if (size() == capacity()) {
		size_t n = pos - _start;
		size_t newCapacity = capacity() * 2;
		if (empty()) {
			newCapacity = 4;
		}
		reserve(newCapacity);
		// 扩容之后，迭代器失效，需要重新修正
		pos = _start + n;
	}
	iterator transport = _finish - 1;
	while (pos <= transport) {
		*(transport + 1) = *transport;
		--transport;
	}
	*pos = val;
	++_finish;
	return pos;
}
```

上面的问题其实就是迭代器内部失效，既然内部都失效了，外部当然更失效，而且因为我们不使用引用，所以修正不了实参，那能不能用引用，回答是不行。迭代器大多数都是由`begin`它们返回出来的。返回值具有常属性，不可被修改，所以不能用引用，而如果使用常引用，那`insert`内部也修正不了了，所以这里直接用`iterator`。

![image-20241025165532021](https://img.mdwind.online/md/202410251655087.png)

那外部迭代器怎么修改呢（如果需要修改的话）？那就接受`insert`的返回值，C++标准规定，`insert`会返回被插入位置的迭代器，于是就能修改上一级函数的迭代器了。

```cpp
iterator erase(iterator pos) {
	assert(pos>= _start && pos < _finish);
	iterator transport = pos + 1;
	while (transport <= _finish) {
		*(transport - 1) = *transport;
		++transport;
	}
	--_finish;
	return pos;
}
```

`erase`不会扩容，所以没有迭代器内部失效的风险，但有外部失效的风险

```cpp
void realization4()
{
	//std::vector<int> v;
	wind::vector<int> v;
	v.push_back(0);
	v.push_back(1);
	v.push_back(2);
	v.push_back(2);
	v.push_back(3);
	v.push_back(3);
	wind::vector<int>::iterator it = v.begin();
	//std::vector<int>::iterator it = v.begin();
	// 目标：删除所有偶数元素
	while (it != v.end())
	{
		if (*it % 2 == 0)
		{
			v.erase(it);
		}
		++it;
	}
	for (auto val : v)
	{
		std::cout << val << " ";
	}
	std::cout << std::endl;
	// 输出结果：1  2  3  3
	// it -> 0    0 1 2 2 3 3   删除 迭代器指向内容发生改变 it -> 1  外部循环再加一 it -> 2
	// it -> 2    1 2 2 3 3     删除 迭代器指向内容发生改变 it -> 2  外部循环再加一 it -> 3
	// it -> 3    1 2 3 3       外部循环加一 it -> 3
	// it -> 3    1 2 3 3       外部循环加一 it -> 3
	// 解决方案： erase是有返回值的，可以用来修正外部迭代器
}
```

![image-20241025170447171](https://img.mdwind.online/md/202410251704233.png)

```cpp
void realization5()
{
	//std::vector<int> v;
	wind::vector<int> v;
	v.push_back(1);
	v.push_back(1);
	v.push_back(1);
	v.push_back(2);
	wind::vector<int>::iterator it = v.begin();
	//std::vector<int>::iterator it = v.begin();
	// 目标：删除所有偶数元素
	while (it != v.end())
	{
		if (*it % 2 == 0)
		{
			v.erase(it);
		}
		++it;
	}
	for (auto val : v)
	{
		std::cout << val << " ";
	}
	std::cout << std::endl;
	// 结果：触发assert警告
	// 最后一个元素被删除之后，迭代器已经指向非法区域_finish
	// 其值为随机值
	// 当为偶数时，再次进入erase，触发范围检查警告
}
```

![image-20241025171116534](https://img.mdwind.online/md/202410251711592.png)

```cpp
// 解决方案：删除之后对迭代器进行修正
void realization6()
{
	//std::vector<int> v;
	wind::vector<int> v;
	v.push_back(0);
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(4);
	wind::vector<int>::iterator it = v.begin();
	//std::vector<int>::iterator it = v.begin();
	// 目标：删除所有偶数元素
	while (it != v.end())
	{
		if (*it % 2 == 0)
		{
			it = v.erase(it);
		}
		else
		{
			++it;
		}
	}
	for (auto val : v)
	{
		std::cout << val << " ";
	}
	std::cout << std::endl;
}
```

![image-20241025170938425](https://img.mdwind.online/md/202410251709490.png)

刚刚使用的是我们自己实现的vector。现在换成VS自己的看一看，我们发现此时4 5号序列都报错，VS对迭代器进行了强制检查，只要发现经过erase的迭代器，没有被修正，直接操作（比如++）就报错。

```cpp
void realization4()
{
	std::vector<int> v;
	//wind::vector<int> v;
	v.push_back(0);
	v.push_back(1);
	v.push_back(2);
	v.push_back(2);
	v.push_back(3);
	v.push_back(3);
	//wind::vector<int>::iterator it = v.begin();
	std::vector<int>::iterator it = v.begin();
	// 目标：删除所有偶数元素
	while (it != v.end())
	{
		if (*it % 2 == 0)
		{
			v.erase(it);
		}
		++it;
	}
	for (auto val : v)
	{
		std::cout << val << " ";
	}
	std::cout << std::endl;
}
```

![image-20241025171556326](https://img.mdwind.online/md/202410251715391.png)

g++则是更像我们实现的逻辑，毕竟我们的实现就是从它的原码开始的。

```shell
[wind@starry-sky IteratorFailure-vector]$ ls
main.cpp  out-4  out-5  out-6
[wind@starry-sky IteratorFailure-vector]$ ./out-4
1 2 3 3 
[wind@starry-sky IteratorFailure-vector]$ ./out-5
Segmentation fault
[wind@starry-sky IteratorFailure-vector]$ ./out-6
1 3 
[wind@starry-sky IteratorFailure-vector]$
```

接下来说一说拷贝构造

```cpp
vector(const vector& v)
	:_start(nullptr)
    ,_finish(nullptr)
	,_endofstarage(nullptr)
{
	const iterator ptr = new T[v.capacity()];
	iterator transport = ptr;
	for (const auto& e : v) {
		new(transport++) T(e);
	}
	_start = ptr;
	_finish = _start + v.size();
	_endofstarage = _start + v.capacity();
}
```

使用定位new表达式和T的默认构造进行深拷贝。

(now) 接下来让我们写  clear, 直接复用之前的私有接口即可, 他的职责是确保目前空间里已经没有一个有效对象了

```cpp
 void clear() {
        pop_back_n(size());
    }
```

接下来我们写拷贝构造

```cpp
vector(const self_type& v)
        : _start(nullptr),
          _finish(nullptr),
          _endofstorage(nullptr),
          _alloc(allocator_traits_type::select_on_container_copy_construction(v._alloc)) {
        try {
            insert(end(), v.begin(), v.end());
        } catch (...) {
            clear();
            if (_start) {
                allocator_traits_type::deallocate(_alloc, _start, capacity());
            }
            throw;
        }
    }
```

初始化列表除了  _alloc 应该没什么要说的, 而空间配置器和适配器的相关知识我现在还不能说--有点门槛, 所以我就跳过了, 说了又是一大堆, 

之后是关于函数体的, 我们这里使用迭代器区间插入, 如果抛出异常, 就清理掉所有的有效对象, 然后将空间还给空间配置器.

对于交换来说, 也只是将维护数据的那三个指针进行交换, 其他的仍旧是有关空间配置器及其适配器的内容, 不要在意

```cpp
  void swap(self_type& other) noexcept(
        allocator_traits_type::propagate_on_container_swap::value ||
        allocator_traits_type::is_always_equal::value) {
        if constexpr (!allocator_traits_type::propagate_on_container_swap::value &&
                      !allocator_traits_type::is_always_equal::value) {
            if (_alloc != other._alloc) {
                throw std::logic_error("UB: swapped vectors with unequal allocators!");
            }
        }

        if constexpr (allocator_traits_type::propagate_on_container_swap::value) {
            std::swap(_alloc, other._alloc);
        }

        std::swap(_start, other._start);
        std::swap(_finish, other._finish);
        std::swap(_endofstorage, other._endofstorage);
    }
```

接下来写一下成员交换函数

```cpp
void swap(vector& v) {
	std::swap(_start, v._start);
	std::swap(_finish, v._finish);
	std::swap(_endofstarage, v._endofstarage);
}
```

赋值重载我们使用现代写法，就不使用古典写法了，详见《string_lesson2》的赋值重载函数。

```cpp
vector& operator=(vector v) {
	swap(v);
	return *this;
}
```

我建议你们目前去看上面那个赋值接口版本, 而不是我这个--仅仅对于模拟实现 vector 来说, 这个看了反而有害, 可读性很低

![](https://img.mdwind.online/img/20261117011252919.png)

```cpp
// 基本安全保证
    self_type& operator=(const self_type& other) {
        if (this == &other) return *this;

        const size_type newSize = other.size();

        // 完成元素拷贝
        auto copy_elements = [&] {
            clear();

            try {
                append_default(newSize);

                for (size_type i = 0; i < newSize; ++i) {
                    _start[i] = other._start[i];
                }
            } catch (...) {
                clear();
                throw;
            }
        };

        // 更新配置器
        auto copy_allocator = [&] { _alloc = other._alloc; };

        if constexpr (allocator_traits_type::propagate_on_container_copy_assignment::value) {
            if constexpr (allocator_traits_type::is_always_equal::value) {
                copy_elements();
                copy_allocator();
            } else {
                if (_alloc == other._alloc) {
                    copy_elements();
                    copy_allocator();
                } else {
                    release_storage();
                    copy_allocator();
                    copy_elements();
                }
            }
        } else {
            copy_elements();
        }

        return *this;
    }
```

移动赋值(你们跳过即可)

```cpp
self_type& operator=(self_type&& other) {
        if (this == &other) return *this;

        release_storage();

        auto move_point = [&] {
            _start = std::exchange(other._start, nullptr);
            _finish = std::exchange(other._finish, nullptr);
            _endofstorage = std::exchange(other._endofstorage, nullptr);
        };

        auto move_alloc = [&] { _alloc = std::move(other._alloc); };

        auto move_elements = [&] {
            const size_type newSize = other.size();
            try {
                append_default(newSize);

                for (size_type i = 0; i < newSize; ++i) {
                    _start[i] = std::move(other._start[i]);
                }
            } catch (...) {
                clear();
                throw;
            }
        };

        if constexpr (allocator_traits_type::propagate_on_container_move_assignment::value) {
            move_alloc();
            move_point();
        } else {
            if constexpr (allocator_traits_type::is_always_equal::value) {
                move_point();
            } else {
                if (_alloc == other._alloc) {
                    move_point();
                } else {
                    move_elements();
                }
            }
        }

        return *this;
    }
```

接下里我们写一下迭代器区间构造

```cpp
template <std::input_iterator It>
    vector(It first, It last) : vector() {
        try {
            insert(end(), first, last);
        } catch (...) {
            release_storage();
            throw;
        }
    }
```

```cpp
// 使用模版便于其它迭代器的初始化
template<class InputIterator>
vector(InputIterator begin, InputIterator end)
	:_start(nullptr)
	, _finish(nullptr)
	, _endofstarage(nullptr)
{
	while (begin != end) {
		push_back(*begin);
		++begin;
	}
}
```

n个val构造(这个不用担心了, 我们现在模板都被约束)

```cpp
vector(size_t n, const T& val)
	:_start(nullptr)
	, _finish(nullptr)
	, _endofstarage(nullptr)
{
	const iterator ptr = new T[n];
	_start = ptr;
	_finish = _start + n;
	_endofstarage = _start + n;
	iterator constructor = ptr;
	while (constructor < _finish) {
		new(constructor++) T(val);
	}
}
```

然后就出问题了：

```cpp
void realization9()
{
	//wind::vector<std::string> v(10, "xxxxxxxxx");

	// 10 和 0都被视为int,这是相同的类型
	// 迭代器区间构造参数为InputIterator, InputIterator
	// 是完全相同的类型
	// 而n个val构造，参数为size_t , T
	// 所以如果用n个val构造，要类型提升，int被提升为size_t
	// 迭代器区间构造不用提升，可以直接用，所以会用
	// 迭代器区间构造
	wind::vector<int> v(10, 0);

	for (auto e : v)
	{
		std::cout << e << " ";
	}
	std::cout << std::endl;
}
```

发生语法错误：而且输出信息看不懂。

```shell
生成开始于 17:32...
1>------ 已启动生成: 项目: myVector, 配置: Debug x64 ------
1>main.cpp
1>E:\C language new project\routine\myVector\myVector\myVector.h(43,15): error C2100: 无法取消引用类型为“InputIterator”的操作数
1>E:\C language new project\routine\myVector\myVector\myVector.h(43,15): error C2100:         with
1>E:\C language new project\routine\myVector\myVector\myVector.h(43,15): error C2100:         [
1>E:\C language new project\routine\myVector\myVector\myVector.h(43,15): error C2100:             InputIterator=int
1>E:\C language new project\routine\myVector\myVector\myVector.h(43,15): error C2100:         ]
1>(编译源文件“main.cpp”)
1>    E:\C language new project\routine\myVector\myVector\myVector.h(43,15):
1>    模板实例化上下文(最早的实例化上下文)为
1>        E:\C language new project\routine\myVector\myVector\main.cpp(244,21):
1>        查看对正在编译的函数 模板 实例化“wind::vector<int>::vector<int>(InputIterator,InputIterator)”的引用
1>        with
1>        [
1>            InputIterator=int
1>        ]
1>            E:\C language new project\routine\myVector\myVector\main.cpp(244,21):
1>            请参阅 "realization9" 中对 "wind::vector<int>::vector" 的第一个引用
1>已完成生成项目“myVector.vcxproj”的操作 - 失败。
========== 生成: 0 成功，1 失败，0 最新，0 已跳过 ==========
========== 生成 于 17:32 完成，耗时 01.617 秒 ==========
```

我们的本意是使用10个0去初始化`vector`，但编译器做出了错误识别，它会进入迭代器区间构造，于是自然会出现问题。

编译器遵循谁合适调用谁的原则，会去调用迭代器区间初始化，而不是n个val构造。最简单的解决方案就是多写几份n个val构造。

```cpp
vector(size_t n, const T& val)
	:_start(nullptr)
	, _finish(nullptr)
	, _endofstarage(nullptr)
{
	const iterator ptr = new T[n];
	_start = ptr;
	_finish = _start + n;
	_endofstarage = _start + n;
	iterator constructor = ptr;
	while (constructor < _finish) {
		new(constructor++) T(val);
	}
}

// 多整几个类型,比如int long 之类
// 此时就这个更适配了,比迭代器区间更合适
vector(int n, const T& val)
	:_start(nullptr)
	, _finish(nullptr)
	, _endofstarage(nullptr)
{
	const iterator ptr = new T[n];
	_start = ptr;
	_finish = _start + n;
	_endofstarage = _start + n;
	iterator constructor = ptr;
	while (constructor < _finish) {
		new(constructor++) T(val);
	}
}
```

![image-20241025173807844](https://img.mdwind.online/md/202410251738908.png)

# End