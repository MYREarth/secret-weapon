#include <cstdio>
#include <utility>
#include <queue>
using namespace std;
int dep[500010],d[500010],q[500010],v[500010],b[500010],a[1000010][2];
bool vis[500010];
void bfs()
{
    int l,r;
    q[l=r=1]=1;
    vis[1]=true;
    while (l<=r)
    {
        int x=q[l++];
        for (int i=b[x];i;i=a[i][1])
        {
            int y=a[i][0];
            if (vis[y])
                continue;
            dep[y]=dep[x]+1;
            d[y]++;
            vis[y]=true;
            q[++r]=y;
        }
    }
}
int main()
{
    int n;
    scanf("%d",&n);
    for (int i=1;i<=n;i++)
        scanf("%d",&v[i]);
    for (int i=1;i<n;i++)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        a[i][0]=y,a[i][1]=b[x],b[x]=i;
        a[i+n][0]=x,a[i+n][1]=b[y],b[y]=i+n;
    }
    bfs();
    int ans=0,t=n;
    priority_queue <pair <int,int> > Q;
    Q.push(make_pair(-(dep[1]+v[1]),1));
    while (!Q.empty())
    {
        t--;
        int x=Q.top().second;
        ans=max(ans,t-Q.top().first);
        Q.pop();
        for (int i=b[x];i;i=a[i][1])
        {
            int y=a[i][0];
            if (dep[y]<dep[x])
                continue;
            if (--d[y]==0)
                Q.push(make_pair(-(dep[y]+v[y]),y));
        }
    }
    printf("%d\n",ans);
}

