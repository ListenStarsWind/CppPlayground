#include"Sort.h"
#include"Stack.h"

bool compare(SortData val1, SortData val2)
{
	if (val1 > val2)
		return true;
	else
		return false;
}

void Swap(pSortData p1, pSortData p2)
{
	SortData transitory = *p1;
	*p1 = *p2;
	*p2 = transitory;
}

void Bubble_sort(pSortData pArray, int Size)
{
	int i = 0;
	int j = 0;
	for (i = 0; i < Size - 1; i++)
	{
		bool falg = true;
		for (j = 0; j < Size - i - 1; j++)
		{
			if (compare(pArray[j], pArray[j + 1]))
			{
				Swap(&pArray[j], &pArray[j + 1]);
				falg = false;
			}
		}
		if (falg)
			break;
	}
}

void Insert_sort(pSortData pArray, int Size)
{
	int compare_begin, protection_compare;
	SortData temporary_storage;
	for (compare_begin = 1; compare_begin < Size; compare_begin++)
	{
		temporary_storage = pArray[compare_begin];
		for (protection_compare = compare_begin - 1; protection_compare >= 0; protection_compare--)
		{
			if (compare(pArray[protection_compare], temporary_storage))
			{
				pArray[protection_compare + 1] = pArray[protection_compare];
			}
			else
			{
				break;
			}
		}
		pArray[protection_compare + 1] = temporary_storage;
	}
}

void Shell_sort(pSortData pArray, int Size)
{
	int intervals = Size;
	int compare_begin, protection_compare, initial = 0;
	SortData replica;
	while (intervals > 1)
	{
		intervals = intervals / 3 + 1;
		for (compare_begin = initial + intervals; compare_begin < Size; compare_begin++)
		{
			replica = pArray[compare_begin];
			for (protection_compare = compare_begin - intervals; protection_compare >= 0; protection_compare -= intervals)
			{
				if (compare(pArray[protection_compare], replica))
				{
					pArray[protection_compare + intervals] = pArray[protection_compare];
				}
				else
				{
					break;
				}
			}
			pArray[protection_compare + intervals] = replica;
		}
	}
}

void Select_sort(pSortData pArray, int Size)
{
	int pend_begin, pend_end;
	int max, min, current;
	for (pend_begin = 0, pend_end = Size - 1; pend_begin < pend_end; pend_begin++, pend_end--)
	{
		max = pend_end;
		min = pend_begin;
		for (current = pend_begin; current < pend_end + 1; current++)
		{
			if (compare(pArray[current], pArray[max]))
			{
				max = current;
			}
			if (compare(pArray[min], pArray[current]))
			{
				min = current;
			}
		}
		Swap(&(pArray[pend_begin]), &(pArray[min]));
		if (pend_begin == max)
		{
			max = min;
		}
		Swap(&(pArray[pend_end]), &(pArray[max]));
	}
}

static int FindFristChild(int parent, int Size)
{
	int child = parent * 2 + 1;
	if (child < Size)
	{
		return child;
	}
	else
	{
		return -1;
	}
}

static int FindSecondChild(int parent, int Size)
{
	int child = parent * 2 + 2;
	if (child < Size)
	{
		return child;
	}
	else
	{
		return -1;
	}
}

static void DownwardAdjustment(pSortData pArray, int Size, int start)
{
	int parent = start;
	int child;
	while (parent < Size)
	{
		int first_child = FindFristChild(parent, Size);
		int second_child = FindSecondChild(parent, Size);
		if (first_child == -1 && second_child == -1)
		{
			break;
		}
		else
		{
			child = first_child;
			if (second_child != -1)
			{
				if (compare(pArray[second_child], pArray[first_child]))
				{
					child = second_child;
				}
			}
		}
		if (compare(pArray[child], pArray[parent]))
		{
			Swap(&(pArray[child]), &(pArray[parent]));
		}
		parent = child;
	}
}

void Heap_sort(pSortData pArray, int Size)
{
	int parent = ((Size - 1) - 1) / 2;
	for (; parent >= 0; parent--)
	{
		DownwardAdjustment(pArray, Size, parent);
	}
	int end;
	for (end = Size - 1; end > 0; end--)
	{
		Swap(&(pArray[0]), &(pArray[end]));
		DownwardAdjustment(pArray, end, 0);
	}
}

static int Hoare_mode(pSortData pArray, int left, int right)
{
	int mid = middle_of_three(pArray, left, right);
	Swap(&(pArray[mid]), &(pArray[left]));
	int key = left;
	while (left < right)
	{
		while (left < right && !compare(pArray[key], pArray[right]))
		{
			right--;
		}
		while (left < right && !compare(pArray[left], pArray[key]))
		{
			left++;
		}
		Swap(&(pArray[left]), &(pArray[right]));
	}
	Swap(&(pArray[right]), &(pArray[key]));
	return right;
}

