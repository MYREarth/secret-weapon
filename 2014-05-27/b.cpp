#include <cstdio>
int a[1000010];
int main()
{
    freopen("business.in","r",stdin);
    int T;
    scanf("%d",&T);
    while (T--)
    {
        int n,m;
        scanf("%d%d",&n,&m);
        for (int i=1;i<=n;i++)
        {
            int x;
            scanf("%d",&x);
            a[x]=i;
        }
        int now=1;
        for (int i=1;i<=m;i++)
        {
            int x;
            scanf("%d",&x);
            x=a[x];
            int ans=x-now;
            if (ans<0)
                ans+=n;
            now=x;
            printf("%d%c",ans,i==m?'\n':' ');
        }
    }
    return(0);
}

