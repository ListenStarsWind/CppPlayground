#include"Stack.h"
#include"Queue.h"

void test1()
{
	PST stack = STInit();
	STPush(stack, 1);
	STPush(stack, 2);
	STPush(stack, 3);
	STPush(stack, 4);
	printf("%d\n",STPop(stack));
	STPopAll(stack);
	stack = NULL;
}

void test2()
{
	PQType pq = QInit();
	QPush(pq, 1);
	QPush(pq, 2);
	QPush(pq, 3);
	QPop(pq);
	QPop(pq);
	QPop(pq);
	QPush(pq, 1);
	QPush(pq, 2);
	QPush(pq, 3);
	QDataType x = QReadFront(pq);
	printf("%d\n", x);
	x = QReadBack(pq);
	printf("%d\n", x);
	QDestory(pq);
	pq = NULL;
}

int main()
{
	test2();
	return 0;
}