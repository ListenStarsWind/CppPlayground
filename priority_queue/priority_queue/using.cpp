#include<queue>
#include<iostream>
#include<algorithm>
#include"priority_queue.h"

using namespace std;

void using1()
{
	//priority_queue<int, vector<int>> pq;
	wind::priority_queue<int, vector<int>, greater<int>> pq;

	pq.push(3);
	pq.push(7);
	pq.push(1);
	pq.push(8);
	pq.push(2);

	while (!pq.empty())
	{
		cout << pq.top() << " ";
		pq.pop();
	}
	cout << endl;
}

void using2()
{
	wind::less<int> cmp;
	cout << cmp.operator()(1, 2) << endl;
}

void using3()
{
	int arr[] = {6, 5, 9, 4, 2};
	size_t sz = sizeof(arr) / sizeof(arr[0]);
	sort(arr, arr + sz, greater<int>());
	//sort(arr, arr + sz);
	for (auto e : arr)
	{
		cout << e << " ";
	}
	cout << endl;
}

void using4()
{
	std::vector<int> v;
	v.push_back(3);
	v.push_back(7);
	v.push_back(1);
	v.push_back(8);
	v.push_back(2);

	wind::priority_queue<int> pq(v.begin(), v.end());

	while (!pq.empty())
	{
		cout << pq.top() << " ";
		pq.pop();
	}
	cout << endl;
}

//int main()
//{
//	using4();
//	return 0;
//}