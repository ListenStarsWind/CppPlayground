
#define choose 1

#if choose

#include <gsl/gsl_integration.h>
#include <gsl/gsl_randist.h>
#include <stdio.h>
#include <math.h>

#define KILL_RADIUS 20
#define STATISTICS_Z 40
#define SUBMARINE_LENGTH 120
#define SUBMARINE_DEPTH 150

double normal_cdf(double x) {
    double sum = 0.0;
    double step = 0.001; // ���ֲ���
    for (double i = -10; i <= x; i += step) {
        sum += gsl_ran_ugaussian_pdf(i) * step; // ʹ�þ��η�������ֵ����
    }
    return sum;
}

double hit_probability_with_error() {
    gsl_integration_workspace* workspace = gsl_integration_workspace_alloc(1000);
    double result, error;

    gsl_function F;
    F.function = &gsl_ran_ugaussian_pdf;
    F.params = NULL;

    double a = SUBMARINE_DEPTH - KILL_RADIUS; // ��������
    double b = SUBMARINE_DEPTH + KILL_RADIUS; // ��������

    // ���л���
    gsl_integration_qag(&F, a, b, 0, 1e-7, 1000, GSL_INTEG_GAUSS61, workspace, &result, &error);

    gsl_integration_workspace_free(workspace);
    return result;
}

int main() {
    double probability = hit_probability_with_error();
    printf("Hit Probability with Error: %f\n", probability);
    return 0;
}

#endif

#if !choose
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define M_PI 3.14159265358979323846


#define NUM_SAMPLES 1000000 // ��������
#define RADIUS 20.0         // ����뾶
#define H0 150.0            // Z ����ľ�ֵ
#define L 120.0             // Z ���������
#define SIGMA_Z 40.0        // Z ����ı�׼��
#define SIGMA_XY 120.0      // XY ����ı�׼��
#define LENGTH 100.0        // ������ĳ���
#define WIDTH 20.0          // ������Ŀ��
#define HEIGHT 25.0         // ������ĸ߶�

// ��׼��̬�ֲ��ܶȺ���
double phi(double x) {
    return (1.0 / sqrt(2 * M_PI)) * exp(-0.5 * x * x);
}

// ��β��̬�ֲ��ܶȺ���
double truncated_normal_density(double v) {
    if (v < L) return 0.0;
    double z = (v - H0) / SIGMA_Z;
    double density = (1.0 / SIGMA_Z) * phi(z);
    double truncation = (1.0 - phi((L - H0) / SIGMA_Z));
    return density / truncation;
}

// �����볤���������ĸ���
double calculate_collision_probability(double drop_distance) {
    int collisions = 0;

    for (int i = 0; i < NUM_SAMPLES; i++) {
        // ���� XY ����
        double x = ((double)rand() / RAND_MAX) * 2 * SIGMA_XY - SIGMA_XY;
        double y = ((double)rand() / RAND_MAX) * 2 * SIGMA_XY - SIGMA_XY;

        // ���� Z ����
        double z = H0 + SIGMA_Z * ((double)rand() / RAND_MAX) * 2 - drop_distance;

        // ����Ƿ�����
        if (sqrt(x * x + y * y) <= RADIUS && z <= drop_distance && z >= 0) {
            if (x >= -LENGTH / 2 && x <= LENGTH / 2 && y >= -WIDTH / 2 && y <= WIDTH / 2) {
                collisions++;
            }
        }
    }

    return (double)collisions / NUM_SAMPLES;
}

int main() {
    srand(time(NULL));

    double max_probability = 0.0;
    double best_distance = 0.0;

    // ���Բ�ͬ���������
    for (double drop_distance = 0; drop_distance <= 300; drop_distance += 1) {
        double probability = calculate_collision_probability(drop_distance);
        if (probability > max_probability) {
            max_probability = probability;
            best_distance = drop_distance;
        }
    }

    printf("����������: %.2f, �����������: %.6f\n", best_distance, max_probability);

    return 0;
}

#endif