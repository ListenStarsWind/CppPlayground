#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>
#include<stdio.h>
#include<stdbool.h>

typedef int STDataType;
typedef struct Stack
{
	STDataType* _val;
	int _top;
	int _capacity;
}ST, * PST;

PST STInit(void);

void STDestroy(PST stack);

_Bool STEmpty(PST stack);

void STPush(PST stack, STDataType val);

STDataType STPop(PST stack);

int STSize(PST stack);

void STPopAll(PST stack);

STDataType STReadTop(PST stack);