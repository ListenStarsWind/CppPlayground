#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"configuration.h"
int RowPreprocessing[] = { 0,9,16,16 };//行数的预选项。
int ColumnPreprocessing[] = { 0,9,16,30 };//列数的预选项 。
int MinePreprocessing[] = { 0,10,40,99 };//地雷个数的预选项。
int AlignmentPatches;//该补丁的存在意义是使方格矩阵在不同难度下都能整齐排列。
int Row;//显示行数。
int Column;//显示列数。
int Mine;//地雷个数
int Rows;//实际创建行数。
int Columns;//实际创建列数。
char ActualArray[40][40];//实际数组
char FormalArray[40][40];//形式数组
void foreword()
{
	printf("********************************************************************************************************************\n");
	printf("这是一个小小的扫雷游戏。\n");
	printf("你也许游玩过这类游戏，但我仍会再次简要说明一下这个游戏。\n");
	printf("这款游戏的玩法是在一个9*9（初级）16*16（中级）16*30（高级）的方块矩阵中随机布置一定量的地雷（初级为10个，中级为40个，高级为99个）。由玩家逐个选择方块，以找出所有地雷为最终游戏目标。如果玩家翻开的方块有地雷，则游戏结束。\n");
	printf("方格中的数字将表示该方格四周8个方格中雷的个数，你可以在你认为一定有雷的方格中插上一个旗子用于排雷；另外由于该程序没有配备图形美化，我们将会用字符‘1’表示雷，字符‘0’表示没有雷；字符‘#’表示旗子，游戏获胜或者失败将展示方格状态。祝你游戏愉快。\n");
	printf("游戏正在准备，请稍后。\n");
	printf("********************************************************************************************************************\n");
}

void DifficultyMenu()
{
	int i;//该变量用于难度选择。
	do
	{
		printf("===========================================\n");
		printf("\n");
		printf("正如前言所说，这个游戏有三种难度，你要选择哪一种呢？\n");
		printf("**************难度1：初级（9*9）方格，共有10个雷。**************\n");
		printf("**************难度2：中级（16*16）方格，共有40个雷。**************\n");
		printf("**************难度3：高级（16*30）方格，共有99个雷。**************\n");
		scanf("%d", &i);
		if (i == 1 || i == 2 || i == 3)//难度选择纠错机制
			break;
		else
		{
			printf("你选择错了，难度只有1,2,3这三种选项，请重新选择：\n");
			continue;
		}
	} while (1);
	if (i == 1)
		AlignmentPatches = 1;//打印方格矩阵数字使用“%d”占位符。
	else if (i == 2)
		AlignmentPatches = 2;//打印方格矩阵数字使用“%2d”占位符。
	else
		AlignmentPatches = 3;//打印方格矩阵数字使用“%2d”占位符。
	Row = RowPreprocessing[i];
	Column = ColumnPreprocessing[i];
	Mine = MinePreprocessing[i];
	Rows = Row + 2;
	Columns = Column + 2;
}

int PlayMenu(void)
{
	int j;//该变量用于判断是否进行游戏。
	do
	{
		printf("\n");
		printf("===========================================\n");
		printf("你想开始游戏吗？\n");
		printf("*************选择1：游玩游戏。*************\n");
		printf("*************选择0：退出游戏。*************\n");
		scanf("%d", &j);
		if (j == 1 || j == 0)//游玩选择纠错机制
			break;
		else
		{
			printf("你选择错了，是否游玩只有1,0这两种选项，请重新选择：\n");
			continue;
		}
	} while (1);
	return j;
}

static void ArrayInitialization(char arr[40][40], char import)//本函数无需在其它文件中调用,用于进行数组初始化。
{
	int i, j;
	for (i = 0; i < Rows; i++)
	{
		for (j = 0; j < Columns; j++)
		{
			arr[i][j] = import;
		}
	}
}

static void PrintingArray(char arr[40][40])//数组打印函数，只在本文件中调用。
{

	int i, j;
	printf("\n");
	switch (AlignmentPatches)
	{
	case 1:printf("-----棋盘如下------\n"); break;
	case 2:printf("--------------------棋盘如下----------------------\n"); break;
	case 3:	printf("------------------------------------------棋盘如下------------------------------------------\n"); break;
	}
	for (i = 0; i <= Column; i++)
	{
		switch (AlignmentPatches)
		{
		case 1:printf("%d ", i); break;
		case 2:printf("%2d ", i); break;
		case 3:printf("%2d ", i); break;
		}
	}
	printf("\n");
	for (i = 1; i <= Row; i++)
	{
		for (j = 0; j <= Column; j++)
		{
			if (j == 0)
			{
				switch (AlignmentPatches)
				{
				case 1:printf("%d ", i); break;
				case 2:printf("%2d ", i); break;
				case 3:printf("%2d ", i); break;
				}
			}
			else
			{
				switch (AlignmentPatches)
				{
				case 1:printf("%c ", arr[i][j]); break;
				case 2:printf("%2c ", arr[i][j]); break;
				case 3:printf("%2c ", arr[i][j]); break;
				}
			}
		}
		printf("\n");
	}
}

static void LayingMines(char arr[40][40])//布雷函数。
{
	int i, j, k;
	i = Mine;
	srand((unsigned int)time(NULL));//布置种子。
	while (i)
	{
		j = rand() % Row + 1;
		k = rand() % Column + 1;
		if (arr[j][k] == '0')
		{
			arr[j][k] = '1';
			i--;
		}
	}
}

static void SelfTestFunction(char arr[40][40])//自检函数，用于观察布雷个数是否正确。
{
	int i, j;
	int k = 0;
	for (i = 1; i <= Row; i++)
	{
		for (j = 1; j <= Column; j++)
			k += arr[i][j] - '0';
	}
	printf("==检测到的地雷个数是%d==", k);
}

static void detection(char arrA[40][40], char arrF[40][40])
{
	int i, j;
	int a, b;
	int k = 0;
	int c = Row * Column - Mine;
	do
	{
		printf("\n");
		PrintingArray(FormalArray);
		printf("请输入要检测的坐标，行在前，列在后,中间用空格隔开。\n");
		scanf("%d%d", &i, &j);
		k = 0;
		if ((i > 0) && (i <= Row) && (j > 0) && (j <= Column))//判断坐标是否合法。
		{
			if (arrA[i][j] == '1')
			{
				printf("这是一个地雷，你被炸死了。\n");
				break;
			}
			else
			{
				for (a = i - 1; a <= i + 1; a++)
				{
					for (b = j - 1; b <= j + 1; b++)
					{
						k += arrA[a][b] - '0';
						printf(" ==%d== ", k);
					}
				}
				arrF[i][j] = k + '0';
				c--;
				PrintingArray(FormalArray);
			}

		}
		else
		{
			printf("此坐标非法，请输入正确坐标。");
			continue;
		}
	} while (c);
	if (c == 0)
		printf("恭喜你，避开了所有的雷。");
}

void game(void)//游戏内容函数。
{
	ArrayInitialization(ActualArray, '0');
	ArrayInitialization(FormalArray, '*');
	LayingMines(ActualArray);
	/*PrintingArray(ActualArray);*///调试完毕后注释掉，已经调试完毕。取消注释将进入作弊模式。
	/*SelfTestFunction(ActualArray);*///调试完毕后注释掉，已经调试完毕。
	detection(ActualArray, FormalArray);
}