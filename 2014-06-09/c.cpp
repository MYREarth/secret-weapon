#include <cstdio>
#include <cstring>
#include <bitset>
#include <algorithm>
using namespace std;
const int inf=1<<30;
int S,T,tot=1,b[1010],a[2600000][3];
void add(int x,int y,int z)
{
    a[++tot][0]=y,a[tot][1]=z,a[tot][2]=b[x],b[x]=tot;
    a[++tot][0]=x,a[tot][1]=0,a[tot][2]=b[y],b[y]=tot;
}
int q[1010],d[1010];
bool build()
{
    int l,r;
    q[l=r=1]=S;
    memset(d,0,sizeof(d));
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
bitset <1010> p[1010];
bool origin[1010];
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    S=m+1,T=S+1;
    for (int i=1;i<=m;i++)
    {
        int K;
        scanf("%d",&K);
        for (int j=1;j<=K;j++)
        {
            int x;
            scanf("%d",&x);
            p[i].set(x);
        }
        char buf[10];
        scanf("%s",buf);
        if (buf[1]=='i')
            add(S,i,1);
        else
            add(i,T,1);
        origin[i]=buf[1]=='i';
    }
    for (int i=1;i<=m;i++)
        for (int j=i+1;j<=m;j++)
        {
            p[0]=p[i]&p[j];
            if (p[0]==p[i])
                add(j,i,inf);
            if (p[0]==p[j])
                add(i,j,inf);
        }
    int ans=0;
    while (build())
        ans+=dinic(S,inf);
    printf("%d\n",ans);
    vector <int> tmp;
    for (int i=1;i<=m;i++)
        if (origin[i]!=(d[i]>0))
            tmp.push_back(i);
    for (int i=0;i<tmp.size();i++)
        printf("%d%c",tmp[i],i+1==tmp.size()?'\n':' ');
    return(0);
}

