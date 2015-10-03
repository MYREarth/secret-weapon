#include <cstdio>
#include <bitset>
using namespace std;
const int limit=400;
int vis[300010],big[300010],b[300010],d[300010],a[600010][2];
bitset <1510> adj[1510];
int main()
{
    freopen("cycles.in","r",stdin);
    freopen("cycles.out","w",stdout);
    int n,m;
    scanf("%d%d",&n,&m);
    for (int i=1;i<=m;i++)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        a[i][0]=y,a[i][1]=b[x],b[x]=i;
        a[i+m][0]=x,a[i+m][1]=b[y],b[y]=i+m;
        d[x]++,d[y]++;
    }
    int tot=0;
    for (int i=1;i<=n;i++)
        if (d[i]>=limit)
            big[i]=++tot;
    int ans=0;
    for (int i=1;i<=n;i++)
    {
        for (int j=b[i];j;j=a[j][1])
        {
            int x=a[j][0];
            vis[x]=i;
        }
        for (int j=b[i];j;j=a[j][1])
        {
            int x=a[j][0];
            if (big[x] || !big[i] && i<=x)
                continue;
            for (int k=b[x];k;k=a[k][1])
            {
                int y=a[k][0];
                if (y<=i || !big[y] && y<=x)
                    continue;
                ans+=vis[y]==i;
            }
        }
    }
    for (int i=1;i<=n;i++)
    {
        if (!big[i])
            continue;
        for (int j=b[i];j;j=a[j][1])
        {
            int x=a[j][0];
            if (big[x])
            {
                adj[big[i]].set(big[x]);
                adj[big[x]].set(big[i]);
            }
        }
    }
    int sum=0;
    for (int i=1;i<=tot;i++)
        for (int j=i+1;j<=tot;j++)
            if (adj[i].test(j))
                sum+=(adj[i]&adj[j]).count();
    printf("%d\n",ans+sum/3);
    return(0);
}

