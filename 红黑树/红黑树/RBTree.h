#pragma once

#include<utility>
#include<vector>
#include<string>
#include<iostream>

namespace wind
{
	template<class V>
	struct less
	{
		bool operator()(const V& val1, const V& val2)
		{
			return val1 < val2;
		}
	};

	enum color
	{
		red,
		black
	};

	template<class V>
	struct RBTreeNode
	{
	private:
		typedef RBTreeNode<V> self;
	public:
		self* _parent;
		self* _left;
		self* _right;
		color _col;
		V _value;

		RBTreeNode(const V& v)
			:_parent(nullptr)
			, _left(nullptr)
			, _right(nullptr)
			, _col(red)   // ��ɫ�ǽڵ��������״,Ĭ��Ϊ��ɫ
			, _value(v)
		{}
	};

	template<class K, class V, class cmp = less<K>>
	class RBTree
	{
		typedef RBTree<K, V, cmp> self;
		typedef K key_type;
		typedef V mapped_type;
		typedef std::pair<key_type, mapped_type> value_type;
		typedef RBTreeNode<value_type> Node;
		typedef cmp less;

		enum direction  // �궨�ӽڵ���ڸ��ڵ�ķ�λ
		{
			left,
			right,
			invalid
		};

	public:
		bool Insert(const value_type& val)
		{
			if (_root == nullptr)
			{
				Node* newNode = new Node(val);
				newNode->_col = black;       // ���ڵ����Ϊ��
				_root = newNode;
				return true;
			}

			// �ڵ����
			less l;
			Node* location = _root;
			Node* parent = nullptr;
			while (location)
			{
				parent = location;
				if (l(val.first, location->_value.first))
					location = location->_left;
				else if (l(location->_value.first, val.first))
					location = location->_right;
				else
					return false;
			}

			location = new Node(val);
			location->_parent = parent;
			if (l(val.first, parent->_value.first))
				parent->_left = location;
			else
				parent->_right = location;

			(void)parent;                // ��������
			Node*& BasePoint = location; // ������,��ǿ�ɶ���
			while (BasePoint)  // ���ѭ��������ʵû�� ���ǿ�������ѭ����
			{
				// ����ѭ����ζ�ڵ����
				Node* parent = BasePoint->_parent;  // �ڵ������ζ�������и���

				if (parent->_col == black)
					break;
				
				// ��������˵�������������ĺ�ɫ�ڵ�
				// ���������ĺ�ɫ�ڵ�˵����ǰ��������ṹ
				Node* grandparent = parent->_parent; // ����ṹ��ζ��grandparent�ض���Ϊ��
				Node* uncle = nullptr;
				direction parent_way = invalid;
				if (parent == grandparent->_left)
				{
					parent_way = left;
					uncle = grandparent->_right;
				}
				else
				{
					parent_way = right;
					uncle = grandparent->_left;
				}

				// ������һ��һ�����ϻ��ݵ�
				// ��ߵ�grandparent��һ��һ����������
				// ��������������grandparentΪ���ڵ�
				// ��Ҫ��������

				if (uncle && uncle->_col == red)  // ���uncle���ڲ���Ϊ��
				{
					parent->_col = uncle->_col = grandparent->_col; // ��ɫ�Ĵ���
					if (grandparent == _root)
						break;                      // ���ڵ�ı�ɫ�Ǻ�ɫ
					else
						grandparent->_col = red;	// ��ɫ��ת����

					// �������� ˵��grandparentһ�����Ǹ��ڵ� ������ɫ�Ѿ�Ϊ��
					BasePoint = grandparent;
				}
				else
				{
					// ������ת���� ��Ҫȷ����λ��ϵ
					direction base_way = invalid;
					if (BasePoint == parent->_left)
						base_way = left;
					else
						base_way = right;

					if (parent_way == base_way)
					{
						// ֱ�߹�ϵ
						if (parent_way == left)
						{
							// ������ת
							_RotateRight(grandparent);
						}
						else
						{
							// ������ת
							_RotateLeft(grandparent);
						}

						parent->_col = grandparent->_col;  // ת�ƺ�ɫ
						grandparent->_col = red;           // grandparent���ڱض����Ǹ��ڵ�

						break;
					}
					else
					{
						// ���߹�ϵ
						if (base_way == right)
						{
							// �ڲ�������ת
							_RotateLeft(parent);
						}
						else
						{
							// �ڲ�������ת
							_RotateRight(parent);
						}

						// ת��Ϊֱ�߹�ϵ
						BasePoint = parent;  // ���ѭ��������һ�ε���
					}
				}
			}

			return true;
		}

