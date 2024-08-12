# 顺序表和链表

数据结构是管理数据各种方法的集合，每种数据结构都有各自的优缺点，所以没有最好的数据结构，只有最适合的数据结构，下面我们将学顺序表。

## 顺序表

顺序表是最简单的数据结构，所以适合作为数据结构的门槛，它的底层是数组，得益于数组元素地址的连续性，顺序表可以借助于下标访问其中的任意数据，但正因如此，在面对数据的插入删除时，顺序表的时间复杂度将会很高。

### 静态顺序表

静态顺序表在栈上开辟，其内存大小固定，这使得它无法根据存储数据的具体个数对内存大小进行动态调整，从而造成诸如空间利用效率过低，存不下超出规定个数的数据群等问题，在日常开发过程中极少使用，一般只作为教学示例，本文将动态顺序表作为介绍主体，下列代码只定义静态顺序表的类型

```c
#define TotalNumber 10
typedef int SLDataType;
typedef struct SeqList
{
    SLDataType arr[TotalNumber];
    int validNumber;
}SeqList;
```

### 动态顺序表

#### 定义顺序表

```c
//将顺序表中存储的数据类型重命名，便于日后管理
typedef int SLDataType;

//使用结构体实现顺序表
typedef struct SeqList
{
	SLDataType* p;          
	int total;              //可容纳的最大个数
	int valid;				//有效数据个数
}SeqList,* PSeqList;
```

有人说使用结构体的柔性数组来实现“动态”，可以是可以，但柔性数组有自己的应用场景，一般不用柔性数组实现顺序表。

#### 获得一个顺序表

为了能够修改上一级函数中的顺序表成员，我们的顺序表函数将把顺序表指针作为标准接口。创建和初始化顺序表都交由具体函数来实现，防止有人乱传指针：

```c
//获得一个已被初始化的顺序表指针
PSeqList SeqListGet(void)
{
	PSeqList ps = (PSeqList)malloc(sizeof(SeqList));
	if (ps == NULL)
	{
		perror("GetSeqList malloc fail");
		return NULL;
	}
	ps->p = NULL;
	ps->total = 0;
	ps->valid = 0;
	return ps;
}
```

#### 销毁顺序表

为了接口的统一性，此处仍旧使用一级指针，在使用完后，要对参数置空。

```c
//销毁顺序表
void SeqListDestroy(PSeqList ps)
{
	if (ps == NULL)
	{
		printf("Invalid parameter!");
		return;
	}
	free(ps->p);
	ps->p = NULL;
	ps->total = 0;
	ps->valid = 0;
	free(ps);
	ps = NULL;
}
```

#### 尾插

为了确保有额外空间可被插入，需要先编写顺序表扩展函数，是否扩展由外层函数决定，而不由扩展函数主动判断，这样做是为了减少扩展函数栈帧的开辟次数，扩展函数将由`static`修饰，用于取消外部链接属性，避免用户直接使用，防止不经判断而直接使用

```c
static void SeqListExpandCapacity(PSeqList ps)
{
	int newsize = 0;
	SLDataType* pnew = NULL;
	newsize = ps->total == 0 ? 4 : ps->total * 2;
	pnew = (SLDataType*)realloc(ps->p, sizeof(SLDataType) * newsize);
	if (pnew == NULL)
	{
		printf("SeqListExpandCapacity malloc fail");
		return;
	}
	ps->p = pnew;
	ps->total = newsize;
}
```

```c
void SeqListPushBack(PSeqList ps, SLDataType x)
{
	if (ps == NULL)
	{
		printf("Invalid parameter!");
		return;
	}
	if (ps->total == ps->valid)
	{
		SeqListExpandCapacity(ps);
	}
	ps->p[ps->valid++] = x;
}
```

#### 打印顺序表

用于测试目的，只适用于顺序表存储类型是`int`的场景，负责打印顺序表中的所有整型数据。

```c
void SeqListPrintf(const PSeqList ps)
{
	if (ps == NULL)
	{
		printf("Invalid parameter!");
		return;
	}
	int cir = 0;
	for (cir = 0; cir < ps->valid; cir++)
	{
		printf("%d ", ps->p[cir]);
	}
}
```

