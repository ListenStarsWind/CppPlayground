#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<windows.h>
#include<stdlib.h>

int main()
{
	int i = 0;
	int left = 0;
	int right = 0;
	int a = 0;
	char arr1[] = { "****Hello Word****" };
	char arr2[] = { "******************" };
	i = sizeof(arr1) / sizeof(arr1[0]);
	//ΪʲôҪ��2�أ���ΪҪ��ȥ\0,������ȳ���H�ٳ���d��Hd����ͬʱ���֡�
	for (left = 0, right = i - 2; left <= right; left++, right--)
	{
		arr2[left] = arr1[left];
		arr2[right] = arr1[right];
		for (a = 0; a < i; a++)
			printf("%c", arr2[a]);
		Sleep(1000);
		system("cls");
	}
	for (a = 0; a < i; a++)
		printf("%c", arr2[a]);
	return 0;
}