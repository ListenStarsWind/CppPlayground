#pragma once

#include<vector>
#include<algorithm>
#include<assert.h>

namespace wind {

	template<class T>
	struct less
	{
		bool operator()(const T& val1, const T& val2)
		{
			return val1 < val2;
		}
	};

	template<class T>
	struct greater
	{
		bool operator()(const T& val1, const T& val2)
		{
			return val1 > val2;
		}
	};

	template<class T, class container = std::vector<T>, class compare = less<T>>
	class priority_queue
	{
		typedef priority_queue<T, container, compare> self;

		size_t find_parent(size_t child)
		{
			return (child - 1) / 2;
		}

		size_t find_first_child(size_t parent)
		{
			return parent * 2 + 1;
		}

		size_t find_second_child(size_t parent)
		{
			return parent * 2 + 2;
		}

		void adjust_up(size_t child)
		{
			compare cmp;
			while (child > 0)
			{
				size_t parent = find_parent(child);
				if (cmp(_con[child], _con[parent]))
				{
					break;
				}
				else
				{
					std::swap(_con[child], _con[parent]);
					child = parent;
				}
			}
		}

		void adjust_down(size_t parent)
		{
			while (parent < _con.size())
			{
				size_t child = 0;
				size_t first_child = find_first_child(parent);
				size_t second_child = find_second_child(parent);

				compare cmp;
				if (!(first_child < _con.size()))
					break;
				else if (!(second_child < _con.size()))
					child = first_child;
				else
				{
					if (cmp(_con[first_child], _con[second_child]))
					{
						child = second_child;
					}
					else
					{
						child = first_child;
					}
				}

				if (cmp(_con[child], _con[parent]))
					break;
				else
				{
					std::swap(_con[child], _con[parent]);
					parent = child;
				}
			}
		}

	public:
		priority_queue() {};
		~priority_queue() {};

		template <class InputIterator>
		priority_queue(InputIterator begin, InputIterator end)
			:_con(begin, end)
		{
			size_t parent = find_parent(_con.size() - 1);
			for( ; parent > 0 ; parent--)
			{
				adjust_down(parent);
			}
			if (parent == 0)
			{
				adjust_down(parent);
			}
		}

		void push(const T& val)
		{
			_con.push_back(val);
			adjust_up(_con.size() - 1);
		}

		void pop()
		{
			assert(_con.size());
			std::swap(_con[0], _con[_con.size() - 1]);
			_con.pop_back();
			adjust_down(0);
		}

		const T& top()
		{
			return _con[0];
		}

		size_t size()
		{
			return _con.size();
		}

		bool empty()
		{
			return _con.empty();
		}

	private:
		container _con;
	};

};