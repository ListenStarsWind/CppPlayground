#pragma once

#include<iostream>

template<class T>
class SmartPtr
{
private:
	T* _ptr;
public:
	SmartPtr(T* ptr)
		:_ptr(ptr)
	{
	}

	~SmartPtr()
	{
		std::cout << "delete->" << _ptr << std::endl;
		delete _ptr;
	}

	T& operator*()
	{
		return *_ptr;
	}

	T* operator->()
	{
		return &(this->operator*());
	}

	SmartPtr(SmartPtr<T>& that)
		:_ptr(that._ptr)
	{
		// 在此种场景下, 智能指针对于指针的托管权是互斥关系
		// 一个智能指针获得托管权, 意味着另一个失去
		that._ptr = nullptr;
	}

	SmartPtr<T>& operator=(SmartPtr<T>& that)
	{
		// 由于只有一个_ptr, 所以对之前指针的托管权相当于被覆盖了
		_ptr = that._ptr;
		that._ptr = nullptr;
	}
};

