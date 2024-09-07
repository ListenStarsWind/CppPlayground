#pragma once

#include<stdbool.h>

typedef struct SubmarineSpecifications
{
	double _length;
	double _width;
	double _height;
}SubmarineSpecifications, * p_SubmarineSpecifications;

typedef struct BombRelatedInformation
{
	double _kill_radius;
	double _detonation_depth;
}BombRelatedInformation, * p_BombRelatedInformation;

typedef struct ObservationCoordinate
{
	double _x;
	double _y;
	double _z;
}ObservationCoordinate, * p_ObservationCoordinate;

typedef struct object
{
	p_SubmarineSpecifications _submarine;
	p_BombRelatedInformation _bombshell;
	double sigma;
}object, * p_object;

