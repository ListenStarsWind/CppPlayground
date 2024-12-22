# Encapsulating set and map

## Introduction

在上篇文章中，我们实现了红黑树，而在这篇文章中，我们将以上篇文章的`class RBTree`为基础，封装出`set`和`map`。

首先我们还是来看看`stl`原码是怎么写的。

打开`set`和`map`源文件，我们看到如下内容：

![image-20241219104201244](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241219104202550.png)

![image-20241219104229370](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241219104230333.png)

我们看到，`set`和`map`中都是头文件的包含，并不包含具体的代码实现。而且我们知道`set`和`map`都是树结构，看上去它们使用的树结构都在`stl_tree.h`里，也就是说，`set`和`map`很可能是用同一棵树模版包装出来的。

![image-20241219104812034](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241219104813075.png)

上面这张图显示了`stl_set.h`中`template class set `的核心声明，从其中我们可以看到`set`所使用的树结构是对模版类`_Rb_tree`的实例化。

```cpp
typedef _Rb_tree<key_type, value_type, 
                _Identity<value_type>, key_compare, _Alloc> _Rep_type;
_Rep_type _M_t;  // red-black tree representing set
```

`template class _Rb_tree`有五个模版参数，后两个就不看了，`key_compare`是个仿函数，用于比较`Key`的相对大小，`_Alloc`是分配器，用于进行内存分配，这不是我们当前的学习方向，所以也忽略，剩下的三个模版参数就需要好好说说了。

第一个参数`key_type`就是`set`中存储的`key`，这很容易猜出，关键是`value_type`和`_Identity<value_type>`。让我们再看看`map`。

![image-20241219110250303](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241219110251531.png)

```cpp
typedef _Rb_tree<key_type, value_type, 
                 _Select1st<value_type>, key_compare, _Alloc> _Rep_type;
_Rep_type _M_t;  // red-black tree representing map
```

让我们来具体对比一下`set`和`map`所传递的模版参数

![image-20241219111341351](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241219111341426.png)

我们可以看到`_Identity`和`_Select1st`实际都是一个仿函数，对于`_Identity`来说，它就是把传入的参数再返回，对于`_Select1st`来说，它是把`pair`的`first`返回。而`value_type`其实就是节点中存储的实际数据，对于`set`来说，就是`Key`，而对于`map`来说，就是`pair<const Key, Value>`。

它为什么要这样设计呢？因为`_Rb_tree`既要作为`set`的底层树，又要作为`map`的底层树，这意味着，光看`_Rb_tree`，是无法得知实现的是`Key`树还是`Key-Value`树的，但这样就带来一个问题，很明显，`_Rb_tree`的实现免不了对`Key`进行比较，这样问题就来了，`_Rb_tree`自身都不知道自己是`Key`模型还是`Key-Value`模型，它怎么知道要比较什么呢？这时候就要`_Rb_tree`的第三个参数发挥作用了，第三个参数的实质，就是把比较项给提取出来，对于`set`来说，它返回的就是`Key`，而对于`map`来说，返回的是`pair`的`first`。

下面就是实际代码，红黑树具体的实现细节请参考上一篇文章，本篇文章只说封装过程。

为什么基树里的那么多`typedef`都被公开了呢？这是因为以后`set`和`map`都是以组合的形式使用基树的，为了对基树的接口进行封装，我们需要把基树的种种接口在`set`和`map`层面进行包装，这免不了要用到基树中的种种类型，为了方便起见，可以把它们全部公开，方便`set`和`map`的使用。

另外可以看到基树中对于`Key`的比较都会来到仿函数`BaseTreeLess`里，其实如果想要代码的可读性更高的话，直接用`<`或许更好，也就是把`cmp(val, location->_value)`改成`KeyOfValue()(val) < KeyOfValue()(location->_value)`但我觉得这太麻烦了，所以内部使用仿函数统一进行管理。为什么叫`KeyOfValue`呢？因为`stl`源码用的就是这名字，它的意思就是从`Value`中把`Key`提取出来。中序遍历暂且再留着，用来运行时看现象，确认主结构无误之后，就要去写迭代器了。

## Operation

