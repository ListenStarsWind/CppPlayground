# Binary Search Tree

## Concept

二叉搜索树，是二叉树的一种，由于二叉树的底层结构，其在数据存储方面表现并不好，但也正是由于它的特殊结构，使得其在数据处理方面有着不可替代的作用，本文所说的搜索二叉树正是二叉树最为基础的一种应用。

![image-20241123162417855](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411231624978.png)

另外需要特别说明一下：搜索二叉树中决不允许出现相同元素。

就如搜索树的名字，它在数据搜索方面有着极好的表现，与根节点相比，查找值较小，则进入左子树，较大，则进入右子树。另外搜索树若是采用中序遍历，也能直接获得升序序列。

![image-20241123163111826](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411231631025.png)

## Operation

下面是实操环节。

实现可以预想到在下面的环节中必然存在许多数据比较的场景，为了便于对之后的`cmp`进行统一管理，我们先写几个仿函数

```cpp
template<class T>
    class less
    {
        public:
        bool operator()(const T& v1, const T& v2)
        {
            return v1 < v2;
        }
    };

template<class T>
    class greater
    {
        public:
        bool operator()(const T& v1, const T& v2)
        {
            return v1 > v2;
        }
    };

template<class T>
    class same
    {
        public:
        bool operator()(const T& v1, const T& v2)
        {
            return v1 == v2;
        }
    };
```

接下来是`class Node`。对于搜索树来说，我们喜欢把其节点中保存的值称为“键值”，因此我们喜欢用`key`的首字母`K`作为类型代称。

```cpp
template<class K>
struct BSTreeNode
{
private:
	typedef BSTreeNode<K> self;
public:
	BSTreeNode* _left;
	BSTreeNode* _right;
	K _val;

	BSTreeNode(const K& val)
		:_left(nullptr)
		, _right(nullptr)
		, _val(val)
	{}
};
```

之后是`class BSTree`

```cpp
	template<class K>
	class BSTree
	{
		typedef BSTreeNode<K> Node;
         typedef BSTree<K> self;
		typedef less<K> Less;
		typedef greater<K> Greater;
		typedef same<K> Same;
        
	public:
		
	private:
		Node* _root = nullptr;
	};
}
```

我们就先不关心格式是否严谨了，也就是说我们不会太关心诸如构造析构这类默认函数，成员只有一个指针，还带了缺省值，使用编译器的默认构造是完全可行的，至于析构，内存泄露就泄露吧，因为上面也说了，这是二叉树最基本的应用，之后我们还会在搜索树的基础上加些别的东西，所以对于析构和迭代器之类的，我们都先不考虑。

首先我们写一个插入

```cpp
bool Insert(const K& key)
{
	if (_root == nullptr)
	{
		Node* p = new Node(key);
		_root = p;
		return true;
	}

	Less l;
	Greater g;

	Node* p = new Node(key);
	Node* parent = nullptr;
	Node* curr = _root;

	while (curr)
	{
		parent = curr;
		if (l(key, parent->_val))
		{
			curr = parent->_left;
		}
		else if (g(key, parent->_val))
		{
			curr = parent->_right;
		}
		else
		{
			delete p;
			return false;
		}
	}

	if (l(key, parent->_val))
	{
		parent->_left = p;
	}
	else
	{
		parent->_right = p;
	}

	return true;
}
```

对于搜索树来说，数据的插入是非常简单的。当根节点为空时，我们要特殊处理，直接把数据挂载到`_root`上即可。至于其它情况，只需要依据搜索树的特性，为插入的数据找个合适的地方，再插入即可。搜索树中不能有相同元素，所以一旦遇到，就要视为失败。

不过由于树状结构天然的嵌套结构，递归写法往往更简洁

```cpp
	bool InsertR(const K& key)
	{
		return _InsertR(key, _root);
	}

private:

	bool _InsertR(const K& key, Node*& root)
	{
		if (root == nullptr)
		{
			Node* p = new Node(key);
			root = p;
			return true;
		}

		Less l;
		Greater g;
		
		if (l(key, root->_val))
			return _InsertR(key, root->_left);
		else if (g(key, root->_val))
			return _InsertR(key, root->_right);
		else
			return false;
	}
```

首先对于递归来说，需要传递根节点指针，有两种解决方案，一种是专门设计一个结构为用户返回根节点指针，由用户传参，但这会影响类的封装，本来`_root`放在私有里就是不想让外界知道的，现在却专门写个接口传出去，不是很好；所以更多是采用上述代码的形式，把递归套在一个非递归接口里，然后由这个非递归接口传递`_root`。另外需要注意的是，`Node*`使用引用是这份代码的精髓，这意味这`root`是父节点中`_left`或者`_right` 的引用，所以第十三行`root = p`也会对上一层父节点的索引进行修改。至于具体的递归逻辑，也是很清晰的：若`key`less`root->_val`，则证明其应该插入到左子树里面，反之，则应该插入右子树中，当然，相等一样返回假。

插入写好了，那就需要写个遍历看看效果，上面说过，我们先不考虑迭代器，所以中序遍历就是直接写的。

```cpp
	std::vector<K> InOrder()
	{
		std::vector<K> v;
		_InOrder(v, _root);
		return v;
	}

private:

	void _InOrder(std::vector<K>& v, Node* root)
	{
		if (root == nullptr)
			return;

		_InOrder(v, root->_left);
		v.push_back(root->_val);
		_InOrder(v, root->_right);
	}
```

