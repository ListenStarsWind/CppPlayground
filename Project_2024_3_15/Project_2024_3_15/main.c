#define _CRT_SECURE_NO_WARNINGS
//����һ���������͵���Ŀ����Ŀ���Ǵ���һ���Զ���ĺ������ú����Ĺ����ǽ��������ͱ��������ͣ���������������
#include<stdio.h>
int Add(int x, int y)
{
	return x + y;
}
int main()
{
	int a, b;
	scanf("%d%d", &a, &b);
	printf("%d", Add(a, b));
	return 0;
}