```cpp
namespace wind
{
	template<class Key>
	struct Less
	{
		bool operator()(const Key& val1, const Key& val2)
		{
			return val1 < val2;
		}
	};

	enum color
	{
		red,
		black
	};

	template<class V>
	struct BaseTreeNode
	{
	private:
		typedef BaseTreeNode<V> self;
		typedef self* link_type;
	public:
		link_type _parent;
		link_type _left;
		link_type _right;
		color _col;
		V _value;

		BaseTreeNode(const V& v)
			:_parent(nullptr)
			, _left(nullptr)
			, _right(nullptr)
			, _col(red)   
			, _value(v)
		{}
	};

	template<class Key, class Value, class KeyOfValue, class Compare>
	class BaseTree
	{
		// 将基树类型开放给具体树
	public:
		typedef BaseTree<Key, Value, KeyOfValue, Compare> self;
		typedef Key key_type;
		typedef Value value_type;
		typedef value_type* pointer;
		typedef const value_type* const_pointer;
		typedef value_type& reference;
		typedef const value_type& const_reference;
		typedef BaseTreeNode<value_type> Node;
		typedef Node* link_type;
		typedef Compare less;

	private:
		struct BaseTreeLess
		{
			bool operator()(const_reference smaller, const_reference larger)
			{
				KeyOfValue Extract;
				return Extract(smaller) < Extract(larger);
			}
		};

		enum direction  
		{
			left,
			right,
			invalid
		};

	public:
		bool Insert(const_reference val)
		{
			if (_root == nullptr)
			{
				link_type newNode = new Node(val);
				newNode->_col = black;       
				_root = newNode;
				return true;
			}

			BaseTreeLess cmp;
			link_type location = _root;
			link_type parent = nullptr;
			while (location)
			{
				parent = location;
				if (cmp(val, location->_value))
					location = location->_left;
				else if (cmp(location->_value, val))
					location = location->_right;
				else
					return false;
			}

			location = new Node(val);
			location->_parent = parent;
			if (cmp(val, parent->_value))
				parent->_left = location;
			else
				parent->_right = location;

			(void)parent;                
			link_type& BasePoint = location; 
			while (BasePoint)  
			{
				link_type parent = BasePoint->_parent;  

				if (parent->_col == black)
					break;
				
				link_type grandparent = parent->_parent; 
				link_type uncle = nullptr;
				direction parent_way = invalid;
				if (parent == grandparent->_left)
				{
					parent_way = left;
					uncle = grandparent->_right;
				}
				else
				{
					parent_way = right;
					uncle = grandparent->_left;
				}

				if (uncle && uncle->_col == red)  
				{
					parent->_col = uncle->_col = grandparent->_col; 
					if (grandparent == _root)
						break;                      
					else
						grandparent->_col = red;	

					BasePoint = grandparent;
				}
				else
				{
					direction base_way = invalid;
					if (BasePoint == parent->_left)
						base_way = left;
					else
						base_way = right;

					if (parent_way == base_way)
					{
						if (parent_way == left)
							_RotateRight(grandparent);
						else
							_RotateLeft(grandparent);

						parent->_col = grandparent->_col;  
						grandparent->_col = red;           

						break;
					}
					else
					{
						if (base_way == right)
							_RotateLeft(parent);
						else
							_RotateRight(parent);

						BasePoint = parent;  
					}
				}
			}
			return true;
		}

		std::vector<value_type> InOrder()
		{
			std::vector<value_type> res;
			_InOrder(_root, res);
			return res;
		}
private:
		void _RotateLeft(link_type parent)  
		{
			link_type subR = parent->_right;   
			link_type subRL = subR->_left;     

			link_type newParPar = parent->_parent;
			parent->_parent = subR;
			(void)parent->_left; 
			parent->_right = subRL;

			if (newParPar == nullptr)
			{
				subR->_parent = nullptr;
				_root = subR;
			}
			else
			{
				if (newParPar->_left == parent)
				{
					newParPar->_left = subR;
				}
				else
				{
					newParPar->_right = subR;
				}

				subR->_parent = newParPar;
			}
			subR->_left = parent;
			(void)subR->_right;  

			if (subRL) 
				subRL->_parent = parent;
		}

		void _RotateRight(link_type parent)
		{
			link_type subL = parent->_left;
			link_type subLR = subL->_right;

			link_type newParPar = parent->_parent;
			parent->_parent = subL;
			parent->_left = subLR;
			(void)parent->_right;

			if (newParPar == nullptr)
			{
				subL->_parent = nullptr;
				_root = subL;
			}
			else
			{
				if (newParPar->_left == parent)
				{
					newParPar->_left = subL;
				}
				else
				{
					newParPar->_right = subL;
				}

				subL->_parent = newParPar;
			}
			(void)subL->_left;
			subL->_right = parent;

			if (subLR)
				subLR->_parent = parent;
		}

		void _InOrder(link_type root, std::vector<value_type>& v)
		{
			if (root == nullptr)
				return;

			_InOrder(root->_left, v);
			v.push_back(root->_value);
			_InOrder(root->_right, v);
		}

		link_type _root = nullptr;
	};
}

```