这个就不写非递归了。

接着是查找，同样分为非递归和递归两种

```cpp
bool Find(const K& key)
{
	Node* curr = _root;

	Less l;
	Greater g;

	while (curr)
	{
		if (l(key, curr->_val))
			curr = curr->_left;
		else if (g(key, curr->_val))
			curr = curr->_right;
		else
			return true;
	}

	return false;
}
```

```cpp
	bool FindR(const K& key)
	{
		return _FindR(key, _root);
	}

private:

	bool _FindR(const K& key, Node* root)
	{
		if (root == nullptr)
			return false;

		Less l;
		Greater g;

		if (l(key, root->_val))
			return _FindR(key, root->_left);
		else if (g(key, root->_val))
			return _FindR(key, root->_right);
		else
			return false;
	}
```

现在我们讨论一下查找的时间复杂度，首先需要注意的是，我们这里的搜索树是普通的二叉树，它在绝大多数情况下都不是完全二叉树或者满二叉树，或者说，它的左右子树不是均衡的，可能一边多一边少，所以查找的复杂度不是$log_2N$，而是$N$，光看这个$N$可能有些抽象，所以可以看这张图

![image-20241127102935725](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411271029826.png)

相比二叉树，这个搜索树长得更像链表，此时查找的复杂度不就是$N$吗？

所以说我们这里学的只是最基础的搜索树，之后我们会学习平衡搜索树，所谓平衡搜索树就是它会自平衡，自动调整成近似于完全二叉树的那种样子。

至于删除，则有不少地方要说的。删除要考虑到两件事，一是被删除节点与父节点的链接关系，而是被删除节点与子节点的链接关系，我们以后者为切入点，一个节点的子节点无非就几种情况：没有子节点，有一个子节点，有两个子节点，对于这些情况我们要分别考虑。

首先就是一个子节点都没有的情况，这意味着该节点就是一个叶节点，叶节点很好删除，只要把父节点上的对应链接置为`nullptr`即可，随后再`delete`这些节点。

有一个子节点分为两种情况，一是子节点在左边，二是子节点在右边，这其实也好解决，由于它此时只有一个子树，所以直接把子节点转交给父节点，顶替自己的位置就行了；不过需要注意的是，当被删除的节点就是根节点时，就意味着它没有父节点，因此需要特殊处理，直接把子节点指针赋给`_root`即可。

有两个子节点是最为复杂的情况，我们使用替换法来解决这个问题，简而言之就是再找一个`target`，让`target`中的值与被删除节点中的值交换数据，最终删除的是`target`。那`target`的选择标准是什么呢？就像在一般情况下，政府进行选举时，总是温和派获得更多票数，毕竟正常情况下绝大多数人的政治倾向都不是特别极端，所以温和派能获得更多民众的支持，更温和的政府越不容易出现激进行为，主打一个尽量不犯错，极端派们也有妥协余地，这种温和政府在国家不面临什么巨大挑战的时候还是不错的。我们的`target`也是如此，我们要以被删除`_val`为标准，找到一个最温和的充当下一节政府领导人。怎么找呢？对于选举人来说，可能是在极左里面找极右，在极右里面找极左，对于搜索树来说，也是如此，当我们锁定了那个存储着需要被删除数据的节点时，我们可以去它的左子树里面找最右边的节点，怎么找呢？我们先进入左子树，然后不断地向着当前节点的右子节点迭代，如果当前节点的右子节点为空，那就说明找到了，而且这种方式找到的`target`也肯定是只有一边或者两边都没有子树，这样我们同样在数据交换之后，直接把`target`的父节点链接到子树上，然后就可以删除自身了；在下面的代码中，我们是在右子树里面找最左的节点。这里还需要注意的是，它有可能都不会在子树中进行迭代，在下面的代码中就是没有进入循环`while (target->_left)`就找到了，此时就要特别处理。

另外去要说明的是，没有子节点和只有一个子节点其实可以合并来写。

```cpp
bool Erase(const K& key)
{
	Node* curr = _root;
	Node* parent = _root;

	Less l;
	Greater g;
	Same s;

	while (!s(key, curr->_val))
	{
		parent = curr;

		if (l(key, curr->_val))
			curr = curr->_left;
		else
			curr = curr->_right;
		
		if (curr == nullptr)
			return false;
	}

	if (curr->_left == nullptr)
	{
		if (curr == _root)
		{
			Node* die = _root;
			_root = curr->_right;
			delete die;
			return true;
		}

		if (l(key, parent->_val))
			parent->_left = curr->_right;
		else
			parent->_right = curr->_right;

		delete curr;
		return true;
	}
	else if (curr->_right == nullptr)
	{
		if (curr == _root)
		{
			Node* die = _root;
			_root = curr->_left;
			delete die;
			return true;
		}

		if (l(key, parent->_val))
			parent->_left = curr->_left;
		else
			parent->_right = curr->_left;

		delete curr;
		return true;
	}
	else
	{
		parent = curr;
		Node* target = parent->_right;

		while (target->_left)
		{
			parent = target;
			target = target->_left;
		}

		if (target == parent->_right)
		{
			std::swap(target->_val, curr->_val);
			curr->_right = target->_right;
		}
		else
		{
			std::swap(target->_val, curr->_val);
			parent->_left = nullptr;
		}

		delete target;
		return true;

	}
}
```

