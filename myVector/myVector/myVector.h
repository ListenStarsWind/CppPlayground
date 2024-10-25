#pragma once

#include<string.h>
#include<assert.h>

namespace wind {
	template<class T>
	class vector {
	public:
		typedef T* iterator;
		typedef const T* const_iterator;

		//---
		vector()
			:_start(nullptr)
			, _finish(nullptr)
			, _endofstarage(nullptr)
		{}

		vector(const vector& v)
			:_start(nullptr)
		    ,_finish(nullptr)
			,_endofstarage(nullptr)
		{
			const iterator ptr = new T[v.capacity()];
			iterator transport = ptr;
			for (const auto& e : v) {
				new(transport++) T(e);
			}
			_start = ptr;
			_finish = _start + v.size();
			_endofstarage = _start + v.capacity();
		}

		// 使用模版便于其它迭代器的初始化
		template<class InputIterator>
		vector(InputIterator begin, InputIterator end)
			:_start(nullptr)
			, _finish(nullptr)
			, _endofstarage(nullptr)
		{
			while (begin != end) {
				push_back(*begin);
				++begin;
			}
		}

		// 大坑：错误的实例化方向
		// vector<int> v(0,10)
		// 会去迭代器区间构造
		vector(size_t n, const T& val)
			:_start(nullptr)
			, _finish(nullptr)
			, _endofstarage(nullptr)
		{
			const iterator ptr = new T[n];
			_start = ptr;
			_finish = _start + n;
			_endofstarage = _start + n;
			iterator constructor = ptr;
			while (constructor < _finish) {
				new(constructor++) T(val);
			}
		}

		// 多整几个类型,比如int long 之类
		// 此时就这个更适配了,比迭代器区间更合适
		vector(int n, const T& val)
			:_start(nullptr)
			, _finish(nullptr)
			, _endofstarage(nullptr)
		{
			const iterator ptr = new T[n];
			_start = ptr;
			_finish = _start + n;
			_endofstarage = _start + n;
			iterator constructor = ptr;
			while (constructor < _finish) {
				new(constructor++) T(val);
			}
		}

		void swap(vector& v) {
			std::swap(_start, v._start);
			std::swap(_finish, v._finish);
			std::swap(_endofstarage, v._endofstarage);
		}

		vector& operator=(vector v) {
			swap(v);
			return *this;
		}

		// ---
		~vector() {
			delete[] _start;
			_start = _finish = _endofstarage = nullptr;
		}

		size_t size() {
			return _finish - _start;
		}

		size_t capacity() {
			return _endofstarage - _start;
		}

		size_t size()const {
			return _finish - _start;
		}

		size_t capacity()const {
			return _endofstarage - _start;
		}

		iterator begin() {
			return _start;
		}

		iterator end() {
			return _finish;
		}

		const_iterator begin()const {
			return _start;
		}

		const_iterator end()const {
			return _finish;
		}

		bool empty() {
			if (begin() == end())
				return true;
			else
				return false;
		}

		bool empty()const {
			if (begin() == end())
				return true;
			else
				return false;
		}

		// ---
		// 大坑：深层浅拷贝——藏得很深的浅拷贝
		/*void reserve(size_t newCapacity) {
			if (newCapacity > capacity()) {
				size_t oldSize = size();
				iterator ptr = new T[newCapacity];
				memcpy(ptr, _start, sizeof(T) * oldSize);
				delete[] _start;
				_start = ptr;
				_finish = _start + oldSize;
				_endofstarage = _start + newCapacity;
			}
		}*/


		//void reserve(size_t newCapacity) {
		//	if (newCapacity > capacity()) {
		//		size_t oldSize = size();
		//		iterator ptr = new T[newCapacity];
		//		iterator constructor = ptr;
		//		for (auto& v : *this) {
		//			// 使用构造函数构造
		//			new(constructor) T(v);
		//			++constructor;
		//		}
		//		delete[] _start;
		//		_start = ptr;
		//		_finish = _start + oldSize;
		//		_endofstarage = _start + newCapacity;
		//	}
		//}

