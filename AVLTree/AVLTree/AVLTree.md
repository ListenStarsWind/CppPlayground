# AVLTree

## concept

我们知道，搜索二叉树利用自身的树状结构来提高搜索效率。然而，搜索二叉树的结构受到插入数据顺序的影响，这导致树的形态并不标准，从而影响搜索效率。尤其当插入的数据接近有序时，搜索二叉树会逐渐退化成类似单链表的结构，导致树状结构的优势丧失。因此，我们需要一种机制，能够在插入新元素后自我调整搜索二叉树的结构，使其尽可能地接近完全二叉树，从而保证搜索效率。

1962年，俄罗斯数学家G.M. Adelson-Velskii和E.M. Landis提出了一种机制，使得搜索树能够自我平衡。为了纪念两位数学家，这种树被命名为AVL树，也就是我们今天学习的内容。

一棵AVLTree有以下特征：

- 它的左右子树都是AVLTree
- 左右子树高度之差(简称平衡因子)的绝对值不超过1(-1/0/1)  

![image-20241205165525501](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241205165525573.png)

AVL树通过使用高度来实现自我平衡，因此也被称为“高度平衡二叉树”。需要注意的是，这里的“高度”并不是形容词，而是指树的高度。在AVL树中，当平衡因子的绝对值不超过1时，树的左右子树高度大致相同，这使得节点能够尽可能均匀地分布在各个子树中。此外，有些情况下，左右子树无法完全均衡。例如，四个节点构成的二叉树，无论如何排列也不可能完全平衡，平衡因子的绝对值不小于1正是为了应对这种情况。

每个节点都有一个平衡因子，它描述了该节点左右子树的高度差。理论上，你可以选择左子树高度减去右子树高度，也可以选择右子树高度减去左子树高度，但在实际应用中，我们通常选择左子树高度减去右子树高度。平衡因子的核心作用是量化左右子树的高度差。通过这个差值的变化，我们可以获取节点及其左右子树高度的相对变化，从而进行自我检查，判断树是否依然符合AVL树的要求。

尽管理论上可以不使用平衡因子，但如果不使用，它意味着每次检查时都需要重新计算子树的深度，这会产生额外的计算开销，而且这些计算可能会有大量重复，从而浪费时间和资源。所以不推荐。

AVL树仍然是一种二叉树结构，但它的节点除了指向左右子树的指针外，还包含指向父节点的指针。这种设计使得AVL树能够方便地进行回溯遍历，进而为树的自我调整提供便利。在进行平衡调整时，能够从子节点向上遍历并检查每个父节点的平衡因子，确保整棵树在插入或删除节点后保持平衡。

## implement

接下来是实现阶段。我们首先搭建一个基本的搜索二叉树框架，然后在此基础上实现AVL树的核心功能——自我检查与自我调整。

```cpp
#pragma once

#include<utility>
#include<cassert>
#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<vector>

namespace wind
{
	template<class V>
	struct less
	{
		bool operator()(const V& val1, const V& val2)
		{
			return val1 < val2;
		}
	};

	template<class V>
	struct AVLTreeNode
	{
	private:
		typedef AVLTreeNode<V> self;
	public:
		self* _parent;
		self* _left;
		self* _right;
		int _balanceFactor; // 约定平衡因子是左子树深度减去右子树深度
		V _value;

		AVLTreeNode(const V& v)
			:_parent(nullptr)
			, _left(nullptr)
			, _right(nullptr)
			, _balanceFactor(0)
			, _value(v)
		{
		}
	};

	template<class K, class V, class cmp = less<K>>
	class AVLTree
	{
		typedef AVLTree<K, V, cmp> self;
		typedef K key_type;
		typedef V mapped_type;
		typedef std::pair<const key_type, mapped_type> value_type;
		typedef AVLTreeNode<value_type> Node;
		typedef cmp less;

		struct equivalent
		{
			// 如果val1 不小于 val2
			// 并且val2 不小于 val1
			// 则说明，它们相等
			bool operator()(const key_type& val1, const key_type& val2)
			{
				less l;
				if (!l(val1, val2) && !l(val2, val1))
					return true;
				else
					return false;
			}
		};

	public:

		// 先不考虑迭代器，因此我们还是返回布尔值
		bool Insert(const value_type& val)
		{
			// 第一个节点插入后必然是平衡的
			if (_root == nullptr)
			{
				Node* newNode = new Node(val);
				_root = newNode;
				return true;
			}

			// 节点插入
			less l;
			Node* location = _root;
			Node* parent = nullptr;
			while (location)
			{
				parent = location;
				if (l(val.first, location->_value.first))
					location = location->_left;
				else if (l(location->_value.first, val.first))
					location = location->_right;
				else
					return false;
			}

			location = new Node(val);
			location->_parent = parent;
			if (l(val.first, parent->_value.first))
				parent->_left = location;
			else
				parent->_right = location;

			// 更新平衡因子以及自我检查

            return true;
		}

	private:
		Node* _root = nullptr;
	};

}
```

让我们分析分析插入阶段如何更新平衡因子，还是拿这棵树为例

![image-20241205165525501](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241205165525573.png)

我们先说父节点的平衡因子更新策略。

鉴于我们的定位机制，可以肯定，新节点一定插入到了某个节点的子树上，而且这个子树在插入前还是空树，这意味着，新节点是叶节点，新节点的左右子树都是空子树，所以新节点的初始平衡因子就是0。

接着看亲代平衡因子，也就是父节点的平衡因子如何调整。既然新节点被插入到了父节点的一个空子树中，那么这个被插入的子树，其深度肯定是加一的，而另一个未被插入的子树，因为没有进行任何操作，其深度肯定是不变的，既然平衡因子是左子树深度减右子树，那么如果新节点插入的是左子树，那么被减数加一，所以其结果就会加一，如果新插入的是右子树，那就是减数加一，所以其结果就会减一。

