#pragma once

#include<algorithm>
#include<vector>

namespace wind
{
	template<class T>
	class less
	{
	public:
		bool operator()(const T& v1, const T& v2)
		{
			return v1 < v2;
		}
	};

	template<class T>
	class greater
	{
	public:
		bool operator()(const T& v1, const T& v2)
		{
			return v1 > v2;
		}
	};

	template<class T>
	class same
	{
	public:
		bool operator()(const T& v1, const T& v2)
		{
			return v1 == v2;
		}
	};

	namespace K_model
	{
		template<class K>
		struct BSTreeNode
		{
		private:
			typedef BSTreeNode<K> self;
		public:
			BSTreeNode* _left;
			BSTreeNode* _right;
			K _val;

			BSTreeNode(const K& val)
				:_left(nullptr)
				, _right(nullptr)
				, _val(val)
			{
			}

			/*void swap(self& n1, self& n2)
			{
				std::swap(n1._left, n2._left);
				std::swap(n1._right, n2._right);
				std::swap(n1._val, n2._val);
			}

			bool operator<(const self* n)const
			{
				less<K> l;
				if (l(this->_val, n->_val))
					return true;
				else
					return false;
			}

			bool operator>(const self* n)const
			{
				greater<K> g;
				if (g(this->_val, n->_val))
					return true;
				else
					return false;
			}

			bool operator==(const self* n)const
			{
				same<K> s;
				if (s(this->_val, n->_val))
					return true;
				else
					return false;
			}*/
		};

		template<class K, class Less = less<K>, class Greater = greater<K>, class Same = same<K>>
		class BSTree
		{
			typedef BSTreeNode<K> Node;
			typedef BSTree<K> self;
			/*typedef less<K> Less;
			typedef greater<K> Greater;
			typedef same<K> Same;*/
		public:
			bool Insert(const K& key)
			{
				if (_root == nullptr)
				{
					Node* p = new Node(key);
					_root = p;
					return true;
				}

				Less l;
				Greater g;

				Node* p = new Node(key);
				Node* parent = nullptr;
				Node* curr = _root;

				while (curr)
				{
					parent = curr;
					if (l(key, parent->_val))
					{
						curr = parent->_left;
					}
					else if (g(key, parent->_val))
					{
						curr = parent->_right;
					}
					else
					{
						delete p;
						return false;
					}
				}

				if (l(key, parent->_val))
				{
					parent->_left = p;
				}
				else
				{
					parent->_right = p;
				}

				return true;
			}

			std::vector<K> InOrder()
			{
				std::vector<K> v;
				_InOrder(v, _root);
				return v;
			}

			bool Find(const K& key)
			{
				Node* curr = _root;

				Less l;
				Greater g;

				while (curr)
				{
					if (l(key, curr->_val))
						curr = curr->_left;
					else if (g(key, curr->_val))
						curr = curr->_right;
					else
						return true;
				}

				return false;
			}

			bool FindR(const K& key)
			{
				return _FindR(key, _root);
			}

			bool Erase(const K& key)
			{
				Node* curr = _root;
				Node* parent = _root;

				Less l;
				Greater g;
				Same s;

				while (!s(key, curr->_val))
				{
					parent = curr;

					if (l(key, curr->_val))
						curr = curr->_left;
					else
						curr = curr->_right;

					if (curr == nullptr)
						return false;
				}

				if (curr->_left == nullptr)
				{
					if (curr == _root)
					{
						Node* die = _root;
						_root = curr->_right;
						delete die;
						return true;
					}

					if (l(key, parent->_val))
						parent->_left = curr->_right;
					else
						parent->_right = curr->_right;

					delete curr;
					return true;
				}
				else if (curr->_right == nullptr)
				{
					if (curr == _root)
					{
						Node* die = _root;
						_root = curr->_left;
						delete die;
						return true;
					}

					if (l(key, parent->_val))
						parent->_left = curr->_left;
					else
						parent->_right = curr->_left;

					delete curr;
					return true;
				}
				else
				{
					parent = curr;
					Node* target = parent->_right;

					while (target->_left)
					{
						parent = target;
						target = target->_left;
					}

					if (target == parent->_right)
					{
						std::swap(target->_val, curr->_val);
						curr->_right = target->_right;
					}
					else
					{
						std::swap(target->_val, curr->_val);
						parent->_left = nullptr;
					}

					delete target;
					return true;

				}
			}

			bool EraseR(const K& key)
			{
				return _EraseR(key, _root);
			}

			bool InsertR(const K& key)
			{
				return _InsertR(key, _root);
			}

			~BSTree()
			{
				Destroy(_root);
				_root = nullptr;
			}

			BSTree(const self& obj)
			{
				_root = Copy(obj._root);
			}

			BSTree() = default;

			self& operator=(self obj)
			{
				std::swap(_root, obj._root);
				return *this;
			}

		private:

			Node* Copy(const Node* root)
			{
				if (root == nullptr)
					return nullptr;

				Node* newRoot = new Node(root->_val);
				newRoot->_left = Copy(root->_left);
				newRoot->_right = Copy(root->_right);

				return newRoot;
			}

			void Destroy(Node* root)
			{
				if (root == nullptr)
					return;

				Destroy(root->_left);
				Destroy(root->_right);
				delete root;
			}

			bool _InsertR(const K& key, Node*& root)
			{
				if (root == nullptr)
				{
					Node* p = new Node(key);
					root = p;
					return true;
				}

				Less l;
				Greater g;

				if (l(key, root->_val))
					return _InsertR(key, root->_left);
				else if (g(key, root->_val))
					return _InsertR(key, root->_right);
				else
					return false;
			}

