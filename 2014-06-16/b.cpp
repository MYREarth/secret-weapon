#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
struct edge
{
    int x,y,len;
};
inline bool operator <(const edge &a,const edge &b)
{
    return(a.len>b.len);
}
edge e[500010];
int f[200010];
int find(int x)
{
    if (x!=f[x])
        f[x]=find(f[x]);
    return(f[x]);
}
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    ll ans=0;
    for (int i=1;i<=m;i++)
    {
        scanf("%d%d%d",&e[i].x,&e[i].y,&e[i].len);
        ans+=e[i].len;
    }
    sort(e+1,e+m+1);
    for (int i=1;i<=n;i++)
        f[i]=i;
    for (int i=1;i<=m;i++)
    {
        if (e[i].len<=0)
            break;
        int x=find(e[i].x),y=find(e[i].y);
        if (x==y)
            continue;
        f[x]=y;
        ans-=e[i].len;
    }
    printf("%lld\n",ans);
    return(0);
}

