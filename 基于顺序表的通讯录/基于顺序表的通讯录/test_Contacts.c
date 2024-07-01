#define _CRT_SECURE_NO_WARNINGS 
/******************************************************************************************
 * 【文件名称】：
 * 【文件标识】：
 * ========================================================================================
 * 【当前作者】：	听风若依
 * 【当前版本】：	V1.0
 * 【完成日期】：	2024年  月日
 * 【更新内容】：
 * ========================================================================================
 * 【历史作者】：	听风若依
 * 【历史版本】：	V1.
 * 【历史日期】：	2024年  月日
 * ========================================================================================
 * 【开发平台】：	VS2022
 * 【程序内容】：
 *******************************************************************************************/
#include"SeqList.h"
#include<string.h>

#ifndef TEST_SEQLIST

int menu(void)
{
	int ret = 0;
	printf("\n通讯录正在准备中，请稍后。\n");
	printf("请选择你要进行的操作：\n");
	printf("1.插入新的联系人\n");
	printf("2.查找联系人\n");
	printf("3.删除联系人\n");
	printf("4.显示全部联系人信息\n");
	printf("5.退出\n");
	printf("输入序列号即可：\n");
	if (scanf("%d", &ret) != 1)
	{
		printf("发生输入错误！请向管理员反馈该问题。\n");
	}
	while (ret != 1 && ret != 2 && ret != 3 && ret != 4 && ret != 5)
	{
		printf("没有这个选项，请重新输入：\n");
		if (scanf("%d", &ret) != 1)
		{
			printf("发生输入错误！请向管理员反馈该问题。\n");
		}
	}
	return ret;
}

int main()
{
	Contacts t;
	initializeContacts(&t);
	int i = 0;
	do
	{
		i = menu();
		int j = 0;
		switch (i)
		{
		case 1:
			insertAtEnd(&t, generateContactList());
			break;
		case 2:
			j = searchContacts(&t);
			displayContact(&t, j);
			break;
		case 3:
			printf("删除之前要先查找。\n");
			j = searchContacts(&t);
			deleteAtPosition(&t, j);
			break;
		case 4:
			displayContacts(&t);
			break;
		}
	} while (i != 5);
	destroyContacts(&t);
}

#endif
