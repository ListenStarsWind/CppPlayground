#pragma once

#include<assert.h>
#include<algorithm>

namespace wind {

	// C++һ�㲻���ڲ���
	// ���Բ�ȡ���ⲿ����ģ��
	// ��typedef�Ĳ���
	// Ϊ�˷���������ʳ�Ա
	// ֱ��ʹ��struct��ȫ����
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

	//	// �������ĳ�Ա����������
	//	// ��������

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

	//	// ����������ָ��һ����
	//	// ���������������ͣ�����ֱ����*ptr����ȡֵ��
	//	T& operator*() const
	//	{
	//		return _ptr->_val;
	//	}

	//	// �����Զ���������˵��
	//	// ��(*ptr).member���Ե��е㷱����
	//	// �������ǿ�����ptr->member�ķ�ʽ���򻯡�

	//	// ��Ȼ������ģ��ָ�룬
	//	// ��ȻҲ��Ҫ����iterator->member�Ĳ�����

	//	// ���������Ǹ�ģ�壬
	//	// ���ǲ���֪��T��ʲô�Զ������ͣ�
	//	// Ҳ��֪��������Щ��Ա�Լ���Щ��Ա�����͡�
	//	// ���Բ���ֱ����T->member�ķ�ʽ��

	//	// ��ô�����������ص�������->����ʱ��
	//	// ��ô��ȡ��Ա�أ�

	//	// C++Ϊ�������ر���
	//	// ������->����ʱ��ֻ�践��T��ָ�롣
	//	// Ȼ���������������ָ�����ҵ���Ӧ�ĳ�Ա��

	//	// ���磬���T��һ���ṹ�� {int a; int b}; 
	//	// ������дiterator->aʱ��
	//	// �������Ὣ�����ΪT*->a��
	//	// ���T*�Ǵ�->�����л�ȡ�ġ�

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
		// ���캯����Ҫ����ͷ���
		// ���Ըɴ�ֱ��д�ɾ��庯��
		node* __init_head_node()
		{
			node* head = new node();
			head->_prev = head;
			head->_next = head;
			head->_val = T();
			return head;
		}
	public:
		// ������Ҫ���ⲿʹ�ã�������ڹ�����
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

		// ��һ��д��ͷ��
		// ˳���ں�����˸�
		// const
		// �����Ļ�iterator
		// �ͻᱻʶ���const_lterator��iterator
		// Ҳ����˵������Ҳ����������
		iterator begin()
		{
			// ��ʽ����ת��
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
			// iteratorȫ����ֱ�ӷ���
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
			// �����ⲿʧЧ������
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
				// ����ɾ����������ʧЧ
				// ʹ�÷���ֵ����������
				it = erase(it);
			}
		}

		~list()
		{
			clean();
			delete _head;
		}

		// ������Ӧ����const list& l
		// ����ûдconst_iterator 
		list(const list& l)
			:_head(__init_head_node())
			, _size(0)
		{
			// ����������Ч��
			for (const auto& e : l)
			{
				push_back(e);
			}
		}

		// �뿽������ͬ����ʱ��list& l
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
