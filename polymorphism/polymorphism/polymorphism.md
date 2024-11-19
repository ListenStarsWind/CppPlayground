# polymorphism

## concept

多态的概念：通俗来说，就是多种形态，具体点就是去完成某个行为，当不同的对象去完成时会产生出不同的状态。  

比如买票这个行为，当普通人买票时，是全价买票；学生买票时，是半价买票；军人买票时是优先买票。  

光说可能还是比较抽象，那就直接上代码了。

```cpp
namespace concept
{

	class Person {
	public:
		virtual void BuyTicket() { cout << "买票-全价" << endl; }
	};

	class Student : public Person {
	public:
		virtual void BuyTicket() { cout << "买票-半价" << endl; }
	};

	void Function(Person& p)
	{
		p.BuyTicket();
	}

	void func()
	{
		Person ps;
		Student st;
		Function(ps);
		Function(st);
	}
}
```

在这份代码中我们使用了虚函数，也就是被`virtual`修饰的函数。先直接感受感受效果。

![image-20241115210842554](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411152108629.png)

如果去掉function的引用，就不会有多态了。

![image-20241115211236704](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411152112091.png)

----------

多态有两个先决条件：

- 对虚函数进行了重写
- 使用基类的指针或者引用调用虚函数

不满足这两个条件，就不会有多态，而是依据实际类型与选择函数。

### virtual function

虚函数的重写具有硬性要求：

基类和派生类中的虚函数具有“三位一体”的特点：函数名必须相同，参数必须相同，返回值可以不严格相同。

首先对函数来说，`virtual`仅能修饰成员函数，要是普通函数，那就没有虚函数的说法。

返回值可以不严格相同的意思是，一般情况下，返回值类型是要严格相同的，但存在一种名为“协变”的例外，允许返回类型不同，但返回值必须是基类或者派生类的指针或者引用。需要注意的是，协变中所说的基类或者派生类也可以是另一对继承类组。

比如，`class A`和`class B`构成继承关系，尽管它们和`Person`和`Student`完全无关，但其指针或引用仍然可以作为`Person and Student`的虚函数返回类型。（为了方便，暂且就不写return了）

![image-20241115214149777](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411152141244.png)

![image-20241115214227890](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411152142397.png)

另外还要注意，基类里的虚函数返回值类型是派生类虚函数返回类型的基类，关系不允许倒置。

![image-20241115214600239](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411152146738.png)

也不能一个用指针，一个用引用。

![image-20241115214658600](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411152146056.png)

除此之外，派生类的`virtual`关键字可以省略，但基类不行。

![image-20241115214955072](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411152149581.png)

虽然可以通过编译，但已经不具有多态性质。

![image-20241115215233225](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411152152516.png)

这也可以理解，因为是对虚函数进行重写，所以被重写的函数一定要是虚函数，但后来重写的函数可以不是虚函数。当然，不建议省略。

------------------

接下来让我们看一看一份展示多态现实意义的代码

```cpp
class Person {
public:
	virtual void BuyTicket() { cout << "买票-全价" << endl; }
	~Person() { cout << "~Person" << endl; }
};

class Student : public Person {
public:
	virtual void BuyTicket() { cout << "买票-半价" << endl; }
	~Student() { cout << "~Student" << endl; }
};

void func()
{
	Person* p = new Person();
	delete p;

	p = new Student();
	delete p;
}
```

![image-20241116102935052](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411161029295.png)

如果没有多态，这两个指针都会使用`Person`的析构。可能你会说，析构函数名字都不一样，怎么达成多态的前提条件——虚函数重写呢？其实，析构函数是个特例，它们在底层上最终都会转换成`destrutor()`，这里的`delete p`会被转化成`p->destrutor() + operator delete(p)`。

这意味着，基类和派生类的析构函数是一种隐藏关系，它是依据类型来进行选择的，在这里由于p的类型是`Person*`，所以都调用了`Person`的析构。为了解决这个问题，我们需要把析构函数写成虚函数，从而实现多态调用。

![image-20241116104842702](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411161048138.png)

倒不是说多态就是为了让析构函数更完善，而是有些场景就是需要不同对象有不同的行为。

