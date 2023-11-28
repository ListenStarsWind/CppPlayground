#include<stdio.h>
int main()
{
    int a = 0;
    while(scanf("%d",&a)!=EOF)
    {
        while(a>0)
        {
            printf("*");
            a--;
        }
       printf("\n"); 
    }
    return 0;
}