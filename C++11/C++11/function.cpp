#include<iostream>
#include<vector>
#include<algorithm>
#include<functional>
#include<map>

using namespace std;

//// 商品类
//struct product
//{
//	string _name;   // 名字
//	double _price;  // 价格
//	int _rating;    // 评分
//
//	product(string name, double price, int rating)
//		:_name(name)
//		, _price(price)
//		, _rating(rating)
//	{
//	}
//};
//
//// 价格更低更好?
//struct CompareByPrice
//{
//	bool operator()(const product& lhs, const product& rhs)
//	{
//		return lhs._price < rhs._price;
//	}
//};
//
//// 亦或者综合评分更高更好?
//struct CompareByRating
//{
//	bool operator()(const product& lhs, const product& rhs)
//	{
//		return lhs._rating > rhs._rating;
//	}
//};

//int main()
//{
//	// 实例化一批商品对象，存储在一个 vector 中
//	vector<product> products =
//	{
//		product("手机", 2999.99, 85),    
//		product("笔记本", 5999.50, 92),  
//		product("耳机", 199.00, 78),     
//		product("充电器", 59.90, 65)     
//	};
//
//	sort(products.begin(), products.end(), CompareByPrice());
//	sort(products.begin(), products.end(), CompareByRating());
//
//	return 0;
//}

//struct functor
//{
//	int operator()(int x)
//	{
//		cout << x << endl;
//		return x;
//	}
//};
//
//int main()
//{
//	// 一个被实例化的lambda表达式
//	[](int x)->int {cout << x << endl; return 0; };
//
//	// 直接调用
//	[](int x)->int {cout << x << endl; return 0; }(123);
//
//	// 用lambda表达式实例化一个有名变量
//	auto f1 = [](int x)->int {cout << x << endl; return 0; };
//	auto f2 = functor();
//	f1(123);
//
//	f2(123);
//
//	return 0;
//}

//int main()
//{
//	// 实例化一批商品对象，存储在一个 vector 中
//	vector<product> products =
//	{
//		product("手机", 2999.99, 85),    
//		product("笔记本", 5999.50, 92),  
//		product("耳机", 199.00, 78),     
//		product("充电器", 59.90, 65)     
//	};
//
//	auto products1 = products;
//
//	auto f1 = [](const product& lhs, const product& rhs) {return lhs._rating > rhs._rating; };
//	auto f2 = [](const product& lhs, const product& rhs) {return lhs._rating > rhs._rating; };
//	auto f3 = [](const product& lhs, const product& rhs) {return lhs._rating > rhs._rating; };
//
//	sort(products.begin(), products.end(), CompareByRating());
//	sort(products1.begin(), products1.end(), f1);
//	
//	cout << typeid(CompareByRating).name() << endl;
//	cout << typeid(f1).name() << endl;
//	cout << typeid(f2).name() << endl;
//	cout << typeid(f3).name() << endl;
//
//	return 0;
//}

//

//int main()
//{
//	int x = -1, y = 0, z = 1;
//	auto f1 = [=, &z]()
//		{
//			cout << x << endl;
//			cout << y << endl;
//			cout << z << endl;
//			++z;
//		};
//	f1();
//	cout << z << endl;
//	return 0;
//}


//class A
//{
//private:
//	int i = 4;
//	int j = 2;
//
//public:
//	void func()
//	{
//		// '='不能直接捕捉到成员变量
//		// 因为其不在func的作用域内
//		// 但可以捕捉到this指针
//		// 从而间接捕捉到成员变量
//		auto f1 = [=]()
//			{
//				cout << i << endl;
//				cout << j << endl;
//			};
//
//		f1();
//	}
//};

