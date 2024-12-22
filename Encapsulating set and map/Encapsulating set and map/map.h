#pragma once
#include"Base_Tree.h"

namespace wind
{
	template<class Key, class Value, class cmp = Less<Key>>
	class map
	{
		struct KeyOfValue
		{
			const Key& operator()(const std::pair<Key, Value>& value)
			{
				return value.first;
			}
		};

		typedef std::pair<const Key, Value> value_type;
		typedef BaseTree<Key, value_type, KeyOfValue, cmp> BaseTree;
		typedef typename BaseTree::const_reference const_reference;
	public:
		typedef typename BaseTree::iterator iterator;
		typedef typename BaseTree::const_iterator const_iterator;
		typedef typename BaseTree::reverse_iterator reverse_iterator;
		typedef typename BaseTree::const_reverse_iterator const_reverse_iterator;
		
	private:
		typedef std::pair<iterator, bool> ret_type;
	public:

		ret_type insert(const_reference value)
		{
			return _Container.insert(value);
		}

		iterator begin()
		{
			return _Container.begin();
		}

		iterator end()
		{
			return _Container.end();
		}

		const_iterator begin()const
		{
			return _Container.begin();
		}

		const_iterator end()const
		{
			return _Container.end();
		}

		reverse_iterator rbegin()
		{
			return _Container.rbegin();
		}

		reverse_iterator rend()
		{
			return _Container.rend();
		}

		const_reverse_iterator rbegin()const
		{
			return _Container.rbegin();
		}

		const_reverse_iterator rend()const
		{
			return _Container.rend();
		}

		Value& operator[](const Key& key)
		{
			// 没有对应的key 就插入一个默认构造的Value
			ret_type ret = insert(std::make_pair(key, Value()));
			// 插入成功 返回新插入节点的迭代器
			// 插入失败 返回原来就有节点的迭代器
			// first就是ret的第一个成员
			// 也就是那个迭代器
			// 迭代器有operator->重载
			// 这样就能节点里的_value的地址
			// 对于map _value是pair<Key, Value>
			// 所以返回的就是Value的引用
			return ret.first->second;
		}

	private:
		BaseTree _Container;
	};
}