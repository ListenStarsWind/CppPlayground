# Inheritance Advanced

## casual talk

这不是本篇文章的重点，只是一个`casual talk`【杂谈】。该小节的话题是——如何实现一个无法被继承的class。

只需一招，把构造函数限制为私有即可，此时，由于构造函数为私有，尽管该类确实存在，但不管是在类外，还是在派生类中，都无法调用构造函数，对象都构造不出来，它自然就是完全无用的。而且此时由于派生类找不到基类的构造函数，所以派生类本身也会报错。

![image-20241115143122633](C:\Users\21066\AppData\Roaming\Typora\typora-user-images\image-20241115143122633.png)

class B也完全无法使用，因为它根本生成不了默认构造，所以是“已经删除的”

![image-20241115143310195](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411151433704.png)

不过如果不构造B，倒不会直接报错。

B在语法检查环节不会报错，是因为它表面上符合语法规则，但若要真的使用B，编译环节进入后就会发现找不到A构造而报错。

![image-20241115143449413](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411151434015.png)

在C++11之后，又引入了关键字`final`，它主要用于

- 防止类被继承。
- 防止虚函数在派生类中被重写。
- 在模板编程中控制派生类的继承。

在这个场景下，我们只看第一种用法，直接使用`final`对class进行后置修饰，此时在语法检查环节就会直接报错。

![image-20241115144404382](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411151444123.png)

## friend function

下面探讨一下继承和友元的关系。

友元关系不会被继承，这也好理解，父亲的朋友和孩子的朋友不是同一个概念，基类和派生各有各的朋友。

![image-20241115150032069](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411151500949.png)

直接报错。除非派生类声明`Display`是自己的朋友。

![image-20241115150247966](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411151502173.png)

## static member

静态成员依旧独立于class单独存在，换句话说，基类和派生类中用的静态成员都是同一个静态成员。

![image-20241115152103154](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411151521233.png)

![image-20241115152153560](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411151521486.png)

或者说，派生类没有继承静态成员本体（如果继承了就不是同一个了），而是继承了静态成员变量的使用权，当然，我说的是静态成员对派生类可见的情况下。

静态成员是用来干什么的我就不说了，之前说过。

## complex inheritance

单继承：一个子类只有一个直接父类时称这个继承关系为单继承  

![image-20241115154642552](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411151546684.png)

多继承：一个子类有两个或以上直接父类时称这个继承关系为多继承  

![image-20241115154728405](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411151547443.png)

比如某个学生也可能是其导师的助教。所以他既有学生身份，也有老师身份。

菱形继承：菱形继承是多继承的一种特殊情况。  

![image-20241115155103278](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411151551325.png)

学生和老师都是人，所以他们都继承了Person，但问题是，助教具有双重身份，当其把Student和Teacher继承后，其内部就有两个Person，一个继承自Student，另一个继承自Teacher，总不能说一个助教是两个人吧？这导致菱形继承中根基类的冗余和歧义。

冗余是说，根基类可能会含有许多成员变量，比如说，姓名，年龄，家庭住址，联系方式等，诚然，一个人老师身份的叫法和学生身份的叫法确实很可能不同，一个可能要以“老师”这个称谓为结尾，比如张老师，另一个可能则可能是小张，但总不能说一个人老师身份的年龄和学生身份的年龄不相同吧，这意味着，`Assistant`继承的两个`Person`绝大多数内容都是相同的，所以会造成空间的浪费。

![image-20241115161145814](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411151611272.png)

歧义是说，编译器分不清`Assistaant`中的`_name`到底是哪一个`_name`，因此必须标注域名。

![image-20241115161436921](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411151614293.png)

![image-20241115161559002](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411151615288.png)

为此，C++提出了虚拟继承的概念。它通过增加一个虚拟中间层，解决了这个问题，使得叶派生类中只有一个根基类。

在根基类派生类的继承方式前添加`virtual`关键字即可实现虚拟继承。

```cpp
namespace complex_inheritance
{
	class Person
	{
	public:
		string _name; // 姓名
		int _age;     // 年龄
	};

	class Student : virtual public Person
	{
	protected:
		int _num; //学号
	};

	class Teacher : virtual public Person
	{
	protected:
		int _id; // 职工编号
	};

	class Assistant : public Student, public Teacher
	{
	protected:
		string _majorCourse; // 主修课程
	};

	void func()
	{
		Assistant t;
		t.Student::_name = "xxx";
		t.Teacher::_name = "xxx";
	}
}

class task
{
	typedef void (*process) ();
public:
	void operator()() { _function(); }
private:
	process _function = complex_inheritance::func;
};

int main()
{
	task action;
	action();
	return 0;
}
```

