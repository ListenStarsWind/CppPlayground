#define _CRT_SECURE_NO_WARNINGS
//������ͼ����ӡ�⣬һ��Ҫ����ͼ����������ҵĹ��ɵģ�����Կ���ͬһ��֮ǰ�ύ�Ĵ���ע����ϵһ�£�
//��Ŀ��https ://www.nowcoder.com/share/jump/9209693051710403447399
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
				if (i == 0 || i == import - 1)
					printf("* ");
				else if (j == 0 || j == import - 1)
					printf("* ");
				else
					printf("  ");
			}
			printf("\n");
		}
	}
	return 0;
}
