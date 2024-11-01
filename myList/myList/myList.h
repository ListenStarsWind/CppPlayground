#pragma once

#include<assert.h>
#include<algorithm>

namespace wind {

	// C++一般不用内部类
	// 所以采取先外部定义模版
	// 再typedef的策略
	// 为了方便别的类访问成员
	// 直接使用struct，全公有
	template<class T>
	struct __list_node_base {
		T _val;
		__list_node_base<T>* _prev;
		__list_node_base<T>* _next;

		__list_node_base(const T& val = T())
			:_val(val)
			, _prev(nullptr)
			, _next(nullptr)
		{}
	};

	//template<class T>
	//struct __list_iterator_base {
	//	typedef __list_node_base<T> node;
	//	node* _ptr;
	//	__list_iterator_base(node* ptr)
	//		:_ptr(ptr)
	//	{}

	//	__list_iterator_base(const __list_iterator_base& obj)
	//		:_ptr(obj._ptr)
	//	{}

	//	// 迭代器的成员是内置类型
	//	// 不用析构

	//	__list_iterator_base& operator++()
	//	{
	//		_ptr = _ptr->_next;
	//		return *this;
	//	}

	//	__list_iterator_base& operator++(int)
	//	{
	//		__list_iterator_base ret = *this;
	//		_ptr = _ptr->_next;
	//		return ret;
	//	}

	//	__list_iterator_base& operator--()
	//	{
	//		_ptr = _ptr->_prev;
	//		return *this;
	//	}

	//	__list_iterator_base& operator--(int)
	//	{
	//		__list_iterator_base ret = *this;
	//		_ptr = _ptr->_prev;
	//		return ret;
	//	}

	//	// 迭代器就像指针一样。
	//	// 对于内置数据类型，可以直接用*ptr来获取值。
	//	T& operator*() const
	//	{
	//		return _ptr->_val;
	//	}

	//	// 对于自定义类型来说，
	//	// 用(*ptr).member会显得有点繁琐，
	//	// 所以我们可以用ptr->member的方式来简化。

	//	// 既然迭代器模仿指针，
	//	// 自然也需要重载iterator->member的操作。

	//	// 不过这里是个模板，
	//	// 我们并不知道T是什么自定义类型，
	//	// 也不知道它有哪些成员以及这些成员的类型。
	//	// 所以不能直接用T->member的方式。

	//	// 那么，当我们重载迭代器的->操作时，
	//	// 怎么获取成员呢？

	//	// C++为此做了特别处理：
	//	// 在重载->操作时，只需返回T的指针。
	//	// 然后编译器会根据这个指针来找到对应的成员。

	//	// 比如，如果T是一个结构体 {int a; int b}; 
	//	// 当有人写iterator->a时，
	//	// 编译器会将其理解为T*->a。
	//	// 这个T*是从->重载中获取的。

	//	T* operator->()const
	//	{
	//		return &(_ptr->_val);
	//	}

	//	bool operator!=(const __list_iterator_base& obj)const
	//	{
	//		if (_ptr != obj._ptr)
	//			return true;
	//		else
	//			return false;
	//	}

	//	bool operator==(const __list_iterator_base& obj)const
	//	{
	//		if (*this != obj)
	//			return true;
	//		else
	//			return false;
	//	}
	//};

	template<class T, class ref, class ptr>
	struct __list_iterator_base {
		typedef __list_node_base<T> node;
		typedef __list_iterator_base<T, ref, ptr> self;

		node* _ptr;

		__list_iterator_base(node* ptr)
			:_ptr(ptr)
		{}

		__list_iterator_base(const self& obj)
			:_ptr(obj._ptr)
		{}

		self& operator++()
		{
			_ptr = _ptr->_next;
			return *this;
		}

		self& operator++(int)
		{
			self ret = *this;
			_ptr = _ptr->_next;
			return ret;
		}

		self& operator--()
		{
			_ptr = _ptr->_prev;
			return *this;
		}

