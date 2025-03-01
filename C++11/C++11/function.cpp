#include<iostream>
#include<vector>
#include<algorithm>
#include<functional>
#include<map>

using namespace std;

//// ��Ʒ��
//struct product
//{
//	string _name;   // ����
//	double _price;  // �۸�
//	int _rating;    // ����
//
//	product(string name, double price, int rating)
//		:_name(name)
//		, _price(price)
//		, _rating(rating)
//	{
//	}
//};
//
//// �۸���͸���?
//struct CompareByPrice
//{
//	bool operator()(const product& lhs, const product& rhs)
//	{
//		return lhs._price < rhs._price;
//	}
//};
//
//// ������ۺ����ָ��߸���?
//struct CompareByRating
//{
//	bool operator()(const product& lhs, const product& rhs)
//	{
//		return lhs._rating > rhs._rating;
//	}
//};

//int main()
//{
//	// ʵ����һ����Ʒ���󣬴洢��һ�� vector ��
//	vector<product> products =
//	{
//		product("�ֻ�", 2999.99, 85),    
//		product("�ʼǱ�", 5999.50, 92),  
//		product("����", 199.00, 78),     
//		product("�����", 59.90, 65)     
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
//	// һ����ʵ������lambda���ʽ
//	[](int x)->int {cout << x << endl; return 0; };
//
//	// ֱ�ӵ���
//	[](int x)->int {cout << x << endl; return 0; }(123);
//
//	// ��lambda���ʽʵ����һ����������
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
//	// ʵ����һ����Ʒ���󣬴洢��һ�� vector ��
//	vector<product> products =
//	{
//		product("�ֻ�", 2999.99, 85),    
//		product("�ʼǱ�", 5999.50, 92),  
//		product("����", 199.00, 78),     
//		product("�����", 59.90, 65)     
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
//		// '='����ֱ�Ӳ�׽����Ա����
//		// ��Ϊ�䲻��func����������
//		// �����Բ�׽��thisָ��
//		// �Ӷ���Ӳ�׽����Ա����
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
//	// ͨ��ָ��ִ���ض�����
//	map<string, function<void(int&, int&)>> cmds;
//	cmds.emplace("����ָ��", swap1);
//	cmds.emplace("�º���", swap1);
//	cmds.emplace("lambda", swap1);
//
//
//	cmds["����ָ��"](x, y);
//	cout << x << " " << y << endl;
//	cmds["�º���"](x, y);
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
//	// �������еĳ�Ա������˵,ʹ��function��װʱ
//	// ����Ҫ��ͻ������,   ���ǰ��Ҫ��`&`
//	// ��`&`��Ϊ���ر����ֳ�Ա��������ͨ����
//	// ��Ϊ��Ա����һ����thisָ��
//	function<int(int, int)> f1 = &Plus::plusi;
//
//	// ��̬��Ա����û��thisָ��, 
//	// ����ǰ�治��Ҫ����ָ��
//	// Ҳ���Բ���`&`, �������ǽ������
//	function<double(Plus*, double, double)> f2 = &Plus::plusd;
//
//	cout << f1(1, 2) << endl;
//	Plus ps;
//	cout << f2(&ps, 1.1, 2.2) << endl;
//
//	// ��ʵҲ���Բ�����ָ������, ֻҪ�ܴ���ȥ���������, ���ں�������ʽ
//	function<double(Plus&, double, double)> f3 = &Plus::plusd;
//	cout << f3(ps, 1.1, 2.2) << endl;
//
//	// ������ֵ, ��Ȼʹ����ֵ����
//	function<double(Plus&&, double, double)> f4 = &Plus::plusd;
//	cout << f4(Plus(), 1.1, 2.2) << endl;
//
//	// ��ָ����൱��->, �����þ��൱��.
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
//	// bind���ǽ���һ���м��
//	// 10 ������ `_2`�������
//	// 50 ������ `_1`�������
//	// `_2`��ԭʼ�ӿڵĵڶ�������
//	// `_1`��ԭʼ�ӿڵĵ�һ������
//
//	// ���൱�ڰ�x�̶�Ϊ20
//	// �ڴ˻�����, y�ͱ����`-1`
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
	// ��̽��bind�ķ�������
	cout << typeid(f1).name() << endl;


	// �˴���`_1`��`_2`��ռλ��, �������ֵ��󶨺�Ľӿ����Ӧ
	function<int(int, int)> f2 = bind(subtract, placeholders::_1, placeholders::_2);
	// ��һ��ʵ�ζ�Ӧ`_1`, �ڶ���ʵ�ζ�Ӧ`_2`
	cout << f2(4, 8) << endl;
	function<int(int, int)> f3 = bind(subtract, placeholders::_2, placeholders::_1);
	// `_1`��`_2`��bind�е�λ�ö�Ӧ�βε�λ��
	// `_2`��ǰ, ��Ӧ��һ���β�, `_1`�ں�, ��Ӧ�ڶ����β�
	cout << f3(4, 8) << endl;

	// ����԰��м�λ�õ��β�д��
	function<void(int, int)> f4 = bind(func, placeholders::_1, 10, placeholders::_2);
	f4(1, 2);

	return 0;
}