删除同样有递归版，使用`Node*`的引用同样是精髓，比如在第十八行，其中对`root`的修改实际上也会修改上一级栈帧中的`root->_left or root->_right`，`EraseR`在此就省略了。

```cpp
bool _EraseR(const K& key, Node*& root)
{
	if (root == nullptr)
		return false;

	Less l;
	Greater g;

	if (l(key, root->_val))
		return _EraseR(key, root->_left);
	else if (g(key, root->_val))
		return _EraseR(key, root->_right);
	else
	{
		if (root->_left == nullptr)
		{
			Node* die = root;
			root = root->_right;

			delete die;
			return true;
		}
		else if (root->_right == nullptr)
		{
			Node* die = root;
			root = root->_left;

			delete die;
			return true;
		}
		else
		{

			Node* parent = root;
			Node* target = parent->_right;

			while (target->_left)
			{
				parent = target;
				target = target->_left;
			}

			if (target == parent->_right)
			{
				std::swap(target->_val, root->_val);
				return _EraseR(key, root->_right);
			}
			else
			{
				std::swap(target->_val, root->_val);
				return _EraseR(key, root->_right);
			}
		}
	}
}
```

接下来的都是小操作。

下面是析构，使用后序递归的方式

```cpp
	~BSTree()
	{
		Destroy(_root);
		_root = nullptr;
	}

private:

	void Destroy(Node* root)
	{
		if (root == nullptr)
			return;

		Destroy(root->_left);
		Destroy(root->_right);
		delete root;
	}
```

下面是拷贝构造，使用前序递归的方式

```cpp
	BSTree(const self& obj)
	{
		_root = Copy(obj._root);
	}

private:

	Node* Copy(const Node* root)
	{
		if (root == nullptr)
			return nullptr;

		Node* newRoot = new Node(root->_val);
		newRoot->_left = Copy(root->_left);
		newRoot->_right = Copy(root->_right);

		return newRoot;
	}
```

需要注意的是，由于我们之前使用的是编译器生成的默认构造，所以当我们写了一个构造函数之后，编译器就不会自动生成了，为了解决这个问题，我们可以自己写一个空构造，也可以使用关键字`default`向编译器强调继续使用之前那个自动生成的默认构造。

```cpp
BSTree() = default;
```

赋值重载就用现代写法了。

```cpp
self& operator=(self obj)
{
	std::swap(_root, obj._root);
	return *this;
}
```

## Application

下面说说搜索树的应用场景。

上面我们实现的搜索树是最最基本的搜索树，我们把这种模型称之为`key`模型，该模型的特点先在搜索树中录入一系列的关键值，之后输入某个值，检查该值是否是搜索树里的关键值。我们拿门禁系统为例，早期图像识别技术还不普及的时候，可能更多的是靠刷卡的形式通过门禁的。比如，对于学生来说，会有自己的校园卡，校园卡中的存储介质存储了某个标识符，每个标识符都指定了一个学生。在门禁系统正式使用前，我们先把所有学生的标识符录入到搜索树中，刷卡的时候，读取卡里面的标识符，然后在搜索树中进行查找，找到了就放人进入，找不到另当别论。

除此之外，还有一个`key-value`模型，对于该模型来说，它插入的是一对数，一个是`key`，一个是`value`，这样就可以做到两种事情，一是查找搜索树中是否存在某个特定的`key`，二是通过搜索树中已经存在的`key`去查找其对应的`value`，也就是说`key-value`建立了某种映射关系。

现在我们在上面`key`模型搜索树的基础上写一下`key-value`模型搜索树，实现一个简单的翻译器。

