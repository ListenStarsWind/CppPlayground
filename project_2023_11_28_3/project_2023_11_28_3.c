#include<stdio.h>
int main()
{
    char arr[]="YES";
    char brr[]="NO";
    char *p;
    char *q;
    p = arr;
    q = brr;
    int a = 0;
    scanf("%d",&a);
    if(a%5 == 0)
    {
        printf("%s\n",p);
    }
    else
    {
        printf("%s\n",q);
    }
    return 0;
}