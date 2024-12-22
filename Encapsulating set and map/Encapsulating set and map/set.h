#pragma once
#include"Base_Tree.h"

namespace wind
{
	template<class Key, class cmp =  Less<Key>>
	class set
	{
		struct KeyOfValue
		{
			const Key& operator()(const Key& value)
			{
				return value;
			}
		};

		typedef Key value_type;
		typedef BaseTree<Key, value_type, KeyOfValue, cmp> BaseTree;
		typedef typename BaseTree::const_reference const_reference;
	public:
		typedef typename BaseTree::const_iterator iterator;
		typedef typename BaseTree::const_iterator const_iterator;
		typedef typename BaseTree::const_reverse_iterator reverse_iterator;
		typedef typename BaseTree::const_reverse_iterator const_reverse_iterator;
		
	private:
		typedef std::pair<iterator, bool> ret_type;

	public:

		ret_type insert(const_reference value)
		{
			return _Container.insert(value);
		}

		iterator begin()const
		{
			return _Container.begin();
		}

		iterator end()const
		{
			return _Container.end();
		}

		reverse_iterator rbegin()const
		{
			return _Container.rbegin();
		}

		reverse_iterator rend()const
		{
			return _Container.rend();
		}

	private:
		BaseTree _Container;
	};
}