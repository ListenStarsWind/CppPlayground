[TOC]

# myVector

## `Feel`【感受】

### `documentation`[【文档】](https://cplusplus.com/reference/vector/vector/)

#### `Vector`【向量】

`template < class T, class Alloc = allocator<T> > class vector; // generic template`告诉我们`vector`是一个类模版，它的模版参数有两个——一是数据类型`T`，二是空间配置器`Alloc`；空间配置器是用来进行内存管理的——通过内存池的方式，内存池我们之后会专门去说，所以这次的`vector`实现我们都是直接`new delete`的。

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

- T：`Type of the elements`【元素的类型】。当可以`guaranteed`【保证】【T】`while moving`【在移动期间】` not throw`【不抛出异常】，就能把vectors`reallocations`【重新分配】的`implementations`【实现】` optimize to`【优化为】`move elements`【移动元素】`instead of`【而不是】（以往的）`copying them`【复制元素】*详见《string_lesson2》::SGI版本string组织形式*。`member type`【成员类型】`vector::allocator_type`是T的`Aliased`【别名】

- `Alloc`【分配】：这是一个用于内存管理`allocator object`【分配器对象】的`type`【类型】，它为`storage allocation`【内存的分配与管理】提供了一个`model`【模型】。` By default`【在没有特别指定的情况下】，会使用默认的`allocator class template`【分配器类模版】，它实现了`Simplest`【最基本的】`memory allocation`【内存管理】功能；并且不依赖于`Value-independent`具体的数据（类型）；` member type`【成员类型】`vector::allocator_type`是它的`Aliased`【别名】

#### `Member types`【成员类型】

