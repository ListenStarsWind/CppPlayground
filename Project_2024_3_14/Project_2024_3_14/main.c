#define _CRT_SECURE_NO_WARNINGS
//���������ڱ�����ʹ���˱䳤���飬��˲�Ҫʹ��VS���б��룻
//�����Ŀ�����ֽо���ת�ã�������������ֱ�ӿ����Ӱɣ�
//https ://www.nowcoder.com/share/jump/9209693051710405192411
//�ұ�������ΪҪ�����������飬���ֻҪһ������͹��ˡ�
//ע��䳤���鲻�ܳ�ʼ����
//�һ��ǽ����㻭�����̿������㿴������2���±�����0,1�����������1,0��
#include <stdio.h>

int main() {
	int a, b;
	int i, j;

	while (scanf("%d %d", &a, &b) != EOF) {
		int arr[a][b];//����д��int arr[a][b] = {0};�����ǰ��ע�����ᵽ�ĳ�ʼ����
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