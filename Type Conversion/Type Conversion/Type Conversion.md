# Type Conversion

我们知道在C语言中，如果赋值运算符左右两侧类型不同，或者形参与实参类型不匹配，或者返回值类型与接收返回值类型不一致时，就需要发生类型转化，C语言中总共有两种形式的类型转换：隐式类型转换和显式类型转换。

- 隐式类型转化：编译器在编译阶段自动进行，能转就转，不能转就编译失败  
- 显式类型转化：需要用户自己处理  

```cpp
struct MyClass
{};

void Test()
{
	int i = 1;
	// 隐式类型转换:    用于转换意义相近的数据类型
	double d = i;
	printf("%d, %.2f\n", i, d);
	int* p = &i;
	// 显式的强制类型转换:   用于对意义不同的数据进行强制转换
	int address = (int)p;   // 指针的意义是地址, 而int, double是数据大小
    // 如果两个类型毫无关系, 强制类型转换也不能使用
    struct MyClass obj;
    int j = (int)obj;
	printf("%x, %d\n", p, address);
}
```

C++ 则认为C语言的类型转换不太规范(指不好分辨转换的具体作用),   所以它引入了自己的类型转换规范: `static_cast、reinterpret_cast、const_cast、dynamic_cast  `,   这四种都要会读会写,  因为面试的时候很容易稍微谈一下

--------------

`static_cast`用于进行相似类型的类型转换, 类似C的隐式类型转换, 相比隐式类型装换,  它直接写明类型,  可读性更高

`reinterpret_cast`用于进行有一定联系,  但在意义上已经不一样的类型转换, 比如上文的`ptr`转`int`

```cpp
int main()
{
	double d = 1.25;
	// int 和 double 表示数据大小,  意义相近, 形式不同
	int a = static_cast<int>(d);
	// 指针和int已经不是一个概念了, 无法使用static_cast
	int* ptr = reinterpret_cast<int*>(a);
	return 0;
}
```

`const_cast`用于取消对象的常属性

```cpp
int main()
{
	const int a = 2;
	int* p =const_cast<int*>(&a);
	*p = 3;
	cout << p << endl;
	cout << &a << endl;
	cout << *p << endl;
	cout << a << endl;
	return 0;
}
```

我们来看看结果

![image-20250306104803318](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250306104803456.png)

为什么会出现这种情况, `p`和`&a`都是一个地址, 为什么其具体内容却不相同?   这其实是编译器优化的结果,  我们在Linux那边说过, 在`signal.md`的`Volatile`子章节中说过这个. 编译器看到`a`被标记为`const`, 所以就认为这个变量不会被修改,   所以它可能就直接把`a`拷贝一份长期存在寄存器里, 以提高访问速度,(甚至把`a`出现的地方替换成2) 而当我们使用`p`修改`a`时, 改的只是内存中的`a`, 寄存器里的`a`没有被修改, 从而出现"数据不一致问题".  为了解决这个问题, 我们需要在`a`定义前面加`Volatile`, 告诉编译器,  对于这个变量, 不要优化, 用的时候都直接从内存里拿.

![image-20250306110120233](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250306110121056.png)

我们看到`&a`的内容不太对,   对此我们不需要太过在意,   这是因为这里的`a`类型有些过于复杂,  等到了`cout`里的时候,   它没有找到一个合适的重载函数,  可能进了`bool`重载, 毕竟`1`这个数字太特殊了, Linux的G++也是这样,  这里强转一下类型, C++的转不动

![image-20250306114211991](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250306114212047.png)

![image-20250306112123955](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250306112124922.png)

如果把`const_cast`换成C中的强制类型转换, 其结果还是相同的,  C++这种设计只是为了提高可读性,  比如这里`const_cast`的意思是这里取消常属性,   很危险,   要留意.

`dynamic_cast`在C语言中就没有对照物了,  这个是完全用在继承和多态的场景的,   对于这种场景, 可能存在一种情况,   需要把由切割产生的基类指针或者基类引用重新转成父类.

```cpp
class A
{
public:
	int _a = 0;

	virtual void func()
	{
		cout << "[class A] _a: " << _a << endl;
	}
};

class B : public A
{
public:
	int _b = 1;

	virtual void func()
	{
		cout << "[class B] _b: " << _b << endl;
	}
};

int main()
{
	A a;
	B b;

	// 派生可以直接转基类, 这是赋值兼容或者说切割
	A* Pa = &a;
	B* Pb = &b;
	Pa->func();
	Pb->func();

	return 0;
}
```

![image-20250306125210277](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250306125210363.png)

我们可能会写这种函数

```cpp
// 有时候, 会有这种需求
void f(A* ptr)
{
	// 默认传的是从class B切割下来的A*
	// 把它转回去
	B* Pb = (B*)ptr;
	Pb->_a++;
	Pb->_b++;
}
```

对于这种函数如果用C语言的强制类型转换就不太好,  如果传进来的实际上是个基类, 那就会造成越界访问.

为了方便实验, 我们临时写个类

```cpp
// 这里为了更好的模拟出越界访问的效果
// 临时修改对齐数, 让它们紧挨在一起
#pragma pack(1)
struct C
{
	A m;
	B n;
};
#pragma pack()
```

先让我们分析一下它们的内存情况

```cpp
int main()
{
	A a;
	B b;

	cout << sizeof(a) << endl;
	cout << sizeof(b) << endl;
	cout << sizeof(C) << endl;

	// 派生可以直接转基类, 这是赋值兼容或者说切割
	A* Pa = &a;
	B* Pb = &b;
	Pa->func();
	Pb->func();

	C c;
	f(&c.m);
	f(&c.n);

	return 0;
}
```

![image-20250306125653334](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250306125653384.png)

先看`class A`, 虚表指针八字节, 对齐到`m`的起始地址处, 偏移量是`[0, 7]`, `int`四字节可以对齐`8`,现在大小是12,  最大对齐数是`8`, 所以还要补一下, 补成16,   对于`m`来说,  继承下来的`class A`是16, 它自己有个`int`, 变成20, 最大对齐数是`8`, 补位, 变成24,  `struct C`的大小因为我们改变了默认对齐数, 所以变成紧挨着的样子.

这是`c`对象的内存

![image-20250306130524272](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250306130524313.png)

上面是`m`部分, 下面是`n`部分.

而在`f`中, 我们把`m`视为`class B`, 于是它就会按照`class B`的内存布局进行操作,

执行完`Pb->_b++`后

![image-20250306130824537](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250306130824577.png)

我们看到它改动了虚表, 而且没有任何报警.

用了`dynamic_cast`, 如果出现这种情况它就会返回空指针, 如果确实是从`class B`中切出来的, 那就会正常返回地址

```cpp
// 有时候, 会有这种需求
void f(A* ptr)
{
	// 默认传的是从class B切割下来的A*
	// 把它转回去
	B* Pb = dynamic_cast<B*>(ptr);
	Pb->_a++;
	Pb->_b++;
}
```

![image-20250306131508473](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/20250306131508877.png)

注意, 使用`dynamic_cast`的前提是进行了虚函数重写.

---------------

C++除了`RAII`, 还有一个`RTTI`(Run-time Type identification), 即运行时类型识别, 

C++通过以下方式来支持 `RTTI`：

- `typeid` 运算符
- `dynamic_cast`运算符
- `decltype  `    

# end