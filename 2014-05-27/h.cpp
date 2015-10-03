#include <cstdio>
#include <cstring>
#include <utility>
#include <queue>
#include <algorithm>
using namespace std;
int b[410],d[410][410],a[10010][3];
bool vis[410];
void dijkstra(int id,int n)
{
    memset(d[id],63,sizeof(d[id]));
    d[id][id]=0;
    priority_queue <pair <int,int> > Q;
    Q.push(make_pair(0,id));
    memset(vis,0,sizeof(vis));
    while (!Q.empty())
    {
        int x=Q.top().second;
        Q.pop();
        if (vis[x])
            continue;
        vis[x]=true;
        for (int i=b[x];i;i=a[i][2])
        {
            int y=a[i][0];
            if (d[id][x]+a[i][1]<d[id][y])
            {
                d[id][y]=d[id][x]+a[i][1];
                Q.push(make_pair(-d[id][y],y));
            }
        }
    }
}
pair <int,int> p[410];
bool check(int u,int v,int n,int len,int mid)
{
    int m=0;
    for (int i=1;i<=n;i++)
    {
        int l=max(0,mid-d[i][u]+1);
        int r=min(len,len-(mid-d[i][v])-1);
        if (l<=r)
            p[++m]=make_pair(l,r);
    }
    sort(p+1,p+m+1);
    int last=-1;
    for (int i=1;i<=m;i++)
    {
        if (p[i].first-last>1)
            return(true);
        last=max(last,p[i].second);
    }
    return(last<len);
}
int calc(int u,int v,int n,int len)
{
    int l=0,r=1000000000,ans=-1;
    while (l<=r)
    {
        int mid=l+r>>1;
        if (check(u,v,n,len,mid))
            ans=mid,r=mid-1;
        else
            l=mid+1;
    }
    return(ans);
}
int main()
{
    freopen("hunt.in","r",stdin);
    int T;
    scanf("%d",&T);
    while (T--)
    {
        int n,m;
        scanf("%d%d",&n,&m);
        memset(b,0,sizeof(b));
        for (int i=1;i<=m;i++)
        {
            int x,y,z;
            scanf("%d%d%d",&x,&y,&z);
            z<<=1;
            a[i][0]=y,a[i][1]=z,a[i][2]=b[x],b[x]=i;
            a[i+m][0]=x,a[i+m][1]=z,a[i+m][2]=b[y],b[y]=i+m;
        }
        for (int i=1;i<=n;i++)
            dijkstra(i,n);
        int ans=1<<30;
        for (int i=1;i<=n;i++)
            for (int j=b[i];j;j=a[j][2])
            {
                int x=a[j][0];
                if (i<x)
                    ans=min(ans,calc(i,x,n,a[j][1]));
            }
        printf("%d\n",ans);
    }
    return(0);
}