			bool _FindR(const K& key, Node* root)
			{
				if (root == nullptr)
					return false;

				Less l;
				Greater g;

				if (l(key, root->_val))
					return _FindR(key, root->_left);
				else if (g(key, root->_val))
					return _FindR(key, root->_right);
				else
					return false;
			}

			bool _EraseR(const K& key, Node*& root)
			{
				if (root == nullptr)
					return false;

				Less l;
				Greater g;

				if (l(key, root->_val))
					return _EraseR(key, root->_left);
				else if (g(key, root->_val))
					return _EraseR(key, root->_right);
				else
				{
					if (root->_left == nullptr)
					{
						Node* die = root;
						root = root->_right;

						delete die;
						return true;
					}
					else if (root->_right == nullptr)
					{
						Node* die = root;
						root = root->_left;

						delete die;
						return true;
					}
					else
					{

						Node* parent = root;
						Node* target = parent->_right;

						while (target->_left)
						{
							parent = target;
							target = target->_left;
						}

						if (target == parent->_right)
						{
							std::swap(target->_val, root->_val);
							return _EraseR(key, root->_right);
						}
						else
						{
							std::swap(target->_val, root->_val);
							return _EraseR(key, root->_right);
						}
					}
				}
			}

			void _InOrder(std::vector<K>& v, Node* root)
			{
				if (root == nullptr)
					return;

				_InOrder(v, root->_left);
				v.push_back(root->_val);
				_InOrder(v, root->_right);
			}

			Node* _root = nullptr;
		};
	}

	namespace KV_model
	{
		template<class Key, class Value>
		struct BSTreeNode
		{
		private:
			typedef BSTreeNode<Key, Value> self;
		public:
			BSTreeNode* _left;
			BSTreeNode* _right;
			Key _key;
			Value _value;

			BSTreeNode(const Key& key, const Value& value)
				:_left(nullptr)
				, _right(nullptr)
				, _key(key)
				,_value(value)
			{}

		};

		template<class Key, class Value, class Less = less<Key>, class Greater = greater<Key>, class Same = same<Key>>
		class BSTree
		{
			typedef BSTreeNode<Key, Value> Node;
			typedef BSTree<Key, Value, Less, Greater, Same> self;
			typedef std::vector<Key> Keys_Returning_Container;
			typedef std::vector<Node> Complete_Mapping_Returning_Container;
			typedef Keys_Returning_Container Keys_Ret;
			typedef Complete_Mapping_Returning_Container Mapping_Ret;
			
		public:
			bool Insert(const Key& key, const Value& value)
			{
				if (_root == nullptr)
				{
					Node* p = new Node(key, value);
					_root = p;
					return true;
				}

				Less l;
				Greater g;

				Node* p = new Node(key, value);
				Node* parent = nullptr;
				Node* curr = _root;

				while (curr)
				{
					parent = curr;
					if (l(key, parent->_key))
					{
						curr = parent->_left;
					}
					else if (g(key, parent->_key))
					{
						curr = parent->_right;
					}
					else
					{
						delete p;
						return false;
					}
				}

				if (l(key, parent->_key))
				{
					parent->_left = p;
				}
				else
				{
					parent->_right = p;
				}

				return true;
			}

			Mapping_Ret InOrder()
			{
				Mapping_Ret v;
				_InOrder(v, _root);
				return v;
			}

			Node* Find(const Key& key)
			{
				Node* curr = _root;

				Less l;
				Greater g;

				while (curr)
				{
					if (l(key, curr->_key))
						curr = curr->_left;
					else if (g(key, curr->_key))
						curr = curr->_right;
					else
						return curr;
				}

				return nullptr;
			}

			bool Erase(const Key& key)
			{
				return _Erase(key, _root);
			}

			~BSTree()
			{
				Destroy(_root);
				_root = nullptr;
			}

			BSTree(const self& obj)
			{
				_root = Copy(obj._root);
			}

			BSTree() = default;

			self& operator=(self obj)
			{
				std::swap(_root, obj._root);
				return *this;
			}

		private:

			Node* Copy(const Node* root)
			{
				if (root == nullptr)
					return nullptr;

				Node* newRoot = new Node(root->_key);
				newRoot->_left = Copy(root->_left);
				newRoot->_right = Copy(root->_right);

				return newRoot;
			}

			void Destroy(Node* root)
			{
				if (root == nullptr)
					return;

				Destroy(root->_left);
				Destroy(root->_right);
				delete root;
			}

			bool _Erase(const Key& key, Node*& root)
			{
				if (root == nullptr)
					return false;

				Less l;
				Greater g;

				if (l(key, root->_key))
					return _Erase(key, root->_left);
				else if (g(key, root->_key))
					return _Erase(key, root->_right);
				else
				{
					if (root->_left == nullptr)
					{
						Node* die = root;
						root = root->_right;

						delete die;
						return true;
					}
					else if (root->_right == nullptr)
					{
						Node* die = root;
						root = root->_left;

						delete die;
						return true;
					}
					else
					{
						Node* parent = root;
						Node* target = parent->_right;

						while (target->_left)
						{
							parent = target;
							target = target->_left;
						}

						if (target == parent->_right)
						{
							std::swap(target->_key, root->_key);
							return _Erase(key, root->_right);
						}
						else
						{
							std::swap(target->_key, root->_key);
							return _Erase(key, root->_right);
						}
					}
				}
			}

			void _InOrder(Mapping_Ret& v, Node* root)
			{
				if (root == nullptr)
					return;

				_InOrder(v, root->_left);
				v.push_back(*root);
				_InOrder(v, root->_right);
			}

			Node* _root = nullptr;
		};
	}
}