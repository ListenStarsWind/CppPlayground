# Inheritance

我们知道，面向对象有三大特性：封装， 继承， 多态，今天我们就来说说继承。

## concept

先让我们说说继承的`concept`【概念】。所谓继承，简单地说，其实就是代码的复用。

比如在C阶段学习排序的时候，我们发现，sort总是少不了大小比较和数据交换，于是我们把它们写成具体的函数，等到排序要用到的时候，再调用这些函数，这就是一种朴素的继承。

再比如，我们想描述一下学生和老师。不论学生还是老师，他们都是人，都有一些人共有的属性，比如姓名，性别，出生日期，身份证号，联系方式之类的东西，那我们就可以先写一个类，描述一下人的共有属性，然后再让学生和老师继承这个类，其它学生和老师特有的属性再另外定义。

在这种场景下，我们把描述人的`class person`称为“父类”， “基类”；而继承`person`的`class teacher`以及`class student`称为“子类”， “派生类”。

```cpp
#include<iostream>
#include<string>

using namespace std;

class Person
{
public:
	void Print()
	{
		cout << "name:" << _name << endl;
		cout << "age:" << _age << endl;
	}
protected:
	string _name = "peter"; // 姓名
	int _age = 18; // 年龄
};

class Student : public Person
{
protected:
	int _stuid; // 学号
}; 


class Teacher : public Person
{
protected:
	int _jobid; // 工号
};
```

我们先不管那么多，现在只需要记一下继承的格式：`class Student : public Person`，其中的`public`描述的是继承关系，访问限定符`protected`先不要去管。

![image-20241113103427115](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411131034865.png)

![image-20241113103446940](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411131034995.png)

`Person`中除了成员变量被继承了，成员函数也被继承了。

![image-20241113103621994](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411131036209.png)

暂且先不管如何初始化。

上面我们稍微感受了继承，接下来我们详细说说继承的格式：

![image-20241113104023481](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411131040549.png)

C++为继承提供了多种方式，这与访问限定符相组合，就有了多种组合。

![image-20241113104231348](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411131042423.png)

![image-20241113104251991](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411131042064.png)

之前我们不写继承，所以说`protected`和`private`是一样的，现在我们学到继承了，就要详细说说它们之间的区别了。

基类`private`成员在派生类中无论以什么方式继承都是不可见的。这里的不可见是指基类的私有成员还是被继承到了派生类对象中，但是语法上限制派生类对象不管在类里面还是类外面都不能去访问它。

基类`private`成员在派生类中是不能被访问，如果基类成员不想在类外直接被访问，但需要在派生类中能访问，就定义为`protected`。可以看出保护成员限定符是因继承才出现的。

一句话来描述这个表格，就是选取更严格的那个作为标准。比如对于`public`【公有】继承来说，基类里的`public`成员就相当于派生类`public`的成员，所以可以直接在派生类外调用；而基类里的`protected`【保护】成员，相当于派生类的`protected`成员，在派生类外，它无法被访问，但如果把这个派生类继承到另一个类里，那对于另一个类来说，它是可以被访问的，但同样，在类外是不能被使用的；基类里的`private`【私有】成员则完全无法被派生类使用。等会我们会用代码进行演示。

基类`private`成员在派生类中全都不可见，对于其它搭配，则选取继承方式和访问限定符更严格的那个。`public`遇到`public`是`public`，`public`遇到`protected`是`protectde`，`public`遇到`private`是`private`。

三种访问限定符乘上三种继承方式就有九种组合。但实际上，几乎很少使用，也不提倡`protected or private`继承方式，因为它们继承下来的成员都只能在派生类的类里面使用，实际中扩展维护性不强。也就是说，一般只用第一列。

基类的`private`成员无论以何种方式继承，在类外，还是在派生类里都不可使用。

![image-20241113110653025](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411131106129.png)

![image-20241113110803123](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411131108124.png)

现在把`Print`改成`protected`，现在在派生类里就可以使用了：

![image-20241113111144548](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411131111405.png)

但在类外仍是不可使用：

![image-20241113111221682](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411131112905.png)

另外再说一声，当不写继承方式时，编译器就会选取默认继承方式，如果派生类是class ，那默认为`private`

![image-20241113112436298](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411131124262.png)

如果派生类是struct ，那就默认为`public`

![image-20241113112536845](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411131125971.png)

不可见和私有的共同点在于它们都不能在类外使用，区别在于，不可见在派生类里也不能使用，但私有可以。

