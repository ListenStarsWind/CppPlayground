#include"AVLTree.h"
#include<string>
#include<vector>
#include<ctime>

using namespace std;

int main()
{
	//vector<int> v = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };
	vector<int> v;
	//srand(time(0));
	for (size_t i = 0; i < 100000; ++i)
	{
		v.push_back(rand());
	}

	wind::AVLTree<int, int> ts;
	for (const auto& i : v)
	{
		ts.Insert(make_pair(i, 0));
	}

	for (size_t pos = 0; pos < v.size(); pos++)
	{
		cout << "正在测试第" << pos << "个数" << endl;
		int i = v[pos];
		ts.erase(i);

		// 针对测试
		//if (pos == 35)
		//{
		//	//printf("Debug\n");
		//	cout << ts.isAVLTree() << endl;
		//	const char* str = "Debug";
		//	/*auto vs = ts.InOrder();

		// 全局测试
		if (!ts.isAVLTree())
		{
			cout << i << endl;
			cout << pos << endl;
			while (1);
		}
	}

	cout << "Celebrate!\n" << endl;

	return 0;
}