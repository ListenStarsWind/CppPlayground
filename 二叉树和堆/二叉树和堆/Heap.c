#include"Heap.h"

// This function has two modes.
// Mode 1: Without negation, it operates in min-heap mode.
// Mode 2: With negation, it operates in max-heap mode.
// If the parameters "child" and "parent" satisfy the corresponding heap rules, it returns true; otherwise, it returns false.
bool rule(HeapData child, HeapData parent)
{
	return (child >= parent);
}

static void Swap(pHeapData p1, pHeapData p2)
{
	assert(p1 && p2);
	HeapData s = *p1;
	*p1 = *p2;
	*p2 = s;
}

pHeap HeapInit(void)
{
	pHeap p = (pHeap)malloc(sizeof(Heap));
	if (p == NULL)
	{
		perror("HeapInit malloc fail");
		return NULL;
	}
	pHeapData pArr = (pHeapData)malloc(sizeof(HeapData));
	if (pArr == NULL)
	{
		perror("Array malloc fail");
		free(p);
		return NULL;
	}
	p->_pArray = pArr;
	p->_Capacity = 1;
	p->_Size = 0;
	return p;
}

void HeapDestroy(pHeap pH)
{
	assert(pH);
	free(pH->_pArray);
	pH->_pArray = NULL;
	pH->_Capacity = 0;
	pH->_Size = 0;
	free(pH);
}

static int depth(int val)
{
	val++;
	double natural = (double)val;
	double x = log2(natural);
	return (int)x;
}

static int total(int val)
{
	double exponent = (double)val;
	double x = exp2(exponent);
	return (int)x;
}

static void HeapDilatation(pHeap pH)
{
	assert(pH);
	int n = depth(pH->_Capacity);
	int NewCapacity = total(++n);
	pHeapData p = (pHeapData)realloc(pH->_pArray, sizeof(HeapData)*NewCapacity);
	if (p == NULL)
	{
		perror("HeapDilatation realloc fail");
		return;
	}
	pH->_pArray = p;
	pH->_Capacity = NewCapacity;
	return;
}

static int FindParent(int Child, int Size)
{
	int ret = (Child - 1) / 2;
	if (ret >= 0)
	{
		return ret;
	}
	else
	{
		return EOF;
	}
}

static int FindFirstChild(int Parent, int Size)
{
	int ret = Parent * 2 + 1;
	if (ret < Size)
	{
		return ret;
	}
	else
	{
		return EOF;
	}
}

static int FindSecondChild(int Parent, int Size)
{
	int ret = Parent * 2 + 2;
	if (ret < Size)
	{
		return ret;
	}
	else
	{
		return EOF;
	}
}

void adjustUP(HeapData* pArray, int Size, int Child)
{
	assert(pArray);
	int Parent = 0;
	while (Child > 0)
	{
		Parent = FindParent(Child, Size);
		if (rule(pArray[Child], pArray[Parent]))
		{
			break;
		}
		else
		{
			Swap(&(pArray[Child]), &(pArray[Parent]));
			Child = Parent;
		}
	}
}

void HeapPush(pHeap pH, HeapData val)
{
	assert(pH);
	if (pH->_Capacity == pH->_Size)
	{
		HeapDilatation(pH);
	}
	pH->_pArray[pH->_Size++] = val;
	adjustUP(pH->_pArray, pH->_Size, pH->_Size - 1);
}

int HeapSize(pHeap pH)
{
	assert(pH);
	return pH->_Size;
}

bool HeapEmpty(pHeap pH)
{
	assert(pH);
	return (HeapSize(pH) == 0);
}

static HeapData PopOverwriting(void)
{
	pHeapData p = (pHeapData)realloc(NULL, sizeof(HeapData));
	if (p == NULL)
	{
		perror("PopOverwriting realloc fail");
		return (HeapData)0;
	}
	HeapData ret = *p;
	free(p);
	return ret;
}

void adjustDOWN(HeapData* pArray, int Size, int Parent)
{
	assert(pArray);
	int Child = 0;
	while (Parent < Size)
	{
		int FirstChild = FindFirstChild(Parent, Size);
		int SecondChild = FindSecondChild(Parent, Size);
		if (FirstChild != EOF && SecondChild != EOF)
		{
			if (rule(pArray[FirstChild], pArray[SecondChild]))
			{
				Child = SecondChild;
			}
			else
			{
				Child = FirstChild;
			}
		}
		else
		{
			if (FirstChild == EOF)
			{
				break;
			}
			else
			{
				Child = FirstChild;
			}
		}
		if (rule(pArray[Child], pArray[Parent]))
		{
			break;
		}
		else
		{
			Swap(&(pArray[Parent]), &(pArray[Child]));
			Parent = Child;
		}
	}
}

