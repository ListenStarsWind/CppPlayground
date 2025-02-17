#pragma once

#include<vector>
#include<string>
#include<utility>
#include<iostream>

namespace wind
{
	// 节点的状态
	enum State_type
	{
		valid,   // 节点有效
		remove,  // 节点中的值被删除
		empty    // 节点为空
	};

	// 针对K-V模型的元素节点
	template<class Key, class Value, class Predicate>
	struct Node
	{
		typedef Key key_type;
		typedef Value mapped_type;
		typedef std::pair<key_type, mapped_type> value_type;
		typedef Predicate key_equal;
		typedef value_type& reference;
		typedef const value_type& const_reference;


		value_type _value;
		State_type _state;

		Node()
			:_value(value_type())
			, _state(empty)
		{
		}

		// 提取节点状态  私有接口  增强可读性
		inline State_type& state_of_node()
		{
			return _state;
		}

		inline const State_type& state_of_node()const
		{
			return _state;
		}

		// 提取节点中的值
		inline const_reference value_of_node()const
		{
			return _value;
		}

		// 查询节点关键字
		inline const key_type& key_of_node()const
		{
			return _value.first;
		}

		inline void enable(const_reference v)
		{
			_value = v;
			_state = valid;
		}

		// 检查节点是否有效
		inline bool validity()const
		{
			if (_state == valid)
				return true;
			else
				return false;
		}

		// 删除一个节点中的值
		inline void Remove()
		{
			_state = remove;
		}
	};

	template<class T>
	struct equal_to
	{
		bool operator()(const T& k1, const T& k2)
		{
			return k1 == k2;
		}
	};

	//通用哈希值映射模版
	template<class T>
	struct HashMapper
	{
		size_t operator()(const T& v)
		{
			return (size_t)v;
		}
	};

	//针对字符串类型的模版特例化
	template <>
	struct HashMapper<std::string>
	{
		size_t operator()(const std::string& s)
		{
			size_t hash = 0;
			for (auto e : s)
			{
				hash *= 131;
				hash += e;
			}
			return hash;
		}
	};

	template<class key, class Value, class Hash = HashMapper<key>, class Predicate = equal_to<key> >
	class HashTable
	{
		typedef Node<key, Value, Predicate> node_type;      // 哈希表中的基本节点
		typedef std::vector<node_type> table_type;          // 哈希表的底层容器
		typedef Hash hasher;								// 将 Key 转化为 size_t
		typedef Predicate equal;							// 比较关键值是否相等
		typedef size_t size_type;							// 用来计量有效元素个数
		typedef size_t factor_type;                         // 用来计量负载因子 factor_type%形式 

		typedef typename node_type::value_type value_type;  // 面向用户的基本数据
		typedef typename node_type::const_reference const_reference;
		typedef typename node_type::key_type key_type;

		typedef HashTable<key, Value, Hash, Predicate> self;

		table_type _table;
		size_type _size;
		size_type _max_size;
		factor_type _load;
		factor_type _max_load;


		inline bool keep_find(const node_type& node)const
		{
			if (node.state_of_node() == empty)
				return false;
			else
				return true;
		}

	public:
		HashTable()
			:_table(table_type(10))   // 默认10个可支配节点
			, _size(0)
			, _max_size(_table.size())
			, _load(0)
			, _max_load(70)
		{
		}

		HashTable(size_type num)
			:_table(table_type(num))   // 用户自定义支配节点个数
			, _size(0)
			, _max_size(_table.size())
			, _load(0)
			, _max_load(70)
		{
		}

		// 提取最大负载因子
		inline factor_type& max_load_factor()
		{
			return _max_load;
		}

		// 检查当前负载因子
		inline const factor_type& load_factor()const
		{
			return _load;
		}

		// 计算哈希表中的有效元素个数
		inline size_type size()const
		{
			return _size;
		}

		// 计算当前底层容器中可支配的最大节点个数
		inline size_type max_size()const
		{
			return _table.size();
		}

		void swap(self& that)
		{
			std::swap(_table, that._table);
			std::swap(_size, that._size);
			std::swap(_max_size, that._max_size);
			std::swap(_load, that._load);
			std::swap(_max_load, that._max_load);
		}

		int find(const key_type& key)const
		{
			size_type Max_size = max_size();
			size_t hash = hasher()(key);
			size_t position = hash % Max_size;
			while (keep_find(_table[position]))
			{
				// 前面那个条件是重点   
				if (_table[position].validity() && equal()(_table[position].key_of_node(), key))
					return position;

				position++;
				position %= Max_size;
			}

			return -1;
		}

