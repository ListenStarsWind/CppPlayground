
#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int i = 0;
int flag1 = 0;
int number = 0;
int conjecture = 0;

void cnumber()
{
	printf("请输入你猜的数字：\n");
	scanf("%d", &conjecture);
}

void RNG()
{
	srand((unsigned int)time(NULL));
	number = rand() % 100 + 1;
}


void menu()
{
	printf("************************************\n");
	printf("选择1：继续游戏\n");
	printf("选择0：退出游戏\n");
	printf("请输入你选择的数字,1或者0.\n");
	printf("************************************\n");
	scanf("%d", &flag1);
}

void InitialInterface()
{
	printf("游戏开始，正在加载中，请稍后\n");
	printf("************************************\n");
	printf("************************************\n");
	printf("************************************\n");
	printf("这是一个小游戏，会给出一个范围为1-100的随机数，而你则要猜出这个数。\n");

}

void game()
{
	int flag2 = 1;
	for (i = 1; i <= 5; i++)
	{

		if (conjecture < number)
		{
			printf("你猜小了\n");
			cnumber();
			continue;
		}
		else if (conjecture > number)
		{
			printf("你猜大了\n");
			cnumber();
			continue;
		}
		else
		{
			printf("你猜对了\n");
			flag2 = 0;
			break;
		}
	}
	if (flag2)
		printf("哎呀，你的运气真不好呀，要再试一下吗？");
}



int main()
{
	InitialInterface();

	while (1)
	{
		menu();
		switch (flag1)
		{
		case 1:
		{
			RNG();
			cnumber();
			game();
		}
		break;
		case 0:
			goto finish;
			break;
		default:
			printf("只有1和2呀，你输错了，请重新输入.\n");
			break;

		}
	}
finish:
	printf("游戏结束，欢迎下次游玩。\n");
	return 0;
}