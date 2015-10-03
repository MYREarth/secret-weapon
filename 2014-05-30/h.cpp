#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
int S,T,tot,b[110],a[1000000][3];
void add(int x,int y,int z)
{
    a[++tot][0]=y,a[tot][1]=z,a[tot][2]=b[x],b[x]=tot;
    a[++tot][0]=x,a[tot][1]=0,a[tot][2]=b[y],b[y]=tot;
}
int d[110],q[110];
bool build()
{
    int l,r;
    memset(d,0,sizeof(d));
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
int dinic(int x,int flow)
{
    if (x==T)
        return(flow);
    int k=flow;
    for (int i=b[x];i;i=a[i][2])
    {
        int y=a[i][0];
        if (d[y]!=d[x]+1 || !a[i][1])
            continue;
        int t=dinic(y,min(k,a[i][1]));
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
int pos[110];
int main()
{
    freopen("hentium.in","r",stdin);
    freopen("hentium.out","w",stdout);
    while (1)
    {
        int n;
        scanf("%d",&n);
        if (n==0)
            break;
        memset(b,0,sizeof(b));
        tot=1;
        S=n+1,T=S+1;
        for (int i=1;i<=n;i++)
        {
            int x,y;
            scanf("%d%d",&x,&y);
            add(S,i,x);
            add(i,T,y);
        }
        for (int i=1;i<=n;i++)
            for (int j=1;j<=n;j++)
            {
                int x;
                scanf("%d",&x);
                add(i,j,x);
            }
        ll ans=0;
        while (build())
            ans+=dinic(S,1<<30);
        printf("%lld\n",ans);
        for (int i=b[S];i;i=a[i][2])
        {
            int y=a[i][0];
            pos[y]=1+(d[y]>0);
        }
        for (int i=1;i<=n;i++)
            printf("%d%c",pos[i],i==n?'\n':' ');
    }
    return(0);
}

