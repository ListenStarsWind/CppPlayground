#include"template.h"

void test1()
{
	int i = add(4, 5);
	std::cout << i << std::endl;
}

int main()
{
	test<int> t;
	t.push(1);
	return 0;
}