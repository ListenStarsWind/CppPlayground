# template's separate compilation

在学习模版的时候，我们说过模版不能分离编译。下面我们就来说一说这是为什么。

比如现在我们有三个文件：

`main.cpp`中是main函数

```cpp
#include"template.h"

int main()
{
	int i = add(4, 5);
	std::cout << i << std::endl;
	return 0;
}
```

`template.h`是模版声明

```cpp
#pragma once

#include<iostream>

template<class T>
T add(const T& n1, const T& n2);
```

`template.cpp`是模版定义

```cpp
#include"template.h"

template<class T>
T add(const T& n1, const T& n2)
{
	return n1 + n2;
}
```

它能跑的动吗？很明显，不行。注意它是`error LNK`，是链接错误。

![image-20241113083634739](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411130836920.png)

这是为什么呢？这就和编译原理有关了。

在预处理阶段，我们会展开头文件。

这样`template.cpp`就会变为`template.i`

```cpp
#include<iostream>

template<class T>
T add(const T& n1, const T& n2);

template<class T>
T add(const T& n1, const T& n2)
{
	return n1 + n2;
}
```

`main.cpp`会变成`main.i`

```cpp
#include<iostream>

template<class T>
T add(const T& n1, const T& n2);

int main()
{
	int i = add(4, 5);
	std::cout << i << std::endl;
	return 0;
}
```

在编译过程后，这两个`.i`文件会转化成对应的机器码。main函数中用到了`add(const int&, const int&)`，编译器发现前面有声明，于是就不会报编译错误，它又看到`add`就是模版，于是实例化出了`add(const int&, const int&)`的函数声明，为什么是函数声明呢？因为这里的模版只是声明，没有定义，它只能实例化出声明。

因为找不到函数的定义，编译器先把`add(const int&, const int&)`的函数地址标记为空，它的意思是等到链接阶段再看看能不能从别的文件里发现`add(const int&, const int&)`的定义，如果发现了，那就修正这个地址，没有就链接错误。

而对于`template.i`来说，其在编译过程中，由于没有用到`add(const int&, const int&)`，所以它不会实例化出`add(const int&, const int&)`的定义。

于是在链接环节，编译器在其它文件里找不到`add(const int&, const int&)`。所以它认为这个函数是无法解析的。

--------------------

现在我们在`template.cpp`中用一下`add(const int&, const int&)`，但不在main函数里调用它。

`template.cpp`

```cpp
#include"template.h"

template<class T>
T add(const T& n1, const T& n2)
{
	return n1 + n2;
}

void f(const int& a, const int& b)
{
	int i = add(a, b);
}
```

其它地方都没变，但已经可以运行了。

![image-20241113085750241](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411130857631.png)

也就是说，模版不支持分离编译的根本原因是因为编译是多个文件并行进行的，编译器不会把一个文件编译一半就跳到另一个文件上，所以就不会有实例化的定义，它自然会出错。

![image-20241113093704949](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411130937037.png)

为什么不支持串行编译呢？因为以后我们写的一个项目，最起码有几十个文件，如果编译器在编译时在文件里跳来跳去，效率就太低了。

-------------

有什么解决方案呢？这些解决方案从根本上来说都是在`template.cpp`里实例化出需要的定义就行，刚才我们是通过在`template.cpp`里使用一个`add(const int&, const int&)`示例化出的，我们也可以手动实例化。

![image-20241113091033424](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411130910118.png)

记住，显式实例化是这样写的：

```cpp
template
int add<int>(const int& n1, const int& n2);
```

接下来我们看看class template ，为了图方便，`push`就只用类型匹配了，没有具体功能。

```cpp
// template.h
template<class T>
class test
{
public:
	void push(const T&);
private:
	T* _p = nullptr;
	size_t _size = 0;
	size_t _capacity = 0;
};
```

```cpp
// template.cpp
template<class T>
void test<T>::push(const T&)
{
	std::cout << "using push(const T&)" << std::endl;
}
```

```cpp
// main.cpp
int main()
{
	test<int> t;
	t.push(1);
	return 0;
}
```

同样是链接错误：

![image-20241113092214115](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411130922838.png)

![image-20241113092228732](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411130922785.png)

也很简单，在定义文件里实例化出一个具体的类就行了。

![image-20241113092642020](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411130926457.png)

```cpp
template
class test<int>;
```

但无论怎么样，这种显示实例化都把模版最大的优点：自动实例化给屏蔽了，所以模版必须写在一个文件里，有时为了明确文件的具体内容，含有模版的文件通常都不是`.h`，而是`.hpp`，`.hpp`中的`h`指头文件，`pp`指`cpp`，暗含的意思是`.hpp`里既有声明也有定义。

那为什么模版写一个文件里就不会有链接错误呢？因为在预处理阶段，模版定义直接全部展开在需要使用的文件中，此时若要使用这个模版，它就直接实例化出定义，完全不依靠其它文件，自然不会有链接错误。

----------

最后说说再总结一下模版的特点;

优点

- 模板复用了代码，节省资源，更快的迭代开发，C++的标准模板库(STL)因此而产生  
- 增强了代码的灵活性  

缺点

- 模板会导致代码膨胀问题，也会导致编译时间变长  
- 出现模板编译错误时，错误信息非常凌乱，不易定位错误  

第一个缺陷没什么问题，它要实例化，每实例化出一个函数对象或者类型都会增加一些代码，但这是不可避免的，说不定你一个一个手写膨胀地更厉害，估计还要找找BUG，手抖一下写错符号了。

第二个缺陷才是要命的，模版的报错太难看了，一报错就是一堆错误，这没办法，在这里我只能说，如果模版出错看第一个错误，因为后面的错误可能是由前一个错误引发的。另外，双击模版报错信息时跳转到的位置有时候不准，有可能错误并不在这个位置，实在找不到，那去看看其它部分。

# end