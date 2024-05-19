#include<stdbool.h>
#include<stdio.h>
_Bool leap_year(int year)
{
	if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0))
		return true;
	else
		return false;
}

int main()
{
	printf("%d", leap_year(2025));
	return 0;
}