		bool insert(const_reference v)
		{
			// 哈希表中是否已经存在该关键值
			if (find(v.first) != -1)
				return false;

			// 检查负载因子
			if (load_factor() > max_load_factor())
			{
				size_type size = max_size();
				self tmp(size * 2);
				for (const auto& e : _table)
				{
					if (e.validity())
						tmp.insert(e.value_of_node());
				}

				swap(tmp);
			}

			// 插入逻辑
			size_type Max_size = max_size();
			size_t hash = hasher()(v.first);
			size_t position = hash % Max_size;
			while (_table[position].validity())
			{
				position++;
				position %= Max_size;
			}
			_table[position].enable(v);
			_size++;

			// 更新负载因子
			_load = size() * 100 / Max_size;

			return true;
		}

		bool erase(const key_type& key)
		{
			int pos = find(key);
			if (pos != -1)
			{
				_table[pos].Remove();
				_size--;

				_load = size() * 100 / max_size();
				return true;
			}
			else
				return false;
		}

		void print()const
		{
			for (size_t i = 0; i < _table.size(); i++)
			{
				std::cout << "[" << i << "]-> ";
				if (_table[i].validity())
					std::cout << _table[i].value_of_node().first;
				std::cout << std::endl;
			}
			std::cout << std::endl;
		}
	};
}


namespace whisper
{
	template<class T>
	struct equal_to
	{
		bool operator()(const T& k1, const T& k2)
		{
			return k1 == k2;
		}
	};

	//通用哈希值映射模版
	template<class T>
	struct HashMapper
	{
		size_t operator()(const T& v)
		{
			return (size_t)v;
		}
	};

	//针对字符串类型的模版特例化
	template <>
	struct HashMapper<std::string>
	{
		size_t operator()(const std::string& s)
		{
			size_t hash = 0;
			for (auto e : s)
			{
				hash *= 131;
				hash += e;
			}
			return hash;
		}
	};

	template<class T>
	struct Node
	{
		typedef T value_type;
		typedef value_type* pointer;
		typedef value_type& reference;
		typedef Node<value_type> self;
		typedef self* link_type;
		typedef const value_type* const_pointer;
		typedef const value_type& const_reference;

		value_type _value;
		link_type _next;

		Node(const_reference v)
			:_value(v)
			, _next(nullptr)
		{
		}

		inline link_type& __link_of_node()
		{
			return _next;
		}

		inline link_type __next_node()
		{
			return __link_of_node();
		}

		inline const value_type& __value_of_node()
		{
			return _value;
		}
	};

	template<class key, class Value, class Hash = HashMapper<key>, class Predicate = equal_to<key> >
	class HashBucker
	{
		typedef key key_type;
		typedef Value mapped_type;
		typedef Hash hasher;
		typedef Predicate key_equal;
		typedef size_t size_type;
		typedef size_t factor_type;
		typedef HashBucker<key, Value, Hash, Predicate> self;

		typedef std::pair<key_type, mapped_type> value_type;
		typedef Node<value_type> node_type;
		typedef typename node_type::pointer pointer;
		typedef typename node_type::reference reference;
		typedef typename node_type::const_pointer const_pointer;
		typedef typename node_type::const_reference const_reference;
		typedef typename node_type::link_type link_type;
		typedef std::vector<link_type> link_table;

		link_table _table;
		size_type _size;
		size_type _max_size;
		factor_type _load;
		factor_type _max_load;

		inline link_type _create_node(const_reference v)const
		{
			link_type p = new node_type(v);
			return p;
		}

		inline void _destroy_node(link_type p)const
		{
			delete p;
		}

		inline const key_type& _key_of_node(link_type p)const
		{
			return p->_value.first;
		}

	public:
		HashBucker()
			:_table(link_table(10))   // 默认10个可支配节点
			, _size(0)
			, _max_size(_table.size())
			, _load(0)
			, _max_load(100)
		{
		}

		HashBucker(size_type num)
			:_table(link_table(num))   // 用户自定义支配节点个数
			, _size(0)
			, _max_size(_table.size())
			, _load(0)
			, _max_load(100)
		{
		}

		~HashBucker()
		{
			size_t size = max_size();
			for (size_t i = 0; i < size; i++)
			{
				link_type curr = _table[i];
				while (curr)
				{
					_destroy_node(curr);
					curr = curr->__next_node();
				}
				_table[i] = nullptr;
			}
		}

