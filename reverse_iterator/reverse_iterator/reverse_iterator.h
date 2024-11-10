#pragma once

#include"version_control.h"
template<class iterator, class reference, class pointer>
class __reverse_iterator
{
	typedef __reverse_iterator<iterator, reference, pointer> self;
public:
	__reverse_iterator(iterator it)
		:_it(it)
	{}

	__reverse_iterator(const self& obj)
		:_it(obj._it)
	{}

	~__reverse_iterator() {}

	self& operator++()
	{
		--_it;
		return *this;
	}

	self& operator--()
	{
		++_it;
		return *this;
	}


#ifdef USING_SGI_STYLE

	reference operator*()const
	{
		iterator it = _it;
		--it;
		return *it;
	}

	pointer operator->()const
	{
		return &(operator*());
	}

#else

	reference operator*()const
	{
		return *_it;
	}

	pointer operator->()const
	{
		//return &(operator*());
		return _it.operator->();
	}

#endif

	bool operator==(const self& obj)const
	{
		return _it == obj._it;
	}

	bool operator!=(const self& obj)const
	{
		if (*this == obj)
			return false;
		else
			return true;
	}

private:
	iterator _it;
};