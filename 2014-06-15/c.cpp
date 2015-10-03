#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
int start[1010],dis[25010],b[25010],len[1000000],a[1000000][3];
bool in[25010];
void spfa()
{
    queue <int> Q;
    memset(dis,63,sizeof(dis));
    Q.push(1);
    dis[1]=0;
    in[1]=true;
    while (!Q.empty())
    {
        int x=Q.front();
        Q.pop();
        in[x]=false;
        for (int i=b[x];i;i=a[i][2])
        {
            int y=a[i][0];
            if (dis[x]+a[i][1]<dis[y])
            {
                dis[y]=dis[x]+a[i][1];
                if (!in[y])
                {
                    in[y]=true;
                    Q.push(y);
                }
            }
        }
    }
}
int S,T,tot;
void add(int x,int y)
{
    a[++tot][0]=y,a[tot][1]=1,a[tot][2]=b[x],b[x]=tot;
    tot++;
}
int idx,vis[25010],pre[25010],p[25010],q[25010];
bool build()
{
    int l,r;
    q[l=r=1]=S;
    idx++;
    vis[S]=idx;
    while (l<=r)
    {
        int x=q[l++];
        for (int i=b[x];i;i=a[i][2])
        {
            int y=a[i][0];
            if (vis[y]==idx || !a[i][1])
                continue;
            vis[y]=idx;
            pre[y]=x;
            p[y]=i;
            q[++r]=y;
            if (y==T)
                break;
        }
    }
    if (vis[T]!=idx)
        return(false);
    for (int i=T;i!=S;i=pre[i])
    {
        int x=p[i];
        a[x][1]--;
        a[x^1][1]++;
    }
    return(true);
}
int maxflow(int n,int m,int K,int value)
{
    S=0,T=1,tot=2*m+1;
    for (int i=1;i<=n;i++)
        for (int j=b[i];j;j=a[j][2])
        {
            int x=a[j][0];
            a[j][1]=dis[i]==dis[x]+len[j];
        }
    b[S]=0;
    for (int i=1;i<=K;i++)
        if (dis[start[i]]==value)
            add(S,start[i]);
    int ans=0;
    while (build())
        ans++;
    return(ans);
}
int main()
{
    int n,m,K;
    scanf("%d%d%d",&n,&m,&K);
    int t=1;
    for (int i=1;i<=m;i++)
    {
        int x,y,z;
        scanf("%d%d%d",&x,&y,&z);
        a[++t][0]=y,a[t][1]=z,a[t][2]=b[x],b[x]=t;
        a[++t][0]=x,a[t][1]=z,a[t][2]=b[y],b[y]=t;
        len[t-1]=len[t]=z;
    }
    spfa();
    vector <int> value;
    for (int i=1;i<=K;i++)
    {
        scanf("%d",&start[i]);
        value.push_back(dis[start[i]]);
    }
    sort(value.begin(),value.end());
    value.erase(unique(value.begin(),value.end()),value.end());
    int ans=0;
    for (int i=0;i<value.size();i++)
        ans+=maxflow(n,m,K,value[i]);
    printf("%d\n",ans);
    return(0);
}