		// 提取最大负载因子
		inline factor_type& max_load_factor()
		{
			return _max_load;
		}

		// 检查当前负载因子
		inline const factor_type& load_factor()const
		{
			return _load;
		}

		// 计算哈希表中的有效元素个数
		inline size_type size()const
		{
			return _size;
		}

		// 计算当前底层容器中可支配的最大节点个数
		inline size_type max_size()const
		{
			return _table.size();
		}

		void swap(self& that)
		{
			std::swap(_table, that._table);
			std::swap(_size, that._size);
			std::swap(_max_size, that._max_size);
			std::swap(_load, that._load);
			std::swap(_max_load, that._max_load);
		}

		link_type find(const key_type& key)
		{
			size_type Max_size = max_size();
			size_t hash = hasher()(key);
			size_t position = hash % Max_size;
			link_type curr = _table[position];
			key_equal equal;
			while (curr)
			{
				if (equal(curr->__value_of_node().first, key))
					return curr;
				curr = curr->__next_node();
			}

			return nullptr;
		}

		bool insert(const_reference v)
		{
			// 哈希表中是否已经存在该关键值
			if (find(v.first))
				return false;

			// 检查负载因子
			if (load_factor() >= max_load_factor())
			{
				size_type Max_size = max_size() * 2;
				link_table tmp(Max_size);
				hasher h;
				for (size_t i = 0; i < _table.size(); i++)
				{
					link_type curr = _table[i];
					while (curr)
					{
						link_type next = curr->__next_node();
						size_t hash = h(curr->__value_of_node().first);
						size_t position = hash % Max_size;
						curr->__link_of_node() = tmp[position];
						tmp[position] = curr;
						curr = next;
					}

					// 不写也可以吗?
					//_table[i] = nullptr;
				}
				_table.swap(tmp);
				_max_size = max_size();


				/*for (auto curr : _table)
				{
					while (curr)
					{
						link_type next = curr->__next_node();
						size_t hash = h(curr->__value_of_node().first);
						size_t position = hash % Max_size;
						curr->__link_of_node() = tmp[position];
						tmp[position] = curr;
						curr = next;
					}
				}
				_table.swap(tmp);*/


				///////////////////////////////////////////////////

				/*size_type Max_size = max_size();
				self tmp(Max_size * 2);
				for (auto e : _table)
				{
					while (e)
					{
						tmp.insert(e->__value_of_node());
						e = e->__next_node();
					}
				}
				swap(tmp);*/
			}

			// 插入逻辑
			size_type Max_size = max_size();
			size_t hash = hasher()(v.first);
			size_t position = hash % Max_size;
			link_type newNode = _create_node(v);
			newNode->__link_of_node() = _table[position];
			_table[position] = newNode;
			_size++;

			// 更新负载因子
			_load = size() * 100 / Max_size;

			return true;
		}

		bool erase(const key_type& key)
		{
			size_t position = key % max_size();
			link_type curr = _table[position];
			link_type prev = nullptr;
			while (curr)
			{
				if (key_equal()(curr->__value_of_node().first, key))
				{
					if (prev == nullptr)
						_table[position] = nullptr;
					else
						prev->__link_of_node() = curr->__link_of_node();

					_destroy_node(curr);
					return true;
				}

				prev = curr;
				curr = curr->__next_node();
			}

			return false;
		}

		void print()const
		{
			for (auto e : _table)
			{
				while (e)
				{
					std::cout << e->__value_of_node().first << "->" << e->__value_of_node().second << std::endl;
					e = e->__next_node();
				}
			}
			std::cout << std::endl;
		}

		void bucketStats(size_t& maxBucketSize, size_t& currentSize, size_t& nonEmptyBuckets, size_t& maxBucketLength, double& averageBucketLength, double& loadFactor, double& maxLoadFactor)
		{
			maxBucketSize = max_size();
			currentSize = _size;
			nonEmptyBuckets = 0;
			maxBucketLength = 0;
			loadFactor = static_cast<double>(load_factor()) / 100.0f;
			maxLoadFactor = static_cast<double>(max_load_factor()) / 100.0f;

			for (size_t i = 0; i < _table.size(); ++i)
			{
				size_type bucketLength = 0;
				link_type currentNode = _table[i];
				if (currentNode)
				{
					nonEmptyBuckets++;
				}
				while (currentNode)
				{
					bucketLength++;
					currentNode = currentNode->__next_node();
				}
				if (bucketLength > maxBucketLength)
				{
					maxBucketLength = bucketLength;
				}
			}
			
			// static_cast<typedef>是C++所倡导的专门用于强制类型转换的操作符
			averageBucketLength = static_cast<double>(currentSize) / static_cast<double>(nonEmptyBuckets);
		}
	};
}

