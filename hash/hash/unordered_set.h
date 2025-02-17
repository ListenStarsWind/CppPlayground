#pragma once

#include"HashTable.h"

namespace wind
{
	template <class _Key, class _HashFn = myTemplate::HashMapper<_Key>, class _EqualKey = myTemplate::equal_to<_Key>>
	class unordered_set
	{
		typedef _Key _Val;

		struct KeyOfValue
		{
			const _Key& operator()(const _Val& value)
			{
				return value;
			}
		};

		typedef myTemplate::HashTable<_Val, _Key, _HashFn, KeyOfValue, _EqualKey> HashTable;

		typedef typename HashTable::const_reference const_reference;
		typedef typename HashTable::key_type key_type;
		typedef typename HashTable::link_type link_type;
		
		HashTable _hashTable;

	public:
		typedef typename HashTable::const_iterator iterator;
		typedef typename HashTable::const_iterator const_iterator;

		iterator begin()const
		{
			return _hashTable.begin();
		}

		iterator end()const
		{
			return _hashTable.end();
		}

		std::pair<iterator, bool> insert(const_reference v)
		{
			auto ret = _hashTable.insert(v);
			return { iterator(ret.first, &_hashTable), ret.second };
		}

		bool erase(const key_type& key)
		{
			return _hashTable.erase(key);
		}
	};
}