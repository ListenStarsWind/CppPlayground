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
			, _col(red)   // 红色是节点的正常性状,默认为红色
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

		enum direction  // 标定子节点对于父节点的方位
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
				newNode->_col = black;       // 根节点必须为黑
				_root = newNode;
				return true;
			}

			// 节点插入
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

			(void)parent;                // 避免歧义
			Node*& BasePoint = location; // 重命名,增强可读性
			while (BasePoint)  // 这个循环条件其实没用 不是靠他跳出循坏的
			{
				// 进入循环意味节点存在
				Node* parent = BasePoint->_parent;  // 节点存在意味着它必有父亲

				if (parent->_col == black)
					break;
				
				// 来到这里说明出现了连续的红色节点
				// 出现连续的红色节点说明当前必有三层结构
				Node* grandparent = parent->_parent; // 三层结构意味着grandparent必定不为空
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

				// 迭代是一层一层往上回溯的
				// 最高点grandparent是一层一层往上升的
				// 后续操作若出现grandparent为根节点
				// 就要主动跳出

				if (uncle && uncle->_col == red)  // 如果uncle存在并且为红
				{
					parent->_col = uncle->_col = grandparent->_col; // 黑色的传递
					if (grandparent == _root)
						break;                      // 根节点的本色是黑色
					else
						grandparent->_col = red;	// 黑色被转移了

					// 来到这里 说明grandparent一定不是根节点 并且颜色已经为红
					BasePoint = grandparent;
				}
				else
				{
					// 包含旋转操作 需要确定方位关系
					direction base_way = invalid;
					if (BasePoint == parent->_left)
						base_way = left;
					else
						base_way = right;

					if (parent_way == base_way)
					{
						// 直线关系
						if (parent_way == left)
						{
							// 向右旋转
							_RotateRight(grandparent);
						}
						else
						{
							// 向左旋转
							_RotateLeft(grandparent);
						}

						parent->_col = grandparent->_col;  // 转移黑色
						grandparent->_col = red;           // grandparent现在必定不是根节点

						break;
					}
					else
					{
						// 折线关系
						if (base_way == right)
						{
							// 内层向左旋转
							_RotateLeft(parent);
						}
						else
						{
							// 内层向右旋转
							_RotateRight(parent);
						}

						// 转换为直线关系
						BasePoint = parent;  // 外层循环依靠下一次迭代
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
				// 检查每条路径黑色节点个数
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
		// 检查是否有连续的红色节点 无连续红色返回true
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
				// 红色节点一定有父节点
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

		// Left Rotation  左单旋
		void _RotateLeft(Node* parent)  // _表示该接口是私有的
		{
			Node* subR = parent->_right;   // Right Subtree
			Node* subRL = subR->_left;     // Left Subtree of Right Subtree

			// 旋转的过程

			// 对于parent
			Node* newParPar = parent->_parent;
			parent->_parent = subR;
			(void)parent->_left; // 我知道有这个成员，但它不用处理
			parent->_right = subRL;

			// 对于subR
			if (newParPar == nullptr)
			{
				// 原先的parent就是根节点
				subR->_parent = nullptr;
				_root = subR;
			}
			else
			{
				// 原先的parent具有父节点
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
			(void)subR->_right;  // 它无需处理

			// 对于subRL
			if (subRL) // 如果它不是空树
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