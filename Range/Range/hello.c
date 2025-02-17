#include<float.h>  


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 上面这些都不用再包含了


// 随机生成 [min, max) 区间的浮点数
float generateRandomFloat(float min, float max) {
    if (min >= max) {
        printf("Error: min must be less than max.\n");
        return -1.0f; // 返回一个错误值
    }
    // 生成一个 [0, 1) 的随机浮点数
    float random = (float)rand() / (float)RAND_MAX;
    // 映射到 [min, max) 区间
    return min + random * (max - min);
}

int main() {
    // 初始化随机数种子
    srand((unsigned int)time(NULL));

    // 测试随机生成的浮点数
    float lowerBound = 1.5f, upperBound = 5.5f;

    // 上面不用看  是为float的获得做准备

    // 创建静态数组
    float arr[10] = { 0 };

    // 插入随机数据
    for (int i = 0; i < 10; i++) {
        arr[i] = generateRandomFloat(lowerBound, upperBound);
    }

    // 找最大值
    float currentMax = arr[0];
    for (int i = 1; i < 10; i++) {
        if (arr[i] > currentMax) currentMax = arr[i];
    }

    // 找最小值
    float currentMin = arr[0];
    for (int i = 1; i < 10; i++) {
        if (arr[i] < currentMin) currentMin = arr[i];
    }

    // 计算范围
    float range = currentMax - currentMin;

    // 输出结果
    printf("Max: %f\n", currentMax);
    printf("Min: %f\n", currentMin);
    printf("Range: %f\n", range);

    return 0;
}