# reverse_iterator

迭代器是STL六大组件之一，通常分为正向迭代器和反向迭代器两类。在之前的学习中，我们已经对正向迭代器有了基本了解，接下来我们来探讨一下反向迭代器。

首先，可以确认的是，在我们已经实现了`vector`和`list`的正向迭代器之后，反向迭代器的实现其实并不复杂。正向迭代器的`begin`指向容器的第一个元素，`end`指向最后一个元素之后的位置，迭代过程是通过对指针或封装类的加减操作来实现的。那么，反向迭代器的实现就是将`rbegin`指向容器的最后一个元素，`rend`指向第一个元素之前的位置。

值得注意的是，我们不需要为反向迭代器单独编写代码。因为正向迭代器已经能够访问所有元素，所以我们可以将其封装成反向迭代器。通过创建一个模板类，将正向迭代器作为类型参数传入，在该类中，元素的访问依然通过正向迭代器进行。唯一需要做的就是调整迭代方向，将反向迭代器的`++`操作重载为正向迭代器的`--`操作。将其实现写成模板的另一个优势是，它能够适配不同容器的迭代器。由于正向迭代器是通用的，因此只要容器支持双向迭代器，就可以通过这个模板来实现反向迭代器。

实际上，这种模板实现的反向迭代器本质上是对正向迭代器的适配，它通过对正向迭代器的封装实现了反向迭代器的功能。

```cpp
template<class iterator, class reference, class pointer>
class __reverse_iterator
{
	typedef __reverse_iterator<iterator, reference, pointer> self;
public:
	__reverse_iterator(iterator it)
		:_it(it)
	{}

	__reverse_iterator(const self& obj)
		:_it(obj._it)
	{}

	~__reverse_iterator() {}

	self& operator++()
	{
		--_it;
		return *this;
	}

	self& operator--()
	{
		++_it;
		return *this;
	}

	reference operator*()const
	{
		return *_it;
	}

	pointer operator->()const
	{
		return &(operator*());
		//return _it.operator->();
	}

	bool operator==(const self& obj)const
	{
		return _it == obj._it;
	}

	bool operator!=(const self& obj)const
	{
		if (*this == obj)
			return false;
		else
			return true;
	}

private:
	iterator _it;
};
```

注意模版参数实际有三个，这和`list`的常迭代器类似，是为了常属性对象做的适配。看看`list`中的模版实例

![image-20241110075743591](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411100757281.png)

![image-20241110075815249](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411100758988.png)

注意，对于我们这种写法需要实际考虑一下容器的底层。`rend`返回第一个元素前的位置，对于 list 来说，就是哨兵位，而`end`恰好就指向哨兵位，所以`rend`返回`end`；`rbegin`返回最后一个元素，对于 list 来说，就是哨兵位前的那个节点，所以`rbegin`返回`--end()`。不过我们在实际代码中没有写成`--end()`的形式，因为`end()`的返回值具有常属性，不能被修改，所以我们使用一个过度迭代器对其进行修改。

值得注意的是，其实直接用`--end()`也不一定会真的报错，实际上，可能是为了便于对匿名变量的临时调整，编译器可能会允许对自定义常属性类型变量进行修改。目前并不清楚这是编译器自己的行为还是C++标准所规定的，不过我个人猜测是编译器个人行为，Visual Studio（VS）编译器的行为有时会偏离标准，举个例子，VS一直都不支持变长数组。因此，为确保兼容性和可读性，推荐使用临时迭代器的写法。

上述行为是基于我们当前实现的讨论。稍后，我们将探讨 SGI STL 中的实现方式。SGI 通过一些巧妙的设计，使得反向迭代器的逻辑更加抽象化，不再依赖容器的底层结构。在这种实现中，`rend()` 返回 `begin()`，而 `rbegin()` 返回 `end()`，从而形成了一个对称而优雅的结构。通过这种设计，反向迭代器的使用变得更为简洁，并与正向迭代器保持一致性，避免了对容器底层细节的关注。

-----------

接下来看看 vector 

![image-20241110083726213](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411100837815.png)

![image-20241110082413148](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411100824676.png)

`rbegin`返回最后一个元素的位置，所以是`end()`前的位置；`rend`返回第一个元素前的位置，所以是`begin()`前的位置。值得注意的是，我们的 vector 返回的其实就是原生指针，指针是内置类型，所以此时若要写成`--end()`的形式真的会报错。 

-----------

现在让我们把视角挪回 class template __reverse_iterator 我们发现一个特别的成员函数 `operator->()`：

```cpp
pointer operator->()const
{
    return &(operator*());
    //return _it.operator->();
}
```

由于 `__reverse_iterator` 是模板类，因此我们无法预先知道容器中元素的类型。对于用户自定义类型，无法确定类型的成员，因此需要显式调用正向迭代器的 `operator->()` 来访问成员。不过，这样的实现有一个隐含的前提条件：正向迭代器必须实现 `operator->()`。但有些容器，比如上面的 vector ，使用的就是原生指针，它的迭代器没有`operator->`重载，此时这样写就会发生错误，比如下面的测试代码

```cpp
struct A
{
	int _i;
	int _j;

	A(const int& i = int(), const int& j = int())
		:_i(i)
		,_j(j)
	{}
};

void test_myVector()
{
	wind::vector <A> v;
	v.push_back(A(1, 2));
	v.push_back(A(3, 4));
	v.push_back(A(5, 6));
	v.push_back(A(7, 8));

	const auto& cv = v;
	auto it = cv.rbegin();
	while (it != cv.rend())
	{
		std::cout << it->_i << " " << it->_j << std::endl;
		++it;
	}
}

int main()
{
	test_myVector();
	return 0;
}
```

![image-20241110084233165](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411100842219.png)

解决方案也很简单，既然`operator*`（指的是 `__reverse_iterator` 中的实现，而非其他地方的 `operator*`）返回的是容器中元素的引用，因此我们可以直接取其地址，这样就不再依赖正向迭代器是否有 `operator->()` 重载。

```cpp
pointer operator->()const
{
    return &(operator*());
}
```

---------------

接下来，我们探讨 SGI STL 如何实现之前提到的对称结构。SGI 只需在关键位置进行小幅调整即可实现这一结构。

![image-20241110085403428](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411100854206.png)

它先创建一个过度迭代器，然后对其进行`--`，使其指向原始迭代器的前一个位置，再访问过度迭代器索引的元素。

让我们看看 SGI 原码

![image-20241110090109744](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411100901377.png)

此时 vector and list 就可以修改成下面的形式

![image-20241110090305459](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411100903239.png)

![image-20241110090343710](https://md-wind.oss-cn-nanjing.aliyuncs.com/md/202411100903392.png)

# end