#### 对尾插函数的测试

```c
int main()
{
	PSeqList ps = SeqListGet();
	SeqListPushBack(ps, 1);
	SeqListPushBack(ps, 2);
	SeqListPushBack(ps, 3);
	SeqListPushBack(ps, 4);
	SeqListPushBack(ps, 5);
	SeqListPushBack(ps, 6);
	SeqListPushBack(ps, 7);
	SeqListPushBack(ps, 8);
	SeqListPushBack(ps, 9);
	SeqListPushBack(ps, 10);
	SeqListPrintf(ps);
	SeqListDestroy(ps);
	ps = NULL;
	return 0;
}
```

![image-20240725175559315](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202407251755472.png)

经测试，程序当前运行正常，无内存泄露，达到预期效果。

#### 头插

考虑到顺序表头插算法时间复杂度过高，建议您最好不要以头插方式插入数据。

```c
void SeqListPushFront(PSeqList ps, SLDataType x)
{
	if (ps == NULL)
	{
		printf("Invalid parameter!");
		return;
	}
	if (ps->total == ps->valid)
	{
		SeqListExpandCapacity(ps);
	}
	int cir = 0;
	for (cir = ps->valid; cir > 0; cir--)
	{
		ps->p[cir] = ps->p[cir - 1];
	}
	ps->p[0] = x;
	ps->valid++;
}
```

#### 对头插函数的测试

```c
void SeqListTest2()
{
	PSeqList ps = SeqListGet();
	SeqListPushBack(ps, 5);
	SeqListPushBack(ps, 6);
	SeqListPushBack(ps, 7);
	SeqListPushBack(ps, 8);
	SeqListPushFront(ps, 4);
	SeqListPushFront(ps, 3);
	SeqListPushFront(ps, 2);
	SeqListPushFront(ps, 1);
	SeqListPushBack(ps, 9);
	SeqListPushBack(ps, 10);
	SeqListPrintf(ps);
	SeqListDestroy(ps);
	ps = NULL;
}
```

![image-20240726082516721](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202407260825859.png)

经测试，程序当前运行正常，无内存泄露，达到预期效果。

#### 尾删

本来，似乎直接把顺序表有效个数减一即可，但是为了提高安全性，对于无效的数据，将会仿照`Visual Studio`中`malloc`的逻辑，将无效数据覆写为`0xcd`。

```c
void SeqListPopBack(PSeqList ps)
{
	if (ps->valid == 0)
	{
		printf("No data available for deletion!");
		return;
	}
	size_t cir = sizeof(SLDataType);
	char* p = (char*)(ps->p + (ps->valid - 1));
	while (cir--)
	{
		*p = 0xcd;
		p++;
	}
	p = NULL;
	ps->valid--;
}
```

#### 链接型BUG

在调试时，遇到与动态开辟有关的函数时，反复弹出窗口：

![663d438328f353136ac47aca6722b7f](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202407261332897.png)

解决方案一：

询问AI，回答：

“提示“未找到 `crtmfcpatch.h`在使用 `realloc `时，通常表示你的开发环境中缺少与 `MFC`（Microsoft Foundation Classes）相关的文件。这个问题可能由以下原因引起：

- `MFC `组件缺失：确保在安装 Visual Studio 时选择了` MFC `组件。如果没有安装，可以通过 Visual Studio Installer 进行修改并添加 `MFC` 支持。
- 项目配置问题：检查你的项目设置，确保包含目录（Include Directories）中包含了 `MFC `的路径。
- 安装损坏：如果 `MFC` 已安装但仍然出现此错误，可能需要修复或重新安装 Visual Studio。
- 环境变量问题：确保你的环境变量（如 INCLUDE 和 LIB）正确配置，指向包含` MFC` 文件的目录。

建议你检查这些设置，并确保 `MFC` 组件已正确安装。如果问题仍然存在，可以尝试修复 Visual Studio 安装。”

对VS进行更新，更新后，VS整体崩溃，启用VS修复选项。

解决方案二：

