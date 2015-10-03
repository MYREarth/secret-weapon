#include <cstdio>
#include <cstdlib>
int a[1010];
int main()
{
    int n=1000;
    printf("%d\n",n);
    for (int i=1;i<=n;i++)
    {
        int x,y;
        if (rand()&1)
        {
            x=rand()%1000+1;
            y=rand()%1001;
        }
        else
        {
            x=rand()%1000+1;
            y=-(rand()%(a[x]+1));
        }
        printf("%d %d\n",x,y);
        a[x]+=y;
    }
    return(0);
}

