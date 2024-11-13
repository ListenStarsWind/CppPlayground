#pragma once

#include<iostream>

template<class T>
T add(const T& n1, const T& n2);

template<class T>
class test
{
public:
	void push(const T&);
private:
	T* _p = nullptr;
	size_t _size = 0;
	size_t _capacity = 0;
};