成功修复并重新配置相关设置后。查看详细信息，提示：找不到文件 `d:\work\vld\crtmfcpatch.h`,推测是内存检测工具`vld`存在链接错误。注释头文件`vld.h`发现，调试畅通无阻，窗口真的再也没弹出来；取消注释，在执行动态开辟函数时，再次弹出窗口，问题锁定，确认为头文件`vld.h`缺乏必要文件支持。考虑到内存检测工具`vld`为开源项目，去`github`下载了整个项目，在项目文件夹下搜索`crtmfcpatch.h`，成功找到，在取消注释情况下，再次调试，执行动态开辟相关函数时，弹窗预期弹出，手动添加包含文件`crtmfcpatch.h`的库，弹窗解除，成功运行，调试正常。

<video src="https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202407261401505.mp4"></video>

#### 回到尾删

下列视频显示VS对`realloc`开辟的空间覆写为`0xcd`：

<video src="https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202407261426106.mp4"></video>

测试之后，无效数据按预期被覆盖为`0xcd`，尾删运行正常：

```c
void SeqListTest3()
{
	PSeqList ps = SeqListGet();
	SeqListPushBack(ps, 5);
	SeqListPushBack(ps, 6);
	SeqListPushBack(ps, 7);
	SeqListPushBack(ps, 8);
	SeqListPushFront(ps, 4);
	SeqListPushFront(ps, 3);
	SeqListPushFront(ps, 2);
	SeqListPushFront(ps, 1);
	SeqListPushBack(ps, 9);
	SeqListPushBack(ps, 10);
	SeqListPrintf(ps);
	SeqListPopBack(ps);
	SeqListPopBack(ps);
	SeqListPopBack(ps);
	SeqListPopBack(ps);
	SeqListPrintf(ps);
	SeqListDestroy(ps);
	ps = NULL;
}
```

![image-20240726144824453](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202407261448544.png)

#### 头删

考虑到头删时间复杂度较高，不建议使用该方式删除数据

```c
void SeqListPopFront(PSeqList ps)
{
	if (ps->valid == 0)
	{
		printf("No data available for deletion!");
		return;
	}
	int i = 0;
	for (i = 0; i < ps->valid - 1; i++)
	{
		ps->p[i] = ps->p[i + 1];
	}
	size_t cir = sizeof(SLDataType);
	char* p = (char*)(ps->p + (ps->valid - 1));
	while (cir--)
	{
		*p = 0xcd;
		p++;
	}
	p = NULL;
	ps->valid--;
}
```

#### 测试头删

```c
void SeqListTest4()
{
	PSeqList ps = SeqListGet();
	SeqListPushBack(ps, 5);
	SeqListPushBack(ps, 6);
	SeqListPushBack(ps, 7);
	SeqListPushBack(ps, 8);
	SeqListPushFront(ps, 4);
	SeqListPushFront(ps, 3);
	SeqListPushFront(ps, 2);
	SeqListPushFront(ps, 1);
	SeqListPushBack(ps, 9);
	SeqListPushBack(ps, 10);
	SeqListPrintf(ps);
	SeqListPopBack(ps);
	SeqListPopBack(ps);
	SeqListPopBack(ps);
	SeqListPopBack(ps);
	SeqListPrintf(ps);
	SeqListPopFront(ps);
	SeqListPrintf(ps);
	SeqListPopFront(ps);
	SeqListPrintf(ps);
	SeqListPopFront(ps);
	SeqListPrintf(ps);
	SeqListPopFront(ps);
	SeqListDestroy(ps);
	ps = NULL;
}
```

<video src="https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202407261535277.mp4"></video>

正常。

#### 指定位置插入

```c
void SeqListInsert(PSeqList ps, int pos, SLDataType x)
{
	if (ps == NULL)
	{
		printf("Invalid parameter!\n");
		return;
	}
	if (ps->total == ps->valid)
	{
		SeqListExpandCapacity(ps);
	}
	if ((pos >= 0) && (pos <= ps->valid))
	{
		int cir = 0;
		for (cir = ps->valid; cir > pos; cir--)
		{
			ps->p[cir] = ps->p[cir-1];
		}
		ps->p[pos] = x;
		ps->valid++;
	}
	else
	{
		printf("Invalid coordinates!\n");
	}
}
```

调试结果正常，另外，前面错误信息的字符串最后加了换行：

<video src="https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202407261635951.mp4"></video>

