#pragma once

#include<deque>

namespace wind {

	template<class T, class containers = std::deque<T>>
	class stack {
	public:

		void push(const T& val)
		{
			_con.push_back(val);
		}

		void pop()
		{
			_con.pop_back();
		}

		size_t size()
		{
			return _con.size();
		}

		bool empty()
		{
			return _con.empty();
		}

		T& top()
		{
			return _con.back();
		}

	private:
		containers _con;
	};


	template<class T, class containers = std::deque<T>>
	class queue {
	public:

		void push(const T& val)
		{
			_con.push_back(val);
		}

		void pop()
		{
			_con.pop_front();
		}

		size_t size()
		{
			return _con.size();
		}

		bool empty()
		{
			return _con.empty();
		}

		T& front()
		{
			return _con.front();
		}

		T& back()
		{
			return _con.back();
		}

	private:
		containers _con;
	};
};