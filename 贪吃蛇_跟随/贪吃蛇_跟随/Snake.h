#pragma once

#include<locale.h>
#include<sal.h>
#include<windows.h>
#include<stdbool.h>
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include <conio.h>  //_kbhit()和_getch()所需要的头文件
#include"vld.h"

#define WALL L'□'
#define BODY L'●'
#define FOOD L'★'

#define INITIAL_X 24
#define INITIAL_Y 5

#define KEY_PRESS(VK) ( (GetAsyncKeyState(VK) & 0x01) ? 1 : 0 )

#define NextNodeIsFood() ( (NextNode->x == ps->_PFood->x && NextNode->y == ps->_PFood->y) ? 1 : 0 )

typedef struct SnakeNode
{
	SHORT x;
	SHORT y;
	struct SnakeNode* next;
}SnakeNode, * PSnakeNode;

typedef enum direction
{
	Up,
	Down,
	Left,
	Right
}direction;

typedef enum VitalStatus
{
	Alive,               //还活着
	Died_By_Wall,        //撞墙死了
	Died_By_Oneself,     //撞自己死了
	Stop,                //暂停
	Quit                 //退出
}VitalStatus;

typedef int score, dealy;

typedef struct Snake
{
	PSnakeNode _PSnake;          //蛇头的指针
	PSnakeNode _PFood;           //食物的指针
	direction _ward;             //运动的方向
	VitalStatus _status;         //蛇的状态
	score _Food_Weight;          //食物的分数
	score _Total;				//游戏的总分数
	dealy _speed;                //用延迟的方式控制运动速度
}Snake, * PSnake;

void GameStart(_In_ PSnake ps);

void SetPos(_In_ SHORT x, _In_ SHORT y);

void GameRun(_In_ PSnake ps);

void GameEnd(_In_ PSnake ps);