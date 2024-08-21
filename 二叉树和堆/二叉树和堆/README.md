# 二叉树和堆

## 前言

在讲二叉树之前，需要对“树”这种数据结构有一些了解。如下图，是一棵"树"。

![绘图1](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408141422337.png)

------

degree：中文译作度。

<audio src="https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408141356684.mp3"></audio>

节点单次向下延伸出的节点个数叫做度，比如节点[A]向下延伸一次可以延伸出六个节点：[B]\[C]\[D]\[E]\[F]\[G]，所以节点[A]的度就是6。

------

terminal node：中文译为终端节点或叶节点。

<audio src="https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408141405270.mp3"></audio>

度为0的节点称为终端节点，如上图[B]\[H]\[J]\[P]\[Q]\[K][L]\[M]\[N]。

------

non-terminal node：中文译为非终端节点或分支节点。

<audio src="https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408141409568.mp3"></audio>

度不为0的节点称为非终端节点，在此不作举例。

------

parent node：中文译为双亲节点或父节点。

<audio src="https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408141412697.mp3"></audio>

child node：中文译为子节点或孩子节点。

<audio src="https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408141415492.mp3"></audio>

对于一个分支节点来说，它自己被称为双亲节点，它延伸出的节点被称为子节点；例如，[G]是[N]的双亲节点，[N]是[G]的子节点。

------

root node：根节点。

<audio src="https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408141503987.mp3"></audio>

在树结构中，根节点是树的最上层节点，没有父节点，是整个树的起始点。如上图中的[A]。

---------

sibling nodes：中文译作兄弟节点。

<audio src="https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408141418354.mp3"></audio>

具有相同双亲节点的子节点互称为兄弟节点。如上图中的[P]\[Q]都有相同的双亲节点[J]，所以它们互为兄弟节点。

------

degree of a tree：中文译作树的度。

<audio src="https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408141430252.mp3"></audio>

一棵树中，最大的节点的度称为树的度；比如在上图中，最大的度是[A]的度，为6，所以这棵树的度为6。

------

height of a tree：中文译为树的高度或树的深度。

<audio src="https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408141436894.mp3"></audio>

从根节点到终端节点中最长路径经过的节点个数。比如，在上图中，根节点到终端节点的最长路径是[A]->[E]->[J]->[P]或者[A]->[E]->[J]->[Q]，其中经过了四个节点，所以上图中树的深度为4。在此种语境下，[A]处于第一层，[B]\[C]\[D]\[E]\[F]\[G]处于第二层，[H]\[I]\[J]\[K]\[L]\[M]\[N]处于第三层，[P]\[Q]处于第四层。对于一个空树，即一个节点都没有的树，此时树的度为0。

在极少数情况下，层数从0开始，即，[A]处于第零层，[B]\[C]\[D]\[E]\[F]\[G]处于第一层，[H]\[I]\[J]\[K]\[L]\[M]\[N]处于第二层，[P]\[Q]处于第三层，在此种语境下，上图树的深度为3。对于一个空树，即一个节点都没有的树，此时树的度为-1。这就是用得少的原因，在此种定义下，会出现负数度。

如不作特殊声明，下文中树的度都以第一种情况为准。

------

ancestor：中文译作祖先。

<audio src="https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408141509300.mp3"></audio>

descendant：中文译作子孙。

<audio src="https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408141512671.mp3"></audio>

从根节点到某个节点中除去这个节点自身的节点，就是这个节点的祖先。比如，在上图中，根节点[A]到节点[J]的路径是[A]->[E]->[J]，则[A]和[E]都是[J]的祖先。

从某个节点延伸出的节点都叫做这个节点的子孙。如上图中，[B]\[C]\[D]\[E]\[F]\[G]\[H]\[I]\[J]\[K]\[L]\[M]\[N]\[P]\[Q]都可以由[A]延伸得出，所以它们是[A]的子孙；又如，[P]\[Q]可由[J]延伸得出，所以[P]\[Q]是[J]的子孙。

------

subtree：中文译作子树。

<audio src="https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408141506264.mp3"></audio>

在树结构中，子树是指某个节点及其所有后代节点所组成的树。每个节点都可以视为其子树的根节点。比如，上图中，以[A]为根节点的树可以拆出6个子树：以[B]为根节点的树，以[C]为根节点的树，以[D]为根节点的树，以[E]为根节点的树，以[F]为根节点的树，以[G]为根节点的树；其中，以[D]为根节点的树，以[E]为根节点的树，以[F]为根节点的树，以[G]为根节点的树还可以进行下一步拆分，例如，以[E]为根节点的树可以被拆分出2个子树：以[I]为根节点的树，以[J]为根节点的树，而以[J]为根节点的树还可以被拆分出两个子树：以[P]为根节点的树和以[Q]为根节点的树。

------

forest：中文译作森林。

<audio src="https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408141536842.mp3"></audio>

由m(m>1)个不相交的树组成的集合叫做森林。

-------

树是一种**非线性**的数据结构，它是由n（n>=0）个有限结点组成一个具有层次关系的集合。**把它叫做树是因为它看起来像一棵倒挂的树，也就是说它是根朝上，而叶朝下的**。  