比如在上面的图中，不过它的平衡因子似乎是右子树深度减去左子树深度，但我们代码中约定的是左子树减去右子树，没关系，道理都一样。假设我们定位到了`[8]`的左子树上，对于这种图来说，左子树深度是被减数，所以父节点的平衡因子需要减一，也就是变成0。而且我们还可以看到，父节点平衡因子从1变成0实际上就意味着新节点把那个较浅的子树给加了一个深度，所以`[8]`这棵树的深度还是不变的。同样的，如果父节点的平衡因子从-1变成了0，也意味着是把较浅的那颗树加了一个深度，`[8]`这棵树的深度并没有变化，既然`[8]`这棵树的深度没有发生变化，就自然意味着`[8]`的父节点，也就是`[7]`的平衡因子没有发生变化，我们不需要更新祖先节点的平衡因子。

还是这张图，现在假设我们定位到了`[9]`的右子树上，那么，由于在这张图中，右子树是被减数，所以`[9]`的平衡因子就发生了变化，从0变成了1，从0变成1的这个过程意味着新节点的插入打破了`[9]`原先左右子树的平衡状态，所以意味着`[9]`这棵树的深度必然发生了变化，增加了一个深度，同理，如果从0变成了-1，也意味着原先左右子树的平衡状态被打破了，所以深度加一，既然`[9]`这棵树的深度发生了变化，就自然会影响到`[9]`的父节点，即`[8]`上 ，接下来我们就要回溯祖先节点，对祖先节点的平衡因子进行调整。

回溯到`[8]`之后，我们发现，我们是从被减数的那个子树过来的，所以`[8]`的平衡因子就要加加，这样`[8]`的平衡因子就变成了2，这意味着`[8]`这棵树已经不是AVLTree了，所以我们接下来做的应该是对这棵树进行调整，调整完了再根据实际情况看看需不需要在往上回溯。

我们来个阶段总结。

如果新的节点插入了被减的子树上，那么父节点的平衡因子加加。
如果新的节点插入了减的子树上，那么父节点的平衡因子减减。

父节点的平衡因子调整后

如果父节点的平衡因子为0，说明父节点所领导的树高度不变，不用再往上回溯，可以`return`了
如果父节点的平衡因子为1或-1，说明父节点领导的树高度加一，需要往上回溯
如果父节点的平衡因子为2或-2，说明父节点所领导的树已经不是AVLTree了，先把这棵树调整之后，再视情况做其它操作

```cpp
// 更新平衡因子以及自我检查
while (parent) // 如果上面已经没有节点了，就说明整棵树已经被调整过了
{
	// 更新父节点平衡因子
	if (location == parent->_left)
		parent->_balanceFactor++;
	else
		parent->_balanceFactor--;

	if (parent->_balanceFactor == 0)
	{	
		// 当前树的高度不改变 跳出循环
		break;
	}
	else if (parent->_balanceFactor == 1 || parent->_balanceFactor == -1)
	{
		// 当前树的高度加一，影响了上级节点，进行回溯
		location = parent;
		parent = parent->_parent;
	}
	else if(parent->_balanceFactor == 2 || parent->_balanceFactor == -2)
	{
		// 这棵树已经不是AVLTree了，需要调整
	}
	else
	{
		// 理论上不存在的分支，如果进入，最起码可以说明平衡因子的更新存在问题
		assert(0);   // 直接自爆
	}
}
```

接下来我们看看如何调整

我们先看最简单的一种情况，现在我们有一棵AVLTree，如下

![image-20241206092537024](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241206092537090.png)

现在我们插入一个`[10]`

![image-20241206092659325](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241206092659438.png)

经过几轮回溯之后，当前的树已经不是AVLTree了，所以我们就需要调整，或者说，旋转

我们知道AVLTree的目的是让树尽可能均衡，现在这棵树中序遍历的顺序是8,9,10，那我们让中序遍历的中间节点做新的根节点就行了

![image-20241206093548952](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241206093549008.png)

就比如，这棵树代表一个国家，而政治是妥协的艺术，有些人可能是改革派，有些人可能是保守派，整棵树的根节点要相对中立，把人们团结起来，国家才会更好。

接下来我们看看更复杂的情况

![image-20241206094515506](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241206094515570.png)

现在我们插入一个`[20]`

![image-20241206094632522](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241206094632583.png)

现在右派似乎有些多了，看来我们的政府需要稍微往右走走，所以现在的`[9]`就要下台了，我们把`[15]`选为新的政府领导人，为了让`[9]`下台的时候少点怨言，我们把`[15]`的左子树，也就是右派中和左派关系更亲的子树分配给`[9]`，这样`[15]`才更容易上台，“既然`[9]`已经收了我`[15]`的好处了，那你下去之后就不要拦着我做事，要是有钱赚咱们四六分成。”

![image-20241206100110865](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241206100110940.png)

我们现在把上面的两种情况抽象概括为一种情况

![image-20241206100900737](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241206100900913.png)

这些抽象的子树都是一棵AVLTree，对于第一种简单情况，`[A]`和`[B]`的左子树就是一棵空树，现在我们发现，`[B]`的右子树平衡因子由0变成1或者-1，这说明`[B]`的右子树高度加一，所以`[B]`的平衡因子就会变成-1，而`[A]`的平衡因子就会变成-2，此时就需要调整，我们让`[B]`充当新的根节点，并把`[B]`的左子树分配给`[A]`，让其充当`[A]`的右子树，然后本轮调整就完成了，接着需要更新涉及到的平衡因子，然后就可以`return`了。

现在我们结合前面两个具体例子来说明这个方案的可行性。比如对于第一种简单情况来说，在插入前，三个抽象子树深度都是0，所以等`[A]`获得了两个子树后不会失衡，而在插入节点后，`[B]`的右子树深度为1，左子树深度也为1，`[B]`这棵树恢复了平衡。对于第二种情况，这三个抽象子树的深度都是1，`[A]`获得新子树后不会失衡，`[B]`成为新的根节点之后，其左右子树的深度都是2，所以也恢复了平衡。

