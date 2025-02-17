# hash
## Introduction

之前，我们经常会接触到哈希这个词，今天我们就来正式学一下哈希，学习哈希前，我们先要认识一下C++中的两个哈希容器，`unordered_set`和`unordered_map`，由于二者用法相似，我们只大致说一下`unordered_map`的用法。

[`unordered_map`](https://legacy.cplusplus.com/reference/unordered_map/unordered_map/)在用法上和`map`差不多，主要区别是`unordered_map`迭代器是单向的，除此之外，`unordered_map`还多了一些其它种类的接口，比如`Modifiers`，`Buckets`，`Hash policy`，`Observers`等，它们都涉及到哈希底层，纯粹从用法上来说，它们几乎都用不到，所以我们暂且略过。

```cpp
#include<map>
#include<set>
#include<string>
#include<iostream>
#include<unordered_map>
#include<unordered_set>

using namespace std;

int main()
{
	unordered_set<int> s;
	s.insert(3);
	s.insert(1);
	s.insert(5);
	s.insert(3);
	s.insert(8);
	s.insert(2);

	unordered_set<int>::iterator it = s.begin();
	while (it != s.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;

	unordered_map<string, int> count;
	string arr[] = { "苹果", "西瓜", "苹果", "西瓜", "苹果", "苹果", "西瓜",
	"苹果", "香蕉", "苹果", "香蕉" };
	for (const auto& e : arr)
	{
		count[e]++;
	}
	for (const auto& e : count)
	{
		cout << e.first << ":" << e.second << endl;
	}

	return 0;
}
```

从现象上来看，`unordered`系列容器的最大特点就是不有序`unordered`，正如它的名字一样。

![image-20241223090304100](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241223090304342.png)

下面进行性能对比，总体上来说，`unordered`系列容器在查找时的效率较高，特别是在重复元素较多时。

```cpp
void Performance_Comparison()
{
	const size_t N = 10000000;
	vector<int> v(N);
	srand(time(nullptr));  // 最多生成32768个随机数 
	for (size_t i = 0; i < N; i++)
	{
		v.push_back(rand());	 // N较大时 含有较多重复项
		//v.push_back(rand() + i); // 重复项相对少
		//v.push_back(i);          // 没有重复项 但非常有序
	}

	set<int> s;
	size_t begin1 = clock();
	for (auto e : v)
	{
		s.insert(e);
	}
	size_t end1 = clock();


	size_t begin2 = clock();
	for (auto e : v)
	{
		s.find(e);
	}
	size_t end2 = clock();


	size_t size1 = s.size();


	size_t begin3 = clock();
	for (auto e : v)
	{
		s.erase(e);
	}
	size_t end3 = clock();

	cout << "set::" << endl;
	cout << "插入个数" << size1 << endl;
	cout << "插入时间" << end1 - begin1 <<"ms"<< endl;
	cout << "查找时间" << end2 - begin1 <<"ms"<< endl;
	cout << "删除时间" << end3 - begin3 <<"ms"<< endl<<endl;

	unordered_set<int> us;
	size_t begin4 = clock();
	for (auto e : v)
	{
		us.insert(e);
	}
	size_t end4 = clock();


	size_t begin5 = clock();
	for(auto e : v)
	{
		us.find(e);
	}
	size_t end5 = clock();


	size_t size2 = us.size();


	size_t begin6 = clock();
	for (auto e : v)
	{
		us.erase(e);
	}
	size_t end6 = clock();

	cout << "unordered_set::" << endl;
	cout << "插入个数" << size2 << endl;
	cout << "插入时间" << end4 - begin4 << "ms" << endl;
	cout << "查找时间" << end5 - begin5 << "ms" << endl;
	cout << "删除时间" << end6 - begin6 << "ms" << endl;
}
```

![image-20241223095142208](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241223095142918.png)

插入和删除要先依据能否找到元素再分别处理，所以它们也可以从侧面体现查找的效率。

![image-20241223095503825](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241223095504525.png)

![image-20241223095544678](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241223095545056.png)

------------------

接下来我们真正开始系统性的认识哈希这个概念。

哈希的关键，就是将元素本身与容器中的位置映射起来，从而极大地减少查找时容器的比对次数，从而提高查找效率，对于非哈希容器来说，其中存储的元素与容器中的位置关系并不是很强，所以在查找过程中就要进行很多次数的查找。比如哈希表本身是一种关联式容器，我们先拿序列式容器做对比，比如`vector`，`vector`的元素插入位置全凭用户，用户使用尾插就使用尾插，用户使用头插就头插，理论上来说，对于一个特定的元素来说，它可能出现在`vector`的任意位置上，和哈希表关系稍微近一点的`set`和`map`，则是利用了搜索树结构的特殊性质，固定了元素存储的大致位置，所以查找起来稍微快一些，并且`set`和`map`迭代器遍历出的值还可以是有序的，但有些场景，我们其实并不关心元素之间的相对大小关系，而是更关心单个元素内部的映射关系(当然，我说的是`K-V`模型)，能不能牺牲一下有序性让查找效率更上一步呢？所以就有了`unordered`系列容器，`unordered_map`就是实现哈希容器的一种方法，它依据元素本身的值，毕竟计算机里的数据归根结底都是二进制序列，都可以转化成某个数，结合容器本身的状态，为每个元素都映射一个相对唯一的位置，这样，在进行元素查找的时候，就可以依据输入参数的值，直接把大部分的位置排除，因为依据元素值与位置的映射关系，那些位置不可能存储这个元素，仅在一小部分位置进行少量比对即可。

比如，查找[字符串中的第一个唯一字符](https://leetcode.cn/problems/first-unique-character-in-a-string/)，因为字符串是由字母构成的，而题目也说了，字符串中的字母都是小写的，所以可以直接构造大小为`26`的静态数组，`a`就可以映射到`'a'-'a'`，也就是`0`号下标，`b`就可以映射到`'b'-'a'`，`1`号下标......之后再对字符串进行两次遍历，第一次遍历是初始化哈希数组，第二次遍历是去找谁是第一个出现的唯一字符即可。

```cpp
class Solution {
public:
    int firstUniqChar(string s) {
        int Count[26] = {0};
        for (auto ch : s) {
            Count[ch - 'a']++;
        }
        int i = 0;
        for (; i < s.size(); i++) {
            if (Count[s[i] - 'a'] == 1)
                return i;
        }
        return -1;
    }
};
```

虽说这里的静态数组看起来像是`K`模型，但实际上是`K-V`模型，只不过它的映射关系被隐藏在数组下标中，`0`下标代表`a`，`1`下标代表`b`.......下标对应的元素即是该字母出现的个数。

这种元素值到容器特定位置的映射机制被称为绝对映射，绝对映射的特点是值到位置的映射关系是绝对唯一的，不可能存在重复，但这种映射关系是有缺点的，什么缺点呢？在极差很大，而且元素个数很少时，就会出现很大的空间浪费，比如现在有`[2, 5, 3, 99, 33, 99999, 8888, 34]`这几个数，如果按照绝对映射来走的话，就要建立元素个数为`99999 - 2`的数组，其中只有8个位置被真正使用。

为此，就有了一种相对映射机制，比如，还是对于`[2, 5, 3, 99, 33, 99999, 8888, 34]`，我可以建立容量为10的数组，然后可以拿元素的值遇上数组的容量，比如`2%10=2`，那就放在`2`号下标位置，`3%10=3`，那就放在`3`号下标位置，依次类推......不过我这里只是在逻辑上简单说一下，数组的容量大小是和元素个数相关联的，我用容量为`10`的数组放`8`个元素是因为`10`取余好求，实际上不应该为`10`，先不考虑容量大小怎么定，我们先看相对映射的一种问题。

`3%10=3`，`33%10=3`，这两个元素映射到了同一个位置，我们把这种现象成称为“哈希碰撞”或者"哈希冲突"。怎么解决“哈希冲突”呢？当前我们有两种解决方法，这两种方法本质上都是一样的：这里已经有元素了，那换一个没有元素的位置不就行了，找空位置也不能乱找，它必须要和原来应该待的位置有一定联系才行。

有两种大方法,我们先说第一种大方法,稍后实现时也先用第一种大方法,这种方法的名字叫做"开放定址法". 开放定值法又可以向下细分出两种方法，一种叫做“线性探测”：这个位置已经有元素了，那就去找下一个位置，下一个位置也有元素，那就再去下一个位置，如果把原来应该待的位置称为`hashi`，那新位置就是`hashi + n`,  越界的话就重新回到最开始；另一种方法是“二次探测”：它就是跳着找位置，如果原来应该待的位置是`hashi`，那新位置就是`hashi + n^2`，要不要担心没有符合的空位置呢？不用，哈希容器有一个“负载因子”的概念，哈希容器中的有效元素个数不能超过容器容量的百分之六七十，超过就要扩容，怎么扩容呢？那就是再开一个更大的数组，由于新数组的容量较旧数组容量发生了变化，所以不能用原来的映射关系了，必须把原旧数组中的有效元素一个一个重新插入到新数组中，听起来似乎有些低效，但实际上这种扩容是可以被接受的，随着数组的容量越来越大，其扩容的速度就会越来越慢，所以扩容效率可以接受。

线性探测有个缺点，就是它会让元素集中在某个小区域中，而不是分散开来的，这样就会增大哈希冲突的概率，所以就不太好，因为哈希表中的元素是散着放的，所以哈希表也被称为“散列”。我们一步一步来，先使用较为简单的线性探测机制。

## Implementation

对于应用"开放定址法"的哈希表来说,也被称为"闭散列", 关于这个名字的具体含义, 我们先跳过.  闭散列的底层容器是一个动态数组(别的容器不是说不行, 但数组比较好操作).  数组中的元素有所谓"有""无"的概念, 有就是数组`size()`接口所计数的部分,或者说可以使用`operator[]`的那部分, 有+无就是数组`capacity()`接口所计数的部分.

![image-20250103155340798](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250103155340963.png)

我们下面所说的空间都是能被直接操作的空间,也就是"有"的那一部分.

对于"有"的这部分来说,其内部的元素又可以细分出三种状态, 它们分别是  有效状态   删除状态   空状态.   有效状态意味着节点中的数据是有效的,被保护的,不能被破坏, 而对于 删除状态  空状态来说  ,其中的数据是不被保护的, 可以被修改覆写.

乍看起来, 删除状态 和 空状态 好像可以被合并成无效状态  , 但实际上,  它们不能被合并成无效状态, 这是为了给查找做准备, 举个例子  ,现在有一个闭散列 , 其内部的状态是这样的,  其中,白色节点  表示为空状态   绿色节点表示为 有效数据   黑色节点表示  删除数据

![image-20250103161031311](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250103161031360.png)

现在我们删除22,  不用直接删除,毕竟真删除也是要花时间的, 只要把节点的状态置为 空状态即可.

![image-20250103161248704](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250103161248752.png)

现在我们要查找`42`, `42 % 10 == 2`, 2号下标的节点不是42, 所以要向后继续找, 12 也不是, 22被删除了,被删除意味着后面可能还有元素 ,所以要跳过它继续找,32不是,继续,42找到了 .  如果只有两种状态:  有效状态 和 无效状态  , 那很明显  删除就是一种无效状态, 此时若是遇到22, 那该继续找, 还是停止找呢? 停止找的话, 就相当于忽略了后面的节点,  如果继续找  , 那就意味着 无效状态也不继续停止 ,那什么时候停止? 把整个数组遍历完吗? 如果真这样做, 哈希表的查找和普通的数组查找有什么区别呢? 所以状态 必须要有三种,不能被简化为有效和无效这两种. 

从上面的过程中我们也能发现, 数组中的元素除了数值之外, 还要有表示该元素的状态参数,所以,在正式写闭散列之前, 我们要在外部先把节点模版类给实现

```cpp
// 节点的状态
enum State_type
{
	valid,   // 节点有效
	remove,  // 节点中的值被删除
	empty    // 节点为空
};

// 针对K-V模型的元素节点
template<class Key, class Value, class Predicate>
struct Node
{
	typedef Key key_type;
	typedef Value mapped_type;
	typedef std::pair<key_type, mapped_type> value_type;
	typedef Predicate key_equal;
	typedef value_type& reference;
	typedef const value_type& const_reference;


	value_type _value;
	State_type _state;

	Node()
		:_value(value_type())
		, _state(empty)
	{
	}

	// 提取节点状态
	inline State_type& state_of_node()
	{
		return _state;
	}

	inline const State_type& state_of_node()const
	{
		return _state;
	}

	// 提取节点中的值
	inline const_reference value_of_node()const
	{
		return _value;
	}

	// 查询节点关键字
	inline const key_type& key_of_node()const
	{
		return _value.first;
	}
	
    // 将一个节点有效化
	inline void enable(const_reference v)
	{
		_value = v;
		_state = valid;
	}

	// 检查节点是否有效
	inline bool validity()const
	{
		if (_state == valid)
			return true;
		else
			return false;
	}

	// 删除一个节点中的值
	inline void Remove()
	{
		_state = remove;
	}
};
```

后面的一堆内联函数是对一些常用操作的实现, 这些操作很简单, 在后面的实现中,也会比较常见, 所以可以直接写成内联函数的形式, 这样一方面可以让我们少写一些代码, 重要的不是少写一些具体的代码, 重要的是, 这些常用代码的省略可以减小错误概率, 万一敲代码的时候一步留神, 本来想访问这个字段,结果实际写成了另一个字段, 自以为写对了, 那就会很难找,  而且内联函数也能在一定程度上提高代码的可读性,所以对于常用的简短代码来说,写成内联比较好.   当然有可能不知道具体要写那些操作,那就先不写内联函数,等到实现哈希表中具体用到这些操作之后,再返回来写.

可能你对`Node`的第三个模版参数`Predicate`比较困惑, 直译起来是"谓语", 这就涉及到C++中的谓语语句概念, 所谓谓语语句,其实就是仿函数,  这个仿函数一般返回一个布尔值,一般作为一种快速逻辑判断方式,  在此处,  `Predicate`其实就是用来判断关键值是否相等的.

```cpp
template<class T>
    struct equal_to
    {
        bool operator()(const T& k1, const T& k2)
        {
            return k1 == k2;
        }
    };

template<class key, class Value, class Predicate = equal_to<key> >
    class HashTable
    {
        typedef Node<key, Value, Predicate> node_type;      // 哈希表中的基本节点
        typedef std::vector<node_type> table_type;          // 哈希表的底层容器
        typedef size_t size_type;						  // 用来计量有效元素个数
        typedef size_t factor_type;                         // 用来计量负载因子 factor_type%形式 

        typedef typename node_type::value_type value_type;  // 面向用户的基本数据
        typedef typename node_type::const_reference const_reference; 
        typedef typename node_type::key_type key_type;

        typedef HashTable<key, Value, Predicate> self;

        table_type _table;
        size_type _size;
        size_type _max_size;
        factor_type _load;
        factor_type _max_load;


        public:
        HashTable()
            :_table(table_type(10))   // 默认10个可支配节点
                , _size(0)
                , _max_size(_table.size())
                , _load(0)
                , _max_load(70)
            {
            }

        HashTable(size_type num)
            :_table(table_type(num))   // 用户自定义支配节点个数
                , _size(0)
                , _max_size(_table.size())
                , _load(0)
                , _max_load(70)
            {
            }

        // 提取最大负载因子
        inline factor_type& max_load_factor()
        {
            return _max_load;
        }

        // 检查当前负载因子
        inline const factor_type& load_factor()const
        {
            return _load;
        }

        // 计算哈希表中的有效元素个数
        inline size_type size()const
        {
            return _size;
        }

        // 计算当前底层容器中可支配的最大节点个数
        inline size_type max_size()const
        {
            return _table.size();
        }
    };
```

我们先来实现插入, 由于我们现在只是粗略写一下, 没有迭代器, 所以先用`bool`做返回值 , 凑活用

```cpp
bool insert(const_reference v)
{
	// 哈希表中是否已经存在该关键值

	// 检查负载因子
	

	// 插入逻辑
	

	// 更新负载因子
	

	
}
```

查看哈希表中是否已经存在`key`, 是`find`的职能, 我们先跳过. 空间不足时的扩容处理也挺简单,毕竟我们都有一个专门的成员记录负载因子了. 扩容时, 直接新创建一个临时对象, 然后把有效数据插入临时对象, 之后再交换一下即可, 交换之后, 原来的哈希表变成了临时变量,当临时变量的生命周期结束后,就会调用析构函数精细析构 ,具体的析构过程我们也不需要写, `vector`有自己的析构逻辑, 我们不需要自己再写析构函数.

```cpp


void swap(self& that)
{
	std::swap(_table, that._table);
	std::swap(_size, that._size);
	std::swap(_max_size, that._max_size);
	std::swap(_load, that._load);
	std::swap(_max_load, that._max_load);
}

bool insert(const_reference v)
{
	// 哈希表中是否已经存在该关键值
	

	// 检查负载因子
	if (load_factor() > max_load_factor())
	{
		size_type size = max_size();
		self tmp(size*2);
		for (const auto& e : _table)
		{
			if (e.validity())
				tmp.insert(e.value_of_node());
		}

		swap(tmp);
	}

	// 插入逻辑

	// 更新负载因子
	
}
```

插入逻辑也比较好实现,  先找一个可以被覆写的位置, 然后使之有效即可

```cpp
bool insert(const_reference v)
{
	// 哈希表中是否已经存在该关键值

	// 检查负载因子
	if (load_factor() > max_load_factor())
	{
		size_type size = max_size();
		self tmp(size*2);
		for (const auto& e : _table)
		{
			if (e.validity())
				tmp.insert(e.value_of_node());
		}

		swap(tmp);
	}

	// 插入逻辑
	size_type Max_size = max_size();
	size_t position = v.first % Max_size;
	while (_table[position].validity())
	{
		position++;
		position %= Max_size;
	}
	_table[position].enable(v);
	_size++;

	// 更新负载因子
	_load = size() * 100 / Max_size;

	return true;
}
```

现在我们去写`find`, 由于没有迭代器, 所以我们就返回下标`int`, `find`的逻辑和`insert`中的寻址过程有些许相似之处, 

```cpp
inline bool keep_find(const node_type& node)const
{
	if (node.state_of_node() == empty)
		return false;
	else
		return true;
}

int find(const key_type& key)const
{
	size_type Max_size = max_size();
	size_t position = key % Max_size;
	while (keep_find(_table[position]))
	{
		if (_table[position].validity() && _table[position].key_of_node() == key)
			return position;

		position++;
		position %= Max_size;
	}

	return -1;
}
```

  如果循环到空状态了, 那就意为着后面没有了, 所以跳出循环, 返回一个不可能的下标,  如果没跳出循环, 有两种可能, 一是这个节点是删除状态  二是这个节点确实有数据,  如果为删除的话, 就说明就节点内的数据已经不被承认了, 所以要跳过,  我们在这里用逻辑运算的短路性质来实现:: 如果节点是删除状态, 后面条件就不会被执行,也就是说,不会去比了,  如果节点有效, 那再去比, 相当就可以返回了. 

这里特别要注意,逻辑与第一个条件容易漏, 容易错.

最后把`insert`写完

```cpp
bool insert(const_reference v)
{
	// 哈希表中是否已经存在该关键值
	if (find(v.first) != -1)
		return false;

	// 检查负载因子
	if (load_factor() > max_load_factor())
	{
		size_type size = max_size();
		self tmp(size*2);
		for (const auto& e : _table)
		{
			if (e.validity())
				tmp.insert(e.value_of_node());
		}

		swap(tmp);
	}

	// 插入逻辑
	size_type Max_size = max_size();
	size_t position = v.first % Max_size;
	while (_table[position].validity())
	{
		position++;
		position %= Max_size;
	}
	_table[position].enable(v);
	_size++;

	// 更新负载因子
	_load = size() * 100 / Max_size;

	return true;
}
```

删除也很好写

```cpp
bool erase(const key_type& key)
{
	int pos = find(key);
	if (pos != -1)
	{
		_table[pos].Remove();
		_size--;

		_load = size() * 100 / max_size();
		return true;
	}
	else
		return false;
}
```

为了方便看现象,再写写打印吧

```cpp
void print()const
{
	for (size_t i = 0; i < _table.size(); i++)
	{
		std::cout << "[" << i << "]-> ";
		if (_table[i].validity())
			std::cout << _table[i].value_of_node().first;
		std::cout << std::endl;
	}
	std::cout << std::endl;
}
```

稍微测试一下

```cpp
int main()
{
	wind::HashTable<int, int> ht;
	ht.insert(std::make_pair(2, 0));
	ht.insert(std::make_pair(12, 0));
	ht.insert(std::make_pair(22, 0));
	ht.insert(std::make_pair(32, 0));
	ht.insert(std::make_pair(42, 0));
	ht.print();
	return 0;
}
```

![image-20250103172213495](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250103172213653.png)

我们看看把`find`易错点漏掉会发生什么现象.

```cpp
int main()
{
	wind::HashTable<int, int> ht;
	ht.insert(std::make_pair(2, 0));
	ht.insert(std::make_pair(12, 0));
	ht.insert(std::make_pair(22, 0));
	ht.insert(std::make_pair(32, 0));
	ht.insert(std::make_pair(42, 0));
	ht.print();
	ht.erase(32);
	ht.print();
	std::cout << ht.find(32) << endl;
	ht.insert(std::make_pair(32, 0));
	ht.print();
	return 0;
}
```

![image-20250103172701531](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250103172701594.png)

在`32`被删除之后, `find`仍然认为它是有效的, 所以返回了`5`,这也导致后续插入的失败.

把第一个条件加上之后的现象

![image-20250103172948865](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250103172948946.png)

如果`key`是负数怎么办?

也不用担心  此时,`first`为`int`,而`Max_size`是`size_t`会发生整型提升, 于是负数就会被解释成`size_t`, `size_t`没负数,所以最高位会被解释为数值位,得出来的仍旧是整数.

```cpp
size_type Max_size = max_size();
size_t position = v.first % Max_size;
```

```cpp
int main()
{
	std::cout << -1 / size_t(1) << endl;
	return 0;
}
```

![image-20250103173602169](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250103173602244.png)

那要是`key`不能进行取余计算怎么办? 没事, 我们可以再建立一道映射层,  将不能取余的数据转化成可以`size_t`, 只要转换规则是相同的, 同一个数据对应的`size_t`就是相同的,  不过,转换规则也并不是完全没有要求, 要尽可能地减少不同数据映射到同一个`size_t`的概率

我们以`string`为例, 最简单的一种转换方法, 就是直接把字符的ASCII相加, 还是通过仿函数的形式供模版使用. 能转换成`size_t`就转换成`size_t`,不能就自己写,  因为字符串是我们经常涉及到的数据 , 所以可以对其进行模版特例化.

```cpp
//通用哈希值映射模版
template<class T>
struct HashMapper
{
	size_t operator()(const T& v)
	{
		return (size_t)v;
	}
};

//针对字符串类型的模版特例化
template <>
struct HashMapper<std::string>
{
	size_t operator()(const std::string& s)
	{
		size_t hash = 0;
		for (auto e : s)
		{
			hash += e;
		}
		return hash;
	}
};
```

然后对有关部分进行简要修改即可.比如下面这样

![image-20250103184437596](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250103184438062.png)

```cpp
int find(const key_type& key)const
{
	size_type Max_size = max_size();
	size_t hash = hasher()(key);
	size_t position = hash % Max_size;
	while (keep_find(_table[position]))
	{ 
		if (_table[position].validity() && equal()(_table[position].key_of_node(), key))
			return position;

		position++;
		position %= Max_size;
	}

	return -1;
}
```

稍微测试一下

```cpp
int main()
{
	wind::HashTable<std::string, int> ht;
	std::vector<std::string> v{ "apple", "banana", "cherry", "date", "elderberry" };
	for (auto e : v)
	{
		if (ht.find(e) == -1)
			ht.insert(std::make_pair(e, 0));
	}
	ht.print();
	return 0;
}
```

![image-20250103190107137](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250103190107314.png)

也是可行的,不过,对于上面我们所写的转换方法还不够好, 比如对于`adc`和`bea`来说,它们会转化成同一个`size_t`,这就会增大哈希碰撞的概率, 因此我们可以换一种方法,有一种方法就是在加上字符之前,对`hash`乘上一个数,诸如31, 131,  至于为什么是这些数, 就可能涉及到离散数学上面了,反正我不知道,所以我们就直接用了,如果想深入探讨,可以看[这篇文章](http://www.cnblogs.com/-clq/archive/2012/05/31/2528153.html).

```cpp
//针对字符串类型的模版特例化
template <>
struct HashMapper<std::string>
{
	size_t operator()(const std::string& s)
	{
		size_t hash = 0;
		for (auto e : s)
		{
			hash *= 131;
			hash += e;
		}
		return hash;
	}
};
```

对于其它一些类型,来说 ,若要作为`Key`的话, 那可以去从中找些不易冲突的项, 再做些离散处理,  比如加加减减乘除什么的, 实在不行, 可以把类型里的数据转换成字符串,然后复用字符串哈希值映射的仿函数. 

额外说一下, 有人不用模版特例化, 用这种方法

```cpp
template<class T>
    struct HashMapper
    {
        size_t operator()(const T& v)
        {
            return (size_t)v;
        }

        size_t operator()(const std::string& s)
        {
            size_t hash = 0;
            for (auto e : s)
            {
                hash *= 131;
                hash += e;
            }
            return hash;
        }
    };
```

想法或许挺好,  这两个`operator()`构成重载, `T`是`int`就用上面的, `T`是`string`就用下面的,  但实际上,不能这样写, 若`T`是`string`,两个`operator()`的参数就会完全一样, 这就不是重载了,  而是重定义.

---------------------------------

针对"闭散列"我们就不继续写下去了,  实际上,  哈希容器的选址方式大都是另一种方法, 而不是上面的"开放定址法", 下面的这种方法, 一般被称为"拉链法", 或者更形象的方法是"哈希桶",  由这种方法实现的哈希容器, 一般被叫做"开散列".

在开散列中, 原来的动态数组不再存放数据本体,  而是存放节点指针, 节点将以链式结构存储在内存空间中, 动态数组中只有该链式结构的头结点指针, 发生哈希冲突后,就把冲突元素放在同一个链条上,而不去影响别的位置.

![image-20250103193502304](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250103193502576.png)

开散列的空间并不是完全定死的, 而是用链式结构展开来的, 所以称之为"开散列", "闭散列"空间是完全定死的, 数据是以一维形式存储的,所以称之为"闭散列".

开散列也是有负载因子的, 一般情况下, 就是1, 用百分比来表示 就是100%,  比如上面这张图, 动态数组有10个可操作的位置,  一共插入的节点个数是6, 所以负载因子是0.6.   当负载因子为1时, 就相当于节点可以被匀到动态数组上, 可能有些链是空的,  有些链稍微多几个,  这就导致哈希桶的平均哈希冲突概率很低, 因此, 哈希桶的时间复杂度不是最坏情况下的时间复杂度, 而是平均时间复杂度, 哈希桶的时间复杂度平均上来说就是$O(1)$.

当然, 也不能排除某些极端情况,  一个链条上有非常多的节点,  出现这种情况的原因大多数都是因为被刻意针对了,  C++没有对这种情况进行下一步优化, 但Java 听说会把过长的链重构成红黑树结构, 据说, 链条长度超过8个就会重构成红黑树.

下面我们就以上面所说的开散列方式来实现哈希表.

为了和上面的闭散列作区分, 我们把开散列的哈希容器写在另一个命名空间中,  这个哈希容器的名字我们就叫做`HashBucker`, 也就是哈希桶.

相较闭散列来说, 开散列就不需要再枚举状态了, 因为开散列的哈希碰撞只会影响目标位置的链式结构长度, 但不会对其它位置产生影响.  对于链表来说, 节点的有无可以直接通过该节点是否链入链表而获知, 所以不需要有效或者无效这两种状态区分, 并且,  不同位置之间不会相互影响, 比如, 某个`key`映射到了`A`位置, 那直接对`A`位置的链表进行遍历即可, 如果`A`这个位置的链表没有`key`, 那就是没有`key`, 其它位置的链表不可能出现`key`, 所以不需要再把无效状态再细分为空或者删除这两个小状态了.

其它的一些东西, 比如哈希值映射仿函数或者`key`相等仿函数和闭散列是一样的, 直接复制过来即可.

很明显, `HashBucker`中肯定是有链表结构的, 我们下面讨论一下该用什么链表,  链表又该具体怎么实现.     就链表的类型来说, 最简单的不带头单向链表就已经够用了, 一方面,  哈希容器本身就不需要走回头路,  或者说, 它的迭代器就是单向的, 所以如果你用双向链表, 那根本用不上双向, 因为双向反而会影响哈希容器的效率,  所以用单链表就已经够用了, 另一方面, 也不需要有头结点, 哨兵位对于单链表来说意义不大,  反而会增加操作的复杂性, 所以最后我们用的就是单向不带头链表.   `STL`里有单链表, 我们要不要直接拿过来用呢? 当然是可以的, 但在这里我们就自己构建链表, 一方面, 单链表操作上很简单,  另一方便, 我们最后对于开散列是要实现迭代器的,  如果你用标准容器的话,  迭代器的实现就可能怪怪的, 最后,  自己写的当然有更大的灵活度,  可以用来实现别的一些特殊需求.

老样子, 我们先把外面的框架给搭起来.

```cpp
template<class T>
struct equal_to
{
	bool operator()(const T& k1, const T& k2)
	{
		return k1 == k2;
	}
};

//通用哈希值映射模版
template<class T>
struct HashMapper
{
	size_t operator()(const T& v)
	{
		return (size_t)v;
	}
};

//针对字符串类型的模版特例化
template <>
struct HashMapper<std::string>
{
	size_t operator()(const std::string& s)
	{
		size_t hash = 0;
		for (auto e : s)
		{
			hash *= 131;
			hash += e;
		}
		return hash;
	}
};

template<class T>
struct Node
{
	typedef T value_type;
	typedef value_type* pointer;
	typedef value_type& reference;
	typedef Node<value_type> self;
	typedef self* link_type;
	typedef const value_type* const_pointer;
	typedef const value_type& const_reference;

	value_type _value;
	link_type _next;

	Node(const_reference v)
		:_value(v)
		, _next(nullptr)
	{
	}

	inline link_type& __link_of_node()
	{
		return _next;
	}

	inline link_type __next_node()
	{
		return __link_of_node();
	}

	inline const value_type& __value_of_node()
	{
		return _value;
	}
};

template<class key, class Value, class Hash = HashMapper<key>, class Predicate = equal_to<key> >
class HashBucker
{
	typedef key key_type;
	typedef Value mapped_type;
	typedef Hash hasher;
	typedef Predicate key_equal;
	typedef size_t size_type;
	typedef size_t factor_type;
	typedef HashBucker<key, Value, Hash, Predicate> self;

	typedef std::pair<key_type, mapped_type> value_type;
	typedef Node<value_type> node_type;
	typedef typename node_type::pointer pointer;
	typedef typename node_type::reference reference;
	typedef typename node_type::const_pointer const_pointer;
	typedef typename node_type::const_reference const_reference;
	typedef typename node_type::link_type link_type;
	typedef std::vector<link_type> link_table;

	link_table _table;
	size_type _size;
	size_type _max_size;
	factor_type _load;
	factor_type _max_load;

	inline link_type _create_node(const_reference v)const
	{
		link_type p = new node_type(v);
		return p;
	}

	inline void _destroy_node(link_type p)const
	{
		delete p;
	}

	inline const key_type& _key_of_node(link_type p)const
	{
		return p->_value.first;
	}

public:
	HashBucker()
		:_table(link_table(10))   // 默认10个可支配节点
		, _size(0)
		, _max_size(_table.size())
		, _load(0)
		, _max_load(100)
	{
	}

	HashBucker(size_type num)
		:_table(link_table(num))   // 用户自定义支配节点个数
		, _size(0)
		, _max_size(_table.size())
		, _load(0)
		, _max_load(100)
	{
	}

	// 提取最大负载因子
	inline factor_type& max_load_factor()
	{
		return _max_load;
	}

	// 检查当前负载因子
	inline const factor_type& load_factor()const
	{
		return _load;
	}

	// 计算哈希表中的有效元素个数
	inline size_type size()const
	{
		return _size;
	}

	// 计算当前底层容器中可支配的最大节点个数
	inline size_type max_size()const
	{
		return _table.size();
	}

	void swap(self& that)
	{
		std::swap(_table, that._table);
		std::swap(_size, that._size);
		std::swap(_max_size, that._max_size);
		std::swap(_load, that._load);
		std::swap(_max_load, that._max_load);
	}

	bool insert(const_reference v)
	{
		// 哈希表中是否已经存在该关键值
		if (find(v.first))
			return false;

		// 检查负载因子

		// 插入逻辑

		// 更新负载因子
		_load = size() * 100 / Max_size;

		return true;
	}
};
```

我们所使用的链表类型为单链表, 所以很明显头插最简单, 因此我们在插入逻辑使用的就是头插, 和闭散列区别不大, 就是先把`key`转化为某个数, 然后直接算出这个数字映射的位置即可.

```cpp
bool insert(const_reference v)
{
	// 哈希表中是否已经存在该关键值
	if (find(v.first))
		return false;

	// 检查负载因子
    
	// 插入逻辑
	size_type Max_size = max_size();
	size_t hash = hasher()(v.first);
	size_t position = hash % Max_size;
	link_type newNode = _create_node(v);
	newNode->__link_of_node() = _table[position];
	_table[position] = newNode;
	_size++;

	// 更新负载因子
	_load = size() * 100 / Max_size;

	return true;
}
```

对于扩容来说, 我们仍可以使用之前的方案, 直接创建一个临时变量, 然后把有效值往里面插入即可. 不过这样做的话, 可能会产生一些小问题, 比如, 你要把值从节点里面取出来, 然后插入到临时对象中, 尽管我们在`class Node`里面写过相应的内联函数, 但是, 在这里用, 总感觉怪怪的,  首先, 你要把值从节点里取出来, 然后把值插入到临时对象中, 所有节点中的值都插入完毕后, 还要将临时对象和`*this`进行交换, 交换之后, 原来的那些节点就存在了临时对象中, 临时对象析构, 就会把以前的节点给释放了, 但是我为什么要把节点的值提取出来然后再以该值创建一个新节点呢? 我不能直接把原来旧节点拿过来改改指针域直接用吗? 当然是可以的, 下面我们就以这种思路来实现扩容. 另外, 刚刚我们提到析构了吧? 这回析构函数不能靠默认了, 要自己写一下, 把节点都给释放掉

```cpp
~HashBucker()
{
	size_t size = max_size();
	for (size_t i = 0; i < size; i++)
	{
		link_type curr = _table[i];
		while (curr)
		{
			_destroy_node(curr);
			curr = curr->__next_node();
		}
		_table[i] = nullptr;
	}
}
```

扩容的具体内容很简单, 先创建一个指针数组, 把`this`中的各个链表遍历一遍, 直接把节点重新定位插入新数组即可, 最后别忘了把新旧数组进行交换.

```cpp
bool insert(const_reference v)
{
    // 哈希表中是否已经存在该关键值
    if (find(v.first))
        return false;

    // 检查负载因子
    if (load_factor() >= max_load_factor())
    {
        size_type Max_size = max_size() * 2;
        link_table tmp(Max_size);
        hasher h;
        for (size_t i = 0; i < _table.size(); i++)
        {
            link_type curr = _table[i];
            while (curr)
            {
                link_type next = curr->__next_node();
                size_t hash = h(curr->__value_of_node().first);
                size_t position = hash % Max_size;
                curr->__link_of_node() = tmp[position];
                tmp[position] = curr;
                curr = next;
            }
        }
        _table.swap(tmp);
        _max_size = max_size();
    }

    // 插入逻辑
    size_type Max_size = max_size();
    size_t hash = hasher()(v.first);
    size_t position = hash % Max_size;
    link_type newNode = _create_node(v);
    newNode->__link_of_node() = _table[position];
    _table[position] = newNode;
    _size++;

    // 更新负载因子
    _load = size() * 100 / Max_size;

    return true;
}
```

 如果你有强迫症, 可以在旧数组的每格被遍历完后置个空, 就是`_table[i] = nullptr`, 但不加也无伤大雅, `link_type`用的又不是哈希桶的析构函数, 而是`vector`, 不会造成节点二次释放的.

`find`也很好写, 找到位置之后遍历链表即可.  而且因为没有那三个状态, 所以也没有陷阱, 直接写即可. 用指针的原因是方便我们后续没有迭代器场景的测试

```cpp
link_type find(const key_type& key)
{
	size_type Max_size = max_size();
	size_t hash = hasher()(key);
	size_t position = hash % Max_size;
	link_type curr = _table[position];
	key_equal equal;
	while (curr)
	{
		if (equal(curr->__value_of_node().first, key))
			return curr;
		curr = curr->__next_node();
	}

	return nullptr;
}
```

`erase`的思路和`find`类似, 但很明显不能直接用`find`, 单链表节点的删除肯定是要知道上一个节点的, 注意,  这是一个不带头单链表, 可能出现没有上一个节点的情况, 需要进行一些特殊处理.

```cpp
bool erase(const key_type& key)
{
	size_t position = key % max_size();
	link_type curr = _table[position];
	link_type prev = nullptr;
	while (curr)
	{
		if (key_equal()(curr->__value_of_node().first, key))
		{
			if (prev == nullptr)
				_table[position] = nullptr;
			else
				prev->__link_of_node() = curr->__link_of_node();

			_destroy_node(curr);
			return true;
		}

		prev = curr;
		curr = curr->__next_node();
	}

	return false;
}
```

接下来我们对比一下效率, 主要是用`P.J  unordered_map`和我们刚刚写的`HashBucker`

```cpp
void test5()
{
	const size_t N = 1000000;

	vector<int> v(N);               // 初始化为 N 个默认值
	srand(time(nullptr));           // 最多生成 32768 个随机数
	for (size_t i = 0; i < N; i++)
	{
		// v[i] = rand();            // N 较大时含有较多重复项
		v[i] = rand() + i;          // 重复项相对少
		// v[i] = i;                 // 没有重复项但非常有序
	}

	map<int, int> map_set;
	size_t insert_start = clock();
	for (auto key : v)
	{
		map_set.insert(make_pair(key, 0));
	}
	size_t insert_end = clock();

	size_t find_start = clock();
	for (auto key : v)
	{
		map_set.find(key);
	}
	size_t find_end = clock();

	size_t map_set_size = map_set.size();

	size_t erase_start = clock();
	for (auto key : v)
	{
		map_set.erase(key);
	}
	size_t erase_end = clock();

	cout << "set::" << endl;
	cout << "插入个数: " << map_set_size << endl;
	cout << "插入时间: " << insert_end - insert_start << "ms" << endl;
	cout << "查找时间: " << find_end - insert_start << "ms" << endl;
	cout << "删除时间: " << erase_end - erase_start << "ms" << endl << endl;

	unordered_map<int, int> unordered_map;
	size_t um_insert_start = clock();
	for (auto key : v)
	{
		unordered_map.insert(make_pair(key, 0));
	}
	size_t um_insert_end = clock();

	size_t um_find_start = clock();
	for (auto key : v)
	{
		unordered_map.find(key);
	}
	size_t um_find_end = clock();

	size_t um_size = unordered_map.size();
	size_t um_bucket_count = unordered_map.bucket_count();

	size_t max_bucket_size = 0;
	size_t non_empty_buckets_size = 0;
	for (size_t i = 0; i < um_bucket_count; i++)
	{
		size_t bucket_size = unordered_map.bucket_size(i);
		if (bucket_size > 0) non_empty_buckets_size++;
		max_bucket_size = max(max_bucket_size, bucket_size);
	}

	double load_factor = unordered_map.load_factor();
	double max_load_factor = unordered_map.max_load_factor();

	size_t um_erase_start = clock();
	for (auto key : v)
	{
		unordered_map.erase(key);
	}
	size_t um_erase_end = clock();

	cout << "unordered_map::" << endl;
	cout << "尝试插入个数: " << N << endl;
	cout << "当前最大个数: " << um_bucket_count << endl;
	cout << "成功插入个数: " << um_size << endl;
	cout << "整体插入时间: " << um_insert_end - um_insert_start << "ms" << endl;
	cout << "整体查找时间: " << um_find_end - um_find_start << "ms" << endl;
	cout << "整体删除时间: " << um_erase_end - um_erase_start << "ms" << endl;
	cout << "非空链表个数: " << non_empty_buckets_size << endl;
	cout << "最长链表长度: " << max_bucket_size << endl;
	cout << "最大负载因子: " << max_load_factor << endl;
	cout << "负载因子大小: " << load_factor << endl;
	cout << "链表平均长度: " << static_cast<double>(um_size) / static_cast<double>(non_empty_buckets_size) << endl;
	cout << endl;

	whisper::HashBucker<int, int> custom_hash;
	size_t hash_insert_start = clock();
	for (auto key : v)
	{
		custom_hash.insert(make_pair(key, 0));
	}
	size_t hash_insert_end = clock();

	size_t hash_find_start = clock();
	for (auto key : v)
	{
		custom_hash.find(key);
	}
	size_t hash_find_end = clock();

	size_t max_bucket_count_custom = 0, current_bucket_count = 0, list_count = 0, max_list_length = 0;
	double hash_load_factor = 0.0f, max_hash_load_factor = 0.0f, avg_list_length = 0.0f;

	custom_hash.bucketStats(max_bucket_count_custom, current_bucket_count, list_count, max_list_length, avg_list_length, hash_load_factor, max_hash_load_factor);

	size_t hash_erase_start = clock();
	for (auto key : v)
	{
		custom_hash.erase(key);
	}
	size_t hash_erase_end = clock();

	cout << "HashBucker::" << endl;
	cout << "尝试插入个数: " << N << endl;
	cout << "当前最大个数: " << max_bucket_count_custom << endl;
	cout << "成功插入个数: " << current_bucket_count << endl;
	cout << "整体插入时间: " << hash_insert_end - hash_insert_start << "ms" << endl;
	cout << "整体查找时间: " << hash_find_end - hash_find_start << "ms" << endl;
	cout << "整体删除时间: " << hash_erase_end - hash_erase_start << "ms" << endl;
	cout << "非空链表个数: " << list_count << endl;
	cout << "最长链表长度: " << max_list_length << endl;
	cout << "最大负载因子: " << max_hash_load_factor << endl;
	cout << "负载因子大小: " << hash_load_factor << endl;
	cout << "链表平均长度: " << avg_list_length << endl;
}
```

我们的比较项包括,  尝试插入个数, 我们最开始通过`rand()`生成了许多随机数, 这些随机数中可能有重复的, 所以不一定会全部插入成功, 尝试插入个数就是`vector`或者`rand`生成的原始数据个数;  当前最大个数其实就是指开散列中一共有多少位置, 或者说, 其实就是开散列中`vector`的`size()`, 它描述了当前开散列中可以容纳的最多链表个数;  成功插入个数就是成功插入哈希容器的数据个数, 它们彼此之间都不相同; 非空链表个数就是开散列虽然有很多位置, 但有些位置的链表可能是空的, 我们这里只计量非空链表的个数, 最大负载因子就是当前容器可以允许的最大负载因子, 负载因子大小就是当前的负载因子, 链表平均长度就是闭散列中的总的数据个数除以非空链表的个数, 在这里其实没有什么参考价值, 严格来说, 平均长度应该是总个数除以链表总个数, 包括空链表的, 但那样和负载因子没什么区别了, 所以这里顺手视为总个数除以非空个数.

另外在说一下, 我们上面的这些叫法其实都是我个人的叫法, 在标准文档中, 不论是闭散列还是开散列, 他们都将其统一称之为`HashTable`, 而不是像我们上面写的那样, 有`HashTable`和`HashBucket`的区别, 当然, 标准库里用的定址方案都是开散列的, 而不会用闭散列, 所以你也可以认为`HashTable`就是默认开散列, 另外, 他们把开散列中的每个链表, 无论是否为空, 都统一叫做`bucket`, 所以`bucket_count()`返回的就是闭散列中的所有链表个数, `bucket_size(size_t idx)`就是每个`bucket`的长度, 其中的参数`idx`, 就是`bucket`所在位置的下标; 下面我们写封装的时候, 就按照标准文档上的叫法来命名. 还有一点要区分, 标准库中的`max_size()`返回的是当前机器理论上可以存储的最大数据个数, 而我们自己写的`max_size()`指的是开散列中的位置总数, 封装的时候我们就不会再用这个名字了, 此外, 封装的时候我们就使用小数作负载因子.

对于我们自己写的开散列来说, 需要写个专门的函数来进行状态统计, 也就是上面代码的`bucketStats`, 其具体内容如下:

```cpp
void bucketStats(size_t& maxBucketSize, size_t& currentSize, size_t& nonEmptyBuckets, size_t& maxBucketLength, double& averageBucketLength, double& loadFactor, double& maxLoadFactor)
{
	maxBucketSize = max_size();
	currentSize = _size;
	nonEmptyBuckets = 0;
	maxBucketLength = 0;
	loadFactor = static_cast<double>(load_factor()) / 100.0f;
	maxLoadFactor = static_cast<double>(max_load_factor()) / 100.0f;

	for (size_t i = 0; i < _table.size(); ++i)
	{
		size_type bucketLength = 0;
		link_type currentNode = _table[i];
		if (currentNode)
		{
			nonEmptyBuckets++;
		}
		while (currentNode)
		{
			bucketLength++;
			currentNode = currentNode->__next_node();
		}
		if (bucketLength > maxBucketLength)
		{
			maxBucketLength = bucketLength;
		}
	}
	
	averageBucketLength = static_cast<double>(currentSize) / static_cast<double>(nonEmptyBuckets);
}
```

稍微说一下`static_cast<typedef>`, 这是C++中专门用于类型转换的操作符, 它在功能上, 与`(typedef)`, 也就是C中的强制类型转换是一样的.  我们看看最终效果.

![image-20250110101540359](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250110101540472.png)

我们看到我们自己写的`HashBucker`, 就速度上来说, 反而比标准库快一些, 这是因为我们是参考`SGI`实现闭散列的, 而`VS`用的`HashTable`自然是用`P.J`版本的, 相比`SGI`, `P.J`版本的`HashTable`有一些小优化, 我们稍后就会看出来, 这些小优化作用上是锦上添花的, 没有也行, 因为它有这种小优化, 所以跑起来稍微慢一点.  具体是什么优化, 我们封装测试的时候再说.

## Encapsulation

```cpp
template<class T>
    struct equal_to
    {
        bool operator()(const T& k1, const T& k2)
        {
            return k1 == k2;
        }
    };

//通用哈希值映射模版
template<class T>
    struct HashMapper
    {
        size_t operator()(const T& v)
        {
            return (size_t)v;
        }
    };

//针对字符串类型的模版特例化
template <>
struct HashMapper<std::string>
{
    size_t operator()(const std::string& s)
    {
        size_t hash = 0;
        for (auto e : s)
        {
            hash *= 131;
            hash += e;
        }
        return hash;
    }
};

template<class _Val, class _Key, class _ExtractKey>
    struct _Hashtable_node
    {
        typedef _Hashtable_node<_Val, _Key, _ExtractKey> self;
        typedef self* link_type;
        _Val _val;
        link_type _next;

        _Hashtable_node(const _Val& v)
            :_val(v)
                , _next(nullptr)
            {
            }

        inline _Val& _value_of_node()
        {
            return _val;
        }

        inline const _Val& _value_of_node()const
        {
            return _val;
        }

        inline const _Key& _key_of_node()const
        {
            return _ExtractKey()(_value_of_node());
        }

        inline link_type& _next_node()
        {
            return _next;
        }
    };
```

由于我们的`HashTable`是`unordered_map`和`unordered_set`的底层容器, 所以和红黑树一样,  类模版实例化时需要输入能够提取`Key`的仿函数, 所以在`class Node`, 中, 我们新加入了常提取节点值`Key`的内联函数, 把模版写好之后, 我们先进行功能性测试, 通过之后在去实现仿函数.

```cpp
//unordered_map<_Key, _Tp, _HashFn, _EqualKey>::HashTable< pair<const _Key, _Tp>, _Key, _HashFn, _ExtractKey, _EqualKey>
//unordered_set<_Key, _HashFn, _EqualKey>::HashTable< const _Key, _Key, _HashFn, _ExtractKey, _EqualKey>
template <class _Val, class _Key, class _HashFcn, class _ExtractKey, class _EqualKey>
class HashTable
{
public:
	typedef _Key key_type;
	typedef _Val value_type;
	typedef _HashFcn hasher;
	typedef _EqualKey key_equal;
	typedef size_t size_type;
	typedef value_type* pointer;
	typedef value_type& reference;
	typedef const value_type* const_pointer;
	typedef const value_type& const_reference;
	typedef _Hashtable_node<value_type, key_type, _ExtractKey> node_type;
	typedef node_type* link_type;
	typedef std::vector<link_type> bucket_type;
	typedef HashTable<_Val, _Key, _HashFcn, _ExtractKey, _EqualKey> self;

private:
	hasher _hash;
	key_equal _equals;
	_ExtractKey _get_key;
	bucket_type _buckets;
	size_type _num_elements;
	double _load;
	double _max_load;

	inline link_type _create_node(const_reference v)
	{
		return new node_type(v);
	}

	inline void _destroy_node(link_type node)
	{
		delete node;
	}

public:

	HashTable()
		:_buckets(bucket_type(10))
		, _num_elements(0)
		, _load(0.0f)
		, _max_load(1.0f)
	{
	}


	HashTable(size_type reserved)
		:_buckets(bucket_type(reserved))
		, _num_elements(0)
		, _load(0.0f)
		, _max_load(1.0f)
	{
	}

	~HashTable()
	{
		size_t size = _buckets.size();
		for (size_t i = 0; i < size; i++)
		{
			link_type curr = _buckets[i];
			while (curr)
			{
				_destroy_node(curr);
				curr = curr->_next_node();
			}
			_buckets[i] = nullptr;
		}
	}

	// 计算vector中理论存放bucket的上限
	inline size_type maxBucketCount()const
	{
		return _buckets.size();
	}

	// 提取最大负载因子
	inline double& max_load_factor()
	{
		return _max_load;
	}

	inline const double& max_load_factor()const
	{
		return _max_load;
	}

	// 检查当前负载因子
	inline const double& load_factor()const
	{
		return _load;
	}

	// 计算哈希表中的有效元素个数
	inline const size_type& size()const
	{
		return _num_elements;
	}

	void swap(self& that)
	{
		std::swap(_buckets, that._buckets);
		std::swap(_num_elements, that._num_elements);
		std::swap(_load, that._load);
		std::swap(_max_load, that._max_load);
	}

	link_type find(const key_type& key)
	{
		size_type max_size = maxBucketCount();
		size_t hash = _hash(key);
		size_t position = hash % max_size;
		link_type curr = _buckets[position];
		while (curr)
		{
			if (_equals(curr->_key_of_node(), key))
				return curr;
			curr = curr->_next_node();
		}

		return nullptr;
	}

	bool insert(const_reference v)
	{
		// 哈希表中是否已经存在该关键值
		if (find(_get_key(v)))
			return false;

		// 检查负载因子
		if (load_factor() >= max_load_factor())
		{
			size_type max_size = maxBucketCount() * 2;
			bucket_type tmp(max_size);
			for (size_t i = 0; i < maxBucketCount(); i++)
			{
				link_type curr = _buckets[i];
				while (curr)
				{
					link_type next = curr->_next_node();
					size_t hash = _hash(curr->_key_of_node());
					size_t position = hash % max_size;
					curr->_next_node() = tmp[position];
					tmp[position] = curr;
					curr = next; 
				}
			}
			_buckets.swap(tmp);
		}

		// 插入逻辑
		size_type max_size = maxBucketCount();
		size_t hash = _hash(_get_key(v));
		size_t position = hash % max_size;
		link_type newNode = _create_node(v);
		newNode->_next_node() = _buckets[position];
		_buckets[position] = newNode;
		_num_elements++;

		// 更新负载因子
		_load = static_cast<double>(size()) / static_cast<double>(max_size);

		return true;
	}

	bool erase(const key_type& key)
	{
		size_t position = key % maxBucketCount();
		link_type curr = _buckets[position];
		link_type prev = nullptr;
		while (curr)
		{
			if (_equals(curr->_key_of_node(), key))
			{
				if (prev == nullptr)
					_buckets[position] = nullptr;
				else
					prev->_next_node() = curr->_next_node();

				_destroy_node(curr);
				return true;
			}
			prev = curr;
			curr = curr->_next_node();
		}

		return false;
	}
};
```

我们对某些冗余成员变量进行了删除, 并将常用的仿函数对象写为成员变量, 并对变量, 类型, 函数的名字进行了一定程度上的优化, 使之更加标准, 成员类型进行了全面公开, 方便上层类或同层类的调用, 现在我们直接写`unordered_map`

```cpp
template <class _Key, class _Tp, class _HashFn = myTemplate::HashMapper<_Key>, class _EqualKey = myTemplate::equal_to<_Key>>
class unordered_map
{
	typedef std::pair<const _Key, _Tp> _Val;

	struct KeyOfValue
	{
		const _Key& operator()(const _Val& value)
		{
			return value.first;
		}
	};

	typedef myTemplate::HashTable<_Val, _Key, _HashFn, KeyOfValue, _EqualKey> HashTable;
	
	typedef typename HashTable::const_reference const_reference;
	typedef typename HashTable::key_type key_type;
	typedef typename HashTable::link_type link_type;

	HashTable _hashTable;

public:
	_Tp& operator[](const key_type& key)
	{
		link_type node = _hashTable.find(key);
		if (node == nullptr)
		{
			_hashTable.insert(std::make_pair(key, _Tp()));
			node = _hashTable.find(key);
		}
		return node->_value_of_node().second;
	}

	bool insert(const_reference v)
	{
		return _hashTable.insert(v);
	}

	bool erase(const key_type& key)
	{
		return _hashTable.erase(key);
	}
};
```

```cpp
void test6()
{
	// 统计水果出现的次数
	string arr[] = { "苹果", "西瓜", "苹果", "西瓜", "苹果", "苹果", "西瓜",
	"苹果", "香蕉", "苹果", "香蕉" };
	wind::unordered_map<string, int> countMap1;
	std::unordered_map<string, int> countMap2;
	for (const auto& str : arr)
	{
		countMap1[str]++;
		countMap2[str]++;
	}

	for (const auto& str : countMap2)
	{
		cout << str.first << "->";
		cout << countMap1[str.first] << endl;;
	}
}
```

![image-20250110110127242](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250110110127340.png)

好, 功能正常, 下面我们来写迭代器.

对于迭代器来说, 首先单链表的迭代很好实现, 关键是一个链表遍历完后怎么换链表, 为此, 我们有两种思路, 一种是把`HashTable`中的`_buckets`传过来, 当然, 不是直接传, 要以指针或者引用的方式来传, 第二种方法, 是直接把`HashTable`对象指针或者引用传过来, 实质上还是把`_buckets`传过来, 我们使用第二种, 因为第二种在后面好封装.  首先我们计算一下当前`bucket`的位置, 算起来很简单, 直接从里面随便找个节点直接算一下, 这样, 就可以知道下一个`bucket`的位置了, 当然, 下一个`bucket`可能是空的, 此时就要去下一个位置, 直到到达了最后一个为止.     需要特别注意的是, `iterator`中的`HashTable`对象或者`_buckets`, 必须使用常指针或者常引用, 因为`HashTable`对象可能有常属性,  此时的`this`是常指针, 普通指针可以变成常指针, 但常指针不能变成普通指针, 所以必须要使用常指针.

```cpp
// 为了让iterator认识HashTable 需要有前置声明
template <class _Val, class _Key, class _HashFcn, class _ExtractKey, class _EqualKey>
class HashTable;

template <class _Val, class _Key, class pointer, class reference, class _HashFcn, class _ExtractKey, class _EqualKey>
class _hash_iterator
{
	typedef HashTable<_Val, _Key, _HashFcn, _ExtractKey, _EqualKey> HashTable;
	typedef _hash_iterator<_Val, _Key, pointer, reference, _HashFcn, _ExtractKey, _EqualKey> self;
	typedef const HashTable* tablePtr;
	typedef typename HashTable::link_type link_type;
	typedef typename HashTable::size_type size_type;

	link_type _pNode;
	tablePtr _pTable;

public:

	_hash_iterator(link_type pNode, tablePtr pTable)
		:_pNode(pNode)
		, _pTable(pTable)
	{}

	reference operator*()
	{
		return _pNode->_value_of_node();
	}

	pointer operator->()
	{
		return &(this->operator*());
	}

	self& operator++()
	{
		link_type next = _pNode->_next_node();
		if (next == nullptr)
		{
			size_type max_size = _pTable->maxBucketCount();
			size_t hash = _HashFcn()(_pNode->_key_of_node());
			size_t position = hash % max_size;
			while (!_pTable->_buckets[++position])
			{
				if (position == max_size - 1)
				{
					_pNode = nullptr;
					return *this;
				}
			}
			next = _pTable->_buckets[position];
		}

		_pNode = next;
		return *this;
	}

	bool operator==(const self& that)const
	{
		if (_pNode == that._pNode)
			return true;
		else
			return false;
	}

	bool operator!=(const self& that)const
	{
		return !this->operator==(that);
	}

};
```

而在`HashTable`中, 为了能让`HashTable`可以访问成员变量, 需要友元声明

```cpp
typedef _hash_iterator<value_type, key_type, pointer, reference, _HashFcn, _ExtractKey, _EqualKey> iterator;
friend iterator;

iterator begin()
{
	for (size_t i = 0; i < maxBucketCount(); i++)
	{
		if (_buckets[i])
			return iterator(_buckets[i], this);
	}
	return end();
}

iterator end()
{
	return iterator(nullptr, this);
}
```

`unordered_map`也需要再套一层

```cpp
typedef typename HashTable::iterator iterator;

iterator begin()
{
	return _hashTable.begin();
}

iterator end()
{
	return _hashTable.end();
}
```

测试开始

```cpp
void test7()
{
	// 统计水果出现的次数
	string arr[] = { "苹果", "西瓜", "苹果", "西瓜", "苹果", "苹果", "西瓜",
	"苹果", "香蕉", "苹果", "香蕉" };
	wind::unordered_map<string, int> countMap1;
	std::unordered_map<string, int> countMap2;
	for (const auto& str : arr)
	{
		countMap1[str]++;
		countMap2[str]++;
	}

	cout << "wind::" << endl;
	auto it1 = countMap1.begin();
	while (it1 != countMap1.end())
	{
		cout << it1->first << "->";
		cout << it1->second << endl;
		++it1;
	}

	cout << endl;

	cout << "std::" << endl;
	auto it2 = countMap2.begin();
	while (it2 != countMap2.end())
	{
		cout << it2->first << "->";
		cout << it2->second << endl;
		++it2;
	}
}
```

![image-20250110112853833](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250110112853918.png)

这里其实已经体现出`SGI`和`P.J`的区别了,  `P.J`的迭代顺序是由插入顺序是由插入顺序决定的, 而`SGI`迭代顺序和插入顺序无关, 单纯由`Key`所映射的位置先后决定.

`P.J`能这样做的原因是因为它的`HashTable`其实有两套索引机制, 一是哈希映射, 用于查找时的索引, 二是双向链表, 用于迭代时的索引.  `P.J`中的节点指针域中除了有一个指向`bucket`下一个节点的指针, 还有一个指向整体链表上一个节点和下一个节点的指针,  就是说, `P.J`里面的节点, 它不止在`bucket`里, 也同时在一个整体链表里, 整体链表按照插入的顺序进行插入, 它的形式和进程控制块在多个队列里排队的形式是一样的, 我们这里因为精力有限, 就不实现了, 另外, 如果要实现的话, 不要用标准库里的双链表, 要自己实现双链表,  标准库里的双链表它并不是为场景而设计的, 如果使用标准库的容器, 相当于每个节点都有一个副本, 它们分别存在整体链表和`bucket`中, 而不是一个节点同时在`bucket`和整体链表中, 这两种方式是有区别的, 同时在的, 找到一个节点后就不用暴力查找整体链表了, 直接在节点上该即可, 分别在的, 在删除`bucket`的节点之后还需要删除整体链表里的副本, 会大大增加删除成本. 

下面我们实现常迭代器, 倒也不能说是实现, 用常指针和常引用重新实例化一个就行了.

```cpp
typedef _hash_iterator<value_type, key_type, const_pointer, const_reference, _HashFcn, _ExtractKey, _EqualKey> const_iterator;
friend const_iterator;

const_iterator begin()const
{
	for (size_t i = 0; i < maxBucketCount(); i++)
	{
		if (_buckets[i])
			return const_iterator(_buckets[i], this);
	}
	return end();
}

const_iterator end()const
{
	return const_iterator(nullptr, this);
}
```

```cpp
typedef typename HashTable::const_iterator const_iterator;

const_iterator begin()const
{
	return _hashTable.begin();
}

const_iterator end()const
{
	return _hashTable.end();
}
```

```cpp
void test8()
{
	// 统计水果出现的次数
	string arr[] = { "苹果", "西瓜", "苹果", "西瓜", "苹果", "苹果", "西瓜",
	"苹果", "香蕉", "苹果", "香蕉" };
	wind::unordered_map<string, int> countMap;
	for (const auto& str : arr)
	{
		countMap[str]++;
	}

	const wind::unordered_map<string, int>& ct = countMap;
	cout << "wind::" << endl;
	auto it = ct.begin();
	while (it != ct.end())
	{
		cout << it->first << "->";
		cout << it->second << endl;
		++it;
	}
}
```

![image-20250110115751166](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250110115751276.png)

可以正常运行, 常引用对象节点的`second`已经是不可修改的了.

我们看看如果`iterator`中的`HashTable`如果不使用常指针, 会报什么错.

![image-20250110120239746](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250110120240033.png)

`“<function-style-cast>”: 无法从“initializer list”转换为“myTemplate::_hash_iterator<std::pair<const _Key,_Tp>,_Key,const std::pair<const _Key,_Tp> *,const std::pair<const _Key,_Tp> &,_HashFcn,_ExtractKey,_EqualKey>”`

它的错误标签是`<function-style-cast>`, 意为函数风格转换, `cast`原意为"铸造", 在计算机科学里面被引申为"类型转换"的意思,  但这个错误的本质不是类型错误, 而是没有合适的构造函数用于构造`const_iterator`对象, 因为此时构造函数的`HashTable`指针用的是普通指针, 而常`HashTable`对象的`this`指针当然是常指针, 常指针无法转化成构造函数中的普通指针, 所以报错了, 类型转换错误只是本质错误  构造失败  的外在表现.

下面我们把一些局部区域改一改, 封装就算是结束了, 

![image-20250110125849091](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250110125849213.png)

`HashTable`还是和红黑树一样, 不直接传迭代器, 而是传送节点指针, 然后在`unordered_map  unordered_set`层再构造迭代器

```cpp
// unordered_map
template <class _Key, class _Tp, class _HashFn = myTemplate::HashMapper<_Key>, class _EqualKey = myTemplate::equal_to<_Key>>
    class unordered_map
    {
        typedef std::pair<const _Key, _Tp> _Val;

        struct KeyOfValue
        {
            const _Key& operator()(const _Val& value)
            {
                return value.first;
            }
        };

        typedef myTemplate::HashTable<_Val, _Key, _HashFn, KeyOfValue, _EqualKey> HashTable;

        typedef typename HashTable::const_reference const_reference;
        typedef typename HashTable::key_type key_type;
        typedef typename HashTable::link_type link_type;


        HashTable _hashTable;

        public:
        typedef typename HashTable::iterator iterator;
        typedef typename HashTable::const_iterator const_iterator;

        iterator begin()
        {
            return _hashTable.begin();
        }

        iterator end()
        {
            return _hashTable.end();
        }

        const_iterator begin()const
        {
            return _hashTable.begin();
        }

        const_iterator end()const
        {
            return _hashTable.end();
        }

        _Tp& operator[](const key_type& key)
        {
            auto pair = insert(std::make_pair(key, _Tp()));
            return pair.first->second;
        }

        std::pair<iterator, bool> insert(const_reference v)
        {
            auto ret = _hashTable.insert(v);
            return { iterator(ret.first, &_hashTable), ret.second };
        }

        bool erase(const key_type& key)
        {
            return _hashTable.erase(key);
        }
    };

// unordered_set
template <class _Key, class _HashFn = myTemplate::HashMapper<_Key>, class _EqualKey = myTemplate::equal_to<_Key>>
    class unordered_set
    {
        typedef _Key _Val;

        struct KeyOfValue
        {
            const _Key& operator()(const _Val& value)
            {
                return value;
            }
        };

        typedef myTemplate::HashTable<_Val, _Key, _HashFn, KeyOfValue, _EqualKey> HashTable;

        typedef typename HashTable::const_reference const_reference;
        typedef typename HashTable::key_type key_type;
        typedef typename HashTable::link_type link_type;

        HashTable _hashTable;

        public:
        typedef typename HashTable::const_iterator iterator;
        typedef typename HashTable::const_iterator const_iterator;

        iterator begin()const
        {
            return _hashTable.begin();
        }

        iterator end()const
        {
            return _hashTable.end();
        }

        std::pair<iterator, bool> insert(const_reference v)
        {
            auto ret = _hashTable.insert(v);
            return { iterator(ret.first, &_hashTable), ret.second };
        }

        bool erase(const key_type& key)
        {
            return _hashTable.erase(key);
        }
    };
```

## others

最后我们再说一下, 闭散列的扩容机制.  在上面的代码中, 我们所采取的扩容策略都是直接把`maxBucketCount`变为原来的两倍, 但有些人认为, 闭散列的`maxBucketCount`应该为素数, 在`SGI`的原码中, 直接在类里定义了一个素数表

```cpp
static const unsigned long __stl_prime_list[__stl_num_primes] =
{
  53ul,         97ul,         193ul,       389ul,       769ul,
  1543ul,       3079ul,       6151ul,      12289ul,     24593ul,
  49157ul,      98317ul,      196613ul,    393241ul,    786433ul,
  1572869ul,    3145739ul,    6291469ul,   12582917ul,  25165843ul,
  50331653ul,   100663319ul,  201326611ul, 402653189ul, 805306457ul, 
  1610612741ul, 3221225473ul, 4294967291ul
};
```

扩容则是以轮询的方式直接寻找当前`maxBucketCount`的下一个素数, 另外需要说明的是, 这个素数表是够用的, 与其考虑素数表够不够用, 不如考虑内存够不够放得下那么多的数.

不过我们就不采用这种策略了, 因为这种策略实际上是存在一定争议的, 尽管`SGI`确实采用了这种策略, 但`P.J`版都是直接倍数扩容, 除此之外, Java也是倍数扩容, 我们知道Java喜欢避C++坑, 在这方面, 我们还是采用之前的策略, 不改了, 这并不是什么特别重要的问题, 另外, 即使是倍数扩容, 所采取的倍数也各有不同, 有些平台考虑到扩容确实有代价, 所以他们一般采用比2倍更大的倍数扩容.

# bitmap

有时我们可能遇到大量的数据个数,  并且对于这些数据, 我们对其的描述非常简单, 比如, 只有 有, 无这两种状态, 此时就可以使用位图这种哈希容器.

比如, 腾讯曾出过一道题, 有40亿个不重复的无符号整型, 没排过序, 现在再给你一个无符号整型, 请你判断这个整型在不在这40亿个数里.

40亿这个数量有些太大了, 光是纯数据, 内存够不够都是个问题, 更不用提, 存放数据的容器了, 比如对于开散列来说, 数据都是放在节点里的, 多少数据就有多少节点,  此时我们要么把数据存外存里, 这可能需要我们改改原码, 把空间分配器和访问接口改一改.

另外, 由题可知, 这是40亿个不重复的数据, 对这些数据的描述是二进制的, 只有 有   无 这两种状态, 再加上  无符号整型实际上也就42亿多, 空间占有率还是比较高的, 所以位图是个绝佳选择.

下面我们就去实现位图, 在标准容器库中, 位图被称为比特集, `bitset`.

```cpp
#define bitsizeof(type) (sizeof(type)*8)

	template<size_t N>
	class bitset
	{
		typedef int type;
		std::vector<type> _bits;

	public:
		bitset()
		{
			_bits.resize(N / bitsizeof(type) + 1);
		}

		// 将x映射的比特位置为1
		void set(size_t x)
		{
			
		}

		// 将x映射的比特位置为0
		void reset(size_t x)
		{
			
		}

		// 测试x映射比特位的状态
		bool test(size_t x)
		{
			
		}
	};
```

我们将`vector<int>`作为我们位图的底层容器, 该容器的每个元素, 都含有`bitsizeof(type)`, 也就是`32`个比特位, 所以它的构造函数很是简单, `N / bitsizeof(type)`大致算出需要的元素个数, 但可能有余数, 所以还要加上一确保够用.    可能有些人会使用位运算代替除法, 但若是这样, 请注意运算符优先级.

接下来我们看看`set`.  在位图中, 将某一比特位置为1或者0, 并不关心该位之前是1还是0, 所以我们的接口不需要有布尔返回值, 需要注意的是, 这些操作都不能影响别的比特位, 所以这需要我们使用一些位运算技巧.

在正式实现`set`之前, 我们需要先找到存储`x`对应比特位的元素, 具体操作很简单, 我们把`x` 除每个元素的比特位数量, 就能找到对应元素的下标, 余一下就能找到对应的位.

之后我们就需要进行位操作了, 为此我们要先知道位运算操作符`<< >>`是高级语言(那对我们来说, 可能是C/C++),中的一部分 高级语言是跨平台的, 单从语言的角度来说,  位操作符是不在乎平台的具体特性的, 比如, 大端和小端.          我们在这里需要注意的是, 虽然我们把`<<`叫做左移运算符, `>>`叫做右移运算符, 但这种说法其实并不严谨, 单从人的角度来看, 对于一个二进制序列串来说, 左边是高位, 右边是低位, 所以左移的实质是向高位移动, 右移是向低位移动, 

而对计算机来说, 其对二进制序列串的存储分为大端和小端这两种, 比如, 我的机器是小端架构

```cpp
int main()
{
	unsigned int i = 1;
	i <<= 8;

	return 0;
}
```

 ![image-20250113121027032](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250113121027111.png)

![image-20250113121043585](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250113121043666.png)

内存窗口使用的是十六进制, `01`是低位第一个字节, 所以被放在前面, 在左移八位之后, 就来到了次低位字节.

但需要注意的是, 我们不需要用位操作符的时候操心这些二进制序列在机器中的具体存储方式, 不要被大端小端给弄迷糊了, 高级语言是会把平台的硬件特性给封装起来的, 我们不需要因为大端或者小端而操心位移方向.  如果连这个都要操心的话, 说明它这个语言就不是高级语言.

`set`使用的位运算是`|`, 我们生成一个数, 这个数它只在`x`的对应位是1, 其它位都是`0`, 按位或是有真则真, 所以其他位都是由之前的状态决定, 而`x`对应的位不管之前是什么状态, 结果都为真.

![image-20241221171857720](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241221171857752.png)

```cpp
void set(size_t x)
{
	size_t i = x / bitsizeof(type);
	size_t j = x % bitsizeof(type);
	_bits[i] |= 1 << j;
}
```

`reset`用的是`&`, 找一个数, 这个数操作位是`0`, 其它位是`1`, 其他位的状态就由以前的状态决定, 而操作位最后结构一定是`1`, 如何得到这个数呢? 把之前的数取反一下就行.

![image-20241221172634533](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241221172634560.png)

```cpp
void reset(size_t x)
{
	size_t i = x / bitsizeof(type);
	size_t j = x % bitsizeof(type);
	_bits[i] &= (~(1 << j));
}
```

至于`test`, 具体的实现方案多种多样, 我在这里是把操作比特位移到最低位, 然后再和`1`按位与

```cpp
bool test(size_t x)
{
	size_t i = x / bitsizeof(type);
	size_t j = x % bitsizeof(type);
	return (_bits[i] >> j) & 1;
}
```

现在我们回到腾讯那道题, 我们说一些使用位图的易错点

能这样构造吗?

```cpp
int main()
{
	wind::bitset<4294967296> bs;

	return 0;
}
```

我们知道, 无符号整型的最大值就是`0xffffffff`, 亦或者说是`4294967295`, 不过还有一个`0`, 所以要加一.  但这种方法, 可能存在风险, 对于某些编译器来说, 它会把显示写的数字都看做整型, 也就是`int`, 就会造成溢出, 当然, 更严谨的来说, 还要看看系统位数, `size_t`在不同位数系统是不一样的, 32位`size_t`存不下`4294967296`

解决方法是使用十六进制, `u`表示无符号

```cpp
int main()
{
	wind::bitset<0x100000000u> bs;

	return 0;
}
```

另外, 要注意这也是不行的

```cpp
int main()
{
	wind::bitset<(unsigned int)-1 + 1> bs;

	return 0;
}
```

整型提升之后还是`unsigned int`, 会溢出变为0             或者这样说, 其实`(unsigned type)-1 + 1`都会溢出

另外, 如果题目明确提到, 没有0, 那也不要直接写成下面这样, 这对32位确实可行, 但对于64位来说, 模版参数`size_t`是`unsigned long long`, 它的`-1`是个很大的数, 内存不一定够.    也不是什么大问题, 现在谁用32位呀,就算用了, 也大多是学校这种老电脑.

```cpp
int main()
{
	wind::bitset<-1> bs;

	return 0;
}
```

位图对于空间的节省还有一个方面, 因为位图中只有`0`和`1`, 所以, 如果是一大片的`0`, 系统不会给它们开辟真正的物理空间的, 当然, 虚拟内存确实开了这么多.  

有时候, 两种状态可能不够用, 此时就需要多维位图了, 另外, 多维位图是我自己的讲法, 不要和其它人说

比如, 现在我们有100亿个无符号整型, 现在我们想看看有哪些数没有出现, 那些数只出现过一次.  那些数只出现两次, 很明显, 现在两种状态不够用了, 此时我们就可以用两个位图, 每个描述对象就对应两个比特位, 就有四种状态

```cpp
template<size_t N>
class twobitset
{
	typedef bitset<N> bitset;

	bitset _bits1;
	bitset _bits2;

	/*
	00   没有出现
	01   出现一次
	10   出现两次
	11   其它情况
	*/

public:
	void set(size_t x)
	{
		if (_bits1.test(x) == false && _bits2.test(x) == false)
		{
			_bits2.set(x);
		}
		else if (_bits1.test(x) == false && _bits2.test(x) == true)
		{
			_bits1.set(x);
			_bits2.reset(x);
		}
		else if (_bits1.test(x) == true && _bits2.test(x) == false)
		{
			_bits2.set(x);
		}
		else;
	}

	int count(size_t x)
	{
		bool m = _bits1.test(x);
		bool n = _bits2.test(x);

		if (m == false && n == false)
			return 0;
		else if (m == false && n == true)
			return 1;
		else if (m == true && n == false)
			return 2;
		else
			return -1;
	}
};
```

 在构造的时候, 模版参数选择`0x100000000u`即可, 无符号整型就这么多, 不必真的用100亿.

# bloom filter

`Bloom filter`即布隆过滤器, 它是在位图的基础上优化得来的. 我们知道, 位图有一个很大的缺点, 就是只能表示整型, 毕竟位图的信息密度太低了, 对于某个个体来说, 它只能表示两种状态, 要么是有, 要么是无, 它甚至都没有存储数据本体, 也就是说, 它存储大量的数据能力是以牺牲信息密度为代价得来的; 这样造成的后果就是, 对于非整型的其它数据来说, 比如字符串, 很明显, 如果要存储字符串, 肯定要建立一个中间的转换层, 把字符串转换成整型, 由于字符串的长度是没有限定的, 所以理论上来说, 字符串有无穷种可能, 而整型是有限的, 这意味着, 无论你的字符串转换成整型的算法再怎么优化, 都肯定存在哈希碰撞的可能.

比如说, 现在我们有两个字符, 记为`A`, `B`, 现在我们通过某种转换算法, 记为$f$,  将`A B`转换成整型, 现在恰巧,  $f(A)=42 $ $f(B)=42$, 也就是说, 它们都会被映射到`42`这个比特位;  现在我们发现`42`这个比特位是被置一的, 那能不能断言, `A`一定在呢? 很明显, 不行的, 因为`42`置一, 也可能是因为之前`B`被`set`过, 因为`B`被`set`过, 所以`42`被置一, 当然, 也有可能是别的转换之后也映射到`42`的字符串被`set`而造成的, 总之, 如果`42`这个比特位是置一的, 是无法确定`A`或者`B`是一定在的, 也就是说, 布隆过滤器对于判断某个个体是否在是不准确的;

现在, 我们再来想一想, 如果`42`这个位是零, 那能不能断言`A`一定是不在的呢? 答案很明显是可以的, `42`为零, 就意味着所有经$f$转化之后为`42`的字符串都是不在的, 所以`A`或者`B`一定是不在的, 总结来说, 布隆过滤器判断某个个体是否不在是准确的.

那布隆过滤器有什么用呢? 在上面的过程中, 我们知道, 布隆过滤器在判断“某个元素是否不存在”时是准确的，但在判断“某个元素是否存在”时可能存在误判, 那这怎么用? 不准确呀, 为此, 在二十世纪七十年代, 布隆(Burton Howard Bloom)就提出一种用法,  可以把布隆过滤器作为过滤器来使用, 比如现在我们有大量的数据需要被处理, 我们可以先用布隆过滤器做一个初步的筛选, 把一大半的数据都给筛出去, 这样, 我们只用处理剩下的那些一小部分数据就行了.   为了提高布隆过滤器的筛选效率, 我们就需要降低"在"的误判率, 为此, 布隆认为可以建立多套转换机制, 让一个字符串映射多个比特位, 比如说, 我们可以建立三套转换算法$f_1, f_2, f_3$, $f_1(A) = 42, f_2(A) = 67, f_3(A)= 648$, 如果`set(A)`,  那就把`42   67   648`这三个位全部置为一, 等到`test(A)` 的时候, 如果`42   67   648`中有一个为零, 就意味着, `A`肯定是不在的, 如果它们全部都是为一的, 则意味着`A`可能在, 也可能不在, 需要进入下一轮来确定到底在不在.

比如, 我们想象一个场景, 账号的注册, 账号注册是需要昵称的,  确认昵称是否重复是需要到用户数据库中搜索的, 如果重复, 那就驳回, 让用户重新想一个, 如果之前没有重名的, 那就允许新用户使用这个昵称.    在这个过程中, 用户输入的昵称就需要到服务器上的数据库进行比对, 以确认该昵称之前是否存在, 先不提网络传输过程, 就单纯从服务器的视角上来看, 因为数据库中存储的是数据本体, 所以所占的空间很大, 因此需要放在外存中, 这样就必然存在硬件访问的过程, 从而影响我们的注册效率, 为了提高效率, 我们就可以先用布隆过滤器记录一下数据库中的昵称, 由于布隆过滤器本质上是位图, 所以所用空间较少, 就可以放在内存中, 这样如果布隆过滤器认为昵称是不在的, 那就肯定是不在的, 让用户直接用就行, 如果布隆过滤器认为昵称是在的, 那再去数据库比对一下, 确定它到底是真的在还是误判了, 如果用户要频繁注册新账号的话,  可能这个用户他是类似于客户经理的那种, 那我们可以把布隆过滤器直接发到客户端上, 这样有些请求甚至不需要经过网络这部分, 也不用担心信息泄露, 毕竟布隆过滤器它没有存储数据本身, 而且数据本身也无法依靠布隆过滤器来还原.  

布隆过滤器的这种思路也可以用在其它地方, 比如对比字符串的时候, 一个字符一个字符比太麻烦了, 我们可以先把字符串进行预处理, 通过哈希函数把它们转换成一个数, 等到比对的时候, 先比对转换出来的数,  毕竟数字比字符串更好对比, 只有数字相同的时候我们再真的去比对一下字符串.

再来个例子, 我们知道现在的服务器系统实际上是分布式的, 所谓分布式就是说数据不是只存在一个服务器上的, 而是存在多个服务器上的, 此时, 就有个问题, 我怎么知道需要的数据存在这台服务器上, 而不是存在那台服务器上呢?   比如说, 我们现在把数据存在四台服务器上, 如果要存储新的数据, 我们就通过哈希函数把新数据转换成整型, 再把数据模上`4`, 得到的余数是几, 就把新数据存在那台服务上, 这样等到查找的时候, 我们通过相同的方法就能知道数据如果存在, 应该会存在哪台服务器上,   不过这种做法还有一定问题, 如果现在数据量过大, 四台服务器也存不下了, 那就需要引入新的服务器, 但这就带来一个问题, 原先的映射关系被破坏了, 难道我们把原先服务器里的数据重新存储吗?  这可是服务器, 这代价太大了, 所以就有人提出了"一致性哈希",  至于"一致性哈希"的具体细节, 这里就不多说了,  这不是我们当前应该考虑的问题.

下面我们实现一下布隆过滤器.

首先我们要考虑一下, 一个元素应该映射几个比特位, 或者说, 布隆过滤器应该有几套哈希函数, 从工程的角度来说, 我们一般都是设置成三个及其以上.  然后就要考虑新的问题, 要开辟多少可支配的空间, 此时就要用下面的公式:
$$
k = \frac{m}{n}ln_2
$$
其中, `k`表示的就是哈希函数的个数, `m`表示的是应该开辟的比特位个数, `n`表示最大的元素个数.  在这里我们把`k`定义成三, 那么就可以将这个式子化简成
$$
m = \frac{3}{ln_2}n ≈ 4n
$$

```cpp
#include<bitset>

struct BKDRHash
{
	size_t operator()(const std::string& key)
	{
		size_t hash = 0;
		for (auto e : key)
		{
			hash *= 131;
			hash += e;
		}
		return hash;
	}
};

struct RSHash
{
	size_t operator()(const std::string& key)
	{
		size_t hash = 0;
		size_t magic = 63689;
		for (auto ch : key)
		{
			hash = hash * magic + ch;
			magic *= 378551;
		}
		return hash;
	}
};

struct APHash
{
	size_t operator()(const std::string& key)
	{
		size_t hash = 0;
		size_t ch = 0;
		for (size_t i = 0; i < key.size(); i++)
		{
			ch = key[i];
			if ((i & 1) == 0)
			{
				hash ^= ((hash << 7) ^ ch ^ (hash >> 3));
			}
			else
			{
				hash ^= (~((hash << 11) ^ ch ^ (hash >> 5)));
			}
		}
		return hash;
	}
};

template<size_t N, class type = std::string, class HashFcn1 = BKDRHash, class HashFcn2 = RSHash, class HashFcn3 = APHash>
class BloomFilter
{
private:
	std::bitset<4 * N> _bits;

public:
	void set(const type& key)
	{
		size_t i = HashFcn1()(key) % N;
		size_t j = HashFcn2()(key) % N;
		size_t k = HashFcn3()(key) % N;

		_bits.set(i);
		_bits.set(j);
		_bits.set(k);
	}

	bool test(const type& key)
	{
		size_t i = HashFcn1()(key) % N;
		if (!_bits.test(i)) return false;

		size_t j = HashFcn2()(key) % N;
		if (!_bits.test(j)) return false;

		size_t k = HashFcn3()(key) % N;
		if (!_bits.test(k)) return false;

		return true;
	}
};
```

下面是我随手写的测试程序, 可以在测试布隆过滤器的同时统计一下误报率, 不过这种统计方式我不确定是否客观,

```cpp
#include"BloomFilter.h"

#define N 1000000
#define TEST_SIZE 100000

string generate_random_string(size_t length) {
	static const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
	std::string str(length, ' ');
	for (size_t i = 0; i < length; ++i) {
		str[i] = charset[rand() % (sizeof(charset) - 1)];
	}
	return str;
}

void simulation_test()
{
	srand(time(nullptr));
	BloomFilter<N> bf;
	unordered_set<string> test_data;
	for (size_t i = 0; i < N; i++)
	{
		test_data.insert(generate_random_string(rand() % 64 + 1));
	}

	for (const auto& str : test_data)
	{
		bf.set(str);
	}

	size_t false_positive_count = 0;
	for (size_t i = 0; i < TEST_SIZE; i++)
	{
		string str = generate_random_string(rand() % 64 + 1);
		if (bf.test(str) == true && test_data.count(str) == 0)
			false_positive_count++;
		if (bf.test(str) == false && test_data.count(str) == 1)
		{
			cout << "致命错误" << endl;
			return;
		}
	}

	cout << static_cast<double>(false_positive_count) / TEST_SIZE << endl;
}

int main()
{
	simulation_test();
	return 0;
}
```

​    从结果上来看, 似乎不太理想, 如果想要把误报率再往下降, 可以考虑再加几套哈希函数.

![image-20250217151709875](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250217151710067.png)

一般来说, 布隆过滤器是没有`reset`的, 还是因为哈希碰撞, 只要两个元素间含有公共的比特位, 当`reset`其中一个的时候, 必然会影响另一个, 有人可能说可以加上引用计数, 但实际上也不行, 比如我们有500个字符串都会涉及到比特位`a`, 现在`a`的计数是200, 此时如果对另外300的字符串作reset, 就必然会影响到之前的200, 而且, 即使退一步来说, 引用计数确实可行, 那也会大大增加数据量, 从而把布隆过滤器最大的节省空间给破坏掉, 总的来说, 布隆过滤器没有可行的`reset`方案, 据说有些布隆过滤器的变种是有`reset`的, 但在这里, 我们暂不考虑.

# others

最后, 我们说两道面试时常见的海量数据题, 介绍一下常用的解题思路.

1. 给两个文件，分别有100亿个query，我们只有1 G内存，如何找到两个文件交集？分别给出精确算法和近似算法

   query是请求的意思, 典型的就是网络请求, 用户在搜索框里搜索相应内容, 搜索引擎将相关的汇总起来, 然后再供用户主动选择, 用户点击某个页面, 就会通过该页面对应的链接找到相应的服务器.            在题目中, 我们可以了解到当前的情况是, 要处理的数据很多, 但可供支配的内存却很少,  所以我们就可以用布隆过滤器对两个文件进行粗略的对比, 这就是近似算法, 至于精确算法, 则需要使用名为"哈希切割"的手段.

   我们假设, 一个 query 50 byte, 则100亿query大概是500 G, 是个非常庞大的数据量, 很明显, 我们要把这些数据给拆分成更小的文件, 关键是怎么分, 首先肯定不能均分, 均分虽然可以进行比对, 但时间复杂度非常高;  为此, 我们就可以先给每个大文件都预设2000个小文件, 并对这些小文件一一编号, 比如, 我们可以把两个大文件记为`a b`, 这样小文件的编号就是`a_0  a_1   a_2  ...  a_1999 , b_0  b_1 ... b_1999`, 之后我们再设计一个哈希函数, 它能将每个query转换成一个整型, 对每个大文件中的100亿query逐个读取, 获得对应的哈希值, 再依据哈希值将query分配到对应的小文件中, 比如某个`a`中query的哈希值是2341, 2341 % 2000 = 341, 那就把该query放到`a_341`中, 等到分配完毕后, 每个小文件理想上来说, 差不多是0.25 G, 如果`a b`中的某两个query相同, 则它们必然进入相同后缀的小文件中, 所以剩下来要做的事, 就是将`a_0 b_0`读取到内存的容器中, 再对它们进行比对, 然后是`a_1 b_1, a_2 b_2 ...`.

   不过我们也说了, 这是理想情况下, 在实际过程中, 小文件中的数据量并不均衡, 可能会出现相同后缀小文件大小之和大于内存或者单个小文件大小大于内存的情况, 此时就需要分类讨论, 超出限制可能是因为两种情况, 情况一, 是大文件本身就有许多完全相同的query, 于是这些相同的query就必然会被分配到同一个小文件中, 从而引起小文件超出限制, 情况二, 小文件中主要是不同的query, 就是太巧了, 它们都被分配到同一个小文件中, 这两种情况是有区别的, 我们的需求是比较两个大文件的交集, 对于单个单文件中的重复元素, 我们只需要一个就够了, 剩下的都不需要输入到容器中.

   那到底具体怎么解决这个问题呢?其实对于这两种情况, 我们都可以使用同一种应对方法, 那就是什么都不管, 直接把小文件中的元素加载到容器中即可, 当然, 我们要选取的容器是无法收录重复元素的, 这样, 重复的元素就会插入失败, 从而不会进入到内存中, 对于情况一来说, 可能两个相同后缀的小文件都加载到内存中后, 内存仍有剩余, 可以继续进行后续操作, 而对于情况二来说, 可能在插入的过程中就会抛出异常, 我们可以捕捉该异常, 并对出现异常的 小文件对 进行更细的划分,  在我印象中, 这似乎是捕捉异常的第一次实际应用.

2. 给一个超过100 G大小的log file, log中存着 IP 地址, 设计算法找到出现次数最多的 IP 地址？与上题条件相同，如何找到top K的 IP ？

   这也是一种  top K 问题, 而且是大小堆不好直接解决的 top K问题, 大小堆适合找极值, 元素间的大小可以局部一个一个比, 但元素的个数很明显是一个全局性的数据, 所以这个问题需要先使用哈希分割的方式去进行局部分割, 这样就缩小了全局性, 之后对小文件中的元素进行遍历与个数统计, 此时既可以直接进行比对, 也可以再借助于大小堆进行辅助.  这里只是让我们找到最大的, 所以直接比较似乎更好.

# end