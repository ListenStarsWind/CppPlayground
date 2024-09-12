#include"configure.h"

double Points_for_case_I() {
    gsl_integration_workspace* workspace = gsl_integration_workspace_alloc(1000);
    double result, error;

    // ��������
    double a = -(kill_radius / 2) * cos((M_PI / 2) - (M_PI / 2)); // ����
    double b = -a;  // ����

    // ׼����������
    gsl_function F;
    F.function = &gsl_ran_ugaussian_pdf;
    F.params = NULL;

    // ���л���
    gsl_integration_qag(&F, a, b, 0, 1e-7, 1000, GSL_INTEG_GAUSS61, workspace, &result, &error);

    // ������
    double ret = result;

    // �ͷŹ����ռ�
    gsl_integration_workspace_free(workspace);

    return result;
}

double Points_for_case_II() {
    gsl_integration_workspace* workspace = gsl_integration_workspace_alloc(1000);
    double result, error;

    // ��������
    double a = -(kill_radius / 2) * sin((M_PI / 2) - (M_PI / 2)); // ����
    double b = -a;  // ����

    // ׼����������
    gsl_function F;
    F.function = &gsl_ran_ugaussian_pdf;
    F.params = NULL;

    // ���л���
    gsl_integration_qag(&F, a, b, 0, 1e-7, 1000, GSL_INTEG_GAUSS61, workspace, &result, &error);

    // ������
    double ret = result;

    // �ͷŹ����ռ�
    gsl_integration_workspace_free(workspace);

    return result;
}

double Points_for_case_III() {
    gsl_integration_workspace* workspace = gsl_integration_workspace_alloc(1000);
    double result, error;

    // ��������
    double a = -(kill_radius / 2) * sin((M_PI / 2) - (M_PI / 2)); // ����
    double b = -a;  // ����

    // ׼����������
    gsl_function F;
    F.function = &gsl_ran_ugaussian_pdf;
    F.params = NULL;

    // ���л���
    gsl_integration_qag(&F, a, b, 0, 1e-7, 1000, GSL_INTEG_GAUSS61, workspace, &result, &error);

    // ������
    double ret = result;

    // �ͷŹ����ռ�
    gsl_integration_workspace_free(workspace);

    return result;
}

double normal_cdf(double x) {
    double sum = 0.0;
    double step = 0.001; // ���ֲ���
    for (double i = -10; i <= x; i += step) {
        sum += gsl_ran_ugaussian_pdf(i) * step; // ʹ�þ��η�������ֵ����
    }
    return sum;
}

double end(double v)
{
    double a = (v - 150.0) / statistics_Z;
    double b = gsl_ran_ugaussian_pdf(a);
    double c = (120.0 - 150.0) / statistics_Z;
    double d = 1 - normal_cdf((120.0 - 150.0) / statistics_Z);
    return b / d;
}

double Points_for_case_end() {
    gsl_integration_workspace* workspace = gsl_integration_workspace_alloc(1000);
    double result, error;

    gsl_function F;
    F.function = &end;
    F.params = NULL;

    double a = 150.0 + 25.0 / 2 + kill_radius; // ��������
    double b = 150.0 + 25.0 / 2; // ��������

    // ���л���
    gsl_integration_qag(&F, a, b, 0, 1e-7, 1000, GSL_INTEG_GAUSS61, workspace, &result, &error);

    double ret = result;

    gsl_integration_workspace_free(workspace);
    return ret;
}