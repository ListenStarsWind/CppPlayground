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
		int _balanceFactor; // Լ��ƽ����������������ȼ�ȥ���������
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
			// ���val1 ��С�� val2
			// ����val2 ��С�� val1
			// ��˵�����������
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

		// �Ȳ����ǵ�������������ǻ��Ƿ��ز���ֵ
		bool Insert(const value_type& val)
		{
			// ��һ���ڵ������Ȼ��ƽ���
			if (_root == nullptr)
			{
				Node* newNode = new Node(val);
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

			// ����ƽ�������Լ����Ҽ��
			while (parent) // ��������Ѿ�û�нڵ��ˣ���˵���������Ѿ�����������
			{
				// ���¸��ڵ�ƽ������
				if (location == parent->_left)
					parent->_balanceFactor++;
				else
					parent->_balanceFactor--;

				if (parent->_balanceFactor == 0)
				{
					// ��ǰ���ĸ߶Ȳ��ı� ����ѭ��
					break;
				}
				else if (parent->_balanceFactor == 1 || parent->_balanceFactor == -1)
				{
					// ��ǰ���ĸ߶ȼ�һ��Ӱ�����ϼ��ڵ㣬���л���
					location = parent;
					parent = parent->_parent;
				}
				else if (parent->_balanceFactor == 2 || parent->_balanceFactor == -2)
				{
					// ������Ѿ�����AVLTree�ˣ���Ҫ����

					// ��һ���ࣺ������ת
					if (parent->_balanceFactor == 2 && location->_balanceFactor == 1)
					{
						// �ҵ���
						_RotaRi(parent);
					}
					else if (parent->_balanceFactor == -2 && location->_balanceFactor == -1)
					{
						// ����
						_RotaLe(parent);
					}

					// �ڶ����ࣺ������ת
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

					// �������Ѿ�����ƽ���ˣ����Ҹ߶�û�иı�
					break;
				}
				else
				{
					// �����ϲ����ڵķ�֧��������룬���������˵��ƽ�����ӵĸ��´�������
					assert(0);   // ֱ���Ա�
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
			Node* should = find(key); // Ӧ�ñ�ɾ���Ľڵ㣨�����Ľڵ㣩
			if (should == nullptr)
				return false;

			// debug
			if (key == -1)
			{
				debug_lock = 1;
			}

			// ת�Ƽ������ͷŵ�����: should->practice
			Node* practice = nullptr; // ʵ�ʻᱻɾ���Ľڵ㣨���ڹ��Ľڵ㣩
			source origin = invalid;  // ���practice����parent������������������
			if (should->_left == nullptr)// ����������
			{
				practice = should; // �Լ����Ļ��Լ��е�
				Node* practice_only_sub = practice->_right;
				Node* practice_parent = practice->_parent;

				// ���ź���
				if (practice_parent == nullptr)
				{
					// �������̳�������
					_root = practice_only_sub;
					if(practice_only_sub)
					practice_only_sub->_parent = nullptr;
					(void)origin;
				}
				else
				{
					// ���ϼ��ڵ��й�
					if (practice_parent->_left == practice)
					{
						practice_parent->_left = practice_only_sub;
						if (practice_only_sub) // �������Ͳ�����ǰ����
							practice_only_sub->_parent = practice_parent;
						origin = left;
					}
					else
					{
						practice_parent->_right = practice_only_sub;
						if (practice_only_sub) // �������Ͳ�����ǰ����
							practice_only_sub->_parent = practice_parent;
						origin = right;
					}
				}
			}
			else if (should->_right == nullptr) //����������
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
				// should����������

				//��������
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
					// ��дshould�ڵ㣬�����ͷŵĽڵ��Ϊ�������ݵĽڵ�
					practice = next;
					//should->_value = practice->_value;
					std::swap(should->_value, practice->_value);


					// �й�
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
					
					// �й�
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
			curr = practice->_parent;  // ��ǰ�������ڵ�

			// ��ƽ�⻯
			while (curr)
			{
				if (debug_lock)
				{
					debug(curr);
					const char* str = "Debug";
				}

				//// ƽ�����ӵ�������
				//if (origin == invalid)
				//{
				//	// ������Ϊ���µĸ��ڵ㣬����ƽ�⻯
				//	break;
				//}
				//else 

				if (origin == left)
				{
					// curr�������߶Ƚ��ή��
					curr->_balanceFactor--;
				}
				else if (origin == right)
				{
					// curr�������߶Ƚ��ή��
					curr->_balanceFactor++;
				}
				else
				{
					// �����ڵķ�֧
					assert(0);
				}

				if (debug_lock)
				{
					debug(curr);
					const char* str = "Debug";
				}

				// ���ƽ����
				if (curr->_balanceFactor == 0)
				{
					// curr������ĸ߶Ƚ���
					// ���ݵ���һ������
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
					// curr������߶Ȳ���
					// �����鷳��һ������
					break;
				}
				else if (std::abs(curr->_balanceFactor) == 2)
				{
					// curr������Ѿ�ʧ��
					// ��Ҫ����
						
					// ��һ�����������Ϊ�������μ�ƽ���������ʧ��
					if (origin == left)
					{
						// ��ǰ�����:��������,��������
						Node* higher_sub = curr->_right;
						if (higher_sub->_balanceFactor == 0)
						{
							// ���������ǰɣ���������ת������,��������ת����ͻ���һЩ
							_RotaLe(curr);

							// ��δ����ǰ���������ĸ߶���h+2
							// ���ߵ������������������Ǹ߶���ͬ,����h
							// ԭ������·����Ϊ��ת��Ȼ���٣����ط���,�����h
							// ��������������·���߶ȣ�ɾ��ǰ(ɾ��ǰ��h)����һ��(�����h-1)����ת�󣬸߶�������һ����
							// �������������ĸ߶���h����������̨���¸��ڵ㣬����·���ĸ߶���h+1
							// ��������������·���߶�ȡ�����������֣���һ����ԭ����target�ڵ㣬������ת�������Ȼ�߶ȼ�һ
							// �ڶ��������Ǵ�ԭ���ϸ������������ƹ������ǿ�����,�߶�Ϊh,������̨�ĸ��ڵ㣬�ͱ����h+1,
							// �����˻����¸��ڵ㣬����������h+2
							// ���ϣ�����֮��ǰ���ĸ߶Ȳ������仯

							// ƽ�����ӵ�����
							higher_sub->_balanceFactor = 1;
							curr->_balanceFactor = -1;

							// �߶Ȳ������仯
							break;
						}
						else if (higher_sub->_balanceFactor == -1)
						{
							_RotaLe(curr);

							// ƽ�����Ӳ���Ҫ����,���Ǿ���0,�������������Ѿ��㹻
							// ���������߼�����,�߶ȼ�һ,��Ҫ���ݵ��ϼ���
							Node* newRoot = curr->_parent; // ��ת���µĸ��ڵ�
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
						// ���ֳ��ϲ���ֱ�ӽ�������
						// ��ʱ�ϸ������������߶�Ϊh
						// ������Ϊh-1
						// ֱ�ӵ�������ɵ�ǰ�������߶�Ϊh+1,
						// ����ǰ�������߶�Ϊh-1
						// ��������µĲ�ƽ��

						// ���ڽϸ�����˵,��������ƫ��
						// ��ǰһ���ڰٳ�,ǿ������ڸ�����
						// bf == 0ʱ�������ľ��ⷢչ,���ĸ������ȸ����˶���
						// bf == -1ʱ��Ȼ��ƫ��,�������������,�Լ���ǿ���Ļ�����
						// bf == 1�ǰ�ǿ�������,û��ǿ��֮��,�����һϵ����������ϱ�¶������

						// ���úõ�ʱ��,�����ⲻ������,���ò��õ�ʱ��,С�����Ǵ�����

						// ����Ҫ������ƽ��һ��,Ȼ����ȥ�����
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

							// bf���������
							if (bf == 0)
							{
								// ����ζ��,higher_subL�����������߶ȶ���h-1
								// ������ƽ��֮��,higher_sub�ĸ߶�Ϊh+1
								// ����higher_subLΪh-1,higher_subRΪh
								// Ҳ�����൱��higher_sub->_balanceFactor == -1�����
							}
							else if (bf == -1)
							{
								// higher_subLL::bf == h-2
								// higher_subLR::bf == h-1
								// ����ƽ���
								// new higher_subL::bf == h-2
								// new higher_subR::bf == h
								// new higher_sub::bf == h+1
								// ��Чhigher_sub->_balanceFactor == -1

							}
							else if (bf == 1)
							{
								// higher_subLL::bf == h-1
								// higher_subLR::bf == h-2
								// ����ƽ���
								// new higher_subL::bf == h-1
								// new higher_subR::bf == h   (old higher_subR::bf == h-1)
								// new higher_sub::bf == h+1
								// ��Чhigher_sub->_balanceFactor == -1
							}
							//////���������ͬ����
							_RotaLe(curr);
							// ƽ�����ӵĸ���
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
							
							Node* newRoot = curr->_parent; // ��ת���µĸ��ڵ�
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
							assert(0); // �����ڵķ�֧
					}
					else if (origin == right)
					{
						// ��ǰ�����:��������,��������
						Node* higher_sub = curr->_left;
						if (higher_sub->_balanceFactor == 0)
						{
							// ���������ǰɣ���������ת������,��������ת����ͻ���һЩ
							_RotaRi(curr);

							// ��δ����ǰ���������ĸ߶���h+2
							// ���ߵ������������������Ǹ߶���ͬ,����h
							// ԭ������·����Ϊ��ת��Ȼ���٣����ط���,�����h
							// ��������������·���߶ȣ�ɾ��ǰ(ɾ��ǰ��h)����һ��(�����h-1)����ת�󣬸߶�������һ����
							// �������������ĸ߶���h����������̨���¸��ڵ㣬����·���ĸ߶���h+1
							// ��������������·���߶�ȡ�����������֣���һ����ԭ����curr�ڵ㣬������ת�������Ȼ�߶ȼ�һ
							// �ڶ��������Ǵ�ԭ���ϸ������������ƹ������ǿ�����,�߶�Ϊh,������̨�ĸ��ڵ㣬�ͱ����h+1,
							// �����˻����¸��ڵ㣬����������h+2
							// ���ϣ�����֮��ǰ���ĸ߶Ȳ������仯

							// ƽ�����ӵ�����
							higher_sub->_balanceFactor = -1;
							curr->_balanceFactor = 1;

							// �߶Ȳ������仯
							break;
						}
						else if (higher_sub->_balanceFactor == 1)
						{
							_RotaRi(curr);

							// ƽ�����Ӳ���Ҫ����,���Ǿ���0,�������������Ѿ��㹻
							// ���������߼�����,�߶ȼ�һ,��Ҫ���ݵ��ϼ���
							Node* newRoot = curr->_parent; // ��ת���µĸ��ڵ�
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
						// ���ֳ��ϲ���ֱ�ӽ�������
						// ��ʱ�ϸ������������߶�Ϊh
						// ������Ϊh-1
						// ֱ�ӵ�������ɵ�ǰ�������߶�Ϊh+1,
						// ����ǰ�������߶�Ϊh-1
						// ��������µĲ�ƽ��

						// ���ڽϸ�����˵,��������ƫ��
						// ��ǰһ���ڰٳ�,ǿ������ڸ�����
						// bf == 0ʱ�������ľ��ⷢչ,���ĸ������ȸ����˶���
						// bf == -1ʱ��Ȼ��ƫ��,�������������,�Լ���ǿ���Ļ�����
						// bf == 1�ǰ�ǿ�������,û��ǿ��֮��,�����һϵ����������ϱ�¶������

						// ���úõ�ʱ��,�����ⲻ������,���ò��õ�ʱ��,С�����Ǵ�����

						// ����Ҫ������ƽ��һ��,Ȼ����ȥ�����
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

							// �������
							if (bf == 0)
							{
								// ����ζ��,higher_subL�����������߶ȶ���h-1
								// ������ƽ��֮��,higher_sub�ĸ߶�Ϊh+1
								// ����higher_subLΪh-1,higher_subRΪh
								// Ҳ�����൱��higher_sub->_balanceFactor == -1�����
							}
							else if (bf == -1)
							{
								// higher_subLL::bf == h-2
								// higher_subLR::bf == h-1
								// ����ƽ���
								// new higher_subL::bf == h-2
								// new higher_subR::bf == h
								// new higher_sub::bf == h+1
								// ��Чhigher_sub->_balanceFactor == -1

							}
							else if (bf == 1)
							{
								// higher_subLL::bf == h-1
								// higher_subLR::bf == h-2
								// ����ƽ���
								// new higher_subL::bf == h-1
								// new higher_subR::bf == h   (old higher_subR::bf == h-1)
								// new higher_sub::bf == h+1
								// ��Чhigher_sub->_balanceFactor == -1
							}
							//////���������ͬ����
							_RotaRi(curr);
							if (debug_lock)
							{
								debug(curr->_parent);
								const char* str = "debug";
							}

							// ƽ�����ӵĸ���

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

							Node* newRoot = curr->_parent; // ��ת���µĸ��ڵ�
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
							assert(0); // �����ڵķ�֧
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

		// ��ƽ�⻯�����б��������Դ
		enum source
		{
			left,
			right,
			invalid // û��parent
		};

		// Left Rotation  ����
		void _RotaLe(Node* parent)  // _��ʾ�ýӿ���˽�е�
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


			// ƽ�����ӵĸ���
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
				(void)subLR->_balanceFactor;  // �����Ա���ô��� �ҵ����Ѿ��������
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
				assert(flag == 0); // ��һ�����ͱ���
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

		// ��鵱ǰ�����е����Ƿ�ΪAVLTree
		bool _isAVLTree(Node* root)
		{
			if (root == nullptr)
				return true;

			int left_height = _height(root->_left);
			int right_height = _height(root->_right);

			int i = left_height - right_height;

			if (i != root->_balanceFactor)
			{
				std::cout << "ƽ�����Ӵ�������" << std::endl;
				std::cout << "��ǰ�ڵ�����Ĺؼ�ֵΪ" << root->_value.first << std::endl;
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