或者我们可以更抽象地来看这个方案的可行性。首先我们知道如果新插入节点后所在树失衡，就意味着这些抽象子树的高度一定相同。为什么这样说呢？我们每次都是一个节点一个节点地插入的，某棵子树从最开始都是一个叶节点，这个叶节点的左右子树都为空，所以最开始的平衡因子都是0，而节点是一个一个插入的，即使造成了所在子树的深度改变，也是以一为单位进行，不可能插入一个节点后这棵树的某个节点平衡因子突然从0变成了2或-2，它一定是先从1变成2或者从-1变成-2的，平衡状态的破坏是具有过程的，不是一蹴而就的，这就意味着如果某棵子树在掺入新节点之后失衡了，就一定是类似这种模式的：本来这棵树是具有平衡性的，平衡因子为0，也就是说，它的左右两棵子树具有相同的高度，然后某棵子树的高度加一，使得这棵子树平衡性降低，而这棵树的平衡性降低就会影响上一级树的平衡性，如果这种影响没有让上一级树失衡，就说明上一级树的平衡因子为0，其所在的两棵子树高度相同，或者是虽然上级树处于次级平衡，但下级树的影响与这种次级平衡是反向的，他们就会对冲，从而让上级树重新完全平衡。但实际是，它失衡了，这就意味着这棵上级树本来就不是很平衡，而下级树的次级平衡加剧了上级树的平衡性，从而使其不平衡，下级树的次级平衡和上级树的次级平衡是同向的，也就是说，上级树本来就是一个子树比另一个子树高，结果新节点的加入正好使得更高的子树高度加一，才使得现在上级树不平衡。

现在我们假设这些抽象子树的深度都为`h`，则在插入前，根节点`[A]`的左子树深度为`h`，右子树深度为`h+1`。当`[B]`成为新根节点之后，因为`[A]`加入根节点的左子树了，并且`[A]`的左右子树深度都是`h`，所以此时`[B]`的左子树深度为`h+1`，至于`[B]`的右子树，由于当初就是因为它高度加一而旋转的，所以它的深度还是`h+1`，因此这棵树恢复了平衡。

![](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241206104928828.png)

![image-20241206105015597](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241206105015706.png)

![image-20241206105226700](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241206105226761.png)

这棵树不仅恢复了平衡，而且深度也和新节点插入前的深度完全一致，所以不会对更上级的树造成影响，因此我们就可以直接`break`了。

现在让我们写一下左单旋函数，也就是这张图。![](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241206104928828.png)

因为它调整起来就像在向左旋转，所以叫左单旋。为了方便起见，我们约定，此图中的`[A]`我们称呼为`parent`，`[B]`称呼为`subR`，`[B]`的左子树称呼为`subRL`。

当我们讨论单旋时，失衡的原因可以归结为某个子树的高度增加，而这个高度的增加总是发生在一个方向上。举个例子，假设右子树比左子树高1，且新插入的节点落在右子树的右子树上，这样就导致了右子树的高度增加，进而造成了不平衡。我们可以将这种不平衡的传递看作一条直线，它沿着树的一个分支平稳地延伸。失衡的根源也就在于这个分支上的某个节点的高度发生了改变，整个过程保持着单向的线性延续。因此，我们可以把这种场景称呼为线性旋转。

```cpp
// Left Rotation  左单旋
void _RotaLe(Node* parent)  // _表示该接口是私有的
{
	Node* subR = parent->_right;   // Right Subtree
	Node* subRL = subR->_left;     // Left Subtree of Right Subtree

	// 旋转的过程

	// 对于parent
	Node* newParPar = parent->_parent;
	parent->_parent = subR;
	(void)parent->_left; // 我知道有这个成员，但它不用处理
	parent->_right = subRL;

	// 对于subR
	if (newParPar == nullptr)
	{
		// 原先的parent就是根节点
		subR->_parent = nullptr;
		_root = subR;
	}
	else
	{
		// 原先的parent具有父节点
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
	(void)subR->_right;  // 它无需处理

	// 对于subRL
	if (subRL) // 如果它不是空树
		subRL->_parent = parent;


	// 平衡因子的更新
	parent->_balanceFactor = 0;
	subR->_balanceFactor = 0;
}

void _RotaRe(Node* parent)
{
	Node* subL = parent->_left;
	Node* subLR = subL->_right;

	Node* newParPar = parent->_parent;
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

	parent->_balanceFactor = 0;
	subL->_balanceFactor = 0;
}
```

接下来，我们看看另一种失衡的情况。与之前的直线式失衡不同，这种失衡的传递过程会在某一层发生方向上的转折，呈现出一种折线般的特征。这种特性使得调整过程相比单旋更复杂，需要结合两次旋转操作来完成平衡的恢复。所以我们称之为复合旋转。

之前我们是在`[B]`的右子树上插入，现在我们来看看在左子树上插入会如何。

![](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241206104928828.png)

`[B]`的左子树高度增加导致`[A]`的右子树高度增加从而引发失衡。此时失衡的影响关系就像是折线一样。

为此我们需要把这个模型再次细分一下。

![image-20241208173234996](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241208173235044.png)

接下来我们要分情况讨论一下。

首先是当`h=0`时，抽象树们都为空，`[C]`节点实际不存在，此时，所在树其实就两个节点。

![image-20241208173704888](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241208173704926.png)

而新插入的节点就是`[C]`。

![image-20241208173918042](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241208173918087.png)

第二种情况，`h=1`，此时不论在`[C]`的左子树还是右子树插入节点都会使其高度加一，从而引发`[B]`的高度加一，最终使得`[A]`失衡。

![image-20241208174723714](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241208174723757.png)

![image-20241208174930496](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241208174930542.png)

![image-20241208175012892](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241208175012951.png)

`h=2`时，可能有更多的情况。

![image-20241208175344009](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241208175344111.png)

![image-20241208175438802](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241208175438855.png)

![image-20241208175525657](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241208175525706.png)

我们不展开了，现在来说怎么调整。

我们先不考虑`h=0`的那种情况

![image-20241208173234996](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241208173235044.png)

先在我们在`b`插入一个新节点，我们忽略它的插入细节，只需知道，这次插入导致`b`的高度加一了。然后造成了一系列影响，最终导致`[A]`失衡

![image-20241208181731923](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241208181731976.png)

接下来是关键操作，我们以`[B]`的位置为旋转点，进行向右旋转

![image-20241208182304135](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241208182304192.png)

对于上图的这种状态来说，我们可以认为它是因为刚刚的右旋而导致的，也可以等效地认为，它上一步其实是这样

![image-20241208182812209](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241208182812259.png)

这里的抽象子树m可以理解成就长这样