在具体写`set`和`map`的时候，如果要从`BaseTree`里取类型，记得加上`typename`，

```cpp
// set.h
#pragma once
#include"Base_Tree.h"

namespace wind
{
	template<class Key, class cmp =  Less<Key>>
	class set
	{
		struct KeyOfValue
		{
			const Key& operator()(const Key& value)
			{
				return value;
			}
		};

		typedef Key value_type;
		typedef BaseTree<Key, value_type, KeyOfValue, cmp> BaseTree;
		typedef typename BaseTree::const_reference const_reference;
	public:
		bool Insert(const_reference value)
		{
			return _Container.Insert(value);
		}

		std::vector<Key> InOrder()
		{
			return _Container.InOrder();
		}
	private:
		BaseTree _Container;
	};
}

// map.h
#pragma once
#include"Base_Tree.h"

namespace wind
{
	template<class Key, class Value, class cmp = Less<Key>>
	class map
	{
		struct KeyOfValue
		{
			const Key& operator()(const std::pair<Key, Value>& value)
			{
				return value.first;
			}
		};
 
		typedef std::pair<Key, Value> value_type;
		typedef BaseTree<Key, value_type, KeyOfValue, cmp> BaseTree;
		typedef typename BaseTree::const_reference const_reference;

	public:
		bool Insert(const_reference value)
		{
			return _Container.Insert(value);
		}

		std::vector<std::pair<Key, Value>> InOrder()
		{
			return _Container.InOrder();
		}

	private:
		BaseTree _Container;
	};
}
```

下面我们来写迭代器，先把样子搭出来，先不管`const`。

树结构也是一种链式结构，所以它的迭代器建立在链表迭代器的基础上，迭代器实际是对节点指针的再封装，所以`operator* operator-> operator== operator!=`都好写，关键是`operator++ operator--`，不管怎么。先把好写的写出来。

```cpp
template<class Value>
struct BaseTreeIterator
{
	typedef Value value_type;
	typedef value_type* pointer;
	typedef value_type& reference;
	typedef BaseTreeNode<value_type> Node;
	typedef Node* link_type;
	typedef BaseTreeIterator<Value> self;

	link_type _ptr;

	BaseTreeIterator(link_type ptr) :_ptr(ptr) {}

	reference operator*()
	{
		return _ptr->_value;
	}

	pointer operator->()
	{
		return &(this->operator*());
	}

	bool operator==(const self& obj)
	{
		return this->_ptr == obj._ptr;
	}

	bool operator!=(const self& obj)
	{
		if (*this == obj)
			return false;
		else
			return true;
	}
};
```

我略微记得以前分析过`operator->`不能写成`return &(_ptr->_value)`的原因，现在我记不得了，但像上面的这种写法肯定是更安全的，现在我们想想怎么写`operator++`，树的迭代器使用的是中序遍历，其遵循的顺序是左子树，根节点，右子树，也就是说，当某棵树的左子树遍历完了，就意味着它之后要遍历根节点，当某棵树的右子树遍历完了，就说明这棵树被遍历完了，要去当前树的上级节点了。我们找个图看看。

![image-20241218213505051](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241218213505147.png)