假如有三个类ABC，B继承A，C继承B，那么如果B采用`protected`继承A，那么C就能使用A里的东西，如果使用`private`继承A，那么C就用不了A里的东西了。

## using

概念说的差不多了，接下来说说怎么用。在正式说怎么用的时候。先说一个奇怪的现象，来引出下面的使用。

我们知道，当两个变量的类型不一致时，若要赋值，会有一个过度的临时变量。

```cpp
int main()
{
	double d = 1.25;
	int i = d;
	return 0;
}
```

这个过度的临时变量具有常属性，这样看，更明显

```cpp
int main()
{
	double d = 1.25;
	int& i = d;
	return 0;
}
```

这个就跑不动了，因为d会先被转换成一个临时的中间变量int，但临时变量具有常属性，而int&可被修改，发生了权限的扩大，所以就无法通过编译。

```cpp
int main()
{
	double d = 1.25;
	const int& i = d;
	return 0;
}
```

加个const就行了。

------------

好的，下面来看奇怪现象了。

```cpp
int main()
{
	Student s;
	Person& p = s;
	return 0;
}
```

这个能跑得动。

因为s到p的过程中并没有产生临时对象，因此可以编译通过，那这p引用的到底是什么呢？实际上，它就是被s继承的Person类型对象。

注意，这里的Student是以public的方式继承Person的，对于其它继承方式，则不一定使用，让我们来谈谈为什么。

---------------------

一个对象的行为由其公开接口决定。对于类而言，这意味着类的行为由其公开接口决定。public继承允许派生类继承基类的公有和保护成员，并保持基类的公有成员为公有，这使得派生类在行为上等同于基类对象，符合“is-a”关系。protected继承和private继承则不同，虽然派生类获得了基类的公有和保护成员，但不将这些成员公开给外部。protected继承会将基类的公有成员在派生类中作为保护成员，而private继承会将其作为私有成员。这影响了进一步派生的类对这些成员的访问权限：在protected继承中，进一步派生的类可以访问这些成员，但在private继承中，则不能。

~~首先我们知道，一个对象的行为是由其接口决定的。更准确地来说，由于类域的限制，是由其公开接口所决定的，这意味这，如果派生类可以获得基类的公开接口并且把它公开，就能具有和基类对象一样的行为。~~

~~public继承暗含两种含义：一是派生类从基类中继承了基类的所有公有和保护成员，比如赋值重载函数这个接口，而是派生类以自己为支点，将从派生类获得的公有成员公开到类外；对于protected和private继承来说，派生类虽然仍旧从基类那里获得了全部的公有和保护成员，但派生类并没有将其公开到类外。那protected和private继承有什么区别呢？它们之间的区别需要再引入一个类才能体现出来，就像上面说的ABC三个类，如果B以protected的方式继承A，则当C继承B时，C也会获得A的全部公有和保护成员，但B若以private的方式继承A，C再继承B的时候就不会获得A的接口。另外要注意的是，protected的限制是可以跨层的，比如若B以protected继承A，则即使C以public方式继承B，那也只能在C内部使用A的接口，而不会把A的接口公开出类外。~~

我们配合代码理解。

![image-20241113134745183](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411131347850.png)

当Student以protected继承Person时，在C内部可以使用Person的接口，因此具有和Person相似的行为，可以对Person进行赋值

![image-20241113135024790](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411131350357.png)

虽然是用public继承的Student，但A的接口没有暴露出类外，类外依旧无法使用Person的接口，因此，无法进行赋值。

--------------------------

~~所以只有以public方式继承基类的派生类才能实现派生类对象向基类对象赋值的行为。我们下面所说的都是赋值行为的具体细节，这都是针对public方式继承来说的。~~

~~在派生类对象中，其内部有着天然的基类对象，这个基类对象有点像匿名对象，稍后在许多地方，特别是初始化环节，我们可以看到它的行为有点像匿名对象。由于派生类对象拥有基类对象的所有公开接口，所以在行为上，就像是派生类对象内的基类对象赋给另一个基类对象。因此，在赋值过程中，不会产生临时变量，这被称为父子类赋值兼容规则，有时也通俗的说成是切割或者切片。~~

只有以public方式继承基类的派生类才能支持将派生类对象赋值给基类对象。下面的讨论均基于public继承的具体细节。

在派生类对象中，隐含地包含了一个基类对象，这个基类对象作为派生类对象的一部分存在。由于派生类对象拥有基类的所有公有接口，它在赋值行为上表现得像是其内部的基类对象赋值给另一个基类对象。因此，在这种赋值过程中，不会创建临时变量，这符合C++中的“切片”或“切割”规则，即派生类对象赋值给基类对象时，只有基类部分会被复制，而派生类特有部分被忽略。

