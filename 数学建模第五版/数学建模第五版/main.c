#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#define M_PI 3.14159265358979323846

// 正态分布函数
double normal_distribution(double x, double mean, double stddev) {
    return (1.0 / (stddev * sqrt(2 * M_PI))) * exp(-0.5 * pow((x - mean) / stddev, 2));
}

// 计算误差情况下的命中概率
double error_hit_probability(double mu_x, double sigma_x, double mu_y, double sigma_y, double mu_h, double sigma_h, double R, double x, double y) {
    double prob_x = normal_distribution(x, mu_x, sigma_x);
    double prob_y = normal_distribution(y, mu_y, sigma_y);
    double prob_h = normal_distribution(mu_h, mu_h, sigma_h);

    // 计算命中区域
    double hit_area = M_PI * R * R; // 命中区域面积
    return prob_x * prob_y * prob_h * hit_area; // 简化的命中概率
}

int main() {
    srand(time(NULL));

    double mu_x = 0, sigma_x = 10; // 潜艇水平坐标参数
    double mu_y = 0, sigma_y = 10;
    double mu_h = 150, sigma_h = 5; // 潜艇深度参数
    double R = 20; // 杀伤半径
    double x = 10; // 投弹落点
    double y = 10;

    double probability = error_hit_probability(mu_x, sigma_x, mu_y, sigma_y, mu_h, sigma_h, R, x, y);
    printf("误差情况下的命中概率: %f\n", probability);
    return 0;
}