首先是找到`begin`，`begin`怎么找呢？从根节点开始，不停往左子树里迭代，直到没有左子树了，也就是找到最左边的那个节点，对于搜索树来说，其实就是最小的节点，对于图来说，就是`[1]`，`[1]`下一个节点是那个呢？按照左子树，根节点，右子树的顺序，`[1]`这棵树的根已经遍历过了，那就要去右子树了，`[1]`也是有右子树的，进入右子树后，我们就又进入了一棵树了，所以接下来我们就要找到最左节点，也就是`[6]`，`[6]`被遍历过后，就相当于`[6]`这棵树的根节点被遍历过了，所以我们接下来要去`[6]`的右子树，但`[6]`的右子树是空的，空树不用遍历，也可以认为空树没有元素，所以就相当于遍历过了，所以`[6]`的右子树就被遍历过了，`[6]`的右子树遍历过了，就相当于`[6]`这棵树遍历完了，`[6]`这棵树是`[1]`的右子树，也就是说`[1]`的右子树遍历完了，`[1]`的右子树遍历完了，就意味着`[1]`这棵树遍历完了，`[1]`这棵树是`[8]`的左树，现在`[8]`的左树已经遍历完了，接下来就要遍历`[8]`这棵树的根节点了，也就是`[8]`，更节点遍历完后，就要去遍历`[8]`的右子树，`[8]`的右子树最左节点就是`[11]`，`[11]`没有右子树，这就意味着`[11]`这棵树遍历完了，`[11]`是`[8]`的右子树，`[8]`的右子树遍历完了，就意味着`[8]`这棵树遍历完了，`[8]`这棵树是`[13]`的左子树，现在`[13]`的左子树遍历完了，所以接下来就要遍历`[13]`这棵树的根节点，也就是`[13]`，`[13]`遍历完了，就要去遍历`[13]`的右子树了，进入`[13]`的右子树后，迭代到右子树的最左节点，也就是`[15]`，`[15]`这棵树是`[17]`的左子树，它遍历完了，就要遍历`[17]`这棵树的根，`[17]`的根遍历完了，就要去遍历`[17]`的右子树，进入右子树后，迭代到最左节点`[22]`，`[22]`是`[25]`的左子树，它遍历完了，就该轮到`[25]`的根节点了，之后是`[25]`这棵树的右子树，`[25]`的右子树遍历完了，就说明`[25]`这棵树遍历完了，`[25]`是`[17]`的右子树，于是`[17]`也遍历完了，`[17]`是`[13]`的右子树，现在它遍历完了，就意味着`[13]`这棵树遍历完了，`[13]`是谁的子树，`[13]`的`parent`是`nullptr`，也就是说没有祖先了，所以整棵树遍历完毕，此时迭代器里存的指针是`nullptr`，它需要借助于`end`停下来，所以`end`就是`nullptr`。

经过上面的这段描述，相信肯定说明白了，不过代码具体怎么写，还需要说一说。我们可以依据右子树是否为空将`operator++`的执行流分成两大部分，第一部分，右子树不为空，那就让迭代器里的指针指向右子树的最左节点，如果右子树为空，说明当前树已经遍历完了，所以我们要先把迭代器里的指针指向当前树的上级节点，但我们并不清楚，上级节点在它的父节点眼中到底扮演什么角色，所以向上回溯的过程是一个循环。

```cpp
self& operator++()
{
	if (_ptr->_right)
	{
		// 右子树不为空
		// 下一节点是右子树的最左节点
		link_type curr = _ptr->_right;
		while (curr->_left) curr = curr->_left;
		_ptr = curr;
	}
	else
	{
		// 右子树为空
		link_type curr = _ptr;
		link_type parent = curr->_parent;
		// 如果当前树是上一级树的右子树
		// 就说明上一级树已经遍历完成
		while (parent && curr == parent->_right)
		{
			curr = parent;
			parent = curr->_parent;
		}

		// 来到这里 有两种情况
		// 
		// 已经没有上级树了 整棵树遍历完了
		// 
		// curr树的右子树已经遍历完了 中序为 左子树 根
		// 节点 右子树 右子树遍历完意味着curr已经遍历完了
		// 又curr是上级树的左子树 所以下一个节点就是父节点
		_ptr = parent;
	}

	return *this;
}
```