namespace myTemplate
{
	template<class T>
	struct equal_to
	{
		bool operator()(const T& k1, const T& k2)
		{
			return k1 == k2;
		}
	};

	//通用哈希值映射模版
	template<class T>
	struct HashMapper
	{
		size_t operator()(const T& v)
		{
			return (size_t)v;
		}
	};

	//针对字符串类型的模版特例化
	template <>
	struct HashMapper<std::string>
	{
		size_t operator()(const std::string& s)
		{
			size_t hash = 0;
			for (auto e : s)
			{
				hash *= 131;
				hash += e;
			}
			return hash;
		}
	};

	template<class _Val, class _Key, class _ExtractKey>
	struct _Hashtable_node
	{
		typedef _Hashtable_node<_Val, _Key, _ExtractKey> self;
		typedef self* link_type;
		_Val _val;
		link_type _next;

		_Hashtable_node(const _Val& v)
			:_val(v)
			, _next(nullptr)
		{
		}

		inline _Val& _value_of_node()
		{
			return _val;
		}

		inline const _Val& _value_of_node()const
		{
			return _val;
		}

		inline const _Key& _key_of_node()const
		{
			return _ExtractKey()(_value_of_node());
		}

		inline link_type& _next_node()
		{
			return _next;
		}
	};


	template <class _Val, class _Key, class _HashFcn, class _ExtractKey, class _EqualKey>
	class HashTable;

	template <class _Val, class _Key, class pointer, class reference, class _HashFcn, class _ExtractKey, class _EqualKey>
	class _hash_iterator
	{
		typedef HashTable<_Val, _Key, _HashFcn, _ExtractKey, _EqualKey> HashTable;
		typedef _hash_iterator<_Val, _Key, pointer, reference, _HashFcn, _ExtractKey, _EqualKey> self;
		typedef const HashTable* tablePtr;
		typedef typename HashTable::link_type link_type;
		typedef typename HashTable::size_type size_type;

		link_type _pNode;
		tablePtr _pTable;

	public:

		_hash_iterator(link_type pNode, tablePtr pTable)
			:_pNode(pNode)
			, _pTable(pTable)
		{}

		reference operator*()
		{
			return _pNode->_value_of_node();
		}

		pointer operator->()
		{
			return &(this->operator*());
		}

		self& operator++()
		{
			link_type next = _pNode->_next_node();
			if (next == nullptr)
			{
				size_type max_size = _pTable->maxBucketCount();
				size_t hash = _HashFcn()(_pNode->_key_of_node());
				size_t position = hash % max_size;
				while (!_pTable->_buckets[++position])
				{
					if (position == max_size - 1)
					{
						_pNode = nullptr;
						return *this;
					}
				}
				next = _pTable->_buckets[position];
			}

			_pNode = next;
			return *this;
		}

		bool operator==(const self& that)const
		{
			if (_pNode == that._pNode)
				return true;
			else
				return false;
		}

		bool operator!=(const self& that)const
		{
			return !this->operator==(that);
		}

	};

	//unordered_map<_Key, _Tp, _HashFn, _EqualKey>::HashTable< pair<const _Key, _Tp>, _Key, _HashFn, _ExtractKey, _EqualKey>
	//unordered_set<_Key, _HashFn, _EqualKey>::HashTable< const _Key, _Key, _HashFn, _ExtractKey, _EqualKey>
	template <class _Val, class _Key, class _HashFcn, class _ExtractKey, class _EqualKey>
	class HashTable
	{
	public:
		typedef _Key key_type;
		typedef _Val value_type;
		typedef _HashFcn hasher;
		typedef _EqualKey key_equal;
		typedef size_t size_type;
		typedef value_type* pointer;
		typedef value_type& reference;
		typedef const value_type* const_pointer;
		typedef const value_type& const_reference;
		typedef _Hashtable_node<value_type, key_type, _ExtractKey> node_type;
		typedef node_type* link_type;
		typedef std::vector<link_type> bucket_type;
		typedef HashTable<_Val, _Key, _HashFcn, _ExtractKey, _EqualKey> self;
		typedef _hash_iterator<value_type, key_type, pointer, reference, _HashFcn, _ExtractKey, _EqualKey> iterator;
		typedef _hash_iterator<value_type, key_type, const_pointer, const_reference, _HashFcn, _ExtractKey, _EqualKey> const_iterator;
		friend iterator;
		friend const_iterator;

