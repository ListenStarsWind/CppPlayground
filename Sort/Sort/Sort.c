#include"Sort.h"

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
	int key = Search_mode(pArray, left, right);
	_Quick_sort_root(pArray, left, key - 1);
	_Quick_sort_root(pArray, key + 1, right);
}

void Quick_sort(pSortData pArray, int Size)
{
	_Quick_sort_root(pArray, 0, Size - 1);
}