		// 如果用的是《string_lesson2》的SGI string引用计数
		// 效率会更高，不会直接深拷贝
		// 以后会说一种名为“移动构造”的语法
		// 也能提升效率
		// 不过作为初学者，没必要追求效率
		void reserve(size_t newCapacity) {
			if (newCapacity > capacity()) {
				const size_t oldSize = size();
				iterator ptr = new T[newCapacity];
				for (size_t transport = 0; transport < oldSize; transport++) {
					// 使用operator=重载深拷贝
					ptr[transport] = _start[transport];
				}
				delete[] _start;
				_start = ptr;
				_finish = _start + oldSize;
				_endofstarage = _start + newCapacity;
			}
		}

		// ---
		void push_back(const T& val) {
			if (size() == capacity()) {
				size_t newCapacity = capacity() * 2;
				if (empty()) {
					newCapacity = 4;
				}
				reserve(newCapacity);
			}
			*_finish = val;
			++_finish;
		}

		// ========================================= 上方为第一阶段

		// 模版可能是其它自定义类型，所以要使用对应的默认构造函数
		// 引用提高效率，const保护实参，以及锚定临时对象
		// 所以内置类型也可以认为有构造函数
		// 以前不说是为了让逻辑更自洽
		// 找两个自定义类型演示演示
		void resize(size_t n, const T& val = T()) {
			if (size() < n) {
				// 保证有足够的空间
				reserve(n);
				while (size() != n) {
					push_back(val);
				}
			}
			else {
				_finish = _start + n;
			}
		}

		// 大坑： 迭代器失效问题
		// 失效：产生未定义问题

		/*iterator insert(iterator pos, const T& val) {
			assert(pos >= _start && pos <= _finish);
			if (empty()) {
				push_back(val);
				return pos;
			}
			else {
				if (size() == capacity()) {
					size_t newCapacity = capacity() * 2;
					reserve(newCapacity);
				}
				iterator transport = _finish - 1;
				while (pos <= transport) {
					*(transport + 1) = *transport;
					--transport;
				}
				*pos = val;
				++_finish;
				return pos;
			}
		}*/

		//// 为空时，transport也能兼容
		//iterator insert(iterator pos, const T& val) {
		//	assert(pos >= _start && pos <= _finish);
		//	if (size() == capacity()) {
		//		size_t newCapacity = capacity() * 2;
		//		if (empty()) {
		//			newCapacity = 4;
		//		}
		//		reserve(newCapacity);
		//	}
		//	iterator transport = _finish - 1;
		//	while (pos <= transport) {
		//		*(transport + 1) = *transport;
		//		--transport;
		//	}
		//	*pos = val;
		//	++_finish;
		//	return pos;
		//}

		// 不能使用迭代器的引用形式，因为很多迭代器都是begin和end接口返回出来的
		// 具有常属性，权限会放大，加const会改不了，那用什么引用改变
		// 上一级函数栈帧迭代器
		// 然后说一说C++标准怎么弥补这件事的：给一个返回值供上一级迭代器修正
		// 迭代器失效——内部
		iterator insert(iterator pos, const T& val) {
			assert(pos >= _start && pos <= _finish);
			if (size() == capacity()) {
				size_t n = pos - _start;
				size_t newCapacity = capacity() * 2;
				if (empty()) {
					newCapacity = 4;
				}
				reserve(newCapacity);
				// 扩容之后，迭代器失效，需要重新修正
				pos = _start + n;
			}
			iterator transport = _finish - 1;
			while (pos <= transport) {
				*(transport + 1) = *transport;
				--transport;
			}
			*pos = val;
			++_finish;
			return pos;
		}

		iterator erase(iterator pos) {
			assert(pos>= _start && pos < _finish);
			iterator transport = pos + 1;
			while (transport <= _finish) {
				*(transport - 1) = *transport;
				++transport;
			}
			--_finish;
			return pos;
		}

		/*iterator<T> erase(iterator begin, iterator end) {
			
		}*/

	private:
		iterator _start = nullptr;
		iterator _finish = nullptr;
		iterator _endofstarage = nullptr;
	};
}