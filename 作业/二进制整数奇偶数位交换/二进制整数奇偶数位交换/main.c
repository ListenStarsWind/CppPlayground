#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>

#define OddEvenSwap(parameter)             \
	{                                      \
		int odd = parameter & 0x55555555;   \
		int even = parameter & 0xAAAAAAAA; \
		int oddnew = even >> 1;            \
		int evennew = odd << 1;            \
		parameter = oddnew | evennew;       \
	}

int main()
{
	unsigned int number = 0x12345678;
	OddEvenSwap(number);
	printf("%u\n",number);
	return 0;
}

//0001 0010 0011 0100 0101 0110 0111 1000
//odd 01 00 01 10 11 10 11 00
//even 00 01 01 00 00 01 01 10
//
//
//
//0010 0001 0011 1000 1010 1001 1011 0100
//odd 00 01 01 00 00 01 01 10
//even 01 00 01 10 11 10 11 00