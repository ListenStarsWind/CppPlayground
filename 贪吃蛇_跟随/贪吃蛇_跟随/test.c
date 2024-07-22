#define _CRT_SECURE_NO_WARNINGS

#include"Snake.h"


//实现游戏主逻辑
void test()
{
	int ch = 0;
	do {
		system("cls");
		//创建贪吃蛇
		Snake snake = { 0 };
		//游戏初始化
		GameStart(&snake);
		//开始游戏
		GameRun(&snake);
		//游戏结束，资源回收  
		GameEnd(&snake);
		//这个while循环是用来读取蛇运行的时候按下的VK虚拟键的循环，
		//把在蛇运行的时候按下的VK键的键值全面读走（包括上键的键值）
		while (_kbhit())  //_kbhit()检测是否有按键被按下
		{
			// 使用 _getch() 获取按下的键
			_getch();
		}
		SetPos(20, 14);
		printf("%s", "要再来一局吗？（Y / N）：");
		ch = getchar();
		while (getchar() != '\n');
	} while (ch == 'y' || ch == 'Y');
}

//搭建游戏运行环境
int main()
{
	//设置窗口大小
	system("mode con cols=110 lines=30");
	//重命名con窗口名
	system("title 贪吃蛇");
	//设置本地化
	setlocale(LC_ALL, "");
	//光标隐藏
	HANDLE hOutput = NULL;
	hOutput = GetStdHandle(STD_OUTPUT_HANDLE);     //获取句柄
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(hOutput, &CursorInfo);    //检索光标信息
	CursorInfo.bVisible = false;
	SetConsoleCursorInfo(hOutput, &CursorInfo);    //设置光标属性

	srand((unsigned int)time(NULL));               //设置“种子”

	test();

	SetPos(82, 25);
	system("pause");
	system("cls");

	return 0;
}

