#define _CRT_SECURE_NO_WARNINGS
#include<stdlib.h>
#include<time.h>
#include<stdio.h>
int j = 0;
int s = 0;
void game()
{
	while (1)
	{
		printf("请输入您猜的数值\n");
		scanf("%d", &j);
		if (j < s)
			printf("猜小了\n");

		if (j > s)
			printf("猜大了\n");

		if (j == s)
		{
			printf("恭喜您猜对了，随机数就是%d。\n", s);
			break;
		}
	}
}
int main()
{
	int i = 0;
	srand((unsigned int)time(NULL));
	s = rand() % 100 + 1;
	do
	{
		printf("**********************\n");
		printf("***游戏准备中***\n");
		printf("***1.继续游戏***\n");
		printf("***0.退出游戏***\n");
		printf("**********************\n");
		printf("***请选择***\n");
		scanf("%d", &i);
		switch (i)
		{
		case 1:
			game();
			break;

		case 0:
			printf("正在退出游戏");
			break;

		default:
			printf("输入错误，请重新输入\n");
			break;
		}
	} while (i);





}