就像前面说的那样，树可以被拆出若干个子树，而这些子树又能被拆出若干个子树，所以说，树是嵌套定义的。

另外注意，对于树来说，除非是根节点，否则每个节点都有且只有一个双亲节点。有些像函数的对应关系，自变量有唯一的因变量与之对应，但因变量可以对应多个自变量，一个节点只能有一个双亲节点，一个双亲节点可以有多个子节点。

-------

该如何定义树的节点？

当每个节点的度差别不是太大时，可以仿照链表或顺序表的节点定义，数值域仍旧存放数据，指针域存放指向其子节点的指针或下标（下标不就是一种简化的地址吗）。指针域中的具体指针个数取决于degree of a true(输入法不能一次性找到“树度”这个词，干脆用英文了)。

当每个节点的degree差别太大时，比如上图中，最大的degree是6，degree of other nodes is 2,1 or none.如果把节点的指针域指针个数定死为6，就会非常麻烦。为了解决这个问题，我们可以在指针域中只定义一个指针，这个指针指向一个数组，这个数组存储着这个节点的子节点的地址，这样当degree发生变化时，我们只需要手动调整数组的大小即可。

前面两种方法本质上都是往指针域里存子节点的指针，当在某些情况下，我们更关心一个节点的parent node而非child node，此时指针域里存的就可以是pointer of parent node，而且由于几乎所有节点的parent node都有且只有一个，所以，指针域可以定死成一个指针。

最后一个方法一般人想不出来，所以压轴登场。它也是最优的方法。在这个方法里，指针域被定死成两个指针，一个指针指向First child node，另一个指针指向Next sibling node，在这个方法中，各个节点的组织形式已经不是树了，而是一张网。如下图所示。

![image-20240814182947329](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408141829481.png)

![绘图1](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408150822184.png)



上述所说的四种方法适用于所有种类的树，但若树的种类已经确定，还可以根据其具体类型用更贴近其类型特性的方法去实现树，比如下文的二叉树，使用的并不是上面的四种方法，而是用更适合二叉树的方法来实现的。

------

在日常生活中，最常见的树就是电脑的文件系统。对于Linux来说，其文件系统就是一棵树，而Windows的文件系统则是森林。

![image-20240815084137491](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408150841708.png)

比如这台电脑，就有一些盘，每个盘就是一棵树，点击一个盘，就可以看到这个盘下的子树，这些子树以文件夹的形式呈现。它们之间是兄弟关系。

![image-20240815084450052](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408150844312.png)

下面的是Linux文件系统

![image-20240815085021111](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408150850247.png)

-------

## 二叉树

前面都是前言，了解一下即可，下面的才是重点。

二叉树是树的一种。在二叉树中，节点的最大度为2。除此之外，二叉树的子树有左右之分，次序不能颠倒。

![image-20240815090404391](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408150904501.png)

注意：对于任意的二叉树都是由以下几种情况复合而成的：  

![image-20240815090508389](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408150905442.png)

-------

#### 完全二叉树和满二叉树

完全二叉树是二叉树中的一种。对于一棵深度为H的满二叉树来说，前H-1层必须是满的，最后一层可以不满，但必须是左右连续的。

比如这就是一个完全二叉树

![绘图1](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408150919206.png)

这就不是完全二叉树

![绘图1](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408150921949.png)

现在问题来了，该如何计算节点最多的完全二叉树节点数目。

当完全二叉树节点最多时，它的每一层都是满的。此时，它的第一层节点数为$2^0$，第二层为$2^1$，第三层为$2^2$，第I层为$2^{I-1}$，所以，数的总节点数就是
$$
F(N) = 2^0+2^1+2^2+……+2^{I-2}+2^{I-1}
$$
根据等比数列和的公式
$$
S_N=a_1\frac{1-r^N}{1-r}=a_1(\frac{1}{1-r}-\frac{r^N}{1-r})
$$
可得出，节点个数为$2^I-1$。

也可以用错位相减法
$$
F(N) = 2^0+2^1+2^2+……+2^{I-2}+2^{I-1}
$$

$$
2F(N) = 2^1+2^2+……+2^{I-2}+2^{I-1}+2^I
$$

$$
F(N) = 2F(N)-F(N) = 2^I-1
$$

所以，对于深度为H的完全二叉树来说，其最大的节点个数为$2^H-1$。

再来一个问题，对于深度为H的完全二叉树来说，其最小的节点个数为多少。

当完全二叉树节点数目最小时，它的最后一层只有一个节点。如果它的深度为H，则前H-1层的节点总个数为$2^{H-1}-1$，再加上一，就是$2^{H-1}$。

所以，对于深度为H的完全二叉树来说，其最小的节点个数为$2^{H-1}$。

------

满二叉树是完全二叉树的一种。顾名思义，满二叉树就是满的完全二叉树，也就是上面说的节点个数最多的完全二叉树。

![绘图1](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408150921949.png)

#### 实现二叉树

二叉树的实现有两种，一种就是按照上文介绍的那样去实现。由于二叉树长得比较规整，那就可以在指针域里放两个或三个指针，分别指向两个子节点及双亲节点。

