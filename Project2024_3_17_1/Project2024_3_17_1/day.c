#define _CRT_SECURE_NO_WARNINGS
int day(int m, int y)
{
	int days[] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
	int day = 0;
	day = days[m];
	if (int_leap(m, y))
		day++;
	return day;
}