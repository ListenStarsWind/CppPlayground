#define _CRT_SECURE_NO_WARNINGS
//����һ���������Ե���Ŀ���������ж�һ���·��е����������ö��ļ���д���ɡ�
//����һ����Ŀ�������ǣ����ʹ��extern��������������include��
#include<stdio.h>
extern int day(int m, int y);
extern int int_leap(int m, int y);
int main()
{
	int mouth, year;
	printf("����������ѡ�е���ݺ��·ݣ�ע������������·���������ݡ�\n");
	scanf("%d%d", &mouth, &year);
	printf("����·���%d�졣\n", day(mouth, year));
	return 0;
}