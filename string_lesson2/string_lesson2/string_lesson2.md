# string_课时2

## 模版之问

我们知道标准库中的`string`实际是`basic_string`模版类关于`char`的实例化。而在《string》,也就是上篇(合并之后就变成刚刚了)文章里，官方文档其实已经说了`string`为模版的原因：

:::comment
啊, 那时候英语不太好, 有些执念, 所以这样写, 后来我把部分类似形式进行了简化处理. (不过, 技术学习和英语学习不要放在一块, 那种学习方法个人感觉不太好)
:::

![image-20241017170223725](https://img.mdwind.online/md/202410171702925.png)

一句话来说，这是为了让C++国际化，可以让不同国家和地区的字符语言需求都得到满足。本片文章的主要内容是实现一个基本的`string`类，但我们不会采用模版的方式，因为这涉及到一些我们还未学习的内容，再加上我们文档已经说了，对于多字节字符以及变长字符`string`都可以使用，所以我们就直接用`char`类型了，等以后对C++的学习更上一层楼后再回来真正地实现。

下面我们稍微过一过字符的主要编码模式：

当今计算机都是二进制的，为了让字符与二进制序列建立映射关系，就出现了ASCII码。ASCII码只有一个字节，它对于英语等拉丁字母语言差不多够用，但其它语言就不太够用了，所以就有人研究出了`Unicode`，其中最常用的就是`UTF-8`:

![image-20241017172651572](https://img.mdwind.online/md/202410171726630.png)

如图所见`UTF-8`是一种变长编码，它的具体字节数并不确定，有一字节，两字节，三字节，四字节这四种。不过对于常用的汉字来说基本都在两字节。`UTF-8`的变长属性，可以使得它以更少的字节存储字符，但它的变长属性也使得它比较复杂，不易管理。不过它仍然是适用范围最广的编码格式。

为了让编码格式更适应于以汉字为基础的东亚文字字符系统，中国信息化技术标准委员会以`UTF-8`为基础，推出了`GBK`系列编码格式，以下为百度百科的相关描述：

![image-20241017182940363](https://img.mdwind.online/md/202410171829406.png)

`Windows`系统主要是以GBK系列编码格式进行汉化的(毕竟他们的商业化行为需要中国政府的默许, 当然更喜欢迎合中国自己制定的国家标准)，微软的其它产品，例如VS，office他们的汉化也都主要用GBK系列。`Linux`系统则更喜欢使用`UTF-8`(所以有的源代码文件传到linux中文注释会变成乱码)。

## 基本实现

:::comment
注意: 代码以新版本为准, 在新版本中, 我们对与成员将引入 SSO 设计

这里我们采取单 hpp 的形式, 一方面是为了省事, 另一方面, 后面那些容器都要写成模板形式, 还必须要写成 hpp 

```cpp
// 我学的时候, 对于静态成员变量大概会这样写
// 因为我学的主要是 C++98到C++14
// 因为是在 hpp 里, 所以外部定义又声明了内联
#pragma once

#include <cstddef>

namespace wind {
    class string{
        static std::size_t SSO_CAPACITY; 
    };

    inline std::size_t string::SSO_CAPACITY = 15;
}
// 具体的有关静态成员的解释我们在C++类和对象, 静态成员小节中
// 有详细说明, 目前更加现代的有关静态成员定义的方法是 inline
// 或者 constexpr (隐式携带inline)

#pragma once

#include <cstddef>

namespace wind {
class string {
   public:
    string() {}

   private:
    static constexpr std::size_t SSO_CAPACITY = 15;
    union storage {
        // 注意末尾还有一个 '\0' , 所以加1
        char _buffer[SSO_CAPACITY + 1];
        char* _ptr;
    };

    // 对于成员函数, 我们先设置缺省值
    // 如果确实有必要, 再用初始化列表进行修改
    storage _storage{};  // 这是空列表初始化, 明确要求编译器对联合体第一个成员进行清零,
                         // 由于其是最大成员, 顺带也给可能的 _ptr 一并初始化为0了
    size_t _size = 0;    // 最开始没有字符串, 长度为0
    size_t _capacity = string::SSO_CAPACITY;  // 最开始使用 SSO , 缓冲区大小固定

    // 内部方法 通过容量的大小判断使用哪种模式
    // const 表示不对对象进行写操作
    // noexcept 表示在设计意图上
    // 不会抛异常, 但到底会不会抛一场
    // 要看具体代码实现
    bool is_sso() const noexcept {
        return _capacity == string::SSO_CAPACITY;
    }
};
}  // namespace wind
```
:::

:::note
讨论: C++ 中的联合体

乍看上去, C++ 中的联合体和 C 里面的联合体差不多

都是共享空间, 比如在上面的缺省值中, 空的列表初始化

会将第一个成员也就是16字节大小的缓冲区全部清零

而由于其是最大的成员, 所以实际上也相当于把 _ptr 也给

置为空, 此时如果你去读 _ptr, 虽然感觉有点不合规, 但也

没太大问题, 读到的还是空指针
但是, 如果我们将 C++ 对于类和对象的声明周期管理方法

也就是构造析构牵扯进来, 就变得复杂了, 比如我们再定义

一个联合体, 两个成员, 分别是内置类型和非平凡构造析构

的自定义类, 那么由于空间是共享的, 编译器怎么知道

我用的到底是这个自定义类型还是那个内置类型, 从而自动

调用构造析构函数呢?                 答案就是, 编译器确实不知道

对于这种情况, 他也不会考虑什么调用构造析构函数的时机

而是完全交给我们进行显式构造和析构, 如果你把联合体的这片

空间视为自定义对象, 那么你就使用定位 new 表达式, 进行显式

构造, 或者使用类似功能, 在C++20新引入的std::construct_at方法

如果这片空间将释放, 你就显式调用析构函数或者使用类似功能的

std::destroy_at方法(在C++17引入), 如果你不想操心这些破事

你可以使用std::variant, 他内部除了联合体之外, 还有一个标签

可以描述当前联合体是以什么样的方式去解释的, 不过就当前而言

我们当然不需要搞得那么复杂, 这两个(字符数组, 指针)都是内置类型

除了要提防一下他们的数值会相互干扰之外, 顶多再考虑一下用堆存储

字符串时, 记得最后要释放空间, 并且我们还可以通过容量来判断当前是

如何使用联合体的, 这也起着标签的作用
:::

(gpt: note是确定的正文旁注, comment 则是批注, 又是其中一些也是尚未进行整理的正式旁注)

我们的`string`其实就四个成员：字符串空间的索引指针，有效字符个数，可容纳个数，静态成员`npos`。不过我们先只写前三个成员，后续会用`npos`引出一些C++特别语法。

```cpp
namespace wind
{
	class string
	{
	public:
		
	private:
		char* _str;
		size_t _size;
		size_t _capacity;
	};
}
```

### string(const char* str)

~~我们在先前说过，对于构造函数来说，应尽可能使用初始化列表进行初始化~~(我不记得我说过, 这种说法有些太偏激了)，除此之外，我们还说了初始化列表的初始化顺序是依照声明顺序，而不是初始化列表顺序，这意味着，写初始化列表要以声明顺序来写，防止因顺序问题出现错误。

:::comment
在无参默认构造中, 尽管我们已经设置了缺省值, 但是为了进行示范, 我们也用一下初始化列表, 

但之后的别的构造函数, 我们就直接使用声明上的缺省值了，针对他们的优先级顺序我们在之前

的类和对象文章中已经提过

```
// public:
    string() : _storage(storage()), _size(0), _capacity(string::SSO_CAPACITY) {}
```

在正式写第一个有参构造之前， 我们还需要写一些有关空间申请与管理的私有方法， 以便于对这些功能进行统一的管理

我们的思路是将接口分为三层进行处理:
![](https://img.mdwind.online/img/20261107143355040.png)
![](https://img.mdwind.online/img/20261107143517402.png)

如果把这三层接口比作一个微型社会，那么第一层就是基层劳动者，负责完成最基础、最具体的工作；第三层则是决策层，负责制定策略、发号施令，通常不亲自参与具体劳动。

至于第二层，颇有些中产阶层的味道：上面提出要求，下面提供能力，自己负责组织协调、严格落实。既要理解上层的意图，又要保证底层的执行结果符合预期。出了问题，还得先检查是不是自己落实得不到位。

看来，即便是在程序设计中，中间层也逃不过承上启下的命运。

先看第一层, 没什么好说的, 就是很平常的空间申请和释放, 由于他们也不需要具体的对象情况, 所以直接设置成静态成员函数

```cpp
    // 申请指定容量的堆空间
    static char* allocate(size_t capacity) {
        return new char[capacity + 1];
    }

    // 释放堆空间
    static void deallocate(char* ptr) noexcept {
        delete[] ptr;
    }
```

接下来我们写第二层, 这就不是很好写了,就像之前我们打趣的那样说法, 中间事情多, 而且不能自己决定做什么事

```cpp
// 依据上层指示进行严格扩容
    void grow_capacity(size_t new_capacity) {
        BOOST_ASSERT_MSG(
            new_capacity > _capacity,
            "This function requires a capacity greater than the current capacity.");  // 此函数在设计上不负责缩小容量
        BOOST_ASSERT_MSG(
            new_capacity <= max_capacity,
            "This function does not perform capacity overflow checks.");  // 此函数在设计上不负责容量溢出检查

        char* new_ptr = allocate(new_capacity);

        std::memcpy(new_ptr, data(), _size + 1);

        if (!is_sso()) deallocate(_storage._ptr);

        _storage._ptr = new_ptr;
        _capacity = new_capacity;
    }
```

前面两个是C++扩展库Boost 中的断言, Boost 我们之后我们也会稍微说一下的, 这两个断言用基础的 assert 来写就是

```cpp
#include <cassert>

assert(new_capacity > _capacity &&
       "This function requires a capacity greater than the current capacity."); // 此函数在设计上不负责缩小容量

assert(new_capacity <= max_capacity &&
       "This function does not perform capacity overflow checks."); // 此函数在设计上不负责容量溢出检查
       
// 利用 && 的短路求值机制附带自定义错误信息：
// 条件成立时，整个表达式为 true，断言通过；
// 条件不成立时，整个表达式为 false，断言失败，
// 错误信息字符串会作为断言表达式的一部分显示在诊断信息中。
```

我为什么突然要在这里加两个断言呢? 这是因为中间层不具有自主决策的能力(在设计定位上), 但是也不能说, 上层传了一个看起来明显不对的参数

中间层闭着眼去执行, 所以我在这里以断言形式对输入参数进行了检查, 这样, 如果我写上层代码突然不知道怎么想的, 输入了一个在设计上不该输入的

参数, 那么下层也可以在代码调试阶段对我进行反映, 而在程序具体发布之后, 断言自动也就失效了, 也没什么多余负担, 当然现在也是  AI 写代码了

那就是向 AI 强调一下接口的参数要求, 对了, 我要强调这是私有成员函数

第一个断言是为了强调该接口不允许进行容量缩小操作, 一方面, 我们在设计定位上, 他就是扩容的, 不应该干缩容的事, 另一方面, 由于我们底层对于字符串的存储

引入了 SSO 机制, 如果缩容的话, 可能要面对一些更为复杂的, 在堆存储模式和 SSO 模式之间的转换, 也就是 回迁到 SSO, 当然扩容也涉及到两个模式的转换, 但他

较为简单: 最多只是从 SSO 到堆, , 如果要回迁  SSO , 还要处理一些额外的逻辑, 实现里面实际上也没有这种逻辑. 

第二个断言不是我加的, chatgpt 担心上层输入一个很大的数, 导致在实际实际空间申请中, 加1发生溢出, 尽管这不太可能, 但确实有道理, 所以采纳了它的建议, 那个

 max_capacity  是静态成员, 因为之后还存在可能用到的地方, 所以我直接把它变成静态成员了, 这里也用到了 C++ 中取得某个类型最大值的方法

![](https://img.mdwind.online/img/20261107160158356.png)

由于该接口设计上就是为了扩容的, 而最小容量就是 SSO 缓冲区中容纳有效字符的数目 SSO_CAPACITY, 所以进入该接口意味着扩容之后肯定是堆模式了, 所以我们紧接着立刻进行了空间申请

然后把原来的数据拷贝过去, 由于 _capacity 还未进行调整, 使用的仍旧是之前的值, 所以 is_sso() 的判断是可信的, 据此我们决定是否要释放之前的空间, 最后调整相关成员, data() 好像之前没有

写, 此处补上

```cpp
public:
    char* data() noexcept {
        return is_sso() ? _storage._buffer : _storage._ptr;
    }
```

接下来看中间的缩容接口

```cpp
 // 依据上层指示进行严格缩容
    void shrink_capacity(size_t target_capacity) {
        BOOST_ASSERT_MSG(!is_sso(), "This function requires heap storage.");

        BOOST_ASSERT_MSG(target_capacity < _capacity,
                         "This function requires a capacity smaller than the current capacity.");

        BOOST_ASSERT_MSG(target_capacity >= _size,
                         "This function does not support shrinking that causes data loss.");

        if (target_capacity <= SSO_CAPACITY) {
            char* old_ptr = _storage._ptr;

            std::memcpy(_storage._buffer, old_ptr, _size + 1);

            deallocate(old_ptr);
            _capacity = SSO_CAPACITY;
            return;
        }

        char* new_ptr = allocate(target_capacity);

        std::memcpy(new_ptr, _storage._ptr, _size + 1);

        deallocate(_storage._ptr);

        _storage._ptr = new_ptr;
        _capacity = target_capacity;
    }
```

第一个断言是为了强调: 对于仍旧处于 SSO 模式下的对象, 不应该进行缩容, 因为 SSO 模式缓冲区大小就是静态, 我说的是大小是固定的, 不是说静态存储, 自然他不应该被缩容

第二个断言是强调: 缩容一定要是缩容, 不应该输入一个更大的目标容量参数

第三个断言是在强调: 缩容不应该把有效字符给丢弃

当目标容量小于SSO 缓冲区大小时, 我们执行回迁逻辑, 注意由于他们是一个联合体, 所以你不应该直接进行覆写, 而是先保存原来的堆空间指针, 另外一种情况就正常的在堆模式下缩容

接下来我们看对外的 reserve

```cpp
  void reserve(size_t min_capacity) {
        if (min_capacity <= _capacity) return;

        if (min_capacity > max_capacity) throw std::length_error("string capacity overflow");

        // 按 1.5 倍计算，避免整数溢出
        size_t increment = _capacity / 2;

        size_t new_capacity =
            _capacity > max_capacity - increment ? max_capacity : _capacity + increment;

        new_capacity = std::max(new_capacity, min_capacity);

        grow_capacity(new_capacity);
    }
```

我们按照 1.5 的增长速度先推出一个预选值, 最终选择预选值和最小容量要求中更大的那一个提供给下层. 第一个 if 判断, 当前容量已经满足要求, 第二个 if , 检查是否可能溢出, 如果命中, 就抛异常, 我们没有细说异常, 但现在其实已经

可以使用了, 抛出异常的关键字是 throw, 后面实例化出一个具体的匿名异常对象, 该接口的定位是审议出具体的扩容参数, 交给下面执行

shrink_to_fit 逻辑更加简单, 就是进行一下条件判断, 是 SSO 模式, 不用适应性缩容, 已经满足要求, 也不用缩容, 显然 _capacity是一定大于等于 _size 的, 所以对此不需要条件判断

```cpp
 void shrink_to_fit() {
        if (is_sso()) return;

        if (_capacity == _size) return;

        shrink_capacity(_size);
    }
```

之后我们来看 append, 这里写这么多, 其实一个目的就是再写一个支持 const char* 的构造函数--只需要把常年字符串交给 append

```cpp
self& append(const char* str) {
        // 将指针转换为无符号整数，通过地址区间判断是否存在自引用
        const auto begin_addr = reinterpret_cast<std::uintptr_t>(data());
        const auto source_addr = reinterpret_cast<std::uintptr_t>(str);

        const bool self_reference = source_addr >= begin_addr && source_addr - begin_addr <= _size;

        // 如果存在自引用，提前记录源字符串相对于当前字符串的偏移量
        // 避免扩容后原始指针失效，导致无法重新定位源字符串
        const size_t offset = self_reference ? static_cast<size_t>(source_addr - begin_addr) : 0;

        const size_t len = std::strlen(str);

        if (len > max_capacity - _size) throw std::length_error("string capacity overflow");

        // 根据追加后的长度决定是否扩容
        reserve(_size + len);

        // 自引用时，通过偏移量重新定位源字符串
        // 普通情况下，继续使用原始指针
        const char* source = self_reference ? data() + offset : str;

        // 只复制有效字符，不复制原字符串的结束符
        // 这样即使存在自引用，源区域与目标区域也不会发生重叠
        std::memcpy(data() + _size, source, len);

        // 更新字符串长度，并统一补充结束符
        _size += len;
        data()[_size] = '\0';

        return *this;
    }
```

append 其实主逻辑非常清晰, 就是把提供的常量字符串往存储字符串的空间后面进行拼接, 当然前提是空间足够, 所以我们还有扩容要求, 但为什么我们写了这么多东西, 这是因为 append 可能会触发名为自引用的特殊情况

![](https://img.mdwind.online/img/20261107172049499.png)

我原本最开始是想直接拿指针去进行比较, 看看有没有落到自指区间上, 但是 chatgpt 在纠结 "指针在语法上不应该比大小", 我最开始认为这个考虑是对的, 但是很快我又意识到, 我被它绕进去了, 这只是形式上的问题, 在逻辑上

是完全没有问题的, 经过协商, 我们决定将指针转化为C++中表示地址的无符号数据类型  std::uintptr_t, reinterpret_cast 我们之前可能没有说过, 他是 C++ 中用于类型转换的操作符, C中对于类型转换的方式是 (type)v;  但是

这种方式不会进行类型检查, 不会判断这种强转是否在语法上是允许的, 所以 C++ 里面就有了 reinterpret_cast, 不过如果你不想进行任何类型检查, 就类似与 C 那种直接类型转换, 所用的操作符是 static_cast, 用法都是一样的

其实我觉得这里使用 static_cast 没什么大问题, 但它用 reinterpret_cast 就用  reinterpret_cast 吧. 我们使用 self_reference 表示有没有落在区间上, 从两个角度来看, 一是 str有没有从 data() 之后开始, 如果没有, 那肯定不再

区间里, 内存分配不可能给你找一个已经部分用过的内存块, 如果在后面, 并且与 data() 的距离在 _size之内, 就说明在区间里, 当然你也可以直观的进行区间形式上的比较, 最后的终止符也最后统一加上, 另一个注意点是, 为了让他支持

之后 += 重载返回自身的需求, 我们最后返回关于对象自身的引用, self 是对于自身类型的重定义, 之后我们在模板里面还会更多的见到这种形式--那样能少写模板的类型参数

对于string(const char*)的实现就很简单了

![](https://img.mdwind.online/img/20261107174013290.png)

接下来我们再写两个私有的清理方法, 这两个清理是从不同角度上进行的

第一个清理, 是清理容器中存储的字符串

```cpp
// 清空字符串内容，保留现有存储空间
    void clear_content() noexcept {
        _size = 0;
        data()[0] = '\0';
    }
```

他这个, 其实就是 clear 的逻辑, 等会我们外面也会直接套一层 clear

保留额外的存储结构(其实我说的就是堆空间, 只不过用"额外的存储结构"更抽象一些,

毕竟底层的资源申请接口 allocate, deallocate, 可以进行更换, 我们当初特意分离出来

不就是为了快速切换新的空间申请方式吗)是为了应对这种场景, 有两个长度差不多的字符串

其中一个存储在对象中, 现在你不想要对象中的这个字符串了, 想把另外一个字符串存

上去, 就可以先 clear, 再追加

第二个清理, 会将额外的存储结构进行释放

```cpp
// 释放额外存储空间，并恢复对象的初始状态
    // 一个主要用途是给析构做清理调用
    // 我们称之为"怎么来的, 就怎么走"
    void release_storage() noexcept {
        if (!is_sso()) deallocate(_storage._ptr);

        _storage._buffer[0] = '\0';
        _size = 0;
        _capacity = SSO_CAPACITY;
    }
```

他会释放可能存在的额外存储结构, 然后回到最开始的 SSO 状态, 并且也只存储一个空字符串, 就像无参构造那样

怎么来的, 就怎么走, 也是计算机里面常见的思路.

三个配套的公开接口是

```cpp
void clear() {
        clear_content();
    }

    void reset_storage(){
        release_storage();
    }
    
 ~string() {
        release_storage();
    }
```

这两个表示成员接口就不说了

![](https://img.mdwind.online/img/20261107205653048.png)

接下来我们写一个 string 关于 [] 的重载我们依据标准库中的说明, 不检查 [] 是否越界, 为了让常对象和普通对象都能使用, 会提供两个版本

![](https://img.mdwind.online/img/20261107211234549.png)

为了进行适配, data 也增加了一个常对象版本

这里是断言检查, 发布版本断言失效, 所以实际上还是归类为不进行检查

既然写了 operator[], 我们也写一下 at, at 会复用 operator[], 但是会对参数进行检查

这里我们也顺便写一下 at, 复用之前的重载函数

![](https://img.mdwind.online/img/20261107211749295.png)

接下来我们来写迭代器, 我们之前说过, 迭代器是对容器中存储元素的统一访问方式, 甚至有的就是对指针的进一步包装, 对于此处的 string 来说

他所储存的元素的字符(不过这些字符有些特别要求, 末尾必须是'\0', )所以迭代器解引用之后就是 string 中的字符, 为此, 对于 begin 和 end, 我们

会分别返回 data() 和 data()+_size, 并且, 更好的是, 指针本身就支持加加以及不等于, 所以我们不需要再设计迭代器类型的加加和不等于重载了

![](https://img.mdwind.online/img/20261107213959587.png)

![](https://img.mdwind.online/img/20261107213753661.png)

那个逆迭代器我们就省略不写了

接下来我们去写 其他版本的 append, 但是再次之前我们先定义静态成员变量 npos, 不过, 在定义 npos 的时候, 我意识到, 之前找 size_t 的方式有些太花哨了, 实际上倒数第二大的数不就是 -2 吗

![](https://img.mdwind.online/img/20261107215240791.png)

接下来我们看看这个版本的 append

```cpp
// 从字符数组中追加 n 个字符，允许包含 '\0'
    self& append(const char* chars, size_t n) {
        if (n == 0) return *this;

        // 检查追加后的容量是否溢出
        if (n > max_capacity - _size) throw std::length_error("string capacity overflow");

        // 判断源地址是否位于当前字符串的有效存储范围内
        const auto begin_addr = reinterpret_cast<std::uintptr_t>(data());
        const auto end_addr = reinterpret_cast<std::uintptr_t>(data() + _size);
        const auto source_addr = reinterpret_cast<std::uintptr_t>(chars);

        const bool self_reference = source_addr >= begin_addr && source_addr <= end_addr;

        // 如果存在自引用，记录源地址相对于当前字符串的偏移量
        const size_t offset = self_reference ? static_cast<size_t>(source_addr - begin_addr) : 0;

        // 根据追加后的字符数量决定是否扩容
        reserve(_size + n);

        // 扩容可能导致原地址失效，因此需要重新定位自引用源地址
        const char* source = self_reference ? data() + offset : chars;

        // 复制指定数量的字符，允许源区域与目标区域重叠
        std::memmove(data() + _size, source, n);

        // 更新长度，统一补充字符串结束符
        _size += n;
        data()[_size] = '\0';

        return *this;
    }
```

他的大体逻辑其实和第一个 append 差不多, 但是一个需要强调的地方是, 这里的第一个参数是一个字符数组, 而非字符串, 字符串是字符数组的一个特例: 它要求最后一个字符是'\0', 并且中间一般不带有'\0', 但是字符数组可就不一样了, 因此我们这里不应该使用 strlen 求出 chars 的长度, n 将成为唯一的长度参考, 另外我们也可以意识到, 之前 const char* 版本完全可以复用当前这个字符数组版本, 所以可以对原来的写法进行修改, 

接下来的两个重载和另一个对象(但其实也允许是自己)有关

```cpp
 self& append(const char* str) {
        return append(str, std::strlen(str));
    }

    // 从另一个 string 的指定位置开始，追加最多 sublen 个字符
    self& append(const self& str, size_t subpos, size_t sublen = npos) {
        // 起始位置不能超过源字符串长度
        if (subpos > str._size) throw std::out_of_range("string::append: subpos out of range");

        // 根据剩余字符数量确定实际追加长度
        const size_t len = std::min(sublen, str._size - subpos);

        // 复用字符数组追加接口
        return append(str.data() + subpos, len);
    }

    // 追加另一个 string 的全部内容
    self& append(const self& str) {
        return append(str, 0);
    }
```

继续

```cpp
// 在字符串末尾追加 n 个字符 c
    self& append(size_t n, char c) {
        if (n == 0) return *this;

        // 检查追加后的容量是否溢出
        if (n > max_capacity - _size) throw std::length_error("string capacity overflow");

        // 确保具有足够的存储空间
        reserve(_size + n);

        // 将 n 个字符 c 填充到字符串末尾
        std::fill_n(data() + _size, n, c);

        // 更新长度，并补充字符串结束符
        _size += n;
        data()[_size] = '\0';

        return *this;
    }
```

这里唯一需要特别说的, 可能就是 std::fill_n, 在这里, 你可以将其理解为 memset, 相比 memset 来说, 他的优点是可以适应性控制单位元素大小, memset 的单位只能是一个字节, 所以如果元素是多字节的, 使用 memset 会出现问题, 但是 std::fill_n 是一个模板函数, 会将第一个参数看作一个迭代器, 于是就通过迭代器的方式会自动调整单位长度, 这样对于非一字节的类型, 也可以正常使用

对于迭代器版本的 append, 可以写一个支持迭代器的构造函数, 然后复用构造函数, 创建一个临时的 string 对象, 进行追加, 这样可以完全避开自引用问题

```cpp
// 追加迭代器区间中的字符
    template <class InputIterator>
    self& append(InputIterator first, InputIterator last) {
        // 先构造独立的临时字符串，避免自引用时迭代器失效
        self temp(first, last);

        // 复用已有的字符串追加接口
        return append(temp);
    }
```

这里我们写了一个成员函数模板, 对于两个参数类型相同的 append 调用来说, 就可能选中这个模板, 实例化出对应迭代器的具体函数来进行调用

在C++20之前, 我们就只能写到这个地步了, 但是对于这种写法来说, 仍旧存在一些问题: 就像上面我所说那样, 是两个参数类型相同的 append, 但这个类型到底是不是一个能用的迭代器, 是并不清楚的

我举一个例子, 假设我们有增加了一个构造函数 `string(size_t n, char c);`, 它负责创建包含 `n` 个字符 `c` 的字符串, 现在调用 `string s(5, 65);`, 尽管我们一看就知道他的意思是拿 A(ASCII 码为 65)去调用 `string(size_t n, char c);`, 构造一个包含`5`个`A`的字符串: 但是对于机器来说会引发歧义, 编译器在进行候选函数审议的时候看到, 5和65都是 int, 看起来和   `self& append(InputIterator first, InputIterator last`,就会命中他, 从而调用了错误的接口, 在 C++20 之前, 对于这种错误, 没有很好的办法去解决, 但是在 C++20 中, 引入了一项专门针对这种问题的特性: 概念与模板约束, 他为我们提供了一项标准概念`std::input_iterator`, 它用来判断某种类型是否满足输入迭代器的要求，包括能读取指向的元素、能够向前推进等, 头文件是 <iterator>, 此时对于这种使用迭代器序列的模板函数来说, 就应该写成`template <std::input_iterator InputIterator>`, 其意思是声明一个名为 `InputIterator` 的模板类型参数，但要求它必须满足 `std::input_iterator` 概念, 此时编译器就会发现5和65尽管是一个类型, 但是感觉完全不是迭代器, 所以他会进行隐式类型转换, 调用 `string(size_t n, char c);`另外C++20还提供了关键字`requires`, 可以显式描述模板约束, 比如约束他应该是个迭代器

```cpp
// 迭代器区间构造
    template <class InputIterator>
        requires std::input_iterator<InputIterator>
    string(InputIterator first, InputIterator last) : string() {
        for (; first != last; ++first) append(1, *first);
    }


 // 追加迭代器区间中的字符
    template <std::input_iterator InputIterator>
    self& append(InputIterator first, InputIterator last) {
        // 先构造独立的临时字符串，避免自引用时迭代器失效
        self temp(first, last);

        // 复用已有的字符串追加接口
        return append(temp);
    }
```

接下来我们去看列表初始化

```cpp
#include <initializer_list>

// 追加初始化列表中的所有字符
self& append(std::initializer_list<char> il) {
    return append(il.begin(), il.size());
}
```

`std::initializer_list` 是 C++11 引入的标准库类模板，可以将其理解为一种轻量级的只读访问适配器。它本身不负责存储元素，而是通过 `begin()`、`end()` 和 `size()` 等成员函数，提供对底层数组的访问能力。

例如：

```
s.append({'H', 'e', 'l', 'l', 'o'});
```

当初始化列表用于构造 `std::initializer_list<char>` 对象时，编译器会在底层创建一个匿名的常量数组，用于存储列表中的字符。这个数组具有临时对象的性质，而 `std::initializer_list<char>` 则通过内部保存的数组访问信息，为外部提供只读访问接口。因此，真正的字符数据存储在匿名数组中，并不存储在 `initializer_list` 对象内部。

这里还涉及一个特殊的生命周期规则：编译器创建的匿名数组原本具有临时对象的生命周期，但在初始化 `std::initializer_list` 时，其生命周期可以按照规定得到延长，效果类似于临时对象绑定到引用(只是类似, 实际不是引用)。在当前示例中，匿名数组会在整个函数调用期间保持有效，因此 `append()` 可以安全地读取其中的字符。

由于底层是字符数组，并不要求以 `'\0'` 结尾，所以我们可以直接复用 `append(const char*, size_t)`，通过数组首地址和元素数量完成追加，而无须借助 `strlen()` 判断长度。

这也体现了之前统一补充字符串终止符的好处：无论传入的字符数组是否以 `'\0'` 结尾，追加操作都会在新字符串的末尾补充终止符。这样既能正确处理普通字符数组，也能保证字符串末尾具有合法的结束标记，避免后续按 C 风格字符串读取时因缺少终止符而越界。

前面介绍的 `std::initializer_list`，可以理解为一种轻量级的只读访问适配器。它通过编译器创建的匿名常量数组提供字符数据，再利用内部保存的访问信息，让我们能够读取这些字符。

不过，如果字符数据已经存在，是否还需要专门创建一个数组？能否直接利用已有的数据，同时避免不必要的字符复制？

C++17 引入的 `std::string_view`（字符串视图）便提供了这样的能力。它同样是一种轻量级的只读访问适配器，通常只需要保存字符序列的首地址和长度，就能够描述一段连续的字符数据。

与 `std::initializer_list` 不同，`std::string_view` 不会为字符创建专门的底层数组，也不负责管理数据的生命周期。它可以直接访问已有的字符串、字符数组，甚至是其中的一部分。

例如：

```
std::string str = "Hello World";std::string_view sv(str.data() + 6, 5);
```

这里的 `sv` 描述了原字符串中的 `"World"`，但没有复制这五个字符。由于它不拥有底层数据，如果原字符串被销毁，或者发生重新分配内存等操作，原来的视图就可能失效。

此外，`std::string_view` 通过长度确定字符范围，并不要求数据以 `'\0'` 结尾，也允许包含内嵌的 `'\0'`。因此，它与我们之前实现的 `append(const char*, size_t)` 十分契合：只需要获取字符的首地址和数量，就能复用已有的追加逻辑。

C++17 也因此为 `std::string::append()` 增加了两个新的模板重载，分别用于追加整个字符串视图，以及追加视图中指定位置开始的部分字符。

这里还涉及一个问题：既然已经存在 `append(const char*)` 等重载，就需要限制新模板的匹配范围，避免它们参与不必要的重载竞争。

我们当前使用的是 C++20，因此可以利用前面接触过的概念（Concepts）和 `requires` 约束来实现：

```
#include <concepts>#include <string_view>// 追加能够转换为字符串视图的字符序列template <class StringViewLike>    requires (        std::convertible_to<const StringViewLike&, std::string_view> &&        !std::convertible_to<const StringViewLike&, const char*>    )self& append(const StringViewLike& t) {    std::string_view view = t;    return append(view.data(), view.size());}// 追加字符串视图中指定位置开始的部分字符template <class StringViewLike>    requires (        std::convertible_to<const StringViewLike&, std::string_view> &&        !std::convertible_to<const StringViewLike&, const char*>    )self& append(const StringViewLike& t, size_t pos, size_t count = npos) {    std::string_view view = t;    std::string_view subview = view.substr(pos, count);    return append(subview.data(), subview.size());}
```

这里的 `requires` 用于规定模板参数需要满足的条件，而 `std::convertible_to` 是 C++20 在 `<concepts>` 中提供的标准概念，用于检查两种类型之间是否满足相应的转换要求。

我们的约束包含两个条件：

```
std::convertible_to<const StringViewLike&, std::string_view>
```

要求传入的对象能够转换为 `std::string_view`。其中，`const StringViewLike&` 对应函数接收的参数类型，而 `std::string_view` 是期望转换得到的目标类型。目标类型不需要添加 `const`，因为字符串视图本身就只提供对底层字符的只读访问。

另一个条件是：

```
!std::convertible_to<const StringViewLike&, const char*>
```

它利用 `!` 排除那些能够转换为 `const char*` 的类型，使 C 风格字符串继续使用我们原先提供的重载。两个条件通过 `&&` 连接，表示必须同时满足，模板才有资格参与重载匹配。

至于具体实现，两个重载都十分简单。第一个直接获取视图的首地址和长度，再复用字符数组追加接口。

第二个则利用 `std::string_view::substr()` 获取子视图。它只调整视图所描述的字符范围，不会复制底层数据。如果起始位置超过原视图的长度，`substr()` 会抛出 `std::out_of_range`；如果指定数量超过剩余字符数量，则只截取实际存在的部分。

这样，C++17 新增的两个重载最终都复用了我们已经完成的 `append(const char*, size_t)`，原有的自引用处理、容量调整以及字符复制逻辑也得以保留。

接下来是 `push_back(char)`, 直接复用之前的`append(size_t, char)`即可

```cpp
void push_back(char c) {
    append(1, c);
}
```

同样的, 接下来的四个operator+=, 也直接复用 append 即可

```cpp
// 追加另一个 string 对象
    self& operator+=(const self& str) {
        return append(str);
    }

    // 追加 C 风格字符串
    self& operator+=(const char* str) {
        return append(str);
    }

    // 追加单个字符
    self& operator+=(char c) {
        return append(1, c);
    }

    // 追加初始化列表中的字符
    self& operator+=(std::initializer_list<char> il) {
        return append(il);
    }
```

接下来我们写一下拷贝构造

```cpp
string(const self& obj) : string() {
    reserve(obj._size);
    _size = obj._size;
    std::memcpy(data(), obj.data(), obj._size);
    data()[_size] = '\0';
}
```

我们先以委托构造的方式获得一个干净的标准状态, 然后扩容到能承载对方的有效字符数目即可, 之后更新自己的成员 size和底层存储结构所存的有效字符, 为了让风格统一, 最后还是统一加上终止符

接下来是 swap

```cpp
 void swap(self& obj) noexcept {
        std::swap(_storage, obj._storage);
        std::swap(_size, obj._size);
        std::swap(_capacity, obj._capacity);
    }
```

这里就能看出我们采用联合体的好处, 我们也不需要具体区分到底采取哪种存储方式, 直接交换就可以了, 对于联合体的解释, 是依据 capacity 的, 并且 SSO 是个大小不变的缓冲区, 对他进行交换也不是很费力气, 如果是堆的话, 交换联合体也一并交换了.

接下来是复制重载

```cpp
self& operator=(const self& obj) {
        // 避免自赋值
        if (this == &obj) return *this;

        clear_content();

        //  确保容量充足，避免扩容时复制即将被覆盖的旧内容
        reserve(obj._size);

        // 复制有效字符
        std::memcpy(data(), obj.data(), obj._size);

        // 更新长度，统一补充终止符
        _size = obj._size;
        data()[_size] = '\0';

        return *this;
    }
```

对于复制重载来说, 一般首先要做的都是判断是否是自赋值, 尽管这种行为看起来很奇怪, 但不能称之为错误, 对于自赋值, 我们只要保持自身状态不变即可, 而对于其他情况, 我们先清除原先不需要的字符数据,然后再进行扩容, 避免扩容的时候把旧数据一块复制了, (这种思路遵循基本异常安全保证: 即使抛出异常, 对象仍旧是可以正常使用的, 但原先数据不保证还有), 然后再把该复制的复制过去. 不过另一种思路着眼于 严格异常安全保证, 该保证意味着, 如果扩容失败, 原有数据也不可丢失: 我们在进行扩容的时候, 可能会抛出异常, 比如什么长度溢出, 内存无法分配, 异常会沿着调用链跑到赋值重载的调用者那里, 如果提前清理, 对象只是能用, 但是原数据丢失, 如果要严格异常保证, 只需要删除清理代码, 然后改一下扩容注释.

对于赋值重载来说, 还存在一些别的更加省力的写法, 比如用拷贝构造以所引用的参数为原本, 实例化一个临时变量, 让自身与临时对象交换, 甚至是不使用对象, 故意让形参自动拷贝, 然后与形参交换, 从中选择一个即可, 多选会歧义

```cpp
self& operator=(const self& obj) {
    self temp(obj);
    swap(temp);
    return *this;
}

// 通过按值传参构造副本，再交换资源
self& operator=(self obj) {
    swap(obj);
    return *this;
}
```

接下来我们说插入, 相比 append 的单纯字引用, 插入还需要考虑原数据是否会变得不连续的问题

![](https://img.mdwind.online/img/20261108153701920.png)

```cpp
self& insert(size_t pos, const char* chars, size_t n) {
        // 检查插入位置
        if (pos > _size) throw std::out_of_range("string::insert: pos out of range");

        if (n == 0) return *this;

        // 检查插入后的容量是否溢出
        if (n > max_capacity - _size) throw std::length_error("string capacity overflow");

        // 通过地址区间判断是否存在自引用
        const auto begin_addr = reinterpret_cast<std::uintptr_t>(data());
        const auto source_addr = reinterpret_cast<std::uintptr_t>(chars);

        const bool self_reference = source_addr >= begin_addr && source_addr - begin_addr <= _size;

        // 如果存在自引用，记录源地址相对于当前字符串的偏移量
        const size_t offset = self_reference ? static_cast<size_t>(source_addr - begin_addr) : 0;

        // 确保具有足够的容量
        reserve(_size + n);

        // 将插入位置之后的有效字符整体右移
        std::memmove(data() + pos + n, data() + pos, _size - pos);

        // 利用两个视图描述需要复制的字符区域
        std::string_view a{};
        std::string_view b{};

        if (!self_reference) {
            // 外部字符数组，直接使用原始数据
            a = std::string_view(chars, n);
        } else if (offset + n <= pos) {
            // 源区域完全位于插入位置之前，不受尾部移动影响
            a = std::string_view(data() + offset, n);
        } else if (offset >= pos) {
            // 源区域整体向右移动了 n 个位置
            a = std::string_view(data() + offset + n, n);
        } else {
            // 插入位置将原来的源区域分成两段
            const size_t first_len = pos - offset;

            a = std::string_view(data() + offset, first_len);
            b = std::string_view(data() + pos + n, n - first_len);
        }

        // 将源字符复制到插入位置
        std::memcpy(data() + pos, a.data(), a.size());

        if (!b.empty()) std::memcpy(data() + pos + a.size(), b.data(), b.size());

        // 更新字符串长度，并统一添加终止符
        _size += n;
        data()[_size] = '\0';

        return *this;
    }
```

接下来我们去看其他插入

```cpp
self& insert(size_t pos, const self& str) {
        return insert(pos, str.data(), str.size());
    }

    self& insert(size_t pos, const self& str, size_t subpos, size_t sublen = npos) {
        // 检查子串开始位置
        if (subpos > str._size) throw std::out_of_range("string::insert: subpos out of range");

        // 根据剩余字符数量确定实际插入长度
        const size_t len = std::min(sublen, str._size - subpos);

        return insert(pos, str.data() + subpos, len);
    }

    self& insert(size_t pos, const char* str) {
        return insert(pos, str, std::strlen(str));
    }

    self& insert(size_t pos, size_t n, char c) {
        // 检查插入位置
        if (pos > _size) throw std::out_of_range("string::insert: pos out of range");

        if (n == 0) return *this;

        // 检查插入后的容量是否溢出
        if (n > max_capacity - _size) throw std::length_error("string capacity overflow");

        reserve(_size + n);

        // 将插入位置之后的有效字符整体右移
        std::memmove(data() + pos + n, data() + pos, _size - pos);

        // 将 n 个字符 c 填充到插入起始位置
        std::fill_n(data() + pos, n, c);

        _size += n;
        data()[_size] = '\0';

        return *this;
    }
    
 // 插入整个字符串视图
    template <class StringViewLike>
        requires(std::convertible_to<const StringViewLike&, std::string_view> &&
                 !std::convertible_to<const StringViewLike&, const char*>)
    self& insert(size_t pos, const StringViewLike& t) {
        std::string_view view = t;
        return insert(pos, view.data(), view.size());
    }

    // 插入字符串视图中的指定部分
    template <class StringViewLike>
        requires(std::convertible_to<const StringViewLike&, std::string_view> &&
                 !std::convertible_to<const StringViewLike&, const char*>)
    self& insert(size_t pos, const StringViewLike& t, size_t subpos, size_t sublen = npos) {
        std::string_view view = t;
        std::string_view subview = view.substr(subpos, sublen);

        return insert(pos, subview.data(), subview.size());
    }
```

要么复用之前的字符数组版本, 要么逻辑较为简单

我们再看用一批迭代器的

```cpp
iterator insert(const_iterator p, size_t n, char c) {
        size_t pos = static_cast<size_t>(p - cbegin());

        insert(pos, n, c);

        return data() + pos;
    }

    iterator insert(const_iterator p, char c) {
        return insert(p, 1, c);
    }

    template <std::input_iterator InputIterator>
    iterator insert(const_iterator p, InputIterator first, InputIterator last) {
        size_t pos = static_cast<size_t>(p - cbegin());
        string tmp(first, last);
        insert(pos, tmp);
        return data() + pos;
    }

    iterator insert(const_iterator p, std::initializer_list<char> il) {
        size_t pos = static_cast<size_t>(p - cbegin());
        insert(pos, il.begin(), il.size());
        return data() + pos;
    }
```

迭代器的问题是, 有时他可能是不可靠的, 所以我们需要转回以前偏移量 pos 的模样, 他们所返回的迭代器和插入时的迭代器具有相同的逻辑位置, 可以对原有的迭代器进行更新.

接下来是 erase

```cpp
 // 从指定位置开始，删除最多 count 个字符
    self& erase(size_t pos = 0, size_t count = npos) {
        // 检查删除位置
        if (pos > _size) throw std::out_of_range("string::erase: pos out of range");

        // 确定实际删除的字符数量
        size_t len = std::min(count, _size - pos);

        // 将删除区间之后的有效字符向前移动
        std::memmove(data() + pos, data() + pos + len, _size - pos - len);

        // 更新长度，统一补充终止符
        _size -= len;
        data()[_size] = '\0';

        return *this;
    }

    // 删除迭代器指向的单个字符
    iterator erase(const_iterator p) {
        size_t pos = static_cast<size_t>(p - cbegin());

        erase(pos, 1);

        return data() + pos;
    }

    // 删除指定迭代器区间内的字符
    iterator erase(const_iterator first, const_iterator last) {
        size_t pos = static_cast<size_t>(first - cbegin());
        size_t len = static_cast<size_t>(last - first);

        erase(pos, len);

        return data() + pos;
    }
```

相比插入, 逻辑简单了不少, 所返回迭代器的含义和插入也是相同的

resize

```cpp
void resize(size_t n, char c = '\0') {
        reserve(n);
        for (size_t i = _size; i < n; i++) {
            data()[i] = c;
        }
        data()[n] = '\0';
        _size = n;
    }
```

接下来我们说 find, 为了节约时间, 这里 find 就用 朴素算法就行了, 我们就不详细介绍 KMP 了, 不过我之前好像写过 C 接口的 KMP [链接](https://blog.csdn.net/venti0411/article/details/166736100?spm=1011.2415.3001.5331), 我们目前直接用朴素算法理解就行, 朴素算法逻辑也很直观

```cpp
 // 朴素匹配：逐一尝试可能的匹配起点
    size_t naive_find(const char* chars, size_t pos, size_t n) const noexcept {
        // 检查起始位置
        if (pos > _size) return npos;

        // 空模式串在合法起点直接匹配成功
        if (n == 0) return pos;

        // 剩余字符不足以容纳模式串
        if (n > _size - pos) return npos;

        // 遍历所有可能的匹配起点
        for (size_t i = pos; i <= _size - n; ++i) {
            if (std::memcmp(data() + i, chars, n) == 0) return i;
        }

        return npos;
    }

    // KMP 匹配：利用 LPS 表减少重复比较
    size_t kmp_find(const char* chars, size_t pos, size_t n) const {
        // 检查搜索范围
        if (pos > _size) return npos;
        if (n == 0) return pos;
        if (n > _size - pos) return npos;

        // 构造 LPS 表，记录各前缀的最长相等真前后缀长度
        std::vector<size_t> lps(n, 0);

        for (size_t i = 1, matched = 0; i < n;) {
            if (chars[i] == chars[matched]) {
                lps[i++] = ++matched;
            } else if (matched != 0) {
                // 根据已经匹配的信息回退
                matched = lps[matched - 1];
            } else {
                lps[i++] = 0;
            }
        }

        // 正式进行 KMP 匹配
        size_t i = pos;
        size_t j = 0;

        while (i < _size) {
            if (data()[i] == chars[j]) {
                ++i;
                ++j;

                // 完整匹配，返回相对于整个字符串的起始下标
                if (j == n) return i - n;
            } else if (j != 0) {
                // 主串位置保持不变，只调整模式串位置
                j = lps[j - 1];
            } else {
                ++i;
            }
        }

        return npos;
    }
    
// 查找另一个 string 对象
    size_t find(const self& str, size_t pos = 0) const noexcept {
        return naive_find(str.data(), pos, str.size());
    }

    // 查找字符数组中的指定数量的字符
    size_t find(const char* chars, size_t pos, size_t n) const {
        return naive_find(chars, pos, n);
    }

    // 查找 C 风格字符串
    size_t find(const char* str, size_t pos = 0) const {
        return find(str, pos, std::strlen(str));
    }

    // 查找单个字符
    size_t find(char c, size_t pos = 0) const noexcept {
        return naive_find(&c, pos, 1);
    }

    // 查找能够转换为字符串视图的字符序列
    template <class StringViewLike>
        requires(std::convertible_to<const StringViewLike&, std::string_view> &&
                 !std::convertible_to<const StringViewLike&, const char*>)
    size_t find(const StringViewLike& t, size_t pos = 0) const {
        std::string_view view = t;
        return naive_find(view.data(), pos, view.size());
    
```

最后一个 find 我选择性去除了一些东西

![](https://img.mdwind.online/img/20261108175539259.png)

接下来是 substr, 我们直接使用迭代器构造, 然后返回

```cpp
// 返回从 pos 开始、最多包含 count 个字符的新字符串
    self substr(size_t pos = 0, size_t count = npos) const {
        // 检查子串起始位置
        if (pos > _size) throw std::out_of_range("string::substr: pos out of range");

        // 确定实际截取长度
        const size_t len = std::min(count, _size - pos);

        // 利用迭代器区间构造新字符串
        return self(cbegin() + pos, cbegin() + pos + len);
    }
```

接下来我们看非成员函数, 首先是各类对于关系运算符的重载, 也就是什么大于, 小于, 等于, 或者掺在一起的那种

不过在此之前我们要想说个概念 (下面对于三种比较顺序的说明, 其渲染是存在问题, 你需要使用 github 支持的版本)

C++20 引入了三路比较运算符 `<=>`，通过不同的比较类别描述数据之间的顺序关系。其中最主要的三种类别分别是强序（`std::strong_ordering`）、弱序（`std::weak_ordering`）和偏序（`std::partial_ordering`）。

理解这三种比较类别，可以从两个角度出发：当两个数据被判定为相等或等价时，它们能否相互替换而不影响比较结果；任意两个数据之间，是否都能确定大小关系。

这里我们只考虑数据所承载的信息，不讨论它们的内存地址或存储位置。

### 1. 强序（`std::strong_ordering`）

强序要求任意两个参与比较的数据，必然满足以下三种关系之一：

\[
a<b,\qquad a=b,\qquad a>b
\]

这三种关系互斥，并且有且只有一种成立。

强序的关键在于相等关系的语义。

当两个数据被判定为相等时，它们应当具有可替换性（Substitutability）。也就是说，在相关比较操作中，用其中一个数据替换另一个，不会改变原有的比较结果。

例如，我们定义三个字符串：

```
std::string Hello1 = "Hello";
std::string Hello2 = "Hello";
std::string World  = "World";
```

采用区分大小写的字典序比较，`Hello1` 和 `Hello2` 相等。

现在分别将它们与 `World` 进行比较：

```
Hello1 < World   // true
Hello2 < World   // true

Hello1 > World   // false
Hello2 > World   // false

Hello1 == World  // false
Hello2 == World  // false
```

可以发现，无论使用 `<`、`>` 还是 `==`，将 `Hello1` 替换为 `Hello2`，都不会影响比较表达式返回的布尔值。

我们可以将这种性质形象地称为隐形替换：虽然参与比较的数据发生了替换，但相关比较操作无法察觉这种变化，其结果始终保持一致。

用数学语言表达，假设 \(a=b\)，对于相关比较操作 \(f\)，应当满足：

\[
f(a)=f(b)
\]

这里的 \(f\) 可以表示将数据与某个第三方数据进行比较并取得布尔结果的操作。

因此，强序中的相等具有较强的语义要求：两个相等的数据，在该比较体系所涉及的相关比较操作中应当具有可替换性。

### 2. 弱序（`std::weak_ordering`）

弱序同样要求任意两个参与比较的数据，必然满足以下三种关系之一：

\[
a<b,\qquad a\sim b,\qquad a>b
\]

其中，\(\sim\) 表示等价（Equivalent）。

与强序相比，弱序放宽了对相等性的要求：两个数据即使存在某些可观察的差异，也可以被当前排序规则判定为等价。

例如，我们定义三个字符串：

```
std::string Hello1 = "Hello";
std::string Hello2 = "hello";
std::string World  = "World";
```

现在约定两种比较操作：

- 排序比较：忽略字母大小写。

- 内容相等比较：区分字母大小写。

在第一种比较规则下，`Hello1` 与 `Hello2` 等价。

分别与 `World` 进行排序比较：

```
// 以下假设使用不区分大小写的排序比较

Hello1 < World   // true
Hello2 < World   // true

Hello1 > World   // false
Hello2 > World   // false
```

可以发现，在当前排序规则下，无论使用 `Hello1` 还是 `Hello2`，比较结果都是相同的。

也就是说，弱序同样具有一定的可替换性。

但是，如果我们改用区分大小写的内容相等比较：

```
// 以下使用区分大小写的内容相等比较

Hello1 == "Hello"  // true
Hello2 == "Hello"  // false
```

替换前后的比较结果便发生了变化。

这说明，`Hello1` 和 `Hello2` 虽然在原先的排序规则下等价，但这种等价关系无法保证它们在其他比较操作中仍然可以实现隐形替换。

这里需要区分两个概念：原先的排序规则并没有出现逻辑矛盾，它仍然是自洽的。只是当我们引入另一种能够观察到更多数据差异的比较操作时，原先的等价关系不足以保证替换结果不变。

因此，弱序的特点可以概括为：

弱序保证等价数据在当前排序规则下具有相同的排序地位，但允许它们在其他相关比较操作中表现出差异。

这与强序形成了区别：强序中的相等承诺了更强的可替换性，而弱序中的等价只承诺当前排序关系所需要的可替换性。

需要说明的是，以上两种比较操作使用了不同的规则。示例展示的是比较关系的设计，并非 `std::string` 标准比较运算符的实际行为。强序的可替换性也应限定在相关比较操作中，不能无限推广到任意能够检查数据内容的操作。

### 3. 偏序（`std::partial_ordering`）

偏序进一步放宽了对比较关系的要求。

强序和弱序虽然对相等性的要求不同，但都要求任意两个数据之间能够确定顺序关系。

偏序则允许出现第四种结果：

\[
a<b,\qquad a\sim b,\qquad a>b,\qquad \text{unordered}
\]

其中，`unordered` 表示无序，即两个数据之间无法按照当前比较规则确定小于、等价或大于关系。

例如，浮点数中的 `NaN`（非数字）就具有这种性质：

```
#include <compare>
#include <limits>

double a = 10.0;
double b = std::numeric_limits<double>::quiet_NaN();

auto result = a <=> b;
// std::partial_ordering::unordered
```

分别检查三种常见关系：

```
a < b   // false
a == b  // false
a > b   // false
```

可以发现，三种关系全部不成立。

这与强序、弱序明显不同。对于它们而言，任意两个数据之间必然有一种顺序关系成立；而偏序允许出现无法比较的情况。

因此，偏序中的无序意味着现有比较规则无法为某些数据建立大小或等价关系。

无序并不意味着比较规则存在矛盾。例如，`NaN` 的比较行为就是浮点数比较语义的一部分。

此外，偏序中的等价也不要求具有强序的可替换性。

### 4. 三种比较类别的关系

| 比较类别 | 比较结果               | 相等或等价时的可替换性                       |
| -------- | ---------------------- | -------------------------------------------- |
| 强序     | 小于、等于、大于       | 在相关比较操作中具有强可替换性               |
| 弱序     | 小于、等价、大于       | 保持当前排序关系，其他比较操作可能观察到差异 |
| 偏序     | 小于、等价、大于、无序 | 允许某些数据无法比较，等价也不要求强可替换性 |

从强序到弱序，再到偏序，可以理解为比较规则所作承诺的逐步减少：

强序 → 弱序： 放宽相等性的要求。允许两个存在可观察差异的数据被视为等价，但仍然保证所有数据都能确定顺序关系。

弱序 → 偏序： 进一步放宽可比较性的要求。允许某些数据之间不存在确定的大小或等价关系。

强序

大小关系明确，相等具有强可替换性

弱序

大小关系明确，允许不同数据等价

偏序

进一步允许某些数据之间无法比较

最后还有一个数学性质需要明确：三种比较类别都必须满足各自要求的一致性与传递性。强序和弱序的区别，并不是前者自洽而后者可能自相矛盾。

实际上，弱序的等价关系同样具有传递性。如果 \(a\sim b\)、\(b\sim c\)，那么必然有 \(a\sim c\)。偏序中已建立的等价关系也满足传递性。

因此，三种比较类别真正的层次差别在于：相等或等价究竟承诺了多大范围的可替换性，以及比较规则是否允许两个数据之间完全无法确定顺序关系。

对于正在实现的字符串类，按照字符内容进行区分大小写的字典序比较，通常能够建立强序关系，因此使用 `std::strong_ordering` 是合适的。

我们先写一个私有的统一比较函数, 该函数先在双方都具有的逻辑位置上使用 memcmp 进行比较, 如果他们在那里是完全相同的, 那么再依据长短来判断大小

```cpp
// 按字典序比较两个字符串
    int compare(const self& obj) const noexcept {
        // 先比较双方共同具有的字符
        const size_t len = std::min(_size, obj._size);

        int result = std::memcmp(data(), obj.data(), len);

        if (result != 0) return result;

        // 公共部分相同，长度较短的字符串更小
        if (_size < obj._size) return -1;
        if (_size > obj._size) return 1;

        return 0;
    }
```

之后我们就要写各种关系运算符的重载函数了, 就像文档上提供的接口

![](https://img.mdwind.online/img/20261108204426683.png)

但进入 C++20 之后, 我们其实有更方便的方式来实现这些接口

```cpp
// 判断两个字符串是否相等
    bool operator==(const self& obj) const noexcept {
        return _size == obj._size && std::memcmp(data(), obj.data(), _size) == 0;
    }

    // 三路比较
      std::strong_ordering operator<=>(const self& obj) const noexcept {
        return compare(obj) <=> 0;
    }
```

我们重点说一下这个三路比较函数, 首先是三路运算符(<=>), 因为其形状又称"太空船运算法", 他会返回一个比较类型值, 而我们在前面已经说过, std::strong_ordering, 是一种表示强序的比较类型, 在我们的定义中, 返回的是一个 int 类型, 对于两个 int 之间的相互比较, 是一种强序关系, 所以我们用  std::strong_ordering 接收完全没有问题, 不过其实也可以使用弱序或者偏序接收也没有什么大问题, 因为他们存在当先的隐式转换关系, 强序可以变成弱序或者偏序, 弱序可以变成偏序, 偏序就只能是偏序了, 所以对于两个浮点数进行比较, 不能用强序或者弱序来接收, 两个浮点数比较是可以出现无法确认大小的情况的, 这在前面我们也说过

在强序类型中, 存在四个命名常量, 他们分别是 

```
// 其中 equal == equivalent
std::strong_ordering::less
std::strong_ordering::equal
std::strong_ordering::equivalent
std::strong_ordering::greater
```

但实际上只有三种, 强序里面的等价, 说的其实就是相等, 特意在强序里面加个等价是为了好进行泛型编程(C++中的具体方式是模板), 避免要写特例判断

但是到这一步, 我们仅仅是完成了 string 关于 三路操作符本身的重载, 那这个重载是如何平替<,>,<=,>=,!=的呢?为了说这一点, 我们需要知道, 这些比较类型自己类比还有一些特殊的关系运算符重载函数, operator< operator>,operator<=, operator>=, operator!=..说是特殊, 是因为他们的第二个操作数必须是0, 他们的返回值表如下

| 比较结果  | `< 0` | `<= 0` | `== 0` | `!= 0` | `>= 0` | `> 0` |
| --------- | ----- | ------ | ------ | ------ | ------ | ----- |
| `less`    | true  | true   | false  | true   | false  | false |
| `equal`   | false | true   | true   | false  | true   | false |
| `greater` | false | false  | false  | true   | true   | true  |

而编译器会对我们平常写的 a < b 等关系运算进行修改, 变成 ((a<=>b) < 0)的形式, 里边括号返回比较类型, 比较类型调用自己的重载, 于是外边就得到了一个布尔值, 从而在功能上对原先的一堆接口在功能上进行平替.

另外, 我们还可以看到这个三路运算符重载是写在成员函数里面的, 而非之前那张图的非成员函数上, 这是因为三路运算符真正面向用户的不是他本身的这个签名, 而是编译器自己对缘由比较的修改, 如果是传统写法, 

```
s < "Hello";可行但是"Hello" < s;不可行, 但是对于三路实现的, 编译器会把后者变成((s <=> "Hello") > 0), 他对不同类型参与比较时的对称性进行了优化
```

接下来我们去写两个流操作符重载, 首先来看 <<, 我们先看如下的代码设计思路和流程图

![](https://img.mdwind.online/img/20261109172235589.png)

我们需要对其中的一些知识介绍一下再写代码

首先我们需要了解 C++ IO 流中的字段宽度`width`设计

同一个 `width()` 设置，在输入和输出时承担不同的职责。

| 操作            | `width()` 的含义   |
| --------------- | ------------------ |
| 字符串输入 `>>` | 最多提取多少个字符 |
| 字符串输出 `<<` | 输出字段的最小宽度 |

对于输入操作来说, 他是指在遇到所谓空白字符或者读出错之前设置的读取最多字符数目的参数. 比如对于字符串"Hello World!", 如果我们去读的话, 如果一切正常不出错, 理论上会把`Hello`读进入, 但是如果我就是有特殊要求, 我就是想, 就读三个字符呢? 此时我们就可以通过对输入流对象进行设置, 从而实现这一点,`in.width(3)`, 不过这种方式之后还要`in.width(0)`把状态进行恢复, 参数为0的时候不做限制, 读到空白字符为止.

或者还有一种一次性方法, 不用事后恢复`width`

```cpp
#include <iomanip>

std::cin >> std::setw(3) >> str;
```

而对于流输出来说, 则是另一种要求, 还是拿`Hello`举例子, 如果流输出的字段宽度定为8, 那么在默认左对齐的情况下, 会输出`   Hello`, 也就是左边有3个空格, 我记得还可以指定字符, 不用空格, 但这里就不说了, 不过如果我们把字段宽度设置为3, 输出的就是`Hello`, 不会把单词给截断.

接下来我们看`sentry`, 他是`std::istream`中的一个辅助类, 提供在正式开始流操作之前的准备工作, 以构造函数的形式, 所以后面我们在代码里面看到, 以`istream`为参数构造了一个`sentry`, 在其构造函数中, 会完成以下工作

1. 检查输入流是否已经处于错误状态
2. 如果输入流关联了输出流，必要时刷新关联的输出流
3. 如果允许跳过前导空白，就不断提取并丢弃空白字符，直到遇到非空白字符
4. 记录准备工作是否成功，供后续输入逻辑判断

我们主要用的就是3和4, 让他跳过前导的空白字符, 以及在正式操作前再用4判断一下流对象的状态是否正常, 比如对于`    Hello`, 忽略前面的三个空格, 从`H`开始读

接下来我们要再说一个概念, 一般我们说的从缓冲区里面读字符, 有两个动作, 一个是读到这个字符, 另一个是把这个字符清理掉, 所以有时我们会用"读出"这个词, 出指的就是让这个字符在逻辑上不在缓冲区中.而对于流提取符来说, 默认是读到后面的空白字符后停止, 但不将其读**出**, 所以我们的逻辑是先看下一个字符是什么, 确认是真的有效字符后, 再真正地读出他.

```cpp
inline std::istream& operator>>(std::istream& in, string::self& str) {
    constexpr size_t BUFFER_SIZE = 16;

    char buff[BUFFER_SIZE];
    size_t curr = 0;
    size_t extracted = 0;

    // 获取本次输入的最大字符数量
    const auto width = in.width();
    const size_t limit = width > 0 ? static_cast<size_t>(width) : string::npos - 1;

    // 准备格式化输入，并根据 skipws 设置处理前导空白
    std::istream::sentry sentry(in);

    if (!sentry) {
        in.width(0);
        return in;
    }

    // 开始读取前清空原有字符串，保留存储容量
    str.clear();

    while (extracted < limit) {
        // 查看下一个字符，但不从输入流中提取
        int ch = in.peek();

        // 输入结束或流读取失败
        if (ch == std::char_traits<char>::eof()) break;

        // 遇到空白字符，停止读取并将其保留在输入流中
        if (std::isspace(static_cast<char>(ch), in.getloc())) break;

        // 正式提取字符
        ch = in.get();

        if (ch == std::char_traits<char>::eof()) break;

        buff[curr++] = static_cast<char>(ch);
        ++extracted;

        // 缓冲区已满，将数据提交给字符串
        if (curr == BUFFER_SIZE) {
            str.append(buff, curr);
            curr = 0;
        }
    }

    // 提交缓冲区中剩余的字符
    if (curr != 0) str.append(buff, curr);

    // 恢复流宽度设置
    in.width(0);

    // 本次没有提取任何字符，标记输入失败
    if (extracted == 0) in.setstate(std::ios::failbit);

    return in;
}
```

变量`curr`, 表示下一个有效字符应该放在缓冲区那个下标未知, `extracted`表示当前读到的有效字符个数: 一方面是因为, 标准IO流规定什么东西都读不到需要为流对象设置错误状态, 也就是`in.setstate(std::ios::failbit);`,另一方面要为可能的字宽设置做准备, 再已经读到足够字符的情况下跳出循环, 之后我们主动读一下流对象的字宽长度, 这个字宽长度可能是默认的`0`, 也有可能之前被用户设置过, 如果已经被设置过, 那我们就使用这个设置值, 作为最多接收的有效字符个数,如果没有被设置, 我们就将其设置为`string`本身理论上能存储的最大字符数目, 表示通过读到后置的空白字符这种方式跳出循环, 随后, 我们通过`sentry`内部的布尔重载函数查看流对象的准备操作是否成功, 不成功我们就恢复流对象的默认字宽, 主动返回, 否则, 进入正式的主逻辑,  

在循环开始之前, 我们先清理对象原有的字符数据, 进入循环后, 先查看下一个字符是什么, 有没有读失败, 是不是空白字符, 有就视为输入结束, 主动退出循环,, 将有效字符读出并写入我们的缓冲区,缓冲区满了进行刷新, 退出循环后, 再清理可能存在的缓冲区中残留数据.这里如何判断是否为空白字符的稍微复杂一些, 第一个参数就是将要读出的下一个字符, 这里强转是为了避免命中错误的重载版本, 第二个参数可以获取当前流对象中真正使用的各种参数设置, 其中的一部分就是描述什么字符被视为空白字符, 这就为上层调整空白字符分类提供了可能--这还是一个紧密嵌入 C++ IO 流设计的一种方式, 你当然可以直接进行判断, 但这样的话, 上层就不能自行调整了.

另外, 由于是再写类外的, 而我们又是再 hpp 写这东西的, 所以最后再加上一个内联

相比之下, 流输出更加简单, 我们只需要在意对齐方式和字宽长度即可, 左对齐, 就先写入有效字符, 再填充字符, 有对齐, 顺序反过来, 我们可以通过`fill()`获得默认的或者用户自己设置的填充字符, 其中唯一可能需要注意的是 lambda 表达式, 那是C++从别的语言那里引进的一种代码复用机制, 可以先把逻辑包装成一个方法对象, 然后需要使用的时候直接进行调用, 本来我是打算后面说的, 但稍微用一下也不是不可以, 这里我们直接把那段 for 循环放到那两个调用的地方看待就行了

```cpp
inline std::ostream& operator<<(std::ostream& out, const string::self& str) {
    // 获取当前字段宽度和字符串长度
    const auto width = out.width();
    const auto length = str.size();

    // 计算填充字符数量
    const size_t padding =
        width > 0 && static_cast<size_t>(width) > length ? static_cast<size_t>(width) - length : 0;

    // 检查是否为左对齐
    const bool left = (out.flags() & std::ios_base::adjustfield) == std::ios_base::left;

    // 获取填充字符
    const char fill = out.fill();

    // 清除本次格式化输出的字段宽度
    out.width(0);

    // 填充指定数量的字符
    auto write_padding = [&]() {
        for (size_t i = 0; i < padding && out; ++i) out.put(fill);
    };

    // 默认右对齐：先填充
    if (!left) write_padding();

    // 输出字符串的完整字符序列
    if (out && length != 0) out.write(str.data(), static_cast<std::streamsize>(length));

    // 左对齐：后填充
    if (left && out) write_padding();

    return out;
}
```

最后我们看一下 `getline`, 与普通的 << 相比, 他有一些区别: 看名字我们就知道, 这是读出一行, 所以在这里我们不考虑字段宽度, 当然, 如果读出 EOF, 那我们还是要停止读的; 另一个方面是他不跳过前导的空白字符了, 这些空白字符也被视为有效字符的一部分, 对于换行符来说, 我们会将其从IO缓冲区中读出, 也把他视为有效字符(如果我们一个有效字符也读不到还是要想之前那样末尾设置错误状态), 但是我们不把他放到应用层的缓冲区里面

另一个需要注意的点, 是, 我本来打算和上面的 operator<< 一样, 也设置一个理论存储最多字符数目, 但是我将这个设计抛弃了, 因为我想强调的是, 这仅仅是一个参考的理论最大值, 实际上是很难命中循环条件`extracted < limit`的(设置为最大理论值的情况下), 我们上面那样写, 是因为他形式上更加美观, 逻辑上更加清晰, 在此处, 我故意对比, 让循环条件恒为真, 只依靠读出换行或者错误之后退出循环

最后要说的是, 分隔符默认选择换行, 但也可以自行更换, 下面我们把用缺省形式实现

```cpp
inline std::istream& getline(std::istream& in, string& str, char delim = '\n') {
    constexpr size_t BUFFER_SIZE = 16;

    // 不跳过前导空白
    std::istream::sentry sentry(in, true);
    if (!sentry) return in;

    char buff[BUFFER_SIZE];
    size_t curr = 0;
    bool extracted = false;

    str.clear();

    while (true) {
        // 观察下一个字符
        int ch = in.peek();
        if (ch == std::char_traits<char>::eof()) break;

        // 提取字符
        ch = in.get();
        if (ch == std::char_traits<char>::eof()) break;

        extracted = true;

        // 分隔符被提取，但不保存
        if (static_cast<char>(ch) == delim) break;

        buff[curr++] = static_cast<char>(ch);

        if (curr == BUFFER_SIZE) {
            str.append(buff, curr);
            curr = 0;
        }
    }

    // 提交剩余字符
    if (curr != 0) str.append(buff, curr);

    // 没有成功提取任何字符
    if (!extracted) in.setstate(std::ios::failbit);

    return in;
}
```

你好(这是占位符)
:::

```cpp
wind::string::string(const char* str)
	:_str(nullptr)
	,_size(strlen(str))
	,_capacity(_size)
{
	// 注意，_capacity指的是可以容纳的有效字符个数
	// 它与开辟空间的大小不是同一概念
	// 为了兼容C语言，开辟空间的最后一个字符必须是'\0'
	// 而char* str身为C中的字符串最后一位就是'\0'
	// 所以_capacity的初始化是就是char* str的长度

	_str = new char[_capacity + 1];
	// 留一个成员空间，用来放`\0`

	strcpy(_str, str);
	// 严格来说，应该用memcpy，但既然确定
	// 不使用模版而使用char来写
	// 那就用C中的字符串相关函数
}

/*
// 因为初始化列表的初始化顺序是按照声明来写的
// 所以会先执行_str(new char[_capacity + 1])
// 但此时_size还未被定义
// 从而引发错误
wind::string::string(const char* str)
	:_size(strlen(str))
	,_capacity(_size + 1)
	,_str(new char[_capacity + 1])
{
	// 略
}
*/
```

### ~string()

```cpp
// 这真的没什么好说的
wind::string::~string()
{
	delete[] _str;
	_str = nullptr;
	_size = _capacity = 0;
}
```

### string()

```cpp
wind::string::string()
	:_str(new char[1] {0})
	,_size(0)
	,_capacity(0)
{
	// C语言规定字符串的最后一位是'\0'
	// 这对空字符串仍然使用，所以要再
	// 开辟一个成员空间存放'\0'
	
	// 前面说过，我们的STL是SGI版本的
	// 之前我们试过，P.J.版本的string
	// 无参构造是会开辟多个空间的
	// 很明显打印P.J.版本的空string
	// 对象是不会打印出任何东西的
	// 所以个人猜测P.J.版本的空string
	// 对象最起码开头也要上道保险性质的'\0'
	// 防止打印出其它内容
}
```

可以把`string(const char* str)`和`string()`使用缺省值进行合并，`string(const char* str = "")`，由于C语言规定常量字符串必须以`\0`结尾，所以空字符串`""`其实并不完全空，后面还有一个`\0`，但这里就不合并了，因为合并之后会让文章逻辑不够顺畅。而且我还要重新排版。

### size_t size()const

```cpp
size_t wind::string::size()const
{
	return _size;
}
```

### size_t capacity()const

```cpp
size_t wind::string::capacity()const
{
	return _capacity;
}
```

### operator[]

```cpp
char& wind::string::operator[](size_t pos)
{
	assert(pos < _size);
	return _str[pos];
}

const char& wind::string::operator[](size_t pos)const
{
	assert(pos < _size);
	return _str[pos];
}
```

### iterator

```cpp
namespace wind
{
	class string
	{
	public:
		typedef char* iterator;
		typedef const char* const_iterator;
		iterator begin();
		iterator end();
		const_iterator begin()const;
		const_iterator end()const;
		string(const char* str);
		string();
		~string();
		char& operator[](size_t pos);
		const char& operator[](size_t pos)const;
		size_t size()const;
		size_t capacity()const;
	private:
		char* _str;
		size_t _size;
		size_t _capacity;
	};
}

wind::string::iterator wind::string::begin()
{
	return _str;
}

wind::string::iterator wind::string::end()
{
	return _str + _size;
}

wind::string::const_iterator wind::string::begin()const
{
	return _str;
}

wind::string::const_iterator wind::string::end()const
{
	return _str + _size;
}
```

### reserve

```cpp
void wind::string::reserve(size_t n)
{
	// 以前试过的，对于小于当前容量的参数
	// SGI和P.J.函数都不作处理
	if (n > _capacity)
	{
		// 注意，_capacity指的是可容纳的有效数据个数
		// 不是开辟空间的成员个数，要额外加一存'\0'

		// C++没原地扩容
		// 所以就new出来一个新空间
		// 然后再从原空间里拷贝内容

		auto p = new char[n + 1];
		strcpy(p, _str);
		delete[] _str;
		_str = p;
		_capacity = n;
	}
}
```

### push_back

```cpp
void wind::string::push_back(const char ch)
{
	if (_size == _capacity)
	{
		reserve(_capacity * 2);
	}
	_str[_size++] = ch;
	_str[_size] = '\0';
}
```

### append

```cpp
void wind::string::push_back(const char ch)
{
	if (_size == _capacity)
	{
		// 为了防止_capacity初始值为0
		if (_capacity == 0)
		{
			reserve(1);
		}
		else
		{
			reserve(_capacity * 2);
		}
	}
	_str[_size++] = ch;
	_str[_size] = '\0';
}
```

### operator+=

```cpp
wind::string& wind::string::operator+=(const char ch)
{
	this->push_back(ch);
	return *this;
}

wind::string& wind::string::operator+=(const char* str)
{
	this->append(str);
	return *this;
}
```

### npos

这是第四个成员变量，它是一个静态无符号整型变量。我们前面说过，静态成员变量是类共用的，所以不会定义在初始化列表中，因此声明中不能给缺省值，理论上应该都定义在声明外，就像这样：

```cpp
// .h
namespace wind
{
	class string
	{
	public:
		typedef char* iterator;
		typedef const char* const_iterator;
		iterator begin();
		iterator end();
		const_iterator cbegin()const;
		const_iterator cend()const;
		string(const char* str);
		string();
		~string();
		void reserve(size_t n);
		char& operator[](size_t pos);
		string& operator+=(const char ch);
		string& operator+=(const char* str);
		const char& operator[](size_t pos)const;
		void push_back(const char ch);
		void append(const char* str);
		size_t size()const;
		size_t capacity()const;
		string& insert(size_t pos, const char* str);
		string& insert(size_t pos, const string& s);
		string& erase(size_t pos = 0, size_t len = npos);
	private:
		char* _str;
		size_t _size;
		size_t _capacity;
		const static size_t npos = -1;
	};
}


// .cpp
const size_t wind::string::npos = -1;
```

但C++标准委员会对静态整型成员变量开了一个特例：它可以在声明中给缺省值。之所以说是特例，是因为静态整型成员变量才能这样做，静态浮点型，静态字符型等都不能给声明缺省，而必须在声明外定义，之前不说这个，是因为这个特例是反逻辑的，会干扰我们的学习逻辑。

```cpp
char* _str;
size_t _size;
size_t _capacity;
const static size_t npos = -1;
```

### insert

```cpp
wind::string& wind::string::insert(size_t pos, const char* str)
{
	// 插入位置合法性检查
	assert(pos <= _size);
	size_t len = strlen(str);
	if (_size + len > _capacity)
	{
		reserve(_size + len);
	}
	size_t source = _size;
	size_t destination = _capacity;

	// 因为下标使用无符号整型
	// 所以很容易出现((size_t)-1) > ((size_t)others)

	// 强制类型转换或者把sour和dest用int类型也不行
	// 一是可能存在int溢出危险
	// 二是C++和C都有一个“算数转换”的说法：
	// 如果某个操作符的各个操作数属于不同的类型，那么
	// 除⾮其中⼀个操作数的转换为另⼀个操作数的类型
	// 否则操作就⽆法进⾏
	// 当int与size_t作比较时，int会被自动强转为size_t

	// 亦不能使用strcpy，因为待填充的空间可能与有限成员空间重叠
	while (source != 0 && source >= pos)
	{
		_str[destination--] = _str[source--];
	}
	// 退出循环，无非是两种情况：
	// source == 0：source已经处于临界值，再减就要变成最大值了
	// source < pos：不用再拷贝了
	if (source >= pos)
	{
		_str[destination--] = _str[source--];
	}
	// strcpy有'\0'，所以不能用
	memcpy(_str + pos, str, strlen(str));


	_size += len;

	return *this;
}

wind::string& wind::string::insert(size_t pos, const string& s)
{
	this->insert(pos, s._str);
	return *this;
}

wind::string& wind::string::insert(size_t pos, const char ch)
{
	assert(pos <= _size);
	if (_size == _capacity)
	{
		if (_capacity == 0)
		{
			reserve(1);
		}
		else
		{
			reserve(_capacity * 2);
		}
	}
	size_t source = _size;
	size_t destination = source + 1;
	while (source != 0 && source >= pos)
	{
		_str[destination--] = _str[source--];
	}
	if (source >= pos)
	{
		_str[destination--] = _str[source--];
	}
	_str[pos] = ch;
	_size++;
	return *this;
}
```

### relational

逻辑运算符在标准库中是以非成员函数的形式出现的，这是为了让运算符使用的更加灵活，第一个参数也可以不是对象，而是一个C中的字符串。

```cpp
const char* wind::string::c_str()
{
	return _str;
}

const char* wind::string::c_str()const
{
	return _str;
}

bool wind::operator>(const wind::string& s1, const wind::string& s2)
{
	// 模版当然不是这样写的，可能是以迭代器或者[]重载的形式
	// 一个个比较成员，但我们这里不是用模版的，所以就直接用
	if (strcmp(s1.c_str(), s2.c_str()) > 0)
		return true;
	else
		return false;
}

bool wind::operator>(const wind::string& s, const char* str)
{
	if (strcmp(s.c_str(), str) > 0)
		return true;
	else
		return false;
}

bool wind::operator>(const char* str, const string& s)
{
	if (strcmp(str, s.c_str()) > 0)
		return true;
	else
		return false;
}


bool wind::operator==(const wind::string& s1, const wind::string& s2)
{
	if (strcmp(s1.c_str(), s2.c_str()) == 0)
		return true;
	else
		return false;
}

bool wind::operator==(const wind::string& s, const char* str)
{
	if (strcmp(s.c_str(), str) == 0)
		return true;
	else
		return false;
}

bool wind::operator==(const char* str, const string& s)
{
	if (strcmp(str, s.c_str()) == 0)
		return true;
	else
		return false;
}


bool wind::operator<(const wind::string& s1, const wind::string& s2)
{
	if (s1 > s2 || s1 == s2)
		return false;
	else
		return true;
}

bool wind::operator<(const wind::string& s, const char* str)
{
	if (s > str || s == str)
		return false;
	else
		return true;
}

bool wind::operator<(const char* str, const string& s)
{
	if (str > s || str == str)
		return false;
	else
		return true;
}
// 其它就先不写了
```

### IO

在C++中，为了对多个对象进行流提取，会像C那样，把'\0'和'\n'默认为间隔符而不被读取，此时就要用`istream`的成员函数`get`，`get`会返回不加处理的原字符，同时，也支持指定某个字符为间隔符，获得一个字符串。

```cpp
std::ostream& wind::operator<<(std::ostream& out, const string& s)
{
	for (auto ch : s)
	{
		out << ch;
	}
	return out;
}

std::istream& wind::operator>>(std::istream& in, string& s)
{
	s.clear();
	// 为了区分多个对象的流提取
	// C++或者C默认以空格和换行为分隔符
	// 但这也为包含空格字符串的提取
	// 造成了困难，istream中的成员
	// 函数get可以自定义分隔符


	//// 空格和换行会被默认为分隔符
	//// 所以不会被提取
	//// 这会使得程序进入死循环
	//char ch;
	//in >> ch;
	//while (ch != ' ' && ch != '\n')
	//{
	//	s += ch;
	//}

	
	/*
	char ch;
	ch = in.get();
	while (ch != ' ' && ch != '\n')
	{
		s += ch;
	}
	这种写法虽然可行
	但扩容频繁效率较低
	*/

	// 字符缓冲区
	char buff[16];
	int curr = 0;
	char tmp;
	do
	{
		// 字符先存储入缓冲区
		tmp = in.get();
		buff[curr++] = tmp;

		// 当缓冲区满后
		// 一次性存入
		if (curr == 15)
		{
			buff[curr] = '\0';
			curr = 0;
			s += buff;
		}
	}while (tmp != ' ' && tmp != '\n');

	// 跳出循环，说明上一个位是
	// 终止位，将其改为'\0'
	buff[curr - 1] = '\0';
	s += buff;

	return in;
}

wind::string& wind::string::get(char delim, std::istream& in)
{
	char buff[16];
	int curr = 0;
	char tmp;
	do
	{
		tmp = in.get();
		buff[curr++] = tmp;

		if (curr == 15)
		{
			buff[curr] = '\0';
			curr = 0;
			*this += buff;
		}
	} while (tmp != delim);

	buff[curr - 1] = '\0';
	*this += buff;

	return *this;
}
```

![image-20241018132134218](https://img.mdwind.online/md/202410181321367.png)

```cpp
int main()
{
	std::string s;
	// 输入"hello string"
	std::cin >> s;
	// 只会提取"hello"
	// "string"还留在缓冲区
	std::cout << s;
	return 0;
}
```

![image-20241018132034411](https://img.mdwind.online/md/202410181320680.png)

### erase

```cpp
wind::string& wind::string::erase(size_t pos, size_t len)
{
	// 位置检查
	assert(pos < _size);
	// begin和end控制挪动的起始
	// 默认len不会超出有效区域
	size_t begin = pos + len;

	// len已经超出有效区域
	// 数据需要进行修正
	if (len == npos || pos + len >= _size)
	{
		// 修正起始位置
		begin = _size;
		// 修正丢弃字符个数
		len = begin - pos;
	}

	// end就是原终止位
	size_t end = _size;
	// 调整有效字符个数
	_size = _size - len;
	// 挪动未丢弃字符部分
	while (begin < end)
	{
		_str[pos++] = _str[begin++];
	}
	// 添加终止位
	_str[pos] = '\0';
	return *this;
}
```

### resize

```cpp
void wind::string::resize(size_t len, char holder)
{
	// 保证空间足够
	reserve(len);
	// 设置填充起始位置
	size_t begin = _size;
	// 修正有效字符个数
	_size = len;
	// 末尾添加终止符
	_str[_size] = '\0';

	// 填充开始
	while (begin < _size)
	{
		_str[begin++] = holder;
	}
}
```

### find

```cpp
size_t wind::string::find(const char ch, size_t pos)const
{
	assert(pos < _size);
	size_t goal = npos;
	size_t begin;
	for(begin = pos; begin < _size; begin++)
	{
		if(_str[begin] == ch)
		{
			goal = begin;
			break;
		}
	}
	return goal;
}

size_t wind::string::find(const char* str, size_t pos)const
{
	assert(pos < _size);
	size_t goal = npos;
	const char* p = strstr(_str + pos, str);
	if (p)
	{
		goal = (size_t)(p - _str);
	}
	return goal;
}

size_t wind::string::find(const wind::string& s, size_t pos)const
{
	assert(pos < _size);
	return find(_str, pos);
}
```

### swap

```cpp
void wind::string::swap(string& s)
{
	std::swap(_str, s._str);
	std::swap(_size, s._size);
	std::swap(_capacity, s._capacity);
}
```

### string

```cpp
//// 古典主义写法
//wind::string::string(const string& s)
//	:_str(new char[s._capacity + 1])
//	, _size(s._size)
//	, _capacity(s._capacity)
//{
//	strcpy(_str, s._str);
//}

// 现代主义写法
wind::string::string(const string& s)
	:_str(nullptr)
	, _size(0)
	, _capacity(0)
{
	string tmp(s._str);

	// this->swap(tmp);
	// 省略this->也行
	swap(tmp);
}
```

古典的写法就是按照标准老老实实地去写，现代的写法则先构造一个满足要求的临时对象，然后交换一下。

### operator=

```cpp
//// 古典主义写法
//wind::string& wind::string::operator=(const wind::string& s)
//{
//	// 防止自我赋值
//	if (this != &s)
//	{
//		// 为了避免空闲空间太大或不够
//		// 直接销毁被赋值对象
//		delete _str[];
//		_str = new char[s._capacity + 1];
//		_size = s._size;
//		_capacity = s._capacity;
//		strcpy(_str, s._str);
//	}
//	return *this;
//}

//// 现代主义写法
//wind::string& wind::string::operator=(const wind::string& s)
//{
//	if (this != &s)
//	{
//		string tmp(s._str);
//		swap(tmp);
//	}
//	return *this;
//}

// 后现代主义写法
wind::string& wind::string::operator=(wind::string s)
{
	swap(s);
	return *this;
}
```

把以前的数据交换给临时对象，随临时对象的析构而析构。——把需要的从临时对象那夺过来，把不需要的扔给临时对象。

### substr

```cpp
wind::string wind::string::substr(size_t pos, size_t len)const
{
	assert(pos < _size);
	string tmp;
	if (len == npos || pos + len >= _size)
	{
		len = _size - pos;
	}
	tmp.reserve(len);
	tmp._size = len;
	tmp._str[len] = '\0';
	strncpy(tmp._str, _str + pos, len);
	return tmp;
}
```

## P.J.版本string组织形式

先来看一份代码：

```cpp
void test5()
{
	std::cout <<"std::string->" << sizeof(std::string)<<std::endl;
	std::cout <<"wind::string->" << sizeof(wind::string)<<std::endl;
}
```

`x64`环境下是

![image-20241020183721106](https://img.mdwind.online/md/202410201837627.png)

在`x64`环境下，`size_t`是`unsigned long long`，它是八个字节的大小，`char*`是地址，也有八个字节，所以`sizeof(wind::string)`是24字节。

```cpp
private:
	char* _str;
	size_t _size;
	size_t _capacity;
	const static size_t npos;
```

在`x86`下，`size_t`是`unsigned int`，所以结果是12

![image-20241020183638609](https://img.mdwind.online/md/202410201836361.png)

我们发现不管是`x86`还是`x64`，标准库里的大小都比我们自己的多`16`字节，这`16`字节是什么呢？

微软给`string`对象又加了一个16字节的静态数组，当有效字符个数小于16时，这些数据就会被存放在这个静态数组里，而当有效字符个数等于或者超过16之后，这个静态数组就会被完全弃用，而改用再`new`处空间的方式存储字符串。

微软这样做的原因是为了防止内存碎片的出现，当进行多次动态开辟之后，内存块间的空间就很难被利用，从而造成内存利用率低，又考虑到字符串一般都不是太长，所以微软直接为对象增了一个静态数组成员，就固定的16字节，微软的`string`大概长这个样子：

```cpp
char _buff[16];
char* _str;
size_t _size;
size_t _capacity;
```

![image-20241020185342122](https://img.mdwind.online/md/202410201853765.png)

![image-20241020185508750](https://img.mdwind.online/md/202410201855810.png)

![image-20241020185541659](https://img.mdwind.online/md/202410201855722.png)

## SGI版本string组织形式

```shell
[wind@starry-sky ~]$ vim test.cpp
[wind@starry-sky ~]$ cat test.cpp
#include<string>
#include<iostream>

int main()
{
  std::cout <<"std::string->" << sizeof(std::string)<<std::endl;
  return 0; 
}
[wind@starry-sky ~]$ g++ test.cpp -o out
[wind@starry-sky ~]$ ./out
std::string->8
[wind@starry-sky ~]$
```

它`8`个字节。先说明一下，现在的`g++`默认`x64`。

这`8`个字节其实就是一个指针的大小，这个指针会指向一处空间，而这处空间里才存储着诸如`_size  _capacity _str`等信息。SGI的`string`从另一个角度提高效率，它使用了延迟拷贝的策略，我们上面写的拷贝构造和VS的大致相同，都是直接进行深拷贝，SGI不这样干，当发生拷贝时，它不会立刻进行深拷贝，而是把拷贝对象的指针赋给被构造对象，让这两个对象共用一处空间，而当这被构造对象要对空间写数据时，才进行深拷贝，让两个对象各用各的。

这处空间还存储着一个数据，这个数据用来描述现在有多少个对象同时使用这处空间，析构时，只对这个数据减一，而当数据为0时，才会`delete`。这个数据被称为“引用计数”。

```shell
[wind@starry-sky ~]$ vim test.cpp
[wind@starry-sky ~]$ cat test.cpp
#include<iostream>
#include<string>

int main()
{
  std::string s1("hello world");
  std::string s2(s1);
  std::cout<<(void*)s1.c_str()<<std::endl;
  std::cout<<(void*)s2.c_str()<<std::endl;
  s2[0]++;
  std::cout<<(void*)s1.c_str()<<std::endl;
  std::cout<<(void*)s2.c_str()<<std::endl;
  return 0;
}
[wind@starry-sky ~]$ g++ test.cpp -o out
[wind@starry-sky ~]$ ./out
0x1f0bc38
0x1f0bc38
0x1f0bc38
0x1f0bc68
[wind@starry-sky ~]$
```

就像进程的写时拷贝。(要换一个比喻, 关键是我还没有发表过系统方面文章)

# 完