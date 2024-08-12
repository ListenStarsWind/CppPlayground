#include"Stack.h"

PST STInit(void)
{
	PST ret = (PST)malloc(sizeof(ST));
	if (ret == NULL)
	{
		perror("Init fail!");
		return NULL;
	}
	ret->_top = 0;
	ret->_capacity = 0;
	ret->_val = NULL;
	return ret;
}

void STDestroy(PST stack)
{
	assert(stack);
	free(stack->_val);
	stack->_val = NULL;
	stack->_top = 0;
	stack->_capacity = 0;
	free(stack);
}

_Bool STEmpty(PST stack)
{
	assert(stack);
	return stack->_top == 0;
}

void STPush(PST stack, STDataType val)
{
	assert(stack);
	if (stack->_top == stack->_capacity)
	{
		int newCapacity = stack->_capacity == 0 ? 4 : 2*stack->_capacity;
		STDataType* p = (STDataType*)realloc(stack->_val, sizeof(STDataType)*newCapacity);
		if (p == NULL)
		{
			perror("extend fail");
			return;
		}
		stack->_val = p;
		stack->_capacity = newCapacity;
	}
	stack->_val[stack->_top] = val;
	stack->_top++;
}

STDataType STPop(PST stack)
{
	assert(stack);
	if (STEmpty(stack))
	{
		printf("The stack already null!\n");
		return;
	}
	else
	{
		STDataType ret = stack->_val[stack->_top-1];
		STDataType* overwriting = (STDataType*)realloc(NULL, sizeof(STDataType));
		if (overwriting == NULL)
		{
			perror("overwriting fail");
		}
		else
		{
			stack->_val[stack->_top-1] = *overwriting;
			free(overwriting);
		}
		stack->_top--;
		return ret;
	}
}

int STSize(PST stack)
{
	assert(stack);
	return stack->_top;
}

void STPopAll(PST stack)
{
	assert(stack);
	while (STSize(stack))
	{
		STDataType val = STPop(stack);
		printf("%d--",val);
	}
	printf("NULL\n");
}

STDataType STReadTop(PST stack)
{
	assert(stack);
	return stack->_val[stack->_top - 1];
}