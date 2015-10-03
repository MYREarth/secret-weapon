#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
int tot=1,S,T,q[110],d[110],b[110],a[1000000][3];
void add(int x,int y,int z)
{
    a[++tot][0]=y,a[tot][1]=z,a[tot][2]=b[x],b[x]=tot;
    a[++tot][0]=x,a[tot][1]=z,a[tot][2]=b[y],b[y]=tot;
}
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
int main()
{
    freopen("highways.in","r",stdin);
    freopen("highways.out","w",stdout);
    int n,m,K;
    scanf("%d%d%d",&n,&m,&K);
    for (int i=1;i<=m;i++)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        add(x,y,1);
        d[x]++,d[y]++;
    }
    S=n+1,T=S+1;
    for (int i=1;i<=n;i++)
    {
        add(S,i,2*K);
        add(i,T,d[i]);
    }
    while (build())
        dinic(S,1<<30);
    vector <int> ans;
    for (int i=1;i<=n;i++)
        if (!d[i])
            ans.push_back(i);
    if (ans.empty())
        printf("OK\n");
    else
    {
        printf("Redundant\n%d\n",ans.size());
        for (int i=0;i<ans.size();i++)
            printf("%d%c",ans[i],i+1==ans.size()?'\n':' ');
    }
    return(0);
}