static int FillGap_mode(pSortData pArray, int left, int right)
{
	int mid = middle_of_three(pArray, left, right);
	Swap(&(pArray[mid]), &(pArray[left]));
	SortData key = pArray[left];
	int gap = left;
	while (left < right)
	{
		while (left < right && !compare(key, pArray[right]))
		{
			right--;
		}
		pArray[gap] = pArray[right];
		gap = right;
		while (left < right && !compare(pArray[left], key))
		{
			left++;
		}
		pArray[gap] = pArray[left];
		gap = left;
	}
	pArray[gap] = key;
	return gap;
}

static int Search_mode(pSortData pArray, int left, int right)
{
	int mid = middle_of_three(pArray, left, right);
	Swap(&(pArray[mid]), &(pArray[left]));
	int key = left;
	int prev = left;
	int curr = left;
	while (curr <= right)
	{
		if (compare(pArray[key], pArray[curr]) && ++prev != curr)
		{
			Swap(&(pArray[prev]), &(pArray[curr]));
		}
		curr++;
	}
	Swap(&(pArray[prev]), &(pArray[key]));
	return prev;
}

static void _Quick_sort_root(pSortData pArray, int left, int right)
{
	if (left >= right)
		return;
	int key = Hoare_mode(pArray, left, right);
	_Quick_sort_root(pArray, left, key - 1);
	_Quick_sort_root(pArray, key + 1, right);
}

void Quick_sort(pSortData pArray, int Size)
{
	_Quick_sort_root(pArray, 0, Size - 1);
}

static void _Quick_sort_root_particularly(pSortData pArray, int left, int right)
{
	if (left >= right)
		return;

	int mid = middle_of_three(pArray, left, right);
	Swap(&(pArray[mid]), &(pArray[left]));

	SortData key = pArray[left];
	int begin = left;
	int current = begin + 1;
	int end = right;
	while (current <= end)
	{
		if (pArray[current] < key)
		{
			Swap(&(pArray[begin++]), &(pArray[current++]));
		}
		else if (pArray[current] == key)
		{
			current++;
		}
		else if (pArray[current] > key)
		{
			Swap(&(pArray[end--]), &(pArray[current]));
		}
	}

	_Quick_sort_root_particularly(pArray, left, begin - 1);
	_Quick_sort_root_particularly(pArray, end + 1, right);
}

void Quick_sort_particularly(pSortData pArray, int Size)
{
	_Quick_sort_root_particularly(pArray, 0, Size - 1);
}

int middle_of_three(pSortData pArray, int left, int right)
{
	srand((unsigned int)time(NULL));
	int mid = left + (rand() % (right - left));
	if (compare(pArray[left], pArray[mid]))
	{
		if (compare(pArray[mid], pArray[right]))
		{
			return mid;
		}
		else
		{
			if (compare(pArray[left], pArray[right]))
			{
				return right;
			}
			else
				return left;
		}
	}
	else
	{
		if (compare(pArray[right], pArray[mid]))
		{
			return mid;
		}
		else
		{
			if (compare(pArray[left], pArray[right]))
			{
				return left;
			}
			else
				return right;
		}
	}
}

void Quick_sort_NonR(pSortData pArray, int Size)
{
	PST pStack = STInit();
	STPush(pStack, Size - 1);
	STPush(pStack, 0);
	while (!STEmpty(pStack))
	{
		int left = STPop(pStack);
		int right = STPop(pStack);
		int key = Hoare_mode(pArray, left, right);
		if (key + 1 < right)
		{
			STPush(pStack, right);
			STPush(pStack, key + 1);
		}
		if (left < key - 1)
		{
			STPush(pStack, key - 1);
			STPush(pStack, left);
		}
	}
	STDestroy(pStack);
}

void _Merge_sort_root(pSortData pArray, int left, int right, pSortData p_Temporary_Storage)
{
	if (left >= right)
		return;
	if (right - left + 1 < 10)
	{
		Insert_sort(pArray + left, right - left + 1);
		return;
	}
	int mid = (left + right) / 2;
	_Merge_sort_root(pArray, left, mid, p_Temporary_Storage);
	_Merge_sort_root(pArray, mid + 1, right, p_Temporary_Storage);
	int begin1 = left, end1 = mid;
	int begin2 = mid + 1, end2 = right;
	int begin = left;
	while (begin1 <= end1 && begin2 <= end2)
	{
		if (compare(pArray[begin1], pArray[begin2]))
		{
			p_Temporary_Storage[begin++] = pArray[begin2++];
		}
		else
		{
			p_Temporary_Storage[begin++] = pArray[begin1++];
		}
	}
	while (begin1 <= end1)
	{
		p_Temporary_Storage[begin++] = pArray[begin1++];
	}
	while (begin2 <= end2)
	{
		p_Temporary_Storage[begin++] = pArray[begin2++];
	}
	memcpy(pArray + left, p_Temporary_Storage + left, sizeof(SortData) * (right - left + 1));
}

