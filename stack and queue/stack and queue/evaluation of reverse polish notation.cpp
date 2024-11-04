#include<string>
#include<vector>
#include<stack>
#include<assert.h>
#include<queue>
#include<iostream>

using namespace std;

#define USINGITERATOR // 不要注释，另一个版本有BUG，这个版本目前没有BUG
// 另一个版本使用下标访问元素，目前已经查出的BUG是Conversion在迭代过程中应该直接传参in_statement
// 而不是构造对象进行传参

namespace wind
{
	template<class T>
	struct __Matcher
	{
		T _opening;
		T _closing;

		typedef __Matcher<T> self;

		__Matcher(T v1, T v2)
			:_opening(v1)
			, _closing(v2)
		{}

		__Matcher(const self& obj)
			:_opening(obj._opening)
			, _closing(obj._closing)
		{}

		bool check(const T& it)
		{
			if (it == _opening)
				return true;
			else
				return false;
		}

		T another()
		{
			return _closing;
		}
	};

	// Only supports four types of operators: "+", "-", "*", "/", and "()".
	class InfixToPostfixConversion {

		typedef vector<string> expression;

#ifdef USINGITERATOR
		typedef __Matcher<expression::const_iterator> Parenthesis;
#else
		typedef __Matcher<size_t> Parenthesis;
#endif

		typedef stack<Parenthesis> pair;

		typedef enum boundaries
		{
			opening,
			closing
		}boundaries;

		bool isParenthesis(const string& s)
		{
			if (s.size() == 1)
			{
				if (s[0] == '(' || s[0] == ')')
					return true;
				else
					return false;
			}
			else
				return false;
		}

		boundaries opening_or_closing(const string& s)
		{
			assert(isParenthesis(s));
			if (s[0] == '(')
				return opening;
			else if(s[0] == ')')
				return closing;
		}


#ifdef USINGITERATOR

		pair ParenthesisMatching(const expression& statement)
		{
			stack<expression::const_iterator> s;
			pair q;

			auto it = statement.begin();
			while (it != statement.end())
			{
				const string& e = *it;
				if (isParenthesis(e))
				{
					boundaries i = opening_or_closing(e);
					if (i == opening)
					{
						s.push(it);
					}
					else
					{
						auto left = s.top();
						auto right = it;
						s.pop();
						q.push(Parenthesis(left, right));
					}
				}
				++it;
			}
			return q;
		}

#else

		pair ParenthesisMatching(const expression& statement)
		{
			stack<size_t> s;
			pair q;

			size_t i = 0;
			while (i < statement.size())
			{
				const string& e = statement[i];
				if (isParenthesis(e))
				{
					boundaries j = opening_or_closing(e);
					if (j == opening)
					{
						s.push(i);
					}
					else
					{
						auto left = s.top();
						auto right = i;
						s.pop();
						q.push(Parenthesis(left, right));
					}
				}
				i++;
			}
			return q;
		}

#endif
		

		bool operators(const string& s)
		{
			if (s.size() == 1)
			{
				if (s[0] == '+' || s[0] == '-' || s[0] == '*' || s[0] == '/' || s[0] == '(' || s[0] == ')')
					return true;
				else
					return false;
			}
			else
			{
				return false;
			}
		}

		/*int Priority(const string& s)
		{
			assert(operators(s));
			if (s[0] == '*' || s[0] == '/')
				return 2;
			else if(s[0] == '+' || s[0] == '-')
				return 1;
		}*/

		int Priority(const string s1, const string s2)
		{
			assert(operators(s1) && operators(s2));
			int s1_pii = 2;
			int s2_pii = 2;
			if (s1[0] == '+' || s1[0] == '-')
				s1_pii = 1;
			if (s2[0] == '+' || s2[0] == '-')
				s2_pii = 1;
			return s1_pii - s2_pii;
		}

#ifdef USINGITERATOR