| `member type`【成员类型】                | ` definition`【定义】                                        | ` notes`【注释】                                             |
| ---------------------------------------- | ------------------------------------------------------------ | ------------------------------------------------------------ |
| `value_type`【数据类型】                 | The first template parameter (`T`)                           |                                                              |
| `allocator_type`【分配器类型】           | The second template parameter (`Alloc`)                      | `defaults to`【默认】: `allocator<value_type>`               |
| `reference`【引用】                      | allocator_type::reference                                    | for the default [allocator](https://legacy.cplusplus.com/allocator): ` value_type&` |
| `const_reference`【常引用】              | allocator_type::const_reference                              | for the default [allocator](https://legacy.cplusplus.com/allocator): `const value_type&` |
| `pointer`【指针】                        | allocator_type::pointer                                      | or the default [allocator](https://legacy.cplusplus.com/allocator): `value_type*` |
| `const_pointer`【常指针】                | allocator_type::const_pointer                                | for the default [allocator](https://legacy.cplusplus.com/allocator): `const value_type*` |
| `iterator`【迭代器】                     | a [random access iterator](https://legacy.cplusplus.com/RandomAccessIterator)【随机访问迭代器】 to `value_type` | `convertible to `【可转换为】`const_iterator`                |
| `const_iterator`【常迭代器】             | a [random access iterator](https://legacy.cplusplus.com/RandomAccessIterator) to `const value_type` |                                                              |
| `reverse_iterator`【反向迭代器】         | reverse_iterator\<iterator>                                  |                                                              |
| `const_reverse_iterator`【反向常迭代器】 | reverse_iterator<const_iterator>                             |                                                              |
| `difference_type`【迭代器间隔类型】      | `a signed integral type`【一种有符号整数类型】, `identical to`【等同于】: `iterator_traits<iterator>::difference_type` | `usually`【通常】 `the same as` [ptrdiff_t](https://legacy.cplusplus.com/ptrdiff_t)【与之相同】 |
| `size_type`【大小类型】                  | an `unsigned integral`【无符号整型】 type that can `represent`【表示】 `any non-negative value`【任何非负值】 of `difference_type` | usually the same as [size_t](https://legacy.cplusplus.com/size_t) |

#### `Member functions`【成员函数】

*已在《string_lesson1》::文档部分说过大致功能，在此不作赘述*

|                                                              |                                                        |
| ------------------------------------------------------------ | ------------------------------------------------------ |
| [**(constructor)**](https://legacy.cplusplus.com/reference/vector/vector/vector/) | Construct vector (public member function )             |
| [**(destructor)**](https://legacy.cplusplus.com/reference/vector/vector/~vector/) | Vector destructor (public member function )            |
| [**operator=**](https://legacy.cplusplus.com/reference/vector/vector/operator=/) | `Assign content`【内容赋值】 (public member function ) |

##### **Iterators**:

|                                                              |                                                              |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| [**begin**](https://legacy.cplusplus.com/reference/vector/vector/begin/) | Return iterator to beginning (public member function )       |
| [**end**](https://legacy.cplusplus.com/reference/vector/vector/end/) | Return iterator to end (public member function )             |
| [**rbegin**](https://legacy.cplusplus.com/reference/vector/vector/rbegin/) | Return reverse iterator to reverse beginning (public member function ) |
| [**rend**](https://legacy.cplusplus.com/reference/vector/vector/rend/) | Return reverse iterator to reverse end (public member function ) |
| [**cbegin** ](https://legacy.cplusplus.com/reference/vector/vector/cbegin/)【C++11】 | Return const_iterator to beginning (public member function ) |
| [**cend** ](https://legacy.cplusplus.com/reference/vector/vector/cend/)【C++11】 | Return const_iterator to end (public member function )       |
| [**crbegin** ](https://legacy.cplusplus.com/reference/vector/vector/crbegin/)【C++11】 | Return const_reverse_iterator to reverse beginning (public member function ) |
| [**crend** ](https://legacy.cplusplus.com/reference/vector/vector/crend/)【C++11】 | Return const_reverse_iterator to reverse end (public member function ) |

##### **Capacity**:

|                                                              |                                                              |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| [**size**](https://legacy.cplusplus.com/reference/vector/vector/size/) | Return size (public member function )                        |
| [**max_size**](https://legacy.cplusplus.com/reference/vector/vector/max_size/) | Return maximum size (public member function )                |
| [**resize**](https://legacy.cplusplus.com/reference/vector/vector/resize/) | `Change`【更改】 size (public member function )              |
| [**capacity**](https://legacy.cplusplus.com/reference/vector/vector/capacity/) | Return size of allocated storage capacity (public member function ) |
| [**empty**](https://legacy.cplusplus.com/reference/vector/vector/empty/) | Test `whether`【是否】 vector is `empty`【为空】 (public member function ) |
| [**reserve**](https://legacy.cplusplus.com/reference/vector/vector/reserve/) | `Request`【请求】 a change in capacity (public member function ) |
| [**shrink_to_fit** ](https://legacy.cplusplus.com/reference/vector/vector/shrink_to_fit/)【C++11】 | `Shrink to fit` 【收缩以适应】(public member function )      |

##### `Element access`【元素访问】:

|                                                              |                                                |
| ------------------------------------------------------------ | ---------------------------------------------- |
| <a href="https://legacy.cplusplus.com/reference/vector/vector/operator[]/">**operator[]**</a> | Access element (public member function )       |
| [**at**](https://legacy.cplusplus.com/reference/vector/vector/at/) | Access element (public member function )       |
| [**front**](https://legacy.cplusplus.com/reference/vector/vector/front/) | Access first element (public member function ) |
| [**back**](https://legacy.cplusplus.com/reference/vector/vector/back/) | Access last element (public member function )  |
| [**data** ](https://legacy.cplusplus.com/reference/vector/vector/data/)【C++11】 | Access data (public member function )          |

##### `Modifiers`【修饰符】：

*emplace和emplace_back以后会专门说，现在先跳过。*

|                                                              |                                                              |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| [**assign**](https://legacy.cplusplus.com/reference/vector/vector/assign/) | `Assign`【赋值】 vector `content`【内容】 (public member function ) |
| [**push_back**](https://legacy.cplusplus.com/reference/vector/vector/push_back/) | Add element at the end (public member function )             |
| [**pop_back**](https://legacy.cplusplus.com/reference/vector/vector/pop_back/) | Delete last element (public member function )                |
| [**insert**](https://legacy.cplusplus.com/reference/vector/vector/insert/) | Insert elements (public member function )                    |
| [**erase**](https://legacy.cplusplus.com/reference/vector/vector/erase/) | `Erase`【删除】 elements (public member function )           |
| [**swap**](https://legacy.cplusplus.com/reference/vector/vector/swap/) | Swap content (public member function )                       |
| [**clear**](https://legacy.cplusplus.com/reference/vector/vector/clear/) | `Clear`【清空】 content (public member function )            |
| [**emplace** ](https://legacy.cplusplus.com/reference/vector/vector/emplace/)【C++11】 | `Construct`【构造】 and `insert`【插入】 element (public member function ) |
| [**emplace_back** ](https://legacy.cplusplus.com/reference/vector/vector/emplace_back/)【C++11】 | Construct and insert element at the end (public member function ) |

##### **Allocator**:

|                                                              |                                         |
| ------------------------------------------------------------ | --------------------------------------- |
| [**get_allocator**](https://legacy.cplusplus.com/reference/vector/vector/get_allocator/) | Get allocator (public member function ) |

#### `Non-member function overloads`【非成员函数重载】

|                                                              |                                                              |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| [**relational operators**](https://legacy.cplusplus.com/reference/vector/vector/operators/) | `Relational operators`【关系运算符】 for vector (function template ) |
| [**swap**](https://legacy.cplusplus.com/reference/vector/vector/swap-free/) | `Exchange contents`【交换内容】 of vectors (function template ) |

#### `Template specializations`【模版的特别实例化】

*为了满足某些特别的需求，特别实现的vector版本，就像通用交换模版和容器内交换函数的关系。*

|                                                              |                                                 |
| ------------------------------------------------------------ | ----------------------------------------------- |
| [**vector\<bool>**](https://legacy.cplusplus.com/reference/vector/vector-bool/) | Vector of bool (class template specialization ) |

### `using`【使用】

```cpp
#include<vector>
#include<string>
#include<iostream>

// construct https://legacy.cplusplus.com/reference/vector/vector/vector/
void using1()
{
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

![image-20241023111438888](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410231114993.png)

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

![image-20241023105048189](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410231050612.png)

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

我们首先通过`resize`为二维数组进行初始化，由于我们没有输入第二个参数，所以第二个参数实际上就是缺省值，根据文档，如果元素类型为自定义类型，就会调用它的默认构造函数，然后它的默认构造是使用分配器的，分配器还没学所以就不继续深究了，但我们现在可以大致猜一下，应该是空的vector\<int>。经过`resize`操作之后，vector<vector\<int>> v就有了`numRows`个元素，这样就已经搭好了二维数组的基本框架。

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

![image-20241023171844217](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410231718830.png)

我们真正要看的内容，估计在\<stl_vector.h>里：

建议把`STL`的文件夹直接用VS打开，这样方便显示。

比如，如果直接把\<stl_vector.h>扔到某个项目里，那它就是杂项文件，有些东西看不到：

你看它无法识别这个宏：

![image-20241023172916746](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410231729217.png)

但如果直接打开文件夹，就能看到了：

![image-20241023173002384](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410231730430.png)

![image-20241023173046680](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410231730771.png)

`gcc-master`是我直接从github上拷下来的源代码，但太新了，看原码要看旧的，新的版本封装得比较好，所以可读性低。

由于它们都在同一个文件夹下，所以就可以识别了：

![image-20241023173418296](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410231734752.png)

![image-20241023173456452](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410231734836.png)

这样就可以看到了，这实际是命名空间。命名空间不是关键内容，那就跳过。什么是关键内容，比如成员变量就是关键内容，还有什么构造插入什么的，这才是体现代码核心逻辑的地方：

![image-20241023174115364](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410231741813.png)

这个就是我们的成员变量，是三个指针。大致可以猜出它们三个是干什么的：`_M_start`可能是存储元素空间的起始地址，其它两个应该一个是最后一个有效元素的下一元素地址，一个是存储空间末元素下一元素的地址。从名字上来看，`_M_end_of_storage`应该是存储空间的末尾地址，这样的话，`_M_finish`应该是有效元素的末尾。

接下来就是找成员函数去确认一下猜想，比如从`begin`and`end`，`size`，`capacity`大致可以证明我们的猜想：

![image-20241023182919380](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410231829059.png)







首先为了和标准库中的`vector`作区分，我们把整个模版包进我们自己的命名域中，对于我个人而言，我的英文名一般是`wind`，所以我就用这个名字做命名域的名字啦。之后，我们把模版类型`T`包装一下，把它的指针重命名为迭代器，为了适应常对象，我们又添加了常迭代器。注意，迭代器在类外也是要能被使用的，所以一定要放在公共区中，别放私有里了。

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
}
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

![image-20241025151637581](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410251516740.png)

问题出在`reserve`上，`reserve`是一种深层次的浅拷贝，这种浅拷贝藏得很深，第一次写不一定能想到，我们在`reserve`中使用的是`memcpy`进行拷贝，`memcpy`只拷贝对象本体，而不拷贝与对象联系内存块中的数据。

![image-20241025084603788](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410250846886.png)

![image-20241025085019556](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410250850708.png)

![image-20241025085315439](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410250853574.png)

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

![image-20241025160138382](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410251601470.png)

既然`reserve`写了，那就顺手写写`resize`吧。

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

如果参数小于当前元素个数，那就是删除，其实不用真删除，直接把元素终止指针`_finish`移过去就行了。元素个数大于当前个数，那就是追加，注意，模版里的元素不一定都是内置类型，所以不能用0做缺省值，而是应用默认构造做缺省值，为了提高效率，我们使用了常引用，常引用可以延长对象的生命周期，这样，匿名对象就会在`val`生命周期结束后再被析构，而不是在这行之后就被析构。另外说一下，之前为了逻辑自洽我们说内置类型没有构造函数，实际上，内置类型是有默认构造函数的。

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

![image-20241025163333567](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410251633611.png)

调试一下，就可以找到问题了。

![image-20241025163926799](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410251639146.png)

![image-20241025163946217](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410251639258.png)

![image-20241025164037994](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410251640354.png)

![image-20241025164052910](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410251640951.png)

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

![image-20241025165532021](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410251655087.png)

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

![image-20241025170447171](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410251704233.png)

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

![image-20241025171116534](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410251711592.png)

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

![image-20241025170938425](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410251709490.png)

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

![image-20241025171556326](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410251715391.png)

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

接下里我们写一下迭代器区间构造

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

n个val构造

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

![image-20241025173807844](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202410251738908.png)

# End