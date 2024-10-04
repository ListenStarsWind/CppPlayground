#include"Stack.h"

wind::Stack::Stack(size_t sz, pSDate pArr)
{
	_capacity = sz;
	if (pArr == nullptr)
	{
		pSDate p = (pSDate)realloc(pArr, sizeof(SDate) * _capacity);
		if (p == nullptr)
		{
			perror("Error: Bulid fail");
			exit(-1);
		}
		_val = p;
		_top = 0;
	}
	else
	{
		_val = pArr;
		_top = _capacity;
	}
}

wind::Stack::~Stack()
{
	free(_val);
	_val = nullptr;
	_top = _capacity = 0;

}

wind::Stack::Stack(const Stack & s)
{
	_capacity = s._capacity;
	_top = s._top;
	pSDate p = (pSDate)realloc(nullptr, sizeof(SDate) * _capacity);
	if (p == nullptr)
	{
		perror("Error: Copy fail");
		return;
	}
	memcpy(p, s._val, sizeof(SDate) * _top);
	_val = p;
}

wind::Stack& wind::Stack::operator=(const Stack& s)
{
	pSDate p = (pSDate)realloc(_val, sizeof(SDate) * s._capacity);
	if (p == nullptr)
	{
		perror("Error: Assign fail");
		return *this;
	}
	_capacity = s._capacity;
	_top = s._top;
	memcpy(p, s._val, sizeof(SDate) * _top);
	_val = p;
	return *this;
}

void wind::Stack::Push(int val)
{
	if (_top == _capacity)
	{
		Extend();
	}

	_val[_top++] = val;
}

void wind::Stack::Extend()
{
	size_t NewCapacity = _capacity == 0 ? 4 : _capacity * 2;
	pSDate p = (pSDate)realloc(_val, sizeof(SDate) * NewCapacity);
	if (p == nullptr)
	{
		perror("Error: Align fail");
		return;
	}
	_val = p;
	_capacity = NewCapacity;
}

void wind::Stack::Print()const
{
	size_t present = 0;
	for (; present < _top; present++)
	{
		std::cout << _val[present] << " ";
	}
	std::cout << std::endl;
}