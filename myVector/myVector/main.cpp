#include<iostream>
#include<string>
#include"myVector.h"
#include"using.h"

void realization1() {
	wind::vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	for (auto data : v)
	{
		std::cout << data << " ";
	}
	std::cout << std::endl;
}

void realization2()
{
	wind::vector<int> v;
	size_t sz = v.capacity();
	std::cout << "making v grow:\n";
	for (int i = 0; i < 100; i++)
	{
		v.push_back(i);
		if (sz != v.capacity())
		{
			sz = v.capacity();
			std::cout << "capacity changed: " << sz << '\n';
		}
	}
	for (auto data : v)
	{
		std::cout << data << " ";
	}
	std::cout << std::endl;
}

void realization3()
{
	wind::vector<std::string> str_arry;
	auto& v = str_arry;
	v.push_back("1111");
	v.push_back("11111111111111111111111111");
	v.push_back("xxxxxxxxxxxxxxxxxxxxxxxxxx");
	v.push_back("11111111111111111111111111");
	wind::vector<std::string>::iterator it = v.end();
	v.insert(it, "hello word");
	for (auto m : v)
	{
		std::cout<<m<<std::endl;
	}
}

// 演示迭代器外部失效
void realization4()
{
	std::vector<int> v;
	//wind::vector<int> v;
	v.push_back(0);
	v.push_back(1);
	v.push_back(2);
	v.push_back(2);
	v.push_back(3);
	v.push_back(3);
	//wind::vector<int>::iterator it = v.begin();
	std::vector<int>::iterator it = v.begin();
	// 目标：删除所有偶数元素
	while (it != v.end())
	{
		if (*it % 2 == 0)
		{
			v.erase(it);
		}
		++it;
	}
	for (auto val : v)
	{
		std::cout << val << " ";
	}
	std::cout << std::endl;
	// 输出结果：1  2  3  3
	// it -> 0    0 1 2 2 3 3   删除 迭代器指向内容发生改变 it -> 1  外部循环再加一 it -> 2
	// it -> 2    1 2 2 3 3     删除 迭代器指向内容发生改变 it -> 2  外部循环再加一 it -> 3
	// it -> 3    1 2 3 3       外部循环加一 it -> 3
	// it -> 3    1 2 3 3       外部循环加一 it -> 3
	// 解决方案： erase是有返回值的，可以用来修正外部迭代器
}

void realization5()
{
	//std::vector<int> v;
	wind::vector<int> v;
	v.push_back(1);
	v.push_back(1);
	v.push_back(1);
	v.push_back(2);
	wind::vector<int>::iterator it = v.begin();
	//std::vector<int>::iterator it = v.begin();
	// 目标：删除所有偶数元素
	while (it != v.end())
	{
		if (*it % 2 == 0)
		{
			v.erase(it);
		}
		++it;
	}
	for (auto val : v)
	{
		std::cout << val << " ";
	}
	std::cout << std::endl;
	// 结果：触发assert警告
	// 最后一个元素被删除之后，迭代器已经指向非法区域
	// 其值为随机值
	// 当为偶数时，再次进入erase，触发范围检查警告
}

// 解决方案：删除之后对迭代器进行修正
void realization6()
{
	//std::vector<int> v;
	wind::vector<int> v;
	v.push_back(0);
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(4);
	wind::vector<int>::iterator it = v.begin();
	//std::vector<int>::iterator it = v.begin();
	// 目标：删除所有偶数元素
	while (it != v.end())
	{
		if (*it % 2 == 0)
		{
			it = v.erase(it);
		}
		else
		{
			++it;
		}
	}
	for (auto val : v)
	{
		std::cout << val << " ";
	}
	std::cout << std::endl;
}


// 刚刚使用的是我们自己实现的vector
// 现在换成VS自己的看一看
// 我们发现此时4 5号序列都报错
// VS对迭代器进行了强制检查
// 只要发现经过erase的迭代器
// 没有被修正，直接操作（比如++）就报错
// 待会看看能不能演示insert，看看效果

// g++则是更像我们实现的逻辑
// 毕竟我们的实现就是从它的原码开始的


// 额外说一下：
// 我们写的模版中成员函数的参数和返回值类型
// 都是直接用vector
// 但在外面可不能这样用
// 之前说过vector是模版
// 但不是类型，实例化后的模版
// 才是类型，但在模版里面
// 编译器默认vector就是vector<T>
// 所以模版里可以写vector
void realization7()
{
	wind::vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);

	for (auto val : v)
	{
		std::cout << val << " ";
	}
	std::cout << std::endl;

	wind::vector<int> val;
	val.push_back(6);
	val.push_back(7);
	val.push_back(8);
	val.push_back(9);
	val.push_back(10);

	v = val;

	for (auto e : v)
	{
		std::cout << e << " ";
	}
	std::cout << std::endl;
}

void realization8()
{
	wind::vector<int> v1;
	v1.push_back(1);
	v1.push_back(2);
	v1.push_back(3);
	v1.push_back(4);
	v1.push_back(5);

	wind::vector<int> v2(v1.begin(), v1.end());

	for (auto e : v2)
	{
		std::cout << e << " ";
	}
	std::cout << std::endl;

	std::string s("hello world");
	wind::vector<int> v3(s.begin(), s.end());

	for (auto e : v3)
	{
		std::cout << e << " ";
	}
	std::cout << std::endl;
}

void realization9()
{
	//wind::vector<std::string> v(10, "xxxxxxxxx");

	// 10 和 0都被视为int,这是相同的类型
	// 迭代器区间构造参数为InputIterator, InputIterator
	// 是完全相同的类型
	// 而n个val构造，参数为size_t , T
	// 所以如果用n个val构造，要类型提升int提升为size_t
	// 迭代器区间构造不用提升，可以直接用，所以会用
	// 迭代器区间构造
	wind::vector<int> v(10, 0);

	for (auto e : v)
	{
		std::cout << e << " ";
	}
	std::cout << std::endl;
}

int main()
{
	realization9();
	return 0;
}