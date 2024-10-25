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

		// ʹ��ģ����������������ĳ�ʼ��
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

		// ��ӣ������ʵ��������
		// vector<int> v(0,10)
		// ��ȥ���������乹��
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

		// ������������,����int long ֮��
		// ��ʱ�������������,�ȵ��������������
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
		// ��ӣ����ǳ���������صú����ǳ����
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
		//			// ʹ�ù��캯������
		//			new(constructor) T(v);
		//			++constructor;
		//		}
		//		delete[] _start;
		//		_start = ptr;
		//		_finish = _start + oldSize;
		//		_endofstarage = _start + newCapacity;
		//	}
		//}

		// ����õ��ǡ�string_lesson2����SGI string���ü���
		// Ч�ʻ���ߣ�����ֱ�����
		// �Ժ��˵һ����Ϊ���ƶ����족���﷨
		// Ҳ������Ч��
		// ������Ϊ��ѧ�ߣ�û��Ҫ׷��Ч��
		void reserve(size_t newCapacity) {
			if (newCapacity > capacity()) {
				const size_t oldSize = size();
				iterator ptr = new T[newCapacity];
				for (size_t transport = 0; transport < oldSize; transport++) {
					// ʹ��operator=�������
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

		// ========================================= �Ϸ�Ϊ��һ�׶�

		// ģ������������Զ������ͣ�����Ҫʹ�ö�Ӧ��Ĭ�Ϲ��캯��
		// �������Ч�ʣ�const����ʵ�Σ��Լ�ê����ʱ����
		// ������������Ҳ������Ϊ�й��캯��
		// ��ǰ��˵��Ϊ�����߼�����Ǣ
		// �������Զ���������ʾ��ʾ
		void resize(size_t n, const T& val = T()) {
			if (size() < n) {
				// ��֤���㹻�Ŀռ�
				reserve(n);
				while (size() != n) {
					push_back(val);
				}
			}
			else {
				_finish = _start + n;
			}
		}

		// ��ӣ� ������ʧЧ����
		// ʧЧ������δ��������

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

		//// Ϊ��ʱ��transportҲ�ܼ���
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

		// ����ʹ�õ�������������ʽ����Ϊ�ܶ����������begin��end�ӿڷ��س�����
		// ���г����ԣ�Ȩ�޻�Ŵ󣬼�const��Ĳ��ˣ�����ʲô���øı�
		// ��һ������ջ֡������
		// Ȼ��˵һ˵C++��׼��ô�ֲ�����µģ���һ������ֵ����һ������������
		// ������ʧЧ�����ڲ�
		iterator insert(iterator pos, const T& val) {
			assert(pos >= _start && pos <= _finish);
			if (size() == capacity()) {
				size_t n = pos - _start;
				size_t newCapacity = capacity() * 2;
				if (empty()) {
					newCapacity = 4;
				}
				reserve(newCapacity);
				// ����֮�󣬵�����ʧЧ����Ҫ��������
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