![image-20241208182958510](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241208182958549.png)

然后由于`d`插入了一个新节点，而导致抽象子树m高度的加一。所以它们两个其实可以视为一种等效。

那对于这种状态，

![image-20241208182812209](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241208182812259.png)

到这种状态

![image-20241208183622333](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241208183622385.png)

我们之前已经有过解决方案，那就是以`[A]`为旋转点进行右旋转。然后我们就解决了问题。

再回顾一下

最开始是平衡的，长这样

![image-20241208173234996](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241208173235044.png)

然后`b`加了一个节点，深度改变，不平衡了。

![image-20241208181731923](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241208181731976.png)

接着对`[B]`这棵树进行右单旋

![image-20241208182304135](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241208182304192.png)

然后对`[A]`这棵树进行左单旋

![image-20241208185125268](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241208185125329.png)

平衡了。

现在我们再换一种场景

![image-20241208173234996](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241208173235044.png)

这会是`c`的高度加一

![image-20241208185443281](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241208185443332.png)

还是对`B`进行右旋

![image-20241208185935991](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241208185936054.png)

我们还是可以抽象地看，`[A]`为什么会失衡，因为`[C]`次级平衡影响到它了，`[C]`为什么会变成次级平衡，因为可以认为它的右子树高度加一了，该怎么解决？对`[A]`进行左旋，尽管这种左旋不是很标准，但确实可以让树重新平衡。

![image-20241208190947102](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241208190947180.png)

至于最后这种特殊情况

![image-20241208173918042](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241208173918087.png)

其实也可以用这种思路

先以`[B]`进行右旋

![image-20241208194546102](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241208194546148.png)

再对`[A]`进行右旋

![image-20241208194741560](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241208194741609.png)

这样我们就可以直接复用之前的两份单旋函数。当然，平衡因子还是需要我们手动调的，我们把这三种情况用新节点插入后`[C]`的平衡因子进行区分，当插入后`[C]`的平衡因子就是0时，双旋之后，`[A][B][C]`三个节点的平衡因子就都是0，若`[C]`的平衡因子是1，双旋之后，`[A][C]`的平衡因子都是0，`[B]`是-1，若`[C]`的平衡因子是-1，双旋之后，`[B][C]`是0，`[A]`是1。

或者也可以这样理解，这两次旋转相当于把`[C]`的左子树变成`[A]`的右子树，把`[C]`的右子树变成`[B]`的左子树，并且`[A][B]`原来自己就有的子树，也就是`[A]`的左子树和`[B]`的右子树，它们的深度都为`h`，而`[C]`的左右子树最开始高度都是`h-1`，如果新节点插入后，平衡因子是`1`，说明`[C]`的左子树深度变成了`h`，而这个子树之后会变成`[A]`的右子树，所以`[A]`新的平衡因子就是0，而`[B]`是`-1`，如果`[C]`的平衡因子变成了`-1`，就说明`[C]`的右子树深度变成了`h`，所以`[B]`的新平衡因子自然是0，而`[A]`就是1。

好，写一下代码

```cpp
void _RotaLR(Node* parent)
{
    Node* subL = parent->_left;
    Node* subLR = subL->_right;

    int flag = subLR->_balanceFactor;

    _RotaLe(subL);
    _RotaRi(parent);

    if (flag == -1)
    {
        parent->_balanceFactor = 0;
        subL->_balanceFactor = 1;
        (void)subLR->_balanceFactor;  // 这个成员不用处理 右单旋已经处理过了
    }
    else if (flag == 1)
    {
        parent->_balanceFactor = -1;
        subL->_balanceFactor = 0;
        (void)subLR->_balanceFactor;
    }
    else
    {
        // flag == 0
        assert(flag == 0); // 万一出错，就报错
        parent->_balanceFactor = 0;
        subL->_balanceFactor = 0;
        (void)subLR->_balanceFactor;
    }
}

void _RotaRL(Node* parent)
{
    Node* subR = parent->_right;
    Node* subRL = subR->_left;

    int flag = subRL->_balanceFactor;

    _RotaRi(subR);
    _RotaLe(parent);


    if (flag == -1)
    {
        parent->_balanceFactor = 1;
        subR->_balanceFactor = 0;
        (void)subRL->_balanceFactor;
    }
    else if (flag == 1)
    {
        parent->_balanceFactor = 0;
        subR->_balanceFactor = -1;
        (void)subRL->_balanceFactor;
    }
    else
    {
        // flag == 0
        assert(flag == 0);
        parent->_balanceFactor = 0;
        subR->_balanceFactor = 0;
        (void)subRL->_balanceFactor;
    }
}
```

```cpp
else if(parent->_balanceFactor == 2 || parent->_balanceFactor == -2)
{
    // 这棵树已经不是AVLTree了，需要调整

    // 第一大类：线性旋转
    if(parent->_balanceFactor == 2 && location->_balanceFactor == 1)
    {
        // 右单旋
        _RotaRi(parent);
    }
    else if(parent->_balanceFactor == -2 && location->_balanceFactor == -1)
    {
        // 左单旋
        _RotaLe(parent);
    }

    // 第二大类：复合旋转
    else if (parent->_balanceFactor == 2 && location->_balanceFactor == -1)
    {
        _RotaLR(parent);

    }
    else if (parent->_balanceFactor == -2 && location->_balanceFactor == 1)
    {
        _RotaRL(parent);
    }
    else
    {
        assert(0);
    }

    // 现在树已经重新平衡了，并且高度没有改变
    break;
}
```

接下来我们写个自检函数，用来检测当前的树是否为AVLTree

```cpp
int _height(Node* root)
{
	if (root == nullptr)
		return 0;

	int left_height = _height(root->_left);
	int right_height = _height(root->_right);

	return std::max(left_height, right_height) + 1;
}

// 检查当前对象中的树是否为AVLTree
bool _isAVLTree(Node* root)
{
	if (root == nullptr)
		return true;

	int left_height = _height(root->_left);
	int right_height = _height(root->_right);

	int i = left_height - right_height;

	if (i != root->_balanceFactor)
	{
		std::cout << "平衡因子存在问题" << std::endl;
		std::cout << "当前节点包含的关键值为" << root->_value.first << std::endl;
	}

	if (std::abs(i) >= 2) // abs是绝对值
		return false;

	return _isAVLTree(root->_left) && _isAVLTree(root->_right);
}

bool isAVLTree() { return _isAVLTree(_root); }
```

