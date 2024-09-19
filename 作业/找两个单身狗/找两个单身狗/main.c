#include<stdlib.h>

int* sockCollocation(int* sockets, int socketsSize, int* returnSize) {
	*returnSize = 2;
	int i = 0;
	int cir = 0;
	for (cir = 0; cir < socketsSize; cir++)
	{
		i ^= sockets[cir];
	}
	int key = 1;
	while ((key & i) == 0)
	{
		key <<= 1;
	}
	int* p = (int*)malloc(sizeof(int) * socketsSize);
	if (p == NULL)
	{
		perror("sockCollocation malloc fail");
		return NULL;
	}
	int* ret = (int*)malloc(sizeof(int) * (*returnSize));
	if (ret == NULL)
	{
		perror("sockCollocation malloc ret fail");
		return NULL;
	}
	int j = 0;
	int k = socketsSize - 1;
	for (cir = 0; cir < socketsSize; cir++)
	{
		if ((sockets[cir] & key) == 0)
		{
			p[j++] = sockets[cir];
		}
		else
		{
			p[k--] = sockets[cir];
		}
	}
	for (i = 0, cir = 0; cir < j; cir++)
	{
		i ^= p[cir];
	}
	ret[0] = i;
	for (i = 0, cir = k + 1; cir < socketsSize; cir++)
	{
		i ^= p[cir];
	}
	ret[1] = i;
	free(p);
	return ret;
}

int main()
{
	int p[] = { 4,5,2,4,6,6 };
	size_t sz = sizeof(p) / sizeof(p[0]);
	int i = 0;
	int* ret = sockCollocation(p, sz, &i);
	return 0;
}