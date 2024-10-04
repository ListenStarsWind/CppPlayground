#pragma once

#include<stdlib.h>
#include<iostream>
#include<assert.h>

namespace wind
{
	typedef int SLDate, * pSLDate;
	class SeqList
	{
	public:
		void Push(const SLDate& val);
		void Print()const;
		size_t Size()const;
		const SLDate& operator[](size_t location)const;
		SLDate& operator[](size_t location);
	private:
		pSLDate _pVal = (pSLDate)malloc(sizeof(SLDate) * 10);
		size_t _Size = 0;
		size_t _Capacity = 10;
	};
}