#include <cstdio>
#include <cstring>
#include <queue>
#include <utility>
using namespace std;
int tot,cnt[100010],b[100010],a[400010][3];
void add(int x,int y,int z)
{
    a[++tot][0]=y,a[tot][1]=z,a[tot][2]=b[x],b[x]=tot;
}
int d[100010];
bool vis[100010];
int dijkstra(int S,int T)
{
    memset(vis,0,sizeof(vis));
    memset(d,63,sizeof(d));
    priority_queue <pair <int,int> > Q;
    Q.push(make_pair(0,S));
    d[S]=0;
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
            if (d[x]+a[i][1]<d[y])
            {
                d[y]=d[x]+a[i][1];
                Q.push(make_pair(-d[y],y));
            }
        }
    }
    return(d[T]);
}
int main()
{
    int n,K,m;
    scanf("%d%d%d",&K,&n,&m);
    for (int i=1;i<=K;i++)
    {
        int x;
        scanf("%d",&x);
        cnt[x]++;
    }
    bool flag=false;
    for (int i=1;i<=n;i++)
        if (cnt[i]>1)
        {
            flag=true;
            break;
        }
    if (flag)
        printf("0\n");
    else
    {
        for (int i=1;i<=m;i++)
        {
            int x,y,z;
            scanf("%d%d%d",&x,&y,&z);
            add(x,y,z);
            add(y,x,z);
        }
        int S=n+1,T=S+1,ans=1<<30;
        for (int k=0;k<=16;k++)
        {
            b[S]=0;
            for (int i=1;i<=n;i++)
                if (a[b[i]][0]==T)
                    b[i]=a[b[i]][2];
            tot=2*m;
            for (int i=1;i<=n;i++)
            {
                if (cnt[i]==0)
                    continue;
                if (i>>k&1)
                    add(S,i,0);
                else
                    add(i,T,0);
            }
            ans=min(ans,dijkstra(S,T));
        }
        printf("%d\n",ans*3);
    }
    return(0);
}

