#pragma once

#include<stdbool.h>
#include<math.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_cdf.h>

typedef struct SubmarineSpecifications
{
	float _length;
	float _width;
	float _height;
}SubmarineSpecifications, * p_SubmarineSpecifications;

typedef struct BombRelatedInformation
{
	float _kill_radius;
	float _detonation_depth;
}BombRelatedInformation, * p_BombRelatedInformation;

typedef struct coordinates
{
	float _x;
	float _y;
	float _z;
}coordinates, * p_coordinates;

typedef struct FirstQuestion
{
	p_SubmarineSpecifications submarine;
	p_BombRelatedInformation bombshell;
	double sigma;
}FirstQuestion, * p_FirstQuestion;

bool IsHits(p_FirstQuestion pVal1, p_coordinates pVal2);

double HitRate(p_FirstQuestion pVal1, p_coordinates pVal2);

double* linspace(double start, double stop, int size);

p_FirstQuestion topicInit(void);

void prescription(void);