#### 指定位置删除

```c
void SeqListErase(PSeqList ps, int pos)
{
	if (ps->valid == 0)
	{
		printf("No data available for deletion!\n");
		return;
	}
	if ((pos >= 0) && (pos < ps->valid))
	{
		int i = 0;
		for (i = pos; i < ps->valid - 1; i++)
		{
			ps->p[i] = ps->p[i + 1];
		}
		size_t cir = sizeof(SLDataType);
		char* p = (char*)(ps->p + (ps->valid - 1));
		while (cir--)
		{
			*p = 0xcd;
			p++;
		}
		p = NULL;
		ps->valid--;
		return;
	}
	else
	{
		printf("Invalid coordinates!\n");
		return;
	}
}
```

#### 指定位置删除测试

```c
void SeqListTest6()
{
	PSeqList ps = SeqListGet();
	SeqListPushBack(ps, 5);
	SeqListPushBack(ps, 6);
	SeqListPushBack(ps, 8);
	SeqListPushFront(ps, 4);
	SeqListPushFront(ps, 1);
	SeqListPrintf(ps);
	SeqListInsert(ps, 1, 3);
	SeqListInsert(ps, 1, 2);
	SeqListPrintf(ps);
	SeqListInsert(ps, 6, 7);
	SeqListPrintf(ps);
	SeqListPopBack(ps);
	SeqListPopFront(ps);
	SeqListPrintf(ps);
	SeqListErase(ps, 2);
	SeqListErase(ps,2);
	SeqListPrintf(ps);
	SeqListDestroy(ps);
	ps = NULL;
}
```

![image-20240726170415363](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202407261704493.png)

测试通过。

#### 查找数据

若找到，返回其对应下标；若找不到，则返回EOF

```c
int SeqListFind(const PSeqList ps, int pos)
{
	if (ps == NULL)
	{
		printf("Invalid parameter!\n");
		return EOF;
	}
	int cir = 0;
	for (cir = 0; cir < ps->valid; cir++)
	{
		if (ps->p[cir] == pos)
		{
			return cir;
		}
	}
	return EOF;
}
```

#### 修改指定位置数据

```c
void SeqListModify(PSeqList ps, int pos, SLDataType x)
{
	if (ps->valid == 0)
	{
		printf("No data available for deletion!\n");
		return;
	}
	if ((pos >= 0) && (pos < ps->valid))
	{
		ps->p[pos] = x;
	}
	else
	{
		printf("Invalid coordinates!\n");
		return;
	}
}
```

#### 菜单

不写了，数据结构服务还要写菜单，不能直接调函数吗？

## 链表

从上述过程可以看出，顺序表的数组特性既是其最大的优点，也是其最大的缺点。由于元素在内存中是连续存储的，顺序表可以直接访问任意元素，但这也意味着在插入新数据时，顺序表必须移动其他元素，从而导致额外的时间开销。此外，顺序表每次扩容至原空间大小的两倍显得过于僵化，特别是在原空间较大时，会造成明显的空间浪费。为了解决这些问题，我们接下来将学习链表。

### 单链表

链表也分为很多种，下面我们主要讲单链表

链表由一个个节点构成，这些节点是链表的基本单位，从这个角度来看，它们可以被视为“原子”。每个节点主要分为两部分：数值域和指针域。数值域用于存储需要管理的数据，而指针域则包含指向其他节点的指针。正是通过指针域中的指针，节点们相互连接，形成一个整体。对于单链表而言，节点的指针域中只有一个指针，用于指示下一个节点的位置。

### 链表的逻辑结构

逻辑结构是什么？逻辑结构是一种理想化模型。二者的区别在于，理想化模型关注的是一个系统，而逻辑结构则专注于数据结构。它们都对实际情况进行了简化，使我们能够把握研究对象的关键特征，从而更好地理解。

以太阳系为例，经典的太阳系模型将太阳视为一个大球，其他行星或天体则是小球，它们沿着圆形轨道围绕太阳旋转。然而，实际上太阳系并不存在真正的轨道，轨道只是为了帮助我们形象地理解天体的运动方式。哥白尼提出的日心说与托勒密的地心说并不是绝对对错，而是不同的参考系。日心说简单明了，形象易懂，而地心说则复杂得多，需要不断添加修正，最终变得臃肿不堪。日心说如果与现象不符，可以将轨道从正圆改为椭圆，依然保持形象，只需进行更多计算，这就是良好的扩展性。

