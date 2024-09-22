#include"stack.h"

int main()
{
	wind::stack s;
	s.Init();
	int Array[] = { 2,4,6,8 };
	for (auto tem : Array)
	{
		s.push(tem);
	}
	while (!s.IsEmpty())
	{
		wind::stack_data val;
		s.ReadPop(val);
		std::cout << val << " ";
	}
	std::cout << std::endl;
	std::cout << sizeof(s) << std::endl;
	s.Dest();
}