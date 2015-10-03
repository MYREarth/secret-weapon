#include <cstdio>
int main()
{
    int n=200,m=10000,K=20;
    printf("%d %d %d\n",n,m,K);
    for (int i=1;i<=100;i++)
        for (int j=101;j<=200;j++)
            printf("%d %d\n",i,j);
    return(0);
}

