#pragma once

#include<locale.h>
#include<sal.h>
#include<windows.h>
#include<stdbool.h>
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include <conio.h>  //_kbhit()��_getch()����Ҫ��ͷ�ļ�
#include"vld.h"

#define WALL L'��'
#define BODY L'��'
#define FOOD L'��'

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
	Alive,               //������
	Died_By_Wall,        //ײǽ����
	Died_By_Oneself,     //ײ�Լ�����
	Stop,                //��ͣ
	Quit                 //�˳�
}VitalStatus;

typedef int score, dealy;

typedef struct Snake
{
	PSnakeNode _PSnake;          //��ͷ��ָ��
	PSnakeNode _PFood;           //ʳ���ָ��
	direction _ward;             //�˶��ķ���
	VitalStatus _status;         //�ߵ�״̬
	score _Food_Weight;          //ʳ��ķ���
	score _Total;				//��Ϸ���ܷ���
	dealy _speed;                //���ӳٵķ�ʽ�����˶��ٶ�
}Snake, * PSnake;

void GameStart(_In_ PSnake ps);

void SetPos(_In_ SHORT x, _In_ SHORT y);

void GameRun(_In_ PSnake ps);

void GameEnd(_In_ PSnake ps);