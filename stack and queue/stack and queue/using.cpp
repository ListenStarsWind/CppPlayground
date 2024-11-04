#include<iostream>
#include<stack>
#include<queue>
#include<list>
#include<algorithm>
#include"stack and queue.h"
using namespace std;

void stack_using1()
{
	wind::stack<int> s;
	s.push(1);
	s.push(2);
	s.push(3);
	s.push(4);
	s.push(5);

	while (!s.empty())
	{
		cout << s.top() << " ";
		s.pop();
	}
	cout << endl;
}

void queue_using1()
{
	wind::queue<int> q;
	q.push(1);
	q.push(2);
	q.push(3);
	q.push(4);

	while (!q.empty())
	{
		cout << q.front() << " ";
		q.pop();
	}
	cout << endl;
}

void using2(const int N)
{
	srand(time(0));

	std::deque<int> obj1, obj2;
	for (int i = 0; i < N; i++)
	{
		int e = rand();
		obj1.push_back(e);
		obj2.push_back(e);
	}

	int begin1 = clock();
	std::vector<int> v(obj1.begin(), obj1.end());
	std::sort(v.begin(), v.end());
	obj1.assign(v.begin(), v.end());
	int end1 = clock();

	int begin2 = clock();
	sort(obj2.begin(), obj2.end());
	int end2 = clock();

	std::cout << "deque->vector->deque:" << end1 - begin1 << "ms." << std::endl;
	std::cout << "deque:" << end2 - begin2 << "ms." << std::endl;
}

int main()
{
	queue_using1();
	return 0;
}