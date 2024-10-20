#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include<string.h>
#include<assert.h>
#include<iostream>

namespace wind
{
	class string
	{
	public:
		typedef char* iterator;
		typedef const char* const_iterator;
		iterator begin();
		iterator end();
		const_iterator begin()const;
		const_iterator end()const;
		string(const char* str);
		string(const string& s);
		string();
		~string();
		string& operator=(string s);
		void reserve(size_t n);
		char& operator[](size_t pos);
		string& operator+=(const char ch);
		string& operator+=(const char* str);
		const char& operator[](size_t pos)const;
		void push_back(const char ch);
		void append(const char* str);
		void clear();
		void resize(size_t len, char holder = '\0');
		void swap(string& s);
		size_t size()const;
		size_t capacity()const;
		string substr(size_t pos = 0, size_t len = npos)const;
		string& insert(size_t pos, const char* str);
		string& insert(size_t pos, const string& s);
		string& insert(size_t pos, const char ch);
		string& erase(size_t pos = 0, size_t len = npos);
		string& get(char delim = ' ', std::istream& in = std::cin);
		const char* c_str();
		const char* c_str()const;
		size_t find(const char goal, size_t pos = 0)const;
		size_t find(const char* str, size_t pos = 0)const;
		size_t find(const string& s, size_t pos = 0)const;
	private:
		char* _str;
		size_t _size;
		size_t _capacity;
		const static size_t npos;
	};
	bool operator>(const string& s1, const string& s2);
	bool operator>(const string& s, const char* str);
	bool operator>(const char* str, const string& s);

	bool operator==(const string& s1, const string& s2);
	bool operator==(const string& s, const char* str);
	bool operator==(const char* str, const string& s);

	bool operator<(const string& s1, const string& s2);
	bool operator<(const string& s, const char* str);
	bool operator<(const char* str, const string& s);


	std::ostream& operator<<(std::ostream& out, const string& s);
	std::istream& operator>>(std::istream& in, string& s);
	//string& get(std::istream& in, string& s, char delim);
}