//"*"�Ŵ�ӡ�������Ҫ���ҹ��ɣ�
//�ȷ�˵��������һ������5���ǾͿ�����Ϊ������һ��5*5�����̣������01234Ȼ�����ǿ��������*����
//ʵ�����ڶԽ�������ʾ�ģ������i����������j���������Ϳ�����Ϊ����*���Ż���i==j�Լ�i+j==4�ϳ��֣�
//��Ŀ���ӣ�https://www.nowcoder.com/share/jump/9209693051710402272732
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
int main()
{
	int i, j, import;
	while (EOF != scanf("%d", & import))
	{
		for (i = 0; i < import; i++)
		{
			for (j = 0; j < import; j++)
			{
				if (i == j)
				{
					printf("*");
				}
				else if (i + j == import - 1)
				{
					printf("*");
				}
				else
					printf(" ");
			}
			printf("\n");
		}
	}

	return 0;
}