```cpp
namespace KV_model
{
	template<class Key, class Value>
	struct BSTreeNode
	{
	private:
		typedef BSTreeNode<Key, Value> self;
	public:
		BSTreeNode* _left;
		BSTreeNode* _right;
		Key _key;
		Value _value;

		BSTreeNode(const Key& key, const Value& value)
			:_left(nullptr)
			, _right(nullptr)
			, _key(key)
			,_value(value)
		{}

	};

	template<class Key, class Value, class Less = less<Key>, class Greater = greater<Key>, class Same = same<Key>>
	class BSTree
	{
		typedef BSTreeNode<Key, Value> Node;
		typedef BSTree<Key, Value, Less, Greater, Same> self;
		typedef std::vector<Key> Keys_Returning_Container;
		typedef std::vector<Node> Complete_Mapping_Returning_Container;
		typedef Keys_Returning_Container Keys_Ret;
		typedef Complete_Mapping_Returning_Container Mapping_Ret;
		
	public:
		bool Insert(const Key& key, const Value& value)
		{
			if (_root == nullptr)
			{
				Node* p = new Node(key, value);
				_root = p;
				return true;
			}

			Less l;
			Greater g;

			Node* p = new Node(key, value);
			Node* parent = nullptr;
			Node* curr = _root;

			while (curr)
			{
				parent = curr;
				if (l(key, parent->_key))
				{
					curr = parent->_left;
				}
				else if (g(key, parent->_key))
				{
					curr = parent->_right;
				}
				else
				{
					delete p;
					return false;
				}
			}

			if (l(key, parent->_key))
			{
				parent->_left = p;
			}
			else
			{
				parent->_right = p;
			}

			return true;
		}

		Mapping_Ret InOrder()
		{
			Mapping_Ret v;
			_InOrder(v, _root);
			return v;
		}

		Node* Find(const Key& key)
		{
			Node* curr = _root;

			Less l;
			Greater g;

			while (curr)
			{
				if (l(key, curr->_key))
					curr = curr->_left;
				else if (g(key, curr->_key))
					curr = curr->_right;
				else
					return curr;
			}

			return nullptr;
		}

		bool Erase(const Key& key)
		{
			return _Erase(key, _root);
		}

		~BSTree()
		{
			Destroy(_root);
			_root = nullptr;
		}

		BSTree(const self& obj)
		{
			_root = Copy(obj._root);
		}

		BSTree() = default;

		self& operator=(self obj)
		{
			std::swap(_root, obj._root);
			return *this;
		}

	private:

		Node* Copy(const Node* root)
		{
			if (root == nullptr)
				return nullptr;

			Node* newRoot = new Node(root->_key);
			newRoot->_left = Copy(root->_left);
			newRoot->_right = Copy(root->_right);

			return newRoot;
		}

		void Destroy(Node* root)
		{
			if (root == nullptr)
				return;

			Destroy(root->_left);
			Destroy(root->_right);
			delete root;
		}

		bool _Erase(const Key& key, Node*& root)
		{
			if (root == nullptr)
				return false;

			Less l;
			Greater g;

			if (l(key, root->_key))
				return _Erase(key, root->_left);
			else if (g(key, root->_key))
				return _Erase(key, root->_right);
			else
			{
				if (root->_left == nullptr)
				{
					Node* die = root;
					root = root->_right;

					delete die;
					return true;
				}
				else if (root->_right == nullptr)
				{
					Node* die = root;
					root = root->_left;

					delete die;
					return true;
				}
				else
				{
					Node* parent = root;
					Node* target = parent->_right;

					while (target->_left)
					{
						parent = target;
						target = target->_left;
					}

					if (target == parent->_right)
					{
						std::swap(target->_key, root->_key);
						return _Erase(key, root->_right);
					}
					else
					{
						std::swap(target->_key, root->_key);
						return _Erase(key, root->_right);
					}
				}
			}
		}

		void _InOrder(Mapping_Ret& v, Node* root)
		{
			if (root == nullptr)
				return;

			_InOrder(v, root->_left);
			v.push_back(*root);
			_InOrder(v, root->_right);
		}

		Node* _root = nullptr;
	};
}
```

大体上都是一样的，只有几个小细节需要修改，例如`class Node`，`Insert`，`Find`，这里由于我们要看一下`key`对应的`value`，所以需要返回节点指针，如果返回值为空，意味着找不到，返回值不为空，相当于查找对应的`value`。

![image-20241127141506308](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411271415504.png)

结束程序有两种办法，一是直接终止进程，也就是`Ctrl C`，二是`Ctrl Z`加`Enter`。

接下来换一个场景，提供一个字符串数组，统计里面词汇的出现个数

```cpp
void test3()
{
	// 统计水果出现的次数
	string arr[] = { "苹果", "西瓜", "苹果", "西瓜", "苹果", "苹果", "西瓜",
	"苹果", "香蕉", "苹果", "香蕉" };
	wind::KV_model::BSTree<string, int> countTree;
	for (const auto& str : arr)
	{
		auto ret = countTree.Find(str);
		if (ret == nullptr)
		{
			countTree.Insert(str, 1);
		}
		else
		{
			ret->_value++;
		}
	}
	auto ret = countTree.InOrder();
	for (const auto& e : ret)
	{
		cout << e._key << "::" << e._value << endl;
	}
}
```

![image-20241127144056475](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411271440571.png)

当然，这里我们如果有需求，最好自己重新设计一下小于大于等于，中文`string`的大小比较取决于它们的编码模式。

## Title

之后，我们主要是找些题目做。

### [preorder traversal](https://leetcode.cn/problems/construct-string-from-binary-tree)

![image-20241127151429609](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411271514721.png)

题目的要求是输出一个字符串，利用该字符串可以很轻松地重构出对应的二叉树。它所采用的遍历方式是前序遍历。

对于示例二来说，首先是节点的值，所以`str += '1'`，接着要遍历`[1]`的子树，所以`str += '('`，子树根节点是`2`，所以`str += '2'`，接着遍历`[2]`的子树，所以`str += '('`，结果子树是空的，子树遍历结束，所以`str += ')'`，接着准备遍历`[2]`的另一个子树，所以`str += '('`，子树根节点是`4`，所以`str += '4'`，接着准备遍历`[4]`的子树，所以`str += '('`，子树遍历完了，`str += ')'`，遍历另一个子树，`str += '('`，子树遍历完了，`str += ')'`，`[2]`的子树遍历完了，`str += ')'`，`[1]`的左子树遍历完了，`str += ')'`， 准备遍历`[1]`的另一个子树，`str += '('`，子树根为`3`，`str += '3'`，准备遍历`[3]`的子树，`str += '('`，遍历完了，`str += ')'`，遍历`[3]`的另一个子树，`str += '('`，遍历完了，`str += ')'`，`[1]`的有子树遍历完了，`str += ')'`，所以输出的初始字符串是`1(2()(4()()))(3()())`，但还需要处理，那些可以省略的空括号是要省略的，所以就变成了`1(2()(4))(3)`，如果右子树有内容，二左子树为空，此时左子树的`()`是不能省略的，否则会引起歧义，分不清到底是哪边的子树。

