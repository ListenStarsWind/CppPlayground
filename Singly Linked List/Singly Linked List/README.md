# 学习

本项目的目的是学习单向链表

由于期末复习的缘故，单链表学一半就中断了，所以现在从头开始；

另外，这也是我第一次在VS项目下创建.md文档，从今以后，我将舍弃原来在**newc++file.cpp** 中添加前注释的方式，而专门使用.md进行说明。

另外，从今以后，我将注意.md的语法，不犯语法错误，比如，你可以看到，前面的两个文件名都被打了红波浪线，这是因为这样写会触发Typora的拼写检查，而且Typora认为这个拼写是有误的。

解决方法是将文件名包裹在反引号（`）中，使其被视为代码。这样Typora就不会对其进行拼写检查。

比如：`newc++file.cpp`和`md`，反引号键是英文输入法Tab键上面的那个。

我还没有专门学习过Markdown的流程图，逻辑图的详细用法，暂且像记流水账那样记录项目开发过程

1. 我忘了在`.h`文档中添加指令`#pragma once`这需要注意
2. 直接使用`int`类型定义单链表数值域，而不是在加一层重命名

绵姐先手动创建节点来示范单链表数值域打印

![CT-20240707014205](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202407070943200.png)

我就不这样了，我打算先写个函数用来创建节点

我记得我之前好像是返回`SListNode`的，搞不懂为什么不直接返回指针。之所以强调不完全初始化，是因为我逻辑上只对数值域进行了赋值，返回到上一级函数之后，指针域还是要改的，这里对指针域置空只是出于谨慎，没有深意。

`test0`第一次测试：无法运行，原因：缺少`printf`头文件

第二次测试：成功。



接下来写单链表打印函数，绵姐是直接全部打印，我本来打算拆的更碎一点：写个函数打印单个节点，循环调用该函数，这样做的原因是之前在顺序表那里我是全部打印的，结果写到后面遇到了一个置打印单个数据体的场景，弄得我要重写。但又考虑了一会之后，最终还是决定一次性打印完，这是因为由于链表的结构，很少会直接访问其中的单个数据，而且这里的数值域用的也仅仅是int，就算重写也很方便。

`test1`第一次测试：无限打印1->,原因：循环变量调整环节是这样写的：`PtrTrav = PtrHead->next;`

第二次测试：成功





单元测试2，第一次运行：卡死，原因：没有进行循环变量调整

第二次运行：成功



单元测试3，一次运行成功



单元测试4_0，第一次运行：卡死，原因：循环变量调整赋值顺序不对：`PtrTail = PtrLast;`

第二次运行：效果不对，没有实现尾删，原因：释放错了，`free(PtrTail);`不对，循环变量选的有问题，直接重做

第三次运行：出现了意料之外的断言错误，原因：打印函数里有断言，空链表误触发了该断言。

第四次运行：成功



单元测试4_1，第一次运行：成功

这样不写代码，只写原因，好像不太好，该用gitee同步，还是直接把代码写进来？

用`gitee`吧

目前项目`gitee`地址：https://gitee.com/listen-to-the-wind-ruoyi/routine/commit/fd1c5142b97f7d5b2dbe02e073a623a1a92919e4



