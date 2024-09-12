#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int* bulid_arr(int size)
{
	int* arr = (int*)realloc(sizeof(int)* size);
	if (arr == NULL)
	{
		perror("bulid fail");
		return NULL;
	}

}