#  排序

## 从数组函数到泛型算法

在实现排序之前，先看一个更简单的问题：从一组整数中找出最大值。我们把第一个元素记作当前结果，再依次查看后面的元素。遇到更大的元素，就更新当前结果。

如果把整数换成浮点数，这套步骤仍然适用。如果把数组换成链表，我们也可以沿着链表逐个访问元素。再换成一组学生记录，按数学成绩和按英语成绩选出的最高分可能来自不同的学生，但查找的步骤依然相同。

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

这里使用 `std::iter_value_t<It>` 取得迭代器对应的元素类型，`result` 保存的是当前最大元素的值。这个例子使用同类型、可以相互比较的迭代器表示区间两端。数组指针和 `std::list` 的迭代器都可以按这种方式传入。

元素类型和访问方式已经交给了调用者，比较规则还写在函数里的 `<` 上。假设用这个函数查找学生成绩，今天想找数学最高分，明天想找英语最高分。两次查找的循环完全一样，变化的只是比较时看的那一项。于是，我们把这一步也交给调用者，用 `comp(a, b)` 表示按当前规则，`a` 是否排在 `b` 前面。

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

普通函数也可以作为比较器传入。这里再看一种 C++ 写法：给类重载函数调用运算符 `operator()`，这样它的对象就可以写成 `comp(a, b)`。这种对象通常叫作**仿函数**。

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

这两次调用传入的是**同一种仿函数类型**，只是对象保存的状态不同。第一次找到数学得分为 96 的学生，第二次找到英语得分为 97 的学生。查找函数只负责在遍历中比较并更新结果，比较器负责决定这次看哪一科。

这和前面实现 `vector` 时的设计思路相通。`vector` 通过 `allocator_traits` 使用空间配置器，查找算法通过迭代器访问元素，通过比较器判断顺序。各部分通过约定好的操作协作，因此换一种访问方式或比较规则时，查找步骤可以原样复用。接下来实现排序时，也可以沿用这个分工：**算法决定何时比较、何时移动元素，比较器决定两个元素的先后顺序。**

----->>>

这段将会被舍去

## 排序的相关概念

排序：所谓排序，就是使一串记录，按照其中的某个或某些关键字的大小，递增或递减的排列起来的操作。
稳定性：假定在待排序的记录序列中，存在多个具有相同的关键字的记录，若经过排序，这些记录的相对次
序保持不变，即在原序列中，r[i]=r[j]，且r[i]在r[j]之前，而在排序后的序列中，r[i]仍在r[j]之前，则称这种排
序算法是稳定的；否则称为不稳定的。
内部排序：数据元素全部放在内存中的排序。
外部排序：数据元素太多不能同时放在内存中，根据排序过程的要求不能在内外存之间移动数据的排序。  

----------

在接下来的学习过程中，我们将会遇到许多排序算法，这些排序算法各有各的优缺点，也因此应用于不同的场景。

---->>>

### 冒泡排序

在冒泡排序的每一轮中，可以用右边界 `end` 将整个序列划分为两部分：左侧是本轮仍需扫描的**待排序区**，右侧是后续轮次会跳过的**已归位区**。为了方便观察，下面用数组来演示。

