#define _CRT_SECURE_NO_WARNINGS
//����һ���������Ե���Ŀ���������ж�һ���·��е����������ö��ļ���д���ɡ�
#include<stdio.h>
#include"day.h"
#include"int_leap.h"
int main()
{
	int mouth, year;
	printf("����������ѡ�е���ݺ��·ݣ�ע������������·���������ݡ�\n");
	scanf("%d%d", &mouth, &year);
	printf("����·���%d�졣\n", day(mouth, year));
	return 0;
}