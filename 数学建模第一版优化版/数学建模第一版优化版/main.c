#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define M_PI 3.14159265358979323846

#define R 20.0         // ����뾶
#define L 100.0        // ������ĳ���
#define W 20.0         // ������Ŀ��
#define H 25.0         // ������ĸ߶�
#define MU_X 0.0       // X ����ľ�ֵ
#define SIGMA_X 120.0  // X ����ı�׼��
#define MU_Z 0.0     // Z ����ľ�ֵ
#define SIGMA_Z 120.0   // Z ����ı�׼��

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

    // ���� X �������������
    double x_lower = MU_X - L / 2 - R;
    double x_upper = MU_X + L / 2 + R;
    double x_probability = truncated_normal_probability(MU_X, SIGMA_X, x_lower, x_upper);

    // ���� Z �������������
    double z_lower = MU_Z - H / 2 - R;
    double z_upper = MU_Z + H / 2 + R;
    double z_probability = truncated_normal_probability(MU_Z, SIGMA_Z, z_lower, z_upper);

    // ����������
    double total_probability = x_probability * z_probability;

    printf("�����������: %.6f\n", total_probability);
    printf("���XY����: (%.2f, 150)\n", MU_X); // ��� X ����Ϊ��ֵ

    return 0;
}
