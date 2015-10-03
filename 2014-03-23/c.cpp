#include <cstdio>
typedef long long ll;
int a[100];
int main()
{
    ll n;
    scanf("%lld",&n);
    int m=0;
    while (n)
    {
        a[++m]=n&1;
        n>>=1;
    }
    for (int i=1;i<=m;i++)
    {
        if (a[i]==0)
            continue;
        int p=m;
        for (int j=i;j<=m;j++)
            if (a[j]==0)
            {
                p=j-1;
                break;
            }
        if (i==p)
            continue;
        for (int j=i+1;j<=p;j++)
            a[j]=0;
        a[i]=-1;
        a[p+1]=1;
        if (p==m)
            m++;
    }
    for (int i=m;i;i--)
        printf("%d%c",a[i],i==1?'\n':' ');
    return(0);
}