很明显，这道题用递归写起来非常容易，唯一需要考虑的地方是，怎么分辨出来哪些括号可以省，哪些不行。让我们来归纳总结一下：

- 先考虑左子树括号

  - 左为空，右为空，可以省
  - 左为空，右不空，不能省
  - 左不空，右为空，不能省
  - 左不空，右不空，不能省

  有结论了：只要有一边不为空，那就不能省

- 再考虑右子树括号

  - 右为空，可以省
  - 右不空，不能省

所以就好写了，前序遍历，先把节点值写到字符串里，然后再尝试去左子树和右子树。

```cpp
class Solution {
public:
    void _tree2str(string& s, const TreeNode* root) {
        if (root == nullptr)
            return;

        s += to_string(root->val);

        if (root->left || root->right) {
            s += '(';
            _tree2str(s, root->left);
            s += ')';
        }

        if (root->right) {
            s += '(';
            _tree2str(s, root->right);
            s += ')';
        }
    }

    string tree2str(TreeNode* root) {
        string ret;
        _tree2str(ret, root);
        return ret;
    }
};
```

第一个`if`也可以从逻辑上考虑，如果左子树不为空，那肯定要加括号，如果左子树为空，那就不确定，需要再看看右子树，如果右子树也为空，那就可以省，不为空，那就不能省。

### [level order traversal-I](https://leetcode.cn/problems/binary-tree-level-order-traversal)

![image-20241127162050683](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411271620845.png)

之前在栈和队列中说过这道题，所以就略微说一下。

![image-20241127162326397](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411271623600.png)

定义两个`vector<Node*>`，一个容纳当前层的节点指针，另一个用来容纳下一层的节点指针，在一个个存储当前层节点值的同时，把节点的子树根节点指针引入下一层即可。

### [lowest-common-ancestor](https://leetcode.cn/problems/lowest-common-ancestor-of-a-binary-tree)

![image-20241127182956156](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411271829455.png)

首先说暴力破解。

很明显，题目中的二叉树只能往深处遍历，而不能回头，所以我们从根节点开始，一点一点地靠近`p`和`q`，看看有什么规律。
为了更明显的展示现象，我们使用示例中的二叉树，但输入的两个节点改成`[7]`和`[4]`。

从根节点`[3]`开始，我们可以直观的看到两个目标节点都位于根节点的左子树，所以我们来到`[5]`，接着我们发现两个目标节点都在`[5]`的右子树中，所以我们来到`[2]`。对于`[2]`来说，两个目标节点分别位于它的左右子树中，所以`[2]`就是它们的最近公共祖先。也就是说，对于某两个节点的最近公共祖先来说，这两个节点应该一个位于它的左子树中，一个位于它的右子树中。

不过我们还需考虑一点，那就是一个节点也可以是它自己的祖先。

比如仍旧是示例中的树，我们要找的两个节点是`[3]`和`[5]`。很明显，它们的最近公共祖先是`[3]`。

现在我们把两个节点定为`[2]`，`[7]`。还是采用逼近法，不断接近两个关键节点。我们发现，对于`[3]`和`[5]`来说，两个节点都位于当前根节点的左子树或者右子树中，但在下一次接近中，我们的根节点就是两个节点其中的一个节点。

```cpp
class Solution {
public:
    bool InTree(TreeNode* root, TreeNode* key) {
        if (root == nullptr)
            return false;

        if (root == key)
            return true;

        return InTree(root->left, key) || InTree(root->right, key);
    }

    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (root == p || root == q)
            return root;

        bool pInLeft = InTree(root->left, p);
        bool pInRight = !pInLeft;

        bool qInLeft = InTree(root->left, q);
        bool qInRight = !qInLeft;

        if (pInLeft && qInLeft)
            return lowestCommonAncestor(root->left, p, q);

        if (pInRight && qInRight)
            return lowestCommonAncestor(root->right, p, q);

        if ((pInLeft && qInRight) || (pInRight && qInLeft))
            return root;

        return nullptr;
    }
};
```

由于`p`和`q`必然位于二叉树中，所以当越过第一个`if`之后，它们必然要么在当前节点的左子树中，要么位于当前节点的右子树中，我们先在当前节点的左子树中寻找`p`，如果返回真，则意味着`p`位于当前节点的左子树中，如果是假，则意味着`p`位于当前节点的右子树中，也就是说，`pInLeft`和`pInRight`必然是互斥的，这对`q`也适用，接着如果它们位于当前节点的某一边，就接近它们继续迭代，如果分立在两边就是我们要找的最近公共祖先。

不过这种解法的时间复杂度有些堪忧。我们还是拿出这张图：

![image-20241127102935725](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411271029826.png)

题目中的二叉树并不标准，可能长得像链表一样，假如要寻找的是`[1]`和`[3]`。那么每轮寻找的复杂度就像是等差数列那样，也就是经典的$N^2$。

