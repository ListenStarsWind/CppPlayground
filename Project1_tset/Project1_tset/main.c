#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
int main()
{
    int a = 0;
    while (scanf("%d", &a) == 1) {
        if (a >= 140) {
            char arr[] = "Genius";
            char* p;
            p = arr;
            printf("%s", p);
        }
    }

    return 0;
}