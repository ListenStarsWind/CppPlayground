#define _CRT_SECURE_NO_WARNINGS

#include"SeqList.h"

PSeqList SeqListGet(void)
{
	PSeqList ps = (PSeqList)malloc(sizeof(SeqList));
	if (ps == NULL)
	{
		perror("GetSeqList malloc fail");
		return NULL;
	}
	ps->p = NULL;
	ps->total = 0;
	ps->valid = 0;
	return ps;
}

void SeqListDestroy(PSeqList ps)
{
	if (ps == NULL)
	{
		printf("Invalid parameter!\n");
		return;
	}
	free(ps->p);
	ps->p = NULL;
	ps->total = 0;
	ps->valid = 0;
	free(ps);
	ps = NULL;
}

void SeqListPrintf(const PSeqList ps)
{
	if (ps == NULL)
	{
		printf("Invalid parameter!\n");
		return;
	}
	int cir = 0;
	for (cir = 0; cir < ps->valid; cir++)
	{
		printf("%d ", ps->p[cir]);
	}
	printf("\n");
}

static void SeqListExpandCapacity(PSeqList ps)
{
	int newsize = 0;
	SLDataType* pnew = NULL;
	newsize = ps->total == 0 ? 4 : ps->total * 2;
	pnew = (SLDataType*)realloc(ps->p, sizeof(SLDataType) * newsize);
	if (pnew == NULL)
	{
		printf("SeqListExpandCapacity malloc fail\n");
		return;
	}
	ps->p = pnew;
	ps->total = newsize;
}



void SeqListPushBack(PSeqList ps, SLDataType x)
{
	if (ps == NULL)
	{
		printf("Invalid parameter!\n");
		return;
	}
	if (ps->total == ps->valid)
	{
		SeqListExpandCapacity(ps);
	}
	ps->p[ps->valid++] = x;
}

void SeqListPushFront(PSeqList ps, SLDataType x)
{
	if (ps == NULL)
	{
		printf("Invalid parameter!");
		return;
	}
	if (ps->total == ps->valid)
	{
		SeqListExpandCapacity(ps);
	}
	int cir = 0;
	for (cir = ps->valid; cir > 0; cir--)
	{
		ps->p[cir] = ps->p[cir - 1];
	}
	ps->p[0] = x;
	ps->valid++;
}

void SeqListPopBack(PSeqList ps)
{
	if (ps->valid == 0)
	{
		printf("No data available for deletion!\n");
		return;
	}
	size_t cir = sizeof(SLDataType);
	char* p = (char*)(ps->p + (ps->valid - 1));
	while (cir--)
	{
		*p = 0xcd;
		p++;
	}
	p = NULL;
	ps->valid--;
}

void SeqListPopFront(PSeqList ps)
{
	if (ps->valid == 0)
	{
		printf("No data available for deletion!\n");
		return;
	}
	int i = 0;
	for (i = 0; i < ps->valid - 1; i++)
	{
		ps->p[i] = ps->p[i + 1];
	}
	size_t cir = sizeof(SLDataType);
	char* p = (char*)(ps->p + (ps->valid - 1));
	while (cir--)
	{
		*p = 0xcd;
		p++;
	}
	p = NULL;
	ps->valid--;
}

void SeqListInsert(PSeqList ps, int pos, SLDataType x)
{
	if (ps == NULL)
	{
		printf("Invalid parameter!\n");
		return;
	}
	if (ps->total == ps->valid)
	{
		SeqListExpandCapacity(ps);
	}
	if ((pos >= 0) && (pos <= ps->valid))
	{
		int cir = 0;
		for (cir = ps->valid; cir > pos; cir--)
		{
			ps->p[cir] = ps->p[cir-1];
		}
		ps->p[pos] = x;
		ps->valid++;
	}
	else
	{
		printf("Invalid coordinates!\n");
		return;
	}
}

void SeqListErase(PSeqList ps, int pos)
{
	if (ps->valid == 0)
	{
		printf("No data available for deletion!\n");
		return;
	}
	if ((pos >= 0) && (pos < ps->valid))
	{
		int i = 0;
		for (i = pos; i < ps->valid - 1; i++)
		{
			ps->p[i] = ps->p[i + 1];
		}
		size_t cir = sizeof(SLDataType);
		char* p = (char*)(ps->p + (ps->valid - 1));
		while (cir--)
		{
			*p = 0xcd;
			p++;
		}
		p = NULL;
		ps->valid--;
		return;
	}
	else
	{
		printf("Invalid coordinates!\n");
		return;
	}
}

int SeqListFind(const PSeqList ps, int pos)
{
	if (ps == NULL)
	{
		printf("Invalid parameter!\n");
		return EOF;
	}
	int cir = 0;
	for (cir = 0; cir < ps->valid; cir++)
	{
		if (ps->p[cir] == pos)
		{
			return cir;
		}
	}
	return EOF;
}

void SeqListModify(PSeqList ps, int pos, SLDataType x)
{
	if (ps->valid == 0)
	{
		printf("No data available for deletion!\n");
		return;
	}
	if ((pos >= 0) && (pos < ps->valid))
	{
		ps->p[pos] = x;
	}
	else
	{
		printf("Invalid coordinates!\n");
		return;
	}
}