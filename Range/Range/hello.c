#include<float.h>  


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// ������Щ�������ٰ�����


// ������� [min, max) ����ĸ�����
float generateRandomFloat(float min, float max) {
    if (min >= max) {
        printf("Error: min must be less than max.\n");
        return -1.0f; // ����һ������ֵ
    }
    // ����һ�� [0, 1) �����������
    float random = (float)rand() / (float)RAND_MAX;
    // ӳ�䵽 [min, max) ����
    return min + random * (max - min);
}

int main() {
    // ��ʼ�����������
    srand((unsigned int)time(NULL));

    // ����������ɵĸ�����
    float lowerBound = 1.5f, upperBound = 5.5f;

    // ���治�ÿ�  ��Ϊfloat�Ļ����׼��

    // ������̬����
    float arr[10] = { 0 };

    // �����������
    for (int i = 0; i < 10; i++) {
        arr[i] = generateRandomFloat(lowerBound, upperBound);
    }

    // �����ֵ
    float currentMax = arr[0];
    for (int i = 1; i < 10; i++) {
        if (arr[i] > currentMax) currentMax = arr[i];
    }

    // ����Сֵ
    float currentMin = arr[0];
    for (int i = 1; i < 10; i++) {
        if (arr[i] < currentMin) currentMin = arr[i];
    }

    // ���㷶Χ
    float range = currentMax - currentMin;

    // ������
    printf("Max: %f\n", currentMax);
    printf("Min: %f\n", currentMin);
    printf("Range: %f\n", range);

    return 0;
}