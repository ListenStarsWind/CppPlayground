#define _CRT_SECURE_NO_WARNINGS

#include"Snake.h"

//光标重定位
void SetPos(_In_ SHORT x, _In_ SHORT y)
{
	if ((x >= 0 && x < 100) && (y >= 0 && y < 30))
	{
		HANDLE hOutput = NULL;
		hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
		COORD postion = { x, y };
		SetConsoleCursorPosition(hOutput, postion);
	}
	else
	{
		return;
	}
}

static void WelcomeToGame()
{
	SetPos(40, 14);
	wprintf(L"%ls", L"欢迎来到贪吃蛇小游戏");
	SetPos(41, 20);
	system("pause");
	system("cls");//清屏
	SetPos(30, 14);
	wprintf(L"%ls", L"用 ↑ ↓ ← → 控制贪吃蛇的移动方向；");
	SetPos(27, 15);
	wprintf(L"%ls", L"F3为加速，F4为减速，加速可以获得更高的分数。");
	SetPos(38, 20);
	system("pause");
	system("cls");//清屏
}

static void CreateMap()
{
	int i = 0;
	SetPos(0, 0);
	for (i = 0; i < 29; i++)
	{
		wprintf(L"%lc", WALL);
	}
	SetPos(0, 26);
	for (i = 0; i < 29; i++)
	{
		wprintf(L"%lc", WALL);
	}
	for (i = 1; i < 26; i++)
	{
		SetPos(0, i);
		wprintf(L"%lc", WALL);
	}
	for (i = 1; i < 26; i++)
	{
		SetPos(56, i);
		wprintf(L"%lc", WALL);
	}
	SetPos(65, 20);
	wprintf(L"%ls", L"不能穿墙，不能撞到自己");
	SetPos(65, 21);
	wprintf(L"%ls", L"用 ↑ ↓ ← → 控制贪吃蛇的移动方向；");
	SetPos(65, 22);
	wprintf(L"%ls", L"F3为加速，F4为减速，加速可以获得更高的分数。");
	SetPos(65, 23);
	wprintf(L"%ls", L"ESC为退出，空格为暂停");
	SetPos(65, 25);
	wprintf(L"%ls", L"作者：听风若依");
}

static void InitSnake(_In_ PSnake ps)
{
	PSnakeNode ptraverse = NULL;
	int i = 0;
	for (i = 0; i < 5; i++)
	{
		ptraverse = (PSnakeNode)malloc(sizeof(SnakeNode));
		if (ptraverse == NULL)
		{
			perror("InitSnake_malloc");
			return;
		}
		ptraverse->x = INITIAL_X + i * 2;
		ptraverse->y = INITIAL_Y;
		if (ps->_PSnake == NULL)
		{
			ptraverse->next = NULL;
			ps->_PSnake = ptraverse;
		}
		else
		{
			ptraverse->next = ps->_PSnake;
			ps->_PSnake = ptraverse;
		}
	}

	while (ptraverse)
	{
		SetPos(ptraverse->x, ptraverse->y);
		wprintf(L"%lc", BODY);
		ptraverse = ptraverse->next;
	}

	ps->_ward = Right;
	ps->_status = Alive;
	ps->_Food_Weight = 10;
	ps->_Total = 0;
	ps->_speed = 200;
}

static void CreateFood(_In_ PSnake ps)
{
	SHORT x = 0;
	SHORT y = 0;
again:
	do
	{
		x = rand() % 53 + 2;
		y = rand() % 25 + 1;
	} while (x % 2 != 0);

	PSnakeNode ptraverse = ps->_PSnake;
	while (ptraverse)
	{
		if ((ptraverse->x == x) && (ptraverse->y == y))
		{
			goto again;
		}
		ptraverse = ptraverse->next;
	}

	PSnakeNode pfood = (PSnakeNode)malloc(sizeof(SnakeNode));
	if (pfood == NULL)
	{
		perror("CreateFood_malloc");
		return;
	}
	pfood->x = x;
	pfood->y = y;
	pfood->next = NULL;

	SetPos(x, y);
	wprintf(L"%lc", FOOD);

	ps->_PFood = pfood;
}

void GameStart(_In_ PSnake ps)  //这里的_In_  和 _Out_是一个用于标注函数参数的属性   _In_表示这个参数是一个输入参数  _Out_是一个输出型的参数
{
	//显示欢迎界面
	//显示说明界面
	WelcomeToGame();

	//绘制地图
	CreateMap();

	//初始化蛇
	InitSnake(ps);

	//创建食物
	CreateFood(ps);

	//设置游戏相关信息
}

static forever(_In_ PSnake ps)
{
	while (ps->_status == Stop)
	{
		if (KEY_PRESS(VK_SPACE))
		{
			ps->_status = Alive;
		}
	}
}

