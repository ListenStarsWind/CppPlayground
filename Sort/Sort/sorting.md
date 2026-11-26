# 排序（Sorting）

## 从数组函数到泛型算法（From Array Functions to Generic Algorithms）

在实现排序之前，先看一个更简单的问题：从一组整数中找出最大值。我们可以把第一个元素记作当前结果，再依次查看后面的元素，遇到更大的元素就更新当前结果。

如果把整数换成浮点数，这套步骤仍然适用；如果把数组换成链表，我们同样可以沿着链表逐个访问元素；再换成一组学生记录，按数学成绩和按英语成绩选出的最高分可能来自不同的学生，但查找的步骤依然相同。

先用 C 写一个接收数组指针和长度的函数。下面的几个版本都从第一个元素取得初始结果，因此要求传入的区间非空。

```c
#include <stddef.h>

int max_value(const int* arr, size_t n) {
    int result = arr[0];

    for (size_t i = 1; i < n; ++i) {
        if (result < arr[i]) {
            result = arr[i];
        }
    }

    return result;
}
```

假如现在要处理 `double` 数组，我们可以照着再写一个函数。逐个访问、比较、更新结果，这些步骤都一样，变化的只有元素类型。在 C++ 中，可以用函数模板把这个类型留作参数。

```cpp
#include <cstddef>

template <class T>
T max_value(const T* arr, std::size_t n) {
    T result = arr[0];

    for (std::size_t i = 1; i < n; ++i) {
        if (result < arr[i]) {
            result = arr[i];
        }
    }

    return result;
}
```

传入 `int` 数组时，编译器可以从参数推导出 `T` 是 `int`；传入 `double` 数组时，`T` 就是 `double`。这样，相同的处理步骤只需要写一遍，由编译器根据实际使用的类型实例化对应的函数。

接下来考虑链表。前两个版本都通过 `arr[i]` 访问元素，但查找最大值的过程中，我们每次只需要读出当前元素，再走到下一个位置。数组可以用指针完成这两步，链表则可以用它自己的迭代器完成。于是，函数可以接收区间的起点 `first` 和终点 `last`，通过 `*first` 读取元素，用 `++first` 前进。

```cpp
#include <iterator>

template <std::input_iterator It>
std::iter_value_t<It> max_value(It first, It last) {
    std::iter_value_t<It> result = *first;

    for (++first; first != last; ++first) {
        if (result < *first) {
            result = *first;
        }
    }

    return result;
}
```

这里使用 `std::iter_value_t<It>` 取得迭代器对应的元素类型，`result` 保存的是当前最大元素的值。这个例子使用同类型、可以相互比较的迭代器表示区间两端，数组指针和 `std::list` 的迭代器都可以按这种方式传入。

元素类型和访问方式已经交给了调用者，比较规则还写在函数里的 `<` 上。假设用这个函数查找学生成绩，今天想找数学最高分，明天想找英语最高分。两次查找的循环完全一样，变化的只是比较时关注的那一项。于是，我们把这一步也交给调用者，用 `comp(a, b)` 表示按当前规则 `a` 是否排在 `b` 前面。

```cpp
template <std::input_iterator It, class Compare>
std::iter_value_t<It> max_value(It first, It last, Compare comp) {
    std::iter_value_t<It> result = *first;

    for (++first; first != last; ++first) {
        if (comp(result, *first)) {
            result = *first;
        }
    }

    return result;
}
```

普通函数也可以作为比较器传入。这里再看一种 C++ 写法：给类重载函数调用运算符 `operator()`，这样它的对象就可以写成 `comp(a, b)`。这种对象通常叫作**仿函数（Functor）**。

```cpp
struct Student {
    int math;
    int english;
};

struct CompareBySubject {
    bool use_math;

    bool operator()(const Student& lhs, const Student& rhs) const {
        if (use_math) {
            return lhs.math < rhs.math;
        }

        return lhs.english < rhs.english;
    }
};

Student students[] = {{96, 82}, {88, 97}, {91, 89}};

const auto best_at_math =
    max_value(students, students + 3, CompareBySubject{true});

const auto best_at_english =
    max_value(students, students + 3, CompareBySubject{false});
```

这两次调用传入的是**同一种仿函数类型**，只是对象保存的状态不同。第一次找到数学得分为 96 的学生，第二次找到英语得分为 97 的学生。查找函数只负责在遍历中比较并更新结果，比较器负责决定这次按哪一科排序。

这和前面实现 `vector` 时的设计思路相通。`vector` 通过 `allocator_traits` 使用空间配置器，查找算法通过迭代器访问元素、通过比较器判断顺序。各部分通过约定好的操作协作，因此换一种访问方式或比较规则时，查找步骤可以原样复用。接下来实现排序时，也可以沿用这个分工：**算法决定何时比较、何时移动元素，比较器决定两个元素的先后顺序。**

## 冒泡排序（Bubble Sort）

### 核心思路（Core Idea）

在冒泡排序的每一轮中，可以用右边界 `end` 将整个序列划分为两部分：左侧是本轮仍需扫描的**待排序区**，右侧是后续轮次会跳过的**已归位区**。为了方便观察，下面用数组来演示。

