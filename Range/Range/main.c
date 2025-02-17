#include<stddef.h>
#include <stdlib.h>
#include<string.h>
#include<float.h>
#include<assert.h>

typedef struct Range
{
	float* _v;
	size_t _size;
	size_t _capacity;
}Range;

Range* creat()
{
	Range* p = malloc(sizeof(Range));
	if (p == NULL)
	{
		perror("fatal filed creat");
		return NULL;
	}
	p->_size = 0;
	p->_capacity = 0;
	p->_v = NULL;
	return p;
}

void insert(Range* pR, float value)
{
	if (pR->_capacity == pR->_size)
	{
		size_t old_size = pR->_size;
		size_t new_size = old_size == 0 ? 1 : old_size*2;
		float* p = malloc(new_size*sizeof(float));
		if (p == NULL)
		{
			perror("fatal filed insert");
			return;
		}
		memcpy(p, pR->_v, sizeof(float)*pR->_size);
		free(pR->_v);
		pR->_v = p;
		pR->_capacity = new_size;
	}

	pR->_v[pR->_size++] = value;
}

// 使用之后  把pR置空
void destroy(Range* pR)
{
	assert(pR);
	free(pR->_v);
	free(pR);
}

float my_max(Range* pR)
{
	assert(pR);
	size_t i = 0;
	float max = 0.00;
	while (i < pR->_size)
	{
		if (pR->_v[i] > max)
		{
			max = pR->_v[i];
		}
		i++;
	}
	return max;
}


float my_min(Range* pR)
{
	assert(pR);
	size_t i = 0;
	float min = FLT_MAX;
	while (i < pR->_size)
	{
		if (min > pR->_v[i])
		{
			min = pR->_v[i];
		}
		i++;
	}
	return min;
}

float range(Range* pR)
{
	assert(pR);
	float max = my_max(pR);
	float min = my_min(pR);
	return max - min;
}

#include<stdio.h>

//int main() {
//	// 创建 Range 实例
//	Range* r = creat();
//	if (!r) {
//		return 1; // 如果创建失败，则退出
//	}
//
//	// 向 Range 中插入一些值
//	insert(r, 1.2f);
//	insert(r, 5.8f);
//	insert(r, 3.3f);
//	insert(r, -2.5f);
//	insert(r, 7.1f);
//
//	// 输出最大值、最小值和范围
//	printf("Max: %f\n", my_max(r));  // 应该输出 7.1
//	printf("Min: %f\n", my_min(r));  // 应该输出 -2.5
//	printf("Range: %f\n", range(r)); // 应该输出 9.6 (7.1 - (-2.5))
//
//	// 清理内存
//	destroy(r);
//	r = NULL;
//
//	return 0;
//}