static void EatFood(_In_ PSnake ps)
{
	ps->_PFood->next = ps->_PSnake;
	ps->_PSnake = ps->_PFood;

	PSnakeNode ptraverse = ps->_PSnake;
	while (ptraverse)
	{
		SetPos(ptraverse->x, ptraverse->y);
		wprintf(L"%lc", BODY);
		ptraverse = ptraverse->next;
	}
	ps->_Total += ps->_Food_Weight;
	CreateFood(ps);
}

static void NotEat(_In_ PSnakeNode pnext, _In_ PSnake ps)
{
	pnext->next = ps->_PSnake;
	ps->_PSnake = pnext;

	PSnakeNode ptraverse = ps->_PSnake;
	while (ptraverse->next->next)
	{
		SetPos(ptraverse->x, ptraverse->y);
		wprintf(L"%lc", BODY);
		ptraverse = ptraverse->next;
	}
	SetPos(ptraverse->x, ptraverse->y);
	wprintf(L"%lc", BODY);

	SetPos(ptraverse->next->x, ptraverse->next->y);
	printf("  ");
	free(ptraverse->next);
	ptraverse->next = NULL;
}

static void SnakeMove(_In_ PSnake ps)
{
	PSnakeNode NextNode = (PSnakeNode)malloc(sizeof(SnakeNode));
	if (NextNode == NULL)
	{
		perror("SnakeMove_malloc");
		return;
	}
	switch (ps->_ward)
	{
	case Up:
		NextNode->x = ps->_PSnake->x;
		NextNode->y = ps->_PSnake->y - 1;
		break;
	case Down:
		NextNode->x = ps->_PSnake->x;
		NextNode->y = ps->_PSnake->y + 1;
		break;
	case Left:
		NextNode->x = ps->_PSnake->x - 2;
		NextNode->y = ps->_PSnake->y;
		break;
	case Right:
		NextNode->x = ps->_PSnake->x + 2;
		NextNode->y = ps->_PSnake->y;
		break;
	}

	if (NextNodeIsFood())
	{
		EatFood(ps);
		free(NextNode);
		NextNode = NULL;
	}
	else
	{
		NotEat(NextNode, ps);
		NextNode = NULL;
	}
}

static void KillByWall(_In_ PSnake ps)
{
	if (ps->_PSnake->x == 0 || ps->_PSnake->x == 56 ||
		ps->_PSnake->y == 0 || ps->_PSnake->y == 26)
	{
		ps->_status = Died_By_Wall;
	}
}

static void KillByOneself(_In_ PSnake ps)
{
	PSnakeNode ptraverse = ps->_PSnake;
	ptraverse = ptraverse->next;
	while (ptraverse)
	{
		if (ptraverse->x == ps->_PSnake->x && ptraverse->y == ps->_PSnake->y)
		{
			ps->_status = Died_By_Oneself;
			break;
		}
		ptraverse = ptraverse->next;
	}
}

void GameRun(_In_ PSnake ps)
{
	do
	{
		//显示分数
		SetPos(65, 15);
		printf("总分数：%hd   ", ps->_Total);
		printf("单个食物分数：%hd", ps->_Food_Weight);

		if (KEY_PRESS(VK_UP) && ps->_ward != Down)
		{
			ps->_ward = Up;
		}
		else if (KEY_PRESS(VK_DOWN) && ps->_ward != Up)
		{
			ps->_ward = Down;
		}
		else if (KEY_PRESS(VK_LEFT) && ps->_ward != Right)
		{
			ps->_ward = Left;
		}
		else if (KEY_PRESS(VK_RIGHT) && ps->_ward != Left)
		{
			ps->_ward = Right;
		}
		else if (KEY_PRESS(VK_ESCAPE))
		{
			ps->_status = Quit;
		}
		else if (KEY_PRESS(VK_SPACE))
		{
			ps->_status = Stop;
			forever(ps);
		}
		else if (KEY_PRESS(VK_F3))
		{
			if (ps->_speed > 80)
			{
				ps->_speed -= 30;
				ps->_Food_Weight += 2;
			}
		}
		else if (KEY_PRESS(VK_F4))
		{
			if (ps->_Food_Weight > 2)
			{
				ps->_Food_Weight -= 2;
				ps->_speed += 30;
			}
		}

		SnakeMove(ps);
		Sleep(ps->_speed);

		KillByWall(ps);
		KillByOneself(ps);
	} while (ps->_status == Alive);
}

void GameEnd(_In_ PSnake ps)
{
	switch (ps->_status)
	{
	case Died_By_Wall:
		SetPos(65, 10);
		wprintf(L"%ls", L"你撞到墙了！游戏结束。");
		break;
	case Quit:
		SetPos(65, 10);
		wprintf(L"%ls", L"游戏退出。");
		break;
	case Died_By_Oneself:
		SetPos(65, 10);
		wprintf(L"%ls", L"你撞到自己了！游戏结束。");
		break;
	}

	PSnakeNode die = ps->_PSnake;
	while (die)
	{
		ps->_PSnake = ps->_PSnake->next;
		free(die);
		die = ps->_PSnake;
	}
	free(ps->_PFood);
	ps->_PFood = NULL;
}