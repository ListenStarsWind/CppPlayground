#pragma once

#include<utility>
#include<vector>
#include<string>
#include<iostream>

namespace wind
{
	template<class Key>
	struct Less
	{
		bool operator()(const Key& val1, const Key& val2)const
		{
			return val1 < val2;
		}
	};

	enum color
	{
		red,
		black
	};

	enum direction
	{
		left,
		right,
		invalid
	};

	template<class V>
	struct BaseTreeNode
	{
	private:
		typedef BaseTreeNode<V> self;
		typedef self* link_type;
	public:
		link_type _parent;
		link_type _left;
		link_type _right;
		color _col;
		V _value;

		BaseTreeNode()
			:_parent(nullptr)
			, _left(nullptr)
			, _right(nullptr)
			, _col(red)
			, _value(V())
		{
		}

		BaseTreeNode(const V& v)
			:_parent(nullptr)
			, _left(nullptr)
			, _right(nullptr)
			, _col(red)
			, _value(v)
		{
		}
	};

	template<class Value, class Pointer, class Reference>
	struct BaseIterator
	{
		typedef Value value_type;
		typedef BaseTreeNode<value_type> Node;
		typedef Node* link_type;
		typedef BaseIterator<Value, Pointer, Reference> self;

	protected:
		link_type _ptr;

	public:
		BaseIterator(link_type ptr) :_ptr(ptr) {}
		BaseIterator(const self& obj) :_ptr(obj._ptr) {}

		virtual Reference operator*() = 0;

		void swap(self& v1, self& v2)
		{
			std::swap(v1._ptr, v2._ptr);
		}


		self& operator=(const self obj)
		{
			swap(*this, obj);
			return *this;
		}

		Pointer operator->()
		{
			return &(this->operator*());
		}

		bool operator==(const self& obj)const
		{
			return this->_ptr == obj._ptr;
		}

		bool operator!=(const self& obj)const
		{
			return !(*this == obj);
		}

		void increment()
		{
			if (_ptr->_right)
			{
				// 右子树不为空
				// 下一节点是右子树的最左节点
				link_type curr = _ptr->_right;
				while (curr->_left) curr = curr->_left;
				_ptr = curr;
			}
			else
			{
				// 右子树为空
				link_type curr = _ptr;
				link_type parent = curr->_parent;
				// 如果当前树是上一级树的右子树
				// 就说明上一级树已经遍历完成
				while (parent && curr == parent->_right)
				{
					curr = parent;
					parent = curr->_parent;
				}

				// 来到这里 有两种情况
				// 
				// 已经没有上级树了 整棵树遍历完了
				// 
				// curr树的右子树已经遍历完了 中序为 左子树 根
				// 节点 右子树 右子树遍历完意味着curr已经遍历完了
				// 又curr是上级树的左子树 所以下一个节点就是父节点
				_ptr = parent;
			}
		}

		void decrement()
		{
			if (_ptr->_left)
			{
				// 左子树不为空
				// 下一节点是左子树的最右节点
				link_type curr = _ptr->_left;
				while (curr->_right) curr = curr->_right;
				_ptr = curr;
			}
			else
			{
				// 左子树为空
				link_type curr = _ptr;
				link_type parent = curr->_parent;
				while (parent && curr == parent->_left)
				{
					curr = parent;
					parent = curr->_parent;
				}
				_ptr = parent;
			}
		}

		virtual self& operator++() = 0;
		virtual self& operator--() = 0;
	};

	template<class Value, class Pointer, class Reference>
	struct BaseTreeIterator : virtual public BaseIterator<Value, Pointer, Reference>
	{
		typedef typename BaseIterator<Value, Pointer, Reference>::link_type link_type;
		typedef BaseTreeIterator<Value, Pointer, Reference> self;
		typedef BaseIterator<Value, Pointer, Reference> Base;

		BaseTreeIterator(link_type ptr) : BaseIterator<Value, Pointer, Reference>(ptr) {}
		BaseTreeIterator(const self& obj) : BaseIterator<Value, Pointer, Reference>(obj) {}

		Reference operator*()
		{
			return Base::_ptr->_value;
		}