		self& operator--(int)
		{
			self ret = *this;
			_ptr = _ptr->_prev;
			return ret;
		}

		ref operator*() const
		{
			return _ptr->_val;
		}

		ptr operator->()const
		{
			return &(_ptr->_val);
		}

		bool operator!=(const self& obj)const
		{
			if (_ptr != obj._ptr)
				return true;
			else
				return false;
		}

		bool operator==(const self& obj)const
		{
			if (*this != obj)
				return true;
			else
				return false;
		}
	};

	template<class T>
	class list {
		typedef __list_node_base<T> node;
		// 构造函数都要生成头结点
		// 所以干脆直接写成具体函数
		node* __init_head_node()
		{
			node* head = new node();
			head->_prev = head;
			head->_next = head;
			head->_val = T();
			return head;
		}
	public:
		// 迭代器要被外部使用，因而放在公共域
		typedef __list_iterator_base<T, T&, T*> iterator;
		typedef __list_iterator_base<T, const T&, const T*> const_iterator;

		list()
			:_head(__init_head_node())
			, _size(0)
		{}

		void push_back(const T& val)
		{
			node* oldTail = _head->_prev;
			node* newNode = new node(val);
			newNode->_next = _head;
			newNode->_prev = oldTail;
			oldTail->_next = newNode;
			_head->_prev = newNode;
			_size++;
		}

		// 第一次写昏头了
		// 顺手在后面加了个
		// const
		// 这样的话iterator
		// 就会被识别成const_lterator或iterator
		// 也就是说常对象也会往这里走
		iterator begin()
		{
			// 隐式类型转换
			return _head->_next;
		}

		iterator end()
		{
			return _head;
		}

		/*bool empty()
		{
			if (begin() == end())
				return true;
			else
				return false;
		}*/

		const_iterator begin()const
		{
			return _head->_next;
		}


		const_iterator end()const
		{
			return _head;
		}

		bool empty()const
		{
			if (begin() == end())
				return true;
			else
				return false;
		}

		/*size_t size()
		{
			return _size;
		}*/

		size_t size()const
		{
			return _size;
		}

		iterator insert(iterator pos, const T& val)
		{
			// iterator全公开直接访问
			node* curr = pos._ptr;
			node* prev = curr->_prev;
			node* newNode = new node(val);
			newNode->_prev = prev;
			newNode->_next = curr;
			curr->_prev = newNode;
			prev->_next = newNode;
			_size++;
			return newNode;
		}

		iterator erase(iterator pos)
		{
			assert(empty());
			node* curr = pos._ptr;
			node* prev = curr->_prev;
			node* next = curr->_next;
			prev->_next = next;
			next->_prev = prev;
			delete curr;
			_size--;
			// 修正外部失效迭代器
			return next;
		}

		void pop_back()
		{
			erase(--end());
		}

		void push_front(const T& val)
		{
			insert(begin(), val);
		}

		void pop_front()
		{
			erase(--end());
		}

		void clean()
		{
			list::iterator it = begin();
			while (it != end())
			{
				// 连着删除，迭代器失效
				// 使用返回值修正迭代器
				it = erase(it);
			}
		}

		~list()
		{
			clean();
			delete _head;
		}

		// 理论上应该用const list& l
		// 但还没写const_iterator 
		list(const list& l)
			:_head(__init_head_node())
			, _size(0)
		{
			// 常引用提升效率
			for (const auto& e : l)
			{
				push_back(e);
			}
		}

		// 与拷贝构造同理，暂时用list& l
		list& operator=(const list& l)
		{
			if (this != &l)
			{
				clean();
				for (auto& e : l)
				{
					push_back(e);
				}
			}
			return *this;
		}

		void swap(const list& l)
		{
			std::swap(_head, l._head);
			std::swap(_size, l._size);
		}

		/*list& operator=(list l)
		{
			swap(*this, l);
		}*/

	private:
		node* _head;
		size_t _size;
	};
}