```cpp
// set.h
iterator begin()
{
    return _Container.begin();
}

iterator end()
{
    return _Container.end();
}

// map.h
iterator begin()
{
    return _Container.begin();
}

iterator end()
{
    return _Container.end();
}
```

让我们来试验一下

```cpp
#include"set.h"
#include"map.h"
#include<set>
#include<map>

using namespace std;

void test_set()
{
	wind::set<int> s;
	s.insert(1);
	s.insert(2);
	s.insert(3);
	s.insert(4);
	s.insert(5);

	for (auto e : s)
	{
		cout << e << " ";
	}
	cout << endl;
}

void test_map()
{
	wind::map<std::string, std::string> m;
	m.insert(std::make_pair("apple", "苹果"));
	m.insert(std::make_pair("banana", "香蕉"));
	m.insert(std::make_pair("grape", "葡萄"));
	m.insert(std::make_pair("orange", "橙子"));
	m.insert(std::make_pair("kiwi", "猕猴桃"));
	m.insert(std::make_pair("pear", "梨"));
	m.insert(std::make_pair("pineapple", "菠萝"));
	m.insert(std::make_pair("peach", "桃子"));

	auto it = m.begin();
	while (it != m.end())
	{
		cout << it->first << "->" << it->second << endl;
		++it;
	}
	cout << endl;
}

int main()
{
	test_set();
	test_map();
	return 0;
}
```

![image-20241219192539108](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241219192539271.png)

`operator--`的逻辑于此类似，只不过顺序变成了先右子树，再根节点，最后左子树。

```cpp
self& operator--()
{
	if (_ptr->_left)
	{
		// 左子树不为空
		// 下一节点是左子树的最右节点
		link_type curr = _ptr->_left;
		while (curr->_right) curr = curr->_right;
		_ptr = curr;
	}
	else
	{
		// 左子树为空
		link_type curr = _ptr;
		link_type parent = curr->_parent;
		while (parent && curr == parent->_left)
		{
			curr = parent;
			parent = curr->_parent;
		}
		_ptr = parent;
	}

	return *this;
}
```

现在迭代器已经有个样子了，我们是时候改一下`insert`的返回值了。

我们用一个专门用来进行比对的软件看看

![image-20241219194503226](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241219194503329.png)

![image-20241219194538742](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241219194538845.png)

![image-20241219194556726](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241219194556821.png)

这比对一下很明显吧。记得再把`set`的`map`层面的返回值也改一下。

现在我们就把`map`的`operator[]`写出来

```cpp
Value& operator[](const Key& key)
{
	// 没有对应的key 就插入一个默认构造的Value
	ret_type ret = insert(std::make_pair(key, Value()));
	// 插入成功 返回新插入节点的迭代器
	// 插入失败 返回原来就有节点的迭代器
	// first就是ret的第一个成员
	// 也就是那个迭代器
	// 迭代器有operator->重载
	// 这样就能节点里的_value的地址
	// 对于map _value是pair<Key, Value>
	// 所以返回的就是Value的引用
	return ret.first->second;
} 
```

```cpp
void testSubscriptOperator()
{
	string arr[] = { "苹果", "西瓜", "苹果", "西瓜", "苹果", "苹果", "西瓜",
		"苹果", "香蕉", "苹果", "香蕉" };
	wind::map<string, int> countMap;
	for (const auto& str : arr)
	{
		countMap[str]++;
	}

	for (const auto& e : countMap)
		cout << e.first << "::" << e.second << endl;
	cout << endl;
}
```

![image-20241219201705808](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241219201705879.png)

接下来我们去解决一下常迭代器，和链表类似，为了让一个迭代器模版可以既实例化出普通迭代器，也可以实例化出常迭代器，我们需要对迭代器模版的参数进行修改，将引用和指针也添加进去，就像链表那样，之后若是想要实例化出普通迭代器，就用一般类型实例化，常迭代器就用常类型初始化。

为了能更优雅的实现反向迭代器，我对项目的部分内容进行了重构，所以下文的代码可能与上文有一些形式上的较大差别。

下面是基树的迭代器声明

![image-20241222182338276](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241222182338702.png)

下面是正向迭代器模版类定义

![image-20241222182700915](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241222182701266.png)

