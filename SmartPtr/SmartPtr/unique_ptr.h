#pragma once

#include<iostream>

namespace wind
{
	template<class T>
	class unique_ptr
	{
	private:
		T* _ptr;
	public:
		unique_ptr(T* ptr)
			:_ptr(ptr)
		{
		}

		~unique_ptr()
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

		unique_ptr(unique_ptr<T>& that) = delete;

		unique_ptr<T>& operator=(unique_ptr<T>& that) = delete;

	};
}