如果是赋值，就把派生类对象的基类部分直接赋值给另一个基类对象，如果是指针或者引用，则是对派生类对象中的基类部分本身取地址。

基类对象一般不能赋给派生类对象，这很好理解，因为派生类对象有些特殊成员，仅靠基类对象无法对其进行初修改，除非建立一套机制，在赋值的同时自动修改特有成员。比如，特别写一个`operator=`重载，让特有成员直接回到初始值。

----------------------------------

下面说一说继承中的作用域。

基类和派生类之间的类域相互独立，因此它们可以有同名成员。

![image-20241113154946120](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411131549682.png)

比如，在这张图中，`Person and Student`都有成员`__number`，在派生类中，编译器默认使用该派生类中的`_number`。

![image-20241113155341659](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411131553018.png)

想要使用基类中的同名成员，需要指定域名。

![image-20241113155512277](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411131555623.png)

有时把这种行为（派生类访问同名成员时，默认使用该派生类成员）的行为叫做派生类同名成员隐藏了基类同名成员，这对函数仍旧适用。

```cpp
class A
{
public:
	void fun()
	{
		cout << "func()" << endl;
	}
};

class B : public A
{
public:
	void fun(int i)
	{
		A::fun();
		cout << "func(int i)->" << i << endl;
	}
};
```

这两个`fun`处于不同的域中，因此一定不是函数重载，实际上它们构成隐藏关系，

![image-20241113160621355](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411131606664.png)

同样的，需要指定域名之后再能调用A中的fun

![image-20241113160814787](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411131608102.png)

当然为了避免混淆，我们不推荐创建同名成员。

----------------------------

接下来我们真的要说怎么用了，围绕派生类的默认函数。

我们先说派生类的默认构造函数，派生类对象中的基类部分可以看做另一个成员变量，在默认构造的初始化列表中，将会首先定义基类对象，再定义派生类特有对象。或者说的更明确一点，继承的对象相当于是声明中的第一个成员变量，所以初始化列表必然最先定义它。

```cpp
class Person
{
public:
	Person(const string& name)
		:_name(name)
	{
		cout << "Person(const string&)" << endl;
	}
protected:
	string _name = "peter"; // 姓名
};

class Student : protected Person
{
public:
	Student(const string& name, int id)
		:Person(name)
		,_stuid(id)
	{
		cout << "Student(const string&, int)" << endl;
	}
protected:
	int _stuid; // 学号
}; 
```

可以看到，这里对派生类对象中基类部分的定义就像是创建匿名对象。

![image-20241113163232508](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411131632837.png)

对于拷贝构造来说，可以直接使用派生类对象定义派生类对象中的基类部分

![image-20241113163953362](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411131639812.png)

![image-20241113164210004](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411131642315.png)

对于赋值重载来说，需要显式调用基类的赋值重载，这里一定要注意，指定域名，因为派生类的赋值重载和基类的赋值重载构成隐藏关系，如果不指定域名，派生类中的赋值重载就会一直自递归。

![image-20241113165820992](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411131658449.png)

![image-20241113165851208](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411131658563.png)

对于析构函数来说，则有些特殊。如同常引用可以锚定匿名对象，使其不会立刻析构，而是在常引用生命周期结束后在析构。派生类对象中的基类部分的生命周期是依附于派生类对象的，因此在派生类的析构函数中不用显式调用基类的析构（实际上，在派生类中的析构函数中不能显式调用基类析构函数，至于到底为什么，我们先不考虑，这是多态中的学习内容，我们先跳过。）

在派生类的析构函数中，我们只要对派生类的特有成员变量进行处理就行了，当然，在该种场景下，特有成员变量是自定义类型，倒也不需要处理，而特有成员如果是自定义类，也不需要处理，因为自定义类型有自己的析构函数。

当派生类被析构之后，由于派生类对象中的基类对象是依附于派生类对象存在的，所以，它的生命周期也会结束，也会自动调用析构函数。

也就是说析构在此种场景下不用写。

![image-20241113171609426](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411131716810.png)

据说析构的顺序是个高频考点，一定是先派生再基类。如果上面的说法是从逻辑层面上解释的话，那接下来的解释就是应用层面的：如果先基再派生，就会出现对基类的重复析构，所以一定要先派生再基类。

# end