	private:

		hasher _hash;
		key_equal _equals;
		_ExtractKey _get_key;
		bucket_type _buckets;
		size_type _num_elements;
		double _load;
		double _max_load;

		inline link_type _create_node(const_reference v)
		{
			return new node_type(v);
		}

		inline void _destroy_node(link_type node)
		{
			delete node;
		}

	public:

		HashTable()
			:_buckets(bucket_type(10))
			, _num_elements(0)
			, _load(0.0f)
			, _max_load(1.0f)
		{
		}


		HashTable(size_type reserved)
			:_buckets(bucket_type(reserved))
			, _num_elements(0)
			, _load(0.0f)
			, _max_load(1.0f)
		{
		}

		~HashTable()
		{
			size_t size = _buckets.size();
			for (size_t i = 0; i < size; i++)
			{
				link_type curr = _buckets[i];
				while (curr)
				{
					_destroy_node(curr);
					curr = curr->_next_node();
				}
				_buckets[i] = nullptr;
			}
		}

		iterator begin()
		{
			for (size_t i = 0; i < maxBucketCount(); i++)
			{
				if (_buckets[i])
					return iterator(_buckets[i], this);
			}
			return end();
		}

		iterator end()
		{
			return iterator(nullptr, this);
		}

		const_iterator begin()const
		{
			for (size_t i = 0; i < maxBucketCount(); i++)
			{
				if (_buckets[i])
					return const_iterator(_buckets[i], this);
			}
			return end();
		}

		const_iterator end()const
		{
			return const_iterator(nullptr, this);
		}

		// 计算vector中理论存放bucket的上限
		inline size_type maxBucketCount()const
		{
			return _buckets.size();
		}

		// 提取最大负载因子
		inline double& max_load_factor()
		{
			return _max_load;
		}

		inline const double& max_load_factor()const
		{
			return _max_load;
		}

		// 检查当前负载因子
		inline const double& load_factor()const
		{
			return _load;
		}

		// 计算哈希表中的有效元素个数
		inline const size_type& size()const
		{
			return _num_elements;
		}

		void swap(self& that)
		{
			std::swap(_buckets, that._buckets);
			std::swap(_num_elements, that._num_elements);
			std::swap(_load, that._load);
			std::swap(_max_load, that._max_load);
		}

		link_type find(const key_type& key)
		{
			size_type max_size = maxBucketCount();
			size_t hash = _hash(key);
			size_t position = hash % max_size;
			link_type curr = _buckets[position];
			while (curr)
			{
				if (_equals(curr->_key_of_node(), key))
					return curr;
				curr = curr->_next_node();
			}

			return nullptr;
		}
		
		std::pair<link_type, bool> insert(const_reference v)
		{
			// 哈希表中是否已经存在该关键值
			link_type p = find(_get_key(v));
			if (p != nullptr)
				return {p, false};

			// 检查负载因子
			if (load_factor() >= max_load_factor())
			{
				size_type max_size = maxBucketCount() * 2;
				bucket_type tmp(max_size);
				for (size_t i = 0; i < maxBucketCount(); i++)
				{
					link_type curr = _buckets[i];
					while (curr)
					{
						link_type next = curr->_next_node();
						size_t hash = _hash(curr->_key_of_node());
						size_t position = hash % max_size;
						curr->_next_node() = tmp[position];
						tmp[position] = curr;
						curr = next; 
					}
				}
				_buckets.swap(tmp);
			}

			// 插入逻辑
			size_type max_size = maxBucketCount();
			size_t hash = _hash(_get_key(v));
			size_t position = hash % max_size;
			link_type newNode = _create_node(v);
			newNode->_next_node() = _buckets[position];
			_buckets[position] = newNode;
			_num_elements++;

			// 更新负载因子
			_load = static_cast<double>(size()) / static_cast<double>(max_size);

			return {newNode , true};
		}

		bool erase(const key_type& key)
		{
			size_t position = key % maxBucketCount();
			link_type curr = _buckets[position];
			link_type prev = nullptr;
			while (curr)
			{
				if (_equals(curr->_key_of_node(), key))
				{
					if (prev == nullptr)
						_buckets[position] = nullptr;
					else
						prev->_next_node() = curr->_next_node();

					_destroy_node(curr);
					return true;
				}
				prev = curr;
				curr = curr->_next_node();
			}

			return false;
		}
	};
}