![](https://img.mdwind.online/img/20261119021107902.gif)

从动图中可以看到，每轮冒泡排序都从待排序区的左端开始，依次比较相邻的两个元素。如果它们的先后顺序与排序规则相反，就交换它们，然后继续比较下一对。以升序为例，每次比较后，两个元素中较大的那个会留在右侧，并参与下一次比较。这样一路比下去，待排序区的最大元素就会留在本轮的最后一个位置。它已经归位，下一轮只需将右边界左移一格，就可以跳过它。

这里还可以做一个小优化：如果一整轮都没有发生交换，说明待排序区中的每对相邻元素都符合排序规则，整个待排序区已经有序，此时可以直接结束排序。

### 实现与语法细节（Implementation and Syntax Details）

![](https://img.mdwind.online/img/20261119023211775.png)

```cpp
#pragma once

#include <iterator>

#include "operations.hpp"

namespace wind {
template <std::bidirectional_iterator It, class Compare = greater<std::iter_value_t<It>>>
    requires std::indirectly_swappable<It, It>
void bubble_sort(It first, It last, Compare cmp = {}) {
    for (auto end = last; first != end; --end) {
        bool swapped = false;

        auto left = first;
        auto right = left;
        ++right;

        for (; right != end; ++left, ++right) {
            if (cmp(*left, *right)) {
                std::ranges::iter_swap(left, right);
                swapped = true;
            }
        }

        if (!swapped) {
            break;
        }
    }
}
}  // namespace wind
```

这段代码中有几个 C++20 泛型编程的细节需要注意：

1. **迭代器约束（Iterator Concepts）**：为了让迭代器既能沿序列向前推进，又能让已归位区的左边界 `end` 逐步退回，迭代器至少需要满足双向迭代器（Bidirectional Iterator）的要求，即同时支持 `++` 和 `--`（注意双向迭代器不一定支持 `it + 1` 或 `it - 1`）。

   从读取和遍历能力的角度划分，C++ 常见的四类迭代器在 C++20 中都引入了对应的概念：

   | 迭代器类型 | C++20 概念 | 核心能力 |
   | --- | --- | --- |
   | 输入迭代器 | `std::input_iterator<It>` | 读取元素、向前推进，允许单遍遍历 |
   | 前向迭代器 | `std::forward_iterator<It>` | 在输入迭代器基础上支持多遍遍历 |
   | 双向迭代器 | `std::bidirectional_iterator<It>` | 增加 `--it`、`it--` |
   | 随机访问迭代器 | `std::random_access_iterator<It>` | 增加 `it + n`、`it - n`、`it[n]` 等随机访问能力 |

   这里需要注意术语方向：沿着容器正常遍历顺序移动到下一个元素（`++it`）称为“向前推进”，移动到上一个元素（`--it`）称为“向后退回”。这与日常口语中把下标增大说成“向后遍历”的习惯刚好相反。此外，这四种迭代器呈递进包含关系，因此以 `std::bidirectional_iterator` 作为最低要求时，随机访问迭代器同样可以无缝匹配。

2. **间接可交换约束与代理引用（Indirectly Swappable & Proxy Reference）**：另一个约束是 `std::indirectly_swappable<It, It>`，它要求可以通过 `std::ranges::iter_swap` 交换两个迭代器所指向的逻辑元素。大多数情况下写 `std::swap(*left, *right)` 也能工作，但存在一类特殊场景称为**代理引用（Proxy Reference）**：迭代器解引用得到的并不是底层真正存储的数据引用，而是一个临时代理对象。典型例子是 `std::vector<bool>`——标准库对其做了位压缩特化，多个布尔值共享同一个字节，此时无法直接对解引用结果取左值引用进行 `std::swap`，但仍可以通过 `std::ranges::iter_swap` 完成交换。

3. **比较器缺省语义（Default Comparator）**：在本文的排序实现中，`cmp(a, b)` 返回 `true` 表示当前这对元素处于逆序、`a` 应当排在 `b` 后面（需要调整），因此默认比较器取 `greater<std::iter_value_t<It>>`。相比之下，C++ 标准库 `std::sort` 中的比较器采用相反的视角——判断 `a` 是否应当排在 `b` 前面，因此其默认比较器为 `std::less`。两者只是描述顺序的视角不同，默认排序效果完全一致，最终得到的都是**升序序列**。

### 测试验证（Testing）

为了验证逻辑正确性与边界行为，针对 `bubble_sort` 设计了以下测试用例：

| 测试 | 验证内容 |
| --- | --- |
| 默认升序 | `[1, 3, 2]` 排成 `[1, 2, 3]`。第一对无需交换，仍要继续处理后面的元素，防止提前退出逻辑误写进内层循环。 |
| 子区间降序 | 只对 `[90, 2, 1, 3, 80]` 的中间三项排序，结果为 `[90, 3, 2, 1, 80]`，两端元素保持原位。 |
| 双向迭代器与稳定性 | 对 `std::list` 中的记录按键排序，`2A, 1B, 2C, 1D` 应变成 `1B, 1D, 2A, 2C`，键相同的记录保持原有相对顺序。 |
| 整轮无交换时提前退出 | 五个已经升序的元素只调用比较器四次，正好扫完一轮即退出。 |
| 空区间与单元素 | 两种调用都不触发比较，单元素值保持原样。 |

运行 `ctest` 的验证结果如下：

```bash
[wind@ubuntu-asus build]$ ctest -R '^test_bubble_sort$' --output-on-failure
Test project /home/wind/CS-Rebuild/04-CPP-Language-Basics/sort/build
    Start 1: test_bubble_sort
1/1 Test #1: test_bubble_sort .................   Passed    0.11 sec

100% tests passed, 0 tests failed out of 1

Total Test time (real) =   0.16 sec
```

## 插入排序（Insertion Sort）

插入排序的核心思想是：将待排序的元素按相对大小关系，逐个插入到一个已经有序的结构中。由于单个元素天然有序，插入排序最开始将首元素视为有序区，随后将其余元素依次插入其中。插入排序主要分为**直接插入排序（Direct Insertion Sort）**和**希尔排序（Shell Sort）**两类。

### 直接插入排序（Direct Insertion Sort）

**插入排序演示（相邻交换版）**

以 `[2, 4, 1, 3]` 为例，观察 `start` 如何标记本轮起点，以及 `curr` 如何跟着待插入的元素向左移动。

<video controls preload="metadata" width="720" src="https://img.mdwind.online/img/20261119042621799.mp4"></video>

[打开图床视频](https://img.mdwind.online/img/20261119042621799.mp4)

https://github.com/user-attachments/assets/11d349e6-91a6-40e3-aa19-9d7a73b6b5aa

下面采用相邻交换的方式实现泛型版本：

```cpp
#pragma once

#include <iterator>

#include "operations.hpp"

namespace wind {
template <std::bidirectional_iterator It, class Compare = greater<std::iter_value_t<It>>>
    requires std::indirectly_swappable<It, It>
void insert_sort(It first, It last, Compare cmp = {}) {
    if (first == last) return;

    auto start = first;
    ++start;
    for (; start != last; ++start) {
        auto curr = start;
        while (curr != first) {
            auto prev = curr;
            --prev;

            if (cmp(*prev, *curr)) {
                std::ranges::iter_swap(prev, curr);
                curr = prev;
                continue;
            }
            break;
        }
    }
}
}  // namespace wind
```

在实现细节上有三点值得注意：

1. **相邻交换与移位覆写**：传统的数组写法通常先拷贝待插入元素，再将有序区中较大的元素依次后移覆写，最后填入空位；这里在泛型迭代器上直接通过相邻交换完成插入，既无需额外要求元素可拷贝，代码结构也更简洁。
2. **空区间保护**：`start` 指向待排序区的首元素。由于单个首元素天然有序，进入循环前执行了 `++start`。如果传入的是空区间（`first == last`），直接自增会越过 `last` 导致未定义行为或死循环，因此开头必须先判断 `if (first == last) return;`。
3. **迭代器定位方式**：双向迭代器不支持 `+ 1` 或 `- 1`，不能直接用算术偏移计算相邻位置。这里选择先令 `curr = start`，再由 `prev = curr; --prev;` 得到前驱位置。若反过来从 `start` 向前推 `curr`，容易让 `curr` 越界到 `last`。当顺序不对时交换两者并更新 `curr = prev`，若一路交换到 `curr == first`，元素已经到达区间起点，内层循环自然结束。

> [!NOTE]
> 时间复杂度（Time Complexity）用于描述一个算法的执行效率随输入规模增长而发生的变化。它关注的不是算法实际运行了多少秒，而是当处理的数据量不断增加时，算法所需执行的操作次数会如何增长。
>
> 通常使用大 O 表示法（Big O Notation）描述时间复杂度，例如：
>
> - $O(1)$：常数时间，执行次数不随数据量变化。
> - $O(n)$：线性时间，数据量增加多少倍，执行次数也相应增加。
> - $O(n^2)$：平方时间，执行次数随数据量的平方增长。
> - $O(\log n)$：对数时间，数据量增长时，执行次数增长得相对缓慢。
>
> 时间复杂度在不同语境下有不同的评判标准，通常默认指最坏情况下的增长趋势。它反映的是渐进趋势而非绝对运行时间；即使两个算法具有相同的时间复杂度，实际运行效率也可能存在差异。

对于直接插入排序：

- **最坏情况**：输入序列完全逆序时，每轮待插入元素都要与有序区中的所有元素比较并一路移动到 `first`，总操作次数构成等差数列，时间复杂度为 $O(n^2)$。
- **最好情况**：输入序列本身已经有序时，每个待插入元素只需与前驱比较一次即可 `break`，时间复杂度为 $O(n)$。

虽然冒泡排序与直接插入排序的最坏时间复杂度同为 $O(n^2)$，但直接插入排序在实际表现上通常优于冒泡排序，尤其在序列接近有序时，其比较和移动次数会显著减少。

### 希尔排序（Shell Sort）

无论是冒泡排序还是直接插入排序，元素每次移动都只能跨越一个相邻位置。如果一个极值落在序列的错误一端，它必须一步一步挪动过去。

为了减少这种长距离搬运，可以引入**预排序（Pre-sorting）**的思想：将序列中相隔固定步长 `gap` 的元素逻辑上划为同一组，对各组分别执行直接插入排序。经过较大步长的预排序后，序列会变得大体有序；随后逐步缩小 `gap`，当 `gap = 1` 时，再执行一趟完整的直接插入排序。由于此时序列已接近有序，最后一趟插入排序的开销会大幅降低。

#### 实现方式一：按下标依次插入（Interleaved Insertion）

先将初始步长固定为 `3` 来观察执行过程。

**希尔排序演示（按下标依次插入）**

当 `gap = 3` 时，把序列按每行三个元素排开，同一列的元素相隔三步。`start` 按原数组下标依次前进，每完成一次插入，当前列的有序前缀就向下延伸一格。绿色下沿逐格形成阶梯，等整行处理完毕，三列才重新对齐。步长缩到 `1` 后，整个序列进行一趟直接插入排序。

<video controls preload="metadata" width="720" src="https://img.mdwind.online/img/20261121154503702.mp4"></video>

[打开图床视频](https://img.mdwind.online/img/20261121154503702.mp4)

https://github.com/user-attachments/assets/12b65ba9-beb6-4e9d-8bce-2a08d7db398c

```cpp
template <std::bidirectional_iterator It, class Compare = greater<std::iter_value_t<It>>>
    requires std::indirectly_swappable<It, It>
void shell_sort1(It first, It last, Compare cmp = {}) {
    using difference_type = std::iter_difference_t<It>;

    for (difference_type gap = 3; gap > 0; gap /= 2) {
        auto start = first;
        std::ranges::advance(start, gap, last);
        for (; start != last; ++start) {
            auto curr = start;
            auto prev = curr;
            while (!std::ranges::advance(prev, -gap, first)) {
                if (cmp(*prev, *curr)) {
                    std::ranges::iter_swap(prev, curr);
                    curr = prev;
                    continue;
                }
                break;
            }
        }
    }
}
```

双向迭代器不支持 `+ n` 或 `- n`，这里借助 `std::ranges::advance(it, offset, bound)` 完成跨步移动：

- 第一个参数是待移动的迭代器，第二个参数是偏移量（类型为 `std::iter_difference_t<It>`，支持负数），第三个参数是边界哨兵。
- 迭代器到达边界时会自动停止，函数返回**尚未走完的剩余步数**。例如偏移量为 `-3` 却只走了两步就触达 `first`，则返回 `-1`；如果完整走完偏移量，则返回 `0`。因此 `!std::ranges::advance(prev, -gap, first)` 恰好表示成功回退了 `gap` 步。

从外向内看，三层循环的职责非常清晰：第一层负责缩小步长 `gap`，最终退化为直接插入排序；第二层从第二行起逐元素向后遍历；第三层则以当前列为视角，将元素插入该列已有的有序前缀中。

#### 实现方式二：逐列插入（Column-by-Column Insertion）

另一种更符合直觉的写法是先排完一整列，再处理下一列。

**希尔排序演示（逐列插入版）**

先看 `gap = 3` 时的分组。`start` 指向当前列的列首，`compare_begin` 每次向后跨 `gap` 步，选出下一个待插入元素。若比较后发生交换，`curr` 就跟着该元素沿本列向上移动。排完一列再处理下一列，最后用 `gap = 1` 做一轮普通插入排序。

<video controls preload="metadata" width="720" src="https://img.mdwind.online/img/20261121161537017.mp4"></video>

[打开图床视频](https://img.mdwind.online/img/20261121161537017.mp4)

https://github.com/user-attachments/assets/5a077d75-0016-4f8e-950f-68afd8134553

```cpp
template <std::bidirectional_iterator It, class Compare = greater<std::iter_value_t<It>>>
    requires std::indirectly_swappable<It, It>
void shell_sort2(It first, It last, Compare cmp = {}) {
    using difference_type = std::iter_difference_t<It>;

    for (difference_type gap = 3; gap > 0; gap /= 2) {
        auto start = first;
        auto finish = start;
        std::ranges::advance(finish, gap, last);
        if (finish == last) continue;
        for (; start != finish; ++start) {
            auto compare_begin = start;
            while (!std::ranges::advance(compare_begin, gap, last) && compare_begin != last) {
                auto curr = compare_begin;
                auto prev = curr;
                while (!std::ranges::advance(prev, -gap, start)) {
                    if (cmp(*prev, *curr)) {
                        std::ranges::iter_swap(prev, curr);
                        curr = prev;
                        continue;
                    }
                    break;
                }
            }
        }
    }
}
```

两种写法的比较与交换总量完全一致，但逐列插入版循环层级更深、边界判断更琐碎，工程中通常优先采用第一种交错推进的写法。

#### 动态步长与存储局部性（Dynamic Gap and Locality of Reference）

当待排序元素较多时，如果一开始就把 `gap` 固定为 `3`，预排序的跨度过小，仍需承担大量工作。要进一步提升效率，需要根据元素总数动态设定初始步长，并按阶梯逐步缩小。

这要求我们将迭代器约束提升为**随机访问迭代器（`std::random_access_iterator`）**。这么做并不仅仅是为了通过 `last - first` 在 $O(1)$ 时间内算出元素个数，更深层的原因在于**数据布局与缓存命中率（Cache Hit Rate）**：

- 计算机采用分层存储结构，距离 CPU 越近的存储介质（寄存器、L1/L2/L3 高速缓存 Cache）读写速度越快，而主存（内存）和外存（SSD、机械硬盘）依次变慢。
- 根据**局部性原理（Principle of Locality）**，程序倾向于重复访问近期使用过的数据（时间局部性），或访问与当前数据内存地址相邻的数据（空间局部性）。
- 随机访问迭代器通常对应连续内存结构（如数组、`std::vector`），支持高效的跨步访问并具有更好的缓存友好性；而在链表这类节点离散分布的容器上执行大跨步 `advance`，不仅每次定位本身是线性开销，还会频繁触发缓存未命中（Cache Miss）。

因此，评估算法性能不能只看渐进时间复杂度，还必须结合数据布局、访问模式与硬件缓存特性。

基于随机访问迭代器的动态步长实现如下：

```cpp
template <std::random_access_iterator It, class Compare = greater<std::iter_value_t<It>>>
    requires std::indirectly_swappable<It, It>
void shell_sort(It first, It last, Compare cmp = {}) {
    using difference_type = std::iter_difference_t<It>;

    difference_type size = last - first;
    for (difference_type gap = size / 2; gap > 0; gap /= 2) {
        auto start = first;
        std::ranges::advance(start, gap, last);
        for (; start != last; ++start) {
            auto curr = start;
            auto prev = curr;
            while (!std::ranges::advance(prev, -gap, first)) {
                if (cmp(*prev, *curr)) {
                    std::ranges::iter_swap(prev, curr);
                    curr = prev;
                    continue;
                }
                break;
            }
        }
    }
}
```

这里采用每次除以 `2` 的步长收缩方式：由于整数除法向下取整，无论元素个数是奇数还是偶数，最终都会收敛到 `gap = 1`，并在执行完最后一趟直接插入排序后以 `gap = 0` 结束循环。

#### 希尔排序的时间复杂度（Time Complexity of Shell Sort）

针对上述 `gap = n / 2` 且逐轮减半的步长序列，可以分析其两种极端情况：

- **最好情况**：当输入序列已经有序时，步长为 $g$ 的一轮循环从第 $g$ 个位置开始，共访问 $n - g$ 个位置。每个位置只需比较一次即可确认有序且无交换。由于 $g \le n / 2$，每轮都执行线性次数的比较，而步长每轮减半共有 $\lfloor \log_2 n \rfloor$ 轮，因此最好时间复杂度为 $\Theta(n \log n)$。
- **最坏情况**：步长为 $g$ 时共有 $g$ 组，每组约有 $n / g$ 个元素，每组执行插入排序的最坏开销为 $O((n / g)^2)$，整轮上界为 $O(g (n / g)^2) = O(n^2 / g)$。将各轮步长倒序累加，总上界约为 $n^2 + n^2 / 2 + n^2 / 4 + \cdots$，仍为 $O(n^2)$。

  这个平方级上界确实可以达到。以 `5, 1, 6, 2, 7, 3, 8, 4` 为例，`gap = 4` 和 `gap = 2` 时只会在同为奇数下标或同为偶数下标的元素之间比较，而这两组各自已经有序，导致预排序全程零交换；直到 `gap = 1` 才开始处理所有的逆序对，退化为普通插入排序。将这种排列推广到长度为 $2$ 的幂的序列，就会在最后一轮留下 $\Theta(n^2)$ 个逆序对。

希尔排序的真正价值在于：**较大的步长允许元素一次跨越多个位置，提前消除大量原本需要多次相邻交换才能消除的逆序**。例如序列 `5, 6, 7, 8, 1, 2, 3, 4`，直接插入排序需要 16 次相邻交换，而希尔排序在 `gap = 4` 时仅交换 4 次即全部有序。实际能够达到的渐进量级高度依赖于所选用的步长序列（如 Hibbard、Knuth 或 Sedgewick 序列）。

## 选择排序（Selection Sort）

### 双向选择排序（Bidirectional Selection Sort）

选择排序将序列分为已归位区和待排序区：每轮扫描待排序区，选出按目标顺序应排在最前面的元素放到左端，随后缩小待排序区。

这里直接实现一种常见的改进——**双向选择排序**：每轮扫描同时确定应该排在最前面和最后面的两个元素，分别归位到待排序区的两端，使待排序区从左右两侧同步向中间收缩。

**双向选择排序演示（边扫描边交换）**

以 `[6, 2, 8, 4, 9, 1, 3]` 为例。每轮先比较待排序区的两端，必要时交换，再让 `scan` 从左向右扫描。遇到应该排得更靠前或更靠后的元素，就当场交换到对应的一端。扫描结束后，两端归位，下一轮继续处理剩下的区间。

<video controls preload="metadata" width="720" src="https://img.mdwind.online/img/20261122100359579.mp4"></video>

[打开图床视频](https://img.mdwind.online/img/20261122100359579.mp4)

https://github.com/user-attachments/assets/f36fdd0f-a9b6-46c5-8eb9-675b00c2ca28

```cpp
#pragma once

#include <iterator>

#include "operations.hpp"

namespace wind {
template <std::bidirectional_iterator It, class Compare = greater<std::iter_value_t<It>>>
    requires std::indirectly_swappable<It, It>
void selection_sort(It first, It last, Compare cmp = {}) {
    while (first != last) {
        --last;

        if (first == last) break;

        if (cmp(*first, *last)) {
            std::ranges::iter_swap(first, last);
        }

        for (auto scan = std::next(first); scan != last; ++scan) {
            if (cmp(*first, *scan)) {
                std::ranges::iter_swap(first, scan);
            } else if (cmp(*scan, *last)) {
                std::ranges::iter_swap(scan, last);
            }
        }

        ++first;
    }
}
}  // namespace wind
```

实现中有三个边界与逻辑细节需要注意：

1. **左闭右开区间的安全性**：`first` 指向待排序区首元素，`last` 指向后半段已归位区的首元素（即待排序区尾后位置）。采用半开区间并在每轮中分步收缩（开头 `--last`，末尾 `++first`），可以彻底避免全闭区间两端同步移动时相互交错、错过 `first == last` 退出条件而引发死循环的问题。
2. **单元素区间退出**：执行 `--last` 后立刻判断 `if (first == last) break;`，用于排除待排序区仅剩一个元素的情况，此时无需再扫描。
3. **扫描前先校准两端基准**：循环开始前先执行 `if (cmp(*first, *last)) iter_swap(first, last);`，确保以升序为例时满足 `*first <= *last`。只有在这个前提下，内层扫描才能安全地使用 `if ... else if ...`：如果 `*scan` 比 `*first` 更小，换到左端后，原 `*first` 仍然小于等于 `*last`，无需再与 `*last` 比较；否则若初始两端本身逆序，就会出现基准失真，导致逻辑错误。

## 堆排序（Heap Sort）

堆排序依赖堆（Heap）这一数据结构来高效维护与提取极值。由于本系列目前尚未展开树与堆的相关内容，堆排序的实现与分析将安排在后续数据结构专题中一并讨论。

## 快速排序（Quick Sort）

快速排序采用**分治（Divide and Conquer）**思想：从待排序区间中选取一个元素作为**基准值（Pivot）**，通过一趟划分（Partition）操作将区间分为两部分，使左侧元素都不大于基准值、右侧元素都不小于基准值（以升序为例），随后对左右两个子区间递归重复上述过程。

划分是快速排序的核心，下面依次介绍三种经典划分方式。

### 划分方式一：交换法 / Hoare 划分（Partition by Swap）

**快速排序演示（以首元素为基准分区）**

以升序为例，观察 `last` 怎样先向左找小于基准的元素，`first` 又怎样向右找大于基准的元素。若两端还没相遇，就交换这两个放错边的元素。视频分别演示了两种相遇方式，并用 `[1, 2]` 说明为什么要让 `first` 从 `key` 开始。

<video controls preload="metadata" width="720" src="https://img.mdwind.online/img/20261122153622125.mp4"></video>

[打开图床视频](https://img.mdwind.online/img/20261122153622125.mp4)

https://github.com/user-attachments/assets/42bf57a0-6edb-4ccc-abc4-5092130a9818

#### 分区逻辑与相遇分析（Partition Logic and Meeting Cases）

以升序为例，选定首元素 `key = first` 作为基准后，使用两个迭代器从左闭右开区间 `[first, last)` 的两端向中间扫描：

- `last` 初始指向尾后位置，因此**先向左回退一步，再比较**，直到找到一个严格小于基准的元素。
- `first` 初始指向有效元素，因此**先比较，再向右推进**，直到找到一个严格大于基准的元素。
- 若两个迭代器尚未相遇，就交换它们所指的元素。

当 `first` 与 `last` 相遇时，存在两种情况：

1. **左侧追上右侧**：说明右侧已经停在一个严格小于基准的元素上，左侧随后走到这里。此时将基准与相遇位置交换，较小的元素回到区间开头，基准归位。
2. **右侧退到左侧**：这又分两种子情况：
   - 如果此前从未发生过交换，`first` 仍停在 `key`，右侧一路退回起点，基准原地归位。
   - 如果此前已经发生过交换，`first` 当前位置上的元素正是上一轮从右侧换过来的、严格小于基准的元素，因此同样可以与基准交换。以 `[3, 4, 2]` 为例：基准 `key` 为首元素 `3`，第一轮 `last` 停在 `2`、`first` 停在 `4`，两者交换后序列变为 `[3, 2, 4]`（此时 `first` 指向刚换过来的 `2`）；进入下一轮，`last` 向左回退一步直接撞上 `first`，相遇位置上的元素正是小于 `3` 的 `2`，最终将其与 `key` 交换得到 `[2, 3, 4]`，基准顺利归位。

#### 为什么一开始不跳过 `key`

直观上可能会想先执行 `++first`，把基准和扫描区间分开。但拿 `[1, 2]` 测试就会发现问题：`last` 会在 `2` 的位置撞上左侧边界并被迫停下，此时 `2` 依然大于基准 `1`，若按常规交换，原本有序的 `[1, 2]` 就会变成 `[2, 1]`。因此让 `first` 从 `key` 起步，为右侧保留一路退回基准位置的可能。

此外，`std::ranges::advance` **恰好走到边界时仍返回 `0`**。以单元素区间为例，`last` 第一次回退恰好到达 `key` 并与自身比较一次；再次尝试回退因无法移动返回 `-1`；随后 `first` 尝试前进同样返回 `1`。最终两者均停在 `key` 并直接返回。空区间则交由外层递归提前返回。

```cpp
#pragma once

#include <iterator>

#include "operations.hpp"

namespace wind {
template <std::bidirectional_iterator It, class Compare = greater<std::iter_value_t<It>>>
    requires std::indirectly_swappable<It, It>
It partition_by_swap(It first, It last, Compare cmp = {}) {
    auto key = first;

    while (first != last) {
        while (!std::ranges::advance(last, -1, first) && !cmp(*key, *last));
        while (!cmp(*first, *key) && !std::ranges::advance(first, 1, last));
        if (first != last) std::ranges::iter_swap(first, last);
    }
    if (key != last) std::ranges::iter_swap(key, last);
    return last;
}

template <std::bidirectional_iterator It, class Compare = greater<std::iter_value_t<It>>>
    requires std::indirectly_swappable<It, It>
void Hoare_sort(It first, It last, Compare cmp = {}) {
    if (first == last) return;

    auto key = partition_by_swap(first, last, cmp);
    Hoare_sort(first, key, cmp);
    Hoare_sort(std::next(key), last, cmp);
}
}  // namespace wind
```

注意内层循环的条件 `!cmp(*key, *last)` 与 `!cmp(*first, *key)`：在默认 `greater` 下，等价于 `*key <= *last` 和 `*first <= *key`，也就是说遇到与基准相等的元素时指针会继续移动，避免两端同时停在相等元素上反复交换而陷入死循环。

### 划分方式二：挖坑填坑法（Partition with Hole）

**快速排序演示（挖坑填坑法）**

以 `[5, 8, 2, 7, 3]` 为例，先取出首元素作为基准，再从两端交替填坑。每填一次，元素原来的位置就成了下一个坑。两端相遇时，把基准填回最后一个坑。

约 33 秒处换用 `std::unique_ptr<int>` 演示。`key` 接管首元素所指的整数后，原槽位变成 `nullptr`。这时先判断 `first == last`，就能在两端相遇时跳过比较，避免解引用空指针。

<video controls preload="metadata" width="720" src="https://img.mdwind.online/img/20261122225558556.mp4"></video>

[打开图床视频](https://img.mdwind.online/img/20261122225558556.mp4)

https://github.com/user-attachments/assets/f401b025-9321-4933-8b58-7d5f02750154

```cpp
template <std::bidirectional_iterator It, class Compare = greater<std::iter_value_t<It>>>
    requires std::indirectly_swappable<It, It>
It partition_with_hole(It first, It last, Compare cmp = {}) {
    using value_type = std::iter_value_t<It>;

    value_type key(std::ranges::iter_move(first));
    auto hole = first;

    while (first != last) {
        do {
            --last;
        } while (first != last && !cmp(key, *last));
        if (first != last) {
            *hole = std::ranges::iter_move(last);
            hole = last;
        }
        while (first != last && !cmp(*first, key)) ++first;
        if (first != last) {
            *hole = std::ranges::iter_move(first);
            hole = first;
        }
    }
    *last = std::move(key);
    return last;
}
```

填坑法用“移出基准 -> 交替覆盖空槽（坑） -> 最后填回基准”替代了成对交换。这里通过 `std::ranges::iter_move` 将迭代器指向的元素以右值形式移出，触发移动语义（Move Semantics）以避免不必要的深拷贝。

但移动语义也引入了一个容易忽略的陷阱：在间接存储场景中，容器保存的往往不是对象本体，而是智能指针（如 `std::unique_ptr<int>`），自定义比较器会先解引用迭代器拿到智能指针，再解引用智能指针比较其指向的值。`first` 的所有权被 `key` 接管后，`*first` 会被置为 `nullptr`。如果 `last` 一路回退直接与 `first` 相遇，此时必须保证 `first` 的循环**先判断 `first != last`，再执行 `cmp(*first, key)`**，利用逻辑与 `&&` 的短路特性跳过比较，从而避免对已移空的智能指针解引用。

### 划分方式三：同向双指针扫描法（Forward Scan Partition）

**同向双指针分区演示**

以 `[6, 1, 9, 7, 4, 6, 5]` 为例，观察 `scan` 如何把小于基准的元素“甩进”左区，以及扫描结束后 `key` 如何与 `boundary` 交换位置。

<video controls preload="metadata" width="720" src="https://img.mdwind.online/img/20261123001532929.mp4"></video>

[打开图床视频](https://img.mdwind.online/img/20261123001532929.mp4)

https://github.com/user-attachments/assets/66c8115c-6178-4a22-9da6-1d083c7f2c03

以升序为例，同向双指针在扫描过程中始终维护两个区间：

- `(key, boundary]` 存放严格小于基准的元素；
- `(boundary, scan)` 存放已经扫过、大于等于基准的元素。

每当 `scan` 发现一个严格小于基准的元素，就先将 `boundary` 向前推进一格，再把该元素交换到新扩出的位置（若 `boundary == scan`，说明元素已在目标位置，省去交换）。扫描结束后，只要小值区非空，`boundary` 就指向最后一个小值的位置，将其与 `key` 交换即可让基准归位；若没有找到任何小值，`boundary` 始终与 `key` 重合，基准留在原位。

```cpp
template <std::forward_iterator It, class Compare = greater<std::iter_value_t<It>>>
    requires std::indirectly_swappable<It, It>
It partition_with_forward_scan(It first, It last, Compare cmp = {}) {
    auto key = first;
    auto boundary = first;

    for (auto scan = std::next(first); scan != last; ++scan) {
        if (cmp(*key, *scan)) {
            ++boundary;
            if (boundary != scan) {
                std::ranges::iter_swap(boundary, scan);
            }
        }
    }

    if (key != boundary) {
        std::ranges::iter_swap(key, boundary);
    }
    return boundary;
}
```

由于两个扫描迭代器均只向前推进，该划分方式的迭代器要求降低到了**前向迭代器（`std::forward_iterator`）**，可直接用于 `std::forward_list` 等单向链表结构。

### 时间复杂度与三数取中优化（Time Complexity and Median-of-Three）

当每次选取的基准值都接近当前区间的中位数时，快速排序的递归调用结构接近一棵平衡二叉树：

![quicksort-time-complexity](https://img.mdwind.online/img/20261123003048181.png)

整棵递归树约有 $\log_2 n$ 层，每层所有子区间的扫描总量为 $O(n)$，因此理想与平均时间复杂度为 $O(n \log n)$。

而在最坏情况下，如果每次选中的基准值恰好都是当前区间的极值（例如对已经有序的序列直接取首元素作基准），递归调用树会退化为深度为 $n$ 的单链，每层仍需扫描线性数量的元素，时间复杂度退化为 $O(n^2)$。

为了降低取到极值的概率，常用的改进是**三数取中（Median-of-Three）**：在区间首元素、中间元素和尾元素三个候选中，选出大小居中的那个作为基准，并将其交换到区间首位，再交给原有的划分函数处理。

先实现取中辅助函数 `median_of_three`（从这里开始，比较器统一采用 `const Compare&` 常引用传参，避免不必要的拷贝）：

```cpp
template <std::input_iterator It, class Compare>
It median_of_three(It a, It b, It c, const Compare& cmp) {
    if (cmp(*a, *c)) {
        std::swap(a, c);
    }

    if (cmp(*a, *b)) {
        return a;
    }

    if (cmp(*b, *c)) {
        return c;
    }

    return b;
}
```

这里的推导过程很直观：`cmp(x, y)` 为真表示 `x` 应排在 `y` 后面。第一步先确保 `c` 排在 `a` 后面；随后如果 `a` 排在 `b` 后面，则顺序为 `b, a, c`，中位数是 `a`；否则 `b` 排在 `a` 后面，再比较 `b` 与 `c`：若 `b` 排在 `c` 后面则顺序为 `a, c, b`，返回 `c`，否则返回 `b`。

接着利用快慢指针在双向迭代器区间中定位中点并选出基准：

```cpp
template <std::bidirectional_iterator It, class Compare>
It choose_pivot(It first, It last, const Compare& cmp) {
    auto fast = first;
    auto mid = first;
    auto tail = std::prev(last);

    while (!std::ranges::advance(fast, 2, last)) ++mid;

    if (mid == tail) return first;

    return median_of_three(first, mid, tail, cmp);
}
```

对于元素个数不足 3 个的区间（例如长度为 2），快指针步进 2 到达 `last` 时 `mid` 会落在第二个元素上，恰好满足 `mid == tail`。此时无需三数取中，直接返回 `first` 即可。

将基准选择与划分策略参数化后，上层递归快速排序如下：

```cpp
template <std::bidirectional_iterator It, class Compare = greater<std::iter_value_t<It>>,
          class Partition = It (*)(It, It, const Compare&)>
    requires std::indirectly_swappable<It, It>
void Hoare_sort(It first, It last, const Compare& cmp = {},
                const Partition& partition = partition_by_swap<It, Compare>) {
    if (first == last || std::next(first) == last) return;

    auto pivot = choose_pivot(first, last, cmp);
    if (pivot != first) {
        std::ranges::iter_swap(first, pivot);
    }

    auto key = partition(first, last, cmp);
    Hoare_sort(first, key, cmp, partition);
    Hoare_sort(std::next(key), last, cmp, partition);
}
```

### 递归版快速排序的实测与局限（Benchmark and Limitations of Recursion）

实现三数取中后，在 `ubuntu-asus` 环境下使用 `Boost.Test` 对递归版快速排序进行测试：正确性测试覆盖 `std::vector` 和 `std::list`，性能与深度统计统一使用 `std::list<int>`，覆盖升序、逆序、乱序和全相等四类输入，测试用例全部通过。

下表为交换法的部分实测数据（比较次数包含三数取中的比较，最大划分深度仅统计真正执行划分的递归层，空区间和单元素区间直接返回）：

| 元素个数 | 输入 | 比较次数 | 划分次数 | 最大划分深度 |
| --- | --- | --- | --- | --- |
| 4096 | 升序 | 51,211 | 2,048 | 12 |
| 4096 | 乱序 | 66,620 | 2,336 | 20 |
| 4096 | 逆序 | 2,110,461 | 2,048 | 1,025 |
| 1024 | 全相等 | 528,888 | 1,023 | 1,023 |
| 2048 | 全相等 | 2,106,360 | 2,047 | 2,047 |
| 4096 | 全相等 | 8,407,032 | 4,095 | 4,095 |

从实测结果可以观察到两个关键现象：

1. **划分次数 vs. 递归深度**：4096 个元素的升序与逆序输入都执行了 2048 次划分，但最大深度分别为 12 和 1025。划分次数统计整棵递归树做了多少次划分，而递归深度取决于其中最长的一条调用链。三数取中能让逆序输入的第一轮划分接近均衡，但后续子区间重新取中后，划分依旧可能失衡。
2. **全相等输入的线性退化**：全相等序列中三个候选值完全一样，在现有的交换法、填坑法和同向扫描法下，每轮基准都会归位到当前区间首位，下一轮仅减少一个待排序元素。规模从 1024 翻倍到 2048 再到 4096 时，最大划分深度依次达到 1023、2047 和 4095，比较次数每次都接近翻四倍。

回到递归本身：每次划分完成后先递归左侧、再递归右侧，只要下层尚未返回，上层栈帧就必须一直驻留在调用栈中。

![quick-sort-recursion-depth](https://img.mdwind.online/img/20261123022556675.png)

划分均衡时，递归深度随输入规模呈对数增长；一旦退化为近似线性的调用链（如本次实测的 4095 层），随着数据规模继续增大，层层嵌套的函数调用就有可能耗尽线程栈空间，导致**栈溢出（Stack Overflow）**。

### 非递归实现（Iterative Quick Sort）

为了避免深层递归耗尽系统调用栈，可以改用分配在堆内存上的容器显式保存待排序的子区间 `[begin, end)`。由于快速排序各子区间相互独立，无论是借助 `std::stack` 按**深度优先（DFS）**处理，还是借助 `std::queue` 按**广度优先（BFS）**处理，都能得到正确的排序结果（通常 DFS 的辅助空间占用更小）。

注：若尚未学习 `std::stack` 与 `std::queue`，可以先跳过本节，待后续了解容器适配器后再回头阅读。代码中的 `emplace` 会直接在容器内部构造 `std::pair<It, It>`，此处暂不展开完美转发机制，可将其理解为更简洁的入栈/入队方式。

```cpp
template <std::bidirectional_iterator It, class Compare = greater<std::iter_value_t<It>>,
          class Partition = It (*)(It, It, const Compare&)>
    requires std::indirectly_swappable<It, It>
void quick_sort_dfs(It first, It last, const Compare& cmp = {},
                    const Partition& partition = partition_by_swap<It, Compare>) {
    using stack = std::stack<std::pair<It, It>>;
    stack s;
    s.emplace(first, last);

    while (!s.empty()) {
        auto [begin, end] = s.top();
        s.pop();

        if (begin == end || std::next(begin) == end) continue;

        auto pivot = choose_pivot(begin, end, cmp);
        if (pivot != begin) {
            std::ranges::iter_swap(begin, pivot);
        }

        auto key = partition(begin, end, cmp);
        s.emplace(std::next(key), end);
        s.emplace(begin, key);
    }
}

template <std::bidirectional_iterator It, class Compare = greater<std::iter_value_t<It>>,
          class Partition = It (*)(It, It, const Compare&)>
    requires std::indirectly_swappable<It, It>
void quick_sort_bfs(It first, It last, const Compare& cmp = {},
                    const Partition& partition = partition_by_swap<It, Compare>) {
    std::queue<std::pair<It, It>> pending;
    pending.emplace(first, last);

    while (!pending.empty()) {
        auto [begin, end] = pending.front();
        pending.pop();

        if (begin == end || std::next(begin) == end) continue;

        auto pivot = choose_pivot(begin, end, cmp);
        if (pivot != begin) {
            std::ranges::iter_swap(begin, pivot);
        }

        auto key = partition(begin, end, cmp);
        pending.emplace(begin, key);
        pending.emplace(std::next(key), end);
    }
}
```

### 三路划分（Three-Way Partition）

非递归写法解决了栈溢出问题，但并没有解决前面实测中暴露的另一个瓶颈：**大量重复元素导致的时间复杂度退化为 $O(n^2)$**。对此，可以采用**三路划分**。

**三路划分演示**

以 `[6, 2, 6, 9, 3, 6, 8, 4]` 为例，观察 `9` 被换到右侧后，`scan` 为什么要留在原地判断换回来的 `4`，以及最后如何让基准与另外两个 `6` 连成等价区间 `[3, 6)`。

<video controls preload="metadata" width="720" src="https://img.mdwind.online/img/20261123041047790.mp4"></video>

[打开图床视频](https://img.mdwind.online/img/20261123041047790.mp4)

https://github.com/user-attachments/assets/4e5ce78e-27ba-4e31-9dcb-318caee7d08c

三路划分的目标是将当前区间划分为三段：左侧严格小于基准，中间全部与基准等价，右侧严格大于基准。划分完成后，整个中间等价区间都已经归位，后续只需对左右两段继续排序。

实现时仍以首元素 `first` 作为基准并让其暂留原地，使用三个迭代器处理剩余区间：

- `scan` 指向当前待检查的元素；
- `before_end` 是小值区的尾后位置，同时也是中间等价区间的起点；
- `after_begin` 是大值区的起点。

扫描过程中始终维持不变量：`[before_end, scan)` 中的元素都与基准等价（区间为空时两者重合）。每一步根据 `*scan` 与 `*first` 的大小关系分为三种情况：

1. **小于基准**：将 `*scan` 与 `*before_end` 交换。若两者不重合，从 `before_end` 换回来的元素已知与基准等价，因此 `scan` 和 `before_end` 可以同步前进一格；若两者重合，则省去交换直接同步前进。
2. **大于基准**：先将 `after_begin` 回退一格，再将其所指元素与 `*scan` 交换（重合时省去交换）。注意此时 **`scan` 必须留在原地**，因为从右侧换回来的元素尚未经过检查，需要在下一轮继续判断。
3. **与基准等价**：在比较器满足严格弱序的前提下，两个方向的比较均不成立即表明等价。此时只推进 `scan`，中间等价区间自然向右扩大一格。

当 `scan == after_begin` 时扫描结束。为了让留在 `first` 的基准与中间等价区间连成一体，将 `before_end` 回退一格得到 `equal_first`：若小值区非空，它指向小值区最后一个元素，与 `first` 交换后基准归入中间区间；若小值区为空，则刚好退回 `first`，基准原地不动。最终返回等价区间 `[equal_first, after_begin)`。

```cpp
template <std::bidirectional_iterator It, class Compare>
    requires std::indirectly_swappable<It, It>
std::pair<It, It> partition_three_way(It first, It last, const Compare& cmp) {
    auto before_end = std::next(first);
    auto scan = before_end;
    auto after_begin = last;

    while (scan != after_begin) {
        if (cmp(*first, *scan)) {
            if (before_end != scan) {
                std::ranges::iter_swap(before_end, scan);
            }
            ++before_end;
            ++scan;
        } else if (cmp(*scan, *first)) {
            --after_begin;
            if (scan != after_begin) {
                std::ranges::iter_swap(scan, after_begin);
            }
        } else {
            ++scan;
        }
    }

    auto equal_first = std::prev(before_end);
    if (equal_first != first) {
        std::ranges::iter_swap(first, equal_first);
    }

    return {equal_first, after_begin};
}

template <std::bidirectional_iterator It, class Compare = greater<std::iter_value_t<It>>>
    requires std::indirectly_swappable<It, It>
void quick_sort_three_way(It first, It last, const Compare& cmp = {}) {
    std::stack<std::pair<It, It>> pending;
    pending.emplace(first, last);

    while (!pending.empty()) {
        auto [begin, end] = pending.top();
        pending.pop();

        if (begin == end || std::next(begin) == end) continue;

        auto pivot = choose_pivot(begin, end, cmp);
        if (pivot != begin) {
            std::ranges::iter_swap(begin, pivot);
        }

        auto [equal_first, equal_last] = partition_three_way(begin, end, cmp);

        pending.emplace(equal_last, end);
        pending.emplace(begin, equal_first);
    }
}
```

对于全相等的输入，三路划分仅需一轮 $O(n)$ 扫描即可将全部元素归入等价区间并结束排序。

## 归并排序（Merge Sort）

### 核心思路与递归实现（Core Idea and Recursive Implementation）

归并排序的核心在于：**如何将两个已经有序的序列合并为一个更大的有序序列**。至于最初的两个有序序列从何而来，只需对任意待排序区间不断从中间对半拆分，直到区间只剩一个元素（天然有序）；随后在递归逐层回溯的过程中，将相邻的两个有序子区间两两归并，直至还原出整个有序序列。

也就是说，**区间的拆分发生在递归深入的过程中，而真正的排序发生在递归回溯的过程中**。

**归并排序演示（递归交换版）**

以 `[4, 2A, 3, 1, 2B]` 为例，观察区间如何在递归过程中不断拆分，以及如何在回溯过程中复用同一片暂存空间完成归并。同时观察相等元素 `2A` 和 `2B` 的相对次序，体会归并排序的稳定性。

<video controls preload="metadata" width="720" src="https://img.mdwind.online/img/20261125141841265.mp4"></video>

[打开图床视频](https://img.mdwind.online/img/20261125141841265.mp4)

https://github.com/user-attachments/assets/5ad6aceb-44ec-4054-9451-f57a8bd78303

```cpp
#pragma once

#include <iterator>
#include <vector>

#include "operations.hpp"

namespace wind {
template <std::random_access_iterator It, class Compare>
    requires std::indirectly_swappable<It, typename std::vector<std::iter_value_t<It>>::iterator>
void _merge_sort(It first, It last, std::vector<std::iter_value_t<It>>& tmp, const Compare& cmp) {
    if (first == last || std::next(first) == last) return;

    auto mid = first + (last - first) / 2;

    _merge_sort(first, mid, tmp, cmp);
    _merge_sort(mid, last, tmp, cmp);

    auto begin1 = first;
    auto begin2 = mid;
    auto begin3 = tmp.begin();

    while (begin1 != mid && begin2 != last) {
        if (cmp(*begin1, *begin2)) {
            std::ranges::iter_swap(begin3, begin2);
            ++begin2;
            ++begin3;
        } else {
            std::ranges::iter_swap(begin3, begin1);
            ++begin1;
            ++begin3;
        }
    }

    while (begin1 != mid) {
        std::ranges::iter_swap(begin3, begin1);
        ++begin1;
        ++begin3;
    }
    while (begin2 != last) {
        std::ranges::iter_swap(begin3, begin2);
        ++begin2;
        ++begin3;
    }

    begin3 = tmp.begin();
    while (first != last) {
        std::ranges::iter_swap(first, begin3);
        ++first;
        ++begin3;
    }
}

template <std::random_access_iterator It, class Compare = greater<std::iter_value_t<It>>>
    requires std::default_initializable<std::iter_value_t<It>> &&
             std::indirectly_swappable<It, typename std::vector<std::iter_value_t<It>>::iterator>
void merge_sort(It first, It last, const Compare& cmp = {}) {
    if (first == last || std::next(first) == last) return;

    std::vector<std::iter_value_t<It>> tmp(last - first);
    _merge_sort(first, last, tmp, cmp);
}
}  // namespace wind
```

实现中有两处关键细节：

1. **默认构造约束**：外层一次性分配与原区间等长的暂存缓冲区 `std::vector<std::iter_value_t<It>> tmp(last - first)`，该构造函数要求元素类型支持默认初始化，因此在概念约束中显式加入了 `std::default_initializable<std::iter_value_t<It>>`。
2. **中点计算**：`mid = first + (last - first) / 2` 采用向下取整，不能额外加 1；否则对长度为 2 的区间 `[0, 2)`，左半区仍是 `[0, 2)`、右半区为空，区间长度无法缩小，会导致无限递归与栈溢出。

### 末端优化（Small-Range Optimization）

归并排序的递归调用树中，当输入规模较大时，底部会产生大量长度极小的分支。假设递归树是一棵高度为 $H$ 的满二叉树，整棵树的节点总数为：

$$
2^H - 1
$$

各底层节点占整棵树的比例非常可观：

| 递归层次 | 节点数 | 约占总节点数 |
| --- | --- | --- |
| 最后一层 | $2^{H-1}$ | 50% |
| 倒数第二层 | $2^{H-2}$ | 25% |
| 倒数第三层 | $2^{H-3}$ | 12.5% |

因此，当子区间长度小到一定阈值（例如 10）时，不再继续向下拆分，而是直接调用直接插入排序将其排好序，就能省去最底层绝大部分的递归调用与小区间归并开销。选择直接插入排序还有两个好处：一是小区间上常数开销极低，二是直接插入排序本身是稳定的，不会破坏归并排序原有的稳定性。

### 自底向上的非递归实现（Bottom-Up Iterative Merge Sort）

归并排序的非递归实现无需像快速排序那样用显式栈模拟递归。递归的目的是先自顶向下拆出有序小区间、再自底向上归并；既然结合末端优化后我们本来就需要长度为 10 的有序小区间，不如直接从底部起步：

1. 将整个待排序区间按长度 10 分组，直接调用 `insert_sort` 使各组内部有序。
2. 将相邻的两个有序区间两两归并。每完成一轮，标准区间长度翻倍，区间总数减半（向上取整）；若本轮区间数为奇数，最后一个区间暂不参与归并，留待下一轮处理。
3. 重复上述过程，直到整个序列合并为唯一一个有序区间。

```cpp
template <std::random_access_iterator It, class Compare>
    requires std::indirectly_swappable<It, typename std::vector<std::iter_value_t<It>>::iterator>
void _merge_sort_iterative(It first, It last, std::vector<std::iter_value_t<It>>& tmp,
                           const Compare& cmp) {
    if (first == last || std::next(first) == last) return;

    auto ceil_div = [](auto n, auto d) { return n / d + (n % d != 0); };

    size_t size = last - first;
    size_t group_count = ceil_div(size, 10);

    auto begin = first;
    for (size_t i = 0; i < group_count; ++i) {
        auto next_group = begin;
        std::ranges::advance(next_group, 10, last);
        insert_sort(begin, next_group, cmp);
        begin = next_group;
    }

    size_t width_multiplier = 1;
    while (group_count > 1) {
        size_t merge_count = group_count / 2;
        begin = first;
        for (size_t i = 0; i < merge_count; ++i) {
            auto left_curr = begin;
            auto mid = left_curr;
            std::ranges::advance(mid, width_multiplier * 10, last);
            auto right_curr = mid;
            auto end = right_curr;
            std::ranges::advance(end, width_multiplier * 10, last);

            auto buffer_curr = tmp.begin();

            while (left_curr != mid && right_curr != end) {
                if (cmp(*left_curr, *right_curr)) {
                    std::ranges::iter_swap(buffer_curr, right_curr);
                    ++right_curr;
                    ++buffer_curr;
                } else {
                    std::ranges::iter_swap(buffer_curr, left_curr);
                    ++left_curr;
                    ++buffer_curr;
                }
            }

            while (left_curr != mid) {
                std::ranges::iter_swap(buffer_curr, left_curr);
                ++left_curr;
                ++buffer_curr;
            }
            while (right_curr != end) {
                std::ranges::iter_swap(buffer_curr, right_curr);
                ++right_curr;
                ++buffer_curr;
            }

            buffer_curr = tmp.begin();
            while (begin != end) {
                std::ranges::iter_swap(buffer_curr, begin);
                ++buffer_curr;
                ++begin;
            }
        }
        group_count = ceil_div(group_count, 2);
        width_multiplier *= 2;
    }
}
```

这里需要注意两处整除的差异：计算总组数 `group_count` 需要向上取整（`ceil_div`），因为尾部不足一组的剩余元素也构成独立分组；而计算本轮需要两两配对归并的对数 `merge_count` 则使用向下取整（`group_count / 2`），落单的最后一组自然留到下一轮。

![bottom-up-merge-sort](https://img.mdwind.online/img/20261125165713983.png)

除此之外，非递归归并还可以采用**逐层写回**的方式：不在每对区间归并后立刻写回原区间，而是让暂存区的写入迭代器持续向后推进，直到整层所有区间（包括落单的最后一组）全部写入暂存区后，再一次性写回原区间。两种写法的时间与空间复杂度一致，这里不再单独列出。

## 内排序与外排序（Internal Sort vs. External Sort）

上述所有排序算法都属于**内排序（Internal Sort）**，即待排序数据能够全部加载到内存中完成处理。当数据量超出内存容量时，就需要借助**外排序（External Sort）**在内存与外存（如硬盘）之间协同完成排序。

外排序的核心依然是归并思想：先将大文件切分为若干能够放入内存的小块，分别读入内存用内排序排好序后写回临时子文件；随后同时打开这些有序子文件，通过文件流逐个读取当前最小元素并写入输出文件，完成多路归并。此处仅介绍基本思路，不展开文件 I/O 实现。

## 非比较排序（Non-Comparison Sorting）

前面讨论的算法都依赖元素之间的大小比较来决定顺序，统称为**比较排序**。除此之外，还存在一类不通过两两比较完成排序的**非比较排序**，常见的有**基数排序（Radix Sort）**和**计数排序（Counting Sort）**。

- **基数排序**：按关键字的各位数字（从低位到高位或从高位到低位）逐位分配与收集。
- **计数排序**：先遍历序列确定数值范围 $[\text{min}, \text{max}]$，开辟对应长度的计数数组统计每个值出现的次数，再按计数顺序展开写回原序列。

计数排序的局限性在于它强依赖于数据范围且仅适用于整数或可离散映射的类型；从本质上看，它是哈希表中**直接定址法**的变形应用。由于本系列尚未展开哈希相关内容，计数排序的完整实现将留待后续专题结合哈希一并讨论。

## 稳定性（Stability）

排序的**稳定性**并非指运行性能的波动程度，而是指：当待排序序列中存在关键字相同的元素（例如 $A_1$ 与 $A_2$）时，**如果排序前 $A_1$ 位于 $A_2$ 之前，排序后 $A_1$ 依然位于 $A_2$ 之前，则称该排序算法是稳定的；否则称为不稳定的。**

稳定性在多关键字排序场景中具有实际意义。例如在考试成绩统计中，如果需要优先按总分排序，总分相同时依次按科目 A、科目 B、科目 C 排序，或者在已有次序的基础上按新关键字二次排序，就必须依赖稳定排序来保留相等记录原有的相对次序。

结合本文的具体实现，各排序算法的稳定性分析如下：

- **冒泡排序（稳定）**：相邻元素仅在严格逆序（`cmp(*left, *right)` 为真）时才交换，相等元素不会越过彼此。
- **直接插入排序（稳定）**：向前扫描时仅在严格逆序时交换，遇到相等元素立即停止，保留原有先后次序。
- **希尔排序（不稳定）**：不同步长分组中的相等元素可能会跨越彼此发生移动，虽然单组内插入是稳定的，但整体无法保证稳定。
- **选择排序（不稳定）**：举一个简单反例——假设序列为 `[A1, A2, B1, B2]` 且 $A > B$，首轮选出最小值 `B1` 与首元素 `A1` 交换后，序列变为 `[B1, A2, A1, B2]`，`A1` 落到了 `A2` 之后，原有次序被破坏。
- **堆排序（不稳定）**：建堆与向下调整过程中的跨层交换会改变相等元素的相对位置。
- **快速排序（不稳定）**：分区过程中的长距离交换会跨越相等元素，破坏原有次序。
- **归并排序（稳定）**：稳定性取决于归并时的分支写法。在本文实现中，只有当 `cmp(*left, *right)` 严格成立（即右半区元素严格更小）时才取右半区元素，否则（包含两元素等价的情况）一律优先取左半区元素，因此能够严格保持稳定。

| 排序算法 | 最好时间复杂度 | 平均时间复杂度 | 最坏时间复杂度 | 空间复杂度 | 稳定性 |
| --- | --- | --- | --- | --- | --- |
| 冒泡排序 | $O(n)$ | $O(n^2)$ | $O(n^2)$ | $O(1)$ | 稳定 |
| 直接插入排序 | $O(n)$ | $O(n^2)$ | $O(n^2)$ | $O(1)$ | 稳定 |
| 希尔排序 | $\Theta(n\log n)$（本文步长） | 取决于步长序列 | $O(n^2)$（本文步长） | $O(1)$ | 不稳定 |
| 选择排序 | $O(n^2)$ | $O(n^2)$ | $O(n^2)$ | $O(1)$ | 不稳定 |
| 快速排序 | $O(n\log n)$ | $O(n\log n)$ | $O(n^2)$ | $O(\log n) \sim O(n)$ | 不稳定 |
| 归并排序 | $O(n\log n)$ | $O(n\log n)$ | $O(n\log n)$ | $O(n)$ | 稳定 |