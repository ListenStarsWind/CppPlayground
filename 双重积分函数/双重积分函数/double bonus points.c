#include <stdio.h>
#include <gsl/gsl_integration.h>
#include <math.h>

// 被积函数
double integrand(double x, void* params) {
    double value = exp(-x * x);
    if (isnan(value) || isinf(value)) {
        printf("Invalid value at x = %f\n", x);
    }
    return value;
}


// 外层积分
double outer_integral(double y, void* params) {
    gsl_integration_workspace* workspace = (gsl_integration_workspace*)params;
    double result, error;

    gsl_function F;
    F.function = &integrand;

    // 计算内层积分
    gsl_integration_qag(&F, -10, 10, 0, 1e-6, 1000, GSL_INTEG_GAUSS61, workspace, &result, &error);
    return result;
}

int main() {
    gsl_integration_workspace* workspace = gsl_integration_workspace_alloc(1000);
    double result, error;

    // 计算外层积分
    gsl_function F;
    F.function = &outer_integral;
    F.params = workspace;

    gsl_integration_qag(&F, -10, 10, 0, 1e-6, 1000, GSL_INTEG_GAUSS61, workspace, &result, &error);

    printf("双重积分结果: %.6f\n", result);

    gsl_integration_workspace_free(workspace);
    return 0;
}