![](https://img.mdwind.online/img/20261119021107902.gif)

从动图中可以看到，每轮冒泡排序都从待排序区的左端开始，依次比较相邻的两个元素。如果它们的先后顺序与排序规则相反，就交换它们，然后继续比较下一对。以升序为例，每次比较后，两个元素中较大的那个会留在右侧，并参与下一次比较。这样一路比下去，待排序区的最大元素就会留在本轮的最后一个位置。它已经归位，下一轮只需将右边界左移一格，就可以跳过它。

还可以做一个小优化。如果一整轮都没有发生交换，说明待排序区中的每对相邻元素都符合排序规则，整个待排序区已经有序。此时可以直接结束排序。

下面让我们看看代码, 有些语法细节需要注意

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

为了让迭代器一方面可以向后迭代, 一方面可以让已归位区的左边界不断向前, 迭代器起码应该是一个双向迭代器(支持自++, 自--)(另外要注意双向迭代器不一定支持 it + 1 和 it - 1 )

如果从读取和遍历能力的角度来划分, C++有四种迭代器, 并且在 C++20 , 他们都引入了对应的概念

| 迭代器类型     | C++20 概念                        | 核心能力                                        |
| -------------- | --------------------------------- | ----------------------------------------------- |
| 输入迭代器     | `std::input_iterator<It>`         | 读取元素、向前推进，允许单遍遍历                |
| 前向迭代器     | `std::forward_iterator<It>`       | 在输入迭代器基础上支持多遍遍历                  |
| 双向迭代器     | `std::bidirectional_iterator<It>` | 增加 `--it`、`it--`                             |
| 随机访问迭代器 | `std::random_access_iterator<It>` | 增加 `it + n`、`it - n`、`it[n]` 等随机访问能力 |

注意:  我们把沿着容器的正常遍历顺序移动到下一个元素的行为叫作"向前推进", 比如 {1, 2, 3, 4, 5}, 中 1->2, 2->3 这种, ++it, 不过在一般语境下, 我们常把索引增大称为"向后遍历", 但是用迭代器的专业术语的话, 这其实是在向前走, 与之相反的, 移动到上一个元素的方向, 称之为"向后退回", --it, 一般语境下, 常被叫作"向前遍历". 我们的习惯说法和迭代器专业术语的方向形容词是倒过来的. 

除此之外, 这四种迭代器还是一个递进关系.. 下面三个必然满足输入迭代器的条件, 因此他们也是输入迭代器, 后两个也必然满足前向迭代器的条件, 所以他们也是前向迭代器.... 所以我说"起码", 意思是双向迭代器是最低要求, 随机访问迭代器也可以完全匹配.

另一个模板参数约束条件是`std::indirectly_swappable<It, It>`, 他要求两个迭代器可以对所指向的逻辑元素进行交换, 也就是之后的`std::ranges::iter_swap`, 其实如果你写`std::swap(*left, *right)`也几乎没什么问题...`std::ranges::iter_swap`的使用是为了防止一些特殊情况: 在极小概率情况下, 迭代器解引用出的元素并不是底层真正存储的数据, 但读起来效果一样, 我们这种情况叫作"代理引用". 一个典型的例子是`std::vector<bool>`, 我们知道, bool 类型理应占据一个字节空间, 但实际上, 由于仅靠两种状态(1个比特位)就可以表达出布尔的所有情况, 因此, 标准库对于 `vector<bool>` 进行了模板特化, 多个布尔值可能存在同一个字节里面, 这时候无法通过解引用来进行元素交换, 但是仍旧可以通过 `std::ranges::iter_swap`, 来对两个迭代器所指向的元素进行交换. 

另外, 我们的函数模板参数对于比较器类型采用了缺省, 默认使用大于--标准库默认用的也是大于, 这样最后就得到一个升序序列.

之后是测试, 我也没有专门学过测试, 我也不想写测试代码, 所以我让 AI 去做了, 据 GPT-6.2 Sol 所说, 他测了这些东西

| 测试                 | 验证内容                                                                                                  |
| -------------------- | --------------------------------------------------------------------------------------------------------- |
| 默认升序             | `[1, 3, 2]` 排成 `[1, 2, 3]`。第一对无需交换，仍要继续处理后面的元素，专门防止提前退出写进内层循环。      |
| 子区间降序           | 只对 `[90, 2, 1, 3, 80]` 的中间三项排序，结果为 `[90, 3, 2, 1, 80]`，两端元素保持原位。                   |
| 双向迭代器与稳定性   | 对 `std::list` 中的记录按键排序，`2A, 1B, 2C, 1D` 应变成 `1B, 1D, 2A, 2C`。键相同的记录保持原有相对顺序。 |
| 整轮无交换时提前退出 | 五个已经升序的元素只调用比较器四次，正好扫完一轮。                                                        |
| 空区间与单元素       | 两种调用都不触发比较，单元素值保持原样。                                                                  |

测试结果看起来没什么问题

```bash
[wind@ubuntu-asus build]$ ctest -R '^test_bubble_sort$' --output-on-failure
Test project /home/wind/CS-Rebuild/04-CPP-Language-Basics/sort/build
    Start 1: test_bubble_sort
1/1 Test #1: test_bubble_sort .................   Passed    0.11 sec

100% tests passed, 0 tests failed out of 1

Total Test time (real) =   0.16 sec
[wind@ubuntu-asus build]$ vim ../tests/CMakeLists.txt 
[wind@ubuntu-asus build]$
```



冒泡排序将数组分为两个部分：比较区和保护区。比较区负责存储将要比较的数据，保护区负责存储已经排完序的数据。比较区的每轮比较，将会从数组首元素开始，接着，将两两相邻元素进行比较，从而将比较区的极值移至比较区末尾；在比较区比完一轮后，比较区的最后一个元素就会并入保护区，随后进行下一轮比较。

如果某轮比较区的比较都是合法的（符合相对大小），则证明此时比较区已经有序，不需要再进行比较，比较区就会整体并入保护区。

![动画](https://img.mdwind.online/md/202409011856651.gif)

思路明白之后，写代码就不难了：

```c
typedef int SortData, * pSortData;

bool compare(SortData val1, SortData val2)
{
	if (val1 > val2)
		return true;
	else
		return false;
}

void Swap(pSortData p1, pSortData p2)
{
	SortData transitory = *p1;
	*p1 = *p2;
	*p2 = transitory;
}
```

```c
void Bubble_sort(pSortData pArray, int Size)
{
	int i = 0;
	int j = 0;
	for (i = 0; i < Size - 1; i++)
	{
		bool falg = true;
		for (j = 0; j < Size - i - 1; j++)
		{
			if (compare(pArray[j], pArray[j + 1]))
			{
				Swap(&pArray[j], &pArray[j + 1]);
				falg = false;
			}
		}
		if (falg)
			break;
	}
}
```

为了提高排序算法对不同数据类型的适用性，我们使用`compare`来定义比较元素的相对大小关系，后续排序算法中，若涉及到对元素的比较，则全部通过调用该函数实现。另外，考虑到后续算法可能经常遇到数据交换问题，所以交换函数也专门写出。

为了对冒泡排序进行测试，还需要定义一些外围函数。

```c
pSortData BulidArray(int Size)
{
	pSortData pArray = (pSortData)malloc(sizeof(SortData)* Size);
	if (pArray == NULL)
	{
		perror("BulidArray malloc fail");
		return NULL;
	}
	int circuit = 0;
	for (; circuit < Size; circuit++)
	{
		pArray[circuit] = rand();
	}
	return pArray;
}

void pArrayPrintf(pSortData pArray, int Size)
{
	int circuit = 0;
	for (; circuit < Size; circuit++)
	{
		printf("%d ",pArray[circuit]);
	}
	printf("\n");
}
```

测试（为了让程序以最优性能运行，请将版本改为Release）

```c
void test1()
{
	int Size = 10;
	pSortData pArray = BulidArray(Size);
	int circuit = 0;
	printf("The contents of the original array:\n");
	pArrayPrintf(pArray, Size);
	Bubble_sort(pArray, Size);
	printf("\nThe contents of the sorted array:\n");
	pArrayPrintf(pArray, Size);
	free(pArray);
	pArray = NULL;
}

int main()
{	
	srand((unsigned int)time(NULL));
	test1();
	return 0;
}
```

![image-20240901190841502](https://img.mdwind.online/md/202409011908607.png)

可以看到，测试是通过的。

后续还会对其它排序算法进行测试，测试的大致思路都和`test1()`相同，只不过调用的排序算法不同，这就会使得`test`系列函数过于重复冗余。为此，我们可以用宏定义的方式生成对应的排序算法测试函数。

```c
#define PerformanceTesting(NumSize, Proceedings)					   \
	void test_##Proceedings()										 \
	{															   \
		printf("The test begins.\n");								 \
		printf("The subroutine tested is " #Proceedings ".\n");		    \
		printf("The number of array members is " #NumSize ".\n");	 	\
		srand((unsigned int)time(NULL));							 \
		int Size = NumSize;										    \
		pSortData pArray = BulidArray(Size);						 \
		int circuit = 0;										   \
		printf("\nThe contents of the original array:\n");			  \
		pArrayPrintf(pArray, Size);									\
		clock_t begin = clock();									\
		Proceedings(pArray, Size);									\
		clock_t end = clock();										\
		printf("\nThe contents of the sorted array:\n");			   \
		pArrayPrintf(pArray, Size);									 \
		free(pArray);												\
		pArray = NULL;												\
		printf("\nEnd of test.\n");									 \
		printf("The " #Proceedings " runtime is %dms.\n", end-begin);	\
    }														
```

这个宏定义生成的测试函数将会打印测试的相关信息。`clock()`用于获取从程序启动到`clock()`执行的间隔时间，单位为毫秒；它的返回值为`clock_t`(long)类型，两个`clock_t`一减，就会粗略获得排序算法的运行时间。

```c
PerformanceTesting(10, Bubble_sort)

int main()
{	
	test_Bubble_sort();
	return 0;
}
```

![image-20240901192343599](https://img.mdwind.online/md/202409011923693.png)

这里显示0毫秒是因为单位的精确度不够，数组成员的个数过少，可以换个数。

```c
PerformanceTesting(10000, Bubble_sort)

int main()
{	
	test_Bubble_sort();
	return 0;
}
```

![image-20240901192731726](https://img.mdwind.online/md/202409011927844.png)

### 插入排序



**插入排序演示（相邻交换版）**

以 `[2, 4, 1, 3]` 为例，观察 `start` 如何标记本轮起点，以及 `curr` 如何跟着待插入的元素向左移动。

<video controls preload="metadata" width="720" src="https://img.mdwind.online/img/20261119042621799.mp4"></video>

[打开图床视频](https://img.mdwind.online/img/20261119042621799.mp4)

https://github.com/user-attachments/assets/11d349e6-91a6-40e3-aa19-9d7a73b6b5aa





插入排序的主题思想是将要排序的值依据相对大小关系插入到一个已经有序的结构中。由于单个元素是无法比较的，所以单个成员就可以视为有序的结构，所以插入排序最开始是将首元素作为那个有序结构，随后在此基础上，对剩余元素逐个插入。插入排序分为两种：连续型和离散型。

我们先说连续型，也叫直接插入排序。



可以看到, 相比后面的 C 代码来说, 这里的 C++ 代码还更加精巧一些

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



C代码的思路是先拷贝一份比较区的首元素, 然后再往前面一个个比较, 不符合规则, 往后挪动一位. 而在 C++ 这里, 我们直接通过交换的方式来改变他们之间的原有顺序. 

另外, 还有一些小的语法细节, 需要注意: `start`表示比较区的首元素, 而第一个首元素, 就像我们上面说的那样--单个元素无法比较, 所以天然是有序的, 因此, 这里我们在进入循环之前, 就自加一下, 但这样也会出现一个新的问题: 假设这是一个空区间, 直接一加, 就跳过 `last` 了, 然后就变成死循环了, 所以在最开始我们需要判断一下是不是空区间.

另外要注意的小点是, 双向迭代器只支持 ++ 或者 -- 不支持 + 或者 -, 所以你不能用 + 1 或者 -1 的方式先有 `prev` 再有 `curr`, 或者先有 `curr` 再有 `prev`, 另外要注意的一点是, 如果你选择前者, 即 `prev = start; curr = prev; ++curr;`, 最后会让 `curr`跑到 `last` 上面, 所以我们这里用的是后者.

如果顺序是错误的, 那就进行交换, 更新 `curr`, 让其与有序区的上一个位置继续进行比较, 当 `curr` 变为 `first` 时, 循环自动结束, 并且, 上一轮的内循环中, 已经通过交换把他放在了 `first`, 所以不需要做更多处理. 









![动画](https://img.mdwind.online/md/202409021314164.gif)

实际代码与动图并不完全相同，实际代码是将对比区的首元素临时拷贝一份，这里的删除实际是覆写，但为了更好理解，动图忽略了这些细节。

当对比区首元素与保护区的元素逐个对比时，会出现三种情况：

- 符合排序规则，那就将拷贝数据写入保护区对比元素之后
- 不符合排序规则，那就将保护区对比元素向后挪一位
- 不符合排序规则，且保护区里的元素全部都比完了，就把拷贝数据写入保护区首元素

因此，最初的代码大概是这样的：

```c
void Insert_sort(pSortData pArray, int Size)
{
    int compare_begin, protection_compare;
    SortData temporary_storage;
    for (compare_begin = 1; compare_begin < Size; compare_begin++)
    {
        temporary_storage = pArray[compare_begin];
        for (protection_compare = compare_begin - 1; protection_compare >= 0; protection_compare--)
        {
            if (compare(pArray[protection_compare], temporary_storage))
            {
                pArray[protection_compare + 1] = pArray[protection_compare];
            }
            else
            {
                pArray[protection_compare + 1] = temporary_storage;
                break;
            }
        }
        if(protection_compare == -1)
        {
            pArray[protection_compare + 1] = temporary_storage;
        }
    }
}
```

当遇到第一种情况时，也就是符合规则的情况时，由于循环是`break`出的，所以`protection_compare`并不会改变，因此，后面的`if(protection_compare == -1)`其实也不用写，于是第一种和第三种情况就可以共用一份代码：

```c
void Insert_sort(pSortData pArray, int Size)
{
	int compare_begin, protection_compare;
	SortData temporary_storage;
	for (compare_begin = 1; compare_begin < Size; compare_begin++)
	{
		temporary_storage = pArray[compare_begin];
		for (protection_compare = compare_begin - 1; protection_compare >= 0; protection_compare--)
		{
			if (compare(pArray[protection_compare], temporary_storage))
			{
				pArray[protection_compare + 1] = pArray[protection_compare];
			}
			else
			{
				break;
			}
		}
		pArray[protection_compare + 1] = temporary_storage;
	}
}
```

让我们来测试一下：

```c
PerformanceTesting(10, Insert_sort)

int main()
{	
	test_Insert_sort();
	return 0;
}
```

![image-20240902134310018](https://img.mdwind.online/md/202409021343082.png)

直接插入排序的时间复杂度是标准的等差数列，所以时间复杂度就不细说了，就是$0(N^2)$。不过对于直接插入排序来说，不太容易真的出现$N^2$级别的时间复杂度；出现$N^2$级别的时间复杂度意味着每次比较都是第三种情况，此时的数据其实就是逆序结构。比如在上面的例子中，直接排序会把输入的数组转化为升序数组，如果出现$N^2$级别的时间复杂度，那就意味着输入的数组就是降序数组。

所以对于直接插入排序来说，除了要知道我们通常说的最坏情况的时间复杂度之外，还要知道最好情况的复杂度，什么时候复杂度最好呢？观看上面的动图你可以发现，有些首元素被拷贝之后，直接就被放回了原位，如果每次比较都是这种情况，那就是最好情况。此时直接插入排序的时间复杂度就为$O(N)$，和最坏情况一样，这种级别的复杂度也很难遇到，遇到这种级别的复杂度，意味着，输入的数组就是顺序数组。

虽然冒泡排序和直接插入排序的时间复杂度（通常说的那个时间复杂度）都是$O(N^2)$，但直接插入排序优于冒泡排序。设想这样一种场景：现在需要将输入的数组转化为升序数组，但恰巧数组第一个元素就是最大值，很明显要把这个最大的元素移到最后一位。对于这种数组，直接插入每轮比较都顺手把这个最大的值向后移动一位，每轮比较都是有配合的；而对于冒泡排序来说，各轮比较像是各干各的，每轮比较只负责把极值推到最后。

---------

接下来我们学习离散式插入排序，更多人将其称为希尔排序。

从前面的过程中，我们可以看到，无论是冒泡排序还是直接插入排序，某个数据到达它应有的位置都必须一步一步地移动，最起码在逻辑层面上，数据都是连续移动的，这正是“连续”的一种体现；

有没有少走两步的方法呢？当然是有的，这就引申出了“预排序”的概念。预排序的目的是让数组接近有序，大体上有序，之后再进行一次直接插入排序，从而减少直接插入排序的移动次数。

预排序的具体做法是将原先排序的数组，分为独立的几个部分，这几个独立数组中的成员在原先数组中并不是连续的，而是相隔一定单位的，随后在对这些独立的数组分别进行直接插入。

这里我们暂且将“一定单位”设为3。





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



这里要注意一些语法上的小细节: 在之前, 我们说过, 双向迭代器是不支持 + 1, -1 这种操作的, 更不用说, + n, - n, 但这并不是说我们完全达不到类似的效果, 这里我们用的是 `std::ranges::advance`, 第一个参数是需要变动的迭代器, 第二个是偏移量, 支持负数, 第三个是边界: 他到边界上会自动停下来, 不再迭代器, 他会返回省下还未走完的偏移量, 如果都走完了, 返回0, 如果设定偏移量是 -3, 只走了"两步", 那么返回 -1, 同样的, 设定为 3, 走"一步", 返回 2. 

偏移量的类型使用的是迭代器的偏移量类型. 

从外向里, 第一个循环负责改变 gap 的值, 缩小预排序的间隔, 最终演变为普通的插入排序; 第二层循环, 负责从第二行开始, 从左往右, 从上到下, 依次遍历. 第三个循环, 负责以列的视角, 将当前的元素插入到原来的有序序列中











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



这一版, 想起来更加直观, 但是代码写起来有些琐碎, 平常大家更喜欢用上一版的思路.



-----



尽管这两种写法的循环层数不同，但它们的核心思想是一致的，只是从不同的角度去实现希尔排序。

不过，上述代码并非希尔排序的极限。

我们可以看到，希尔排序的核心思想，是通过较大间隔的预排序，为之后较小间隔的预排序减轻负担。因此，当待排序元素较多时，如果一开始就将间隔设定为 3，间隔变化得可能过于迅速，后续间隔为 3 的预排序仍然需要承担较大的工作量。

所以，如果想进一步提高希尔排序的效率，就需要根据待排序元素的数量，动态调整间隔，使其按照更加合理的阶梯逐步下降。

但这需要建立在一个条件上，那就是使用随机访问迭代器区间来表示待排序的元素序列。

或许，你的第一反应是：这样做是因为随机访问迭代器支持直接相减，可以快速得到待排序元素的数量。但这并不是主要原因。更重要的是，随机访问迭代器往往对应着能够提供较好数据访问局部性的数据结构，因此也往往更有利于提高 CPU 缓存命中率。

这里有必要了解一下计算机的存储层次。计算机采用分层存储结构，距离 CPU 越近的存储部件，读写速度通常越快，但单位存储容量的成本也越高。例如，CPU 内部的寄存器和高速缓存（Cache），访问速度远高于主存（内存），而主存又远快于 SSD 和机械硬盘。

CPU 在执行程序时，如果需要的数据已经存在于高速缓存中，就可以直接从缓存获取；如果缓存中没有，就需要从更低层次的存储中读取，产生额外的访问开销。因此，缓存命中率会直接影响程序的实际运行效率。

这也引出了局部性原理：程序在访问数据时，往往倾向于在较短时间内重复访问已经使用过的数据，或者访问与当前数据位置相邻的数据。合理的数据访问模式能够提高缓存命中率，从而减少 CPU 等待数据的时间。

因此，我们不能只看算法的理论复杂度。理论复杂度描述的是算法运算量随数据规模增长的趋势，而实际运行效率还受到数据布局、访问模式以及缓存命中率等因素的影响。即使两个实现的理论效率相近，它们在实际运行中也可能表现出不同的性能。



-----





代码也是很好写, 上述我们用的那些接口, 比如 `std::ranges::advance` 或者 `std::ranges::iter_swap`, 他们是泛型编程接口, 完全不需要变, 我们只需要在外面套层间隔动态变化的循环就行了



```cpp
template<std::random_access_iterator It, class Compare = greater<std::iter_value_t<It>>>
    requires std::indirectly_swappable<It, It>
void shell_sort(It first, It last, Compare cmp = {}){
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



这里我们用的是除 2 这种间隔迭代公式: 如果个数是偶数, 最后都会除出 2, 这样就可以得到 1, 如果是奇数, 也没什么问题, C/C++ 除法向下取整, 所以其实上和一开始为偶数没什么区别.



关于时间复杂度: 我不知道你们有没有之前有没有接触过时间复杂度这个词, 但是我可以确定的是, 我之前没在我的公开文章里讲过, 所以我这里略微说一下, 

> [!NOTE]
>
> 时间复杂度（Time Complexity）用于描述一个算法的执行效率随输入规模增长而发生的变化。它关注的不是算法实际运行了多少秒，而是当处理的数据量不断增加时，算法所需要执行的操作次数会如何增长。
>
> 通常使用大 O 表示法（Big O Notation）描述时间复杂度，例如：
>
> - \(O(1)\)：常数时间，执行次数不随数据量变化。
> - \(O(n)\)：线性时间，数据量增加多少倍，执行次数也相应增加。
> - \(O(n^2)\)：平方时间，执行次数随数据量的平方增长。
> - \(O(\log n)\)：对数时间，数据量增长时，执行次数增长得相对缓慢。
>
> 时间复杂度主要用于分析和比较算法在不同输入规模下的效率，帮助我们判断算法能否适应更大规模的数据。需要注意的是，时间复杂度反映的是增长趋势，而不是实际运行时间；即使两个算法具有相同的时间复杂度，实际运行效率也可能存在差异。



时间复杂度在不同语境下有着不同的评判标准, 通常是指算法在最坏情况下随着输入规模增长的情况.

对于常规的插入排序来说, 最坏的情况就是每次从比较区里拿出的第一个元素, 参与有序区的比较, 最后都是比完, 放到第一个位置的情况, 这样运算级别就相当于是一个等差数列, 等差数列的和是 $N^2$ 级别, 所以普通插入排序就在这里





### 希尔排序的时间复杂度

这里分析的是按序列长度选择间隔的版本。第一次取 `gap = n / 2`，之后每轮将间隔减半，直到 `gap = 1`。

**最好情况**可以从一个已经有序的序列看起。间隔为 \(g\) 时，前 \(g\) 个元素各自是所在组的第一个元素，外层循环从第 \(g\) 个下标开始，一共访问 \(n-g\) 个位置。每个位置只比较一次就能确定当前元素已经在正确的位置上，因此这一轮恰好比较 \(n-g\) 次，没有交换。由于 \(g\) 最大也只有 \(n/2\)，每轮仍要做线性数量的比较。间隔每轮减半，一共有 \(\lfloor\log_2 n\rfloor\) 轮，所以最好时间复杂度是 \(\Theta(n\log n)\)。

**最坏情况**可以先逐轮估算。间隔为 \(g\) 时，一共有 \(g\) 组，每组约有 \(n/g\) 个元素。每组做一次普通插入排序，因此这一轮最多要做 \(O(g(n/g)^2)=O(n^2/g)\) 的工作。把间隔倒过来看，从 \(1\) 开始至少每轮翻倍，各轮开销之和可以用 \(n^2+n^2/2+n^2/4+\cdots\) 来估算，总上界仍是 \(O(n^2)\)。

这个二次上界确实能达到。以 `5, 1, 6, 2, 7, 3, 8, 4` 为例，`gap = 4` 和 `gap = 2` 的两轮只在同为奇数或同为偶数的下标之间比较，而这两组各自已经有序，所以预排序一次交换都没有。直到 `gap = 1`，最后一轮才开始处理大数在前、小数在后的逆序，相当于直接对原序列做普通插入排序。把这种排列推广到长度为 2 的幂的序列，就能在最后一轮留下 \(\Theta(n^2)\) 个逆序。

希尔排序的优化体现在**较大的间隔能让元素一次跨过多个位置，提前消除一些原本需要多次相邻交换才能消除的逆序**。比如 `5, 6, 7, 8, 1, 2, 3, 4`，普通插入排序需要 16 次相邻交换，而希尔排序在 `gap = 4` 时交换 4 次，整个序列就已经有序了。实际能省下多少工作，取决于输入的排列和选用的间隔序列。上面两个极端能说明这版实现的最好情况和最坏情况，具体能优化到什么量级，还得针对所选的间隔序列和要分析的情况进一步推导。









![动画](https://img.mdwind.online/md/202409031322975.gif)

经过预排序的数组相比未经过预排序的数组相比，在进行直接插入排序时，会出现更多每轮比较只进行一次的情况，算法的时间复杂度将更加靠近$O(N)$。

不过在实际代码中，并不是真的把这一个数组分成独立的几个小数组。而是让下标由每次加一变成每次加一定单位。

```c
void Shell_sort(pSortData pArray, int Size)
{
	//preorder
	int intervals = 3;
	int initial, compare_begin, protection_compare;
	SortData replica;
	for (initial = 0; initial < intervals; initial++)
	{
		for (compare_begin = initial + intervals; compare_begin < Size; compare_begin += intervals)
		{
			replica = pArray[compare_begin];
			for (protection_compare = compare_begin - intervals; protection_compare >= 0; protection_compare -= intervals)
			{
				if (compare(pArray[protection_compare], replica))
				{
					pArray[protection_compare + intervals] = pArray[protection_compare];
				}
				else
				{
					break;
				}
			}
			pArray[protection_compare + intervals] = replica;
		}
	}

	//direct
}
```

不过更常用的是这种：

```c
void Shell_sort(pSortData pArray, int Size)
{
    //preorder
    int intervals = 3;
    int initial, compare_begin, protection_compare;
    SortData replica;
    initial = 0;
    for (compare_begin = initial + intervals; compare_begin < Size; compare_begin++)
    {
        replica = pArray[compare_begin];
        for (protection_compare = compare_begin - intervals; protection_compare >= 0; protection_compare -= intervals)
        {
            if (compare(pArray[protection_compare], replica))
            {
                pArray[protection_compare + intervals] = pArray[protection_compare];
            }
            else
            {
                break;
            }
        }
        pArray[protection_compare + intervals] = replica;
    }

    //direct
}
```

只用两层循环，但实际还是一样的，不同的是，只有两层循环实际上是先把第一个独立数组比较一轮，再把第二个独立数组比较一轮，接着把第三个独立数组比较一轮，然后再让第一个独立数组比较一轮······

三层循环则是先把第一个独立数组完全比完，再去比较第二个独立数组和第三个独立数组。可以这样认为三层循环的代码是三个独立数组异步走，而只有二层循环的代码是三个独立数组同步走。

它们效率实际上是完全一样的，只不过两层循环看上去比三层循环更好看，所以常见的还是用两层循环。

好的，让我们先不写后续的直接插入，直接先测试一下：

```c
PerformanceTesting(10, Shell_sort)

int main()
{	
	test_Shell_sort();
	return 0;
}
```

![image-20240903153837511](https://img.mdwind.online/md/202409031538889.png)

我们把`intervals`改成1试试

![image-20240903154137223](https://img.mdwind.online/md/202409031541395.png)

我们发现此时输出的数组就是有序的，为什么呢？因为间隔为1时，每个独立数组其实就只有一个成员，或者说，间隔为1的时候，独立数组只有一个，那就是输入数组本身。也就是说，直接插入排序，或者说连续式插入排序其实就是希尔排序，或者说离散式排序的一种特例，它们之间是被包含与包含的关系。

或者，也可以说，间隔`intervals`决定了输出数组的有序度。`intervals`越大（当然是合法的越大），输出数组的有序度就越小；而当`intervals`为1时，输出数组就是完全有序的。

于是，我们就可以改变`intervals`的值，让数组进行多次希尔排序，每次排序都可以被视为后一个排序的预排序，最后让`intervals`等于1即可。`intervals`就用数组成员个数来初始化。

```c
void Shell_sort(pSortData pArray, int Size)
{
	int intervals = Size;
	int compare_begin, protection_compare, initial = 0;
	SortData replica;
	while (intervals > 1)
	{
		intervals = intervals / 3 + 1;
		for (compare_begin = initial + intervals; compare_begin < Size; compare_begin++)
		{
			replica = pArray[compare_begin];
			for (protection_compare = compare_begin - intervals; protection_compare >= 0; protection_compare -= intervals)
			{
				if (compare(pArray[protection_compare], replica))
				{
					pArray[protection_compare + intervals] = pArray[protection_compare];
				}
				else
				{
					break;
				}
			}
			pArray[protection_compare + intervals] = replica;
		}
	}
}
```



C++ 化后遇不到这些问题, 所以我们就删除他们吧.









`intervals`在其中的迭代公式为`intervals = intervals / 3 + 1;`它的思路是通过不断地整除三让`intervals`变小，最终让`intervals`小于三，此时加一就发挥了作用，它会使得`intervals`最终变成一，在执行完间隔为1的希尔排序后，借由`while (intervals > 1)`跳出循环，完成排序。

有人可能会问`while (intervals > 1)`能不能带等于号，答案是不行的。

第一个原因，不算致命问题。从代码中可以看出，它的逻辑是，先判断`intervals`，再调整`intervals`，然后再进行一次希尔排序。如果`intervals`已经为1了，则意味着上一次希尔排序间隔就为1，为什么还要再排一次呢？

第二个原因，是致命问题。当`intervals`为1之后，它的值就永远为1了，如果加上等号，程序就会陷入死循环。

除此之外，另一种主流的迭代公式为`intervals = intervals / 2;`。这是什么思路呢？数可以被分为奇数偶数，如果`intervals`最初是偶数，那`intervals`最终必会等于1，然后由`while (intervals > 1)`跳出循环；如果`intervals`最初是奇数，由于这里是整除，所以和偶数是一样的。

希尔排序的间隔公式还有其它版本。只要你数学好，能推导出满足要求的公式，那就可以用。

```c
PerformanceTesting(10, Shell_sort)

int main()
{	
	test_Shell_sort();
	return 0;
}
```

![image-20240903215139914](https://img.mdwind.online/md/202409032151156.png)

希尔排序的效率远高于直接插入排序。甚至可以直接与快排和堆排序一较高下。

下面我们来浅谈一下希尔排序的时间复杂度。为什么是浅谈呢？因为我数学不好，希尔排序的时间复杂度推导超出了我的数学知识水平。等我学了相关数学知识后再把没说的细节补上。

---------

好的，让我们先看最外层的循环，也就是`while (intervals > 1)`；如果以`intervals = intervals / 3 + 1;`来看的话，复杂度就为$log_3N$，（由于时间复杂度是粗略计算，所以后面的那个“1”就忽略了。）

从第二层循环开始，这就超出了我的知识水平。由于`intervals`是在变化的，所以非常难计算。我们只能粗略算一下，怎么算呢？

我们从`intervals`的两个极端入手。

当`intervals`很大时，比如说$\frac{Size}{3}$，此时粗略来讲，将会有$\frac{Size}{3}$个独立数组，每个数组有三个成员，前面说过，直接插入排序的时间复杂度是个标准的等差数列，所以对于单个独立数组来说，它的具体复杂度就是1+2+3等于6，那有多少个独立数组呢？一共有$\frac{Size}{3}$个独立数组，所以此时的时间复杂度就为$\frac{Size}{3}*6=2Size$，也就是说，这是$O(N)$级别的。

当`intervals`很小时，经过前面的预排序之后，此时原数组已经几乎是有序了。所以此时的复杂度就是前面说的最好情况`O(N)`。

所以说，单从`intervals`的两个极端来说，它的复杂度都是$O(N)$。

据说，当`intervals`又不大又不小的时候，时间复杂度会增加。所以`intervals`从大到小，其复杂度的变化过程应该是先上升再下降。

上面说的这些，是让大家明白，非常粗略地来讲（即使是对复杂度来说，也是过于粗略的，不能真的作为复杂度的。）它的复杂度是$O(N*log_2N)$，这个级别的复杂度差不多能赶上堆排序和快排了。所以说希尔排序的效率远远高于直接插入排序。

至于希尔排序的具体时间复杂度就不说了，一方面是，这和`intervals`的迭代公式有关；另一方面，这真的很难算。

那到底多少呢？我也是听别人说的，大概是$O(N^{1.25})$到$O(1.6N^{1.25})$。非要给具体值就是$O(N^{1.3})$。

### 选择排序



**双向选择排序演示（边扫描边交换）**

以 `[6, 2, 8, 4, 9, 1, 3]` 为例。每轮先比较待排序区的两端，必要时交换，再让 `scan` 从左向右扫描。遇到应该排得更靠前或更靠后的元素，就当场交换到对应的一端。扫描结束后，两端归位，下一轮继续处理剩下的区间。

<video controls preload="metadata" width="720" src="https://img.mdwind.online/img/20261122100359579.mp4"></video>

[打开图床视频](https://img.mdwind.online/img/20261122100359579.mp4)

https://github.com/user-attachments/assets/f36fdd0f-a9b6-46c5-8eb9-675b00c2ca28





选择排序将序列分成已归位区和待排序区。每一轮扫描待排序区，找出按目标顺序应该排在最前面的元素，把它放到待排序区的左端。这个元素从此归位，下一轮只需处理剩下的元素。

而在这里, 我们使用了一个小优化: 将其变为双向选择排序, 双向选择排序沿用同一个思路，只是每轮同时选出应该排在最前面和最后面的元素，让它们分别在两端归位。待排序区也就从两端向中间逐步缩小。



```cpp
#pragma once

#include <iostream>

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



尽管核心思想较为简单, 但有些代码细节需要注意.



首先注意到, 对于双端迭代器 `first` 和 `last` , 其区间是半实半开的, `first` 指向的是待排序区的第一个元素, 而 `last` 指向的是已归位区后半部分的第一个元素, 这是故意而为的--为了避免全实区间一起迭代, 相互叉开的情况, 假设现在我们使用的是全实区间的双端迭代器, 现在待排序区实际上已经排完, `A B`, 两个迭代器都指向他们, 现在如果他们一起迭代, 就会彼此查看, 命中不了"相等"的循环退出条件, 所以就死循环了. 而采用半实半开区间的方式, 就能很好描述和判断空区间.



在两个迭代器都分步迭代后, 再进行以此判断, 是为了排除待排序区只有一个元素的情况, 那样自然是不需要再进行排序的.



随后, 我们将待排序区最左边和最右边的元素作为比较基准, 去判断中间元素中是否有更适合放到一端的, 不过, 在那之前, 还需要再比较一下这两端, 避免基准失真的情况--如果不比较的话, (假设我们想要的升序), 左边可能是更大的数值, 而右边可能是更小的数值, 那意味着如果触发交换, 还要把交换过来的重新进行比较, 看看能不能放到最右端, 所以就不能写成 if lese, 而是两个 if, 那会让逻辑很混乱, 并且, 最后还是要比较一下两端, 























































选择排序非常简单。但效率太低了。它的思想是从数组中找出一个极值，把它放到应有的位置上，然后从剩余部分再找极值，依次类推。

我们稍微优化一下，每轮比较把最大值和最小值都找出来。我们通过交换把这两个极值放在合适的位置上：

![动画](https://img.mdwind.online/md/202409041525680.gif)

大概是这个意思，不得不说，选择排序效率太低了，我画图都画了很长时间，画完没有细看是不是完全对的。

不过若是还这样写，还不行

```c
void Select_sort(pSortData pArray, int Size)
{
	int pend_begin, pend_end;
	int max, min, current;
	for (pend_begin = 0, pend_end = Size - 1; pend_begin < pend_end; pend_begin++, pend_end--)
	{
		max = pend_end;
		min = pend_begin;
		for (current = pend_begin; current < pend_end + 1; current++)
		{
			if (compare(pArray[current], pArray[max]))
			{
				max = current;
			}
			if (compare(pArray[min], pArray[current]))
			{
				min = current;
			}
		}
		Swap(&(pArray[pend_begin]), &(pArray[min]));
		Swap(&(pArray[pend_end]), &(pArray[max]));
	}
}
```

在交换成员时，有时会出现一种情况，这种情况在动画中并没有体现出来。如果`pend_begin`恰好就和`max`相同时，在进行第一次交换后，原先选出的最大数就会跑到`min`的位置上，从而出现问题。所以还要略微修改。

```c
void Select_sort(pSortData pArray, int Size)
{
	int pend_begin, pend_end;
	int max, min, current;
	for (pend_begin = 0, pend_end = Size - 1; pend_begin < pend_end; pend_begin++, pend_end--)
	{
		max = pend_end;
		min = pend_begin;
		for (current = pend_begin; current < pend_end + 1; current++)
		{
			if (compare(pArray[current], pArray[max]))
			{
				max = current;
			}
			if (compare(pArray[min], pArray[current]))
			{
				min = current;
			}
		}
		Swap(&(pArray[pend_begin]), &(pArray[min]));
		if (pend_begin == max)
		{
			max = min;
		}
		Swap(&(pArray[pend_end]), &(pArray[max]));
	}
}
```

```c
PerformanceTesting(10, Select_sort)

int main()
{	
	test_Select_sort();
	return 0;
}
```

![image-20240904153338179](https://img.mdwind.online/md/202409041533321.png)

### 堆排序



堆排序目前略: 因为他需要堆这个数据结构的支持--而我的公开文章中目前并没有说过堆. 他被安排在后面.













之前说过堆排序，就在《二叉树和堆》那个项目下，这里再简单地回顾一下。

堆排序利用的是堆根节点是堆中成员极值的性质。先将输入的数组通过调整算法调整为堆，再把根节点数值与数组尾元素数值进行交换，接着再把剩余部分调整为堆；不断循环，最后得出有序数组。

示意图在《二叉树和堆》文档中已经给出，在此不做赘述。

```c
static int FindFristChild(int parent, int Size)
{
	int child = parent * 2 + 1;
	if (child < Size)
	{
		return child;
	}
	else
	{
		return -1;
	}
}

static int FindSecondChild(int parent, int Size)
{
	int child = parent * 2 + 2;
	if (child < Size)
	{
		return child;
	}
	else
	{
		return -1;
	}
}

static void DownwardAdjustment(pSortData pArray, int Size, int start)
{
	int parent = start;
	int child;
	while (parent < Size)
	{
		int first_child = FindFristChild(parent, Size);
		int second_child = FindSecondChild(parent, Size);
		if (first_child == -1 && second_child == -1)
		{
			break;
		}
		else
		{
			child = first_child;
			if (second_child != -1)
			{
				if (compare(pArray[second_child], pArray[first_child]))
				{
					child = second_child;
				}
			}
		}
		if (compare(pArray[child], pArray[parent]))
		{
			Swap(&(pArray[child]), &(pArray[parent]));
		}
		parent = child;
	}
}

void Heap_sort(pSortData pArray, int Size)
{
	int parent = ((Size - 1) - 1) / 2;
	for (; parent >= 0; parent--)
	{
		DownwardAdjustment(pArray, Size, parent);
	}
	int end;
	for (end = Size - 1; end > 0; end--)
	{
		Swap(&(pArray[0]), &(pArray[end]));
		DownwardAdjustment(pArray, end, 0);
	}
}
```

```c
PerformanceTesting(10, Heap_sort)

int main()
{	
	test_Heap_sort();
	return 0;
}
```

![image-20240905083612392](https://img.mdwind.online/md/202409050836625.png)

### 快速排序

快速排序采用分治的思想。它先在待排数组中任取一成员作为基准值，随后依据该值将数组分为两个子部分，分别存放大于和小于基准值的成员，随后再将这两个子部分视为新的待排数组，重复上述步骤。

因为快速排序使用递归结构，所以要先实现单轮排序。单轮排序一共有三种实现方式。

第一种：`Hoare`法。`Hoare`正是快速排序的提出者，此种方法也是快速排序的原生思路。

在`Hoare`法中，默认选择待排序数组的第一个成员作为基准值；随后创建两个指针，最开始分别指向待排数组的第一个成员和最后一个成员；为了方便叙述，下面将这两个指针依据其相对方位分别命名为`left`和`right`;`left`的职责是寻找大于基准值的数，而`right`于此正好相反，这两个指针找到各自的目标后，会对所指向的数组成员进行数值交换，然后重复上述过程，直到两个指针指向同一个数组成员；这个成员所处的位置正是基准值应该处于的位置，此时，对该成员与数组第一个成员（也就是基准值）进行数值交换；单轮排序就结束了。

这两个指针采取“异步”的方式寻找目标，即某个指针（比如A）找到目标后，再让另一个指针（B）寻找自己的目标，在交换数值后，另一个指针（A）再寻找目标。指针最初的移动顺序也有讲究。当要生成升序数组时，由于基准值最后是通过与相遇位置成员进行数值交换才来到应有位置的，而基准值又默认为第一个成员的数值，所以必须要确保被基准值交换的成员数值是小于基准值的，为此，必须先让`right`指针先进行移动；当`left`与`right`相遇时，由于`right`先进行移动，所以绝大多数情况下，都是`right`先找到目标，然后`left`在寻找自己对应目标的过程中与`right`相遇，这意味这相遇位置的成员数值必然是小于基准值的。同理，若将基准值设置为最后一个成员，则必须先让`left`先走，以确保相遇位置的数值大于基准值。也就是说，两指针的移动顺序与基准值的位置有关。















----

**快速排序演示（以首元素为基准分区）**

以升序为例，观察 `last` 怎样先向左找小于基准的元素，`first` 又怎样向右找大于基准的元素。若两端还没相遇，就交换这两个放错边的元素。视频分别演示了两种相遇方式，并用 `[1, 2]` 说明为什么要让 `first` 从 `key` 开始。

<video controls preload="metadata" width="720" src="https://img.mdwind.online/img/20261122153622125.mp4"></video>

[打开图床视频](https://img.mdwind.online/img/20261122153622125.mp4)

https://github.com/user-attachments/assets/42bf57a0-6edb-4ccc-abc4-5092130a9818





### 以第一个元素为基准进行分区

我们先以升序为例。选定第一个元素作为基准后，希望把序列分成三部分：左边的元素都小于等于基准，中间是基准本身，右边的元素都大于等于基准。为此，可以准备两个迭代器，从区间两端向中间扫描，另用 `key` 记住基准的位置。

区间是左闭右开的 `[first, last)`。一开始，`last` 指向尾后位置，所以它要**先向左走一步，再比较**，直到找到一个严格小于基准的元素。`first` 已经指向一个元素，所以它**先比较，再向右走**，直到找到一个严格大于基准的元素。如果两个迭代器还没相遇，就交换它们所指的元素。这样，左侧当前位置换进了一个比基准小的元素，右侧当前位置换进了一个比基准大的元素。

### 两个迭代器相遇时

如果是**左侧追上右侧**，说明右侧已经找到了一个小于基准的元素，左侧刚好走到这里。于是可以把基准换到相遇位置，让这个较小的元素回到区间开头。

如果是**右侧退到左侧**，就要看此前有没有进行过交换。如果还没交换过，`first` 仍在 `key` 上，右侧一路退回来，基准原地归位。如果已经交换过，`first` 当前位置上的元素就是上一次从右边换来的，它严格小于基准，所以也可以和基准交换。最后返回基准归位后的迭代器。

### 为什么一开始不跳过 `key`

乍一看，可以先做一次 `++first`，把基准和扫描区间分开。但拿 `[1, 2]` 试一下，右侧会在 `2` 的位置碰到左侧边界。它停下来是因为已经走到了头，此时 `2` 依然大于基准 `1`。如果照常交换，原本有序的序列就会变成 `[2, 1]`。所以这里让 `first` 从 `key` 开始，给右侧保留一路退回基准位置的可能。

还有一个细节。`advance` **恰好走到边界时仍返回 `0`**。以单元素区间为例，`last` 第一次回退恰好来到 `key`，接着还会拿基准和自身比较一次。再次回退才会因为走不动而返回 `-1`。左侧尝试前进同样走不动，返回 `1`。最后两个迭代器都停在 `key`，直接返回这个位置。空区间则可以由外层快排直接处理。



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

    auto key = partition_around_first(first, last, cmp);
    Hoare_sort(first, key, cmp);
    Hoare_sort(std::next(key), last, cmp);
}
}  // namespace wind

```



----



































除此之外，另一种特殊情况，先行指针在遍历完整个选中数组后仍没有找到目标，此时两指针直接在基准值相遇，但由于指针相遇位置与基准值位置相同，所以数值交换不会产生有效影响。

对于和基准值相同的数值成员，两指针不会进行任何响应（不视为目标），而是交由后续轮次排序处理。

以下动画展现的是基于`Hoare`法单轮排序的整体过程，而非单轮排序过程。

![动画](https://img.mdwind.online/md/202409051944718.gif)

```c
static int Hoare_mode(pSortData pArray, int left, int right)
{
	int key = left;
	while (left < right)
	{
		while (left < right && !compare(pArray[key], pArray[right]))
		{
			right--;
		}
		while (left < right && !compare(pArray[left], pArray[key]))
		{
			left++;
		}
		Swap(&(pArray[left]), &(pArray[right]));
	}
	Swap(&(pArray[right]), &(pArray[key]));
	return right;
}

tatic void _Quick_sort_root(pSortData pArray, int left, int right)
{
	if (left >= right)
		return;
	int key = Hoare_mode(pArray, left, right);
	_Quick_sort_root(pArray, left, key - 1);
	_Quick_sort_root(pArray, key + 1, right);
}

void Quick_sort(pSortData pArray, int Size)
{
	_Quick_sort_root(pArray, 0, Size - 1);
}
```

在实际写代码时，要特别注意两指针找目标的循环条件。前面的`left < right`，防止跑出数组；后面的大小比较一定要带等于号，试想一下这种情况，当数组中除基准值时还含有两个和基准值相同的成员，而指针循环条件没带等号时

```c
while (left < right && pArray[right] > pArray[key])
{
    right--;
}
while (left < right && pArray[key] < pArray[left])
{
    left++;
}
```

这两个指针就会把与基准值相等的那两个值分别选为目标，交换之后，两个指针的指向内容依旧与基准值相等，所以依旧不会进入循环，两指针不会发生变化，于是它们就会再交换一下，于是，就死循环了。

```c
erformanceTesting(10, Quick_sort)

int main()
{	
	test_Quick_sort();
	return 0;
}
```

![image-20240905203056503](https://img.mdwind.online/md/202409052030659.png)

第二种，填坑法。





**快速排序演示（挖坑填坑法）**

以 `[5, 8, 2, 7, 3]` 为例，先取出首元素作为基准，再从两端交替填坑。每填一次，元素原来的位置就成了下一个坑。两端相遇时，把基准填回最后一个坑。

约 33 秒处换用 `std::unique_ptr<int>` 演示。`key` 接管首元素所指的整数后，原槽位变成 `nullptr`。这时先判断 `first == last`，就能在两端相遇时跳过比较，避免解引用空指针。

<video controls preload="metadata" width="720" src="https://img.mdwind.online/img/20261122225558556.mp4"></video>

[打开图床视频](https://img.mdwind.online/img/20261122225558556.mp4)

https://github.com/user-attachments/assets/f401b025-9321-4933-8b58-7d5f02750154



对于填坑法来说, 在代码逻辑上更容易进行控制, 但是相对于之前我们写的原教旨快速排序, 霍尔法的 C++ 代码来说, 填坑法的代码就不是那么优雅简洁了. 在这里, 我们采用了移动语义来进行覆写, 赋值的行为, 这里用到的新的接口 `std::ranges::iter_move` 是将迭代器指向的元素表示为右值形式返回, 所以命中了移动语义, 不过移动语义倒也引入了新的坑. 对于 last 来说, 变化不大, 仍旧是先移动, 再判断是否到边界, 再进行比较, 但是我们看到, 对于 first 来说, 其循环条件则也写成了先判断是否到达边界, 再去比较... 这是特意这样写的, 如果用原先霍尔法的顺序, 结合移动语义可能出现问题: 这种场景也不能说是非正常的用法, 其实也很常见的, 那就是采用间接存储的方式来往容器里面装元素, 容器存储的并不是元素的本体, 而是指向元素的指针(而且这里大概率不是原生指针, 而是被包装的指针对象, 至于原因, 时候到了我们自然会说), 对于这种存储形式, 自定义比较器的逻辑大概是解引用迭代器, 找到里面存的地址, 地址再解引用, 找到元素, 进行比较, 如果是原生指针, 那其实问题不大, 因为原生指针是内置类型, 他们没有完善的移动语义, 所以移动实际上还是采用赋值的行为, 但问题是, 这里大概率不会是原生指针, 而是一些对指针进行了再包装的指针对象类型, 比如视频中的 `std::unique_ptr`,  对于这些指针包装器来说, 他们的移动语义接口当然是完善的, 所以移动之后, 会把自身存储的指针置为空, 这时候, 如果再参与比较, 比较方法里面再解引用出包装指针, 包装指针再解引用, 就是对空指针进行解引用了, 所以在这里, 我们特意调整了 first 的循环条件顺序: 当 last 一路狂奔, 直接到 first, 尽管 first 目前已经是一个空指针, 但是由于已经到达边界, 命中 `first == last`, 所以 `&&` 短路, 后面的比较就不会进行.





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































从上面的学习中，可以看到霍尔法有很多坑，于是就有人以霍尔法的思想为指导，创造出了填坑法。

填坑法与霍尔法的主要区别就是数据的传递方式的不同。霍尔法的数据传递方式是交换，而填坑法的数据传递是覆写。

和霍尔法类似，我们先默认基准值是数组第一个成员。在确定基准值之后，对基准值进行拷贝，由于拥有备份，所以基准值在数组中的原位置就可以随意处理了，此时它就变成了一个坑，可以写入数组中的其它数据。然后就要寻找填入坑的数据，由于坑最开始位于数组的第一个成员处，所以想要找数据自然是要从数组最后一个成员处开始寻找。于是`right`指针就登场了，它会寻找比基准值小的数，找到之后，就把自己指向的数据写入坑里，此时`right`指向的数据也有了拷贝，于是`right`就成为了新的坑，有新的坑，就要寻找新的数据，由于此时的坑在右侧，所以想要找新的数据自然是要从数组左侧开始找起，于是`left`就登场了，它会寻找大于基准值的数据，找到之后填入坑里，于是它指向的地方就成为了新坑，`right`就会找数据用来填入新坑，重复上述过程，当两指针相遇后，它们指向的位置就是基准值应处于的位置，于是把之前拷贝的基准值写入这个位置。

![动画](https://img.mdwind.online/md/202409060917428.gif)

```c
static int FillGap_mode(pSortData pArray, int left, int right)
{
	SortData key = pArray[left];
	int gap = left;
	while (left < right)
	{
		while (left < right && !compare(key, pArray[right]))
		{
			right--;
		}
		pArray[gap] = pArray[right];
		gap = right;
		while (left < right && !compare(pArray[left], key))
		{
			left++;
		}
		pArray[gap] = pArray[left];
		gap = left;
	}
	pArray[gap] = key;
	return gap;
}

static void _Quick_sort_root(pSortData pArray, int left, int right)
{
	if (left >= right)
		return;
	int key = FillGap_mode(pArray, left, right);
	_Quick_sort_root(pArray, left, key - 1);
	_Quick_sort_root(pArray, key + 1, right);
}

void Quick_sort(pSortData pArray, int Size)
{
	_Quick_sort_root(pArray, 0, Size - 1);
}
```

当然，此时仍需要注意循环变量的等于号。

```c
PerformanceTesting(100000, Quick_sort)

int main()
{	
	test_Quick_sort();
	return 0;
}
```

![image-20240906092011072](https://img.mdwind.online/md/202409060920225.png)

第三种方法，没有统一的命名，依据思路，要不叫它“跟屁虫法”或者“搜索法”？























**同向双指针分区演示**

以 `[6, 1, 9, 7, 4, 6, 5]` 为例，观察 `scan` 如何把小于基准的元素“甩进”左区，以及扫描结束后 `key` 如何与 `boundary` 交换位置。

<video controls preload="metadata" width="720" src="https://img.mdwind.online/img/20261123001532929.mp4"></video>

https://github.com/user-attachments/assets/66c8115c-6178-4a22-9da6-1d083c7f2c03



以升序为例，同向双指针在扫描过程中维护两个区间。`(key, boundary]` 存放严格小于基准的元素，`(boundary, scan)` 存放已经扫过、大于等于基准的元素。每当 `scan` 找到一个小于基准的元素，就先让 `boundary` 向前走一格，再把这个元素交换到新扩出来的位置。如果 `boundary` 恰好追上了 `scan`，说明这个元素已经在该在的位置，只推进边界就够了。

扫描结束后，只要小值区里有元素，`boundary` 指向的就是最后一个小值的位置。此时把它和 `key` 交换，较小的元素去了区间开头，基准到了小值区的末尾。于是基准左边全是小于它的元素，右边全是大于等于它的元素。如果一个小值也没找到，`boundary` 就一直和 `key` 重合，基准留在原位。





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



这里是同向的, 因此迭代器约束也变成了前向迭代器





















在搜索法中，同样有两个指针，一个指针负责搜索目标，另一个指针负责尾随前一个指针。还是以数组首元素为基准值，搜索指针会寻找比基准值小的数据，找到一个，尾随指针就会向后移动一位，然后这两个指针指向的内存块就会交换数值，当搜索指针跑出数组后，尾随指针指向的内存块就会和基准值交换。

![动画](https://img.mdwind.online/md/202409060953553.gif)

```c
static int Search_mode(pSortData pArray, int left, int right)
{
	int key = left;
	int prev = left;
	int curr = left;
	while (curr <= right)
	{
		if (compare(pArray[key], pArray[curr]))
		{
			Swap(&(pArray[++prev]), &(pArray[curr]));
		}
		curr++;
	}
	Swap(&(pArray[prev]), &(pArray[key]));
	return prev;
}

static void _Quick_sort_root(pSortData pArray, int left, int right)
{
	if (left >= right)
		return;
	int key = Search_mode(pArray, left, right);
	_Quick_sort_root(pArray, left, key - 1);
	_Quick_sort_root(pArray, key + 1, right);
}

void Quick_sort(pSortData pArray, int Size)
{
	_Quick_sort_root(pArray, 0, Size - 1);
}
```

```c
PerformanceTesting(100000, Quick_sort)

int main()
{	
	test_Quick_sort();
	return 0;
}
```

![image-20240906100446971](https://img.mdwind.online/md/202409061004095.png)

也还可以优化优化：

```c
static int Search_mode(pSortData pArray, int left, int right)
{
	int key = left;
	int prev = left;
	int curr = left;
	while (curr <= right)
	{
		if (compare(pArray[key], pArray[curr]) && ++prev != cur)
		{
			Swap(&(pArray[prev]), &(pArray[curr]));
		}
		curr++;
	}
	Swap(&(pArray[prev]), &(pArray[key]));
	return prev;
}
```

就是加加后还等于搜索指针就不交换了。其实优不化优化都行的。

--------

接下来我们看看快速排序的时间复杂度，当基准值恰好为选中数组的中位数时，快速排序效率达到最高，此时快速排序的结构与二叉树类似

![image-20240906132723453](https://img.mdwind.online/md/202409061327706.png)



这是新图, 他将代替原来的旧图.

![quicksort-time-complexity](https://img.mdwind.online/img/20261123003048181.png)



每个节点就可以被视为一个函数栈帧，一共有$log_2N$层，每一层所选中数组部分合在一块就相等于整个数组，所以每层都是$N$，再乘一下，于是就得到时间复杂度$O(N*log_2N)$。

最坏情况是什么呢？那就是每次选中的基准值都恰好是极值，此时的函数栈帧更像是链表而非树，每层的复杂度仍是$N$，但此时深度已经变成了$N$，所以复杂度就变成了$O(N^2)$。

前面说过，基准值实际是可以任意选择的，所以为了避免出现最坏情况，就可以对快速排序进一步优化：

我们先挑出三个预选值，分别是数组末尾，开头，中间，然后选择中间的那一个。但如果直接在单轮排序上修改就太麻烦了，所以我们的实际操作是先把三个数中间的那个数找出来，然后让它与数组首元素进行数值交换。



我们先写一个辅助性的接口, 输入三个迭代器及其比较方法, 他会返回排列在中间的那个迭代器



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



cmp(x, y) 为真表示 x 应当在 y 后面, 第一次比较是确保 c 一定在 a 后面, 把这个作为已知条件, 如果确定 a 也在 b 后面, 则正确顺序是 b a c , 所以返回 a, 如果不是, 则意味着 b 在 a 后面, 但我们不能确定, b 是不是还在 c 后面, 所以再进行比较, 如果 b 在 c 后面, 那么自然就是 a c b , 所以返回 c , 如果还不是, 那么说明 c 在 b 后面, 所以返回 b



另外, 这里比较器用的是常引用, 之前我不用常引用并不是什么特别的原因, 而是我纯粹忘记加了.





另外要说的是, 对于起码是前向迭代器来说. 我们可以通过快慢指针的方式找到位于中间位置的迭代器



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





这个函数模板负责找基准, 也就是 `pivot`, 在快速排序中一般被译作基准. 这里还有一个问题, 有没有可能区间里面不足三个元素? 在这里我们是通过判断找到到 mid 和最后一个元素的位置 tail 是否相同来判读的, 由于我们这种做法是取靠右的中间迭代器(偶数元素的区间, fast 最后会落到两个元素中更右边的那个, 比如对于仅有两个元素的区间来说, mid 会落到第二个元素上), 如果 mid 和 tail 相同, 就意味着他们不足三个元素, 此时没必要再调整基准值, 用原来的第一个就可以了, 所以直接返回 first, 而元素区间够的情况下, 就会复用之前的 `median_of_three`, 返回一个排在中间的迭代器



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



对于最后的上层方法, 也进行了调整, 一方面是用上常引用了, 另一方面我们将下层的单过程以参数的方式进行了传入.





接下来我们测试一下, 考虑到测试细说又是另外一个东西, 并且我用的是 Boots_Test, 你们也可能没有, 所以我就不贴测试代码了







### 递归版快速排序的实测

实现三数取中后，我们先在 `ubuntu-asus` 上测试递归版快速排序。正确性测试覆盖了 `std::vector` 和 `std::list`，数据统计统一使用 `std::list<int>`，分别测试升序、逆序、乱序和全相等的输入。两个测试用例均通过。

下表取交换法的一部分输出。比较次数包含三数取中时的比较，最大划分深度只统计真正执行划分的递归层，空区间和单元素区间直接返回。

| 元素个数 | 输入   | 比较次数  | 划分次数 | 最大划分深度 |
| -------- | ------ | --------- | -------- | ------------ |
| 4096     | 升序   | 51,211    | 2,048    | 12           |
| 4096     | 乱序   | 66,620    | 2,336    | 20           |
| 4096     | 逆序   | 2,110,461 | 2,048    | 1,025        |
| 1024     | 全相等 | 528,888   | 1,023    | 1,023        |
| 2048     | 全相等 | 2,106,360 | 2,047    | 2,047        |
| 4096     | 全相等 | 8,407,032 | 4,095    | 4,095        |

先看 4096 个元素的升序和逆序输入。两组都划分了 2048 次，最大深度却分别是 12 和 1025。**划分次数统计整棵递归树做了多少次划分，递归深度看的是其中最长的一条调用链。** 三数取中能让这组逆序输入的第一轮划分接近均衡，后续每轮的基准仍要从各自子区间的三个候选里重新选，划分依旧可能失衡。

全相等的情况更直观。三个候选的值都一样，选谁作基准效果都一样。用目前的交换法、填坑法和同向扫描法，基准每轮都归到当前区间的首位，下一轮只少一个待排序元素。输入规模从 1024 增加到 2048，再增加到 4096，三种写法的最大划分深度都依次达到 1023、2047 和 4095，比较次数每次都接近翻四倍。

### 递归写法的缺点

回到递归代码。每次划分完成后，先递归处理基准左侧，等左侧返回，再处理右侧。只要下层调用还没返回，上层调用就还在等待。图的左边用 7 个元素演示这个调用顺序，右边画出全相等输入下那条不断向下延伸的调用链。



![quick-sort-recursion-depth](https://img.mdwind.online/img/20261123022556675.png)



划分比较均衡时，递归层数随输入规模按对数增长。像全相等这组输入，每轮只归位一个元素，调用链就可能随输入规模线性增长。本次测试正常跑完，实测到的是 **4095 层划分深度**。如果继续增大输入，层层嵌套的函数调用就有可能耗尽线程的调用栈。















```c
int middle_of_three(pSortData pArray, int left, int right)
{
	int mid = (left + right) / 2;
	if (compare(pArray[left], pArray[mid]))
	{
		if (compare(pArray[mid], pArray[right]))
		{
			return mid;
		}
		else
		{
			if (compare(pArray[left], pArray[right]))
			{
				return right;
			}
			else
				return left;
		}
	}
	else
	{
		if (compare(pArray[right], pArray[mid]))
		{
			return mid;
		}
		else
		{
			if (compare(pArray[left], pArray[right]))
			{
				return left;
			}
			else
				return right;
		}
	}
}
```

为了观察三数选中的效果，我们先修改一下数组构建函数

```c
pSortData BulidArray(int Size)
{
	pSortData pArray = (pSortData)malloc(sizeof(SortData) * Size);
	if (pArray == NULL)
	{
		perror("BulidArray malloc fail");
		return NULL;
	}
	int circuit = 0;
	for (; circuit < Size; circuit++)
	{
		pArray[circuit] = circuit;
	}
	return pArray;
}
```

现在单次排序没有三数选中，让我们看看效率：

```c
PerformanceTesting(100000, Quick_sort)

int main()
{	
	test_Quick_sort();
	return 0;
}
```

![image-20240908200824256](https://img.mdwind.online/md/202409082008593.png)

看样子是函数栈帧层数过多，栈溢出了。

换一下，

```c
PerformanceTesting(3000, Quick_sort)

int main()
{	
	test_Quick_sort();
	return 0;
}
```

![image-20240908203743047](https://img.mdwind.online/md/202409082037232.png)

现在加上三数选中，再来一次。

![image-20240908203850427](https://img.mdwind.online/md/202409082038544.png)

差别不是很明显，这应该是我电脑性能不行，参数设大一些就栈溢出了，理论上来说，参数越大，差别就应该越明显。等会以非递归实现快排之后，再试一试。

------

刚刚我们就看到了递归的缺点，当递归过深后，就容易出现栈溢出，所以接下来我们要以非递归的方式实现快速排序。



快排不怎么在意顺序, 所以无论是深度优先搜索 `dfs` 或者说是广度优先搜索 `bfs`, 都是可以的, 不过, 采用 `dfs` 更加合适, 毕竟我们采用非递归方式实现快排, 主要是为了防止递归过程中调用链过长的问题. 不过这里是排序算法专题, 所以我不会再深度讨论 `bfs` 和 `dfs` 了



其中用到的数据结构, stack queue 都还没说, 所以实在不行, 你跳过非递归, 之后说完再看也是可以的.



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



这里我们用的是 `pair`, 也就是一对来存储区间迭代器, emplace 用的是完美转发, 那是之后的知识了, 现在只需要认为, `emplace` 可以以更简便, 更灵活的方式进行 `push`



















先让我们想一想当初为什么偏要用递归的方式去实现快排。其实很简单，就是利用递归把函数栈帧以树状的形式组织起来，然后用单轮排序返回的下标值把它们联系起来。

还是回到霍尔法，以动图中的数组[  6,1,2,7,9,3,4,7,10,8 ]为例。图中，蓝色文本数字表示数组下标，蓝红色序列号表示先后顺序。

![1e7d0fb3335ddd78a1de96e9b07f68d3](https://img.mdwind.online/md/202409091954265.png)

从这张图中，我们可以看到，下标数据遵循着“先进后出”的性质，哪种数据结构有“先进后出”的性质呢？那就是栈。注意这里说的“栈”是数据结构的栈，而不是内存的那个栈。我们自己开辟的栈是建立在内存的堆上的，堆的大小远大于栈（内存），所以就不会像递归那么容易出现栈溢出。

```c
void Quick_sort_NonR(pSortData pArray, int Size)
{
	PST pStack = STInit();
	STPush(pStack, Size - 1);
	STPush(pStack, 0);
	while (!STEmpty(pStack))
	{
		int left = STPop(pStack);
		int right = STPop(pStack);
		int key = Hoare_mode(pArray, left, right);
		if (key + 1 < right)
		{
			STPush(pStack, right);
			STPush(pStack, key + 1);
		}
		if (left < key - 1)
		{
			STPush(pStack, key - 1);
			STPush(pStack, left);
		}
	}
	STDestroy(pStack);
}
```

注：栈的相关文件请参考《栈和队列》。

```c
PerformanceTesting(100000, Quick_sort_NonR)

int main()
{	
	test_Quick_sort_NonR();
	return 0;
}
```

![image-20240909205856952](https://img.mdwind.online/md/202409092058124.png)

看，即使是这样大的数据个数也不会栈溢出。

好的，上面的是带有三数选中的，让我们先把数组构造函数换成最坏情况的那种，然后再对比一下三数选中有无的效果。

```c
PerformanceTesting(10000000, Quick_sort_NonR)

int main()
{	
	test_Quick_sort_NonR();
	return 0;
}
```

含有三数选中时的结果：

![image-20240909213236764](https://img.mdwind.online/md/202409092132023.png)

现在我们把三数选中去掉，为了节约时间，就不打印了。

好的，最起码运行了15分钟，然后我受不了了，关掉了。

除了栈之外，队列也可以实现快速排序的非递归版本，只不过此时它的遍历次序已经和递归完全不同了。此时它应该先把0,9压入队列，再弹出0,9；随后压入0,4和6,9；然后弹出0,4；压入0,1和3,4；然后弹出6,9，压入6,7和9······也就是说，它是层序遍历树的。这里就不详细说了。

------

在某些极端情况下，上述三种的快速排序可能会全部失效。什么情况呢？那就是整个数组的所有成员的数值都相同。此时，比如说，`right`就会去寻找比基准值小的数，可是，很明显，它找不到，于是它就越界了。

为此，就有了“三路划分”。三路划分和以往的三套方法相比，有些根本上的不同。三路划分不像上述三套方法一样，对等于基准值的数值视而不见，而是想办法，把这些数值移到中间。于是在经过一轮排序之后，数组就可以被分成三个部分：左边的部分，存放着比基准值小的数值；中间的部分，存放着和基准值相同的数值；右边的部分，存放着比基准值大的值。



























### 三路划分





**三路划分演示**

以 `[6, 2, 6, 9, 3, 6, 8, 4]` 为例，观察 `9` 被换到右侧后，`scan` 为什么要留在原地判断换回来的 `4`，以及最后如何让基准与另外两个 `6` 连成等价区间 `[3, 6)`。

<video controls preload="metadata" width="720" src="https://img.mdwind.online/img/20261123041047790.mp4"></video>

https://github.com/user-attachments/assets/4e5ce78e-27ba-4e31-9dcb-318caee7d08c





三路划分是针对存在与基准值相同的元素所做的一种优化。以升序为例，我们希望一轮划分结束后，左边全是小于基准值的元素，中间全是与基准值相等的元素，右边全是大于基准值的元素。这样，接下来就可以跳过中间这段区间，只对左右两侧继续排序。

实际操作时，我们仍然用第一个元素作为基准值，让它在扫描过程中留在 `first`。对剩下的区间，我们用三个迭代器来处理。`scan` 指向当前要判断的元素，`before_end` 是小值区的尾后位置，也是相等区间的起点，`after_begin` 则是大值区的起点。扫描过程中，`[before_end, scan)` 里的元素都与基准值相等。如果这个区间为空，`before_end` 就和 `scan` 重合。

当 `scan` 指向的元素**小于基准值**时，就把它和 `before_end` 所指的元素交换。两者分开时，从 `before_end` 换回来的值已经知道与基准值相等，所以 `scan` 可以直接向后走一步。与此同时，`before_end` 的位置刚刚放进了一个小于基准值的元素，它也要向后走一步，重新指向相等区间的起点。如果两者本来就重合，省去交换，两者照样一起向后走。

当 `scan` 指向的元素**大于基准值**时，就把它放到右边。`after_begin` 指向的是大值区已有的起点，所以要先向前退一步，再和 `scan` 所指的元素交换。这里 `scan` 要留在原地，因为从右侧换回来的元素还不知道有多大，下一轮还要判断它。如果 `after_begin` 退完恰好与 `scan` 重合，当前元素已经在该放的位置上，省去交换即可。

如果两个方向的比较都不成立，在比较器满足严格弱序的前提下，当前元素就与基准值等价。这时只让 `scan` 向后走一步，`before_end` 留在原地，中间的相等区间就增加了一个元素。

当 `scan` 和 `after_begin` 相遇时，剩余区间已经扫描完了，但基准值还留在首位。为了让它和中间的相等区间接起来，我们从 `before_end` 往回退一步。如果小值区有元素，这一步就落到小值区的最后一个元素上，把它和首元素交换，基准值便归入中间区间。如果小值区为空，退一步刚好回到 `first`，基准值已经在该在的位置上。最后返回相等区间的两个边界 `[equal_first, after_begin)`，外层就可以据此取出左右两个区间继续排序。







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











































































































在三路划分中，将会有三个指针：`left right curr`。`left`和`right`的初始位置仍然在数组两端，依旧把数组首元素视为基准值，`curr`最开始将会位于第二个成员处。之后`curr`将会对数组成员进行遍历，对于小于基准值的成员，将会与`left`指向的成员进行数值交换，这样做有两个目的：一是把比基准值小的数移到左边，二是把比基准值相同的数值往中间移；在进行完数值交换之后，`left`和`curr`都会向下移动一位；对于等于基准值的数，`curr`会直接移到下一位，将这些与基准值相同的成员交给`left`日后处理；如果成员大于基准值，`curr`指向的成员就会与`right`指向的成员进行数值交换，这样比基准值大的数值就被移到了右边，不过，由于不知道从`right`那边移过来的数值到底是什么情况，所以`curr`不会向后移一位，当然`right`确实会向前移一位；当`curr`到达`right`的右边时，就意味着，整个数组的全部成员都已经被`curr`遍历，比较过了，于是，这轮比较就结束了。

为了方便起见，下面的动图没有考虑三数取中。

![动画](https://img.mdwind.online/md/202409122026105.gif)

```c
static void _Quick_sort_root_particularly(pSortData pArray, int left, int right)
{
	if (left >= right)
		return;

	SortData key = pArray[left];
	int begin = left;
	int current = begin + 1;
	int end = right;
	while (current <= end)
	{
		if (pArray[current] < key)
		{
			Swap(&(pArray[begin++]), &(pArray[current++]));
		}
		else if (pArray[current] == key)
		{
			current++;
		}
		else if (pArray[current] > key)
		{
			Swap(&(pArray[end--]), &(pArray[current]));
		}
	}

	_Quick_sort_root_particularly(pArray, left, begin - 1);
	_Quick_sort_root_particularly(pArray, end + 1, right);
}

void Quick_sort_particularly(pSortData pArray, int Size)
{
	_Quick_sort_root_particularly(pArray, 0, Size - 1);
}
```

```c
PerformanceTesting(10, Quick_sort_particularly)

int main()
{	
	test_Quick_sort_particularly();
	return 0;
}
```

当然，可以看到，我们之前写的比较函数还不够好，应该用整型或者其它类型，布尔值只有两个选项，而大小有三种可能：大于，小于，等于。应该用整型，大于0的代表大于，等于0的代表等于，小于0的代表小于。比较函数的缺陷之后我们还会再说。

![image-20240913085445779](https://img.mdwind.online/md/202409130854063.png)

一般来说，这种级别的快排就没有什么问题了。但在某些在线编程测试平台上，即使是这种级别的快排依旧无法通过，无法通过的原因是因为上面的代码没有三数选中，所以效率有些低；但是，即使加上之前那三个方法的三数选中，依旧无法通过，因为，快排被这个平台恶意针对了，它的测试用例恰好是左中右就是极值，所以让三数选中失效了。

不过，我们也有对策。解决方案是不把选中数组中间的成员作为三数中中间的那个数，而是从选中数组中随机找一个成员作为中间的值。

```c
int middle_of_three(pSortData pArray, int left, int right)
{
	srand((unsigned int)time(NULL));
	int mid = left + (rand() % (right - left));
	if (compare(pArray[left], pArray[mid]))
	{
		if (compare(pArray[mid], pArray[right]))
		{
			return mid;
		}
		else
		{
			if (compare(pArray[left], pArray[right]))
			{
				return right;
			}
			else
				return left;
		}
	}
	else
	{
		if (compare(pArray[right], pArray[mid]))
		{
			return mid;
		}
		else
		{
			if (compare(pArray[left], pArray[right]))
			{
				return left;
			}
			else
				return right;
		}
	}
}
```

不过日常情况下用不着使用这种级别的快排，上面三种就够用了，当然，更可以直接使用标准库里的快排。

### 归并排序









**归并排序演示（递归交换版）**

以 `[4, 2A, 3, 1, 2B]` 为例，观察区间如何在递归过程中不断拆分，以及如何在回溯过程中复用同一片暂存空间完成归并。同时观察相等元素 `2A` 和 `2B` 的相对次序，体会归并排序的稳定性。

<video controls preload="metadata" width="720" src="https://img.mdwind.online/img/20261125141841265.mp4"></video>

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



由于 `std::vector::resize` 用的是无参默认构造, 所以在外层接口我们用概念强调了一下, 要求支持默认无参构造. 除此之外, 在求中点的时候还需要注意一下 mid 的求法, 这里是不可以加一的, 否则对于两个元素, 前面两个区间就是 [0, 2), 后面就是空的, 这会导致区间长度不能缩小, 一直重复调用, 导致栈溢出.



归并排序的核心思想很简单，就是如何将两个已经有序的序列合并成一个更大的有序序列。

当然，我们首先需要解决一个问题，这两个有序序列从哪里来？其实也很简单。对于任意一个待排序区间，我们可以不断地将其从中间划分为两个子区间，并采用深度优先的方式递归处理，直到区间中只有一个元素，或者区间为空(但实际上中途不能为空, 那意味着中间有个划分区间长度始终不缩小)。这样的区间自然可以视为有序区间。

随后，随着递归逐层返回，我们将两个已经有序的子区间进行归并，使其形成一个更大的有序区间，再将其交给上一层继续归并，直至整个序列有序。

因此，**区间的划分发生在递归深入的过程中，而真正的排序发生在递归回溯的过程中。** 这也体现了归并排序的分治思想。

从宏观上看，区间划分只是为归并创造条件，归并才是整个算法的核心操作。





### 归并排序的末端优化

归并排序的递归写法还有一些可以优化的地方。

我们知道，递归调用可以从逻辑上组织成一棵树，每个节点对应一次函数调用。当归并排序输入的数据量较大时，这棵树就会产生大量细小的分支，而这些分支所对应的区间长度实际上已经很小了，没必要让它们一直划分到只有一个元素为止。

于是，我们就可以设计一种机制，当区间长度小到一定程度时，直接调用其他排序算法将其排好序，使其能够参与后续的归并过程。

这种优化的意义，还可以从递归树的结构上来看。

假设归并排序的递归调用树恰好是一棵高度为 \(H\)（共 \(H\) 层）的满二叉树，那么整棵树的节点总数为：

\[ 2^H-1 \]

其中，最后一层的节点数为 \(2^{H-1}\)，倒数第二层的节点数为 \(2^{H-2}\)。

| 递归层次   | 节点数      | 约占总节点数 |
| ---------- | ----------- | ------------ |
| 最后一层   | \(2^{H-1}\) | 50%          |
| 倒数第二层 | \(2^{H-2}\) | 25%          |
| 倒数第三层 | \(2^{H-3}\) | 12.5%        |

可以看到，递归树越往下，每层所包含的节点就越多。因此，**尽管末端优化只减少了一两层递归深度，却能够省去大量的递归调用和小区间归并操作。**

那么，到底该选择什么排序算法呢？

这里我选择的是直接插入排序。毕竟这些待处理区间已经很小了，直接插入排序的实现简单，额外开销也小。另外，前面实现的直接插入排序是一种稳定的排序算法，因此也能够保留归并排序原有的稳定性。















接下来我们把末端优化和非递归一块写了



```cpp
template <std::random_access_iterator It, class Compare>
    requires std::indirectly_swappable<It, typename std::vector<std::iter_value_t<It>>::iterator>
void _merge_sort(It first, It last, std::vector<std::iter_value_t<It>>& tmp, const Compare& cmp) {
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



对于归并排序的非递归写法，我们其实没有必要像快速排序那样，借助一个显式的栈来模拟递归过程。

我们回顾一下归并排序的递归逻辑：递归的目的，是不断划分区间，直到得到一些已经有序的小区间，随后再自底向上地逐步归并。既然我们最终需要的是这些有序的小区间，那么为什么不直接从这些小区间开始呢？

我们先将整个待排序区间按照长度为 10 进行分组，并借助插入排序使各组内部有序。接下来，将相邻的两个有序区间两两归并。每完成一轮归并，有序区间的标准长度就会变为原来的两倍，而有序区间的数目则会减半（向上取整）。如果某一轮的区间数目为奇数，那么最后一个区间就不参与本轮归并，留到下一轮再进行处理。如此反复，直到整个待排序区间只剩下一个有序区间，排序也就完成了。

如果从递归树的角度来看，递归写法是先自顶向下地划分，再自底向上地归并；而非递归写法则是直接从树的底部开始，逐层向上归并，省去了向下划分以及相应的函数调用过程。



当然这里有些小细节, 比如有的要用向上取整的除法, 有的用向下取整的除法



![bottom-up-merge-sort](https://img.mdwind.online/img/20261125165713983.png)









除此之外，非递归归并排序还可以采用逐层写回的方式。它与上述代码的核心思想完全相同，区别仅在于写回原区间的时机：上述代码每完成一对有序区间的归并，就立即将结果写回原区间；而逐层写回则是让暂存区的写入迭代器持续向后移动，直到本轮所有区间归并完毕，再统一将结果写回原区间。需要注意的是，如果某一轮的有序区间数为奇数，那么最后一个未参与归并的区间也需要被转移到暂存区中。这两种写法在时间复杂度和空间复杂度上没有区别，因此这里就不再单独实现了。









归并排序使用的仍是分治的思想，它先将整个数组分成若干个子数组，然后再将这些子数组作进一步的拆分，直到拆分出的子数组一定是有序的。什么叫“一定有序”，很简单，拆的只剩一个成员它不就自然有序了。比如，对于一个有10个成员的数组来说，它先把这10个数组拆分成2个大小为5的子数组，下标分别是0到4, 5到9；然后再进一步拆分，拆成4个数组，下标分别是0到2, 3到4，5到7, 8到9,；随后再拆分，变成下标为0到1， 1到2， 3, 4， 5到6,  6到7, 8, 9········

拆成1个成员怎么办呢？比如现在已经有两个已经“被迫”（就一个成员吗）有序的数组了，第一个数组，有一个成员，是4；第二个数组，是1,；归并归并，就是归档，合并；于是我们先把这两个数组的首元素比较一下，我们发现，1是更小的，于是就把1拷贝到一个暂时的空间，然后第二个数组遍历完了，于是就把第一个数组剩下的部分，也就是那个6，拷贝到暂存空间中，然后再拷贝回去，这样，原数组的这两个子数组合并完了，于是，此时原数组的那个地方就变成了1,6；好的，现在已经有两个数组，这两个数组都有两个成员，第一个数组是1,6；第二个数组是3,8；然后呢，我们把这两个数组的首元素比较一下，我们发现，1更小是吧，就把1拷贝到暂存空间中，然后对比一下，第一个数组的第二成员和第二个数组的第一个成员，我们发现3更小，是吧，那就把3拷贝到暂存空间，然后再比较一下第一个数组和第二个成员的第二成员，我们发现6更小，于是拷贝到暂存空间，然后第一个数组没成员了，于是就把第二个数组的剩下部分再拷贝到暂存空间，此时暂存空间的这个地方就是1,3,6,8了，再把这地方拷贝会原数组的地方就行了。

![动画](https://img.mdwind.online/md/202409111041977.gif)

因为某些不可抗拒因素，可能有些帧没有被成功录入。

```c
void _Merge_sort_root(pSortData pArray, int left, int right, pSortData p_Temporary_Storage)
{
	if (left >= right)
		return;
	int mid = (left + right) / 2;
	_Merge_sort_root(pArray, left, mid, p_Temporary_Storage);
	_Merge_sort_root(pArray, mid + 1, right, p_Temporary_Storage);
	int begin1 = left, end1 = mid;
	int begin2 = mid + 1, end2 = right;
	int begin = left;
	while (begin1 <= end1 && begin2 <= end2)
	{
		if (compare(pArray[begin1], pArray[begin2]))
		{
			p_Temporary_Storage[begin++] = pArray[begin2++];
		}
		else
		{
			p_Temporary_Storage[begin++] = pArray[begin1++];
		}
	}
	while (begin1 <= end1)
	{
		p_Temporary_Storage[begin++] = pArray[begin1++];
	}
	while (begin2 <= end2)
	{
		p_Temporary_Storage[begin++] = pArray[begin2++];
	}
	memcpy(pArray + left, p_Temporary_Storage + left, sizeof(SortData) * (right - left + 1));
}

void Merge_sort(pSortData pArray, int Size)
{
	pSortData pTS = (pSortData)malloc(sizeof(SortData) * Size);
	if (pTS == NULL)
	{
		perror("Merge_sort pTS fail");
		return; 
	}
	_Merge_sort_root(pArray, 0, Size - 1, pTS);
	free(pTS);
}
```

```c
PerformanceTesting(10, Merge_sort)

int main()
{	
	test_Merge_sort();
	return 0;
}
```

![image-20240911104406653](https://img.mdwind.online/md/202409111044774.png)

归并排序的递归写法还有一些地方可以再优化优化。我们知道，递归其实就是把函数栈帧以树的形式组织起来。当归并排序输入的数据量过大时，这棵树就会有太多的细小分支，这些细小分支中的数组个数都很小，没必要让它再继续分支下去。于是我们就可以设计一种机制，当数组的成员个数小到一定程度时，调用其他排序算法对这个小数组进行排序，这样的话，这个小数组其实也算是被迫有序了，就可以参与到后续的合并过程中。而且由于树结构的特点，比如，现在假设归并排序的递归版本所运行的栈帧树就是一棵标准的满二叉树，这样的话，每个栈帧都可以被视为一个节点；此时，这棵树一共有$2^H-1$个节点，最后一层的节点数就是$2^{H - 1}$,倒数第二层就是$2^{H - 2}$,也就是说，最后一层大概占总结点数的50%，倒数第二层大概占总结点数的25.5%；而末端优化优化的正是这些更深处的层，于是，归并排序的总递归次数就少了不小。

那到底该选择什么排序呢？我这里用的是插入排序，毕竟这里要排的数组只是一个小数组罢了，用不着快排，堆排，希尔之类，再加上插入排序并不会破坏归并排序的稳定性（后面会说的），所以，还是用它。

具体改起来很简单

```c
void _Merge_sort_root(pSortData pArray, int left, int right, pSortData p_Temporary_Storage)
{
	if (left >= right)
		return;
	if (right - left + 1 < 10)
	{
		Insert_sort(pArray + left, right - left + 1);
		return;
	}
	int mid = (left + right) / 2;
	_Merge_sort_root(pArray, left, mid, p_Temporary_Storage);
	_Merge_sort_root(pArray, mid + 1, right, p_Temporary_Storage);
	int begin1 = left, end1 = mid;
	int begin2 = mid + 1, end2 = right;
	int begin = left;
	while (begin1 <= end1 && begin2 <= end2)
	{
		if (compare(pArray[begin1], pArray[begin2]))
		{
			p_Temporary_Storage[begin++] = pArray[begin2++];
		}
		else
		{
			p_Temporary_Storage[begin++] = pArray[begin1++];
		}
	}
	while (begin1 <= end1)
	{
		p_Temporary_Storage[begin++] = pArray[begin1++];
	}
	while (begin2 <= end2)
	{
		p_Temporary_Storage[begin++] = pArray[begin2++];
	}
	memcpy(pArray + left, p_Temporary_Storage + left, sizeof(SortData) * (right - left + 1));
}
```

![image-20240912190529299](https://img.mdwind.online/md/202409121905605.png)

-----

接下来我们说一说归并排序的非递归。

上面我们说过，当数组只有一个成员时，它就自然而言地有序了，所以我们就先把数组中的相邻成员直接两两分组，每组排一下，然后每小组（两个成员）就有序了，然后，再把相邻的两个小组进行合并，以此类推，当然，可以预见到，这种方法肯定会有很多越界错误，所以我们要做的，就是把这些错误找出来，针对这些错误，对代码进行不断优化。

```c
void Merge_sort_NonR(pSortData pArray, int Size)
{
	pSortData pTS = (pSortData)malloc(sizeof(SortData) * Size);
	if (pTS == NULL)
	{
		perror("Merge_sort pTS fail");
		return;
	}
	int gap;
	for (gap = 1; gap < Size; gap *= 2)
	{
		// The variable “begin” changes itself when it is written to the staging array, 
		// eliminating the need to manually control the iteration.
		int begin = 0;
		while (begin < Size)
		{
			// The variable “start” is used to control the starting position of the data copy.
			int start = begin;
			int begin1 = begin, end1 = begin1 + gap - 1;
			int begin2 = end1 + 1, end2 = begin2 + gap - 1;

			// The three conditional statements along with 
			// the outer loop condition prevent the variable from going out of bounds.
			if (end1 >= Size)
			{
				end1 = Size - 1;
				end2 = Size - 1;
				begin2 = end2 + 1;
			}
			if (begin2 >= Size)
			{
				end2 = Size - 1;
				begin2 = end2 + 1;
			}
			if (end2 >= Size)
			{
				end2 = Size - 1;
			}


			while (begin1 <= end1 && begin2 <= end2)
			{
				if (compare(pArray[begin1], pArray[begin2]))
				{
					pTS[begin++] = pArray[begin2++];
				}
				else
				{
					pTS[begin++] = pArray[begin1++];
				}
			}
			while (begin1 <= end1)
			{
				pTS[begin++] = pArray[begin1++];
			}
			while (begin2 <= end2)
			{
				pTS[begin++] = pArray[begin2++];
			}
			memcpy(pArray + start, pTS + start, sizeof(SortData) * (end2 - start + 1));
		}
	}
	free(pTS);
}
```

其中，条件语句的下标调整故意使得`begin2`>`end2`从而不进入下面的第一个循环。

```c
PerformanceTesting(10, Merge_sort_NonR)

int main()
{	
	test_Merge_sort_NonR();
	return 0;
}
```

![image-20240912092136769](https://img.mdwind.online/md/202409120921111.png)

还有一种方法实现归并排序的非递归，与上面的思想大致相同，主要区别是，这种写法的是一层一层地覆写回原数组的，而上面的写法是一对一对地覆写回原数组了。

为什么说是“一层一层”呢？这是从归并排序的递归角度来说的，很明显，在递归过程中，函数栈帧就像一棵树一样展开，这棵树的每一层都是把数组分成间隔不同的子数组，然后再逐个排序；

```c
void Merge_sort_NonR1(pSortData pArray, int Size)
{
	pSortData pTS = (pSortData)malloc(sizeof(SortData) * Size);
	if (pTS == NULL)
	{
		perror("Merge_sort pTS fail");
		return;
	}
	int gap;
	for (gap = 1; gap < Size; gap *= 2)
	{
		int begin = 0;
		while (begin < Size)
		{
			int begin1 = begin, end1 = begin1 + gap - 1;
			int begin2 = end1 + 1, end2 = begin2 + gap - 1;

			
			if (end1 >= Size)
			{
				end1 = Size - 1;
				end2 = Size - 1;
				begin2 = end2 + 1;
			}
			if (begin2 >= Size)
			{
				end2 = Size - 1;
				begin2 = end2 + 1;
			}
			if (end2 >= Size)
			{
				end2 = Size - 1;
			}


			while (begin1 <= end1 && begin2 <= end2)
			{
				if (compare(pArray[begin1], pArray[begin2]))
				{
					pTS[begin++] = pArray[begin2++];
				}
				else
				{
					pTS[begin++] = pArray[begin1++];
				}
			}
			while (begin1 <= end1)
			{
				pTS[begin++] = pArray[begin1++];
			}
			while (begin2 <= end2)
			{
				pTS[begin++] = pArray[begin2++];
			}
		}
		memcpy(pArray, pTS, sizeof(SortData) * Size);
	}
	free(pTS);
}
```

差不多，这两种的关键都是控制下标不要越界。

```c
PerformanceTesting(10, Merge_sort_NonR1)

int main()
{	
	test_Merge_sort_NonR1();
	return 0;
}
```

![image-20240912094039704](https://img.mdwind.online/md/202409120940795.png)

## 内排序和外排序

之前我们在堆的章节说过，当数据量过大时，就无法将全部数据一次性压入内存。上面我们说的排序代码都是内排序，接下来我们将会学习外排序。所谓内排序就是在内存中对数据进行排序，外排序就是在外存（主要是硬盘）中对数据进行排序。

那外排序到底怎么排的呢？实际上，我们用的仍然是归并排序的思想，所以我在上文说，“排序代码”而不是“排序”；它的思想是把大文件分成一个个小文件，小到其中的数据已经放得下内存里了，然后，使用内排序对这些数据进行排序，然后再写回到文件的原位置处，之后以文件访问的方式打开这些子文件，使用文件指针对其中的成员逐个访问，依次类推。

由于时间关系，在此我们先只说思想。

## 非比较排序

上面我们说的排序都是比较排序，接下来我们说一说非比较排序，这种排序在日常生活中基本不会用到，主要是了解一下。

非比较排序分为基数排序和计数排序。基数排序用的就是学前班数学的思路：有两个数，怎么比较大小？先看一下，它们的位数都一样的，那就比一下最高位，谁最高位大谁就大，一样就比较下一位，它真的没什么用。

计数排序虽然在日常生活中也不会用到，但它具有很深的教育启蒙意义，往深了说，它是对哈希直接定址法的变形应用，这是C++里的，我就不深入讲了。

计数排序具体怎么做呢？

它首先会将要排序的数组遍历一遍，从而确定要排序数据的大致范围，然后依据这个范围开辟一个数组，接着再次遍历排序数组，对这些数据进行计数，遍历完后，对开辟数组的计数进行展开，就能得到有序数组，好吧，还是看动图吧。



以后我们会说哈希的, 所以现在就不说了.

  ![动画](https://img.mdwind.online/md/202409131459388.gif)

绝对映射就是1就对应下标1,2就对应下标2,3就对应下标3,100000就对应100000那种。如果这样映射，就要建13个成员的数组了。

```c
void count_sort(int* pArray, int Size)
{
	int min = pArray[0], max = pArray[0];
	int current;
	for (current = 0; current < Size; current++)
	{
		if (min > pArray[current])
		{
			min = pArray[current];
		}
		if (max < pArray[current])
		{
			max = pArray[current];
		}
	}
	int temSize = max - min + 1;
	int* p_tem = (int*)calloc(temSize, sizeof(int));
	if (p_tem == NULL)
	{
		perror("count_sort malloc fail");
		return;
	}
	for (current = 0; current < Size; current++)
	{
		p_tem[pArray[current] - min]++;
	}
	int i = 0;
	for (current = 0; current < temSize; current++)
	{
		while (p_tem[current])
		{
			pArray[i++] = current + min;
			p_tem[current]--;
		}
	}
	free(p_tem);
}
```

```c
int main()
{
	int arr[] = { 4,7,15,6,7,8,9,5,6,15,13 };
	int sz = sizeof(arr) / sizeof(arr[0]);
	count_sort(arr, sz);
	int i;
	for (i = 0; i < sz; i++)
	{
		printf("%d ",arr[i]);
	}
	printf("\n");
	return 0;
}
```

很明显，计数排序很受数组数据范围的影响，所以不能使用通用测试模块，另外，你可能注意到，计数排序的数据类型用的全是原生类型，因为计数排序只能对整型，或者说整数进行排序，它的数据类型是被定死的。

![image-20240913154406863](https://img.mdwind.online/md/202409131544473.png)

## 稳定性

什么叫稳定性？可能有些人会将稳定性误以为是性能的稳定性，其实不是。在排序过程中，可能会有相同的数值成员，为了方便，我们就认为有两个相同的值，$A_1$和$A_2$，如果在排序之前，$A_1$在$A_2$的前面，排完序后，$A_1$依旧在$A_2$的前面，那这种算法就是稳定的，否则就是不稳定的。

这是有实际应用价值的。描述某个事物，可能要不止一个数据，比如，它可能是个结构体，此时就要进行多次排序，优先级高的先排序，然后对于数值相同的，我们需要进行下一轮排序，此时的参考项就是优先级低一层的。

比如，对于某场考试，它可能由多场科目构成，比如说，有科目ABC，优先级依次降低，我先比一下总分，然后再比一下A科，再比一下B科，接着是C科，此时的排序算法就必须是稳定的才行。

冒泡是稳定的，对于相同的数值，不会进行交换；直接插入排序是稳定的，对于数值相同的项，我们是写在有序区后一位的；希尔排序只能保证子数组的稳定性，但整体稳定性就无法保证了；选择排序我就不分析了，直接举个反例：已知在数组中现有四个数：$A_1 A_2; B_1 B_2$,已知$A>B$，其中$A_1$是数组首元素，$A_2$夹在$B_1$和$A_1$之间；$A_2$在$A_1$之后，为了方便考虑，我们每轮就找一个极值，最小值；现在假设，$B$恰好即使是最小的那个值，于是在第一轮寻找中，$A_1$就会和$B_1$交换位置，这样，$A_1$就会在$A_2$后了，换言之，稳定性被破坏了；堆排序也不稳定，比如，现在要建一个小堆，根节点和左节点数值相同，根节点大于右节点，这样一交换，稳定性就被破坏了；快排不稳定，即使不考虑三数取中，它也是不稳的，当有两个比基准值大的相同值时，就不稳定了；归并，要看具体代码，比如在上面的代码中，如果等于，先写入的确实是`begin1`，所以是稳定的，如果else分支里写的是`begin2`那就不稳了，此时若要稳定，就需要在条件判断里加个等于号，不过由于这里的比较函数设计有缺陷，所以要仿照霍尔排序的那种取反来写。

# 完