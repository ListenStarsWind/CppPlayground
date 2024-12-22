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
			// û�ж�Ӧ��key �Ͳ���һ��Ĭ�Ϲ����Value
			ret_type ret = insert(std::make_pair(key, Value()));
			// ����ɹ� �����²���ڵ�ĵ�����
			// ����ʧ�� ����ԭ�����нڵ�ĵ�����
			// first����ret�ĵ�һ����Ա
			// Ҳ�����Ǹ�������
			// ��������operator->����
			// �������ܽڵ����_value�ĵ�ַ
			// ����map _value��pair<Key, Value>
			// ���Է��صľ���Value������
			return ret.first->second;
		}

	private:
		BaseTree _Container;
	};
}