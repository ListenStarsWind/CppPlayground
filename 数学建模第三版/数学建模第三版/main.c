#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define M_PI 3.14159265358979323846

#define NUM_SAMPLES 100 // 采样数量
#define RADIUS 20.0         // 球体半径
#define H0 150.0            // Z 坐标的均值
#define L 120.0             // Z 坐标的下限
#define SIGMA_Z 40.0        // Z 坐标的标准差
#define SIGMA_XY 120.0      // XY 坐标的标准差
#define LENGTH 100.0        // 长方体的长度
#define WIDTH 20.0          // 长方体的宽度
#define HEIGHT 25.0         // 长方体的高度
#define GRID_SIZE 3         // 球体阵列行列数

// 标准正态分布密度函数
double phi(double x) {
    return (1.0 / sqrt(2 * M_PI)) * exp(-0.5 * x * x);
}

// 计算与长方体相遇的概率
double calculate_collision_probability(double drop_distance, double square_size) {
    int collisions = 0;

    // 球体中心的偏移量
    double offset = (square_size * (GRID_SIZE - 1)) / 2.0;

    for (int i = 0; i < NUM_SAMPLES; i++) {
        // 生成 XY 坐标
        double x_center = ((double)rand() / RAND_MAX) * 2 * SIGMA_XY - SIGMA_XY;
        double y_center = ((double)rand() / RAND_MAX) * 2 * SIGMA_XY - SIGMA_XY;

        // 生成 Z 坐标
        double z = H0 + SIGMA_Z * ((double)rand() / RAND_MAX) * 2 - drop_distance;

        // 检查每个球体的碰撞
        for (int row = 0; row < GRID_SIZE; row++) {
            for (int col = 0; col < GRID_SIZE; col++) {
                double x = x_center + (col - 1) * square_size; // 计算球体的 X 坐标
                double y = y_center + (row - 1) * square_size; // 计算球体的 Y 坐标

                // 检查是否相遇
                if (sqrt(x * x + y * y) <= RADIUS && z <= drop_distance && z >= 0) {
                    if (x >= -LENGTH / 2 && x <= LENGTH / 2 && y >= -WIDTH / 2 && y <= WIDTH / 2) {
                        collisions++;
                        break; // 至少一个球相遇，跳出内循环
                    }
                }
            }
            if (collisions > 0) break; // 如果已经找到碰撞，跳出外循环
        }
    }

    return (double)collisions / NUM_SAMPLES;
}

int main() {
    srand(time(NULL));

    double max_probability = 0.0;
    double best_distance = 0.0;
    double best_square_size = 0.0;

    // 尝试不同的下落距离和正方形边长
    for (double drop_distance = 0; drop_distance <= 300; drop_distance += 1) {
        for (double square_size = 10; square_size <= 50; square_size += 1) {
            double probability = calculate_collision_probability(drop_distance, square_size);
            if (probability > max_probability) {
                max_probability = probability;
                best_distance = drop_distance;
                best_square_size = square_size;
            }
        }
    }

    printf("最佳下落距离: %.2f, 最佳正方形边长: %.2f, 最大相遇概率: %.6f\n", best_distance, best_square_size, max_probability);

    return 0;
}