不过，由于二叉树长得确实很整齐。日常中往往用第二种方式来实现。第二种方式底层是顺序表，成员类型就是数据类型，成员之间依靠下标判断相互关系。

具体流程是把节点中的数据按照由浅到深，有左到右的顺序放入顺序表中。

当想找到一个节点的子节点时，它的第一个子节点下标就是它自己的下标乘2再加1，它的第二个子节点下标就是它自己的下标乘2再加2。
$$
FirstChild = Parent *2 +1
$$

$$
SecondChild = Parent * 2 + 2
$$

如果是子节点找双亲节点则是
$$
Parent = \frac{FirstChild - 1}{2}=\frac{SecondChild - 2}{2}
$$
不过由于计算机的除法是整除，所以也可以被总结为
$$
Parent = \frac{Child - 1}{2}
$$


![image-20240815110919830](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408151109977.png)

从中可以看到，这种组织形式更适合完全二叉树。

#### 堆

注意，内存里也有一个堆，而这里的堆指的是数据结构的堆，它们不是同一个概念。

堆是满二叉树的一种。在堆中，双亲节点与子节点中存储的数据有着严格的次序要求。堆有两种。一是大堆，二是小堆。

对于大（根）堆，其中的双亲节点中的数据要大于或等于子节点中的。对于小（根）堆，其中双亲节点中的数据要小于或等于子节点。

![image-20240815112731835](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408151127967.png)

注意，对于物理结构的顺序表来说，这个顺序表不是有序顺序表。

#### 实现堆

##### 定义堆

```c
typedef int HeapData, * pHeapData;
typedef struct Heap
{
	pHeapData _pArray;
	int _Capacity;
	int _Size;
}Heap, * pHeap;
```

##### 定义相对大小

```c
bool greater(HeapData Max, HeapData Min)
{
	return (Max >= Min);
}
```

上面说过，堆层与层之间是有严格次序的，为此需要专门写一个函数去定义什么是小，什么是大。以后我们可能会修改`HeapData`的类型，比如，变成`char`，变成`double`，甚至变成其它的结构体。这时候只要改这一个函数就行了。除此之外，你可能会奇怪为什么要加个括号，这个暂且先不谈。

##### 初始化

```c
pHeap HeapInit(void)
{
	pHeap p = (pHeap)malloc(sizeof(Heap));
	if (p == NULL)
	{
		perror("HeapInit malloc fail");
		return NULL;
	}
	pHeapData pArr = (pHeapData)malloc(sizeof(HeapData));
	if (pArr == NULL)
	{
		perror("Array malloc fail");
		free(p);
		return NULL;
	}
	p->_pArray = pArr;
	p->_Capacity = 1;
	p->_Size = 0;
	return p;
}
```

没什么好说的。

##### 销毁

```c
void HeapDestroy(pHeap pH)
{
	assert(pH);
	free(pH->_pArray);
	pH->_pArray = NULL;
	pH->_Capacity = 0;
	pH->_Size = 0;
	free(pH);
}
```

还是没什么好说的

##### 插入数据

还是像以前一样，在插入数据之前先要判断够不够插入数据，不够，就要扩展。

###### 扩展

我的扩展逻辑是每次扩展都把它的下一层整个扩展出来。为此，在实现扩展之前，需要先写两个函数。

-------

首先需要写一个函数去计算当前二叉树的深度，依据上文中的分析，可以得出二叉树的深度计算公式为
$$
depth(x) = log2(x + 1)
$$


```c
static int depth(int val)
{
	val++;
	double natural = (double)val;
	double x = log2(natural);
	return (int)x;
}
```

函数`log2`的参数及返回值都是`double`，因此需要进行强制类型转换。我最初担心强制类型转换会把它的数据弄乱，测试之后，发现没有。估计是因为当初学指针的时候，时不时就对一个整型取地址，然后对地址强转成其它指针，再对得到的指针解引用，然后它的数值自然乱了，所以有这种担心。而在这里强转的不是指针，只要小心一点，就不会出现数值错乱问题。

------

第二个函数是依据二叉树深度计算它的总结点个数

```c
static int total(int val)
{
	double exponent = (double)val;
	double x = exp2(exponent);
	return (int)x;
}
```

没什么好说的

------

然后我们的扩展函数就写出来了

```c
static void HeapDilatation(pHeap pH)
{
	assert(pH);
	int n = depth(pH->_Capacity);
	int NewCapacity = total(++n);
	pHeapData p = (pHeapData)realloc(pH->_pArray, sizeof(HeapData)*NewCapacity);
	if (p == NULL)
	{
		perror("HeapDilatation realloc fail");
		return;
	}
	pH->_pArray = p;
	pH->_Capacity = NewCapacity;
	return;
}
```

###### 调整

插入数据本身并不是什么难事，但如果插入的数据破坏了层与层之间的相对大小，就需要对其进行调整。

如何进行调整呢？比如说，现在有一个小堆：

![绘图1](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408151636686.png)



现在要插入一个“6”，可以看到，插入之后，次序关系被破坏了

![绘图1](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408151638006.png)

这时就需要调整，调整起来也很简单，交换一下数据就行

![绘图1](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408151640140.png)

交换之后，发现2,3层的关系正确了，1,2层关系又被破坏了，所以需要再调整