//
//
//void Swap1(int& x, int& y)
//{
//	int temp = x;
//	x = y;
//	y = temp;
//}
//
//struct Swap2
//{
//	void operator()(int& x, int& y)
//	{
//		int temp = x;
//		x = y;
//		y = temp;
//	}
//};
//
//int main()
//{
//	function<void(int&, int&)> swap3 = [](int& x, int& y)
//		{
//			int temp = x;
//			x = y;
//			y = temp;
//		}; 
//
//	decltype(swap3) swap2 = Swap2();
//	decltype(swap3) swap1 = Swap1;
//
//	int x = 1, y = 2;
//	cout << x << " " << y << endl;
//	swap1(x, y);
//	cout << x << " " << y << endl;
//	swap2(x, y);
//	cout << x << " " << y << endl;
//	swap3(x, y);
//	cout << x << " " << y << endl;
//
//	// 通过指令执行特定命令
//	map<string, function<void(int&, int&)>> cmds;
//	cmds.emplace("函数指针", swap1);
//	cmds.emplace("仿函数", swap1);
//	cmds.emplace("lambda", swap1);
//
//
//	cmds["函数指针"](x, y);
//	cout << x << " " << y << endl;
//	cmds["仿函数"](x, y);
//	cout << x << " " << y << endl;
//	cmds["lambda"](x, y);
//	cout << x << " " << y << endl;
//
//	
//
//	return 0;
//}

//class Plus
//{
//public:
//	static int plusi(int a, int b)
//	{
//		return a + b;
//	}
//
//	double plusd(double a, double b)
//	{
//		return a + b;
//	}
//};

//int main()
//{
//	// 对于类中的成员函数来说,使用function包装时
//	// 首先要能突破类域,   其次前面要加`&`
//	// 加`&`是为了特别区分成员函数和普通函数
//	// 因为成员函数一般有this指针
//	function<int(int, int)> f1 = &Plus::plusi;
//
//	// 静态成员函数没有this指针, 
//	// 所以前面不需要加类指针
//	// 也可以不加`&`, 不过还是建议加上
//	function<double(Plus*, double, double)> f2 = &Plus::plusd;
//
//	cout << f1(1, 2) << endl;
//	Plus ps;
//	cout << f2(&ps, 1.1, 2.2) << endl;
//
//	// 其实也可以不用类指针类型, 只要能传进去对象就行了, 不在乎具体形式
//	function<double(Plus&, double, double)> f3 = &Plus::plusd;
//	cout << f3(ps, 1.1, 2.2) << endl;
//
//	// 对于右值, 自然使用右值引用
//	function<double(Plus&&, double, double)> f4 = &Plus::plusd;
//	cout << f4(Plus(), 1.1, 2.2) << endl;
//
//	// 传指针就相当于->, 传引用就相当于.
//
//
//	function<double(double, double)> f5 = bind(&Plus::plusd, Plus(), placeholders::_1, placeholders::_2);
//	cout << f5(1.1, 2.2) << endl;
//
//	return 0;
//}


//int Sub(int x, int y)
//{
//	return x - y;
//}
//
//int main()
//{
//	function<int(int, int)> f1 = Sub;
//	cout << f1(10, 50) << endl;
//
//	function<int(int, int)> f2 = bind(Sub, placeholders::_2, placeholders::_1);
//	cout << f2(10, 50) << endl;
//
//	// bind就是建立一个中间层
//	// 10 传给了 `_2`这个参数
//	// 50 传给了 `_1`这个参数
//	// `_2`是原始接口的第二个参数
//	// `_1`是原始接口的第一个参数
//
//	// 这相当于把x固定为20
//	// 在此基础上, y就变成了`-1`
//	function<int(int)> f3 = bind(Sub, 20, placeholders::_1);
//	cout << f3(50) << endl;
//
//	
//
//	return 0;
//}

int subtract(int x, int y)
{
	return x - y;
}

void func(int i, int j, int k)
{
	cout << i << endl;
	cout << j << endl;
	cout << k << endl;
}


int main()
{
	auto f1 = bind(subtract, placeholders::_1, placeholders::_2);
	// 不探讨bind的返回类型
	cout << typeid(f1).name() << endl;


	// 此处的`_1`和`_2`是占位符, 其具体数值与绑定后的接口相对应
	function<int(int, int)> f2 = bind(subtract, placeholders::_1, placeholders::_2);
	// 第一个实参对应`_1`, 第二个实参对应`_2`
	cout << f2(4, 8) << endl;
	function<int(int, int)> f3 = bind(subtract, placeholders::_2, placeholders::_1);
	// `_1`和`_2`在bind中的位置对应形参的位置
	// `_2`在前, 对应第一个形参, `_1`在后, 对应第二个形参
	cout << f3(4, 8) << endl;

	// 亦可以把中间位置的形参写死
	function<void(int, int)> f4 = bind(func, placeholders::_1, 10, placeholders::_2);
	f4(1, 2);

	return 0;
}