为什么这析构函数的机制这么奇怪呢？还要都转换成一个叫`destrutor()`的函数呢？一句话来说，就是C++吃书了。C++是逐渐发展的，它是现有类的概念再有继承多态的概念的，最开始，在只有类的时候，大家想的都很清楚，既然类里有构造，那就有析构，为了和构造相区分，析构函数的名字就是`~classname`，也不用经过什么`destrutor()`，逻辑很通畅，很自然。

但后来继承来了，人们发现了这样一个问题：我`new`了一个派生类对象，既然是`new`出来的，肯定是需要指针承接的，虽说我也不知道第一个发现这个问题的人为什么拿基类指针承接派生类对象，但从语法上说，这也没什么问题，但在`delete`的时候出事了，本来虽说这是个基类指针，但它毕竟指向的是派生类对象，从逻辑上说，它析构时应该用派生类的析构函数，但编译器只看参数类型，用的是基类析构。

发现问题就要解决，很可能大家也发现了其它同类型的问题：派生类对象中的基类部分有时候要和纯基类对象的行为有所区别，所以这就要求C++发展出多态的概念。

这多态其实也不是多难实现，我们计算机科学界祖师爷级别的人物，戴维·约翰·惠勒就说过这种话：计算机科学中的所有问题都可以通过增加一个间接层来解决。我们在上节课中也看到了，虚拟继承是用虚拟中间层实现的，虚函数其实也是用虚拟中间层实现的，具体我们会在后面说，于是人们就实现了多态。

但现在就出现了一个问题，虚函数要同名的，这析构函数名字不一样呀，前后逻辑冲突了，为了向前兼容，C++没有像Python那样具有魄力，发一纸通告，说以后我们不支持前面的某些操作，那会被人骂死的。所以没有办法，C++委员会就给C++硬打打上一个补丁。

说析构函数现在不是像以前那样直接调用了，编译器会把析构函数统一转化成`destrutor()`处理。

只能说C++是第一代经典的面向对象语言，没有现成的可以借鉴，都在摸索，C++之父`Bjarne Stroustrup`毕竟也是人，之前想类的时候没有想到后面会出这种事，所以这里的逻辑非常奇怪。

--------

从上面的过程中，我们可以看到普通调用和多态调用的区别，普通调用就看参数类型，对得上哪个类型，就用该类型中的函数；而多态调用，不只看参数类型，它更看参数索引的对象究竟是什么，如果你这基类对象是从派生对象中拿出来的，那就用派生中的函数，否则就用基类里的函数。

## what

从上面的过程中，我们已经了解到，虚函数的重写是对基类函数实现的重写，它所使用的接口仍旧是基类的，光这样说，可能没什么感觉，所以下面我们来几道题，来加深我们对虚函数重写内容的理解，要知道它重写的究竟是什么。

```cpp
namespace what
{
	class A
	{
	public:
		virtual void function(int val = 1) { std::cout << "A->" << val << std::endl; }
		virtual void test() { function(); }
	};

	class B : public A
	{
	public:
		void function(int val = 0) { std::cout << "B->" << val << std::endl; }
	};

	void func()
	{
		B* p = new B;
		p->test();
	}

	// A: A->0   B : B->1   C : A->1   D : B->0   E : 编译出错   F : 以上都不正确
}
```

只能说，出这道题的人对虚函数的重写有很深的理解。

我就不让大家猜了，直接给答案。

![image-20241118151203824](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411181512027.png)

首先我们`new`了一个派生类对象，用派生类指针去承接`new`出的指针，然后用这个指针调用基类里的`test()`，由于派生类中的`test()`是`public`的，所以派生类具有`test()`的使用权，此时`B*->test()`的行为就相当于`A*->test()`。这就是一次普通调用。

然后我们都知道，成员函数是通过`this`指针与对象建立联系的，当`p->test()`之后，`test()`里的`this`指针指向的就是`p`指向派生类对象中的基类部分，而成员函数内部使用其它成员函数，也会把自己的`this`指针传给其它成员函数。`this`指针的类型是由成员函数所在的类域决定的，这里的`test()`是`class A`的成员函数，所以`test()`的`this`指针类型就是`A*`。