```cpp
template<class Value, class Pointer, class Reference>
struct BaseTreeIterator : virtual public BaseIterator<Value, Pointer, Reference>
{
	typedef typename BaseIterator<Value, Pointer, Reference>::link_type link_type;
	typedef BaseTreeIterator<Value, Pointer, Reference> self;
	typedef BaseIterator<Value, Pointer, Reference> Base;

	BaseTreeIterator(link_type ptr) : BaseIterator<Value, Pointer, Reference>(ptr) {}
	BaseTreeIterator(const self& obj) : BaseIterator<Value, Pointer, Reference>(obj) {}

	Reference operator*()
	{
		return Base::_ptr->_value;
	}

	self& operator++()
	{
		Base::increment();
		return *this;
	}

	self& operator--()
	{
		Base::decrement();
		return *this;
	}
};
```

正向迭代器和反向迭代器的相同内容都被写到了基迭代器中，基迭代器是个抽象类，为需要重写的成员函数规定了标准接口，正反向迭代器以继承方式实现

```cpp
template<class Value, class Pointer, class Reference>
struct BaseIterator
{
	typedef Value value_type;
	typedef BaseTreeNode<value_type> Node;
	typedef Node* link_type;
	typedef BaseIterator<Value, Pointer, Reference> self;

protected:
	link_type _ptr;

public:
	BaseIterator(link_type ptr) :_ptr(ptr) {}
	BaseIterator(const self& obj) :_ptr(obj._ptr) {}

	virtual Reference operator*() = 0;

	void swap(self& v1, self& v2)
	{
		std::swap(v1._ptr, v2._ptr);
	}


	self& operator=(const self obj)
	{
		swap(*this, obj);
		return *this;
	}

	Pointer operator->()
	{
		return &(this->operator*());
	}

	bool operator==(const self& obj)const
	{
		return this->_ptr == obj._ptr;
	}

	bool operator!=(const self& obj)const
	{
		return !(*this == obj);
	}

	void increment()
	{
		if (_ptr->_right)
		{
			// 右子树不为空
			// 下一节点是右子树的最左节点
			link_type curr = _ptr->_right;
			while (curr->_left) curr = curr->_left;
			_ptr = curr;
		}
		else
		{
			// 右子树为空
			link_type curr = _ptr;
			link_type parent = curr->_parent;
			// 如果当前树是上一级树的右子树
			// 就说明上一级树已经遍历完成
			while (parent && curr == parent->_right)
			{
				curr = parent;
				parent = curr->_parent;
			}

			// 来到这里 有两种情况
			// 
			// 已经没有上级树了 整棵树遍历完了
			// 
			// curr树的右子树已经遍历完了 中序为 左子树 根
			// 节点 右子树 右子树遍历完意味着curr已经遍历完了
			// 又curr是上级树的左子树 所以下一个节点就是父节点
			_ptr = parent;
		}
	}

	void decrement()
	{
		if (_ptr->_left)
		{
			// 左子树不为空
			// 下一节点是左子树的最右节点
			link_type curr = _ptr->_left;
			while (curr->_right) curr = curr->_right;
			_ptr = curr;
		}
		else
		{
			// 左子树为空
			link_type curr = _ptr;
			link_type parent = curr->_parent;
			while (parent && curr == parent->_left)
			{
				curr = parent;
				parent = curr->_parent;
			}
			_ptr = parent;
		}
	}

	virtual self& operator++() = 0;
	virtual self& operator--() = 0;
};
```

下面我们细说一下基树中的迭代器类型实例化

```cpp
typedef BaseTreeIterator<value_type, pointer, reference> iterator;
typedef BaseTreeIterator<value_type, const_pointer, const_reference> const_iterator;
```

众所周知，迭代器能对容器中的元素精细修改，是因为它返回了元素的引用或者指针，如果它用的就是普通的引用和指针，那元素是否能修改就要看`set`和`map`层所传入的`Value`是怎样的，如果用的是常指针和常引用，那就一定无法修改元素，因为常指针和常引用已经对`Value`加了一层`const`了，所以是一定改不了元素的。

对于`set`来说，它的元素就是`key`，就是不能被更改的，所以它的迭代器就是基树中的常迭代器。

