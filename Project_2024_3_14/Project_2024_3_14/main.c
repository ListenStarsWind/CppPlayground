#define _CRT_SECURE_NO_WARNINGS
//声明：由于本程序使用了变长数组，因此不要使用VS进行编译；
//这个题目的名字叫矩阵转置，不好描述，你直接看链接吧：
//https ://www.nowcoder.com/share/jump/9209693051710405192411
//我本来还以为要创建两个数组，结果只要一个数组就够了。
//注意变长数组不能初始化。
//我还是建议你画个棋盘看看，你看比如是2，下标先是0,1，后来变成了1,0；
#include <stdio.h>

int main() {
	int a, b;
	int i, j;

	while (scanf("%d %d", &a, &b) != EOF) {
		int arr[a][b];//不能写成int arr[a][b] = {0};这就是前文注释里提到的初始化。
		for (i = 0; i < a; i++) {
			for (j = 0; j < b; j++)
				scanf("%d ", &arr[i][j]);
		}
		for (i = 0; i < b; i++) {
			for (j = 0; j < a; j++)
				printf("%d ", arr[j][i]);
			printf("\n");
		}

	}
	return 0;
}