		void Conversion(const expression& in_statement, pair& pr, expression& out_statement,\
			expression::const_iterator begin_it,\
			expression::const_iterator end_it)
		{
			if (begin_it == end_it)
				return;

				stack<string> st;

				while (begin_it != end_it)
				{
					auto e = *begin_it;
					if (operators(e))
					{
						if (e == "(" || e == ")")
						{
							if (e == "(")
							{
								auto tmp = pr.top();
								pr.pop();
								Conversion(in_statement, pr, out_statement, ++tmp._opening, tmp._closing);
								begin_it = tmp._closing;
							}
						}
						else
						{
							if (st.empty())
							{
								st.push(e);
							}
							else
							{
								auto tp = st.top();
								int i = Priority(tp, e);
								switch (i)
								{
								case 0:
									out_statement.push_back(tp);
									st.pop();
									st.push(e);
									break;
								case -1:
									st.push(e);
									break;
								case 1:
									out_statement.push_back(tp);
									st.pop();
									st.push(e);
									break;
								}
							}
						}
					}
					else
					{
						out_statement.push_back(e);
					}
					++begin_it;
				}
				while (!st.empty())
				{
					auto tmp = st.top();
					st.pop();
					out_statement.push_back(tmp);
				}
		}

#else

		void Conversion(const expression& in_statement, pair& pr, expression& out_statement, size_t pos = 0)
		{
			if (pos == in_statement.size())
				return;

			stack<string> st;

			while (pos < in_statement.size())
			{
				auto e = in_statement[pos];
				if (operators(e))
				{
					if (e == "(" || e == ")")
					{
						if (e == "(")
						{
							auto tmp = pr.top();
							pr.pop();
							expression i;
							for (++pos; pos < tmp._closing; pos++)
							{
								i.push_back(in_statement[pos]);
							}
							Conversion(i, pr, out_statement);
						}
					}
					else
					{
						if (st.empty())
						{
							st.push(e);
						}
						else
						{
							auto tp = st.top();
							int i = Priority(tp, e);
							switch (i)
							{
							case 0:
								out_statement.push_back(tp);
								st.pop();
								st.push(e);
								break;
							case -1:
								st.push(e);
								break;
							case 1:
								out_statement.push_back(tp);
								st.pop();
								st.push(e);
								break;
							}
						}
					}
				}
				else
				{
					out_statement.push_back(e);
				}
				pos++;
			}

			while (!st.empty())
			{
				auto tmp = st.top();
				st.pop();
				out_statement.push_back(tmp);
			}

		}

#endif

		

	public:
		expression Conversion(const expression& statement)
		{
			expression ret;

			pair i = ParenthesisMatching(statement);

#ifdef USINGITERATOR

			Conversion(statement, i, ret, statement.begin(), statement.end());

#else

			Conversion(statement, i, ret, 0);

#endif
			return ret;
		}
	};
};

namespace leetcode
{
	class Solution {
		bool operators(const string& s) {
			if (s.size() == 1) {
				if (s[0] == '+' || s[0] == '-' || s[0] == '*' || s[0] == '/')
					return true;
				else
					return false;
			}
			else {
				return false;
			}
		}

	public:
		int evalRPN(vector<string>& tokens) {
			stack<string> s;
			for (auto e : tokens) {
				if (operators(e)) {
					int right = stoi(s.top());
					s.pop();
					int left = stoi(s.top());
					s.pop();

					int end = 0;
					switch (e[0]) {
					case '+':
						end = left + right;
						break;
					case '-':
						end = left - right;
						break;
					case '*':
						end = left * right;
						break;
					case '/':
						end = left / right;
						break;
					}
					s.push(to_string(end));
				}
				else {
					s.push(e);
				}
			}
			return stoi(s.top());
		}
	};
};

// ((10 * (6 / ((9 + 3) * -11))) + 17) + 5
// "10","6","9","3","+","-11","*","/","*","17","+","5","+"
//int main()
//{
//	vector<string> v;
//	v.push_back("(");
//	v.push_back("(");
//	v.push_back("10");
//	v.push_back("*");
//	v.push_back("(");
//	v.push_back("6");
//	v.push_back("/");
//	v.push_back("(");
//	v.push_back("(");
//	v.push_back("9");
//	v.push_back("+");
//	v.push_back("3");
//	v.push_back(")");
//	v.push_back("*");
//	v.push_back("-11");
//	v.push_back(")");
//	v.push_back(")");
//	v.push_back(")");
//	v.push_back("+");
//	v.push_back("17");
//	v.push_back(")");
//	v.push_back("+");
//	v.push_back("5");
//	
//	auto i = wind::InfixToPostfixConversion().Conversion(v);
//	for (auto e : i)
//	{
//		cout << e << " ";
//	}
//	cout << endl;
//}