[单元测试5，测试前文件](https://gitee.com/listen-to-the-wind-ruoyi/routine/commit/ac0fed2087ca7937aeafe5640214f894fef9b97b)

第一次运行：成功



单元测试6：

[初始状态](https://gitee.com/listen-to-the-wind-ruoyi/routine/commit/5d76c398319e2421a0ef0da73b16c3e11c750003)

第一次运行：无法运行，原因，已有函数test5；

第二次运行：成功



单元测试7：

[初始状态](https://gitee.com/listen-to-the-wind-ruoyi/routine/commit/c9b49029c90412230d378a2b44ffa70ba74312f1)

第一次运行：成功



单元测试8：

[初始状态](https://gitee.com/listen-to-the-wind-ruoyi/routine/commit/e464141fdf75bcf21acfc9518a8fb3335b0add72)

第一次运行：成功



单元测试9：

[初始状态](https://gitee.com/listen-to-the-wind-ruoyi/routine/commit/bf9285ac483409c0d62af4aabdac8f769a4beb92)

第一次运行：成功



# 单链表经典算法OJ题：

1. [移除链表元素](https://leetcode.cn/problems/remove-linked-list-elements/description/)

   给你一个链表头结点指针head和一个整数val，请你删除所有数值域为val的节点，并返回新的头节点。

   ![](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202407072238725.png)

   有两种思路：

   - 在原链表的基础上进行修改，删除掉符合的节点。
   - 建立一个新的链表，只有数值域不是val的节点才能被收录其中。

   先说第二个思路，因为绵姐就是以此为例的。

   ```c
   /**
    * Definition for singly-linked list.
    * struct ListNode {
    *     int val;
    *     struct ListNode *next;
    * };
    */
   struct ListNode* removeElements(struct ListNode* head, int val) {
       struct ListNode* HeadNode = NULL;//新的头结点
       struct ListNode* TailNode = NULL;//末尾节点
       while(head)
       {
           if(head->val == val)
           {
               ;
           }
           else
           {
               if(HeadNode == NULL)
               {
                   HeadNode = head;
                   TailNode = head;
               }
               else
               {
                   TailNode->next = head;//连接节点
                   TailNode = head;//成为末尾节点
               }
           }
           head = head->next;
           //防止原链表指针域中的指针污染新链表
           //从而将新链表导向未知区域
           if(TailNode != NULL)
           {
               TailNode->next = NULL;
           }
       }
       return HeadNode;
   }
   ```

   第一个思路：

   暂且搁置

2. [反转链表](https://leetcode.cn/problems/reverse-linked-list/description/)

   给你单链表的头节点 `head` ，请你反转链表，并返回反转后的链表。

   ![image-20240708011251255](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202407080112396.png)

   也是有两个思路：

   - 创建一个新的链表，将原链表的节点头插入新链表
   - 使用三个指针，在原链表的基础上进行修改，直接得到反转后的链表

   下面只说第二个思路：

   第二个思路并不是很难理解，但是很难想到，非常有算法的那种感觉

   为方便叙述，可以将这三个指针命名为`n1``n2``n3`，它们的初始位置是：`n1`为空，`n2`为head,`n3`为head->next;

   让`n2`的指针域指向`n1`，把`n2`的值赋给`n1`，把`n3`的值赋给`n2`，再把`n3`的指针域赋给`n3`自己，不断循环，直到`n1`指向了原链表中的最后一个节点。下面是示意视频：

   <video src="https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202407080155681.mp4"><\video>

   另外要注意，当原链表为空时，需要新建一个分支处理

   ```c
   /**
    * Definition for singly-linked list.
    * struct ListNode {
    *     int val;
    *     struct ListNode *next;
    * };
    */
   struct ListNode* reverseList(struct ListNode* head) {
       if (head == NULL) {
           return NULL;
       } else {
           struct ListNode* n1 = NULL;
           struct ListNode* n2 = head;
           struct ListNode* n3 = head->next;
           while (n2 != NULL) {
               n2->next = n1;
               n1 = n2;
               n2 = n3;
               if (n3 != NULL) {
                   n3 = n3->next;
               }
           }
           return n1;
       }
   }
   ```

   

3. [链表的中间节点](https://leetcode.cn/problems/middle-of-the-linked-list/description/)

   给你单链表的头结点 `head` ，请你找出并返回链表的中间结点。

   如果有两个中间结点，则返回第二个中间结点。

   ![](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202407080252908.png)

   有两个主要方向：

   - 将链表数组化，比如遍历节点得出节点个数，从而找到哪里是中间；将节点指针放进数组中，直接返回数组中间元素
   - 快慢指针

   这里主要说第二种，这里的“快慢”指的是指针单位变化的程度，慢指针一次循环只移动到下个节点，快指针一次循环则是移动的下下个节点，它们的初始位置都是head，下面是参考视频：

   <video src="https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202407080312383.mp4"><\video>

   ```c
   /**
    * Definition for singly-linked list.
    * struct ListNode {
    *     int val;
    *     struct ListNode *next;
    * };
    */
   struct ListNode* middleNode(struct ListNode* head) {
       struct ListNode* slow = head;
       struct ListNode* fast = head;
       while(fast && fast->next)
       {
           slow = slow->next;
           fast = fast->next->next; 
       }
       return slow;
   }
   ```

   

   4. [合并两个有序链表](https://leetcode.cn/problems/merge-two-sorted-lists/description/)

      将两个升序链表合并为一个新的 **升序** 链表并返回。新链表是通过拼接给定的两个链表的所有节点组成的。 

      ![](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202407101143179.png)

      之前好像写过一个合并有序数组的题，给你两个升序的数组，数组内有效元素个数分别是m和n，为了方便叙述，我们分别称为数组1，数组2，数组1的实际大小是m+n个元素单位，其中前m个事有效元素，数组2实际大小是n个元素，要求不创建新数组，以数组1为载体，存储新的合并的有序数组，为了不覆盖数组1前面的数据，我们是从后往前，从大往小地比较，噢，这里只是联想到了而已，后面的操作和这没关系。

      这道题本身并不难，但在解题的过程中，将会引出一个思想，这个算法思想才是真正的重点。

      思路有两种：

      - 在原链表的基础上进行修改，谁小就插入谁，这里就不说了

      - 创建一个新的链表，分别遍历两个数组，谁小谁插入到新链表中

        比较简单，不做媒体示例了。

        ```c
        /**
         * Definition for singly-linked list.
         * struct ListNode {
         *     int val;
         *     struct ListNode *next;
         * };
         */
        struct ListNode* mergeTwoLists(struct ListNode* list1, struct ListNode* list2) {
            if(list1 == NULL)
            {
                return list2;
            }
            if(list2 == NULL)
            {
                return list1;
            }
            
            struct ListNode* ListHead = NULL;
            struct ListNode* ListTail = NULL;
            while(list1 && list2)
            {
                if(list1->val < list2->val)
                {
                    if(ListHead == NULL)
                    {
                        ListHead = list1;
                        ListTail = list1;
                    }
                    else
                    {
                        ListTail->next = list1;
                        ListTail = ListTail->next;
                    }
                    list1 = list1->next;
                }
                else
                {
                    if(ListHead == NULL)
                    {
                        ListHead = list2;
                        ListTail = list2;
                    }
                    else
                    {
                        ListTail->next = list2;
                        ListTail = ListTail->next;
                    }
                    list2 = list2->next;
                }
            }
            if(list1)
            {
                ListTail->next = list1;
            }
            if(list2)
            {
                ListTail->next = list2;
            }
            return ListHead;
        }
        ```

        流程图：

        ![未命名绘图-第 2 页](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202407101314197.png)

        哦，我曾经疑惑过，为什么把还没空的链表插入新链表环节为什么用if而不是while,后来意识到，链表和数组不同，它自身就带有连接属性，看似只插入了一个节点，实际上后面也插入进来了。

        好的，现在要看重点了，我们可以看到，我们建立了一个判断新链表是否为空的分支结构，有没有办法把这个分支结构改成顺序结构呢？当然是有的，这时就要引入“哨兵位”这个概念。

        在创建负责维护新链表的指针变量时，不再将其初始化为空，而是让它们指向一块动态开辟的节点大小的空间，这样就不用再考虑由于指针变量为空而无法解引用的情况。别忘了最后把动态开辟的空间再释放。

        ```c
        /**
         * Definition for singly-linked list.
         * struct ListNode {
         *     int val;
         *     struct ListNode *next;
         * };
         */
        struct ListNode* mergeTwoLists(struct ListNode* list1, struct ListNode* list2) {
            if(list1 == NULL)
            {
                return list2;
            }
            if(list2 == NULL)
            {
                return list1;
            }
            
            struct ListNode* ListHead = NULL;
            struct ListNode* ListTail = NULL;
            ListHead = ListTail = (struct ListNode*)malloc(sizeof(struct ListNode));
        
            while(list1 && list2)
            {
                if(list1->val < list2->val)
                {
                    ListTail->next = list1;
                    ListTail = ListTail->next;
                    list1 = list1->next;
                }
                else
                {
                    
                    ListTail->next = list2;
                    ListTail = ListTail->next;
                    list2 = list2->next;
                }
            }
            if(list1)
            {
                ListTail->next = list1;
            }
            if(list2)
            {
                ListTail->next = list2;
            }
            struct ListNode* ret = ListHead->next;
            free(ListHead);
            ListHead = NULL;
            return ret;
        }
        ```

        这种链表被称为“带头链表”，此处的“头”指的是头链表，之前我们说的头链表其实是一种错误的说法，头链表指的就是哨兵位，之前说头链表，只是这样能更好理解，实际之前的说法就是错的。

   5.  [环形链表的约瑟夫问题](https://www.nowcoder.com/practice/41c399fdb6004b31a6cbb047c641ed8a)

      据说著名犹太 Josephus有过以下的故事：在罗马人占领乔塔帕特后，39个犹太人与
      Josephus及他的朋友躲到⼀个洞中，39个犹太人决定宁愿死也不要被人抓到，于是决定了⼀个自杀
      方式，41个人排成⼀个圆圈，由第1个人开始报数，每报数到第3人该人就必须⾃杀，然后再由下⼀
      个重新报数，直到所有人都自杀身亡为止。
      然而Josephus和他的朋友并不想遵从，Josephus要他的朋友先假装遵从，他将朋友与自己安排在
      第16个与第31个位置，于是逃过了这场死亡游戏。

        

      编号为 1 到 n 的 n 个人围成一圈。从编号为 1 的人开始报数，报到 m 的人离开。下一个人继续从 1 开始报数。

      n-1 轮结束以后，只剩下一个人，问最后留下的这个人编号是多少？

      数据范围： 1≤𝑛,𝑚≤100001≤*n*,*m*≤10000

      进阶：空间复杂度 𝑂(1)*O*(1)，时间复杂度 𝑂(𝑛)*O*(*n*)

      ![image-20240710142246051](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202407101422155.png)

      这里涉及到了循环链表，循环链表就是尾部的节点指针域不再指向NULL，而是指向头结点（这里的头节点指的是链表开始位置的节点，不是说必须是哨兵位）。

      逻辑其实并不难，其实就是把过程模拟一遍就行了，可能代码量有些多。

      ```c
      /**
       * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
       *
       * 
       * @param n int整型 
       * @param m int整型 
       * @return int整型
       */
      
      //节点定义重命名
      typedef struct ListNode ListNode;
      
      //创建并初始化一个节点
      ListNode* getnode(int m)
      {
          ListNode* node  = (ListNode*)malloc(sizeof(ListNode));
          if(node == NULL)
          {
              exit(1);
          }
          node->val = m;
          node->next = NULL;
          return node;
      }
      
      //获得一个循环链表
      ListNode* getlist(int n)
      {
          ListNode* listhead = getnode(1);
          ListNode* listtail = listhead;
          int number  = 2;
          for(number=2;number<=n;number++)
          {
              listtail->next = getnode(number);
              listtail = listtail->next;
          }
          //首尾相连
          listtail->next = listhead;
          //注意返回尾节点，因为这是单向链表，返回头结点不好找上个节点
          return listtail;
      }
      
      int ysf(int n, int m ) {
          // write code here
          ListNode* lastnode = getlist(n);
          ListNode* dienode = lastnode->next;
          int count  = 1;
          while(lastnode != dienode)
          {
              if(count == m)
              {
                  count = 1;
                  lastnode->next = dienode->next;
                  free(dienode);
                  dienode = lastnode->next;
              }
              else
              {
                  count++;
                  lastnode = lastnode->next;
                  dienode = dienode->next;
              }
          }
          int ret = lastnode->val;
          free(lastnode);
          lastnode = dienode = NULL;
          return ret;
      }
      ```

      我觉得这思路挺清晰的，就不画流程图了。

   6. [分割链表](https://leetcode.cn/problems/partition-list-lcci/description/)

      力扣把这题的难度定为了中等，要我说，前面的题目若都能过去，这题倒也不难了。

      给你一个链表的头节点 `head` 和一个特定值 `x` ，请你对链表进行分隔，使得所有 **小于** `x` 的节点都出现在 **大于或等于** `x` 的节点之前。你不需要 **保留** 每个分区中各节点的初始相对位置。

      ![image-20240710160307671](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202407101603771.png)

      还是分成两种思路

      - 思路一：在原链表的基础上进行修改，把数值域大于或等于x的节点移动到尾部。另外注意，为了减轻尾插的资源负担，我们先把原链表遍历一遍，找到尾节点，并记录，尾插的时候就不用再遍历了，另外，这个尾节点指针还可以判断是否每个节点都被遍历过（实际上并不是每个节点都会被遍历）那个原来的尾节点其实没有比较，但作为两个部分的交界，其val到底怎么样都无所谓了。

        ```c
        /**
         * Definition for singly-linked list.
         * struct ListNode {
         *     int val;
         *     struct ListNode *next;
         * };
         */
        
        // 类型重命名
        typedef struct ListNode ListNode;
        
        struct ListNode* partition(struct ListNode* head, int x) {
        
            if (head == NULL) {
                return NULL;
            } else {
                ListNode* traversal = head;
                ListNode* last = (ListNode*)malloc(sizeof(ListNode));
                ListNode* ret = last;
                ListNode* tail = NULL;
                ListNode* newtail = NULL;
        
                last->next = head;
        
                while (traversal->next) {
                    traversal = traversal->next;
                }
                tail = newtail = traversal;
        
                traversal = head;
                while (traversal != tail) {
                    if (traversal->val < x) {
                        traversal = traversal->next;
                        last = last->next;
                    } else {
                        last->next = traversal->next;
                        traversal->next = NULL;
                        newtail->next = traversal;
                        newtail = newtail->next;
                        traversal = last->next;
                    }
                }
                traversal = ret;
                ret = ret->next;
                free(traversal);
                traversal = NULL;
                last = NULL;
                tail = NULL;
                newtail = NULL;
                return ret;
            }
        }
        ```

      - 思路二：创建两个新链表，分别作为存放两部分的载体，最后再连接上就好了

        ```c
        // 类型重命名
        typedef struct ListNode ListNode;
        
        struct ListNode* partition(struct ListNode* head, int x) {
            ListNode* small = (ListNode*)malloc(sizeof(ListNode));
            ListNode* big = (ListNode*)malloc(sizeof(ListNode));
            ListNode* smalltail = small;
            ListNode* bigtail = big;
            small->next = NULL;
            big->next = NULL;
            
            while(head)
            {
                if(head->val < x)
                {
                    smalltail->next = head;
                    smalltail = smalltail->next;
                    head = head->next;
                    smalltail->next =NULL;
                }
                else
                {
                    bigtail->next = head;
                    bigtail = bigtail->next;
                    head = head->next;
                    bigtail->next = NULL;
                }
            }
            bigtail = big;
            big = big->next;
            free(bigtail);
            bigtail = NULL;
            smalltail->next = big;
            smalltail = small;
            small = small->next;
            free(smalltail);
            smalltail = NULL;
            big = NULL;
            return small;
        }
        ```

      - 思路三：在原链表的基础上，头插和尾插，略，差不多。

      噢，另外要注意，编程题超出时间限制的意思是出现了死循环

   链表的分类

   链表的结构非常多样，以下情况组合起来就有8种（`2x2x2`）链表结构：

   ![image-20240710175941915](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202407101759006.png)

   “头”指的就是头结点，这里的头结点指的就是哨兵位

   “单双”指的是链表允许的流向，单向链表只能从前往后遍历，指针域中只有一个指针；双向链表既可以从前往后遍历，也可以从后往前遍历，这是因为，双向链表的指针域里有两个指针，一个指针指向next节点，另一个指针指向last节点

   “循环”指的是最后一个节点和第一个节点有没有建立联系，对于单向链表来说是最后一个节点的next指向首节点；对于双向来说，是首节点的last指向最后一个节点，最后一个节点的next指向首节点

   之前我们学的`SList`更详细来说是指不带头单向不循环链表。  

   

   





