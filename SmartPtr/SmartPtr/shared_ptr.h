#pragma once

#include<functional>
#include<atomic>

namespace wind
{
	template<class T>
	class shared_ptr
	{
	private:
		T* _ptr;
		std::function<void(T*)> _del = [](T* ptr) {delete ptr; };
		std::atomic<size_t>* _count;
		inline void release_control()
		{
			if (--*_count == 0)
			{
				_del(_ptr);
				delete _count;
			}
		}

	public:
		shared_ptr()
			:_ptr(nullptr)
			, _del([](T* ptr) {delete ptr; })
			, _count(new std::atomic<size_t>(1))
		{
		}

		template<class Del>
		shared_ptr(T* ptr, Del del)
			:_ptr(ptr)
			, _del(del)
			, _count(new std::atomic<size_t>(1))
		{
		}

		shared_ptr(T* ptr)
			:_ptr(ptr)
			, _count(new std::atomic<size_t>(1))
		{
		}

		shared_ptr(const shared_ptr<T>& that)
			:_ptr(that._ptr)
			, _count(that._count)
		{
			++*_count;
		}

		~shared_ptr()
		{
			release_control();
		}

		shared_ptr<T>& operator=(const shared_ptr<T>& that)
		{
			if (_ptr != that._ptr)
			{
				release_control();

				_ptr = that._ptr;
				_count = that._count;
				++*_count;
			}
			return *this;
		}

		T& operator*()
		{
			return *_ptr;
		}

		T* operator->()
		{
			return &(this->operator*());
		}

		T* get()const
		{
			return _ptr;
		}

		size_t use_count()const
		{
			return *_count;
		}
	};

	template<class T>
	class weak_ptr
	{
	private:
		T* _ptr;
	public:
		weak_ptr()
			:_ptr(nullptr)
		{
		}

		weak_ptr(const shared_ptr<T>& that)
			:_ptr(that.get())
		{
		}

		weak_ptr<T>& operator=(const shared_ptr<T>& that)
		{
			_ptr = that.get();
			return *this;
		}

		T& operator*()
		{
			return *_ptr;
		}

		T* operator->()
		{
			return &(this->operator*());
		}
	};
}