而`test()`里的`function()`就相当于`this->function()`，而在`class A`中，`function()`是虚函数，所以它能被派生类中的`function()`重写，即使`class B`中的`funcition`并没有被`virtual`修饰，而`this`又是一个基类指针，所以`this->function()`是多态调用。

现在的问题是，到底调用哪个`function()`。首先因为`this`指针指向的基类对象位于派生类对象中，所以就`function()`的实现来说，它肯定是调用`class B`里的实现，但问题是，它用的接口是谁的。

虚函数重写的是函数实现，而不是函数接口，函数接口依旧是从基类上继承下来的，这也是为什么虚函数重写必须参数一样的原因，参数不一样对不上，而在之前的概念说明中，我们破坏虚函数重写条件，无论是从基类那里破坏还是从派生类那里破坏，可以看到的细节都是派生类报错，而不是基类函数报错，因为虚函数重写的接口就是以基类为标准的，只要派生类重写函数接口和基类接口不一致，那就是派生类的错，不是基类的错。

而在当前场景下，基类和派生类的接口确实是一致的，但缺省值不同，所以弄清虚函数用的到底是哪个接口就很重要了，虚函数用的是基类的接口，所以`val`被赋为了`1`，然后再调用派生类中的函数实现，所以最后打印的结果是`B->1`。

现在我们再直接调用一下基类和派生类中的`function()`

![image-20241118161211520](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411181612388.png)

当然，这种题目也只有在笔试或者面试的时候会被看到了，实际工作中肯定不能写出这种代码。这份代码更具有教学意义，没有应用价值。

---------------

接下里我们对比一下重载，重写（覆盖），重定义（隐藏）。

我们已经接触过重载一段时间了，重载的两个函数位于相同的作用域中，它们的函数名必须相同，同时参数必须不相同，参数不同包括三个方面：类型不同，个数不同，顺序不同。

重写的两个函数位于不同的作用域中，它们的函数名，参数，返回值都要完全相同（协变除外），并且基类中的函数必须是虚函数。

重定义的两个函数同样位于不同的作用域中，它们的函数名，参数，返回值都要完全相同，但不能是虚函数，最起码基类中的函数不能是虚函数。

如果有名字，参数，返回值都相同的两个函数分别位于基类和派生类中，则它们不是重写关系就是重定义关系。

----------------

从上面的过程中，我们可以看到C++对函数重写的条件比较苛刻，为了让开发者在编译过程就确定两个函数是否构成重写关系，C++11后新增了`override`关键字，在对派生类函数用该关键字进行修饰后，如果该函数找不到重写目标，`override`就会主动报错。

当重写有效时，`override`不会有任何信息

![image-20241118165309202](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411181653335.png)

重写失效就会报错。

![image-20241118165457763](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411181654497.png)

`error C3668: “what::B::function”: 包含重写说明符“override”的方法没有重写任何基类方法`

如果基类中的某些虚函数非常关键，重写会引发很大问题，就可以用`final`修饰该虚函数，使其无法被继承者重写。

![image-20241118164812332](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411181648261.png)

`error C3248: "what::A::function": 声明为 "final" 的函数不能由 "what::B::function" 重写`

`final`只能修饰虚函数。因为非虚函数本来就不能被重写。

## abstract class

在虚函数的声明之后加个`= 0`，则称这个虚函数为纯虚函数。纯虚函数只有一个接口，没有实现，实现依靠其派生类。包含纯虚函数的类被称为抽象类，也叫接口类。抽象类无法实例化出对象，在抽象类被继承后，若不对其中的纯虚函数进行重写，则派生类也无法实例化出对象。

写份代码

```cpp
namespace abstract_class
{
	class car
	{
	public:
		virtual void drive() = 0;
	};

	class tesla : public car
	{
	public:
		void drive() { cout << "disruptive" << endl;}
	};

	class xiaomi : public car
	{
	public:
		void drive() { cout << "cost-effective" << endl; }
	};

	void func()
	{
		car* pTesla = new tesla;
		pTesla->drive();

		car* pXiaomi = new xiaomi;
		pXiaomi->drive();
	}
}
```

