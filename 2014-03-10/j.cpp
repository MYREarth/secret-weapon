#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int N=100010;
int idx,up[N],Log[N],low[N],dfn[N],dep[N],p[N],b[N],a[N*2][2],fa[N][17];
void dfs(int x)
{
    for (int i=1;i<=Log[dep[x]];i++)
        fa[x][i]=fa[fa[x][i-1]][i-1];
    dfn[x]=low[x]=++idx;
    p[idx]=x;
    for (int i=b[x];i;i=a[i][1])
    {
        int y=a[i][0];
        if (dfn[y])
            continue;
        dep[y]=dep[x]+1;
        fa[y][0]=x;
        up[y]=i;
        dfs(y);
    }
}
int lca(int x,int y)
{
    if (dep[x]<dep[y])
        swap(x,y);
    for (int i=Log[dep[x]];i>=0;i--)
        if (dep[fa[x][i]]>=dep[y])
            x=fa[x][i];
    if (x==y)
        return(x);
    for (int i=Log[dep[x]];i>=0;i--)
        if (fa[x][i]!=fa[y][i])
            x=fa[x][i],y=fa[y][i];
    return(fa[x][0]);
}
int rb[N],ra[N*2][2],f[N][17];
int calc(int x,int len)
{
    if (len==1)
        return(low[x]);
    int t=Log[len];
    if (len==1<<t)
    {
        int &ret=f[x][t];
        if (ret==0)
            ret=min(calc(x,len>>1),calc(fa[x][t-1],len>>1));
        return(ret);
    }
    return(min(calc(x,1<<t),calc(fa[x][t],len-(1<<t))));
}
bool ans[N*2];
int main()
{
    freopen("redundant.in","r",stdin);
    freopen("redundant.out","w",stdout);
    int n,m,root;
    scanf("%d%d%d",&n,&m,&root);
    Log[1]=0;
    for (int i=2;i<=n;i++)
        Log[i]=Log[i-1]+((i&i-1)==0);
    for (int i=1;i<=m;i++)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        a[i][0]=y,a[i][1]=b[x],b[x]=i;
        ra[i][0]=x,ra[i][1]=rb[y],rb[y]=i;
    }
    dep[root]=1;
    dfs(root);
    memset(ans,true,sizeof(ans));
    for (int i=idx;i;i--)
    {
        int x=p[i];
        for (int j=rb[x];j;j=ra[j][1])
        {
            int y=ra[j][0];
            if (y==fa[x][0] || !dfn[y])
                continue;
            int t=lca(x,y);
            if (t==y)
                low[x]=min(low[x],dfn[y]);
            else if (t==x)
                low[x]=min(low[x],calc(y,dep[y]-dep[x]));
            else
                low[x]=min(low[x],min(dfn[t],calc(y,dep[y]-dep[t])));
        }
        if (low[x]==dfn[x])
            ans[up[x]]=false;
    }
    printf("%d\n",count(ans+1,ans+m+1,true));
    bool first=true;
    for (int i=1;i<=m;i++)
    {
        if (!ans[i])
            continue;
        if (!first)
            printf(" ");
        first=false;
        printf("%d",i);
    }
    printf("\n");
    return(0);
}