即使不算时间复杂度，光凭感觉也知道复杂度较高，可以很明显感觉到有很多搜索过程都是重合的。

所以接下来让我们看看另一个解法。

第二个解法其实就是直接解析出两个节点的绝对路径，然后直接用绝对路径找最近公共祖先。
那么，问题，来了该如何解析出二叉树中某个节点的绝对路径呢？

我们设计一个基于前序遍历的递归函数，这个函数的返回值为布尔类型，依据返回值决定递归是否继续进行。在递归开始前，前往该函数中输入一个空栈，作为存储路径的容器。

<img src="https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411271925722.png" alt="image-20241127192533520" style="zoom:200%;" />

还是示例中的二叉树。假如我们现在要解析出`[4]`的绝对路径。我们先把`[3]`入栈，因为它可能是绝对路径的一环，先去左子树，`[5]`不是关键节点，但先入栈，此时栈中的数据就是`[3], [5]`，接着继续去左子树，将`[6]`先入栈，`[6]`不是关键节点，继续去左子树，左子树为空，去右子树，右子树也为空，既然在`[6]`的左右子树中都没有关键节点，那就说明`[6]`不在绝对路径中，所以`[6]`出栈，`[5]`的左子树找完了，就该找右子树了，于是先将`[2]`入栈，接着去左子树，将`[7]`入栈，`[7]`的左右子树都没有关键节点，所以`[7]`就要出栈，接着去找`[2]`的右子树，先把`[4]`入栈，`[4]`就是关键节点，所以返回真，告诉上层栈帧们不需要继续遍历了，结束递归，这样我们就可以在那个栈中获得关键节点的绝对路径。

获得了两个关键节点的绝对路径后我们首先要把两个栈的大小统一，如果关键节点都在根节点的同一个子树中，那此时就可以返回栈顶了，但关键节点可能分立在根节点的两个子树中，所以还需要一轮循环找到相同的节点。

```cpp
class Solution {
public:
    bool _Path(TreeNode* root, TreeNode* key, stack<TreeNode*>& s) {
        if (root == nullptr)
            return false;

        s.push(root);

        if (root == key)
            return true;

        if (_Path(root->left, key, s))
            return true;

        if (_Path(root->right, key, s))
            return true;

        s.pop();

        return false;
    }

    stack<TreeNode*> Path(TreeNode* root, TreeNode* key) {
        stack<TreeNode*> s;
        _Path(root, key, s);
        return s;
    }

    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        stack<TreeNode*> p_path = Path(root, p);
        stack<TreeNode*> q_path = Path(root, q);

        while (p_path.size() != q_path.size()) {
            if (p_path.size() > q_path.size())
                p_path.pop();
            else
                q_path.pop();
        }

        while (p_path.top() != q_path.top()) {
            p_path.pop();
            q_path.pop();
        }
        
        return p_path.top();
    }
};
```

在此种情况下，处理路径的两个循环复杂度几乎可以忽略不计，复杂度都在路径解析过程中，即使是最极端的情况——两个节点都在前序遍历几乎进行完毕的情况下才找到，其复杂度也是$N$。

### [BST to sorted list](https://www.nowcoder.com/share/jump/9209693051732883567834)

![image-20241129203349401](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411292033554.png)

题目特别要求，空间复杂度是一，这意味着我们不能借助于任何中间容器，必须直接在二叉树的节点上该变指针索引。

题目要求我们输出一个有序的链表，这意味着这个链表的遍历顺序和搜索树的中序遍历顺序是相同的，所以我们就可以在中序递归的大框架下进行节点指针的改变，我们在每个节点中有两个指针需要改变，`left`应该指向链表的上一节点，而`right`应该指向链表的下一节点，不过由于链表的遍历顺序与中序遍历顺序相同，所以我们就可以把问题转化一下：`left`指向中序遍历的上一节点，而`right`指向中序遍历的上一节点，对于`left`的改变，很好想到，我们可以在递归函数中加入一个指针变量的引用，由于使用的是引用，所以该变量对所有函数栈帧都有效，当栈帧即将回归到上一层栈帧，或者说来到下一个中序遍历节点前，我们更新该变量，这样等到下一个节点就能通过该变量获取上一节点的指针，这样就可以把相邻顺序的节点建立联系，为了方便称呼，我们就把这个变量叫做`prev`，最开始的节点，也就是`[4]`，前面并没有其它节点，所以`prev`的初始值就是`nullptr`，由于`[4]`没有上一节点，所以自然不用将上一节点的`right`指向现在的节点，之后对`prev`进行更新，将当前节点的指针赋给它，这样，等到遇到下一个中序遍历节点的时候，让`left = prev`即可，接着，如果有上一个节点，那就让上一节点的`right`指向本节点即可。

```cpp
class Solution {
  public:
    void _Convert(TreeNode* curr, TreeNode*& prev) {
        if (curr == nullptr)
            return ;

        _Convert(curr->left, prev);

        curr->left = prev;
        if (prev)
            prev->right = curr;
        prev = curr;

        _Convert(curr->right, prev);

    }

    TreeNode* Convert(TreeNode* pRootOfTree) {
        TreeNode* prev = nullptr;
        _Convert(pRootOfTree, prev);

        TreeNode* ret = pRootOfTree;
        while (ret && ret->left)
            ret = ret->left;

        return ret;
    }
};
```

