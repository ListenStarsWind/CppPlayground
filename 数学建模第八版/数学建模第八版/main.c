#include"configure.h"

int main()
{
	double point1 = Points_for_case_I();
	double point2 = Points_for_case_II();
	double point3 = Points_for_case_end();
	double ret = point1 * point2 * (1.0 / statistics_Z) * point3;
	printf("%f\n",ret);
	return 0;
}