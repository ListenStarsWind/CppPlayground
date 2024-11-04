[TOC]

# stack and queue

## stack

### feel

#### [documentation](https://legacy.cplusplus.com/reference/stack/stack/)

##### stack

Stacks are a type of `container adaptor`【容器适配器】, `specifically`【专门】`designed`【设计】`to`【用于】`in a LIFO context`【在LIFO上下文】\(`last-in first-out`【后进先出】)中`operate`【操作】，elements only `from container`【从容器】` one end of `【的一端】`inserted and extracted `【插入和提取】。

stacks are `implemented as`【实现为】 `container adaptors`【容器适配器】，这是一种`use`【使用】`specific container class `【特定容器类】`of`【的】`encapsulated object`【封装对象】`as`【作为】`underlying container`【底层容器】的`classes`【类】，并`providing`【提供】`set of`【一组】`specific`【特定的】`member functions`【成员函数】`to`【以】` access`【访问】`its elements`【其元素】。Elements are from specific container `of`【的】`back`【后面】`pushed/popped`【推入或弹出】 ，`which`【这】`known as`【被称为】`top of the stack`【栈的顶部】。

`underlying container `【底层容器】` may be`【可以是】`standard container class templates`【标准容器类模版】or `other specifically designed container class`【其它专门设计的容器类】，`The container`【该容器】`shall`【应该】`support`【支持】`following`【以下】`operations`【操作】：

- empty（是否为空）
- size（大小）
- back（获取最后一个元素）
- push_back（在末尾添加元素）
- pop_back（从末尾移除元素）

`standard container classes`【标准容器类】vector, deque and list `fulfill`【满足】`these requirements`【这些要求】，`By default`【默认情况下】, `if`【如果】`no`【没有】为`particular stack class`【特定的栈类】`instantiation`【实例化】`specified`【指定】`container class`【容器类】，则used standard container deque 。

##### Template parameters

- T: Type of the elements. Aliased as member type stack::value_type.
- `Container`【容器】: ` internal `【内部】`underlying container object`【底层容器对象】的`type`【类型】。用于`stored`【存储】`elements `。`Its`【其】value_type `shall be`【应为】T。`Aliased as`【别名为】member type stack::container_type。

##### Member types

