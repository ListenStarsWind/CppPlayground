#include<stdbool.h>
#include<stdio.h>
_Bool is_prime(int num)
{
	int i;
	for (i = 2; i < num; i++)
	{
		if (num % i == 0)
			return false;
	}
	return true;
}

int main()
{
	for (int i = 100; i <= 200; i++)
	{
		if (is_prime(i))
			printf("%d ", i);
	}
	return 0;
}