![绘图1](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408151642462.png)

现在已经调整到根节点了，因此不需要调整了。

从上面的关系中，我们可以看到，需要找双亲节点，所以要先写对应函数

`````c
static int FindParent(int Child, int Size)
{
	int ret = (Child - 1) / 2;
	if (ret >= 0)
	{
		return ret;
	}
	else
	{
		return EOF;
	}
}
`````

如果找到一个非法坐标，就返回`EOF`，这里的`Size`主要是为接口统一性而存在的，实际并无意义。既然找双亲都写出来了，也顺便写写找孩子。

```c
static int FindFirstChild(int Parent, int Size)
{
	int ret = Parent * 2 + 1;
	if (ret < Size)
	{
		return ret;
	}
	else
	{
		return EOF;
	}
}

static int FindSecondChild(int Parent, int Size)
{
	int ret = Parent * 2 + 2;
	if (ret < Size)
	{
		return ret;
	}
	else
	{
		return EOF;
	}
}
```

这里的`Size`真用上了，用来判断坐标是否合法。

------

然后就能写调整函数了

```c
void adjustUP(HeapData* pArray, int Size, int Child)
{
	assert(pArray);
	int Parent = 0;
	while (Child > 0)
	{
		Parent = FindParent(Child, Size);
		if (rule(pArray[Child], pArray[Parent]))
		{
			break;
		}
		else
		{
			Swap(&(pArray[Child]), &(pArray[Parent]));
			Child = Parent;
		}
	}
}
```

为什么要加一个"UP"，其一是因为，从上面的过程中，可以看到它确实是向上调整，从二是因为，后面还有一个向下调整。这里用数组首元素指针的方式传参而不用堆指针传参也是有深意的，具体后面讲。

注意循环跳出条件是`Child == 0`，可以看到，`Child`最后是由`Parent`赋值的，当`Child == 0`就意味着下标为0的那个节点，也就是根节点已经被动过了，那就不需要再调整了。

这里的交换函数是自己写的，主要是害怕出现类型匹配问题。也能增加可读性，不是吗？

------

调整也写好了，那就写插入函数了

```c
void HeapPush(pHeap pH, HeapData val)
{
	assert(pH);
	if (pH->_Capacity == pH->_Size)
	{
		HeapDilatation(pH);
	}
	pH->_pArray[pH->_Size++] = val;
	adjustUP(pH->_pArray, pH->_Size, pH->_Size - 1);
}
```

#### 测试

现在项目已经可以初步测试了，让我们测试一下，随便找个数组来做插入数据。

```c
void test1()
{
	pHeap pH = HeapInit();
	int arr[] = { 65,100,70,32,50,60 };
	int sz = sizeof(arr)/sizeof(arr[0]);
	int current = 0;
	for(current = 0; current < sz; current++)
	{
		int i = arr[current];
		HeapPush(pH, i);
	}
	HeapDestroy(pH);
	pH = NULL;
}
```

<video src="https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408151706053.mp4"></video>

可以看到，插入后的数组为[ 32, 50, 60, 100, 65, 70]，确实是个小堆。

那怎么变成大堆呢？还记得前面埋的坑吗？为什么要打括号，打括号是为了确保先判断相对大小，当我们在括号前加个取反号，就能变成大堆了。

<video src="https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408151715455.mp4"></video>

当然，现在想来，这个函数的名字取得不太好，或许叫"rule"更好，防止加取反号之后，被人误会，以为前面那个数字更大。算了，让未来的我改好了。以后出问题我肯定会看这个文档的。

算了，现在就换吧，使用VS一键替换功能：`ctrl`+`H`，替换后，重新生成解决方案，没有问题，替换成功。

修改之后，函数的定义是这样的：

//该函数共有两种模式
//模式一：不带取反号，此时为小根堆模式。
//模式二：带取反号，此时为大根堆模式。
//如果参数"child""parent"满足对应堆的规则，就返回真，否则返回假。

```c
// This function has two modes.
// Mode 1: Without negation, it operates in min-heap mode.
// Mode 2: With negation, it operates in max-heap mode.
// If the parameters "child" and "parent" satisfy the corresponding heap rules, it returns true; otherwise, it returns false.
bool rule(HeapData child, HeapData parent)
{
	return (child >= parent);
}
```

#### 删除

首先，我们需要想一下，删除时应该删除哪个成员。是删除最后一个成员吗？我的回答是如是。俗话说“枪打出头鸟”“擒贼先擒王”，要删除，就要删除最特别的那一个，哪个最特别呢？很明显，就是根节点。由于堆的自身性质，根节点中的数据是众节点中的极值，要么是最小的，要么是最大的。所以要删除的是根节点。

确定删的是根节点，接下来就要讨论怎么删？直接删吗？就像顺序表头删那样，把其它成员整体向前挪一格。比如上面的堆，其顺序表形式是[ 32, 50, 60, 100, 65, 70]，按照这种删法，就变成了[50, 60, 100, 65, 70]，这就带来两个问题，一，全部成员都需要前移，时间复杂度太大了，二，移过之后，辈分乱了，原来[50]\[60]是兄弟关系，现在变成父子了，整个堆的框架全乱了，如果想重新调整成堆，就需要像上面测试那样，逐个读取数组中的值，然后再逐个插入到一个新的堆里。