什么是中间层呢？如果你对操作系统有了解，那肯定知道我说的中间层是什么意思。没学过系统也不用担心，上面的代码其实也有一个中间层，我以函数指针定义了一个仿函数，更改程序的执行函数只需要修改仿函数缺省声明中的域名即可，main函数本身则从来不改动。

不过我并不是说虚拟继承里的中间层就是仿函数，我只是想让你感受一下中间层的思想，方便我们下面说虚拟继承中的中间层。

虚拟继承后，对于根基类成员变量既可以指定域名，也可以不指定域名，实际上，此时`Assistant`中只有一个`Person`，这个`Person`既是`Student`的`Person`，也是`Teacher`的`Person`，所以自然不存在歧义问题，同时由于只有一份`Person`，冗余问题也被自然解决。

![image-20241115164610319](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411151646697.png)

注意，这也是一种菱形继承

![image-20241115165246877](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411151652914.png)

此时要用`virtual`修饰`Student`和上面的那个黑框，也就是修饰根基类的派生类。或者说要修饰会产生冗余基类的派生类上。

---------------

下面说一下原理。

我们先写一个足够简单的菱形继承。

```cpp
class A
{
public:
	int _a;
};

class B : virtual public A
{
public:
	int _b;
};

class C : virtual public A
{
public:
	int _c;
};

class D : public B, public C
{
public:
	int _d;
};

void func()
{
	D d;
	d.B::_a = 1;
	d.C::_a = 2;
	d._b = 3;
	d._c = 4;
	d._d = 5;
}
```

对象`d`的整体构造过程是这样的：

首先调用`class D`的构造函数，当然，这里用的是编译器自动生成的那一份，进入其初始化列表中，由于`class D`先继承`class B`，再继承`class C`，相当于声明中先是`B`，再是`C`，之前说过，初始化列表的顺序是依据声明顺序进行的，所以先对`B`进行初始化。

之后调用`class B`的构造函数，进入初始化列表之后，先对`A`进行初始化。

于是就进入了`class A`的构造函数，`class A`是根基类，其成员`_a`为内置类型，可能没有被初始化，这不重要，构造函数的函数体是空的，所以`class A`就构造完成了，之后就定义`class B`中的特有成员`_b`，同样的，`class B`构造函数的函数体为空，所以`class B`就构造完成了。

这样我们就又回到了`class D`的初始化列表中，接着对`class C`构造，来到`class C`构造函数的初始化列表部分，本来它确实是应该再构造一个`class A`的，但发现已经有一个`class A`了，于是就不再构造`class A`，而是通过虚拟中间层锚定了之前的`class A`，这个之前的`class A`就相当于`class C`自己的`class A`，同时，这个`class A`也是`class B`中的`class A`，这就是虚拟的含义：`class C`不是真的有`class A`，它只是共用之前已经存在的`class A`。

之后再定义`class C`中的特有成员`_c`，这样`class C`就构造完了，回到了`class D`的初始化列表中，对`class D`的特有成员`_d`进行定义，由于`class D`构造函数的函数体部分是空的，所以`d`就构造完成了。

不过我们还是没有说中间层是什么东西，没关系，下面就通过内存监视看一下中间层到底是什么。因为其中涉及到指针操作，所以为了方便观察，我们要把调试环境改成`x86`。

在`d`已经被构造完后，我们来到它的起始地址处。为了方便观察整型的四个字节，要把列调成4.

![image-20241115185142785](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411151851257.png)

![image-20241115185313789](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411151853818.png)

单步一下，就能找到`_a`

![image-20241115185408632](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411151854954.png)

![image-20241115185440597](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411151854635.png)

再单步一下，变成2，说明确实是`_a`

![image-20241115185529206](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411151855578.png)

![image-20241115185544109](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411151855141.png)

再单步一下，找到`class B`的特有成员`_b`

![image-20241115185645223](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411151856577.png)

![](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411151857583.png)

再单步一下，找到`class C`的特有成员`_c`

![image-20241115185848737](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411151858066.png)