近代科学发现太阳也在绕银河中心旋转，这同样是可以扩展的，核心思想依旧是较大的天体围绕较小的天体运动。那么，链表的逻辑结构又是什么呢？链表可以比作一列火车（现代可能是动车），每个节点就像一节车厢，车厢里存放着两样东西：要管理的数据和指向下一个节点的指针。指针就像链条，将车厢连接成一个整体。

![image-20240729111835515](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202407291118773.png)

### 链表的物理结构

物理结构是什么？与化学中的物理结构不同，化学物质有实体，而数据结构则没有实际的物理实体。在计算机科学中，物理结构指的是数据在内存中的存储形式。这些数据可以是连续存储的，也可以是不连续存储的。

以链表为例，其各个节点的地址并不连续。每个节点都是通过 `malloc `动态分配的，`malloc` 的运行逻辑是根据内存中可用空间进行分配，因此节点的地址可能不相邻。当节点中的数据不再需要时，可以直接使用 `free `释放内存。

不过，计算机科学中的物理结构与化学中的物理结构并非完全无关。它们都有一个共同点：结构决定性质，而性质又反映结构。

#### 定义单链表

```c
typedef int SinglyDataType;

typedef struct SinglyListNode
{
	SinglyDataType data;
	struct SinglyListNode* next;
}SinglyListNode,* PSinglyListNode;
```

#### 打印单链表

```c
void SinglyListPrintf(PSinglyListNode PHead)
{
	PSinglyListNode PCurrent = PHead;
	while (PCurrent)
	{
		printf("%d ",PCurrent->data);
		PCurrent = PCurrent->next;
	}
	printf("\n");
}
```

尽管这里直接用`PHead`不会修改实参，但我们仍旧新创建一个指针来当循环变量，这主要是一种习惯。每次打印完这个节点的数据，就通过这个节点的指针域让`PCurrent`指向下一个节点，依次类推，当链表遍历完了，`PCurrent`就变成了`NULL`，于是就跳出了这个循环。

#### 获得一个节点

```c
static PSinglyListNode SinglyListNodeGet(SinglyDataType x)
{
	PSinglyListNode PNewNode = (PSinglyListNode)malloc(sizeof(SinglyListNode));
	if (PNewNode == NULL)
	{
		perror("SinglyListGet malloc fail");
		return NULL;
	}
	PNewNode->data = x;
	PNewNode->next = NULL;
	return PNewNode;
}
```

我们之后并不直接调用该函数，而是由插入函数间接调用，所以使用`static`来修饰该函数，这里没什么好说的，开辟，初始化，返回即可。

#### 头插

```c
void SinglyListPushFront(PSinglyListNode* PPHead, SinglyDataType x)
{
	assert(PPHead);
	PSinglyListNode PNewNode = SinglyListNodeGet(x);
	PNewNode->next = *PPHead;
	*PPHead = PNewNode;
}
```

这里为什么要用二级指针呢？因为形参只是实参的拷贝，修改形参不会影响实参。我们现在是头插，新创建的节点需要被上一级函数的`PHead`所指，为此，我们必须修改`PHead`的值，而形参只是实参的拷贝，所以要想修改`PHead`的值，必须把`PHead`的指针传过去，所以参数类型为二级指针。同理，这二级指针肯定不能是空的，但解引用后可以为空吗？可以的，空链表不就是`PHead == NULL`吗？那看这个函数，它的逻辑仍然可以正常运行，因为没有对链表表头进行解引用。

#### 测试头插

```c
void Test1()
{
	PSinglyListNode PHead = NULL;
	SinglyListPushFront(&PHead, 1);
	SinglyListPushFront(&PHead, 2);
	SinglyListPushFront(&PHead, 3);
	SinglyListPushFront(&PHead, 4);
	SinglyListPrintf(PHead);
}
```

![image-20240729132159815](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202407291322044.png)

