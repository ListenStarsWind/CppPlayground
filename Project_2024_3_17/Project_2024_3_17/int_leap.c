#define _CRT_SECURE_NO_WARNINGS
int int_leap(int m, int y)
{
	if (((y % 4 == 0) && (y % 100 != 0) || (y % 400 == 0)) && (m == 2))
		return 1;
	else
		return 0;
}