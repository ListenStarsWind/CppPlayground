#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define M_PI 3.14159265358979323846

// 正态分布随机数生成函数（Box-Muller方法）
double normal_random(double mean, double stddev) {
    double u1 = rand() / (double)RAND_MAX;
    double u2 = rand() / (double)RAND_MAX;
    return mean + stddev * sqrt(-2.0 * log(u1)) * cos(2.0 * M_PI * u2);
}

// 计算重叠概率
double calculate_overlap_probability(double circle_x, double circle_y, double radius,
    double rect_width, double rect_height,
    double mean_x, double stddev_x,
    double mean_y, double stddev_y,
    int num_samples, double* best_x, double* best_y) {
    int overlap_count = 0;
    double max_prob = 0.0;

    for (int i = 0; i < num_samples; i++) {
        // 从正态分布生成长方形中心点
        double rect_x = normal_random(mean_x, stddev_x);
        double rect_y = normal_random(mean_y, stddev_y);

        // 计算长方形的最近点
        double nearest_x = fmax(rect_x - rect_width / 2, fmin(circle_x, rect_x + rect_width / 2));
        double nearest_y = fmax(rect_y - rect_height / 2, fmin(circle_y, rect_y + rect_height / 2));

        // 计算距离
        double distance = sqrt(pow(circle_x - nearest_x, 2) + pow(circle_y - nearest_y, 2));

        // 检查是否重叠
        if (distance <= radius) {
            overlap_count++;
            // 更新最佳坐标
            if ((overlap_count / (double)(i + 1)) > max_prob) {
                max_prob = overlap_count / (double)(i + 1);
                *best_x = rect_x;
                *best_y = rect_y;
            }
        }
    }

    // 返回重叠概率
    return (double)overlap_count / num_samples;
}

int main() {
    srand(time(NULL)); // 设置随机种子

    // 定义圆形参数
    double circle_x = 0.0; // 圆心X坐标
    double circle_y = 0.0; // 圆心Y坐标
    double radius = 20.0;    // 半径

    // 定义长方形参数
    double rect_width = 100.0;
    double rect_height = 20.0;
    double mean_x = 0.0;    // 正态分布均值X
    double stddev_x = 120.0;   // 正态分布标准差X
    double mean_y = 0.0;    // 正态分布均值Y
    double stddev_y = 120.0;   // 正态分布标准差Y

    // 蒙特卡洛模拟次数
    int num_samples = 100000;

    // 存储最佳坐标
    double best_x = 0.0;
    double best_y = 0.0;

    // 计算重叠概率
    double overlap_probability = calculate_overlap_probability(circle_x, circle_y, radius,
        rect_width, rect_height,
        mean_x, stddev_x,
        mean_y, stddev_y,
        num_samples, &best_x, &best_y);

    printf("重叠概率: %f\n", overlap_probability);
    printf("概率最大的坐标: (%.2f, %.2f)\n", best_x, best_y);
    return 0;
}
