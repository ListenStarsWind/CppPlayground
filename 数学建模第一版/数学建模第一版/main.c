#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define M_PI 3.14159265358979323846

// ��̬�ֲ���������ɺ�����Box-Muller������
double normal_random(double mean, double stddev) {
    double u1 = rand() / (double)RAND_MAX;
    double u2 = rand() / (double)RAND_MAX;
    return mean + stddev * sqrt(-2.0 * log(u1)) * cos(2.0 * M_PI * u2);
}

// �����ص�����
double calculate_overlap_probability(double circle_x, double circle_y, double radius,
    double rect_width, double rect_height,
    double mean_x, double stddev_x,
    double mean_y, double stddev_y,
    int num_samples, double* best_x, double* best_y) {
    int overlap_count = 0;
    double max_prob = 0.0;

    for (int i = 0; i < num_samples; i++) {
        // ����̬�ֲ����ɳ��������ĵ�
        double rect_x = normal_random(mean_x, stddev_x);
        double rect_y = normal_random(mean_y, stddev_y);

        // ���㳤���ε������
        double nearest_x = fmax(rect_x - rect_width / 2, fmin(circle_x, rect_x + rect_width / 2));
        double nearest_y = fmax(rect_y - rect_height / 2, fmin(circle_y, rect_y + rect_height / 2));

        // �������
        double distance = sqrt(pow(circle_x - nearest_x, 2) + pow(circle_y - nearest_y, 2));

        // ����Ƿ��ص�
        if (distance <= radius) {
            overlap_count++;
            // �����������
            if ((overlap_count / (double)(i + 1)) > max_prob) {
                max_prob = overlap_count / (double)(i + 1);
                *best_x = rect_x;
                *best_y = rect_y;
            }
        }
    }

    // �����ص�����
    return (double)overlap_count / num_samples;
}

int main() {
    srand(time(NULL)); // �����������

    // ����Բ�β���
    double circle_x = 0.0; // Բ��X����
    double circle_y = 0.0; // Բ��Y����
    double radius = 20.0;    // �뾶

    // ���峤���β���
    double rect_width = 100.0;
    double rect_height = 20.0;
    double mean_x = 0.0;    // ��̬�ֲ���ֵX
    double stddev_x = 120.0;   // ��̬�ֲ���׼��X
    double mean_y = 0.0;    // ��̬�ֲ���ֵY
    double stddev_y = 120.0;   // ��̬�ֲ���׼��Y

    // ���ؿ���ģ�����
    int num_samples = 100000;

    // �洢�������
    double best_x = 0.0;
    double best_y = 0.0;

    // �����ص�����
    double overlap_probability = calculate_overlap_probability(circle_x, circle_y, radius,
        rect_width, rect_height,
        mean_x, stddev_x,
        mean_y, stddev_y,
        num_samples, &best_x, &best_y);

    printf("�ص�����: %f\n", overlap_probability);
    printf("������������: (%.2f, %.2f)\n", best_x, best_y);
    return 0;
}