这里没有销毁，报内存泄露警告了，没有关系，销毁函数还没写，头插函数运行是正常的，所以是通过了。

#### 销毁

```c
void SinglyListDestroy(PSinglyListNode* PPDie)
{
	assert(PPDie);
	PSinglyListNode PNextNode = NULL;
	while (*PPDie)
	{
		PNextNode = (*PPDie)->next;
		free(*PPDie);
		*PPDie = PNextNode;
	}
}
```

这里用不用二级指针都行，区别是用一级指针要像`free`那样，外部再置为空；用二级指针，外部就不用再置为空了，由于上面头插函数用的是二级指针，所以这里也用二级指针。虽说把个空指针销毁看起来有些大病，但既然`free`参数为空时也不会发生什么事，所以断言就不看解引用是不是空了。

#### 测试销毁

```c
void Test2()
{
	PSinglyListNode PHead = NULL;
	SinglyListPushFront(&PHead, 1);
	SinglyListPushFront(&PHead, 2);
	SinglyListPushFront(&PHead, 3);
	SinglyListPushFront(&PHead, 4);
	SinglyListPrintf(PHead);
	SinglyListDestroy(&PHead);
}
```

![image-20240729140514135](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202407291405290.png)

这下确实没有报内存泄露警告。

#### 尾插

```c
void SinglyListPushBack(PSinglyListNode* PPHead, SinglyDataType x)
{
	assert(PPHead);
	PSinglyListNode PNewNode = SinglyListNodeGet(x);
	if (*PPHead == NULL)
	{
		*PPHead = PNewNode;
	}
	else
	{
		PSinglyListNode PEnd = *PPHead;
		while (PEnd->next)
		{
			PEnd = PEnd->next;
		}
		PEnd->next = PNewNode;
	}
}
```

这里的参数而是用二级指针，当链表为空时，尾插不就相当于头插吗？也需要修改上一层函数`PHead`的值，所以用二级指针。当链表为空时，直接让`PHead`指向新节点就行，也就是`*PPHead = PNewNode;`，而当链表不为空时，就需要找到最后一个节点，修改其中`next`的值，使之指向新节点，也就是`PEnd->next = PNewNode;`，可以看到，这两种模式是无法兼容的，所以必须要分成两个分支来写。最后一个节点怎么找？最后一个节点的`next`是空指针，就用这个特征来找，当`next`的值为`NULL`时，跳出循环即可。

#### 测试尾插

```c
void Test3()
{
	PSinglyListNode PHead = NULL;
	SinglyListPushFront(&PHead, 2);
	SinglyListPushFront(&PHead, 1);
	SinglyListPushBack(&PHead, 3);
	SinglyListPushBack(&PHead,4);
	SinglyListPrintf(PHead);
	SinglyListDestroy(&PHead);
}
```

![image-20240729143612053](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202407291436181.png)

通过了。

#### 头删

```c
void SinglyListPopFront(PSinglyListNode* PPHead)
{
	assert(PPHead && *PPHead);
	PSinglyListNode PStart = *PPHead;
	*PPHead = PStart->next;
	free(PStart);
	PStart = NULL;
}
```

还是和上面一样，这个函数需要修改上一级函数的链表表头指针，所以要用二级指针。让我们想一想，什么情况才能删除链表中的节点，很明显，链表里要确实有节点才能删除，所以这次断言必须包括解引用了，剩下的就是该释放的释放，表头指针该修改的修改，没什么好说的。

#### 尾删

```c
void SinglyListPopBack(PSinglyListNode* PPHead)
{
	assert(PPHead && *PPHead);
	PSinglyListNode PLast = *PPHead;
	PSinglyListNode PTerminal = *PPHead;
	int isanode = 1;
	while (PTerminal->next)
	{
		PLast = PTerminal;
		PTerminal = PTerminal->next;
		isanode = 0;
	}
	PLast->next = NULL;
	free(PTerminal); 
	PTerminal = NULL;
	if (isanode)
	{
		*PPHead = NULL;
	}
}
```

