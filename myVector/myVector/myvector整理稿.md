# myVector

## 初识与使用（`Feel`）

### 标准库文档（[`Documentation`](https://cplusplus.com/reference/vector/vector/)）

#### 向量（`Vector`）

`template < class T, class Alloc = allocator<T> > class vector; // generic template` 表明 `vector` 是一个类模板，它接收两个模板参数：一是元素的数据类型 `T`，二是空间配置器 `Alloc`。空间配置器用于将具体的内存分配、释放操作与容器本身的逻辑解耦合。由于空间配置器与底层内存管理涉及较多前置知识，我们会在后续文章中专门展开；在本文的初始视角中，可以先从基础的动态内存管理逻辑入手来理解 `vector`。

`vector` 是用于表示大小可变数组（动态数组）的序列容器。

就像普通数组一样，`vector` 使用连续的存储位置存放元素。这意味着它的元素不仅可以通过下标访问，也可以通过对指向元素的常规指针进行偏移量运算来访问，效率与普通数组相当。但与普通数组不同的是，`vector` 的大小可以动态改变，其底层存储空间的分配与释放由容器自动管理。

在内部，`vector` 使用动态分配的数组来存储元素。当插入新元素导致空间不足时，这个数组可能需要重新分配内存（`Reallocation`）以增大大小——这意味着需要分配一个新的数组，并将原有的全部元素迁移到新空间中。就处理时间而言，这是一项开销相对较大的任务；因此，`vector` 并不会在每次向容器添加元素时都重新分配内存。

相反，`vector` 容器通常会预留一些额外的存储空间，以适应未来可能的增长。因此，容器的实际容量（`capacity`）可能会大于严格容纳当前元素所需的存储大小（`size`）。不同的标准库可以实现不同的增长策略，以便在内存使用量和重新分配频率之间取得平衡。但无论采用何种系数，重新分配都应仅在容量呈对数频率增长的间隔处发生（即每次扩容按固定比例倍增，减少将元素从原空间迁移到新空间的次数），从而保证在末尾插入单个元素时能够提供分摊常数级别（`Amortized constant`）的时间复杂度（详见 `push_back`）。

因此，与普通数组相比，`vector` 会消耗更多的内存，以此换取高效管理存储空间和动态增长的能力。

与其他动态序列容器（如双端队列 `deque`、双向链表 `list` 和单向链表 `forward_list`）相比，`vector` 在随机访问元素方面与普通数组一样高效，并且在末尾添加或删除元素时也相对高效。但对于在末尾以外的位置添加或删除元素的操作，`vector` 需要搬移后续元素，性能表现不如链表结构；同时，由于扩容和元素搬移会改变元素的存储位置，`vector` 的迭代器和引用在操作前后的有效性（一致性）也相对较弱。

#### 容器属性（`Container properties`）

- **有序性（`Sequence`）**：序列容器中的元素按照严格的线性顺序排列，单个元素通过它们在序列中的位置进行访问。
- **动态数组（`Dynamic array`）**：允许直接访问序列中的任何元素，甚至可以通过指针算术运算（例如借助 `data()` 接口）进行访问，并且在序列末尾添加或删除元素的操作具有较快的速度。
- **空间配置器感知（`Allocator-aware`）**：容器使用一个空间配置器对象来动态处理其存储需求。

#### 模板参数（`Template parameters`）