我们知道，车，（说汽车可能不严谨），有很多种，有老品牌宝马奔驰什么，也有近年来才火起来的品牌，也就是代码中的特斯拉和小米。特斯拉的车开起来有颠覆性，它改变了人们原来对电动汽车的传统印象，并把软件系统大规模引入车中，还有自动驾驶什么的，以及马斯克个人也很具有个人魅力，等等；小米家的车和它们家其它产品一样，性价比都很高，安全，舒适度，营销什么的，都不错，雷军这个人也挺有意思。

好，回到现在的话题，在上面的代码中，`car`就是一个抽象类。它无法实例化出具体对象。

![image-20241118173548651](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411181735919.png)

指针和引用倒是可以用，不然怎么多态调用，使用派生类中的函数实现呢？

![image-20241118173741881](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411181737843.png)

![image-20241118173833588](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411181738845.png)

运行一下：

![image-20241118173950432](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411181739046.png)

我们看到，和以前的多态有些不同，它的这种多态是派生类之间的，不同的派生类行为就不同，而不是像往常一样，基类和派生类行为不同。这就是抽象类的一种优势：实现由同一个抽象类所继承的派生类对象的不同行为。

除此之外，抽象类要求派生类必须有虚函数重写（不然不能实例化出派生类对象），这相当于另一种`override`。抽象类是C++98引入的概念，而`override`是C++11引入的关键字。

还有一个优势，就是抽象类可以把描述的对象抽象化。光说这句话可能还是很抽象，那我们看看维基百科是怎么说的。

![image-20241118175305066](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411181753247.png)

![image-20241118175334063](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411181753260.png)

还是很抽象，来看看ChatGPT怎么说

![image-20241118175603123](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411181756338.png)

这回不抽象了，抽象就是概括事物最关键的本质特征，从而化繁为简，忽略不必要的细节。

车都能被开，开起来有不同的感觉。人有多种，按职业分，有公职员，工程师，风控管理，教师等，他们都是人，都会吃饭睡觉学习娱乐，但不同种的人各有各的具体实现。计算机有很多外部设备，它们都有读写方法，系统都把抽象成文件进行统一管理，所以Linux一切皆文件。

普通函数的继承是一种实现继承，派生类继承了基类函数，可以使用函数，继承的是函数的实现。虚函数的继承是一种接口继承，派生类继承的是基类虚函数的接口，目的是为了重写，达成多态，继承的是接口。所以如果不实现多态，不要把函数定义成虚函数。  

## principle

下面我们深究一下多态的实现原理。

先来一道题目引导一下我们的思路：

```cpp
namespace principle
{
	// 这里常考一道笔试题：sizeof(Base)是多少？
	class Base
	{
	public:
		virtual void Function()
		{
			cout << "Function()" << endl;
		}
	private:
		int _a = 1;
		char _b;
	};

	void func()
	{
		cout << sizeof(Base) << endl;
		auto t = Base();
	}
}
```

答案是16，注意这里用的是x64

![image-20241118182630277](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411181826863.png)

首先我们要知道，对于VS来说，它的自定义类是有内存对其策略的。

![image-20241118183126621](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411181831712.png)

现在我们为了方便描述，把类的起始位置看做是0。假设int是第一个成员，那它直接对齐0位置，char的对齐数是1，所以它可以对齐在4下标。最大对齐数是4，所以类的大小要是4的整数倍，现在是5，还不够，所以要加上3，变成8，但答案是16，因为还有一个指针，而指针在x64环境下是8字节，所以合计是16。

如果改成x86，那就是8+4=12了

![image-20241118192120513](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411181921843.png)

不过上面的推导逻辑还不够严谨，在上面的推理过程中，我们把指针是看做一个单独成员直接加上的，但实际上，内存对齐对于这个指针也是生效的。

![image-20241118192529129](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411181925514.png)

还要注意的是，这个指针其实才是第一个成员。比如在这张照片中，环境为64位，指针大小为8，指针是第一个成员，其对齐数就是8，接着才是int，现在类有12个字节了，但最大对齐数是8，所以还要补位，于是变成了16。