很明显，不能直接删。那怎么删呢？我们首先让堆的首元素和最后一个元素交换一下，然后再把最后一个元素删除，所以我上面说是“如是”。它确实是删除首元素，但它的删除方式是先让首元素与最后一个元素交换，再删除交换后的最后一个元素。这样做的好处是，只会破坏某两层间的大小关系，但其它层之间的大小关系并没有被打破，各节点间的辈分也没有被完全破坏。堆的大框架还是在的。

堆的大框架在的好处就是允许我们进行调整，这就是我们之前说的向下调整。

还是以[ 32, 50, 60, 100, 65, 70]为例。

![绘图1](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408191421683.png)

先首尾交换，再删尾节点

![绘图1](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408191423555.png)

可以看到，只有一二层间的关系被破坏了。接下来就是向下调整，先看初始节点（在这里是根节点）的两个子节点，看一下它们两个中谁更适合做双亲节点。怎么看呢？用上面刚刚写出的函数`rule`来判断。比如这里，根节点的子节点[50]\[60]中[50]更适合做双亲节点，所以就选[50]，接下来，再拿这个[50]和它的双亲节点[70]用`rule`判断一下，看看目前它俩现在是否符合规则。不符合，就交换。

![绘图1](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408191432308.png)

现在，一二两层的关系已经被修复好了。二三层的关系可能被破坏了，再重复一下上面的步骤。

![绘图1](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408191436944.png)

现在找不到子节点了，那就调整完了。

下面写代码：

像往常一样，如果堆已经是空的了，那就不能删，所以顺手写写堆的大小和判空函数。

```c
int HeapSize(pHeap pH)
{
	assert(pH);
	return pH->_Size;
}

bool HeapEmpty(pHeap pH)
{
	assert(pH);
	return (HeapSize(pH) == 0);
}
```

正常来说，删除只要让`_Size--`即可，但为了在调试时，调试时窗口有反应，就是变红了，我打算再找个值覆写到尾元素上，那问题就来了，到底覆写什么呢？我的思路是让它回归刚被`realloc`开辟的状态，VS对`realloc`的实现逻辑是，在开辟出那块内存块后，再往里面写`0xcd`，直到把那块内存块填满。所以我的做法是，先用`realloc`开辟个大小为`sizeof(HeapData)`的内存块，再把这里的值，覆写到末尾成员上，然后再`_Size--`。我并不直接手动往末尾成员上写`0xcd`，一是因为麻烦，要弄几个指针强转类型；二是写`0xcd`只是VS的逻辑，其它`IDE(集成式开发环境)`不一定这样。当然，如果开辟失败，那没办法，就干脆返回个`(HeapData)0`，什么都不返回有的编译器直接就跑不动了，本人也有点强迫症，看到警告我也难受。

```c
static HeapData PopOverwriting(void)
{
	pHeapData p = (pHeapData)realloc(NULL, sizeof(HeapData));
	if (p == NULL)
	{
		perror("PopOverwriting realloc fail");
		return (HeapData)0;
	}
	HeapData ret = *p;
	free(p);
	return ret;
}
```

然后是向下调整

```c
void adjustDOWN(HeapData* pArray, int Size, int Parent)
{
	assert(pArray);
	int Child = 0;
	while (Parent < Size)
	{
		int FirstChild = FindFirstChild(Parent, Size);
		int SecondChild = FindSecondChild(Parent, Size);
		if (FirstChild != EOF && SecondChild != EOF)
		{
			if (rule(pArray[FirstChild], pArray[SecondChild]))
			{
				Child = SecondChild;
			}
			else
			{
				Child = FirstChild;
			}
		}
		else
		{
			if (FirstChild == EOF)
			{
				break;
			}
			else
			{
				Child = FirstChild;
			}
		}
		if (rule(pArray[Child], pArray[Parent]))
		{
			break;
		}
		else
		{
			Swap(&(pArray[Parent]), &(pArray[Child]));
			Parent = Child;
		}
	}
}
```

前面那个if是找Child的，后面那个if是看父子节点间是不是符合规则的，不符合，就交换，再循环。由于堆的前提条件是完全二叉树，所以没有第一个子节点，就一定没有第二个子节点。这里的循环条件其实无所谓，在Parent越出有效内存快前，肯定会到终端节点，然后因为没有子节点，就自动Break了，此处定位这个，一是与前面的向上调整形成类似的结构（对参数进行判断），二是这种写法比较好看。

最后是删除

```c
void HeapPop(pHeap pH)
{
	assert(pH);
	if (HeapEmpty(pH))
	{
		printf("This heap is already empty!\n");
		return;
	}
	else
	{
		Swap(&(pH->_pArray[0]), &(pH->_pArray[pH->_Size - 1]));
		pH->_pArray[pH->_Size - 1] = PopOverwriting();
		pH->_Size--;
		adjustDOWN(pH->_pArray, pH->_Size, 0);
	}
}
```

#### 测试

