#pragma once

#include<stdlib.h>
#include<iostream>


namespace wind
{
	template<class SDate>
	class Stack
	{
	public:
		Stack(size_t sz = 4, SDate* pArr = nullptr);
		~Stack();
		Stack(const Stack& s);
		Stack& operator=(const Stack& s);
		void Push(int val);
		void Extend();
		void Print()const;
	private:
		SDate* _val;
		size_t _top;
		size_t _capacity;
	};
}

template<class SDate>
wind::Stack<SDate>::Stack(size_t sz, SDate* pArr)
{
	_capacity = sz;
	if (pArr == nullptr)
	{
		SDate* p = (SDate*)realloc(pArr, sizeof(SDate) * _capacity);
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

template<class SDate>
wind::Stack<SDate>::~Stack()
{
	free(_val);
	_val = nullptr;
	_top = _capacity = 0;

}

template<class SDate>
wind::Stack<SDate>::Stack(const Stack& s)
{
	_capacity = s._capacity;
	_top = s._top;
	SDate* p = (SDate*)realloc(nullptr, sizeof(SDate) * _capacity);
	if (p == nullptr)
	{
		perror("Error: Copy fail");
		return;
	}
	memcpy(p, s._val, sizeof(SDate) * _top);
	_val = p;
}

template<class SDate>
wind::Stack<SDate>& wind::Stack<SDate>::operator=(const Stack& s)
{
	SDate* p = (SDate*)realloc(_val, sizeof(SDate) * s._capacity);
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

template<class SDate>
void wind::Stack<SDate>::Push(int val)
{
	if (_top == _capacity)
	{
		Extend();
	}

	_val[_top++] = val;
}

template<class SDate>
void wind::Stack<SDate>::Extend()
{
	size_t NewCapacity = _capacity == 0 ? 4 : _capacity * 2;
	SDate* p = (SDate*)realloc(_val, sizeof(SDate) * NewCapacity);
	if (p == nullptr)
	{
		perror("Error: Align fail");
		return;
	}
	_val = p;
	_capacity = NewCapacity;
}

template<class SDate>
void wind::Stack<SDate>::Print()const
{
	size_t present = 0;
	for (; present < _top; present++)
	{
		std::cout << _val[present] << " ";
	}
	std::cout << std::endl;
}