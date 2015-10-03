#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int inf=1<<30;
int SS,TT,tot,deg[210],b[210],id[10010],e[10010][2],a[1000000][3];
bool use[10010];
void add(int x,int y,int z)
{
    a[++tot][0]=y,a[tot][1]=z,a[tot][2]=b[x],b[x]=tot;
    a[++tot][0]=x,a[tot][1]=0,a[tot][2]=b[y],b[y]=tot;
}
void add(int x,int y,int l,int u)
{
    add(SS,y,l);
    add(x,TT,l);
    add(x,y,u-l);
}
int d[210],q[210];
bool build(int S,int T)
{
    memset(d,0,sizeof(d));
    int l,r;
    q[l=r=1]=S;
    d[S]=1;
    while (l<=r)
    {
        int x=q[l++];
        for (int i=b[x];i;i=a[i][2])
        {
            int y=a[i][0];
            if (d[y] || !a[i][1])
                continue;
            d[y]=d[x]+1;
            q[++r]=y;
            if (y==T)
                return(true);
        }
    }
    return(false);
}
int dinic(int x,int T,int flow)
{
    if (x==T)
        return(flow);
    int k=flow;
    for (int i=b[x];i;i=a[i][2])
    {
        int y=a[i][0];
        if (d[y]!=d[x]+1 || !a[i][1])
            continue;
        int t=dinic(y,T,min(k,a[i][1]));
        k-=t;
        a[i][1]-=t;
        a[i^1][1]+=t;
        if (k==0)
            break;
    }
    if (k==flow)
        d[x]=-1;
    return(flow-k);
}
int main()
{
    int n,m,K;
    scanf("%d%d%d",&n,&m,&K);
    int S=n+1,T=S+1;
    SS=T+1,TT=SS+1;
    tot=1;
    for (int i=1;i<=n;i++)
        if (i<=n/2)
            add(S,i,K);
        else
            add(i,T,K);
    for (int i=1;i<=m;i++)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        id[i]=tot+1;
        e[i][0]=x,e[i][1]=y;
        add(x,y,1);
    }
    int ans=0;
    while (build(S,T))
        ans+=dinic(S,T,inf);
    printf("%d\n",ans);
    for (int i=1;i<=m;i++)
        use[i]=a[id[i]][1]==0;
    for (int i=1;i<=n;i++)
        if (i<=n/2)
            for (int j=b[i];j;j=a[j][2])
                deg[i]+=a[j][1]==0;
        else
            for (int j=b[i];j;j=a[j][2])
                deg[i]+=a[j^1][1]==0;
    for (int i=K;i;i--)
    {
        memset(b,0,sizeof(b));
        tot=1;
        for (int j=1;j<=n;j++)
            if (j<=n/2)
                deg[j]==i?add(S,j,1,1):add(S,j,1);
            else
                deg[j]==i?add(j,T,1,1):add(j,T,1);
        for (int j=1;j<=m;j++)
            if (use[j])
            {
                id[j]=tot+1;
                add(e[j][0],e[j][1],1);
            }
        add(T,S,inf);
        while (build(SS,TT))
            dinic(SS,TT,inf);
        for (int j=1;j<=m;j++)
            if (use[j] && a[id[j]][1]==0)
            {
                printf("%d %d\n",j,i);
                deg[e[j][0]]--;
                deg[e[j][1]]--;
                use[j]=false;
            }
    }
    return(0);
}