```c
void test2()
{
	pHeap pH = HeapInit();
	int arr[] = { 65,100,70,32,50,60 };
	int sz = sizeof(arr) / sizeof(arr[0]);
	int current = 0;
	for (current = 0; current < sz; current++)
	{
		int i = arr[current];
		HeapPush(pH, i);
	}
	HeapPop(pH);
	HeapDestroy(pH);
	pH = NULL;
}
```

<video src="https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408191533695.mp4"></video>

先是小堆，然后是大堆。

#### 读取根节点

```c
HeapData HeapTop(pHeap pH)
{
	assert(pH);
	assert(!HeapEmpty(pH));
	return pH->_pArray[0];
}
```

#### 测试

```c
void test3()
{
	pHeap pH = HeapInit();
	int arr[] = { 65,100,70,32,50,60 };
	int sz = sizeof(arr) / sizeof(arr[0]);
	int current = 0;
	for (current = 0; current < sz; current++)
	{
		int i = arr[current];
		HeapPush(pH, i);
	}
	while (!HeapEmpty(pH))
	{
		HeapData top = HeapTop(pH);
		printf("%d\n",top);
		HeapPop(pH);
	}
	HeapDestroy(pH);
	pH = NULL;
}
```

![image-20240819155108797](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408191551910.png)

看这结果是不是有点排序的感觉？但这还不是排序，只不过是打印。排序是输入一个乱序数据结构（一般是数组），然后输出一个对应的有序数据结构。

### 堆排序

------

第一个方法简单粗暴，先把源数组中的成员逐个插入一个新的堆，然后再读一下堆顶，删一下堆顶。把读到的值覆写到源数组上，循环迭代，直到堆为空。

```c
void HeapSort1(pHeapData pArray, int Size)
{
	assert(pArray);
	pHeap pH = HeapInit();
	int circulation = 0;
	for (circulation = 0; circulation < Size; circulation++)
	{
		HeapPush(pH, pArray[circulation]);
	}
	circulation = 0;
	while (!HeapEmpty(pH))
	{
		HeapData top = HeapTop(pH);
		pArray[circulation++] = top;
		HeapPop(pH);
	}
	HeapDestroy(pH);
	pH = NULL;
}
```

```c
void test4()
{
	HeapData arr[] = { 65,100,70,32,50,60 };
	int sz = sizeof(arr) / sizeof(arr[0]);
	HeapSort1(arr, sz);
	int cir = 0;
	for (; cir < sz; cir++)
	{
		printf("arr[%d]=%d\n", cir, arr[cir]);
	}
}
```

![image-20240819165141095](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408191651265.png)

看，在小堆模式下，得到的是升序数组。当然，简单粗暴是有代价的，从时间复杂度上来看，这种方法是先把一堆数据从一个地方拷贝到另一个地方，这样拷贝来拷贝去，麻烦。从空间复杂度来说，这种方法要新建堆，这新堆的大小大概率还比原数组大，浪费。

------

反正堆的物理结构就是数组，能不能在源数组上直接动刀？当然是可以的，但这样和上面的方法略微有些不同。

还是这个数组{ 65,100,70,32,50,60 }

![绘图1](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408201002844.png)

我们用一个指针，叫什么呢？就叫"current"吧，我们把"current"与数组起始地址间的部分称为“堆部分”；"current"与数组末尾地址间的部分称为“非堆部分”，下面为了区分，我们把“堆部分”标注为橙色，“非堆部分”标注为蓝色。

“current”最初应该在哪里呢？它应该指向“1”处，因为只有一个节点，所以无法比较相对大小，因此前面部分就自然而言成了堆。

![绘图1](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408201004664.png)

![绘图1](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408201004294.png)

之后，再把"current"向后移动一位，以移动后的"current"为初始地址（或者说子节点）进行向上调整，经过向上调整之后，前面部分就符合rule，于是就成了堆。

![绘图1](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408201005099.png)

![绘图1](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408201006475.png)

第二次迭代

![绘图1](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408201007553.png)

![绘图1](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408201008904.png)

第三次迭代

![绘图1](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408201010662.png)

![绘图1](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408201011633.png)

第四次迭代

![绘图1](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408201013544.png)

![绘图1](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408201013349.png)

第五次迭代

![绘图1](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408201015025.png)

![绘图1](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408201015479.png)

这就是上面的向上调整和向下调整算法要有三个接口：数组首元素地址，数组大小，起始下标，而不用一个`pH`了事的原因，这样可以让算法变得更加灵活，这两个调整算法不仅可以用于插入删除，也可以用于堆排序。

而且由于调整算法已经实现过了，在堆排序时，就不需要关心如何调整，而只需知道经过调整之后就会变成堆，我们只需要关注整体思想，细节不需要去想。从而有更清晰的代码逻辑。

------

现在我们已经把源数组修改成了小堆，接下来就是在小根堆的基础上进行排序了。然后就有一个问题，小根堆排出来的是升序数组还是降序数组呢？

让我们想一想，对于一个小根堆来说，它的根节点就是最小值，如果要形成一个升序数组的话，第一个元素就要是最小值，恰巧根节点就是首元素，所以现在根节点里的数据要保护起来，下面的步骤不能动这个根节点。然后就要找第二小的数据了，可现在根节点不能动，所以找不到第二小的数。所以排不出升序数组。