```cpp
template<class Key, class cmp =  Less<Key>>
class set
{
	struct KeyOfValue
	{
		const Key& operator()(const Key& value)
		{
			return value;
		}
	};

	typedef Key value_type;
	typedef BaseTree<Key, value_type, KeyOfValue, cmp> BaseTree;
	typedef typename BaseTree::const_reference const_reference;
public:
	typedef typename BaseTree::const_iterator iterator;
	typedef typename BaseTree::const_iterator const_iterator;
	typedef typename BaseTree::const_reverse_iterator reverse_iterator;
	typedef typename BaseTree::const_reverse_iterator const_reverse_iterator;
	
private:
	typedef std::pair<iterator, bool> ret_type;

public:

	ret_type insert(const_reference value)
	{
		return _Container.insert(value);
	}

	iterator begin()const
	{
		return _Container.begin();
	}

	iterator end()const
	{
		return _Container.end();
	}

	reverse_iterator rbegin()const
	{
		return _Container.rbegin();
	}

	reverse_iterator rend()const
	{
		return _Container.rend();
	}

private:
	BaseTree _Container;
};
```

我们先只看`set`，而不关心`map`，此时还有一个很关键的地方需要进行修改，那就是基树中的`insert`，为什么呢？因为`set`的普通迭代器和常迭代器其实都是基树的常迭代器，而基树的`insert`所返回`pair`第一个成员类型是普通迭代器，在`set`层的`insert`中，`_Container.insert(value)`返回的是`pair<BaseTree::iterator, bool>`而`set::insert`的返回类型是`pair<Base::const_iterator, bool>`，由于`iterator`无法变为`const_iterator`，所以会无法通过编译，为了解决这个问题，我们需要对`BaseTree::insert`的返回值类型进行修改，怎么修改呢？我们可以把`pair<iterator, bool>`变成`pair<link_type, bool>`，因为`link_type`既可以构造出普通迭代器也可以构造出常迭代器，所以就解决了这个类型不匹配的问题。

`pair`之所以能这样做，是因为它有一个非常巧妙的构造函数，这个构造函数是用模版形式写成的，所以它对类型的要求并不是特别严格

```cpp
template<class U, class V> 
pair (const pair<U,V>& pr)
    :first(pr.first)
    ,second(pr.second)
    {}
```

此时`BaseTree::insert`返回的是`pair<link_type, bool>`，而我们需要的是`pair<set::iterator, bool>`，此时就相当于会实例化出这种函数

```cpp
pair<set::iterator, bool> (const pair<link_type, bool>)
	:first(pr.first)
     ,second(pr.second)
    {}
```

`bool`类型当然可以初始化`bool`类型，关键是`link_type`可以初始化`set::iterator`或者说`BaseTree:const_iterator`，所以就可以解决这个问题，并且，这种解决方案也是可以适配`map`的。

接下来我们看看`map`，`map`怎么做到普通迭代器第一个不可修改，第二个可以修改呢？`map`可以在`BaseTree`的实例化参数上做手脚，我们可以直接把`pair<const key, value>`传进去，这样即使是普通迭代器，索引出的`Value_type`仍旧是`pair<const Key, value>`，所以改不了第一个成员，但改得了第二个成员。

![image-20241222190542956](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241222190543210.png)

至于常迭代器，相当于索引出的类型是`const pair<const Key, Value>`，整个`value_type`是完全不能修改的，自然满足常迭代器的要求。

上文所说的`pair`构造函数在`map`中也有体现，让我们来看看`map::insert`

```cpp
ret_type insert(const_reference value)
{
	return _Container.insert(value);
}
```

这里的`const_reference`是从`BaseTree`中取出的类型，具体来说，是`const pair<const Key, Value>&`，但我们在外面调用的时候，其实也可以插入`pair<Key, Value>`，而不会引发类型冲突，所以`pair`的这个构造写的非常好，巧妙的解决了不少事。

反向迭代器就不细说了，我们上面说的树是不带头结点的树，不带头节点的树反向迭代器实现起来稍微有些不优雅，其实也并不是很难，大概是这样的，下面的代码不是我写的，是从别的地方复制过来的。