好了，不说内存对齐了。下面我们说一说这个指针到底是用来干什么用的。这个指针指向了一个中间的虚拟层，我们把这个虚拟层结构叫做虚函数表，把这个指针叫做虚函数表指针。虚函数表实际是一个函数指针数组，它存储着该对象虚函数的地址。

为了方面起见，减少内存对其和指针运算对我们的困扰，以下说明都是在x86环境下进行的

![image-20241118193534233](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411181935666.png)

![image-20241118193550319](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411181935355.png)

如果一个类中含有虚函数，则其对象的第一个成员为虚函数表指针，就是调试窗口中的`_vfptr`，`v`就是`virtual`，`f`就是`function`，不过最好再加一个`t`，毕竟它是数组指针，加个`table`，变成`_vftptr`，以突出它数组的形式。这个虚函数表是为以后派生类的重写做作准备的，并不是说一个类没虚函数它就绝对没虚函数表，等会我们具体谈到的时候再细说。

现在我们加几个虚函数，让效果更明显一些。

![image-20241118195108811](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411181951187.png)

![image-20241118195123534](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411181951576.png)

通过虚函数表中的函数指针就能在代码段直接找到对应的虚函数对象，或者说虚函数里面的指令。

现在我们回到之前的`class person class student`，以此来探讨多态的实现原理。

```cpp
namespace concept
{
	class A { protected: int _i; };
    class B : public A { protected: int _j; };

	class Person {
	public:
		virtual void BuyTicket() { cout << "买票-全价" << endl; }
		virtual ~Person() { cout << "~Person" << endl; }
		virtual void function() {}
	private:
		int _i = 0;
	};

	class Student : public Person {
	public:
		virtual void BuyTicket() { cout << "买票-半价" << endl; }
		virtual ~Student() { cout << "~Student" << endl; }
	private:
		int _j = 1;
	};

	void func1()
	{
		Person* p = new Person();
		delete p;

		p = new Student();
		delete p;
	}

	void Function(Person& p)
	{
		p.BuyTicket();
	}

	void func()
	{
		Person ps;
		Student st;
		Function(ps);
		Function(st);
	}
}
```

为了方便观察，某些地方被修改了。

![image-20241118201035030](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411182010418.png)

先看基类对象

![image-20241118200932959](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411182009041.png)

用监视窗口可能看的不是很真切，所以我们接下来看内存窗口

![image-20241118201104297](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411182011340.png)

![image-20241118201149535](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411182011588.png)

这就是`ps`对象，上面那行是虚函数表指针，下面那行就是成员变量`_i`

接下里我们去虚函数表里面看看

![image-20241118201610671](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411182016725.png)

和监视窗口里的值也是可以对上的。我们在基类里写了三个虚函数，它确实有三个函数指针。

而对于派生类对象来说，它会以拷贝的方式从基类那里继承一份虚函数表，然后，如果你重写了这些虚函数，就把新重写的函数指针覆盖掉原来的函数指针，没有重写方案，那就不管，所以重写还有一个名字，被称为“覆盖”，就是从原理的角度说的。因为派生类对象用的虚函数表是从基类那里拷贝过来的，所以派生类的重写函数可以不用`virtual`修饰。

![image-20241118202630942](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411182026985.png)

![image-20241118202735999](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411182027042.png)

前两行就是派生类中的基类部分，第三行是派生类对象自己特有的部分。

![image-20241118203017244](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411182030294.png)

前两个函数我们重写了，所以原来的函数指针被覆写了，现在这些指针指向派生类中重写的那些函数，而第三个函数我们没有重写，所以就用原来的。

接着我们来看汇编

![image-20241118203712697](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411182037831.png)

![image-20241118203759305](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411182037393.png)

我们来看看它引用的`p`

![image-20241118203859043](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411182038092.png)

我们来读一读汇编

![image-20241118204055206](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411182040259.png)

`mov         eax,dword ptr [p]`就是从`p`的起始地址开始读四个字节，然后把这四个字节写到`eax`寄存器中，所以`eax`里现在存的就是那个虚函数表指针