如果要排降序数组呢？对于一个小根堆来说，根节点就是最小值，现在要找第二小的值（也只能找第二小的值），为了找第二小的值，我们把现在的数组首尾元素交换，恰巧降序数组的最后一个元素要的就是最小值，之后为了保护这个最小值，我们把数组的大小减一，不把它视为数组的有效部分；然后以调整后的根节点为起始地址，经过向下调整后，找到第二小的数。为了便于区分，橙色代表数组的可操作部分（有效部分），蓝色代表数组的不可操作部分。

![绘图1](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408201039546.png)

![绘图1](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408201039771.png)

![绘图1](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408201040297.png)

![绘图1](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408201041351.png)

![绘图1](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408201044629.png)

![绘图1](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408201044162.png)

第二次迭代

![绘图1](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408201047491.png)

![绘图1](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408201047476.png)

第三次迭代

![绘图1](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408201049248.png)

![绘图1](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408201049340.png)

第四次迭代

![绘图1](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408201051248.png)

![绘图1](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408201052994.png)

第五次迭代

![绘图1](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408201053494.png)

![绘图1](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408201053276.png)

就剩一个元素了，那就不用调整了。跳出循环。

-------

思路都讲清楚了，下面直接写代码就行。

```c
void HeapSort2(pHeapData pArray, int Size)
{
	assert(pArray);
	int circulation = 0;
	for (circulation = 1; circulation < Size; circulation++)
	{
		adjustUP(pArray, circulation + 1, circulation);
	}
	for (circulation = Size - 1; circulation > 0; circulation--)
	{
		Swap(&(pArray[0]), &(pArray[circulation]));
		adjustDOWN(pArray, circulation, 0);
	}
}
```

```c
void test5()
{
	HeapData arr[] = { 65,100,70,32,50,60 };
	int sz = sizeof(arr) / sizeof(arr[0]);
	HeapSort2(arr, sz);
	int cir = 0;
	for (; cir < sz; cir++)
	{
		printf("arr[%d]=%d\n", cir, arr[cir]);
	}
}
```

![image-20240820105839001](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408201058147.png)

和测试中的打印不同，这里小根堆输出的是降序数组，那要是大根堆模式呢？

![image-20240820110104105](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408201101268.png)

那就是升序数组了。

-------

上面使用的是向上调整建堆，调整算法有两种，除了向上调整外还有向下调整，能不能用向下调整的方式建堆呢？当然是可以的。

首先我们需要明白，不论向上调整还是向下调整，其前提都是调整区域的大框架还是堆。而当节点只有一个时，由于无法进行比较，所以单就一个节点一定是堆，所以在上面的向上调整过程中，起始下标从堆的第二层开始；那对于向下调整来说，起始位置就在倒数第二层的最后一个节点，或者说，堆最后一个节点的双亲节点处。为便于区分，下图中把绿色部分视为将要被调整的子树，把蓝色部分视为还未调整的部分，橙色部分视为已经被调整符合堆规则的部分。

![绘图1](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408211428366.png)

![绘图1](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408211429038.png)

调整之后就变成了

![绘图1](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408211430310.png)

然后起始下标减减，就来到了之前起始下标的兄弟节点

![绘图1](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408211432798.png)

调整一下

![绘图1](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408211433178.png)

再减减，就来到了上一层。

![绘图1](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408211435303.png)

调整之后

![绘图1](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408211440014.png)

起始位置到根节点了，那就跳出循环。

写成代码就是

```c
void HeapSort(pHeapData pArray, int Size)
{
	assert(pArray);
	int circulation = 0;
	for (circulation = FindParent(Size - 1, Size); circulation >= 0; circulation--)
	{
		adjustDOWN(pArray, Size, circulation);
	}
	for (circulation = Size - 1; circulation > 0; circulation--)
	{
		Swap(&(pArray[0]), &(pArray[circulation]));
		adjustDOWN(pArray, circulation, 0);
	}
}
```

```c
void test6()
{
	HeapData arr[] = { 65,100,70,32,50,60,85 };
	int sz = sizeof(arr) / sizeof(arr[0]);
	HeapSort(arr, sz);
	int cir = 0;
	for (; cir < sz; cir++)
	{
		printf("arr[%d]=%d\n", cir, arr[cir]);
	}
}
```

![image-20240821144838933](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408211448077.png)

既然有多个堆排序，那就用复杂度比较一下，第一个堆排序就不比较了，就是模仿打印逻辑的那个。

首先看一看向下调整建堆的时间复杂度。

为了便于讨论，同时也是为了符合复杂度最坏情况的要求，我们假设，原数组中共有N个元素，这N个元素可以建立一个满二叉树。

如果用H表示这个二叉树的深度，则有
$$
N = 2^0+2^1+2^2+……+2^{H-2}+2^{H-1} = 2^H-1
$$

$$
H(N) = log_2(N+1)
$$

![绘图1](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408211506373.png)

第一层，有$2^{1-1}$个节点，每个节点最多调整$H-1$次

第二层，有$2^{2-1}$个节点，每个节点最多调整$H-2$次

第三层，有$2^{3-1}$个节点，每个节点最多调整$H-3$次