然后是中序遍历

```cpp
void _InOrder(Node* root, std::vector<value_type>& v)
{
	if (root == nullptr)
		return;

	_InOrder(root->_left, v);
	v.push_back(root->_value);
	_InOrder(root->_right, v);
}

std::vector<value_type> InOrder()
{
	std::vector<value_type> res;
	_InOrder(_root, res);
	return res;
}
```

现在我们测试一下

```cpp
#include"AVLTree.h"
#include<string>
#include<vector>
#include<ctime>

using namespace std;

int main()
{
	vector<int> v = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };
	/*vector<int> v;
	srand(time(0));
	for (size_t i = 0; i < 100000; ++i)
	{
		v.push_back(rand());
	}*/

	wind::AVLTree<int, int> ts;
	for(const auto& i : v)
	{
		ts.Insert(make_pair(i, 0));
	}

	if (ts.isAVLTree())
	{
		cout << "true" << endl;
	}
	else
	{
		cout << "false" << endl;
	}

	auto vs = ts.InOrder();

	for (const auto& e : vs)
	{
		cout << e.first << endl;
	}
	return 0;
}
```

![image-20241209085326257](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241209085326476.png)

```cpp
int main()
{
	//vector<int> v = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };
	vector<int> v;
	srand(time(0));
	for (size_t i = 0; i < 100000; ++i)
	{
		v.push_back(rand());
	}

	wind::AVLTree<int, int> ts;
	for(const auto& i : v)
	{
		ts.Insert(make_pair(i, 0));
	}

	if (ts.isAVLTree())
	{
		cout << "true" << endl;
	}
	else
	{
		cout << "false" << endl;
	}

	/*auto vs = ts.InOrder();

	for (const auto& e : vs)
	{
		cout << e.first << endl;
	}*/
	return 0;
}
```

![image-20241209085427957](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241209085428085.png)

下面我们略微说一说AVLTree的删除，其实也是在二叉搜索树的基础上进行的，先是把要删除的数据移到终端节点或者从树中解离出来，然后是再平衡操作，我们稍微谈谈思路。

注意我们写的AVLTree节点中是有三个指针的，注意替换的过程中不要出现错误链接。和插入一样，我们的平衡因子要放在再平衡过程中。

至于再平衡过程，首先是平衡因子的调节策略发生了变化，当平衡因子的绝对值为1时，说明它是由平衡状态变为不平衡状态的，所以树的高度不变，因此可以直接退出；当平衡因子为0时，说明这棵树的深度发生了变化，因此需要向上回溯，分析当前树对上一级树的影响；然后就是平衡因子绝对值为2的场景了，此时就需要进行一系列旋转操作。平衡因子调整必须放在再平衡状态中就是因为在循环过程中也必须自动调整平衡因子，如果在替换过程中贸然更改平衡因子，就会在平衡过程中造成特例。

我们先看第一种情况：因为左子树而导致当前树的失衡。

很明显，此时的状况是左子树低，右子树高，很明显，我们需要左旋的方式从右子树那里匀点高度给左子树，接下来我们就要看看右子树的情况，看看它是否准备好左旋。为了方便起见，我们把这里的右子树称为`higher_sub`。

第一种情况，`higher_sub->_balanceFactor == 0`

![image-20241213160802896](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241213160803084.png)

让我们分析一下为什么这样画。为什么来到了这里？因为左子树高度下降，所以造成了左子树低右子树高的局面。我们可以设现在左子树的高度是`h-1`，右子树的高度比左子树高2，所以右子树的高度为`h+1`，`Hsub`自己占据了一个高度，所以剩下的`h`由它的子树提供，又`bf==0`。所以它的左右子树就是`h`。

能不能直接左旋呢？能不能直接左旋取决于左旋之后是否会产生新的不平衡情况，很显然，这里没有

![image-20241213161532791](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241213161532856.png)

接下来我们要去手动调整一下平衡因子它自己调整不了，从图上可知，`root->_bf = -1`，`Hsub->_bf = 1`，并且这棵树的高度没有发生变化，所以可以直接退出。

第二种`higher_sub->_balanceFactor == -1`

![image-20241213161952699](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241213161952773.png)

也可以直接左旋，不过这回的问题是，树的高度变矮了，所以要向上回溯。平衡因子让它自己调节。

![image-20241213162159584](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241213162159653.png)

`higher_sub->_balanceFactor == 1`

![image-20241213162825799](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241213162825865.png)

这种情况就不能直接左旋，直接左旋是这样的

![image-20241213163013850](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241213163013907.png)

直接左旋回过度调整，从而造成新的不平衡。

所以在左旋之前，我们先要对`Hsub`进行一些调整，我们让那个被扔到对面的子树高度减少一点，从而避免过度调整，怎么让被移交的子树变矮呢？很简单，让`Hsub`先自己右旋。

为了分析这个右旋，我们需要把图画的更细节一些。为方便起见，我们把`Hsub->_left->_bf`简称为`bf`。

第一种情况`bf == 0`

![image-20241213163729643](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241213163729706.png)

右旋之后变成这样

![image-20241213163929410](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241213163929478.png)

抽象一下就变成了这样

![image-20241213161952699](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241213161952773.png)

所以就可以直接左旋了。

`bf == 1`

![image-20241213164145811](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241213164145870.png)

右旋之后就变成这样了

![image-20241213164326743](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241213164326811.png)

抽象一下还是这样

![image-20241213161952699](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241213161952773.png)

`bf == -1`

![image-20241213164546147](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241213164546226.png)

![image-20241213164655611](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241213164655684.png)

可以抽象成这样

![image-20241213164757197](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20241213164757247.png)

略微有些不同，但好在左旋是没有问题的。而且高度也减低了，可以与上述两种情况合并。需要注意的是，对于平衡因子的更新要具体情况具体分析。

右子树所造成的失衡于此类似，在此省略。

下面是具体代码，其中包含一些调试代码。另外特别说一下，为了方便覆写交换，键值对的first我去除了const。

