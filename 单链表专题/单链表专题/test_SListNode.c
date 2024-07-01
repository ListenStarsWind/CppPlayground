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
#include"SListNode.h"

//功能测试（Functional Testing） : FT
//异常测试（Negative Testing） : NT
//单元测试（Unit Testing） : UT
//集成测试（Integration Testing） : IT
//系统测试（System Testing） : ST
//回归测试（Regression Testing） : RT
//性能测试（Performance Testing） : PT
//压力测试（Stress Testing） : ST
//验收测试（Acceptance Testing） : AT
//安全测试（Security Testing） : SecT

void SListNodeEndPushUT(void)
{
	SListNode* SLNHead = NULL;
	SListNodeEndPush(&SLNHead, 1);
	SListNodeEndPush(&SLNHead, 2);
	SListNodeEndPush(&SLNHead, 3);
	SListNodeEndPush(&SLNHead, 4);
	SListNodePrintf(SLNHead);
}

void SListNodeFrontPushUT(void)
{
	SListNode* SLNHead = NULL;
	SListNodeFrontPush(&SLNHead, 4);
	SListNodeFrontPush(&SLNHead, 3);
	SListNodeFrontPush(&SLNHead, 2);
	SListNodeFrontPush(&SLNHead, 1);
	SListNodePrintf(SLNHead);
}

void SListNodeEndPopUT()
{
	SListNode* SLNHead = NULL;
	SListNodeFrontPush(&SLNHead, 4);
	SListNodeFrontPush(&SLNHead, 3);
	SListNodeFrontPush(&SLNHead, 2);
	SListNodeFrontPush(&SLNHead, 1);
	SListNodePrintf(SLNHead);
	SListNodeEndPop(&SLNHead);
	SListNodeEndPop(&SLNHead);
	SListNodePrintf(SLNHead);
	SListNodeEndPop(&SLNHead);
	SListNodeEndPop(&SLNHead);
	SListNodePrintf(SLNHead);
}

void SListNodeFrontPopUT()
{
	SListNode* SLNHead = NULL;
	SListNodeFrontPush(&SLNHead, 4);
	SListNodeFrontPush(&SLNHead, 3);
	SListNodeFrontPush(&SLNHead, 2);
	SListNodeFrontPush(&SLNHead, 1);
	SListNodePrintf(SLNHead);
	SListNodeFrontPop(&SLNHead);
	SListNodeFrontPop(&SLNHead);
	SListNodePrintf(SLNHead);
	SListNodeFrontPop(&SLNHead);
	SListNodeFrontPop(&SLNHead);
	SListNodePrintf(SLNHead);
}

void SListNodeFindUT()
{
	SListNode* SLNHead = NULL;
	SListNodeFrontPush(&SLNHead, 4);
	SListNodeFrontPush(&SLNHead, 3);
	SListNodeFrontPush(&SLNHead, 2);
	SListNodeFrontPush(&SLNHead, 1);
	SListNode* Ptr = SListNodeFind(SLNHead, 5);
	if (Ptr == NULL)
	{
		printf("Not found.\n");
	}
	else
	{
		printf("Found it.\n");
		SListNodePrintf(Ptr);
	}
}

void SListNodeInsertUT()
{
	SListNode* SLNHead = NULL;
	SListNodeFrontPush(&SLNHead, 5);
	SListNodeFrontPush(&SLNHead, 3);
	SListNodeFrontPush(&SLNHead, 2);
	SListNodeFrontPush(&SLNHead, 1);
	SListNodePrintf(SLNHead);
	SListNode* Ptr = SListNodeFind(SLNHead, 1);
	if (Ptr == NULL)
	{
		printf("Not found.\n");
	}
	else
	{
		SListNodeInsertBefore(&SLNHead, Ptr, 4);
	}
	SListNodePrintf(SLNHead);
}

void SListNodeInsertAfterUT()
{
	SListNode* SLNHead = NULL;
	SListNodeFrontPush(&SLNHead, 5);
	SListNodeFrontPush(&SLNHead, 3);
	SListNodeFrontPush(&SLNHead, 2);
	SListNodeFrontPush(&SLNHead, 1);
	SListNodePrintf(SLNHead);
	SListNode* Ptr = SListNodeFind(SLNHead, 3);
	if (Ptr == NULL)
	{
		printf("Not found.\n");
	}
	else
	{
		SListNodeInsertAfter(Ptr, 4);
		SListNodePrintf(SLNHead);
	}
}

int main()
{
	SListNodeInsertAfterUT();
	return 0;
}