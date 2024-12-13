#pragma once

#include<utility>
#include<cassert>
#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<vector>

int debug_lock = 0;

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

	template<class V>
	struct AVLTreeNode
	{
	private:
		typedef AVLTreeNode<V> self;
	public:
		self* _parent;
		self* _left;
		self* _right;
		int _balanceFactor; // 约定平衡因子是左子树深度减去右子树深度
		V _value;

		AVLTreeNode(const V& v)
			:_parent(nullptr)
			, _left(nullptr)
			, _right(nullptr)
			, _balanceFactor(0)
			, _value(v)
		{
		}
	};

	template<class K, class V, class cmp = less<K>>
	class AVLTree
	{
		typedef AVLTree<K, V, cmp> self;
		typedef K key_type;
		typedef V mapped_type;
		typedef std::pair<key_type, mapped_type> value_type;
		typedef AVLTreeNode<value_type> Node;
		typedef cmp less;

		struct equivalent
		{
			// 如果val1 不小于 val2
			// 并且val2 不小于 val1
			// 则说明，它们相等
			bool operator()(const key_type& val1, const key_type& val2)
			{
				less l;
				if (!l(val1, val2) && !l(val2, val1))
					return true;
				else
					return false;
			}
		};

	public:

		// 先不考虑迭代器，因此我们还是返回布尔值
		bool Insert(const value_type& val)
		{
			// 第一个节点插入后必然是平衡的
			if (_root == nullptr)
			{
				Node* newNode = new Node(val);
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

			// 更新平衡因子以及自我检查
			while (parent) // 如果上面已经没有节点了，就说明整棵树已经被调整过了
			{
				// 更新父节点平衡因子
				if (location == parent->_left)
					parent->_balanceFactor++;
				else
					parent->_balanceFactor--;

				if (parent->_balanceFactor == 0)
				{
					// 当前树的高度不改变 跳出循环
					break;
				}
				else if (parent->_balanceFactor == 1 || parent->_balanceFactor == -1)
				{
					// 当前树的高度加一，影响了上级节点，进行回溯
					location = parent;
					parent = parent->_parent;
				}
				else if (parent->_balanceFactor == 2 || parent->_balanceFactor == -2)
				{
					// 这棵树已经不是AVLTree了，需要调整

					// 第一大类：线性旋转
					if (parent->_balanceFactor == 2 && location->_balanceFactor == 1)
					{
						// 右单旋
						_RotaRi(parent);
					}
					else if (parent->_balanceFactor == -2 && location->_balanceFactor == -1)
					{
						// 左单旋
						_RotaLe(parent);
					}

					// 第二大类：复合旋转
					else if (parent->_balanceFactor == 2 && location->_balanceFactor == -1)
					{
						_RotaLR(parent);

					}
					else if (parent->_balanceFactor == -2 && location->_balanceFactor == 1)
					{
						_RotaRL(parent);
					}
					else
					{
						assert(0);
					}

					// 现在树已经重新平衡了，并且高度没有改变
					break;
				}
				else
				{
					// 理论上不存在的分支，如果进入，最起码可以说明平衡因子的更新存在问题
					assert(0);   // 直接自爆
				}
			}

			return true;
		}

		bool isAVLTree() { return _isAVLTree(_root); }

		std::vector<value_type> InOrder()
		{
			std::vector<value_type> res;
			_InOrder(_root, res);
			return res;
		}

		int height() { return _height(_root); }

		Node* find(const key_type& key)
		{
			Node* curr = _root;
			less l;
			while (curr)
			{
				if (l(key, curr->_value.first))
					curr = curr->_left;
				else if (l(curr->_value.first, key))
					curr = curr->_right;
				else
					return curr;
			}
			return nullptr;
		}

		bool erase(const key_type& key)
		{
			Node* should = find(key); // 应该被删除的节点（闯祸的节点）
			if (should == nullptr)
				return false;

			// debug
			if (key == -1)
			{
				debug_lock = 1;
			}

			// 转移即将被释放的属性: should->practice
			Node* practice = nullptr; // 实际会被删除的节点（背黑锅的节点）
			source origin = invalid;  // 标记practice是其parent的左子树还是右子树
			if (should->_left == nullptr)// 仅有右子树
			{
				practice = should; // 自己闯的祸自己承担
				Node* practice_only_sub = practice->_right;
				Node* practice_parent = practice->_parent;

				// 安排后事
				if (practice_parent == nullptr)
				{
					// 让子树继承整棵树
					_root = practice_only_sub;
					if(practice_only_sub)
					practice_only_sub->_parent = nullptr;
					(void)origin;
				}
				else
				{
					// 找上级节点托孤
					if (practice_parent->_left == practice)
					{
						practice_parent->_left = practice_only_sub;
						if (practice_only_sub) // 空子树就不用向前链接
							practice_only_sub->_parent = practice_parent;
						origin = left;
					}
					else
					{
						practice_parent->_right = practice_only_sub;
						if (practice_only_sub) // 空子树就不用向前链接
							practice_only_sub->_parent = practice_parent;
						origin = right;
					}
				}
			}
			else if (should->_right == nullptr) //仅有左子树
			{
				practice = should;
				Node* practice_only_sub = practice->_left;
				Node* practice_parent = practice->_parent;

				if (practice_parent == nullptr)
				{
					_root = practice_only_sub;
					if (practice_only_sub)
						practice_only_sub->_parent = nullptr;
					(void)origin;
				}
				else
				{
					if (practice_parent->_left == practice)
					{
						practice_parent->_left = practice_only_sub;
						if (practice_only_sub)
							practice_only_sub->_parent = practice_parent;
						origin = left;
					}
					else
					{
						practice_parent->_right = practice_only_sub;
						if (practice_only_sub)
							practice_only_sub->_parent = practice_parent;
						origin = right;
					}
				}
			}
			else
			{
				// should有两个孩子

				//找替死鬼
				Node* prev = should;
				Node* next = prev->_right;
				while (next->_left)
				{
					prev = next;
					next = next->_left;
				}

				/*if (debug_lock)
				{
					debug(prev);
					const char* str = "Debug";
				}*/

				if (next == prev->_right)
				{
					// 覆写should节点，将被释放的节点变为多余内容的节点
					practice = next;
					//should->_value = practice->_value;
					std::swap(should->_value, practice->_value);


					// 托孤
					Node* practice_child = practice->_right;
					prev->_right = practice_child;
					if (practice_child)
						practice_child->_parent = practice->_parent;
					origin = right;
				}
				else
				{
					practice = next;
					//should->_value = practice->_value;
					std::swap(should->_value, practice->_value);
					
					// 托孤
					Node* practice_child = practice->_right;
					prev->_left = practice_child;
					if (practice_child)
						practice_child->_parent = practice->_parent;
					origin = left;
				}
				/*if (debug_lock)
				{
					debug(practice);
					const char* str = "Debug";
				}*/
			}

			Node* curr = nullptr;
			if(practice)
			curr = practice->_parent;  // 当前子树根节点

			// 再平衡化
			while (curr)
			{
				if (debug_lock)
				{
					debug(curr);
					const char* str = "Debug";
				}

				//// 平衡因子迭代机制
				//if (origin == invalid)
				//{
				//	// 子树成为了新的根节点，无需平衡化
				//	break;
				//}
				//else 

				if (origin == left)
				{
					// curr左子树高度将会降低
					curr->_balanceFactor--;
				}
				else if (origin == right)
				{
					// curr右子树高度将会降低
					curr->_balanceFactor++;
				}
				else
				{
					// 不存在的分支
					assert(0);
				}

				if (debug_lock)
				{
					debug(curr);
					const char* str = "Debug";
				}

				// 检查平衡性
				if (curr->_balanceFactor == 0)
				{
					// curr这棵树的高度降低
					// 回溯到上一级子树
					Node* parent = curr->_parent;
					if (parent == nullptr)
					{
						curr = parent;
						origin = invalid;
					}
					else
					{
						if (parent->_left == curr)
							origin = left;
						else
							origin = right;
						curr = parent;
					}
					if (debug_lock)
					{
						debug(curr);
						const char* str = "debug";
					}
				}
				else if (std::abs(curr->_balanceFactor) == 1)
				{
					// curr这棵树高度不变
					// 不必麻烦上一级子树
					break;
				}
				else if (std::abs(curr->_balanceFactor) == 2)
				{
					// curr这棵树已经失衡
					// 需要调整
						
					// 第一种情况——因为左子树次级平衡而引发的失衡
					if (origin == left)
					{
						// 当前情况是:左子树低,右子树高
						Node* higher_sub = curr->_right;
						if (higher_sub->_balanceFactor == 0)
						{
							// 左子树低是吧？那向左旋转就行了,向哪里旋转哪里就会变高一些
							_RotaLe(curr);

							// 在未插入前，整棵树的高度是h+2
							// 更高的树有两棵子树，它们高度相同,都是h
							// 原右子树路径因为旋转必然减少，不必分析,变成了h
							// 现在左左子树的路径高度，删除前(删除前是h)减少一个(变成了h-1)，旋转后，高度又增加一个，
							// 所以左左子树的高度是h，加上新上台的新根节点，这条路径的高度是h+1
							// 现在左右子树的路径高度取决于两个部分，第一个是原来的target节点，它被旋转下来后必然高度加一
							// 第二个因素是从原来较高树的左子树移过来的那棵子树,高度为h,加上下台的根节点，就变成了h+1,
							// 别忘了还有新根节点，合起来就是h+2
							// 综上，左单旋之后当前树的高度不发生变化

							// 平衡因子的修正
							higher_sub->_balanceFactor = 1;
							curr->_balanceFactor = -1;

							// 高度不发生变化
							break;
						}
						else if (higher_sub->_balanceFactor == -1)
						{
							_RotaLe(curr);

							// 平衡因子不需要修正,它们就是0,仅依靠单旋就已经足够
							// 按照上述逻辑分析,高度减一,需要回溯到上级树
							Node* newRoot = curr->_parent; // 旋转后新的根节点
							Node* parent = newRoot->_parent;
							if (parent == nullptr)
							{
								origin = invalid;
							}
							else
							{
								if (parent->_left == newRoot)
									origin = left;
								else
									origin = right;
							}
							curr = parent;
							if (debug_lock)
							{
								debug(curr);
								const char* str = "Debug";
							}
						}
						else if (higher_sub->_balanceFactor == 1)
						{
						// 此种场合不能直接进行左单旋
						// 此时较高树的左子树高度为h
						// 右子树为h-1
						// 直接单旋会造成当前左子树高度为h+1,
						// 而当前右子树高度为h-1
						// 这会引发新的不平衡

						// 对于较高树来说,它本来就偏科
						// 以前一俊遮百丑,强项可以掩盖弱项
						// bf == 0时是真正的均衡发展,把哪个子树匀给别人都行
						// bf == -1时虽然有偏科,但把弱项给别人,自己靠强项活的还可以
						// bf == 1是把强项给别人,没有强项之后,弱项的一系列问题就马上暴露出来了

						// 经济好的时候,大问题不是问题,经济不好的时候,小问题是大问题

						// 所以要先自我平衡一下,然后再去帮别人
							Node* higher_subL = higher_sub->_left;
							int bf = higher_subL->_balanceFactor;
							if (debug_lock)
							{
								debug(higher_subL);
								const char* str = "debug";
							}

							_RotaRi(higher_sub);
							if (debug_lock)
							{
								debug(curr);
								const char* str = "debug";
							}

							// bf有三种情况
							if (bf == 0)
							{
								// 这意味着,higher_subL的两个子树高度都是h-1
								// 在自我平衡之后,higher_sub的高度为h+1
								// 其中higher_subL为h-1,higher_subR为h
								// 也就是相当于higher_sub->_balanceFactor == -1的情况
							}
							else if (bf == -1)
							{
								// higher_subLL::bf == h-2
								// higher_subLR::bf == h-1
								// 自我平衡后
								// new higher_subL::bf == h-2
								// new higher_subR::bf == h
								// new higher_sub::bf == h+1
								// 等效higher_sub->_balanceFactor == -1

							}
							else if (bf == 1)
							{
								// higher_subLL::bf == h-1
								// higher_subLR::bf == h-2
								// 自我平衡后
								// new higher_subL::bf == h-1
								// new higher_subR::bf == h   (old higher_subR::bf == h-1)
								// new higher_sub::bf == h+1
								// 等效higher_sub->_balanceFactor == -1
							}
							//////三种情况相同操作
							_RotaLe(curr);
							// 平衡因子的更新
							if (debug_lock)
							{
								debug(curr->_parent);
								const char* str = "debug";
							}

							if (bf == -1)
							{
								curr->_balanceFactor = 1;
								higher_sub->_balanceFactor = 0;
							}
							else if (bf == 0)
							{
								curr->_balanceFactor = 0;
								higher_sub->_balanceFactor = 0;
							}
							else if (bf == 1)
							{
								curr->_balanceFactor = 0;
								higher_sub->_balanceFactor = -1;
							}
							else
								assert(0);
							
							Node* newRoot = curr->_parent; // 旋转后新的根节点
							Node* parent = newRoot->_parent;
							if (parent == nullptr)
							{
								origin = invalid;
							}
							else
							{
								if (parent->_left == newRoot)
									origin = left;
								else
									origin = right;
							}
							curr = parent;
						}
						else
							assert(0); // 不存在的分支
					}
					else if (origin == right)
					{
						// 当前情况是:左子树高,右子树低
						Node* higher_sub = curr->_left;
						if (higher_sub->_balanceFactor == 0)
						{
							// 右子树低是吧？那向右旋转就行了,向哪里旋转哪里就会变高一些
							_RotaRi(curr);

							// 在未插入前，整棵树的高度是h+2
							// 更高的树有两棵子树，它们高度相同,都是h
							// 原左子树路径因为旋转必然减少，不必分析,变成了h
							// 现在右右子树的路径高度，删除前(删除前是h)减少一个(变成了h-1)，旋转后，高度又增加一个，
							// 所以右右子树的高度是h，加上新上台的新根节点，这条路径的高度是h+1
							// 现在左右子树的路径高度取决于两个部分，第一个是原来的curr节点，它被旋转下来后必然高度加一
							// 第二个因素是从原来较高树的左子树移过来的那棵子树,高度为h,加上下台的根节点，就变成了h+1,
							// 别忘了还有新根节点，合起来就是h+2
							// 综上，左单旋之后当前树的高度不发生变化

							// 平衡因子的修正
							higher_sub->_balanceFactor = -1;
							curr->_balanceFactor = 1;

							// 高度不发生变化
							break;
						}
						else if (higher_sub->_balanceFactor == 1)
						{
							_RotaRi(curr);

							// 平衡因子不需要修正,它们就是0,仅依靠单旋就已经足够
							// 按照上述逻辑分析,高度减一,需要回溯到上级树
							Node* newRoot = curr->_parent; // 旋转后新的根节点
							Node* parent = newRoot->_parent;
							if (parent == nullptr)
							{
								origin = invalid;
							}
							else
							{
								if (parent->_left == newRoot)
									origin = left;
								else
									origin = right;
							}
							curr = parent;
						}
						else if (higher_sub->_balanceFactor == -1)
						{
						// 此种场合不能直接进行左单旋
						// 此时较高树的左子树高度为h
						// 右子树为h-1
						// 直接单旋会造成当前左子树高度为h+1,
						// 而当前右子树高度为h-1
						// 这会引发新的不平衡

						// 对于较高树来说,它本来就偏科
						// 以前一俊遮百丑,强项可以掩盖弱项
						// bf == 0时是真正的均衡发展,把哪个子树匀给别人都行
						// bf == -1时虽然有偏科,但把弱项给别人,自己靠强项活的还可以
						// bf == 1是把强项给别人,没有强项之后,弱项的一系列问题就马上暴露出来了

						// 经济好的时候,大问题不是问题,经济不好的时候,小问题是大问题

						// 所以要先自我平衡一下,然后再去帮别人
							Node* higher_subR = higher_sub->_right;
							int bf = higher_subR->_balanceFactor;
							if (debug_lock)
							{
								debug(higher_subR);
								const char* str = "debug";
							}

							_RotaLe(higher_sub);
							if (debug_lock)
							{
								debug(curr);
								const char* str = "debug";
							}

							// 三种情况
							if (bf == 0)
							{
								// 这意味着,higher_subL的两个子树高度都是h-1
								// 在自我平衡之后,higher_sub的高度为h+1
								// 其中higher_subL为h-1,higher_subR为h
								// 也就是相当于higher_sub->_balanceFactor == -1的情况
							}
							else if (bf == -1)
							{
								// higher_subLL::bf == h-2
								// higher_subLR::bf == h-1
								// 自我平衡后
								// new higher_subL::bf == h-2
								// new higher_subR::bf == h
								// new higher_sub::bf == h+1
								// 等效higher_sub->_balanceFactor == -1

							}
							else if (bf == 1)
							{
								// higher_subLL::bf == h-1
								// higher_subLR::bf == h-2
								// 自我平衡后
								// new higher_subL::bf == h-1
								// new higher_subR::bf == h   (old higher_subR::bf == h-1)
								// new higher_sub::bf == h+1
								// 等效higher_sub->_balanceFactor == -1
							}
							//////三种情况相同操作
							_RotaRi(curr);
							if (debug_lock)
							{
								debug(curr->_parent);
								const char* str = "debug";
							}

							// 平衡因子的更新

							if (bf == -1)
							{
								curr->_balanceFactor = 0;
								higher_sub->_balanceFactor = 1;
							}
							else if (bf == 0)
							{
								curr->_balanceFactor = 0;
								higher_sub->_balanceFactor = 0;
							}
							else if (bf == 1)
							{
								curr->_balanceFactor = -1;
								higher_sub->_balanceFactor = 0;
							}
							else
								assert(0);

							Node* newRoot = curr->_parent; // 旋转后新的根节点
							Node* parent = newRoot->_parent;
							if (parent == nullptr)
							{
								origin = invalid;
							}
							else
							{
								if (parent->_left == newRoot)
									origin = left;
								else
									origin = right;
							}
							curr = parent;
						}
						else
							assert(0); // 不存在的分支
					}
					else
						assert(0);
				}
			}

			delete practice;
			return true;
		}

	private:

		void debug(Node* root)
		{
			if (root == nullptr)
			{
				printf("                                            NULL\n");
				return;
			}

			printf("                                            ");
			printf("[root:%d]", root->_value.first);
			printf("(bf:%d)\n", root->_balanceFactor);

			Node* subL = root->_left;
			Node* subR = root->_right;

			if (subL)
			{
				printf("                  ");
				printf("[subL:%d]", subL->_value.first);
				printf("(bf:%d)                                       ", subL->_balanceFactor);
			}
			else
			{
				printf("                  ");
				printf("NULL                                       ");
			}

			if (subR)
			{
				printf("[subR:%d]", subR->_value.first);
				printf("(bf:%d)\n", subR->_balanceFactor);
			}
			else
			{
				printf("NULL");
			}

			if (subL)
			{
				Node* subLL = subL->_left;
				if (subLL)
				{
					printf("[subLL](height:%d bf:%d)     ", _height(subLL), subLL->_balanceFactor);
				}
				else
				{
					printf("            NULL             ");
				}

				Node* subLR = subL->_right;
				if (subLR)
				{
					printf("[subLR](height:%d bf:%d)     ", _height(subLR), subLR->_balanceFactor);
				}
				else
				{
					printf("            NULL             ");
				}
			}
			else
			{
				printf("            NULL             ");
				printf("            NULL             ");
			}

			if (subR)
			{
				Node* subRL = subR->_left;
				if (subRL)
				{
					printf("[subLL](height:%d bf:%d)     ", _height(subRL), subRL->_balanceFactor);
				}
				else
				{
					printf("            NULL             ");
				}

				Node* subRR = subR->_right;
				if (subRR)
				{
					printf("[subLR](height:%d bf:%d)     ", _height(subRR), subRR->_balanceFactor);
				}
				else
				{
					printf("            NULL             ");
				}
			}
			else
			{
				printf("            NULL             ");
				printf("            NULL             ");
			}

			printf("\n======================================================END======================================================\n\n");

		}

		// 在平衡化过程中标记子树来源
		enum source
		{
			left,
			right,
			invalid // 没有parent
		};

		// Left Rotation  左单旋
		void _RotaLe(Node* parent)  // _表示该接口是私有的
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


			// 平衡因子的更新
			parent->_balanceFactor = 0;
			subR->_balanceFactor = 0;
		}

		void _RotaRi(Node* parent)
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

			parent->_balanceFactor = 0;
			subL->_balanceFactor = 0;
		}

		void _RotaLR(Node* parent)
		{
			Node* subL = parent->_left;
			Node* subLR = subL->_right;

			int flag = subLR->_balanceFactor;

			_RotaLe(subL);
			_RotaRi(parent);

			if (flag == -1)
			{
				parent->_balanceFactor = 0;
				subL->_balanceFactor = 1;
				(void)subLR->_balanceFactor;  // 这个成员不用处理 右单旋已经处理过了
			}
			else if (flag == 1)
			{
				parent->_balanceFactor = -1;
				subL->_balanceFactor = 0;
				(void)subLR->_balanceFactor;
			}
			else
			{
				// flag == 0
				assert(flag == 0); // 万一出错，就报错
				parent->_balanceFactor = 0;
				subL->_balanceFactor = 0;
				(void)subLR->_balanceFactor;
			}
		}

		void _RotaRL(Node* parent)
		{
			Node* subR = parent->_right;
			Node* subRL = subR->_left;

			int flag = subRL->_balanceFactor;

			_RotaRi(subR);
			_RotaLe(parent);


			if (flag == -1)
			{
				parent->_balanceFactor = 1;
				subR->_balanceFactor = 0;
				(void)subRL->_balanceFactor;
			}
			else if (flag == 1)
			{
				parent->_balanceFactor = 0;
				subR->_balanceFactor = -1;
				(void)subRL->_balanceFactor;
			}
			else
			{
				// flag == 0
				assert(flag == 0);
				parent->_balanceFactor = 0;
				subR->_balanceFactor = 0;
				(void)subRL->_balanceFactor;
			}
		}

		int _height(Node* root)
		{
			if (root == nullptr)
				return 0;

			int left_height = _height(root->_left);
			int right_height = _height(root->_right);

			return std::max(left_height, right_height) + 1;
		}

		// 检查当前对象中的树是否为AVLTree
		bool _isAVLTree(Node* root)
		{
			if (root == nullptr)
				return true;

			int left_height = _height(root->_left);
			int right_height = _height(root->_right);

			int i = left_height - right_height;

			if (i != root->_balanceFactor)
			{
				std::cout << "平衡因子存在问题" << std::endl;
				std::cout << "当前节点包含的关键值为" << root->_value.first << std::endl;
			}

			if (std::abs(i) >= 2)
				return false;

			return _isAVLTree(root->_left) && _isAVLTree(root->_right);
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