```cpp
bool erase(const key_type& key)
{
    Node* should = find(key); // 应该被删除的节点（闯祸的节点）
    if (should == nullptr)
        return false;

    // debug
    if (key == -1)
    {
        debug_lock = 1;
    }

    // 转移即将被释放的属性: should->practice
    Node* practice = nullptr; // 实际会被删除的节点（背黑锅的节点）
    source origin = invalid;  // 标记practice是其parent的左子树还是右子树
    if (should->_left == nullptr)// 仅有右子树
    {
        practice = should; // 自己闯的祸自己承担
        Node* practice_only_sub = practice->_right;
        Node* practice_parent = practice->_parent;

        // 安排后事
        if (practice_parent == nullptr)
        {
            // 让子树继承整棵树
            _root = practice_only_sub;
            if(practice_only_sub)
                practice_only_sub->_parent = nullptr;
            (void)origin;
        }
        else
        {
            // 找上级节点托孤
            if (practice_parent->_left == practice)
            {
                practice_parent->_left = practice_only_sub;
                if (practice_only_sub) // 空子树就不用向前链接
                    practice_only_sub->_parent = practice_parent;
                origin = left;
            }
            else
            {
                practice_parent->_right = practice_only_sub;
                if (practice_only_sub) // 空子树就不用向前链接
                    practice_only_sub->_parent = practice_parent;
                origin = right;
            }
        }
    }
    else if (should->_right == nullptr) //仅有左子树
    {
        practice = should;
        Node* practice_only_sub = practice->_left;
        Node* practice_parent = practice->_parent;

        if (practice_parent == nullptr)
        {
            _root = practice_only_sub;
            if (practice_only_sub)
                practice_only_sub->_parent = nullptr;
            (void)origin;
        }
        else
        {
            if (practice_parent->_left == practice)
            {
                practice_parent->_left = practice_only_sub;
                if (practice_only_sub)
                    practice_only_sub->_parent = practice_parent;
                origin = left;
            }
            else
            {
                practice_parent->_right = practice_only_sub;
                if (practice_only_sub)
                    practice_only_sub->_parent = practice_parent;
                origin = right;
            }
        }
    }
    else
    {
        // should有两个孩子

        //找替死鬼
        Node* prev = should;
        Node* next = prev->_right;
        while (next->_left)
        {
            prev = next;
            next = next->_left;
        }

        /*if (debug_lock)
			{
				debug(prev);
				const char* str = "Debug";
			}*/

        if (next == prev->_right)
        {
            // 覆写should节点，将被释放的节点变为多余内容的节点
            practice = next;
            //should->_value = practice->_value;
            std::swap(should->_value, practice->_value);


            // 托孤
            Node* practice_child = practice->_right;
            prev->_right = practice_child;
            if (practice_child)
                practice_child->_parent = practice->_parent;
            origin = right;
        }
        else
        {
            practice = next;
            //should->_value = practice->_value;
            std::swap(should->_value, practice->_value);

            // 托孤
            Node* practice_child = practice->_right;
            prev->_left = practice_child;
            if (practice_child)
                practice_child->_parent = practice->_parent;
            origin = left;
        }
        /*if (debug_lock)
			{
				debug(practice);
				const char* str = "Debug";
			}*/
    }

    Node* curr = nullptr;
    if(practice)
        curr = practice->_parent;  // 当前子树根节点

    // 再平衡化
    while (curr)
    {
        if (debug_lock)
        {
            debug(curr);
            const char* str = "Debug";
        }

        //// 平衡因子迭代机制
        //if (origin == invalid)
        //{
        //	// 子树成为了新的根节点，无需平衡化
        //	break;
        //}
        //else 

        if (origin == left)
        {
            // curr左子树高度将会降低
            curr->_balanceFactor--;
        }
        else if (origin == right)
        {
            // curr右子树高度将会降低
            curr->_balanceFactor++;
        }
        else
        {
            // 不存在的分支
            assert(0);
        }

        if (debug_lock)
        {
            debug(curr);
            const char* str = "Debug";
        }

        // 检查平衡性
        if (curr->_balanceFactor == 0)
        {
            // curr这棵树的高度降低
            // 回溯到上一级子树
            Node* parent = curr->_parent;
            if (parent == nullptr)
            {
                curr = parent;
                origin = invalid;
            }
            else
            {
                if (parent->_left == curr)
                    origin = left;
                else
                    origin = right;
                curr = parent;
            }
            if (debug_lock)
            {
                debug(curr);
                const char* str = "debug";
            }
        }
        else if (std::abs(curr->_balanceFactor) == 1)
        {
            // curr这棵树高度不变
            // 不必麻烦上一级子树
            break;
        }
        else if (std::abs(curr->_balanceFactor) == 2)
        {
            // curr这棵树已经失衡
            // 需要调整

            // 第一种情况——因为左子树次级平衡而引发的失衡
            if (origin == left)
            {
                // 当前情况是:左子树低,右子树高
                Node* higher_sub = curr->_right;
                if (higher_sub->_balanceFactor == 0)
                {
                    // 左子树低是吧？那向左旋转就行了,向哪里旋转哪里就会变高一些
                    _RotaLe(curr);

                    // 在未插入前，整棵树的高度是h+2
                    // 更高的树有两棵子树，它们高度相同,都是h
                    // 原右子树路径因为旋转必然减少，不必分析,变成了h
                    // 现在左左子树的路径高度，删除前(删除前是h)减少一个(变成了h-1)，旋转后，高度又增加一个，
                    // 所以左左子树的高度是h，加上新上台的新根节点，这条路径的高度是h+1
                    // 现在左右子树的路径高度取决于两个部分，第一个是原来的target节点，它被旋转下来后必然高度加一
                    // 第二个因素是从原来较高树的左子树移过来的那棵子树,高度为h,加上下台的根节点，就变成了h+1,
                    // 别忘了还有新根节点，合起来就是h+2
                    // 综上，左单旋之后当前树的高度不发生变化

                    // 平衡因子的修正
                    higher_sub->_balanceFactor = 1;
                    curr->_balanceFactor = -1;

                    // 高度不发生变化
                    break;
                }
                else if (higher_sub->_balanceFactor == -1)
                {
                    _RotaLe(curr);

                    // 平衡因子不需要修正,它们就是0,仅依靠单旋就已经足够
                    // 按照上述逻辑分析,高度减一,需要回溯到上级树
                    Node* newRoot = curr->_parent; // 旋转后新的根节点
                    Node* parent = newRoot->_parent;
                    if (parent == nullptr)
                    {
                        origin = invalid;
                    }
                    else
                    {
                        if (parent->_left == newRoot)
                            origin = left;
                        else
                            origin = right;
                    }
                    curr = parent;
                    if (debug_lock)
                    {
                        debug(curr);
                        const char* str = "Debug";
                    }
                }
                else if (higher_sub->_balanceFactor == 1)
                {
                    // 此种场合不能直接进行左单旋
                    // 此时较高树的左子树高度为h
                    // 右子树为h-1
                    // 直接单旋会造成当前左子树高度为h+1,
                    // 而当前右子树高度为h-1
                    // 这会引发新的不平衡

                    // 对于较高树来说,它本来就偏科
                    // 以前一俊遮百丑,强项可以掩盖弱项
                    // bf == 0时是真正的均衡发展,把哪个子树匀给别人都行
                    // bf == -1时虽然有偏科,但把弱项给别人,自己靠强项活的还可以
                    // bf == 1是把强项给别人,没有强项之后,弱项的一系列问题就马上暴露出来了

                    // 经济好的时候,大问题不是问题,经济不好的时候,小问题是大问题

                    // 所以要先自我平衡一下,然后再去帮别人
                    Node* higher_subL = higher_sub->_left;
                    int bf = higher_subL->_balanceFactor;
                    if (debug_lock)
                    {
                        debug(higher_subL);
                        const char* str = "debug";
                    }

                    _RotaRi(higher_sub);
                    if (debug_lock)
                    {
                        debug(curr);
                        const char* str = "debug";
                    }

                    // bf有三种情况
                    if (bf == 0)
                    {
                        // 这意味着,higher_subL的两个子树高度都是h-1
                        // 在自我平衡之后,higher_sub的高度为h+1
                        // 其中higher_subL为h-1,higher_subR为h
                        // 也就是相当于higher_sub->_balanceFactor == -1的情况
                    }
                    else if (bf == -1)
                    {
                        // higher_subLL::bf == h-2
                        // higher_subLR::bf == h-1
                        // 自我平衡后
                        // new higher_subL::bf == h-2
                        // new higher_subR::bf == h
                        // new higher_sub::bf == h+1
                        // 等效higher_sub->_balanceFactor == -1

                    }
                    else if (bf == 1)
                    {
                        // higher_subLL::bf == h-1
                        // higher_subLR::bf == h-2
                        // 自我平衡后
                        // new higher_subL::bf == h-1
                        // new higher_subR::bf == h   (old higher_subR::bf == h-1)
                        // new higher_sub::bf == h+1
                        // 等效higher_sub->_balanceFactor == -1
                    }
                    //////三种情况相同操作
                    _RotaLe(curr);
                    // 平衡因子的更新
                    if (debug_lock)
                    {
                        debug(curr->_parent);
                        const char* str = "debug";
                    }

                    if (bf == -1)
                    {
                        curr->_balanceFactor = 1;
                        higher_sub->_balanceFactor = 0;
                    }
                    else if (bf == 0)
                    {
                        curr->_balanceFactor = 0;
                        higher_sub->_balanceFactor = 0;
                    }
                    else if (bf == 1)
                    {
                        curr->_balanceFactor = 0;
                        higher_sub->_balanceFactor = -1;
                    }
                    else
                        assert(0);

                    Node* newRoot = curr->_parent; // 旋转后新的根节点
                    Node* parent = newRoot->_parent;
                    if (parent == nullptr)
                    {
                        origin = invalid;
                    }
                    else
                    {
                        if (parent->_left == newRoot)
                            origin = left;
                        else
                            origin = right;
                    }
                    curr = parent;
                }
                else
                    assert(0); // 不存在的分支
            }
            else if (origin == right)
            {
                // 当前情况是:左子树高,右子树低
                Node* higher_sub = curr->_left;
                if (higher_sub->_balanceFactor == 0)
                {
                    // 右子树低是吧？那向右旋转就行了,向哪里旋转哪里就会变高一些
                    _RotaRi(curr);

                    // 在未插入前，整棵树的高度是h+2
                    // 更高的树有两棵子树，它们高度相同,都是h
                    // 原左子树路径因为旋转必然减少，不必分析,变成了h
                    // 现在右右子树的路径高度，删除前(删除前是h)减少一个(变成了h-1)，旋转后，高度又增加一个，
                    // 所以右右子树的高度是h，加上新上台的新根节点，这条路径的高度是h+1
                    // 现在左右子树的路径高度取决于两个部分，第一个是原来的curr节点，它被旋转下来后必然高度加一
                    // 第二个因素是从原来较高树的左子树移过来的那棵子树,高度为h,加上下台的根节点，就变成了h+1,
                    // 别忘了还有新根节点，合起来就是h+2
                    // 综上，左单旋之后当前树的高度不发生变化

                    // 平衡因子的修正
                    higher_sub->_balanceFactor = -1;
                    curr->_balanceFactor = 1;

                    // 高度不发生变化
                    break;
                }
                else if (higher_sub->_balanceFactor == 1)
                {
                    _RotaRi(curr);

                    // 平衡因子不需要修正,它们就是0,仅依靠单旋就已经足够
                    // 按照上述逻辑分析,高度减一,需要回溯到上级树
                    Node* newRoot = curr->_parent; // 旋转后新的根节点
                    Node* parent = newRoot->_parent;
                    if (parent == nullptr)
                    {
                        origin = invalid;
                    }
                    else
                    {
                        if (parent->_left == newRoot)
                            origin = left;
                        else
                            origin = right;
                    }
                    curr = parent;
                }
                else if (higher_sub->_balanceFactor == -1)
                {
                    // 此种场合不能直接进行左单旋
                    // 此时较高树的左子树高度为h
                    // 右子树为h-1
                    // 直接单旋会造成当前左子树高度为h+1,
                    // 而当前右子树高度为h-1
                    // 这会引发新的不平衡

                    // 对于较高树来说,它本来就偏科
                    // 以前一俊遮百丑,强项可以掩盖弱项
                    // bf == 0时是真正的均衡发展,把哪个子树匀给别人都行
                    // bf == -1时虽然有偏科,但把弱项给别人,自己靠强项活的还可以
                    // bf == 1是把强项给别人,没有强项之后,弱项的一系列问题就马上暴露出来了

                    // 经济好的时候,大问题不是问题,经济不好的时候,小问题是大问题

                    // 所以要先自我平衡一下,然后再去帮别人
                    Node* higher_subR = higher_sub->_right;
                    int bf = higher_subR->_balanceFactor;
                    if (debug_lock)
                    {
                        debug(higher_subR);
                        const char* str = "debug";
                    }

                    _RotaLe(higher_sub);
                    if (debug_lock)
                    {
                        debug(curr);
                        const char* str = "debug";
                    }

                    // 三种情况
                    if (bf == 0)
                    {
                        // 这意味着,higher_subL的两个子树高度都是h-1
                        // 在自我平衡之后,higher_sub的高度为h+1
                        // 其中higher_subL为h-1,higher_subR为h
                        // 也就是相当于higher_sub->_balanceFactor == -1的情况
                    }
                    else if (bf == -1)
                    {
                        // higher_subLL::bf == h-2
                        // higher_subLR::bf == h-1
                        // 自我平衡后
                        // new higher_subL::bf == h-2
                        // new higher_subR::bf == h
                        // new higher_sub::bf == h+1
                        // 等效higher_sub->_balanceFactor == -1

                    }
                    else if (bf == 1)
                    {
                        // higher_subLL::bf == h-1
                        // higher_subLR::bf == h-2
                        // 自我平衡后
                        // new higher_subL::bf == h-1
                        // new higher_subR::bf == h   (old higher_subR::bf == h-1)
                        // new higher_sub::bf == h+1
                        // 等效higher_sub->_balanceFactor == -1
                    }
                    //////三种情况相同操作
                    _RotaRi(curr);
                    if (debug_lock)
                    {
                        debug(curr->_parent);
                        const char* str = "debug";
                    }

                    // 平衡因子的更新

                    if (bf == -1)
                    {
                        curr->_balanceFactor = 0;
                        higher_sub->_balanceFactor = 1;
                    }
                    else if (bf == 0)
                    {
                        curr->_balanceFactor = 0;
                        higher_sub->_balanceFactor = 0;
                    }
                    else if (bf == 1)
                    {
                        curr->_balanceFactor = -1;
                        higher_sub->_balanceFactor = 0;
                    }
                    else
                        assert(0);

                    Node* newRoot = curr->_parent; // 旋转后新的根节点
                    Node* parent = newRoot->_parent;
                    if (parent == nullptr)
                    {
                        origin = invalid;
                    }
                    else
                    {
                        if (parent->_left == newRoot)
                            origin = left;
                        else
                            origin = right;
                    }
                    curr = parent;
                }
                else
                    assert(0); // 不存在的分支
            }
            else
                assert(0);
        }
    }

    delete practice;
    return true;
}

private:

void debug(Node* root)
{
    if (root == nullptr)
    {
        printf("                                            NULL\n");
        return;
    }

    printf("                                            ");
    printf("[root:%d]", root->_value.first);
    printf("(bf:%d)\n", root->_balanceFactor);

    Node* subL = root->_left;
    Node* subR = root->_right;

    if (subL)
    {
        printf("                  ");
        printf("[subL:%d]", subL->_value.first);
        printf("(bf:%d)                                       ", subL->_balanceFactor);
    }
    else
    {
        printf("                  ");
        printf("NULL                                       ");
    }

    if (subR)
    {
        printf("[subR:%d]", subR->_value.first);
        printf("(bf:%d)\n", subR->_balanceFactor);
    }
    else
    {
        printf("NULL");
    }

    if (subL)
    {
        Node* subLL = subL->_left;
        if (subLL)
        {
            printf("[subLL](height:%d bf:%d)     ", _height(subLL), subLL->_balanceFactor);
        }
        else
        {
            printf("            NULL             ");
        }

        Node* subLR = subL->_right;
        if (subLR)
        {
            printf("[subLR](height:%d bf:%d)     ", _height(subLR), subLR->_balanceFactor);
        }
        else
        {
            printf("            NULL             ");
        }
    }
    else
    {
        printf("            NULL             ");
        printf("            NULL             ");
    }

    if (subR)
    {
        Node* subRL = subR->_left;
        if (subRL)
        {
            printf("[subLL](height:%d bf:%d)     ", _height(subRL), subRL->_balanceFactor);
        }
        else
        {
            printf("            NULL             ");
        }

        Node* subRR = subR->_right;
        if (subRR)
        {
            printf("[subLR](height:%d bf:%d)     ", _height(subRR), subRR->_balanceFactor);
        }
        else
        {
            printf("            NULL             ");
        }
    }
    else
    {
        printf("            NULL             ");
        printf("            NULL             ");
    }

    printf("\n======================================================END======================================================\n\n");

}

// 在平衡化过程中标记子树来源
enum source
{
    left,
    right,
    invalid // 没有parent
};
```

以下为测试代码

```cpp
int main()
{
    //vector<int> v = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };
    vector<int> v;
    //srand(time(0));
    for (size_t i = 0; i < 100000; ++i)
    {
        v.push_back(rand());
    }

    wind::AVLTree<int, int> ts;
    for (const auto& i : v)
    {
        ts.Insert(make_pair(i, 0));
    }

    for (size_t pos = 0; pos < v.size(); pos++)
    {
        cout << "正在测试第" << pos << "个数" << endl;
        int i = v[pos];
        ts.erase(i);

        // 针对测试
        //if (pos == 35)
        //{
        //	//printf("Debug\n");
        //	cout << ts.isAVLTree() << endl;
        //	const char* str = "Debug";
        //	/*auto vs = ts.InOrder();

        // 全局测试
        if (!ts.isAVLTree())
        {
            cout << i << endl;
            cout << pos << endl;
            while (1);
        }
    }
    return 0;
}
```

# end