![image-20241115185902743](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411151859781.png)

可以看到`_b`和`_c`中间还有一个`a4 cd ef 00`，这其实是个地址，指向中间层的地址。

打开另一个内存窗口，输入该地址，这里是小端字节序。

![image-20241115190255844](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411151902879.png)

我们看那个`0c 00 00 00`，上面的`00 00 00 00`先不要看。我们把`a4 cd ef 00`的地址，也就是`0x0073f604`加上`00 00 00 0c`得到了`0x0073f610`，要注意这是16进制，c是12,12加4是16，所以结果是10。

`0x0073f610`中存着什么？就是`_a`

![image-20241115185440597](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411151854635.png)

再看看`_b`前面的`98 cd ef 00`

![image-20241115191119980](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411151911016.png)

把`98 cd ef 00`的地址`0x0073f5fc`加上`00 00 00 14`得到`0x0073f610`，就是`_a`的地址。

也就是说，中间层存储着一个地址的偏移量，`0x0073f5fc`是`class B`的起始地址，`0x0073f604`是`class C`的起始地址，在`class B and class C`的特有成员变量`_b`和`_c`之前，存储着一个指针，该指针指向一个中间层结构，在该结构中存储着`class A`相对各自派生类的偏移量，用各自派生类的起始地址加上这个偏移量就能找到它们的基类`class A`，`class A`只有一个成员`_a`，所以`_a`的地址与``class A`的地址相同。

我们把`class B and class C`前面的那两个指针称为“虚基表指针”，而它们指向的中间层结构称为“虚基表”，虚基表中存储着地址偏移量，通过这个偏移量就可以找到其虚拟继承的基类起始地址。

## summary

在继承的开头，我们就说了继承是一种复用，复用的方式多种多样，除了继承，还有名为组合的方式。其实组合之间我们就用过，其实就是把一个类对象作为成员变量来使用，所以它是"has a"的关系，而继承则是"is a"的关系。

由于组合严格的使用类的接口，所以可以完全不关心被复用类的内部逻辑，这种复用风格被称为黑箱复用(black-box reuse)，因为对象的内部细节是不可见的。对象只以“黑箱”的形式出现。  这种复用的好处是组合类之间没有很强的依赖性，我们将这种性质称呼为“低耦合”。每个类专攻某个特定的功能，它们可以方便地进行搭配组合，从而快速实现不同的效果。当某个类出现问题时，也能较为方便地对该类进行修正甚至是替换。

继承会让组合类变得高耦合，需要关心被复用类的具体细节，所以复用通常被称为白箱复用(white-box reuse)。  但它比组合更加灵活，更关键的是，多态是建立在继承基础上的，想要实现多态就必须用到继承。

而在实际的工程项目中，更多的还是看所描述的具体对象，若其具有"has a"的关系，当然最好使用组合，而其具有"is a"的关系，更应使用继承。

## example problem

试比较p1, p2, p3的大小关系

```cpp
class Base1 { public: int _b1; };
class Base2 { public: int _b2; };
class Derive : public Base1, public Base2 { public: int _d; };

int main(){
    Derive d;
    Base1* p1 = &d;
    Base2* p2 = &d;
    Derive* p3 = &d;
    return 0;
}
```

`Base1`先被继承，所以其地址与`Derive`的起始地址相同，而`Base2`后继承，所以地址在它们其后，故`p1 == p3 != p2`

```cpp
namespace example_problem
{
	class A {
	public:
		A(const char* s) { cout << s << endl; }
		~A() {}
	};

	class B :virtual public A
	{
	public:
		B(const char* s1, const char* s2) :A(s1) { cout << s2 << endl; }
	};

	class C :virtual public A
	{
	public:
		C(const char* s1, const char* s2) :A(s1) { cout << s2 << endl; }
	};

	class D :public C, public B
	{
	public:
		D(const char* s1, const char* s2, const char* s3, const char* s4) :B(s1, s2), C(s1, s3), A(s1)
		{
			cout << s4 << endl;
		}
	};

	void func()
	{
		D* p = new D("class A", "class B", "class C", "class D");
		delete p;
	}
}
```

照着虚拟继承原理中的构造过程走就行，答案是`class A class C class B class D`。因为`class A`已经在`class C`的构造过程中被构造过了，所以`class D`构造函数初始化列表中的`A(s1)`不会生效。注意初始化列表定义顺序。

# end