### [Build tree from preorder and Inorder](https://leetcode.cn/problems/construct-binary-tree-from-preorder-and-inorder-traversal)

![image-20241130163700220](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411301637323.png)

这道题仍旧使用分治的思想。我们的主要思路就是用前序遍历一个个地确定根节点，用中序遍历区分左右子树。第一个前序节点`[3]`，当然是根节点，然后依据`[3]`，就可以把中序遍历分成两个部分：`[9]`和`[15, 20, 7]`，`[9]`就是`[3]`左子树的中序遍历，而`[15, 20, 7]`就是`[3]`右子树的中序遍历。

等到我们已经把`[3]`这个节点构建出之后，就可以构建`[3]`的左子树和右子树，这样就可以把问题分而治之。

为了能控制当前栈帧根节点的位置，我们需要使用一个引用变量，每确定一个根节点值后，都向后迭代一次，另外，我们还需要两个值控制一下当前栈帧对应树的中序遍历区间，当这个区间非法时，即说明当前节点下面没有子树了，可以回归了。

```cpp
class Solution {
public:
    TreeNode* _buildTree(const vector<int>& preorder, const vector<int>& inorder, int& root_pos, int inbegin, int inend){
        if(inbegin > inend)
            return nullptr;
        
        int val = preorder[root_pos++];
        int partition = inbegin;
        while(partition <= inend && inorder[partition] != val)
            partition++;
        
        TreeNode* node = new TreeNode(val);
        node->left = _buildTree(preorder, inorder, root_pos, inbegin, partition - 1);
        node->right = _buildTree(preorder, inorder, root_pos, partition + 1, inend);
        return node;
    }
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        int pos = 0;
        return _buildTree(preorder, inorder, pos, 0, inorder.size() - 1);
    }
};
```

我们可以来分析一下，以示例一为例，最开始，我们指向的根节点位置为0，中序遍历区间是`[0, 4]`，我们找到的分割点是1，所以左子树的中序区间是`[0, 0]`，接着进入下一层调用，找到的分割点是0，这样左子树区间是`[0, -1]`，右子树的区间是`[1, 0]`，都是不合法的区间，这意味着下面没有子树了，所以返回······

### [Build tree from postorder and Inorder](https://leetcode.cn/problems/construct-binary-tree-from-inorder-and-postorder-traversal)

![image-20241130171028255](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411301710341.png)

```cpp
class Solution {
public:
    TreeNode* _buildTree(const vector<int>& inorder,
                         const vector<int>& postorder, int& root_pos,
                         int inbegin, int inend) {
        if (inbegin > inend)
            return nullptr;

        int val = postorder[root_pos--];
        int partition = inbegin;
        while (partition <= inend && inorder[partition] != val)
            partition++;

        TreeNode* node = new TreeNode(val);
        node->right =
            _buildTree(inorder, postorder, root_pos, partition + 1, inend);
        node->left =
            _buildTree(inorder, postorder, root_pos, inbegin, partition - 1);
        return node;
    }
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        int pos = postorder.size() - 1;
        return _buildTree(inorder, postorder, pos, 0, inorder.size() - 1);
    }
};
```

### [preorder](https://leetcode.cn/problems/binary-tree-preorder-traversal)

![image-20241130172733354](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411301727441.png)

分治算法可以通过递归或非递归的方式实现。递归的实现方式相比非递归更为直观清晰，但递归有栈溢出的风险，因此我们需要了解如何使用非递归的方式实现同样的功能。

为了更好地理解，我们先来看一下使用非递归方式实现前序遍历的代码。由于之前我们已经通过递归实现过前序遍历，从整体思想上来说，我们已经大致了解了分治的思路。因此，在这里我们直接给出代码：

```cpp
class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        stack<TreeNode*> save;
        vector<int> ret;
        while (!save.empty() || root) {
            save.push(root);
            ret.push_back(root->val);
            root = root->left;

            while (root == nullptr && !save.empty()) {
                TreeNode* node = save.top();
                save.pop();
                root = node->right;
            }
        }
        return ret;
    }
};
```

在递归中，我们通过每个栈帧对函数参数的修改，将一个大问题逐步分解为多个小问题——前序遍历一棵树就是：存储根节点 + 前序遍历左子树 + 前序遍历右子树。递归给人的感觉是，我们先深入走，直到无法再深入时回头，如果回头后发现有新的路径可以继续深入，就继续前行。递归能够在回头时继续深入，是因为之前的栈帧还存在，其中存储的局部数据依然有效，这使得它能像系统还原一样“回档”，恢复到之前的状态。在我们使用电脑进行一些高风险操作时，往往会先创建一个系统还原点，就像游戏中的存档一样，这样在出现问题时可以恢复到之前的状态。

对于非递归的实现，我们必须找到一种方法来保存每次循环中的关键数据，以便在需要时恢复到之前的状态。最常用的存储方法就是栈，因为栈具有先进后出的特性，能够帮助我们自然地沿着之前的路径回到某个节点，然后再换个方向继续深入。

