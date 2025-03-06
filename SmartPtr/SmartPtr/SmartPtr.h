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
		// �ڴ��ֳ�����, ����ָ�����ָ����й�Ȩ�ǻ����ϵ
		// һ������ָ�����й�Ȩ, ��ζ����һ��ʧȥ
		that._ptr = nullptr;
	}

	SmartPtr<T>& operator=(SmartPtr<T>& that)
	{
		// ����ֻ��һ��_ptr, ���Զ�֮ǰָ����й�Ȩ�൱�ڱ�������
		_ptr = that._ptr;
		that._ptr = nullptr;
	}
};

