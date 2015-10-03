#include <cstdio>
#include <set>
#include <algorithm>
using namespace std;
typedef long long ll;
int idx,pos[100010],to[100010],dep[100010],b[100010],a[200010][2],fa[100010][17];
void dfs(int x,int father)
{
    pos[x]=++idx;
    to[idx]=x;
    fa[x][0]=father;
    for (int i=1;i<=16;i++)
        fa[x][i]=fa[fa[x][i-1]][i-1];
    for (int i=b[x];i;i=a[i][1])
    {
        int y=a[i][0];
        if (y==father)
            continue;
        dep[y]=dep[x]+1;
        dfs(y,x);
    }
}
inline int lca(int x,int y)
{
    if (dep[x]<dep[y])
        swap(x,y);
    for (int i=16;i>=0;i--)
        if (dep[fa[x][i]]>=dep[y])
            x=fa[x][i];
    if (x==y)
        return(x);
    for (int i=16;i>=0;i--)
        if (fa[x][i]!=fa[y][i])
            x=fa[x][i],y=fa[y][i];
    return(fa[x][0]);
}
inline int dist(int x,int y)
{
    return(dep[x]+dep[y]-2*dep[lca(x,y)]);
}
int main()
{
    int n;
    scanf("%d",&n);
    for (int i=1;i<n;i++)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        a[i][0]=y,a[i][1]=b[x],b[x]=i;
        a[i+n][0]=x,a[i+n][1]=b[y],b[y]=i+n;
    }
    dep[0]=-1;
    dfs(1,0);
    set <int> S;
    S.insert(1);
    int m,last=1;
    ll sum=0;
    scanf("%d",&m);
    for (int i=1;i<=m;i++)
    {
        int x;
        scanf("%d",&x);
        set <int>::iterator p=S.lower_bound(pos[x]),q=p;
        q--;
        if (p==S.end())
        {
            last=x;
            sum+=dist(x,to[*q]);
        }
        else
        {
            sum-=dist(to[*p],to[*q]);
            sum+=dist(x,to[*p]);
            sum+=dist(x,to[*q]);
        }
        S.insert(pos[x]);
        printf("%lld%c",sum+dep[last]-dep[x],i==m?'\n':' ');
    }
    return(0);
}