		self& operator++()
		{
			Base::increment();
			return *this;
		}

		self& operator--()
		{
			Base::decrement();
			return *this;
		}
	};

	template<class Value, class Pointer, class Reference>
	struct BaseTreeReverseIterator : virtual public BaseIterator<Value, Pointer, Reference>
	{
		typedef typename BaseIterator<Value, Pointer, Reference>::link_type link_type;
		typedef BaseTreeReverseIterator<Value, Pointer, Reference> self;
		typedef BaseIterator<Value, Pointer, Reference> Base;

		BaseTreeReverseIterator(link_type ptr) : BaseIterator<Value, Pointer, Reference>(ptr) {}
		BaseTreeReverseIterator(const self& obj) : BaseIterator<Value, Pointer, Reference>(obj) {}

		Reference operator*()
		{
			self it = *this;
			++it;
			return it._ptr->_value;
		}

		self& operator++()
		{
			Base::decrement();
			return *this;
		}

		self& operator--()
		{
			Base::increment();
			return *this;
		}
	};

	template<class Key, class Value, class KeyOfValue, class Compare>
	class BaseTree
	{
		// 将基树类型开放给具体树
	public:
		typedef BaseTree<Key, Value, KeyOfValue, Compare> self;
		typedef Key key_type;
		typedef Value value_type;
		typedef value_type* pointer;
		typedef const value_type* const_pointer;
		typedef value_type& reference;
		typedef const value_type& const_reference;
		typedef BaseTreeNode<value_type> Node;
		typedef Node* link_type;
		typedef Compare Less;
		typedef BaseTreeIterator<value_type, pointer, reference> iterator;
		typedef BaseTreeIterator<value_type, const_pointer, const_reference> const_iterator;
		typedef BaseTreeReverseIterator<value_type, pointer, reference> reverse_iterator;
		typedef BaseTreeReverseIterator<value_type, const_pointer, const_reference> const_reverse_iterator;
		typedef std::pair<link_type, bool> ret_type;

	private:
		struct BaseTreeLess
		{
			bool operator()(const_reference smaller, const_reference larger)
			{
				KeyOfValue Extract;
				Less cmp;
				return cmp(Extract(smaller), Extract(larger));
			}
		};

		inline link_type create_node(const_reference val)
		{
			return new Node(val);
		}

		inline link_type create_node()
		{
			return new Node();
		}

		inline link_type& node_left(link_type& node)
		{
			return node->_left;
		}

		inline const link_type& node_left(const link_type& node)const
		{
			return node->_left;
		}

		inline link_type& node_right(link_type& node)
		{
			return node->_right;
		}

		inline const link_type& node_right(const link_type& node)const
		{
			return node->_right;
		}

		inline link_type& node_parent(link_type& node)
		{
			return node->_parent;
		}

		inline const link_type& node_parent(const link_type& node)const
		{
			return node->_parent;
		}

		inline color& node_color(link_type& node)
		{
			return node->_col;
		}

		inline Value& node_value(link_type& node)
		{
			return node->_value;
		}

		inline link_type left_most_node(link_type node)const
		{
			while (node && node_left(node))
				node = node_left(node);
			return node;
		}

		inline link_type right_most_node(link_type node)const
		{
			while (node && node_right(node))
				node = node_right(node);
			return node;
		}

		BaseTreeLess less;
		link_type _head;
		link_type& _root;


	public:
		BaseTree()
			:less(BaseTreeLess())
			, _head(create_node())
			,_root(_head->_parent)
		{
		}

		iterator begin()
		{
			return iterator(left_most_node(_root));
		}

		iterator end()
		{
			return iterator(_head);
		}

		const_iterator begin()const
		{
			return const_iterator(left_most_node(_root));
		}

		const_iterator end()const
		{
			return const_iterator(_head);
		}

		reverse_iterator rbegin()
		{
			return reverse_iterator(_head);
		}

		reverse_iterator rend()
		{
			return reverse_iterator(left_most_node(_root));
		}

		const_reverse_iterator rbegin()const
		{
			return const_reverse_iterator(_head);
		}

