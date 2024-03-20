#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"configuration.h"
int RowPreprocessing[] = { 0,9,16,16 };//������Ԥѡ�
int ColumnPreprocessing[] = { 0,9,16,30 };//������Ԥѡ�� ��
int MinePreprocessing[] = { 0,10,40,99 };//���׸�����Ԥѡ�
int AlignmentPatches;//�ò����Ĵ���������ʹ��������ڲ�ͬ�Ѷ��¶����������С�
int Row;//��ʾ������
int Column;//��ʾ������
int Mine;//���׸���
int Rows;//ʵ�ʴ���������
int Columns;//ʵ�ʴ���������
char ActualArray[40][40];//ʵ������
char FormalArray[40][40];//��ʽ����
void foreword()
{
	printf("********************************************************************************************************************\n");
	printf("����һ��СС��ɨ����Ϸ��\n");
	printf("��Ҳ�������������Ϸ�������Ի��ٴμ�Ҫ˵��һ�������Ϸ��\n");
	printf("�����Ϸ���淨����һ��9*9��������16*16���м���16*30���߼����ķ���������������һ�����ĵ��ף�����Ϊ10�����м�Ϊ40�����߼�Ϊ99��������������ѡ�񷽿飬���ҳ����е���Ϊ������ϷĿ�ꡣ�����ҷ����ķ����е��ף�����Ϸ������\n");
	printf("�����е����ֽ���ʾ�÷�������8���������׵ĸ����������������Ϊһ�����׵ķ����в���һ�������������ף��������ڸó���û���䱸ͼ�����������ǽ������ַ���1����ʾ�ף��ַ���0����ʾû���ף��ַ���#����ʾ���ӣ���Ϸ��ʤ����ʧ�ܽ�չʾ����״̬��ף����Ϸ��졣\n");
	printf("��Ϸ����׼�������Ժ�\n");
	printf("********************************************************************************************************************\n");
}

void DifficultyMenu()
{
	int i;//�ñ��������Ѷ�ѡ��
	do
	{
		printf("===========================================\n");
		printf("\n");
		printf("����ǰ����˵�������Ϸ�������Ѷȣ���Ҫѡ����һ���أ�\n");
		printf("**************�Ѷ�1��������9*9�����񣬹���10���ס�**************\n");
		printf("**************�Ѷ�2���м���16*16�����񣬹���40���ס�**************\n");
		printf("**************�Ѷ�3���߼���16*30�����񣬹���99���ס�**************\n");
		scanf("%d", &i);
		if (i == 1 || i == 2 || i == 3)//�Ѷ�ѡ��������
			break;
		else
		{
			printf("��ѡ����ˣ��Ѷ�ֻ��1,2,3������ѡ�������ѡ��\n");
			continue;
		}
	} while (1);
	if (i == 1)
		AlignmentPatches = 1;//��ӡ�����������ʹ�á�%d��ռλ����
	else if (i == 2)
		AlignmentPatches = 2;//��ӡ�����������ʹ�á�%2d��ռλ����
	else
		AlignmentPatches = 3;//��ӡ�����������ʹ�á�%2d��ռλ����
	Row = RowPreprocessing[i];
	Column = ColumnPreprocessing[i];
	Mine = MinePreprocessing[i];
	Rows = Row + 2;
	Columns = Column + 2;
}

int PlayMenu(void)
{
	int j;//�ñ��������ж��Ƿ������Ϸ��
	do
	{
		printf("\n");
		printf("===========================================\n");
		printf("���뿪ʼ��Ϸ��\n");
		printf("*************ѡ��1��������Ϸ��*************\n");
		printf("*************ѡ��0���˳���Ϸ��*************\n");
		scanf("%d", &j);
		if (j == 1 || j == 0)//����ѡ��������
			break;
		else
		{
			printf("��ѡ����ˣ��Ƿ�����ֻ��1,0������ѡ�������ѡ��\n");
			continue;
		}
	} while (1);
	return j;
}

static void ArrayInitialization(char arr[40][40], char import)//�����������������ļ��е���,���ڽ��������ʼ����
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

static void PrintingArray(char arr[40][40])//�����ӡ������ֻ�ڱ��ļ��е��á�
{

	int i, j;
	printf("\n");
	switch (AlignmentPatches)
	{
	case 1:printf("-----��������------\n"); break;
	case 2:printf("--------------------��������----------------------\n"); break;
	case 3:	printf("------------------------------------------��������------------------------------------------\n"); break;
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

static void LayingMines(char arr[40][40])//���׺�����
{
	int i, j, k;
	i = Mine;
	srand((unsigned int)time(NULL));//�������ӡ�
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

static void SelfTestFunction(char arr[40][40])//�Լ캯�������ڹ۲첼�׸����Ƿ���ȷ��
{
	int i, j;
	int k = 0;
	for (i = 1; i <= Row; i++)
	{
		for (j = 1; j <= Column; j++)
			k += arr[i][j] - '0';
	}
	printf("==��⵽�ĵ��׸�����%d==", k);
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
		printf("������Ҫ�������꣬����ǰ�����ں�,�м��ÿո������\n");
		scanf("%d%d", &i, &j);
		k = 0;
		if ((i > 0) && (i <= Row) && (j > 0) && (j <= Column))//�ж������Ƿ�Ϸ���
		{
			if (arrA[i][j] == '1')
			{
				printf("����һ�����ף��㱻ը���ˡ�\n");
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
			printf("������Ƿ�����������ȷ���ꡣ");
			continue;
		}
	} while (c);
	if (c == 0)
		printf("��ϲ�㣬�ܿ������е��ס�");
}

void game(void)//��Ϸ���ݺ�����
{
	ArrayInitialization(ActualArray, '0');
	ArrayInitialization(FormalArray, '*');
	LayingMines(ActualArray);
	/*PrintingArray(ActualArray);*///������Ϻ�ע�͵����Ѿ�������ϡ�ȡ��ע�ͽ���������ģʽ��
	/*SelfTestFunction(ActualArray);*///������Ϻ�ע�͵����Ѿ�������ϡ�
	detection(ActualArray, FormalArray);
}