和上面差不多，当链表只剩一个节点的时候，尾删即头删，需要修改上一级的链表表头，所以用二级指针。不过这里不仅要找最后一个节点，还要找倒数第二个节点，先释放最后一个节点，再把倒数第二个节点的`next`置为空。不过，这种分析容易写出有问题的代码，因为某些情况下，链表根本没有倒数第二个节点，所以循环变量一定不能设置成`P->next->next`这种样子，在这里我们创建两个指针，一个用来标记最后一个节点，另一个用来标记前一个节点，循环变量只有`PTerminal->next`，这种方法的好处是一个节点也可以正常运行，当只有一个节点时，根本不会进入循环，`isanode`还是为真，链表表头会被置为空，这两个指针都指向头结点；当节点不止一个时，会进入循环，`isanode`就变为了假，`PTerminal`指向最后一个节点，`PLast`指向倒数第二个节点。

当然，你也可以创建两个分支，一个分支用来应对只有一个节点的情况，另一个分支用来应对节点多于一个的情况，不过我个人不喜欢写分支，所以用上述形式。

#### 测试头删和尾删

```c
void Test4()
{
	PSinglyListNode PHead = NULL;
	SinglyListPushFront(&PHead, 2);
	SinglyListPushFront(&PHead, 1);
	SinglyListPushBack(&PHead, 3);
	SinglyListPushBack(&PHead, 4);
	SinglyListPrintf(PHead);
	SinglyListPopFront(&PHead);
	SinglyListPrintf(PHead);
	SinglyListPopBack(&PHead);
	SinglyListPrintf(PHead);
	SinglyListPopBack(&PHead);
	SinglyListPrintf(PHead);
	SinglyListPopBack(&PHead);
	SinglyListPrintf(PHead);
	SinglyListDestroy(&PHead);
}
```

![image-20240729174316195](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202407291743472.png)

正常。

#### 查找

```c
PSinglyListNode SinglyListFind(PSinglyListNode PHead, SinglyDataType val)
{
	PSinglyListNode PCurrent = PHead;
	while (PCurrent)
	{
		if (PCurrent->data == val)
		{
			return PCurrent;
		}
		else
		{
			PCurrent = PCurrent->next;
		}
	}
	return PCurrent;
}
```

这里就不断言了，虽说在空链表里查找查找听起来怪怪的，但逻辑上是没问题，还是查不到吗，照样返回空指针。可以看到上面的打印也没断言，因为空链表也可以打印，只不过不打印数据而已，如果加了，输空链表它就崩了。

#### 指定位置插入

```c
//指定位置插入
//当PPHead合法时，在pos节点之前插入
//当PPHead为空时，在pos节点之后插入
void SinglyInsert(PSinglyListNode* PPHead, PSinglyListNode pos, SinglyDataType val)
{
	assert(pos);
	PSinglyListNode PNewNode = SinglyListNodeGet(val);
	if (PPHead == NULL)
	{
		//后插
		PNewNode->next = pos->next;
		pos->next = PNewNode;
	}
	else
	{
		//前插
		assert(*PPHead);
		PSinglyListNode prev = NULL;
		PSinglyListNode current = *PPHead;
		while (current != pos)
		{
			prev = current;
			current = current->next;
		}
		if (prev == NULL)
		{
			PNewNode->next = current;
			*PPHead = PNewNode;
		}
		else
		{
			PNewNode->next = current;
			prev->next = PNewNode;
		}
	}
}
```

前插要看看指定位置是不是就是头结点。

#### 测试指定位置插入

```c
void Test5()
{
	PSinglyListNode PHead = NULL;
	SinglyListPushBack(&PHead, 4);
	SinglyListPushFront(&PHead, 1);
	SinglyListPrintf(PHead);
	PSinglyListNode pos = SinglyListFind(PHead, 1);
	if (pos)
	{
		SinglyInsert(NULL, pos, 2);
	}
	else
	{
		printf("Find fail!\n");
	}
	pos = SinglyListFind(PHead, 4);
	if (pos)
	{
		SinglyInsert(&PHead, pos, 3);
	}
	else
	{
		printf("Find fail!\n");
	}
	SinglyListPrintf(PHead);
	SinglyListPopFront(&PHead);
	SinglyListPopBack(&PHead);
	SinglyListPopFront(&PHead);
	SinglyListPrintf(PHead);
	pos = SinglyListFind(PHead, 3);
	if (pos)
	{
		SinglyInsert(&PHead, pos, 2);
	}
	else
	{
		printf("Find fail!\n");
	}
	SinglyListPrintf(PHead);
	SinglyListDestroy(&PHead);
}
```

