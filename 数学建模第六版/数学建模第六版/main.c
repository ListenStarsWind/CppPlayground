#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#define M_PI 3.14159265358979323846

#define NUM_BOMBS 9 // �����

// ��̬�ֲ�����
double normal_distribution(double x, double mean, double stddev) {
    return (1.0 / (stddev * sqrt(2 * M_PI))) * exp(-0.5 * pow((x - mean) / stddev, 2));
}

// ��������һö����еĸ���
double at_least_one_hit_probability(double mu_x, double sigma_x, double mu_y, double sigma_y, double R, double x, double y) {
    double single_hit_prob = normal_distribution(x, mu_x, sigma_x) * normal_distribution(y, mu_y, sigma_y);
    return 1 - pow((1 - single_hit_prob), NUM_BOMBS); // ����һö���и���
}

int main() {
    srand(time(NULL));

    double mu_x = 0, sigma_x = 10; // Ǳͧˮƽ�������
    double mu_y = 0, sigma_y = 10;
    double R = 20; // ɱ�˰뾶
    double x = 10; // Ͷ�����
    double y = 10;

    double probability = at_least_one_hit_probability(mu_x, sigma_x, mu_y, sigma_y, R, x, y);
    printf("����һö����и���: %f\n", probability);
    return 0;
}