		const_reverse_iterator rend()const
		{
			return const_reverse_iterator(left_most_node(_root));
		}

		ret_type insert(const_reference val)
		{
			if (_root == nullptr)
			{
				link_type newNode = create_node(val);
				node_color(newNode) = black;
				_root = newNode;
				node_parent(_root) = _head;
				return ret_type(std::make_pair(_root, true));
			}

			link_type location = _root;
			link_type parent = nullptr;
			while (location)
			{
				parent = location;
				if (less(val, node_value(location)))
					location = node_left(location);
				else if (less(node_value(location), val))
					location = node_right(location);
				else
					return ret_type(std::make_pair(location, false));
			}

			location = create_node(val);
			node_parent(location) = parent;
			if (less(val, node_value(parent)))
				node_left(parent) = location;
			else
				node_right(parent) = location;

			(void)parent;
			link_type BasePoint = location;
			while (BasePoint)
			{
				link_type parent = node_parent(BasePoint);

				if (parent->_col == black)
					break;

				link_type grandparent = node_parent(parent);
				link_type uncle = nullptr;
				direction parent_way = invalid;
				if (parent == node_left(grandparent))
				{
					parent_way = left;
					uncle = node_left(grandparent);
				}
				else
				{
					parent_way = right;
					uncle = node_right(grandparent);
				}

				if (uncle && node_color(uncle) == red)
				{
					node_color(parent) = node_color(uncle) = node_color(grandparent);
					if (grandparent == _root)
						break;
					else
						node_color(grandparent) = red;

					BasePoint = grandparent;
				}
				else
				{
					direction base_way = invalid;
					if (BasePoint == node_left(parent))
						base_way = left;
					else
						base_way = right;

					if (parent_way == base_way)
					{
						if (parent_way == left)
							_RotateRight(grandparent);
						else
							_RotateLeft(grandparent);

						node_color(parent) = node_color(grandparent);
						node_color(grandparent) = red;

						break;
					}
					else
					{
						if (base_way == right)
							_RotateLeft(parent);
						else
							_RotateRight(parent);

						BasePoint = parent;
					}
				}
			}

			node_left(_head) = left_most_node(node_parent(_head));
			node_right(_head) = right_most_node(node_parent(_head));

			return ret_type(std::make_pair(location, true));
		}

		iterator find(const key_type& key)
		{
			Less cmp;
			KeyOfValue Extract;
			link_type location = _root;
			link_type parent = nullptr;
			while (location)
			{
				parent = location;
				if(cmp(key, Extract(node_value(location))))
					location = node_left(location);
				else if(cmp(Extract(node_value(location)), key))
					location = node_right(location);
				else
					return iterator(location);
			}

			return end();
		}

	private:

		void _RotateLeft(link_type parent)
		{
			link_type subR = parent->_right;
			link_type subRL = subR->_left;

			link_type newParPar = parent->_parent;
			parent->_parent = subR;
			(void)parent->_left;
			parent->_right = subRL;

			if (newParPar == nullptr)
			{
				subR->_parent = nullptr;
				_root = subR;
				node_parent(_root) = _head;
			}
			else
			{
				if (newParPar->_left == parent)
				{
					newParPar->_left = subR;
				}
				else
				{
					newParPar->_right = subR;
				}

				subR->_parent = newParPar;
			}
			subR->_left = parent;
			(void)subR->_right;

			if (subRL)
				subRL->_parent = parent;
		}

		void _RotateRight(link_type parent)
		{
			link_type subL = parent->_left;
			link_type subLR = subL->_right;

			link_type newParPar = parent->_parent;
			parent->_parent = subL;
			parent->_left = subLR;
			(void)parent->_right;

			if (newParPar == nullptr)
			{
				subL->_parent = nullptr;
				_root = subL;
				node_parent(_root) = _head;
			}
			else
			{
				if (newParPar->_left == parent)
				{
					newParPar->_left = subL;
				}
				else
				{
					newParPar->_right = subL;
				}

				subL->_parent = newParPar;
			}
			(void)subL->_left;
			subL->_right = parent;

			if (subLR)
				subLR->_parent = parent;
		}
	};
}
