#pragma once

#include<string.h>
#include<assert.h>
#include"reverse_iterator.h"
#include"version_control.h"

namespace wind {
	template<class T>
	class vector {
		typedef T value_type;
		typedef T& reference;
		typedef T* pointer;

		typedef const T& const_reference;
		typedef const T* const_pointer;

	public:
		typedef T* iterator;
		typedef const T* const_iterator;

		typedef __reverse_iterator<iterator, reference, pointer> reverse_iterator;
		typedef __reverse_iterator<const_iterator, const_reference, const_pointer> const_reverse_iterator;


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

#ifdef USING_SGI_STYLE

		reverse_iterator rbegin()
		{
			return reverse_iterator(end());
		}

		reverse_iterator rend()
		{
			return reverse_iterator(begin());
		}

		const_reverse_iterator rbegin()const
		{
			return const_reverse_iterator(end());
		}

		const_reverse_iterator rend()const
		{
			return const_reverse_iterator(begin());
		}

#else

		reverse_iterator rbegin()
		{
			iterator it = end();
			return reverse_iterator(--it);
		}

		reverse_iterator rend()
		{
			iterator it = begin();
			return reverse_iterator(--it);
		}

		const_reverse_iterator rbegin()const
		{
			const_iterator it = end();
			return const_reverse_iterator(--it);
		}

		const_reverse_iterator rend()const
		{
			const_iterator it = begin();
			return const_reverse_iterator(--it);
		}

#endif

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

		void reserve(size_t newCapacity) {
			if (newCapacity > capacity()) {
				const size_t oldSize = size();
				iterator ptr = new T[newCapacity];
				for (size_t transport = 0; transport < oldSize; transport++) {
					ptr[transport] = _start[transport];
				}
				delete[] _start;
				_start = ptr;
				_finish = _start + oldSize;
				_endofstarage = _start + newCapacity;
			}
		}

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

		void resize(size_t n, const T& val = T()) {
			if (size() < n) {
				reserve(n);
				while (size() != n) {
					push_back(val);
				}
			}
			else {
				_finish = _start + n;
			}
		}

		iterator insert(iterator pos, const T& val) {
			assert(pos >= _start && pos <= _finish);
			if (size() == capacity()) {
				size_t n = pos - _start;
				size_t newCapacity = capacity() * 2;
				if (empty()) {
					newCapacity = 4;
				}
				reserve(newCapacity);
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

		
	private:
		iterator _start = nullptr;
		iterator _finish = nullptr;
		iterator _endofstarage = nullptr;
	};
}