#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define M_PI 3.14159265358979323846

#define R 20.0         // 球体半径
#define L 100.0        // 长方体的长度
#define W 20.0         // 长方体的宽度
#define H 25.0         // 长方体的高度
#define MU_X 0.0       // X 坐标的均值
#define SIGMA_X 120.0  // X 坐标的标准差
#define MU_Z 0.0     // Z 坐标的均值
#define SIGMA_Z 120.0   // Z 坐标的标准差

double phi(double x) {
    return (1.0 / sqrt(2 * M_PI)) * exp(-0.5 * x * x);
}

double truncated_normal_probability(double mu, double sigma, double lower, double upper) {
    double lower_z = (lower - mu) / sigma;
    double upper_z = (upper - mu) / sigma;
    return phi(upper_z) - phi(lower_z);
}

int main() {
    srand(time(NULL));

    // 计算 X 方向的相遇概率
    double x_lower = MU_X - L / 2 - R;
    double x_upper = MU_X + L / 2 + R;
    double x_probability = truncated_normal_probability(MU_X, SIGMA_X, x_lower, x_upper);

    // 计算 Z 方向的相遇概率
    double z_lower = MU_Z - H / 2 - R;
    double z_upper = MU_Z + H / 2 + R;
    double z_probability = truncated_normal_probability(MU_Z, SIGMA_Z, z_lower, z_upper);

    // 总相遇概率
    double total_probability = x_probability * z_probability;

    printf("最大相遇概率: %.6f\n", total_probability);
    printf("球的XY坐标: (%.2f, 150)\n", MU_X); // 最佳 X 坐标为均值

    return 0;
}
