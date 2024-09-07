#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define M_PI 3.14159265358979323846

#define NUM_SAMPLES 100 // ��������
#define RADIUS 20.0         // ����뾶
#define H0 150.0            // Z ����ľ�ֵ
#define L 120.0             // Z ���������
#define SIGMA_Z 40.0        // Z ����ı�׼��
#define SIGMA_XY 120.0      // XY ����ı�׼��
#define LENGTH 100.0        // ������ĳ���
#define WIDTH 20.0          // ������Ŀ��
#define HEIGHT 25.0         // ������ĸ߶�
#define GRID_SIZE 3         // ��������������

// ��׼��̬�ֲ��ܶȺ���
double phi(double x) {
    return (1.0 / sqrt(2 * M_PI)) * exp(-0.5 * x * x);
}

// �����볤���������ĸ���
double calculate_collision_probability(double drop_distance, double square_size) {
    int collisions = 0;

    // �������ĵ�ƫ����
    double offset = (square_size * (GRID_SIZE - 1)) / 2.0;

    for (int i = 0; i < NUM_SAMPLES; i++) {
        // ���� XY ����
        double x_center = ((double)rand() / RAND_MAX) * 2 * SIGMA_XY - SIGMA_XY;
        double y_center = ((double)rand() / RAND_MAX) * 2 * SIGMA_XY - SIGMA_XY;

        // ���� Z ����
        double z = H0 + SIGMA_Z * ((double)rand() / RAND_MAX) * 2 - drop_distance;

        // ���ÿ���������ײ
        for (int row = 0; row < GRID_SIZE; row++) {
            for (int col = 0; col < GRID_SIZE; col++) {
                double x = x_center + (col - 1) * square_size; // ��������� X ����
                double y = y_center + (row - 1) * square_size; // ��������� Y ����

                // ����Ƿ�����
                if (sqrt(x * x + y * y) <= RADIUS && z <= drop_distance && z >= 0) {
                    if (x >= -LENGTH / 2 && x <= LENGTH / 2 && y >= -WIDTH / 2 && y <= WIDTH / 2) {
                        collisions++;
                        break; // ����һ����������������ѭ��
                    }
                }
            }
            if (collisions > 0) break; // ����Ѿ��ҵ���ײ��������ѭ��
        }
    }

    return (double)collisions / NUM_SAMPLES;
}

int main() {
    srand(time(NULL));

    double max_probability = 0.0;
    double best_distance = 0.0;
    double best_square_size = 0.0;

    // ���Բ�ͬ���������������α߳�
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

    printf("����������: %.2f, ��������α߳�: %.2f, �����������: %.6f\n", best_distance, best_square_size, max_probability);

    return 0;
}

