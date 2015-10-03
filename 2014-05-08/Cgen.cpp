#include <cstdio>
#include <cstdlib>
int f[100010];
int main()
{
    int n=100;
    printf("%d\n",n);
    for (int i=2;i<=n;i++)
    {
        f[i]=rand()%(i-1)+1;
        printf("%d ",f[i]);
    }
    printf("\n");
    int Q=100;
    printf("%d\n",Q);
    while (Q)
        if (rand()&1)
        {
            printf("Q %d %d\n",rand()%n+1,rand()%n+1);
            Q--;
        }
        else
        {
            int u=rand()%n+1;
            if (f[u]==0)
                continue;
            int v=rand()%f[u]+1;
            printf("C %d %d\n",u,v);
            Q--;
        }
    return(0);
}