接下来，我们讨论一下两个循环。外层循环相当于递归中的每一层栈帧，它的作用类似于递归的边界条件：当栈为空时，意味着没有更多的路径可以遍历，或者说，之前的状态已经没有可以恢复的存档。而`root`则代表着当前需要遍历的树的根节点，相当于递归中的参数。如果`root`不为空，说明我们还能继续深入遍历。如果`root`为空且栈也为空，那么说明我们已经遍历了所有可能的路径，并且没有更多的“存档点”，这时就可以结束遍历了。

外层循环里面的内容，就相当于递归中每个函数栈帧的内容，它们负责存档关键状态数据，状态调整，以及满足需求。每次循环都是一次新的开始，所以要存储一下关键数据`root`，方便之后我们回来，先序是先读节点值，所以我们立刻存储一下节点中的值，接着把`root`调整为左子树的根节点，于是下轮循环就变成了对左子树进行先序遍历，当左子树为空时，就需要回归，所以我们读一下之前存储的关键数据，回到之前的状态，接着，再把`root`调整为右子树的根节点，这意味着，下一次循环的目的是对右子树进行前序遍历。

至此，我们就完成了非递归实现的分治过程，既能深入，也能回归。

### [inorder](https://leetcode.cn/problems/binary-tree-inorder-traversal)

![image-20241130185150547](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411301851635.png)

与前序思路及形式几乎完全相同，在此不作说明

```cpp
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        stack<TreeNode*> save;
        vector<int> ret;
        while (!save.empty() || root) {
            save.push(root);
            root = root->left;
            while (root == nullptr && !save.empty()) {
                TreeNode* node = save.top();
                save.pop();
                ret.push_back(node->val);
                root = node->right;
            }
        }
        return ret;
    }
};
```

### [postorder](https://leetcode.cn/problems/binary-tree-postorder-traversal)

![image-20241130185432261](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411301854353.png)

后序和前序以及中序有些不太一样，整体思路确实相同，但有些细节需要借助于一些额外手段才能实现。

哪里不太一样呢？在前序和中序阶段，我们读一次档就要删除它，但对于后序来说，我们要读两回档，在去往左子树的时候存档，在去往右子树的时候读档，右子树走完了，需要再回来读一次档，用来存储节点中的值，所以需要把握存档删除的时机，而且很明显，由于存档和读档是混合着来的，因为树状结构是天然嵌套的，它可能是读完档之后立刻存档，所以无法简单的通过一个标志位去管理删档时机。

怎么解决呢？实际很简单，一个标志位管理不过来就用一群标志位，每个节点都有自己对应的标志位，这样它们就不会互相干扰，然后我们就可以用这个标志位去控制读档之后的操作，是去右子树呢？还是删档呢？

你可以用其它类型的标志位，我这里用的是一个整型充当计数器，用来记录被读档的次数。

```cpp
class Solution {
public:
    struct Splitter {
        TreeNode* node;
        int count;
        Splitter(TreeNode* p) : node(p), count(0) {}
    };
    vector<int> postorderTraversal(TreeNode* root) {
        stack<Splitter> save;
        vector<int> ret;
        while (!save.empty() || root) {
            save.push(root);
            root = root->left;

            while (root == nullptr && !save.empty()) {
                Splitter& top = save.top();
                if (top.count == 0) {
                    root = top.node->right;
                    top.count = 1;
                } else {
                    ret.push_back(top.node->val);
                    save.pop();
                }
            }
        }
        return ret;
    }
};
```

还有一个更巧妙的方法。对于后序遍历来说，很明显，是右子树被遍历完了之后节点中的值才被存储，这种读档就属于要删除的一种，同样的，对于右子树的根节点来说，它也是如此，并且这两个过程是连着走的，是右子树根节点的值被存储后，紧接着，就是根节点的值被存储，如果我们能提前定义一个指针，把前一个被存储值的节点地址记下来，那就可以通过这个值来判断这是不是第二次读档。

![image-20241130212405308](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411302124403.png)

比如，单就这张图来说，那肯定是`[5]`的值被存储之后才回退到`[2]`的，如果我们创建一个指针，记录上一次被存储值的节点指针，当我们从`[5]`回退到`[2]`的时候，肯定要借助于栈把`[2]`的指针读出来，与此同时，现在指针`prev`还指向着上一个存储值的节点，也就是`[5]`，如果栈顶节点的`right`等于`prev`，则证明这次是为了从右子树回来而读档的，既然是从右子树回来的，那就证明接下来应该删除栈中`[2]`的存档，并存储节点中的值，以及重新更新`prev`。如果是从左子树回来的，那此时的`prev`应该指向的是左子树的根节点，也就是说`top->right != prev`，所以那就是第一次读档，不能删除。

`prev`最初应该设置为`nullptr`，因为此时还没有上一个节点的概念。

```cpp
class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        stack<TreeNode*> save;
        vector<int> ret;
        TreeNode* prev = nullptr;
        while(root || !save.empty())
        {
            while(root)
            {
                save.push(root);
                root = root->left;
            }

            TreeNode* top = save.top();
            // 如果右子树为空，那就不用再遍历右子树了，直接记录根节点值即可
            if(top->right == nullptr || top->right == prev)
            {
                save.pop();
                ret.push_back(top->val);
                prev = top;
            }
            else
            {
                root = top->right;
            }
        }
        return ret;
    }
};
```

# end