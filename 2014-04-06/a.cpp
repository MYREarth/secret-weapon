#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int v[110],a[110][110];
int main()
{
    while (1)
    {
        int n,m;
        scanf("%d%d",&n,&m);
        if (n==0 && m==0)
            break;
        memset(a,63,sizeof(a));
        for (int i=1;i<=n;i++)
        {
            scanf("%d",&v[i]);
            a[i][i]=0;
        }
        for (int i=1;i<=m;i++)
        {
            int x,y;
            scanf("%d%d",&x,&y);
            a[x][y]=a[y][x]=v[x]!=v[y];
        }
        for (int k=1;k<=n;k++)
            for (int i=1;i<=n;i++)
                for (int j=1;j<=n;j++)
                    a[i][j]=min(a[i][j],a[i][k]+a[k][j]);
        int ans=1<<30;
        for (int i=1;i<=n;i++)
            ans=min(ans,*max_element(a[i]+1,a[i]+n+1));
        printf("%d\n",ans);
    }
    return(0);
}