`mov         edx,dword ptr [eax]`就是从`eax`里存的地址为开始，把四个字节，也就是`BuyTicket()`的函数指针存到`edx`里

`mov         eax,dword ptr [edx]`就是把`edx`里的地址存到`eax`里

`call        eax`就是调用`eax`里函数指针指向的函数

我们调寄存器窗口看看

![image-20241118204743555](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411182047652.png)

要注意，这里寄存器指向的是地址，要借助于内存窗口去看这个地址里面有什么

![image-20241118210424048](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411182104125.png)

`EAX`指向的是`0x00fff548`，我们用内存窗口看了之后发现它里面的四字节内容就是虚函数表指针。

直接输入`edx`回车就能看到里面内容

![image-20241118210756630](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411182107688.png)

![image-20241118210814548](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411182108607.png)

可以看到，里面的内容就是基类里的`BuyTicket()`指针。

现在马上就要去`call`了

![image-20241118210945961](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411182109048.png)

![image-20241118211002956](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411182110993.png)

![image-20241118211042465](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411182110575.png)

这样就来到基类里的虚函数了

-----------

接下里看看派生类

![image-20241118211233106](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411182112256.png)

![image-20241118211342275](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411182113394.png)

![image-20241118211413026](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411182114117.png)

寄存器的值是派生类对象的虚函数表

![image-20241118211606977](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411182116039.png)

`edx`里的值是派生类重写函数的地址

![image-20241118211715354](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411182117446.png)

![image-20241118211728833](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411182117879.png)

准备`call`

![image-20241118211819623](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411182118742.png)

![image-20241118211842960](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411182118084.png)

![image-20241118211859196](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411182118300.png)

现在我们再写一个类继承`student`

![image-20241118213521692](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411182135937.png)

我们再来对比一下，`C`，`student`， `person`的虚函数表

![image-20241118213541735](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411182135788.png)

![image-20241118213602450](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411182136498.png)

![image-20241118213617206](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411182136263.png)

监视1是`C`实例化对象，监视2是`student`的实例化对象，监视3是`person`实例化对象

由于`student`中的两个函数都被`virtual`修饰，所以它的虚函数表继承给了`C`，`BuyTicket`没有被重写，所以`C`里的还是`student`里的，C有默认析构，而`student`里的析构也被`virtual`修饰，所以还是被重写了，最后`person`里的`function`那还是一直这样。

现在把`student`中的`virtual`去掉

![image-20241118214133730](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411182141149.png)

![image-20241118214038898](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411182140949.png)

![image-20241118214102122](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411182141161.png)

![image-20241118214117895](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411182141951.png)

`function`我就不说了，`BuyTicKet`可以略微说一下，`Student`对`Person`中的该函数进行了重写，所以，`Student`中的虚表中的函数指针发生了改变，然后`C`没有重写该函数，所以自然不改变。

至于`destrutor`，要特别强调一下，被`virtual`修饰的成员函数一定是虚函数，但这不意味着不被`virtual`修饰的成员函数就一定不是虚函数。比如在这里，尽管`Student`中的`destrutor`并没有被`virtual`修饰，但它也是虚函数，其指针被收录入虚表中，既然它已经被收录到虚表中，而`C`又有默认构造，所以还是完成了重写，并且此时`C`的默认构造也成为了虚函数，被收录到虚表中。

-----------------

如果不使用引用或者指针进行传参的时候，必然要经过拷贝构造这一中间过程，拷贝构造只拷贝普通成员变量，但它不会对虚函数表进行覆盖，所以它们自然无法实现多态。

你看`p`和`ps`的虚函数表是一样的，所以实现不了多态

![image-20241118215248558](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411182152954.png)

![image-20241118215301953](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411182153013.png)

![image-20241118215316374](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411182153426.png)

![image-20241118215349139](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411182153180.png)

拷贝构造不能覆盖虚函数表，那样会乱套的，分不清谁是谁。比如若是在上面的过程中使得拷贝构造会覆盖虚函数表，就会让`p`调用`student`析构。

同时这也能说明同样的类共用一个虚函数表，`ps`和`p`都是`0xcdbb34`，是同一份表。

# end