#pragma once

#include <gsl/gsl_integration.h>
#include <gsl/gsl_randist.h>
#include <stdio.h>
#include <math.h>
#define M_PI 3.14159265358979323846
#define kill_radius 20
#define statistics_Z 40
#define l = 120;
#define H_0 = 150;


double Points_for_case_I();

double Points_for_case_II();


// 标准正态分布的累积分布函数
double normal_cdf(double x);

double Points_for_case_end();