```cpp
// 假设 RBTree 是一个红黑树容器模板类
template<class K,class T,class KeyOfT>
class RBTree {
public:
    // ... 其他成员和方法 ...

    // 迭代器类型别名
	typedef RBTreeIterator<T, T*, T&> iterator;
	typedef ReverseIterator<iterator> reverse_iterator;

    // 获取指向容器中第一个元素的迭代器
    iterator begin() {
       		Node* subL = _root;
		while (subL && subL->_left) {
			subL = subL->_left;
		}
		return iterator(subL);
    }

    // 获取指向容器末尾之后位置的迭代器
    iterator end() { return nullptr; }
    
    reverse_iterator rbegin(){
		Node* right = _root;
		while (right && right->_right){
			right = right->_right;
		}
		return reverse_iterator(iterator(right));
	}
	reverse_iterator rend(){
		return reverse_iterator(iterator(nullptr));
	}
    
    //end()  rbegin()在使用时存在缺陷。
    // ... 其他成员和方法 ...
};
————————————————

版权声明：本文为博主原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接和本声明。
                        
原文链接：https://blog.csdn.net/weixin_73494835/article/details/137021821
```

我们来看STL源代码怎么写的

![image-20241222193036190](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241222193036344.png)

原码写的非常对称，`rbegin`直接复用`end`，`rend`直接复用`begin`，STL凭什么这样写呢？因为它用的树和我们之前说的树有些小区别，STL的树是带头结点的，而我们上面的树没有带头结点，所以如果想做到这么对称就比较困难，所以我把项目进行了一定程度上的优化，把树改成了带有头结点的树，而且在分析源代码思路的时候，我看到了很多内联函数，这些内联函数将重复的代码细节进行了小范围的封装，这样用起来，除非名字打错了，否则就不容易出错，可能本来向写`node->left`的，然后不知道怎么写成了`node->right`，就可以避免这种错误，而且代码可读性也有了一定的提升。

对于有头结点的树来说，有几处小细节略微发生了变化，头结点的`_left`字段指向树的最左节点，`_right`字段指向树的最右节点，`_parent`指向树的根节点，树根节点的`parent`也要指向`_head`，为了快速更改，我直接把原来的`_root`变成了`_head->_parent`的引用，这样就不用进行太大范围的更改，在每次插入之后，要对`_head->_left`和`_head->_right`进行修正，旋转的时候，如果根节点发生了变化，也要记得让新的根节点`_parent`指向`_head`，然后就行了。

反向迭代器模版如下

```cpp
template<class Value, class Pointer, class Reference>
struct BaseTreeReverseIterator : virtual public BaseIterator<Value, Pointer, Reference>
{
	typedef typename BaseIterator<Value, Pointer, Reference>::link_type link_type;
	typedef BaseTreeReverseIterator<Value, Pointer, Reference> self;
	typedef BaseIterator<Value, Pointer, Reference> Base;

	BaseTreeReverseIterator(link_type ptr) : BaseIterator<Value, Pointer, Reference>(ptr) {}
	BaseTreeReverseIterator(const self& obj) : BaseIterator<Value, Pointer, Reference>(obj) {}

	Reference operator*()
	{
		self it = *this;
		++it;
		return it._ptr->_value;
	}

	self& operator++()
	{
		Base::decrement();
		return *this;
	}

	self& operator--()
	{
		Base::increment();
		return *this;
	}
};
```

不过我这里的正反向迭代器是继承实现了，所以不太好相互复用，但也是比较简洁的

```cpp
iterator begin()
{
	return iterator(left_most_node(_root));
}

iterator end()
{
	return iterator(_head);
}

reverse_iterator rbegin()
{
	return reverse_iterator(_head);
}

reverse_iterator rend()
{
	return reverse_iterator(left_most_node(_root));
}
```

到目前未知，我们似乎还没有遇到基树中对`Key`类型的使用，那能不能不传呢？不行，因为要是不传`Key`，`find`拿什么查呢？

```cpp
iterator find(const key_type& key)
{
	Less cmp;
	KeyOfValue Extract;
	link_type location = _root;
	link_type parent = nullptr;
	while (location)
	{
		parent = location;
		if(cmp(key, Extract(node_value(location))))
			location = node_left(location);
		else if(cmp(Extract(node_value(location)), key))
			location = node_right(location);
		else
			return iterator(location);
	}

	return end();
}
```

#  end