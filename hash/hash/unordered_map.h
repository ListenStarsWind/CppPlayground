#pragma once

#include"HashTable.h"

namespace wind
{
	//unordered_map<_Key, _Tp, _HashFn, _EqualKey>::HashTable< pair<const _Key, _Tp>, _Key, _HashFn, _ExtractKey, _EqualKey>
	//unordered_set<_Key, _HashFn, _EqualKey>::HashTable< const _Key, _Key, _HashFn, _ExtractKey, _EqualKey>
	template <class _Key, class _Tp, class _HashFn = myTemplate::HashMapper<_Key>, class _EqualKey = myTemplate::equal_to<_Key>>
	class unordered_map
	{
		typedef std::pair<const _Key, _Tp> _Val;

		struct KeyOfValue
		{
			const _Key& operator()(const _Val& value)
			{
				return value.first;
			}
		};

		typedef myTemplate::HashTable<_Val, _Key, _HashFn, KeyOfValue, _EqualKey> HashTable;
		
		typedef typename HashTable::const_reference const_reference;
		typedef typename HashTable::key_type key_type;
		typedef typename HashTable::link_type link_type;
		

		HashTable _hashTable;

	public:
		typedef typename HashTable::iterator iterator;
		typedef typename HashTable::const_iterator const_iterator;

		iterator begin()
		{
			return _hashTable.begin();
		}

		iterator end()
		{
			return _hashTable.end();
		}

		const_iterator begin()const
		{
			return _hashTable.begin();
		}

		const_iterator end()const
		{
			return _hashTable.end();
		}

		/*_Tp& operator[](const key_type& key)
		{
			link_type node = _hashTable.find(key);
			if (node == nullptr)
			{
				_hashTable.insert(std::make_pair(key, _Tp()));
				node = _hashTable.find(key);
			}
			return node->_value_of_node().second;
		}*/

		_Tp& operator[](const key_type& key)
		{
			auto pair = insert(std::make_pair(key, _Tp()));
			return pair.first->second;
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