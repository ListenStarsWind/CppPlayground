#include"test.h"

void wind::a::init()
{
	a::_used = a::_using = 0;
}

void wind::a::out(int& ed, int& ing)
{
	ed = a::_used;
	ing = a::_using;
}

wind::a::a()

{
	++_used;
	++_using;
}

wind::a::a(const a& opject)

{
	++_used;
	++_using;
}

wind::a::~a()
{
	--_used;
}

void wind::f(wind::a project)
{
	wind::a x = project;
}

/////////////////////////////////////////////////

wind::A::A()
	:_i(0)
{
	std::cout << "Constructor" << std::endl;
}

wind::A::A(const A& opject)
	:_i(0)
{
	std::cout << "Copy Constructor" << std::endl;
}

wind::A::~A()
{
	std::cout << "Destructor" << std::endl;
}

void wind::F(A opject)
{
	opject.print();
}

void wind::A::print()const
{
	std::cout << _i << std::endl;
}

wind::A& wind::A::operator=(const A& opject)
{
	_i = opject._i;
	return *this;
}