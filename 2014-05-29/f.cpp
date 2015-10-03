#include <cstdio>
#include <vector>
using namespace std;
const int limit=450;
int v[100010],big[100010],d[100010],b[100010],a[200010][2],f[limit][100010];
vector <int> adj[limit];
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    for (int i=1;i<=n;i++)
        scanf("%d",&v[i]);
    int ans=0;
    for (int i=1;i<=m;i++)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        d[x]++,d[y]++;
        ans+=v[x]!=v[y];
        a[i][0]=y,a[i][1]=b[x],b[x]=i;
        a[i+m][0]=x,a[i+m][1]=b[y],b[y]=i+m;
    }
    int tot=0;
    for (int i=1;i<=n;i++)
        if (d[i]>=limit)
            big[i]=++tot;
    for (int i=1;i<=n;i++)
    {
        if (!big[i])
            continue;
        for (int j=b[i];j;j=a[j][1])
        {
            int x=a[j][0];
            f[big[i]][v[x]]++;
            if (big[x])
                adj[big[i]].push_back(big[x]);
        }
    }
    int Q;
    scanf("%d",&Q);
    while (Q--)
    {
        int x,t;
        scanf("%d%d",&x,&t);
        if (big[x])
        {
            ans-=d[x]-f[big[x]][v[x]];
            ans+=d[x]-f[big[x]][t];
            for (int i=0;i<adj[big[x]].size();i++)
            {
                int y=adj[big[x]][i];
                f[y][v[x]]--;
                f[y][t]++;
            }
        }
        else
            for (int i=b[x];i;i=a[i][1])
            {
                int y=a[i][0];
                ans-=v[x]!=v[y];
                ans+=t!=v[y];
                if (big[y])
                {
                    f[big[y]][v[x]]--;
                    f[big[y]][t]++;
                }
            }
        v[x]=t;
        printf("%d\n",ans);
    }
    return(0);
}

