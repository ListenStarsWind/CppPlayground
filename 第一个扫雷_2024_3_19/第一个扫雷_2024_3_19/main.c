#define _CRT_SECURE_NO_WARNINGS
#include"configuration.h"
int main()
{
	int import;//是否游玩变量。
	foreword();//前言函数，用于对游戏进行说明。
	do
	{
import = PlayMenu();//游玩菜单函数，将返回值赋给import。
		if (import == 1)
		{
			DifficultyMenu();//难度菜单函数，用于难度选择。
			game();

		}

	} while (import);
	return 0;
}