- `T`：元素的类型。当能够保证 `T` 在移动期间不会抛出异常时，`vector` 在重新分配内存的实现中可以优化为移动元素（`move`）而非复制元素（`copy`）（相关背景可参考前文[《string》](https://blog.csdn.net/venti0411/article/details/170494383?spm=1011.2415.3001.5331)）。成员类型 `vector::value_type` 是 `T` 的别名。
- `Alloc`：用于定义内存分配与管理模型的空间配置器对象类型。在没有特别指定的情况下，默认使用 `allocator<T>` 类模板，它实现了最基础的、不依赖于具体数据类型（`Value-independent`）的内存分配功能。成员类型 `vector::allocator_type` 是它的别名。

#### 成员类型（`Member types`）

考虑到空间配置器（`allocator`）及其适配器（`allocator_traits`）需要较多背景知识，本文的实现视角会暂且略过它们的内部细节。对于下表中引用、常引用或指针等类型是如何从配置器中提取出来的，这里先不必深究，重点关注它们最终对应的实际类型即可。

| 成员类型（`member type`） | 定义（`definition`） | 注释（`notes`） |
| --- | --- | --- |
| `value_type`【数据类型】 | 第一个模板参数（`T`） | |
| `allocator_type`【分配器类型】 | 第二个模板参数（`Alloc`） | 默认为：`allocator<value_type>` |
| `reference`【引用】 | `allocator_type::reference`（C++11 起直接定义为 `value_type&`） | 默认分配器下为：`value_type&` |
| `const_reference`【常引用】 | `allocator_type::const_reference`（C++11 起直接定义为 `const value_type&`） | 默认分配器下为：`const value_type&` |
| `pointer`【指针】 | `allocator_traits<allocator_type>::pointer` | 默认分配器下为：`value_type*` |
| `const_pointer`【常指针】 | `allocator_traits<allocator_type>::const_pointer` | 默认分配器下为：`const value_type*` |
| `iterator`【迭代器】 | 指向 `value_type` 的[随机访问迭代器](https://legacy.cplusplus.com/RandomAccessIterator) | 可转换为 `const_iterator` |
| `const_iterator`【常迭代器】 | 指向 `const value_type` 的[随机访问迭代器](https://legacy.cplusplus.com/RandomAccessIterator) | |
| `reverse_iterator`【反向迭代器】 | `reverse_iterator<iterator>` | |
| `const_reverse_iterator`【常反向迭代器】 | `reverse_iterator<const_iterator>` | |
| `difference_type`【差值类型】 | 一种有符号整数类型，等同于：`iterator_traits<iterator>::difference_type` | 表示两个迭代器之间的距离，通常与 [`ptrdiff_t`](https://legacy.cplusplus.com/ptrdiff_t) 相同 |
| `size_type`【大小类型】 | 一种无符号整数类型，可表示 `difference_type` 的任何非负值 | 通常与 [`size_t`](https://legacy.cplusplus.com/size_t) 相同 |

#### 成员函数（`Member functions`）

*常见接口的大致功能已在前文[《string》](https://blog.csdn.net/venti0411/article/details/170494383?spm=1011.2415.3001.5331)的文档部分介绍过，在此不作赘述。*

| 函数名称 | 功能说明 |
| --- | --- |
| [**(constructor)**](https://legacy.cplusplus.com/reference/vector/vector/vector/) | 构造 `vector`（公共成员函数） |
| [**(destructor)**](https://legacy.cplusplus.com/reference/vector/vector/~vector/) | 析构 `vector`（公共成员函数） |
| [**operator=**](https://legacy.cplusplus.com/reference/vector/vector/operator=/) | 内容赋值（公共成员函数） |

##### 迭代器（`Iterators`）

| 函数名称 | 功能说明 |
| --- | --- |
| [**begin**](https://legacy.cplusplus.com/reference/vector/vector/begin/) | 返回指向起始位置的迭代器（公共成员函数） |
| [**end**](https://legacy.cplusplus.com/reference/vector/vector/end/) | 返回指向末尾（尾后位置）的迭代器（公共成员函数） |
| [**rbegin**](https://legacy.cplusplus.com/reference/vector/vector/rbegin/) | 返回指向反向起始位置的反向迭代器（公共成员函数） |
| [**rend**](https://legacy.cplusplus.com/reference/vector/vector/rend/) | 返回指向反向末尾位置的反向迭代器（公共成员函数） |
| [**cbegin**](https://legacy.cplusplus.com/reference/vector/vector/cbegin/)【C++11】 | 返回指向起始位置的 `const_iterator`（公共成员函数） |
| [**cend**](https://legacy.cplusplus.com/reference/vector/vector/cend/)【C++11】 | 返回指向末尾的 `const_iterator`（公共成员函数） |
| [**crbegin**](https://legacy.cplusplus.com/reference/vector/vector/crbegin/)【C++11】 | 返回指向反向起始位置的 `const_reverse_iterator`（公共成员函数） |
| [**crend**](https://legacy.cplusplus.com/reference/vector/vector/crend/)【C++11】 | 返回指向反向末尾位置的 `const_reverse_iterator`（公共成员函数） |

##### 容量（`Capacity`）

| 函数名称 | 功能说明 |
| --- | --- |
| [**size**](https://legacy.cplusplus.com/reference/vector/vector/size/) | 返回有效元素个数（公共成员函数） |
| [**max_size**](https://legacy.cplusplus.com/reference/vector/vector/max_size/) | 返回可容纳的最大元素数（公共成员函数） |
| [**resize**](https://legacy.cplusplus.com/reference/vector/vector/resize/) | 更改有效元素个数（公共成员函数） |
| [**capacity**](https://legacy.cplusplus.com/reference/vector/vector/capacity/) | 返回当前已分配存储空间的容量大小（公共成员函数） |
| [**empty**](https://legacy.cplusplus.com/reference/vector/vector/empty/) | 测试 `vector` 是否为空（公共成员函数） |
| [**reserve**](https://legacy.cplusplus.com/reference/vector/vector/reserve/) | 请求改变容量（公共成员函数） |
| [**shrink_to_fit**](https://legacy.cplusplus.com/reference/vector/vector/shrink_to_fit/)【C++11】 | 收缩容量以适应当前大小（公共成员函数） |

##### 元素访问（`Element access`）

| 函数名称 | 功能说明 |
| --- | --- |
| [**operator[]**](https://legacy.cplusplus.com/reference/vector/vector/operator[]/) | 访问元素（公共成员函数） |
| [**at**](https://legacy.cplusplus.com/reference/vector/vector/at/) | 访问元素，带越界检查（公共成员函数） |
| [**front**](https://legacy.cplusplus.com/reference/vector/vector/front/) | 访问第一个元素（公共成员函数） |
| [**back**](https://legacy.cplusplus.com/reference/vector/vector/back/) | 访问最后一个元素（公共成员函数） |
| [**data**](https://legacy.cplusplus.com/reference/vector/vector/data/)【C++11】 | 返回指向底层元素数组的指针（公共成员函数） |

##### 修改器（`Modifiers`）

*`emplace` 和 `emplace_back` 以后会专门讨论，目前先略过。*

| 函数名称 | 功能说明 |
| --- | --- |
| [**assign**](https://legacy.cplusplus.com/reference/vector/vector/assign/) | 为 `vector` 重新赋值内容（公共成员函数） |
| [**push_back**](https://legacy.cplusplus.com/reference/vector/vector/push_back/) | 在末尾添加元素（公共成员函数） |
| [**pop_back**](https://legacy.cplusplus.com/reference/vector/vector/pop_back/) | 删除最后一个元素（公共成员函数） |
| [**insert**](https://legacy.cplusplus.com/reference/vector/vector/insert/) | 插入元素（公共成员函数） |
| [**erase**](https://legacy.cplusplus.com/reference/vector/vector/erase/) | 删除元素（公共成员函数） |
| [**swap**](https://legacy.cplusplus.com/reference/vector/vector/swap/) | 交换内容（公共成员函数） |
| [**clear**](https://legacy.cplusplus.com/reference/vector/vector/clear/) | 清空内容（公共成员函数） |
| [**emplace**](https://legacy.cplusplus.com/reference/vector/vector/emplace/)【C++11】 | 原地构造并插入元素（公共成员函数） |
| [**emplace_back**](https://legacy.cplusplus.com/reference/vector/vector/emplace_back/)【C++11】 | 在末尾原地构造并插入元素（公共成员函数） |

##### 空间配置器（`Allocator`）

| 函数名称 | 功能说明 |
| --- | --- |
| [**get_allocator**](https://legacy.cplusplus.com/reference/vector/vector/get_allocator/) | 获取空间配置器（公共成员函数） |

#### 非成员函数重载（`Non-member function overloads`）

| 函数名称 | 功能说明 |
| --- | --- |
| [**relational operators**](https://legacy.cplusplus.com/reference/vector/vector/operators/) | `vector` 的关系运算符（函数模板） |
| [**swap**](https://legacy.cplusplus.com/reference/vector/vector/swap-free/) | 交换两个 `vector` 的内容（函数模板） |

#### 模板特化（`Template specializations`）

*为了满足某些特定需求而专门实现的 `vector` 版本，类似于通用交换模板与容器内交换函数的关系。*

| 特化版本 | 功能说明 |
| --- | --- |
| [**vector\<bool\>**](https://legacy.cplusplus.com/reference/vector/vector-bool/) | 针对 `bool` 类型的 `vector`（类模板特化） |

### 基本使用（`Using`）

#### 构造与遍历

`std::vector` 默认使用标准库提供的缺省空间配置器，其本身的执行效率已经比较高；如果我们自己编写了自定义的空间配置器（例如 `wind::allocator<T>`），也可以通过第二个模板参数传入。下面这段代码展示了 `vector` 的常见构造方式、二维数组构建以及三种遍历方式：

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

    // 定义 10 个元素，并将其都初始化为 0
    vector<int> v2(10, 0);

    // 使用容器的迭代器区间进行初始化
    vector<int> v3(v2.begin(), v2.end());
    std::string s("Hello World!");
    vector<char> v4(s.begin(), s.end());

    // 类型转换：char（ASCII 码形式） -> int
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

    // 范围 for
    for (auto& n : v5) {
        std::cout << ++n << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

运行结果如下：

```bash
[wind@ubuntu-asus build]$ ./main-debug
72 101 108 108 111 32 87 111 114 108 100 33 
Hello World!
73 102 109 109 112 33 88 112 115 109 101 34 
[wind@ubuntu-asus build]$ 
```

#### 内存分配与扩容机制观测

我们可以通过连续调用 `push_back` 并监测 `capacity()` 的变化，来观察不同标准库实现下的扩容策略：

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

在 P.J. 版本（MSVC 工具链）下，早期使用 Visual Studio 2022 的运行结果如下：

![image-20241023111438888](https://img.mdwind.online/md/202410231114993.png)

后来改用 VS Code 作为前端、2026 版本的 MSVC 工具链作为后端重复该实验，结果一致，说明工具链迭代并未改变其约 1.5 倍扩容的策略：

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

而在 Linux 环境下使用 Clang 或 G++（SGI STL 演进版本）编译运行，容量则按 2 倍的方式增长：

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

### 常见例题（`Example`）

#### [二叉树的前序遍历](https://leetcode.cn/problems/binary-tree-preorder-traversal/)

![image-20241023105048189](https://img.mdwind.online/md/202410231050612.png)

这道题可以用来对比 C 语言与 C++ 在接口设计和动态数组管理上的差别。在 LeetCode 的 C 语言接口中，函数需要将结果数组返回给调用方，同时通过输出型参数 `returnSize` 返回数组长度。由于原生动态数组不能自动扩容，为了确定 `malloc` 动态开辟数组的大小，我们需要先遍历一次二叉树求出节点总数，然后再在递归遍历中通过二级指针控制数据的写入位置：

```c
int BTSize(struct TreeNode* root) {
    if (root == NULL)
        return 0;
    return BTSize(root->left) + BTSize(root->right) + 1;
}

void _preorderTraversal(struct TreeNode* root, int** pCurrent) {
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

而在 C++ 中，因为 `vector` 自身记录了元素个数并且支持动态扩容，接口只需要直接返回 `vector<int>` 即可，前序遍历和元素插入可以同步进行：

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

这道题利用按位异或（`^`）的性质即可解决（其进阶版本是[《数组中数字出现的次数》](https://leetcode.cn/problems/shu-zu-zhong-shu-zi-chu-xian-de-ci-shu-lcof)，当时我把它叫作《找两个单身狗》）：

```cpp
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int val = 0;
        for (auto curr : nums) {
            val ^= curr;
        }
        return val;
    }
};
```

#### [杨辉三角](https://leetcode.cn/problems/pascals-triangle)

这道题如果用 C 语言实现，首先要手动建立一个二维数组：先建立一个指针数组 `int**`，再建立多个一维数组 `int*`，并把每个一维数组的首元素地址写入指针数组中。因为返回的是二级指针，为了让调用方能够遍历这个二维数组，接口还需要传入 `returnSize` 和 `returnColumnSizes` 来分别描述行数和每一行的列数——其中 `*returnSize` 被赋值为 `numRows`，而 `returnColumnSizes` 则指向一个记录每一行元素个数的一维数组。

用 C++ 的话，直接使用 `vector<vector<int>>` 即可建立一个二维数组，且空间分配无需手动管理。C 语言访问二维数组需要连续解引用，C++ 底层虽然也是解引用，但对用户而言，直接通过两次 `operator[]` 重载就可以访问元素。

我们首先通过 `resize` 对外层二维数组进行初始化。由于没有输入第二个参数，第二个参数会使用缺省值；根据文档，当元素类型为自定义类型时，会调用它的默认构造函数，因此外层 `vector<vector<int>> v` 中会生成 `numRows` 个空的 `vector<int>`，从而搭好二维数组的基本框架。

接下来我们对 `vector<vector<int>>` 中的每一个 `vector<int>` 元素进行初始化。观察杨辉三角可以发现，每一行的元素个数等于其所在行数：第一行有 1 个数，第二行有 2 个数，第三行有 3 个数……由于我们使用从 `0` 开始的下标访问外层元素，第 `i` 行的大小应设为 `i + 1`。这次调用 `v[i].resize(i + 1)` 同样没有传入第二个参数，内层 `int` 元素会使用缺省值 `0`。此时的缺省值起到了占位的作用，使我们可以直接通过 `[]` 重载访问二维数组中的 `int` 元素；同时，因为每一行的首尾数字都是 `1`，我们可以在这一步顺手完成赋值。

最后进行一次遍历。除去首尾的数字之外，其余每个数字都等于上一行同下标的数字与上一行前一下标的数字之和（例如第三行下标为 `1` 的数字 `2`，就是由第二行下标为 `1` 和下标为 `0` 的两个数字相加得到的）。计算完成后将 `v` 返回即可：

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

## 模拟实现（`Realization`）

### 标准库源码结构观察

在动手编写之前，我们先看看标准库源码是如何组织 `vector` 的。打开 `<vector>` 头文件，里面只有数十行引导代码：

![image-20241023171844217](https://img.mdwind.online/md/202410231718830.png)

真正的核心实现位于 `<stl_vector.h>` 中。阅读源码时，建议用编辑器直接打开整个 `STL` 源码文件夹，这样方便宏解析与符号跳转。如果只是单独把 `<stl_vector.h>` 放到某个项目里，它会被视作杂项文件，导致部分宏无法识别：

![image-20241023172916746](https://img.mdwind.online/md/202410231729217.png)

而直接打开源码文件夹后，上下文依赖就能正常显示了（下图中的 `gcc-master` 是从 GitHub 拉取的较新源码，新版源码的封装层级较多，阅读源码时可以先从早期版本入手）：

![image-20241023173002384](https://img.mdwind.online/md/202410231730430.png)

![image-20241023173046680](https://img.mdwind.online/md/202410231730771.png)

由于相关头文件都在同一个文件夹下，外层的宏就可以被识别出来了：

![image-20241023173418296](https://img.mdwind.online/md/202410231734752.png)

![image-20241023173456452](https://img.mdwind.online/md/202410231734836.png)

可以看到这个宏实际上表示命名空间。略过外围命名空间，我们重点关注类的成员变量以及构造、插入等体现核心逻辑的部分：

![image-20241023174115364](https://img.mdwind.online/md/202410231741813.png)

这里的成员变量是三个指针：`_M_start`、`_M_finish` 和 `_M_end_of_storage`。从命名上大致可以推测出它们的职责：`_M_start` 是存储元素空间的起始地址，其余两个指针中，一个是最后一个有效元素的下一位置地址，另一个是整个存储空间末尾的下一位置地址。结合名称来看，`_M_end_of_storage` 对应存储空间的末尾，而 `_M_finish` 则对应有效元素的末尾。

接着查看 `begin`、`end`、`size` 和 `capacity` 等成员函数的实现，可以验证这一判断：

![image-20241023182919380](https://img.mdwind.online/md/202410231829059.png)

### 类型接口与成员变量设计

为了和标准库中的 `std::vector` 作区分，我们把整个类模板放进自定义的命名空间 `wind` 中。

接下来我们先看类的类型接口（`Member types`）。以往我们提到“接口”，通常是指函数接口，但现在可以把接口的概念进一步拓宽：一个类向外提供哪些可提取的内嵌类型，同样是它的重要行为特征。而且，这种特性的使用不依赖于某个已经存在的对象或静态成员，只要将类型别名在 `public` 区公开，外部就能随时通过作用域操作符取出它们，这在泛型编程场景下发挥着独特的作用。

在这里，由于我配套编写了一个实验性质的空间配置器 `wind::allocator` 及其对应的适配器 `wind::allocator_traits`，因此部分类型直接通过提取适配器的类型接口获得；如果读者只想实现一个基础版本的 `vector`，直接以模板参数 `T` 为基础定义这些类型别名即可。

```cpp
#pragma once

#include <type_traits>

#include "allocator.hpp"
#include "allocator_traits.hpp"

namespace wind {
template <class T, class Alloc = wind::allocator<T>>
    requires(std::is_object_v<T>)  // 约束：这应该是个对象类型，而不是引用、函数等其他类型
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
```

在这段定义中，有两处细节值得说明：
一是其中的两个引用类型（`reference` 与 `const_reference`）在不同的 C++ 标准中有所差异：在 C++11 之前，这两个引用类型一般也是从空间配置器中取出来的；但在 C++11 引入适配器之后，标准对配置器不再做这一公开接口要求，因此改为了直接基于 `value_type` 定义。
二是我们增加了一处静态断言 `static_assert`，用于在编译期检查从空间配置器适配器中取出的核心数据类型是否与 `T` 相同；如果不相同，说明传入的配置器类型与容器元素类型不匹配，直接在编译期报错。

> **旁注：容器、空间配置器适配器与空间配置器之间的分层关系**
>
> 考虑到空间配置器及其适配器综合利用了较多 C++ 特性，本文的核心视角是略过它们的内部细节来实现 `vector`。但为了看懂后续代码中的调用形式，这里用一张结构图简要说明三者之间的层次关系：
>
> ```
> +-----------------------------------------------------------------------+
> |                        容器层: wind::vector<T, Alloc>                  |
> |  不直接操作底层 Alloc，而是统一向适配器请求类型接口与内存/对象管理操作  |
> +-----------------------------------------------------------------------+
>                                     |
>              提取类型 / 调用静态方法 | (allocate / construct / destroy / deallocate)
>                                     v
> +-----------------------------------------------------------------------+
> |             适配层: wind::allocator_traits<allocator_type>            |
> |  - 若底层配置器提供了某类型接口（如 pointer），则从配置器中一路取出   |
> |  - 若底层配置器未提供，则由适配器根据 value_type 自动推导出默认类型   |
> +-----------------------------------------------------------------------+
>                                     |
>                      转发底层空间操作 |
>                                     v
> +-----------------------------------------------------------------------+
> |                     配置器层: wind::allocator<T>                      |
> |                 负责底层原始空间的分配与释放等具体操作                |
> +-----------------------------------------------------------------------+
> ```
>
> 可以看到，容器中的这些类型接口，有的是从空间配置器里面一路透传取出来的，有的则是当空间配置器没有显式提供时，由适配器自动推导配出来的。

为了便于理解，下表解构了这些类型封装，给出当假设 `T` 为 `int` 时展开后的确切类型：

| 类型别名 | 定义来源 | 展开后的具体类型 | 说明 |
| --- | --- | --- | --- |
| `value_type` | `T` | `int` | 容器存储的元素类型 |
| `allocator_type` | `Alloc` | `wind::allocator<int>` | 容器使用的空间配置器类型 |
| `allocator_traits_type` | `wind::allocator_traits<allocator_type>` | `wind::allocator_traits<wind::allocator<int>>` | 配置器适配器，统一提供类型及操作接口 |
| `reference` | `value_type&` | `int&` | 元素的可修改左值引用 |
| `const_reference` | `const value_type&` | `const int&` | 元素的只读左值引用 |
| `pointer` | `allocator_traits_type::pointer` | `int*` | 默认配置器提供原始指针；自定义配置器可能提供花式指针 |
| `const_pointer` | `allocator_traits_type::const_pointer` | `const int*` | 指向只读元素的指针类型 |
| `iterator` | `pointer` | `int*` | 当前实现直接将指针作为迭代器 |
| `const_iterator` | `const_pointer` | `const int*` | 当前实现使用指向只读元素的指针作为迭代器 |
| `difference_type` | `allocator_traits_type::difference_type` | `std::ptrdiff_t` | 表示迭代器之间的距离，可为负数 |
| `size_type` | `allocator_traits_type::size_type` | `std::size_t` | 表示容器大小、容量及元素数量 |

接下来，我们依据之前观察到的源码结构，给 `vector` 加上私有成员变量：

![](https://img.mdwind.online/img/20261113171525485.png)

![](https://img.mdwind.online/img/20261113171750544.png)

除了维护连续空间的三个指针外，这里还有第四个私有成员 `_alloc`（空间配置器对象），负责与适配器配合执行各类内存与对象管理任务；如果读者是直接用 `new` 和 `delete` 来模拟实现，则不需要这个成员。

另外值得一提的是，在早期的历史写法中，我曾把三个指针成员的类型声明为 `iterator`：

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
} // 历史写法：用迭代器作为底层指针成员的类型声明并不妥当，语义上应当直接使用 pointer
```

现在回看，尽管在 `vector` 中 `iterator` 底层也是指针，但迭代器本质上是面向遍历的抽象概念，而容器内部直接维护存储空间边界的成员变量，在语义上应当明确使用 `pointer` 类型。

接下来我们先写一个基本的默认构造函数，其余构造函数因为涉及一些容易踩坑的细节，稍后再展开。由于模板类的声明和定义分离到不同文件会出现链接问题，我们的定义都直接写在头文件中：

```cpp
vector()
    : _start(nullptr)
    , _finish(nullptr)
    , _endofstorage(nullptr)
{}
```

这个默认构造函数只是把指针成员初始化为空指针；如果在成员变量声明处已经给出了缺省值 `= nullptr`，甚至可以不写初始化列表，直接写成 `vector() {}`。那么问题来了：既然编译器自己能生成默认构造函数，能不能直接不写呢？如果整个类一个构造函数都不写，确实可以交给编译器生成；但我们稍后还要编写拷贝构造、区间构造等其他构造函数，一旦用户显式定义了任何构造函数，编译器就不再自动生成默认构造函数了。此时如果省略 `vector()`，我们的容器就无法无参构造了，因此需要显式保留。

### 容器状态与基础访问接口

现在我们先不着急实现析构函数，先把那些表示容器状态与首尾迭代器的基础函数接口写上去。注意这些函数都没有修改成员变量，为了适配常对象（`const` 对象），它们都需要提供 `const` 版本：

```cpp
size_type size() const noexcept {
    return _finish - _start;
}

size_type capacity() const noexcept {
    return _endofstorage - _start;
}

bool empty() const noexcept {
    return begin() == end();
}

iterator begin() noexcept {
    return _start;
}

iterator end() noexcept {
    return _finish;
}

const_iterator begin() const noexcept {
    return _start;
}

const_iterator end() const noexcept {
    return _finish;
}
```

### 扩容机制（`reserve`）：从浅拷贝问题到异常安全设计

在实现插入操作之前，我们需要先实现负责扩容的 `reserve` 函数。`reserve` 中文常译作“预留”，文档中也说明了，它对容量的调整是一种请求而非强制命令：只有当目标容量大于当前容量 `capacity()` 时，容器才会执行异地扩容；如果输入参数小于或等于当前容量，出于效率考虑不做任何操作。此外，由于 `size()` 和 `capacity()` 都是通过指针相减计算出来的，为了避免修改 `_start` 指针后干扰原元素个数的计算，在调整指针之前需要先用局部变量保存原有的 `oldSize`。

#### 初学阶段的常见问题：`memcpy` 引发的深层次浅拷贝

在初学阶段，如果直接使用 `new[] / delete[]` 配合 `memcpy` 来实现 `reserve` 和 `push_back`，很容易写出下面这样的代码：

```cpp
// 存在隐患的历史实现：使用 memcpy 拷贝元素
void reserve(size_t newCapacity) {
    if (newCapacity > capacity()) {
        size_t oldSize = size();
        iterator ptr = new T[newCapacity];
        memcpy(ptr, _start, sizeof(T) * oldSize);
        delete[] _start;
        _start = ptr;
        _finish = _start + oldSize;
        _endofstarage = _start + newCapacity;
    }
}

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

当存储内置类型（如 `int`）时，这段代码看起来可以正常工作；但当我们用它存放 `std::string` 并触发扩容时，问题就会暴露出来：

```cpp
void realization3() {
    wind::vector<std::string> str_arry;
    auto& v = str_arry;
    v.push_back("1111");
    v.push_back("11111111111111111111111111");
    v.push_back("xxxxxxxxxxxxxxxxxxxxxxxxxx");
    v.push_back("11111111111111111111111111");
    wind::vector<std::string>::iterator it = v.end();
    v.insert(it, "hello word");
    for (auto m : v) {
        std::cout << m << std::endl;
    }
}
```

运行结果如下：

![image-20241025151637581](https://img.mdwind.online/md/202410251516740.png)

为什么后几个字符串会打印出乱码？问题出在 `reserve` 中的 `memcpy` 上。这是一种深层次的浅拷贝：`memcpy` 只是按字节拷贝了 `vector` 数组中存放的 `std::string` 对象本体，而没有拷贝 `std::string` 对象内部指针所关联的堆内存数据。

![image-20241025084603788](https://img.mdwind.online/md/202410250846886.png)

![image-20241025085019556](https://img.mdwind.online/md/202410250850708.png)

![image-20241025085315439](https://img.mdwind.online/md/202410250853574.png)

如上图所示，`delete[] _start` 会先调用旧空间中每个 `std::string` 元素的析构函数，然后再释放旧数组内存。于是，新空间中拷贝出来的 `std::string` 对象所指向的字符堆空间，在旧对象析构时已经被释放了，打印时自然出现乱码。那为什么第一个短字符串 `"1111"` 没有乱码呢？因为标准库中的 `std::string` 内部还有一个固定大小的静态数组 `buff`（小字符串优化），当字符个数小于 16 时，字符直接存放在对象内部的 `buff` 数组中，不涉及外部动态内存的释放；只有当字符个数较多时，才会动态开辟堆内存。

这也印证了前文[《string》](https://blog.csdn.net/venti0411/article/details/170494383?spm=1011.2415.3001.5331)中讨论过的深拷贝与引用计数（写时拷贝）机制：如果不采用引用计数，那么在迁移对象时就必须老老实实执行深拷贝。在仅使用 `new[] / delete[]` 的基础实现下，我们可以通过调用元素的赋值运算符重载 `operator=`（或使用定位 `new` 调用拷贝构造）来替代 `memcpy`：

```cpp
void reserve(size_t newCapacity) {
    if (newCapacity > capacity()) {
        const size_t oldSize = size();
        iterator ptr = new T[newCapacity];
        for (size_t transport = 0; transport < oldSize; transport++) {
            // 使用 T 的 operator= 重载完成深拷贝
            ptr[transport] = _start[transport];
        }
        delete[] _start;
        _start = ptr;
        _finish = _start + oldSize;
        _endofstarage = _start + newCapacity;
    }
}
```

修复之后再次运行，输出就恢复正常了：

![image-20241025160138382](https://img.mdwind.online/md/202410251601470.png)

#### 引入空间配置器与异常安全的现代实现

上面的历史版本虽然修正了 `memcpy` 浅拷贝的问题，但直接 `new T[newCapacity]` 会将整个新容量区间内的元素全部默认构造一遍，再用赋值操作覆盖有效元素，既要求类型 `T` 必须具备默认构造函数，也带来了额外的构造开销。接下来我们看引入空间配置器、容量上限审议、移动语义与异常回退机制后的实现版本：

```cpp
    void reserve(size_type minCapacity) {
        // 取出适配器提供的最大数目，作为检查的判断依据
        const size_type maxCapacity = allocator_traits_type::max_size(_alloc);

        if (minCapacity > maxCapacity) throw std::length_error("wind::vector::reserve");

        size_type oldSize = size();
        size_type oldCapacity = capacity();

        if (oldCapacity >= minCapacity) return;

        // 小于等于 1 时，为了避免 / 2 仍旧为 0，预选增量定为 4
        size_type increment = oldCapacity <= 1 ? 4 : oldCapacity / 2;
        // 对当前容量进行审议，在确保加上 0.5 倍不超过上限的情况下才加上
        // 但 maxCapacity 极小时，4 可能会大于它，造成 increment 大于上限的情况
        // 所以 increment 不能作为被减数参与加减计算
        size_type newCapacity =
            increment >= maxCapacity - oldCapacity ? maxCapacity : oldCapacity + increment;

        newCapacity = std::max(newCapacity, minCapacity);
        pointer ptr = allocator_traits_type::allocate(_alloc, newCapacity);
        pointer curr = ptr;

        size_type idx = 0;
        try {
            for (; idx < oldSize; idx++) {
                // 使用原来的对象参与新对象的构造
                // std::move_if_noexcept：如果移动构造保证不抛异常，则转为右值，匹配移动语义构造；
                // 移动构造可能抛异常且允许拷贝时，优先使用拷贝构造；不支持拷贝构造时，仍然尝试移动
                allocator_traits_type::construct(_alloc, curr + idx,
                                                 std::move_if_noexcept(_start[idx]));
            }
        } catch (...) {
            // 如果中途构造抛出异常，析构之前已经成功构造的新元素，并释放新空间
            size_type firefighter = 0;
            for (; firefighter < idx; firefighter++) {
                allocator_traits_type::destroy(_alloc, curr + firefighter);
            }
            allocator_traits_type::deallocate(_alloc, ptr, newCapacity);
            // 向上交接异常
            throw;
        }

        // 为了能够进行回退，我们必须在新元素全部构造完成之后，再析构原先对应的旧元素
        for (idx = 0; idx < oldSize; idx++) {
            allocator_traits_type::destroy(_alloc, _start + idx);
        }
        // 释放原先的旧空间（在它们确实存在的情况下）
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

这段代码中涉及到几个需要逐步理清的设计细节：

1. **新容量的审议逻辑与无符号减法边界**
   受限于类型表示范围或配置器自身的规定，容器能够申请的空间大小（以元素个数为单位）存在一个上限 `maxCapacity`。在函数开头，我们先对传入的最小目标容量 `minCapacity` 进行了检查，如果超过上限则直接抛出 `std::length_error` 异常。
   接下来，我们在此处融合了按 1.5 倍系数扩容的策略：为了防止直接乘以 1.5 导致超出上限，我们先用 `oldCapacity / 2` 算出那 0.5 倍的增量 `increment`，再准备加到 `oldCapacity` 上。对于除以 2 的运算，当旧容量 `oldCapacity` 为 `0` 或 `1` 时，除以 2 的结果依然是 `0`，因此我们为这种情况指定了常量增量 `4`。但指定常量 `4` 的行为在一个极端假设下会埋下隐患：万一 `maxCapacity` 本身极小（甚至小于 `4`），`increment` 就有可能超过 `maxCapacity`。
   这直接决定了下一步如何判断 `oldCapacity + increment` 是否超出上限。如果超出上限，我们就直接选取 `maxCapacity`；如果没有超出，才把两者相加。判断有没有超出有两种移项写法：一种是用 `maxCapacity - increment` 看看剩下的空间够不够放 `oldCapacity`；另一种是用 `maxCapacity - oldCapacity` 看看剩下的空间够不够放 `increment`。这里必须选择后者。因为表示大小和容量的 `size_type` 是无符号整型，而前面提到 `increment` 在极端情况下可能大于 `maxCapacity`，一旦在无符号类型下用小数减去大数，结果就会发生回绕，使大小比较失去可靠性；相反，当前的 `oldCapacity` 一定没有超过 `maxCapacity`，所以 `maxCapacity - oldCapacity` 始终是安全的。

2. **原始空间申请与对象构造分离**
   代码中的 `pointer ptr = allocator_traits_type::allocate(_alloc, newCapacity);` 通过适配器的静态方法调用底层空间配置器 `_alloc`，申请一份能够容纳 `newCapacity` 个元素的原始内存空间。注意，这一步只申请空间，并不会在这片空间上构造对象（可以类比为 C++ 内存管理中的 `operator new`）。随后的循环才通过 `allocator_traits_type::construct` 在新空间上逐个构造有效元素。

3. **`try-catch` 异常捕获与状态回退**
   接下来我们需要让新空间中的对象所存储的数据信息与旧空间对应位置的对象保持等价。由于对象的构造函数是可能抛出异常的，设想旧空间中有 5 个有效元素，在向新空间构造的过程中，前 2 个处理成功，第 3 个在构造时抛出了异常——如果此时不做处理，不仅新申请的空间会丢失，容器也会卡在一个半途而废的中间状态。
   为了能够在异常发生时进行状态回退，我们必须**在新元素全部构造完成之后，再去析构旧空间里的对象**。同时，用 `try-catch` 结构包裹新对象的构造过程：一旦 `try` 块中的某个构造函数抛出异常，执行流就会直接跳转到 `catch` 块中，把新空间里前 `[0, idx)` 个已经构造成功的对象逐一调用 `destroy` 析构，再调用 `deallocate` 释放新空间，最后通过 `throw` 将异常继续向上层传递，交由调用方分析处理。由于旧空间的对象此前并未被触碰，回退之后容器依然保持原有的状态。

4. **效率与安全的权衡：`std::move_if_noexcept`**
   要让新空间中的对象与旧空间对象实现数据信息等价，常见的方式有三种：复制、移动或共享。我们可以举一个日常的例子：假设现在需要提交一份承载特定信息的文档（如调研报告或电子作业），恰好手头有一份满足要求的参考文档。一种方式是提取其中的有效信息，重新誊写一份到新文档里（容器中的复制往往是按原格式完整照抄一份新的数据载体），这对应**复制（拷贝构造）**；另一种更省事的方式是直接把原参考文档上的署名改成自己的，宣布该文档数据载体的所有权归自己所有，这对应**移动（移动构造）**；而**共享**则是多个对象共同使用同一份底层数据（如前文提到过的部分早期 `string` 实现中的引用计数方案）。
   在通用容器实现中，主要依赖复制和移动。移动操作因为直接移交数据载体的所有权，省去了重新分配和拷贝数据的开销，效率通常更高。但移动必须建立在一个前提之上：原对象已经不再需要这份数据载体了（例如原对象的生命周期即将结束）。编译器把这类可以安全移交所有权的对象统称为**右值**；当编译器无法仅从语法位置直接断定某个具名对象不再被需要时，就需要程序员通过 `std::move` 显式向编译器声明“它可以被视作右值，请去匹配具有移动语义的函数接口”。
   在 `reserve` 中，正常流程下旧空间里的元素马上就会被全部析构，按理说它们不再需要原有的数据载体了。但为什么这里没有直接使用 `std::move`，而是使用了 `std::move_if_noexcept` 呢？这是因为移动构造本身也有可能抛出异常。如果使用拷贝构造，旧对象内部的数据载体并没有被移走，中途抛出异常时只需清理新空间即可；但如果使用移动构造，前几个旧对象的数据载体所有权已经被移交给了新对象，一旦中途抛出异常，若想回退到原状态，还得想办法把已经移交出去的数据再反向移动回旧对象中，这不仅会显著增加 `catch` 块的回退复杂度，而且反向移动本身仍可能再次抛出异常。
   因此，这里使用了有条件的 `std::move_if_noexcept`：如果元素类型的移动构造函数承诺不抛异常（标记了 `noexcept`），就将其转为右值匹配移动构造；如果移动构造可能抛出异常且该类型支持拷贝构造，则不转为右值，退回匹配拷贝构造，从而保留旧对象中的数据，让回退逻辑简单可靠（如果某个类型只支持移动构造而不支持拷贝构造，那么即使未保证不抛异常，也只能尝试使用移动构造）。这样，我们在容器力所能及的范围内，尽可能兼顾了执行效率与异常安全。

### 插入与删除（`insert` / `erase`）：重叠区间推导、异常回退与迭代器失效

把插入和删除接口写好之后，诸如尾插、拷贝构造等其他写操作接口都可以通过复用它们来完成。我们先来看在指定位置插入多个相同元素的 `insert` 实现，再结合历史代码讨论迭代器失效的问题。

#### 指定位置填充多个元素的 `insert` 实现与重叠区间分析

在编写 `insert(const_iterator pos, size_type count, const_reference value)` 时，我们需要按步骤解决以下几个问题：

1. **参数合法性检查与偏移量记录**
   首先，传入的迭代器 `pos` 可能不在合法区间内。合法的插入区间是 `[_start, _finish]`（对应偏移量 `[0, oldSize]`，当偏移量为 `oldSize` 时即相当于尾插），如果越界则抛出 `std::out_of_range`。同时，为了容纳新元素，后续可能会调用 `reserve` 扩容；一旦扩容，底层空间位置发生变动，原有的迭代器 `pos` 就会失效。因此在扩容之前，我们需要先用偏移量 `insert_offset = pos - _start` 记录插入的逻辑位置，以便扩容后重新定位。
   如果插入个数 `count` 为 `0`，则直接返回；注意形参 `pos` 是常迭代器 `const_iterator`，而返回值类型是普通迭代器 `iterator`，这里需要使用 `const_cast` 去除 `const` 属性后返回。随后，像在 `reserve` 中一样，检查 `count` 是否会导致总元素个数超过 `max_size`。

2. **填充元素的可靠性保证（防止自引用）**
   我们需要防范这样一种情况：传入的 `value` 恰好就是当前 `vector` 容器中已经存储的某个元素（例如调用 `v.insert(v.begin(), 3, v[0])`）。因为 `value` 采用的是常引用形式，一旦后续触发扩容释放旧空间，或者在挪动元素时覆盖了原位置，`value` 引用就会失效或被修改。因此，这里采用一个简单直接的办法：在扩容和挪动之前，先通过拷贝构造生成一份独立的局部副本 `value_type fill_value = value;`（这也要求 `value_type` 必须支持拷贝构造，我们在函数开头的 `static_assert` 中对此做了编译期检查）。

3. **空间关系划分与重叠区间（`Overlap`）推导**
   调用 `reserve(oldSize + count)` 确保容量充足后，我们先理清当前底层动态数组的空间关系：以 `_start` 为基地址，`[0, oldSize)` 区间内放着原有的有效对象。我们需要将插入位置之后的后半部分元素向后挪动，为新元素腾出空间，然后再把填充元素写进去。
   在理想情况下，填充完成后的空间状态仍然以 `_start` 为基地址，划分为三部分：
   - `[0, insert_offset)`：原有的前半部分元素，保持不变；
   - `[insert_offset, insert_offset + count)`：新插入的 `count` 个元素；
   - `[insert_offset + count, oldSize + count)`：从原位置向后平移过来的后半部分元素。

   由此我们定义三个指针：`insert_pos`（插入起点）、`move_src`（需要挪动的原后半部分起点，等于 `insert_pos`）以及 `move_dst`（平移后的目标区间起点，等于 `insert_pos + count`）。由于原前半部分有 `insert_offset` 个元素，原有总数为 `oldSize`，因此需要向后挪动的元素个数为 `move_count = oldSize - insert_offset`。
   为什么要特别关注 `move_count`（需要挪动的元素个数）与 `count`（新插入的元素个数）呢？因为通过对比这两个数目，可以判断在平移原后半部分元素时，**源区间与目标区间是否存在空间重叠**：当 `move_count > count` 时，源区间的后缀与目标区间的前缀是重叠的，具体的重叠元素个数就是 `overlap_count = move_count - count`。

   ![](https://img.mdwind.online/img/20261114223025449.png)

   ![](https://img.mdwind.online/img/20261114223042557.png)

   如上面两张示意图所示，关注是否重叠的第一个原因在于确定**挪动方向**：对于源区间后缀与目标区间前缀重叠的情况，我们在挪动时不能从前往后写，否则会提前把后面尚未挪动的源数据给覆写掉。因此，我们应当采取**从后往前**的挪动方法（这一方向对于不重叠的情况同样适用）。
   这里还有一个类型细节：表示移动个数的 `move_count` 和下标变量 `idx` 使用的都是有符号的 `difference_type`，而非无符号的 `size_type`。这是有意为之的——因为后续从后往前挪动时，`idx` 会被初始化为 `move_count - 1`（当容器为空或在末尾插入时，`move_count` 为 `0`，`idx` 初值即为 `-1`），并且循环需要在迭代完 `0` 位置后再递减到 `-1` 停下，因此必须使用支持负数的有符号类型，防止无符号下溢。

4. **尾后默认占位构造（解耦生命周期与数据迁移）**
   在正式挪动元素之前，我们先在原有效区间末尾 `[_finish, _finish + count)` 上构造了 `count` 个默认对象：

   ```cpp
   allocator_traits_type::construct(_alloc, _finish + idx);
   ```

   不传入第三个参数时，该调用会在 `_finish + idx` 指向的未初始化空间上执行无参默认构造，使其成为一个生命周期已开启的有效对象。这样做的目的是**将元素对象的生命周期管理与之后的数据等效化处理（赋值）相解耦**——如果把容器中的对象比作水杯，里面存储的有效数据比作水，那么在把水倒进后面的新位置之前，我们先在那里摆好 `count` 个空水杯。这样一来，`[0, oldSize + count)` 整片区间内就全都是已经构造好的对象了，后续无论是平移后半部分元素还是填入新元素，都统一使用赋值操作即可，不会与对象的构造/析构混杂在一起。当然，如果构造空对象的过程抛出异常，我们需要把已经构造出来的那部分对象逆序析构掉，再继续向上抛出异常。

5. **数据挪动与重叠区间的异常恢复推导**
   进入数据挪动阶段后，如果条件允许，我们也希望优先使用基于移动语义的赋值。由于标准库中的 `std::move_if_noexcept` 只针对移动构造函数进行检查，无法检查移动赋值运算符是否保证不抛异常，这里我们借助 C++17 的编译期条件分支 `if constexpr (std::is_nothrow_move_assignable_v<value_type>)` 手动实现判断：如果类型保证移动赋值不抛异常，就为源元素加上 `std::move` 匹配移动赋值；否则使用常规的拷贝赋值。

   接下来是挪动中途抛出异常时的安全回退逻辑。由于移动赋值只有在保证不抛异常时才会被选用（且我们在函数开头已通过 `static_assert` 要求类型必须支持拷贝赋值），正常情况下只有走拷贝赋值分支时才可能抛出异常。

   ![](https://img.mdwind.online/img/20261115010703268.png)

   这就引出了我们关注区间重叠的第二个重要原因：一旦源区间与目标区间存在重叠，在向目标位置进行拷贝赋值时，就有可能把原来后半部分的某些源元素给覆写掉。如果此时中途抛出了异常，即使停止挪动，原来的源数据也未必是完整的，需要考虑把被覆写的部分恢复回来。
   但是，仔细推导就会发现，**即使存在重叠，也不意味着只要发生异常就必须把整个后半部分重新写回一遍**。
   前面我们已经确定，挪动操作是从后往前进行的。假设一共需要挪动 `move_count` 个元素，向右挪动的距离为 `count`，真正发生重叠的元素数量为：

   ```cpp
   overlap_count = move_count - count;
   ```

   （这里先考虑 `move_count > count` 即确实存在重叠的情况。）
   由于我们从后往前挪动，最开始处理的其实是源区间最后面的 `count` 个元素。而这些元素的目标位置已经落在了原源区间之外的尾部占位区里，因此在这一阶段，即使拷贝赋值抛出异常，也不会因为目标位置的写入而破坏原先的源数据。
   那么，什么时候才会真正开始覆写原数据呢？源区间最后一个元素的下标是 `move_count - 1`，而最开始可能发生覆写的位置，恰好对应源区间前面 `overlap_count` 个元素中的最后一个。所以：
   - 当 `idx >= overlap_count` 时，目标位置还没有进入原源区间；
   - 只有当 `idx < overlap_count` 时，才意味着我们已经进入了可能覆写原数据的阶段。

   我们还可以继续往下推导：既然知道发生异常时的下标 `idx`，能不能进一步确定究竟是哪些元素可能被覆写了？
   当然可以。因为目标地址是在源地址的基础上向后偏移了 `count` 个元素（`move_dst = move_src + count`），所以对于下标为 `idx` 的源元素，它写入的目标位置就是：

   ```cpp
   move_dst[idx] == move_src[idx + count]
   ```

   假设在当前下标 `idx` 处的这次赋值抛出了异常。由于我们是从后往前执行的，下标大于 `idx` 的迁移操作都已经完成（它们的副本已经保存在 `move_dst` 对应位置中），而下标小于 `idx` 的迁移操作还没有开始。至于为什么要把当前失败的这一次赋值位置 `idx + count` 也考虑进去，是因为拷贝赋值并不保证在抛出异常之前完全没有修改目标对象——即使赋值最终失败，它也可能已经改变了目标位置的数据。
   这意味着，**可能已经被覆写的源数据，一定集中在原源区间的后缀部分，其恢复区间（相对于 `move_src` 的下标）可以精确确定为 `[idx + count, move_count)`**。

   ![](https://img.mdwind.online/img/20261115011103461.png)

   恢复时，我们从前往后遍历该区间，把之前已经搬到目标区间 `move_dst` 中的副本重新写回 `move_src` 原来的位置：

   ```cpp
   if (idx < overlap_count) {
       for (difference_type i = idx + count; i < move_count; ++i) {
           if constexpr (std::is_nothrow_move_assignable_v<value_type>) {
               move_src[i] = std::move(move_dst[i]);
           } else {
               move_src[i] = move_dst[i];
           }
       }
   }
   ```

   为什么恢复时可以从前往后遍历呢？因为 `move_dst` 始终位于 `move_src` 的右侧，现在我们是把数据从右向左写回去，只要从前往后进行，就不会提前覆写后面仍然需要读取的副本——这与之前向右挪动时必须从后往前进行恰好是相反的。
   恢复完原数据后，再把之前从 `_finish` 开始额外构造的那 `count` 个占位对象析构掉即可。

6. **新值填充与收尾**
   如果数据挪动顺利完成，下一步就进入新值填充逻辑：使用拷贝赋值将 `fill_value` 依次填入 `[insert_pos, insert_pos + count)`。如果在填充过程中抛出异常，考虑到填充区域已经修改了前半部分位置，我们直接将 `[0, move_count)` 的全部元素从 `move_dst` 搬回 `move_src`，并析构尾部的 `count` 个额外对象。若一切顺利，最后更新 `_finish += count` 并返回 `insert_pos` 即可。

完整实现代码如下：

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

        // 如果数目为 0，直接退出；另外为了和返回值契合，去除 const
        if (count == 0) return const_cast<iterator>(pos);

        // 取出允许的最大容量上限，检查是否存在溢出的可能
        const size_type maxSize = allocator_traits_type::max_size(_alloc);
        if (count > maxSize - oldSize)
            throw std::length_error("wind::vector::insert(iterator, size_type, const_reference)");

        // 拷贝填充元素，避免出现自依赖问题（此处要求存在拷贝构造）
        value_type fill_value = value;

        // 要求拥有足够的容量
        reserve(oldSize + count);

        // 理想填充之后的情况：
        // [0, insert_offset) 不变
        // [insert_offset, insert_offset + count) 新填充区间
        // [insert_offset + count, oldSize + count) 新移动出的区间

        pointer insert_pos = _start + insert_offset;  // 填充区间起点
        pointer move_src = insert_pos;                // 移动源区间起点
        pointer move_dst = insert_pos + count;        // 移动目标区间起点
        // 注意这里可以尾插，存在 0 的可能，之后 -1 可为负数
        difference_type move_count = oldSize - insert_offset;  // 需要移动的元素个数
        const difference_type overlap_count =
            move_count > count ? move_count - count : 0;  // 重叠的个数

        // 使用有符号，防止下溢出
        difference_type idx = 0;

        // 确保理想填充的合法区间中都是有效对象
        try {
            for (; idx < count; ++idx) {
                // 不输入第三参数，转发后命中无参构造
                allocator_traits_type::construct(_alloc, _finish + idx);
            }
        } catch (...) {
            // 空构造失败进行状态回退，对已经构造的进行析构
            for (--idx; idx >= 0; --idx) {
                allocator_traits_type::destroy(_alloc, _finish + idx);
            }
            throw;
        }

        idx = move_count - 1;
        // 抛出异常进行回退
        try {
            // 由于可能是重叠空间，需要从后往前挪动，进行数据载体的等效化处理
            for (; idx >= 0; --idx) {
                if constexpr (std::is_nothrow_move_assignable_v<value_type>) {
                    move_dst[idx] = std::move(move_src[idx]);
                } else {
                    move_dst[idx] = move_src[idx];
                }
            }
        } catch (...) {
            // 回退：
            // 1) 源数据恢复（仅当拷贝赋值进入重叠区域时，恢复 [idx + count, move_count)）
            if (idx < overlap_count) {
                for (difference_type i = idx + count; i < move_count; ++i) {
                    if constexpr (std::is_nothrow_move_assignable_v<value_type>) {
                        move_src[i] = std::move(move_dst[i]);
                    } else {
                        move_src[i] = move_dst[i];
                    }
                }
            }

            // 2) 将额外构造的、原先准备被赋值的新元素析构
            for (idx = 0; idx < count; ++idx) {
                allocator_traits_type::destroy(_alloc, _finish + idx);
            }
            throw;
        }

        // 开始填充，抛出异常同样回退
        try {
            for (idx = 0; idx < count; ++idx) {
                insert_pos[idx] = fill_value;
            }
        } catch (...) {
            // 1. 让原来的元素恢复原先的数据状态
            for (idx = 0; idx < move_count; ++idx) {
                if constexpr (std::is_nothrow_move_assignable_v<value_type>) {
                    move_src[idx] = std::move(move_dst[idx]);
                } else {
                    move_src[idx] = move_dst[idx];
                }
            }

            // 2. 析构额外构造出的新元素
            for (idx = 0; idx < count; ++idx) {
                allocator_traits_type::destroy(_alloc, _finish + idx);
            }
            throw;
        }

        _finish += count;
        return insert_pos;
    }
```

#### 迭代器区间插入与 `erase` 删除实现

接下来看**插入迭代器区间**的接口。它的整体逻辑与填充相同元素的 `insert` 基本一致，但面临一个特殊问题：对于外部传入的任意迭代器区间 `[first, last)`，我们无法直接判断它是否存在自引用——因为传入的可能是其他包装类型的迭代器，但底层依然指向当前容器自身的元素。为了稳妥解决自引用问题，我们的方案是先找一个中转容器把迭代器区间中的内容拷贝出来。注意，这里不能选择 `wind::vector` 自己作为中转容器，因为后续的迭代器区间构造函数底层正是复用了这个区间插入接口；我们选择双向链表 `std::list` 来完成中转（后续我们也会自己实现 `list`），其余挪动与回退逻辑与上面相同：

![](https://img.mdwind.online/img/20261115165555259.png)

![](https://img.mdwind.online/img/20261115165613803.png)

单元素插入的逻辑同样类似，此处不再重复列出。

接着看**迭代器区间的删除** `erase(const_iterator first, const_iterator last)`。它的核心思路是将待删除区间后面的 `[last, _finish)` 元素整体向前（向左）挪动 `erase_count = last - first` 个位置，覆盖到以 `first` 为起点的位置上，最后析构尾部多余的 `erase_count` 个对象。由于这次是向左平移，重叠模型与 `insert` 相反：正向挪动时从前往后遍历，而异常回退恢复时则从 `idx - erase_count` 开始倒序向 `0` 恢复，因此判断条件 `if` 与恢复循环 `for` 可以自然地合并为一个 `for` 循环：

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

指定单个位置的删除 `erase(const_iterator pos)` 直接复用区间删除即可（下图下方的两个 `emplace` 接口与原地构造有关，这里先略过）：

![](https://img.mdwind.online/img/20261115171621282.png)

#### 迭代器失效问题剖析（内部失效与外部失效）

在上面的实现中，我们在 `insert` 扩容前特意先计算了偏移量 `insert_offset = pos - _start`，并在 `erase` 中返回了指向被删除位置（即后续替补上来元素）的迭代器。为什么要这样做？这涉及到 `vector` 实现与使用中的第二个常见问题——**迭代器失效**。

1. **`insert` 扩容引发的内部与外部迭代器失效**
   在初学编写单元素 `insert` 时，如果忽略了扩容对指针的影响，很容易写出下面这种未更新 `pos` 的代码：

   ```cpp
   // 错误示范：扩容后未修正 pos 导致内部迭代器失效
   iterator insert(iterator pos, const T& val) {
       assert(pos >= _start && pos <= _finish);
       if (empty()) {
           push_back(val);
           return pos;
       } else {
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
   }
   ```

   如果用上面这段 `insert` 去运行前面的测试函数 `realization3()`，程序会直接崩溃：

   ![image-20241025163333567](https://img.mdwind.online/md/202410251633611.png)

   通过调试观察指针地址的变化，就能定位到原因：

   ![image-20241025163926799](https://img.mdwind.online/md/202410251639146.png)

   ![image-20241025163946217](https://img.mdwind.online/md/202410251639258.png)

   ![image-20241025164037994](https://img.mdwind.online/md/202410251640354.png)

   ![image-20241025164052910](https://img.mdwind.online/md/202410251640951.png)

   `pos` 是以原来的旧内存块为参考的；现在触发了 `reserve` 异地扩容，`_start` 和 `_finish` 都已经指向新内存块，而 `pos` 没有被修正，依然指向已被释放的旧内存块，处于非法位置，后续挪动数据时自然会发生越界。这就是**迭代器内部失效**。修正方法就是在扩容前记录相对偏移量 `size_t n = pos - _start;`，扩容后再执行 `pos = _start + n;` 重新定位。

   既然函数内部的形参 `pos` 都会失效，调用方传入的外部实参迭代器当然也会失效。那么，能不能把形参改成引用 `iterator& pos` 来直接帮外部修正实参呢？回答是不行。因为迭代器常常是由 `begin()`、`end()` 等函数按值返回的临时对象，返回值具有常属性（右值），不能作为非 `const` 引用参数传递；而如果改成常引用 `const iterator&`，`insert` 内部又无法修改它了：

   ![image-20241025165532021](https://img.mdwind.online/md/202410251655087.png)

   那么外部迭代器如果需要继续使用，该如何更新呢？答案是接收 `insert` 的返回值——C++ 标准规定，`insert` 会返回指向新插入元素的迭代器，调用方可以通过返回值来更新外部迭代器。

2. **`erase` 引发的外部迭代器失效**
   `erase` 不会扩容，因此没有因空间重分配导致的内部失效风险，但同样存在**外部迭代器失效**的问题。由于删除元素是通过将后续元素整体前移覆盖来实现的，删除之后原迭代器指向的位置已经变成了原本排在后面的下一个元素。
   我们来看一个典型场景：遍历并删除 `vector` 中的所有偶数元素。如果调用 `v.erase(it)` 后不接收返回值，而是继续在循环末尾执行 `++it`，会出现什么结果？

   先看序列 `0, 1, 2, 2, 3, 3`（带有连续偶数）：

   ```cpp
   void realization4() {
       wind::vector<int> v;
       v.push_back(0);
       v.push_back(1);
       v.push_back(2);
       v.push_back(2);
       v.push_back(3);
       v.push_back(3);
       wind::vector<int>::iterator it = v.begin();
       // 目标：删除所有偶数元素
       while (it != v.end()) {
           if (*it % 2 == 0) {
               v.erase(it);
           }
           ++it;
       }
       for (auto val : v) {
           std::cout << val << " ";
       }
       std::cout << std::endl;
       // 输出结果：1 2 3 3
       // it -> 0 : 删除后后续元素前移，it 指向的内容变为 1，外部循环再 ++it，it 指向第一个 2
       // it -> 2 : 删除第一个 2 后，第二个 2 前移到当前 it 位置，外部循环再 ++it，直接跳过了第二个 2，指向 3
   }
   ```

   ![image-20241025170447171](https://img.mdwind.online/md/202410251704233.png)

   再看序列 `1, 1, 1, 2`（偶数位于末尾）：

   ```cpp
   void realization5() {
       wind::vector<int> v;
       v.push_back(1);
       v.push_back(1);
       v.push_back(1);
       v.push_back(2);
       wind::vector<int>::iterator it = v.begin();
       while (it != v.end()) {
           if (*it % 2 == 0) {
               v.erase(it);
           }
           ++it;
       }
       // 结果：触发越界警告或崩溃
       // 最后一个元素 2 被删除后，_finish 前移，此时 it 已经等于 _finish (即 end())；
       // 随后外部循环再执行一次 ++it，导致 it 越过 end() 指向非法区域，循环无法终止
   }
   ```

   ![image-20241025171116534](https://img.mdwind.online/md/202410251711592.png)

   如果把上述代码中的容器换成标准库的 `std::vector<int>`：在 Visual Studio（MSVC）下，由于标准库对迭代器做了强制调试检查，只要发现经过 `erase` 的迭代器未被重新赋值就直接执行 `++` 操作，就会直接报错拦截：

   ![image-20241025171556326](https://img.mdwind.online/md/202410251715391.png)

   而在 `g++` 下，由于其底层实现也是原生指针包装，表现出的行为就与我们的实现完全一致（序列 4 漏删，序列 5 越界段错误）：

   ```shell
   [wind@starry-sky IteratorFailure-vector]$ ls
   main.cpp  out-4  out-5  out-6
   [wind@starry-sky IteratorFailure-vector]$ ./out-4
   1 2 3 3 
   [wind@starry-sky IteratorFailure-vector]$ ./out-5
   Segmentation fault
   [wind@starry-sky IteratorFailure-vector]$ ./out-6
   1 3 
   ```

   因此，正确的做法是利用 `erase` 的返回值来更新外部迭代器：当执行删除时，直接由 `it = v.erase(it)` 接管下一个待检查元素的位置；只有当不执行删除时，才手动执行 `++it`：

   ```cpp
   // 解决方案：删除之后用返回值对迭代器进行修正
   void realization6() {
       wind::vector<int> v;
       v.push_back(0);
       v.push_back(1);
       v.push_back(2);
       v.push_back(3);
       v.push_back(4);
       v.push_back(4);
       wind::vector<int>::iterator it = v.begin();
       while (it != v.end()) {
           if (*it % 2 == 0) {
               it = v.erase(it);
           } else {
               ++it;
           }
       }
       for (auto val : v) {
           std::cout << val << " ";
       }
       std::cout << std::endl;
   }
   ```

   ![image-20241025170938425](https://img.mdwind.online/md/202410251709490.png)

### 尾插（`push_back`）、大小调整（`resize`）与清空析构（`clear` / `~vector`）

有了前面的 `insert` 接口，`push_back` 写起来就非常简单，直接复用现成的左值和右值插入接口即可：

![](https://img.mdwind.online/img/20261115172658490.png)

接下来我们看 `resize`。在初学阶段，我曾写过如下的 `resize` 版本：

```cpp
// 历史写法（作为错误示范）：缩容时仅移动指针，未析构对象
void resize(size_t n, const T& val = T()) {
    if (size() < n) {
        reserve(n);
        while (size() != n) {
            push_back(val);
        }
    } else {
        _finish = _start + n; // 不妥：直接把指针往前移动，没有调用被裁掉对象的析构函数
    }
}
```

现在尤其是用上空间配置器与适配器之后，**对象的生命周期**与**底层存储空间**分得很清楚：当参数 `n < size()` 需要缩容时，直接把 `_finish` 指针往前移动是不对的，因为 `[n, size())` 区间内的有效对象并没有被析构，若它们内部管理着动态资源就会造成泄漏。

另外，观察现代标准库的 `resize` 可以看到，它提供了两个重载接口：

![](https://img.mdwind.online/img/20261115173217295.png)

C++98 曾通过缺省参数 `const T& val = T()` 把它们结合在一起，为什么 C++11 又拆成了两个独立的重载接口呢？这主要是从类型特征（`Type traits`）的角度考虑的：如果是 C++98 的缺省参数实现，哪怕不传第二个参数，也相当于提供了一个默认构造出的填充元素 `val`，随后追加元素时必然要以**拷贝填充元素**的方式把它们插入进去，这就强制要求元素类型 `T` 必须支持拷贝。而在 C++11 拆开之后，第一个单参数接口 `resize(size_type n)` 在追加默认元素时，底层直接调用无参构造 `allocator_traits_type::construct(_alloc, _finish + idx);`，并非通过拷贝形式插入，因此**不需要类型 `T` 具备拷贝相关的接口**；第二个双参数接口 `resize(size_type n, const_reference val)` 则明确用于需要拷贝填充特定值的场景。

为此，我们先编写两个私有辅助接口，一个负责在末尾默认追加指定数目的元素（`append_default`），另一个负责析构并弹出末尾指定数目的元素（`pop_back_n`）：
（注：写到这里也可以看出，前面 `insert` 中在末尾默认构造 `count` 个占位对象的逻辑，其实本来应该放在这里并由 `insert` 去复用，我们在实现下一个容器时再调整这一实现顺序。）

```cpp
    // 默认追加指定数目元素，_finish 会进行适应性调整
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

    // 析构并弹出末尾指定元素
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

有了这两个私有接口，两个 `resize` 重载以及 `clear` 就可以直接复用它们：

```cpp
    void resize(size_type n) {
        const size_type oldSize = size();
        if (n < oldSize) {
            pop_back_n(oldSize - n);
        } else if (n > oldSize) {
            append_default(n - oldSize);
        }
    }

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

    // 确保目前空间里已经没有有效对象
    void clear() noexcept {
        pop_back_n(size());
    }
```

至于析构函数 `~vector()`，在仅使用 `new[] / delete[]` 的基础版本中，直接 `delete[] _start` 即可；而在使用空间配置器的版本中，只需先调用 `clear()` 析构全部有效元素，再调用 `deallocate` 释放 `_start` 指向的存储空间（我们可以将其封装为 `release_storage()` 辅助函数供析构与异常清理复用）。

### 拷贝控制与构造重载（拷贝构造、`swap`、`operator=` 与区间构造冲突）

#### 拷贝构造

在早期直接管理原始指针的写法中，拷贝构造需要手动分配空间并通过定位 `new` 逐个调用 `T` 的拷贝构造：

```cpp
// 早期写法
vector(const vector& v)
    : _start(nullptr)
    , _finish(nullptr)
    , _endofstarage(nullptr) {
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

而在实现了区间插入之后，现代版本可以在初始化列表中通过适配器获取空间配置器，并在函数体中直接复用区间 `insert`，若抛出异常则调用 `clear()` 并将空间归还给空间配置器：

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

#### 交换（`swap`）与赋值重载（`operator=`）

对于成员 `swap` 函数来说，核心逻辑就是将维护数据的那三个指针进行交换：

```cpp
void swap(vector& v) {
    std::swap(_start, v._start);
    std::swap(_finish, v._finish);
    std::swap(_endofstorage, v._endofstorage);
}
```

如果加入了空间配置器及其适配器的传播特性（`propagate_on_container_swap` 与 `is_always_equal`），则额外包含配置器状态的判断与交换（初学者可以暂且略过配置器部分，只看末尾的三指针交换）：

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

对于赋值运算符重载 `operator=`，如果仅仅是为了模拟实现 `vector` 的基础核心逻辑，建议直接使用前文[《string》](https://blog.csdn.net/venti0411/article/details/170494383?spm=1011.2415.3001.5331)中介绍过的现代写法——利用传值参数触发拷贝构造，再调用 `swap` 交换：

```cpp
vector& operator=(vector v) {
    swap(v);
    return *this;
}
```

而在我的完整实验版本中，为了处理空间配置器在拷贝赋值与移动赋值时的传播语义（`propagate_on_container_copy_assignment` / `propagate_on_container_move_assignment`），代码引入了较多的分支判断，可读性相对较低，仅供对配置器传播机制感兴趣的读者参考，初学模拟实现时直接跳过即可：

![](https://img.mdwind.online/img/20261117011252919.png)

```cpp
    // 拷贝赋值（基本异常安全保证，含配置器传播逻辑）
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

    // 移动赋值（含配置器传播逻辑）
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

#### 迭代器区间构造与 `n` 个 `val` 构造的匹配冲突

最后我们来看迭代器区间构造与 `n` 个 `val` 构造。在早期未加模板约束的实现中，我们通常会这样写这两个构造函数：

```cpp
// 使用模板便于其它容器迭代器的初始化
template<class InputIterator>
vector(InputIterator begin, InputIterator end)
    : _start(nullptr)
    , _finish(nullptr)
    , _endofstarage(nullptr) {
    while (begin != end) {
        push_back(*begin);
        ++begin;
    }
}

vector(size_t n, const T& val)
    : _start(nullptr)
    , _finish(nullptr)
    , _endofstarage(nullptr) {
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

但这样写完之后，一旦执行下面这段测试代码就会出现编译错误：

```cpp
void realization9() {
    // 10 和 0 都被视为 int，这是完全相同的类型；
    // 迭代器区间构造参数为 (InputIterator, InputIterator)，可以直接将 InputIterator 推导为 int；
    // 而 n 个 val 构造的参数为 (size_t, const T&)，如果调用它，第一个参数需要从 int 提升转换为 size_t。
    // 编译器遵循谁更匹配就调用谁的原则，因此会优先匹配无需类型转换的迭代器区间构造。
    wind::vector<int> v(10, 0);

    for (auto e : v) {
        std::cout << e << " ";
    }
    std::cout << std::endl;
}
```

编译器输出的报错信息如下：

```shell
生成开始于 17:32...
1>------ 已启动生成: 项目: myVector, 配置: Debug x64 ------
1>main.cpp
1>E:\C language new project\routine\myVector\myVector\myVector.h(43,15): error C2100: 无法取消引用类型为“InputIterator”的操作数
1>E:\C language new project\routine\myVector\myVector\myVector.h(43,15): error C2100:         with
1>E:\C language new project\routine\myVector\myVector\myVector.h(43,15): error C2100:         [
1>E:\C language new project\routine\myVector\myVector\myVector.h(43,15): error C2100:             InputIterator=int
1>E:\C language new project\routine\myVector\myVector\myVector.h(43,15): error C2100:         ]
```

我们的本意是使用 10 个 `0` 去初始化 `vector`，但因为 `10` 和 `0` 都是 `int` 类型，匹配模板 `vector(InputIterator, InputIterator)` 时不需要任何类型转换，比需要将 `int` 转换为 `size_t` 的 `vector(size_t n, const T& val)` 更契合，于是编译器进入了迭代器区间构造，并在执行解引用 `*begin` 时发生语法错误。

在传统写法中，最简单的解决方案是为 `n` 个 `val` 构造多提供几个重载版本（例如补充 `vector(int n, const T& val)`），使其在传入 `int` 参数时直接精确匹配：

```cpp
vector(int n, const T& val)
    : _start(nullptr)
    , _finish(nullptr)
    , _endofstarage(nullptr) {
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

而在引入 C++20 概念约束（`Concepts`）的现代实现中，我们不再需要担心这个问题，也无需编写多个冗余的整型重载——只需在区间构造函数的模板参数上直接声明 `std::input_iterator` 约束，要求传入的参数必须满足输入迭代器的基本特征，整型参数在编译期重载匹配时就会被自动排除：

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

# End