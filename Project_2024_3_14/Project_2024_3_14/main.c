#define _CRT_SECURE_NO_WARNINGS
//�����Ŀ������������ǳ��򵥣���ȫ���Բ������������и���ϰ�߿���ѧ��
//��Ŀ��https ://www.nowcoder.com/share/jump/9209693051710406905222
#include<stdio.h>
int main()
{
	int a = 0;
	int arr[10] = { 0 };//������Ǹ���ϰ�ߣ�����һ�����飬����г�ʼ������Ȼ���ոգ���һ���ύ���룩�еı䳤�����ǧ��Ҫ��ʼ����
	for (a = 0; a < 10; a++)
		scanf("%d", &arr[a]);/*�������ʱ�䣬���԰�scanf�е�"%d"�ĳ�"%d "�����ᷢ��ʲô��*/
	for (a = 9; a >= 0; a--)
		printf("%d ", arr[a]);
	return 0;
}