		std::vector<value_type> InOrder()
		{
			std::vector<value_type> res;
			_InOrder(_root, res);
			return res;
		}

		bool IsBalance()
		{
			if (_root == nullptr)
				return true;

			if (_root->_col == red)
				return false;

			std::vector<std::pair<size_t, std::string>> NBlack;
			size_t count = 0;
			std::string path;

			if (_IsBalance(_root, count, path, NBlack))
			{
				auto it = NBlack.begin();
				size_t prev = it->first;
				++it;
				// ���ÿ��·����ɫ�ڵ����
				while (it != NBlack.end())
				{
					if (it->first != prev)
					{
						for (const auto& e : NBlack)
						{
							std::cout << e.first << "->" << e.second << std::endl;
						}
						return false;
					}
					prev = it->first;
					++it;
				}
				return true;
			}
			else
				return false;
		}
	private:
		// ����Ƿ��������ĺ�ɫ�ڵ� ��������ɫ����true
		bool _IsBalance(Node* root, size_t count, std::string path, std::vector<std::pair<size_t, std::string>>& NBlack)
		{
			if (root == nullptr)
			{
				path += "\\nullptr";
				NBlack.push_back(make_pair(count, path));
				return true;
			}

			path += "\\";
			path += root->_value.first;

			if (root->_col == red)
			{
				// ��ɫ�ڵ�һ���и��ڵ�
				if (root->_parent->_col == red)
					return false;
			}
			else
			{
				count++;
			}

			return _IsBalance(root->_left, count, path, NBlack) &&
				_IsBalance(root->_right, count, path, NBlack);
		}

		// Left Rotation  ����
		void _RotateLeft(Node* parent)  // _��ʾ�ýӿ���˽�е�
		{
			Node* subR = parent->_right;   // Right Subtree
			Node* subRL = subR->_left;     // Left Subtree of Right Subtree

			// ��ת�Ĺ���

			// ����parent
			Node* newParPar = parent->_parent;
			parent->_parent = subR;
			(void)parent->_left; // ��֪���������Ա���������ô���
			parent->_right = subRL;

			// ����subR
			if (newParPar == nullptr)
			{
				// ԭ�ȵ�parent���Ǹ��ڵ�
				subR->_parent = nullptr;
				_root = subR;
			}
			else
			{
				// ԭ�ȵ�parent���и��ڵ�
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
			(void)subR->_right;  // �����账��

			// ����subRL
			if (subRL) // ��������ǿ���
				subRL->_parent = parent;
		}

		void _RotateRight(Node* parent)
		{
			Node* subL = parent->_left;
			Node* subLR = subL->_right;

			Node* newParPar = parent->_parent;
			parent->_parent = subL;
			parent->_left = subLR;
			(void)parent->_right;

			if (newParPar == nullptr)
			{
				subL->_parent = nullptr;
				_root = subL;
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

		void _InOrder(Node* root, std::vector<value_type>& v)
		{
			if (root == nullptr)
				return;

			_InOrder(root->_left, v);
			v.push_back(root->_value);
			_InOrder(root->_right, v);
		}

		Node* _root = nullptr;
	};
}