第四层，有$2^{4-1}$个节点，每个节点最多调整$H-4$次

·······························

第H-2层，有$2^{H-2-1}$个节点，每个节点最多调整$2$次

第H-1层，有$2^{H-1-1}$个节点，每个节点最多调整$1$次

第H层，不用调整。

于是就有
$$
F(H) = 2^0*(H-1)+2^1*(H-2)+2^2*(H-3)+2^3*(H-4)+……2^{H-3}*2+2^{H-2}*1
$$
利用错位相减法求解
$$
2F(H) =  2^1*(H-1)+2^2*(H-2)+2^3*(H-3)+2^4*(H-4)+……2^{H-2}*2+2^{H-1}*1
$$

$$
F(H) = 2F(H) - F(H) = 2^1*[(H-1)-(H-2)]+……+ 2^{H-2}*(2-1)+2^{H-1}*1-2^0*(H-1)
$$

$$
F(H) = 2^1 + 2^2 +……+2^{H-2}+2^{H-1}-2^0*(H-1)
$$

$$
F(H) = 2^1 + 2^2 +……+2^{H-2}+2^{H-1}+2^0-H
$$

$$
F(H) = 2^0+2^1+2^2+……+2^{H-2}+2^{H-1}-H
$$

复杂度是以数据个数N计算的
$$
F(N) = N -log_2(N+1)
$$
复杂度看的是粗略值，这个式子可以分为两部分：

线性部分：$N$                          复杂度为$N$

非线性部分：$-log_2(N+1)$   复杂度为$log_2N$

在大$N$的情况下，线性部分增长速度远高于非线性部分，所以整体复杂度由线性部分主导。

综上，向下调整建堆的时间复杂度为$O(N)$。

---------

对于向上调整有

第一层，不用调整

第二层，有$2^{2-1}$个节点，每个节点最多调整$1$次

第三层，有$2^{3-1}$个节点，每个节点最多调整$2$次

第四层，有$2^{4-1}$个节点，每个节点最多调整$3$次

·······························

第H-2层，有$2^{H-3}$个节点，每个节点最多调整$H-3$次

第H-1层，有$2^{H-2}$个节点，每个节点最多调整$H-2$次

第H层，有$2^{H-1}$个节点，每个节点最多调整$H-1$次
$$
F(H) = 2^1*1+2^2*2+……+2^{H-2}*(H-2)+2^{H-1}*(H-1)
$$

$$
2F(H) = 2^2*1+2^3*2+……+2^{H-1}*(H-2)+2^{H}*(H-1)
$$

$$
F(H) = 2F(H)-F(H)=2^2*(1-2)+2^3*(2-3)+……+2^{H-1}*[(H-2)-(H-1)]+2^H*(H-1)-2^1*1
$$

$$
F(H)=-2^2-2^3-……-2^{H-1}-2^1+2^H*(H-1)
$$

$$
F(H)=-(2^1+2^2+……+2^{H-1})+2^H*(H-1)
$$

$$
F(H)=-(2^0+2^1+2^2+……+2^{H-1}-2^0)+2^H*H-2^H
$$

$$
F(H)=-(2^0+2^1+2^2+……+2^{H-1})+2^0+2^H*H-2^H
$$

$$
F(N) = -N+1+(N+1)*log_2(N+1)-(N+1)
$$

$$
F(N) = (N+1)*log_2(N+1)-2N
$$

复杂度看的是粗略值，这个式子可以分成两个部分：

线性乘以非线性部分：$(N+1)*log_2(N+1)$   复杂度为$N*log_2N$

线性部分：                  $-2N$                               复杂度为$N$

在大$N$的情况下，线性乘以非线性部分增长速度远高于线性部分，所以整体复杂度由线性乘以非线性部分主导。

综上，向上调整建堆的时间复杂度为$O(N*log_2N)$。

----------

由时间复杂度可知，向下调整建堆优于向上调整建堆。

下面来看看排序过程的时间复杂度。

第H层，有$2^{H-1}$个节点，也就是说，要交换$2^{H-1}$次，每次交换完后，最多再调整$H-1$次

第H-1层，有$2^{H-2}$个节点，也就是说，要交换$2^{H-2}$次，每次交换完后，最多再调整$H-2$次

·······························

第三层，有$2^{3-1}$个节点，也就是说，要交换$2^{3-1}$次，每次交换完后，最多再调整$2$次

第二层，有$2^{2-1}$个节点，也就是说，要交换$2^{2-1}$次，每次交换完后，最多再调整$1$次

第一层，跳出循环
$$
F(H) = 2^1*1+2^2*2+……+2^{H-2}*(H-2)+2^{H-1}*(H-1)
$$
这不和向上调整建堆一样吗？所以

排序的时间复杂度为$O(N*log_2N)$。

那么如果采用向下建堆方式写成的堆排序，其复杂度准确描述就为$O(N+N*log_2N)$；粗略描述就是$O(N*log_2N)$。

如果采用向上建堆方式写成的堆排序，其复杂度准确描述就为$O(2N*log_2N)$；粗略描述就是$O(N*log_2N)$。

所以，复杂度一样，不代表它俩时间消耗都一样，复杂度一样的还可能是精度不够，比不出来。

--------