void Merge_sort(pSortData pArray, int Size)
{
	pSortData pTS = (pSortData)malloc(sizeof(SortData) * Size);
	if (pTS == NULL)
	{
		perror("Merge_sort pTS fail");
		return; 
	}
	_Merge_sort_root(pArray, 0, Size - 1, pTS);
	free(pTS);
}

void Merge_sort_NonR(pSortData pArray, int Size)
{
	pSortData pTS = (pSortData)malloc(sizeof(SortData) * Size);
	if (pTS == NULL)
	{
		perror("Merge_sort pTS fail");
		return;
	}
	int gap;
	for (gap = 1; gap < Size; gap *= 2)
	{
		// The variable ¡°begin¡± changes itself when it is written to the staging array, 
		// eliminating the need to manually control the iteration.
		int begin = 0;
		while (begin < Size)
		{
			// The variable ¡°start¡± is used to control the starting position of the data copy.
			int start = begin;
			int begin1 = begin, end1 = begin1 + gap - 1;
			int begin2 = end1 + 1, end2 = begin2 + gap - 1;

			// The three conditional statements along with 
			// the outer loop condition prevent the variable from going out of bounds.
			if (end1 >= Size)
			{
				end1 = Size - 1;
				end2 = Size - 1;
				begin2 = end2 + 1;
			}
			if (begin2 >= Size)
			{
				end2 = Size - 1;
				begin2 = end2 + 1;
			}
			if (end2 >= Size)
			{
				end2 = Size - 1;
			}


			while (begin1 <= end1 && begin2 <= end2)
			{
				if (compare(pArray[begin1], pArray[begin2]))
				{
					pTS[begin++] = pArray[begin2++];
				}
				else
				{
					pTS[begin++] = pArray[begin1++];
				}
			}
			while (begin1 <= end1)
			{
				pTS[begin++] = pArray[begin1++];
			}
			while (begin2 <= end2)
			{
				pTS[begin++] = pArray[begin2++];
			}
			memcpy(pArray + start, pTS + start, sizeof(SortData) * (end2 - start + 1));
		}
	}
	free(pTS);
}

void Merge_sort_NonR1(pSortData pArray, int Size)
{
	pSortData pTS = (pSortData)malloc(sizeof(SortData) * Size);
	if (pTS == NULL)
	{
		perror("Merge_sort pTS fail");
		return;
	}
	int gap;
	for (gap = 1; gap < Size; gap *= 2)
	{
		int begin = 0;
		while (begin < Size)
		{
			int begin1 = begin, end1 = begin1 + gap - 1;
			int begin2 = end1 + 1, end2 = begin2 + gap - 1;

			
			if (end1 >= Size)
			{
				end1 = Size - 1;
				end2 = Size - 1;
				begin2 = end2 + 1;
			}
			if (begin2 >= Size)
			{
				end2 = Size - 1;
				begin2 = end2 + 1;
			}
			if (end2 >= Size)
			{
				end2 = Size - 1;
			}


			while (begin1 <= end1 && begin2 <= end2)
			{
				if (compare(pArray[begin1], pArray[begin2]))
				{
					pTS[begin++] = pArray[begin2++];
				}
				else
				{
					pTS[begin++] = pArray[begin1++];
				}
			}
			while (begin1 <= end1)
			{
				pTS[begin++] = pArray[begin1++];
			}
			while (begin2 <= end2)
			{
				pTS[begin++] = pArray[begin2++];
			}
		}
		memcpy(pArray, pTS, sizeof(SortData) * Size);
	}
	free(pTS);
}

void count_sort(int* pArray, int Size)
{
	int min = pArray[0], max = pArray[0];
	int current;
	for (current = 0; current < Size; current++)
	{
		if (min > pArray[current])
		{
			min = pArray[current];
		}
		if (max < pArray[current])
		{
			max = pArray[current];
		}
	}
	int temSize = max - min + 1;
	int* p_tem = (int*)calloc(temSize, sizeof(int));
	if (p_tem == NULL)
	{
		perror("count_sort malloc fail");
		return;
	}
	for (current = 0; current < Size; current++)
	{
		p_tem[pArray[current] - min]++;
	}
	int i = 0;
	for (current = 0; current < temSize; current++)
	{
		while (p_tem[current])
		{
			pArray[i++] = current + min;
			p_tem[current]--;
		}
	}
	free(p_tem);
}