void HeapPop(pHeap pH)
{
	assert(pH);
	if (HeapEmpty(pH))
	{
		printf("This heap is already empty!\n");
		return;
	}
	else
	{
		Swap(&(pH->_pArray[0]), &(pH->_pArray[pH->_Size - 1]));
		pH->_pArray[pH->_Size - 1] = PopOverwriting();
		pH->_Size--;
		adjustDOWN(pH->_pArray, pH->_Size, 0);
	}
}

HeapData HeapTop(pHeap pH)
{
	assert(pH);
	assert(!HeapEmpty(pH));
	return pH->_pArray[0];
}

void HeapSort1(pHeapData pArray, int Size)
{
	assert(pArray);
	pHeap pH = HeapInit();
	int circulation = 0;
	for (circulation = 0; circulation < Size; circulation++)
	{
		HeapPush(pH, pArray[circulation]);
	}
	circulation = 0;
	while (!HeapEmpty(pH))
	{
		HeapData top = HeapTop(pH);
		pArray[circulation++] = top;
		HeapPop(pH);
	}
	HeapDestroy(pH);
	pH = NULL;
}

void HeapSort2(pHeapData pArray, int Size)
{
	assert(pArray);
	int circulation = 0;
	for (circulation = 1; circulation < Size; circulation++)
	{
		adjustUP(pArray, circulation + 1, circulation);
	}
	for (circulation = Size - 1; circulation > 0; circulation--)
	{
		Swap(&(pArray[0]), &(pArray[circulation]));
		adjustDOWN(pArray, circulation, 0);
	}
}

void HeapSort(pHeapData pArray, int Size)
{
	assert(pArray);
	int circulation = 0;
	for (circulation = FindParent(Size - 1, Size); circulation >= 0; circulation--)
	{
		adjustDOWN(pArray, Size, circulation);
	}
	for (circulation = Size - 1; circulation > 0; circulation--)
	{
		Swap(&(pArray[0]), &(pArray[circulation]));
		adjustDOWN(pArray, circulation, 0);
	}
}

pHeapData TopK1(int k)
{
	FILE* pf = fopen("data.txt", "r");
	if (pf == NULL)
	{
		perror("TopK open fail");
		return NULL;
	}
	pHeap pH = HeapInit();
	HeapData val = (HeapData)0;
	while (k--)
	{
		fscanf(pf, "%d", &val);
		HeapPush(pH, val);
	}
	while (!feof(pf))
	{
		fscanf(pf, "%d", &val);
		if (rule(val, HeapTop(pH)))
		{
			pH->_pArray[0] = val;
			adjustDOWN(pH->_pArray, pH->_Size, 0);
		}
	}
	fclose(pf);
	pf = NULL;

	pHeapData ret = NULL;
	ret = (pHeapData)realloc(pH->_pArray, sizeof(HeapData) * pH->_Size);
	if (ret == NULL)
	{
		ret = pH->_pArray;
		free(pH);
	}
	else
	{
		HeapSort(ret, pH->_Size);
		free(pH);
	}
	return ret;
}

pHeapData TopK(int k)
{
	FILE* pf = fopen("data.txt", "r");
	if (pf == NULL)
	{
		perror("TopK open fail");
		return NULL;
	}
	pHeapData pArray = (pHeapData)malloc(sizeof(HeapData) * k);
	if (pArray == NULL)
	{
		perror("TopK malloc fail");
		return NULL;
	}
	int circulation = 0;
	for (; circulation < k; circulation++)
	{
		fscanf(pf, "%d", &(pArray[circulation]));
	}
	for (circulation = FindParent(k - 1, k); circulation >= 0; circulation--)
	{
		adjustDOWN(pArray, k, circulation);
	}
	HeapData val = 0;
	while (!feof(pf))
	{
		fscanf(pf, "%d", &val);
		if (rule(val, pArray[0]))
		{
			pArray[0] = val;
			adjustDOWN(pArray, k, 0);
		}
	}
	fclose(pf);
	pf = NULL;

	for (circulation = k - 1; circulation > 0; circulation--)
	{
		Swap(&(pArray[0]), &(pArray[circulation]));
		adjustDOWN(pArray, circulation, 0);
	}

	return pArray;
}