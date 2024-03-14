#define _CRT_SECURE_NO_WARNINGS
//这个题目叫逆序输出，非常简单，完全可以不看，但这里有个好习惯可以学；
//题目：https ://www.nowcoder.com/share/jump/9209693051710406905222
#include<stdio.h>
int main()
{
	int a = 0;
	int arr[10] = { 0 };//这就是那个好习惯：定义一个数组，最好有初始化，当然，刚刚（上一个提交代码）中的变长数组可千万不要初始化。
	for (a = 0; a < 10; a++)
		scanf("%d", &arr[a]);/*如果你有时间，试试把scanf中的"%d"改成"%d "看看会发生什么；*/
	for (a = 9; a >= 0; a--)
		printf("%d ", arr[a]);
	return 0;
}