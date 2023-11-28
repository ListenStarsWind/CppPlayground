#include<stdio.h>
int main()
{
    int a = 0;
    int b = 0;
    while(scanf("%d %d",&a,&b)!=EOF)
    {
        if(a==b)
        {
            printf("%d=%d\n",a,b);
        }
        if(a>b)
        {
            printf("%d>%d\n",a,b);
        }
        if(a<b)
        {
            printf("%d<%d\n",a,b);
        }
    }

    return 0;
}