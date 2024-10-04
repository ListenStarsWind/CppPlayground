#include"A.h"

wind::A::A(int i, int& j)
	:_a(i)
	,_b(j)
{}

std::ostream& wind::operator<<(std::ostream& out, const wind::A& m)
{
	out << m._a << " " << m._b;
	return out;
}

void wind::A::F()
{
	_b++;
}