| member type    | definition                                | notes                                                        |
| -------------- | ----------------------------------------- | ------------------------------------------------------------ |
| value_type     | The first template parameter (T)          | Type of the elements                                         |
| container_type | The second template parameter (Container) | Type of the underlying container                             |
| size_type      | an unsigned integral type                 | usually the same as [size_t](https://legacy.cplusplus.com/size_t)【通常size_t相同】 |

##### Member functions

|                                                              |                                                           |
| :----------------------------------------------------------- | :-------------------------------------------------------- |
| [**(constructor)**](https://legacy.cplusplus.com/reference/stack/stack/stack/) | Construct stack (public member function )                 |
| [**empty**](https://legacy.cplusplus.com/reference/stack/stack/empty/) | Test whether container is empty (public member function ) |
| [**size**](https://legacy.cplusplus.com/reference/stack/stack/size/) | Return size (public member function )                     |
| [**top**](https://legacy.cplusplus.com/reference/stack/stack/top/) | Access next element (public member function )             |
| [**push**](https://legacy.cplusplus.com/reference/stack/stack/push/) | Insert element (public member function )                  |
| [**emplace** ](https://legacy.cplusplus.com/reference/stack/stack/emplace/) | Construct and insert element (public member function )    |
| [**pop**](https://legacy.cplusplus.com/reference/stack/stack/pop/) | Remove top element (public member function )              |
| [**swap** ](https://legacy.cplusplus.com/reference/stack/stack/swap/) | Swap contents (public member function )                   |

##### Non-member function overloads

|                                                              |                                                       |
| ------------------------------------------------------------ | ----------------------------------------------------- |
| [**relational operators**](https://legacy.cplusplus.com/reference/stack/stack/operators/) | Relational operators for stack (function )            |
| [**swap (stack)** ](https://legacy.cplusplus.com/reference/stack/stack/swap-free/) | Exchange contents of stacks (public member function ) |

##### Non-member class specializations

|                                                              |                                            |
| ------------------------------------------------------------ | ------------------------------------------ |
| [**uses_allocator** ](https://legacy.cplusplus.com/reference/stack/stack/uses_allocator/) | Uses allocator for stack (class template ) |

#### example

##### [min stack](https://leetcode.cn/problems/min-stack)

![image-20241101173439878](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411011734159.png)

我们的策略是使用两个栈，一个栈存储数据，另一个栈存储最小数据。

![image-20241101173710135](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411011737227.png)

假如push【2】【0】【3】【0】然后连着走四轮getMin pop。

首先往_s填入2，发现\_min是空的，所以要向\_min填入2

![image-20241101174022835](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411011740933.png)

然后填入0，发现0比_min的栈顶小，所以这次\_s和\_min都要填入0

![image-20241101174223157](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411011742241.png)

接着填入3, 3比_min栈顶大，那只需要填入\_s即可

![image-20241101174326136](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411011743244.png)

填入0, 0和_min栈顶相等，那就再插入一个0

![image-20241101174451554](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411011744646.png)

此时getMin，就去取_min栈顶，得0

push，发现_s的栈顶和\_min的栈顶相同，那就都push

![image-20241101174812895](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411011748971.png)

此时getMin，就去取_min栈顶，得0

push，发现_s的栈顶大于\_min的栈顶，那就只push _s

![image-20241101174918701](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411011749786.png)

此时getMin，就去取_min栈顶，得0

push，发现_s的栈顶和\_min的栈顶相同，那就都push

![image-20241101175001167](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411011750250.png)

此时getMin，就去取_min栈顶，得2

push，发现_s的栈顶和\_min的栈顶相同，那就都push

所以关键就是push和pop的逻辑：

对于push而言，

- 如果_min是空的，那\_s和\_min都push，\_min都空了还比什么呢？
- 如果新插入的值比_min栈顶小，那\_min和\_s也都push
- 如果新插入的值比_min栈顶大，那只push _s
- 如果相同，那_min和\_s也都push

对于pop而言，

- 如果将要被取出的值比_min栈顶大，那只pop\_s
- 如果将要被取出的值和_min栈顶相同，那就都pop
- 若push的逻辑正确，不会出现将要被取出的值比_min比栈顶小的情况

为了进行优化，防止连续插入多个最小值，我们可以把_min的元素换成节点，这个节点将采取引用计数的方式，此时当新插入的值和\_min栈顶相同，就让计数加一。而当计数归0之后，再pop节点。

```cpp
#include<stack>
#include<iostream>

using namespace std;
template <class T> struct __node {
    T _val;
    size_t _size;

    typedef __node<T> self;

    __node(const T& val = T()) : _val(val), _size(1) {}

    self& operator++() {
        _size++;
        return *this;
    }

    self& operator--() {
        _size--;
        return *this;
    }

    bool invalid() {
        if (_size == 0)
            return true;
        else
            return false;
    }
};

class MinStack {
    typedef __node<int> Node;

public:
    MinStack() {}

    void push(int val) {
        if (_min.empty()) {
            _min.push(Node(val));
        }
        else if (_min.top()._val > val) {
            _min.push(Node(val));
        }
        else if (_min.top()._val == val) {
            ++_min.top();
        }
        _s.push(val);
    }

    void pop() {
        if (_s.top() == _min.top()._val) {
            --_min.top();
            if (_min.top().invalid()) {
                _min.pop();
            }
        }
        _s.pop();
    }

    int top() { return _s.top(); }

    int getMin() { return _min.top()._val; }

private:
    stack<int> _s;
    stack<Node> _min;
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */
```

##### [push and pop sequence of the stack](https://www.nowcoder.com/share/jump/9209693051730456047239)

![image-20241101183825997](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411011838180.png)

思路是真的构建一个栈，去模拟整个过程。

比如输入次序是[1,2,3,4,5]，输出次序是[3,2,4,5,1]。我们一个一个地输入数据，每次输入完后，再看看栈顶值能否与选中的输出值相同，如果相同，就让输出值向后迭代一次，并把栈顶值抛出，之后再看看栈顶值能否与选中的输出值相同，由于我们是一个一个的输入数据的，所以跳出循环后，栈理应是空的，如果没空，说明依照输出序列无法把所有值都拿出来，所以这个序列就是不对的。

![image-20241101185058574](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411011850692.png)

![image-20241101185201843](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411011852957.png)

![image-20241101185302575](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411011853688.png)

![image-20241101185354797](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411011853900.png)

![image-20241101185515004](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411011855091.png)

![image-20241101185624526](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411011856628.png)

![image-20241101185709846](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411011857947.png)

![image-20241101185801336](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411011858436.png)

![image-20241101185841456](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411011858538.png)

![image-20241101185934825](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411011859927.png)

![image-20241101190009498](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411011900591.png)

```cpp
#include<vector>
#include<stack>

using namespace std;

class Solution {
public:
    bool IsPopOrder(vector<int>& pushV, vector<int>& popV) {
        stack<int> s;
        auto in = pushV.begin();
        auto out = popV.begin();
        auto it = pushV.begin();
        auto in_end = pushV.end();
        auto out_end = popV.end();
        while (in != in_end) {
            s.push(*in);
            ++in;
            while (!s.empty() && out != out_end && s.top() == *out) {
                ++out;
                s.pop();
            }
        }
        return s.empty();
    }
};
```

##### [level order traversal](https://leetcode.cn/problems/binary-tree-level-order-traversal)

![image-20241103103858545](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411031038709.png)

直接说一下过程吧

为了方便起见，我们把节点用"[val]"的形式表现

![image-20241103104937637](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411031049683.png)

首先判断根节点是否为空，不为空，就入队列，leveles就是队列每轮调整后的size

![image-20241103105255552](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411031052598.png)

当队列不为空时，将上一轮压入队列的节点记录并弹出

![image-20241103105733055](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411031057101.png)

将弹出节点映射的数据压入vector\<int>

![image-20241103105901552](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411031059614.png)

将当前节点的子节点压入queue

![image-20241103110010189](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411031100231.png)

在上一轮压入节点全部弹出后(依据leveles判断)，将vector\<int>压入vector\<vector\<int>>中，并清空数据

![image-20241103110246955](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411031102001.png)

上一轮节点的子节点已经全部压入queue中，对leveles进行修正

![image-20241103110353082](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411031103126.png)

------------------------

将上一轮压入队列的节点记录并弹出

![image-20241103110510281](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411031105329.png)

将弹出节点映射的数据压入vector\<int>

![image-20241103110601609](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411031106660.png)

将当前节点的子节点压入queue

![image-20241103110601609](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411031106660.png)

将上一轮压入队列的节点记录并弹出

![image-20241103110739702](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411031107753.png)

将弹出节点映射的数据压入vector\<int>

![image-20241103110820055](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411031108104.png)

将当前节点的子节点压入queue

![image-20241103110914014](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411031109057.png)

在上一轮压入节点全部弹出后(依据leveles判断)，将vector\<int>压入vector\<vector\<int>>中，并清空数据

![image-20241103110956244](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411031109290.png)

上一轮节点的子节点已经全部压入queue中，对leveles进行修正

![image-20241103110956244](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411031109290.png)

----------------

当队列不为空时，将上一轮压入队列的节点记录并弹出

![image-20241103111300143](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411031113191.png)

将弹出节点映射的数据压入vector\<int>

![image-20241103111321030](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411031113074.png)

将当前节点的子节点压入queue

![image-20241103111321030](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411031113074.png)

将上一轮压入队列的节点记录并弹出

![image-20241103111550520](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411031115578.png)

将弹出节点映射的数据压入vector\<int>

![image-20241103111609516](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411031116563.png)

将当前节点的子节点压入queue

![image-20241103111609516](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411031116563.png)

在上一轮压入节点全部弹出后(依据leveles判断)，将vector\<int>压入vector\<vector\<int>>中，并清空数据

![image-20241103111641825](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411031116870.png)

上一轮节点的子节点已经全部压入queue中，对leveles进行修正

![image-20241103111703391](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411031117440.png)

当队列不为空时，为空，返回，退出

```cpp
////Definition for a binary tree node.
//struct TreeNode {
//	int val;
//	TreeNode* left;
//	TreeNode* right;
//	TreeNode() : val(0), left(nullptr), right(nullptr) {}
//	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
//	TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
//};
 

//#include<vector>
//#include<queue>

//using namespace std;

class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> vv;
        queue<TreeNode*> q;
        int leveles = 0;
        if (root) {
            q.push(root);
            leveles = q.size();
        }

        while (!q.empty()) {
            vector<int> v;
            while (leveles--) {
                TreeNode* current = q.front();
                q.pop();

                v.push_back(current->val);

                if (current->left) {
                    q.push(current->left);
                }
                if (current->right) {
                    q.push(current->right);
                }
            }
            vv.push_back(v);
            v.clear();
            leveles = q.size();
        }
        return vv;
    }
};
```

![image-20241103114938296](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411031149358.png)

根节点是否为空，不为空，则入vector\<TreeNode*>

![image-20241103115157096](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411031151142.png)

当前层是否为空，不为空，则遍历，一方面，把元素对应的值压入vector\<int>，另一方面，把元素子节点压入下一层

![image-20241103115445927](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411031154974.png)

当前层遍历结束，清空

![image-20241103115524846](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411031155894.png)

将vector\<int>压入vector\<vector\<int>>，并清空

![image-20241103115716485](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411031157531.png)

当前层与下一层交换

![image-20241103115806029](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411031158080.png)

---------------

当前层是否为空，不为空，则遍历，一方面，把元素对应的值压入vector\<int>，另一方面，把元素子节点压入下一层

![image-20241103115847003](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411031158051.png)

![image-20241103115927597](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411031159642.png)

当前层遍历结束，清空

![image-20241103120037950](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411031200997.png)

将vector\<int>压入vector\<vector\<int>>，并清空

![image-20241103120114343](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411031201397.png)

当前层与下一层交换

![image-20241103120156536](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411031201585.png)

当前层是否为空，不为空，则遍历，一方面，把元素对应的值压入vector\<int>，另一方面，把元素子节点压入下一层

![image-20241103120237097](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411031202145.png)

![image-20241103120258112](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411031202160.png)

当前层遍历结束，清空

![](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411031203479.png)

将vector\<int>压入vector\<vector\<int>>，并清空

![image-20241103120442868](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411031204914.png)

当前层与下一层交换

![image-20241103120442868](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411031204914.png)

当前层为空，返回，退出，结束

```cpp
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> vv;
        vector<TreeNode*> current;
        vector<TreeNode*> next;
        vector<int> val;

        if (root) {
            current.push_back(root);
        }

        while (!current.empty()) {
            for (auto e : current) {
                val.push_back(e->val);

                if (e->left) {
                    next.push_back(e->left);
                }
                if (e->right) {
                    next.push_back(e->right);
                }
            }
            vv.push_back(val);
            val.clear();
            current.clear();
            current.swap(next);
        }
        return vv;
    }
};
```

##### [evaluation of reverse polish notation](https://leetcode.cn/problems/evaluate-reverse-polish-notation)

下面说说如何把中缀表达式转换成后缀表达式

为了对表达式中的各个部分进行区分，我们使用vextor\<string>的形式来存储表达式

![image-20241103203450456](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411032034632.png)

数字直接压入`vector<string>`

![image-20241103203843227](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411032038288.png)

当遍历到的元素为操作符时，若satck就为空，则直接压入其中

![image-20241103204027651](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411032040739.png)

![image-20241103204222300](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411032042354.png)

stack不为空，当前元素又是操作符时，需要比较优先级

当栈顶操作符优先级高于元素操作符时，说明栈顶操作符先使用操作数，所以它要出栈，压入vector\<string>，之后再把元素操作符压入栈中

当栈顶操作符优先级低于或者等于元素操作符时，说明栈顶操作符不先使用操作数，所以它不用出栈，之后再把元素操作符压入栈中

![image-20241103204828393](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411032048447.png)

![image-20241103204858831](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411032048881.png)

元素遍历完后，将栈中数据压入vector\<string>

![image-20241103205012116](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411032050175.png)

![image-20241103205053217](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411032050277.png)

如果遇到括号，则将括号中的部分以子问题的形式进行递归迭代。

具体代码不作赘述，由于下面代码未经过全面测试，所以只以截图展示部分

括号中的部分以子问题形式递归解决

![image-20241103205448846](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411032054252.png)

接口

![image-20241103205546522](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411032055905.png)

![image-20241103205620155](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411032056553.png)

匹配器用于对`()`进行匹配

![image-20241103205813063](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411032058403.png)

括号匹配模块

![image-20241103210102112](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411032101644.png)

栈顶操作符和元素操作符的优先级比较

![image-20241103210223356](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411032102804.png)

![image-20241103210344594](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411032103675.png)

题目当中只要求计算后缀表达式，不需要转换

此时是数字入栈，检索到操作符后直接计算即可。

```cpp
class Solution {
	bool operators(const string& s) {
		if (s.size() == 1) {
			if (s[0] == '+' || s[0] == '-' || s[0] == '*' || s[0] == '/')
				return true;
			else
				return false;
		}
		else {
			return false;
		}
	}

public:
	int evalRPN(vector<string>& tokens) {
		stack<string> s;
		for (auto e : tokens) {
			if (operators(e)) {
				int right = stoi(s.top());
				s.pop();
				int left = stoi(s.top());
				s.pop();

				int end = 0;
				switch (e[0]) {
				case '+':
					end = left + right;
					break;
				case '-':
					end = left - right;
					break;
				case '*':
					end = left * right;
					break;
				case '/':
					end = left / right;
					break;
				}
				s.push(to_string(end));
			}
			else {
				s.push(e);
			}
		}
		return stoi(s.top());
	}
};
```

### realization

栈和队列都是容器适配器，简单地说，它们都是由其它容器作一定封装后实现的，从文档中我们可以看到，栈和队列的底层其实就是`deque`【双端队列】，双端队列其实不是严格意义上的队列，所以最好还是用`deque`称呼它最好。

```cpp
template<class T, class containers = std::deque<T>>
class stack {
public:

	void push(const T& val)
	{
		_con.push_back(val);
	}

	void pop()
	{
		_con.pop_back();
	}

	size_t size()
	{
		return _con.size();
	}

	bool empty()
	{
		return _con.empty();
	}

	T& top()
	{
		return _con.back();
	}

private:
	containers _con;
};
```

就像前面的文档说的那样，只要支持这些接口，一个容器就可以成为栈和队列的底层容器。

至于`deque`，它是个四不像，有很多的接口，但效率都没能发挥到极致

![image-20241103214455455](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411032144606.png)

`deque`是`vector`和`list`的妥协版，从宏观上看，`deque`由一个个地址并不连续的节点构成，从细节上看，它的节点像是一个小的`vector`

一般来说，`deque`的每一个小节点元素个数都是相同的，在插入数据时，它会先从节点小数组的中间插入数据，这样，`deque`就能很方便的对头尾元素进行操作，而当节点小数组满了之后，`deque`会再开辟一个小节点，供头部或者尾部插入数据。除此之外，`deque`还有一个“中控数组”，中控数组本质是个指针数组，指向节点小数组的开始，当“中控数组”满了之后，再从别处开辟一个更大的空间，再对原空间中的数据（指针）进行浅拷贝。

这种特殊的组织形式，使得`deque`对头尾数据的操作非常便捷，同时由于节点小数组的元素个数固定，也能实现随机访问，不过因为它要依赖一些中间层，所以就随机访问而言，它的效率远远比不上`vector`，以至于`deque`尽管有随机迭代器，可以使用算法库中的`sort`，但如果真要排序的时候，一般都是直接把`deque`中的元素复制到`veector`，然后再对`vector`使用算法库的`sort`，`vector`排完之后再写回`deque`。至于中间插入数据，由于要挪动数据，所以效率不行。

不过这种组织形式使得它的迭代器较为复杂，有四个成员：`cur`指向当前位置，`first  last`指向节点小数组首尾，`node`指向中控数组对应的节点。

![image-20241104084326489](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411040843696.png)

这种组织形式尽管复杂，但实际易懂，比如仅凭上面的一张图，就可以大致看出`deque`迭代器的迭代方式。

```cpp
void using2(const int N)
{
	srand(time(0));

	std::deque<int> obj1, obj2;
	for (int i = 0; i < N; i++)
	{
		int e = rand();
		obj1.push_back(e);
		obj2.push_back(e);
	}

	int begin1 = clock();
	std::vector<int> v(obj1.begin(), obj1.end());
	std::sort(v.begin(), v.end());
	obj1.assign(v.begin(), v.end());
	int end1 = clock();

	int begin2 = clock();
	sort(obj2.begin(), obj2.end());
	int end2 = clock();

	std::cout << "deque->vector->deque:" << end1 - begin1 << "ms." << std::endl;
	std::cout << "deque:" << end2 - begin2 << "ms." << std::endl;
}

int main()
{
	using2(1000000);
	return 0;
}
```

![image-20241104085634328](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411040856749.png)



## queue
### feel

#### [documentation](https://legacy.cplusplus.com/reference/queue/queue/)

queues are a type of container adaptor, specifically designed to operate in a FIFO context (first-in first-out), where elements are inserted into `one end of`【一端】 the container and `extracted`【提取】 from the `other`【另一端】.

queues are `implemented as`【实现为】 containers adaptors, which are classes that use an encapsulated object of a specific container class as its underlying container, providing a specific set of member functions to access its elements. `Elements are pushed into the "back" of the specific container and popped from its "front".`【元素被推入特定容器的“后面”，从“前面”弹出。】

The underlying container may be one of the standard container class template or some other specifically designed container class. This underlying container shall support at least the following operations:

- empty（是否为空）
- size（大小）
- front（获取第一个元素）
- back（获取最后一个元素）
- push_back（在末尾添加元素）
- pop_front（从前面移除元素）

The standard container classes [deque](https://legacy.cplusplus.com/deque) and [list](https://legacy.cplusplus.com/list) fulfill these requirements. By default, if no container class is specified for a particular queue class instantiation, the standard container [deque](https://legacy.cplusplus.com/deque) is used.

##### Template parameters

| **member type** | **definition**                            | **notes**                                                    |
| --------------- | ----------------------------------------- | ------------------------------------------------------------ |
| value_type      | The first template parameter (T)          | Type of the elements                                         |
| container_type  | The second template parameter (Container) | Type of the *underlying container*                           |
| size_type       | an unsigned integral type                 | usually the same as [size_t](https://legacy.cplusplus.com/size_t) |

##### Member functions

|                                                              |                                                           |
| ------------------------------------------------------------ | --------------------------------------------------------- |
| [**(constructor)**](https://legacy.cplusplus.com/reference/queue/queue/queue/) | Construct queue (public member function )                 |
| [**empty**](https://legacy.cplusplus.com/reference/queue/queue/empty/) | Test whether container is empty (public member function ) |
| [**size**](https://legacy.cplusplus.com/reference/queue/queue/size/) | Return size (public member function )                     |
| [**front**](https://legacy.cplusplus.com/reference/queue/queue/front/) | Access next element (public member function )             |
| [**back**](https://legacy.cplusplus.com/reference/queue/queue/back/) | Access last element (public member function )             |
| [**push**](https://legacy.cplusplus.com/reference/queue/queue/push/) | Insert element (public member function )                  |
| [**emplace** ](https://legacy.cplusplus.com/reference/queue/queue/emplace/) | Construct and insert element (public member function )    |
| [**pop**](https://legacy.cplusplus.com/reference/queue/queue/pop/) | Remove next element (public member function )             |
| [**swap** ](https://legacy.cplusplus.com/reference/queue/queue/swap/) | Swap contents (public member function )                   |

##### Non-member function overloads

|                                                              |                                                       |
| ------------------------------------------------------------ | ----------------------------------------------------- |
| [**relational operators**](https://legacy.cplusplus.com/reference/queue/queue/operators/) | Relational operators for queue (function )            |
| [**swap (queue)** ](https://legacy.cplusplus.com/reference/queue/queue/swap-free/) | Exchange contents of queues (public member function ) |

##### Non-member class specializations

|                                                              |                                            |
| ------------------------------------------------------------ | ------------------------------------------ |
| [**uses_allocator** ](https://legacy.cplusplus.com/reference/queue/queue/uses_allocator/) | Uses allocator for queue (class template ) |

### realization

```cpp
template<class T, class containers = std::deque<T>>
class queue {
public:

	void push(const T& val)
	{
		_con.push_back(val);
	}

	void pop()
	{
		_con.pop_front();
	}

	size_t size()
	{
		return _con.size();
	}

	bool empty()
	{
		return _con.empty();
	}

	T& front()
	{
		return _con.front();
	}

	T& back()
	{
		return _con.back();
	}

private:
	containers _con;
};
```

# end