![image-20240731114042028](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202407311140284.png)

目前没有发生问题。就当通过了。

#### 指定位置删除

```c
void SinglyErase(PSinglyListNode* PPHead, PSinglyListNode pos)
{
	assert(PPHead && *PPHead);
	if (pos)
	{
		PSinglyListNode prev = NULL;
		PSinglyListNode current = *PPHead;
		while (current != pos)
		{
			prev = current;
			current = current->next;
		}
		if (prev)
		{
			prev->next = current->next;
			free(current);
		}
		else
		{
			*PPHead = current->next;
			free(current);
		}
	}
	else
	{
		printf("Invalid parameter!\n");
		return;
	}
}
```

#### 测试指定位置删除

```c
void Test6()
{
	PSinglyListNode PHead = NULL;
	SinglyListPushBack(&PHead, 4);
	SinglyListPushFront(&PHead, 1);
	SinglyListPrintf(PHead);
	PSinglyListNode pos = SinglyListFind(PHead, 1);
	if (pos)
	{
		SinglyErase(&PHead, pos);
	}
	else
	{
		printf("Find fail!\n");
	}
	SinglyListPrintf(PHead);
	pos = SinglyListFind(PHead, 4);
	if (pos)
	{
		SinglyErase(&PHead, pos);
	}
	else
	{
		printf("Find fail!\n");
	}
	SinglyListPrintf(PHead);
	SinglyListDestroy(&PHead);
}
```

![image-20240731123221759](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202407311232899.png)

看起来没什么问题。

# 题外话

之前我们曾稍微说过链表和顺序表的比较，我们说顺序表内存地址连续的特点既是其优点点，也是其缺点。顺序表最大的优点就是可以直接访问（复杂度O（1））其中的任意成员；缺点是当插入数据时，可能需要对数据进行搬移，从而提高复杂度。除此之外，顺序表的缓存利用率也比链表高。

我们知道，不管是链表还是顺序表，都是存放在内存中的，但内存的计算速度远高于内存的读写速度，所以当CPU对内存中的数据进行操作时，它不是直接在内存上操作，而是先把需要的数据复制到读写速度更快的存储结构里，然后在这些读写速度更快的存储结构里对数据进行操作，操作完后，再把结果覆写到内存中的对应位置上。

当需要的数据存储空间比较小时，它会被放在寄存器上，比如对某个整型`i`执行"++"操作，那计算机就会先把`i`覆写到加法寄存器中，然后在加法寄存器中对数据进行加一操作，再把得到的结构重新覆写到内存中`i`的位置上，可以通过反汇编来观察这个过程。

当需要的数据存储空间比较大时，它就会被放在三级高速缓存中，比如数据结构中的某个成员。在把需要数据覆写到高速缓冲区时，并不是光把需要的数据覆写过去，而是从需要的数据地址开始，把单位大小的数据一股脑全复制到高速缓冲区。这样做的原因是，对于计算机来说，只拷贝需要的数据和拷贝包含需要数据单位大小的内存块成本是一样的，所以本着“万一靠近需要数据待会就要用”的想法，计算机会从当前需要的数据地址开始，经过某个单位长度，把这整个单位长度（通常情况下，是计算机的字长）都拷贝到高速缓冲区。

同样是四个整型1234，分别存储在顺序表和链表中。对于顺序表来说，当需要读取1时，计算机就会从1的地址处开始，经过单位长度，把这个单位长度大小的内存块复制到高速缓冲区，由于顺序表成员地址连续，所以可能1234这四个成员都被拷贝到了高速缓冲区，而对于链表来说，由于1234这四个节点地址不连续，所以有可能只拷贝了1这一个节点，当要访问2时，由于顺序表中的2已经被放在高速缓冲区了，所以就不需要再复制，而对于链表来说，2不在缓冲区，所以还要再把2这个节点复制过来。所以说，顺序表的内存利用率（也有叫缓冲命中率）比链表高。

![image-20240809090639325](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202408090906600.png)

# 完

