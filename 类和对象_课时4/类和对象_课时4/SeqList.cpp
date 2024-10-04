#include"SeqList.h"

void wind::SeqList::Push(const SLDate& val)
{
	_pVal[_Size++] = val;
}

void wind::SeqList::Print()const
{
	size_t i = 0;
	for (; i < _Size; i++)
	{
		std::cout << _pVal[i] << " ";
	}
	std::cout << std::endl;
}

size_t wind::SeqList::Size()const
{
	return _Size;
}

const wind::SLDate& wind::SeqList::operator[](size_t location)const
{
	assert(location < _Size);
	return _pVal[location];
}

wind::SLDate& wind::SeqList::operator[](size_t location)
{
	assert(location < _Size);
	return _pVal[location];
}