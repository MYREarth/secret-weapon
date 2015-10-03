#include <cstdio>
typedef long long ll;
int dep[100010],b[100010],cnt[100010],a[200010][2],fa[100010][17];
ll f[100010];
void dfs(int x)
{
    for (int i=1;i<=16;i++)
        fa[x][i]=fa[fa[x][i-1]][i-1];
    cnt[x]=f[x]=1;
    for (int i=b[x];i;i=a[i][1])
    {
        int y=a[i][0];
        if (y==fa[x][0])
            continue;
        dep[y]=dep[x]+1;
        fa[y][0]=x;
        dfs(y);
        f[x]+=ll(cnt[x])*cnt[y];
        cnt[x]+=cnt[y];
    }
}
ll s[100010];
void dp(int x)
{
    s[x]+=f[x];
    for (int i=b[x];i;i=a[i][1])
    {
        int y=a[i][0];
        if (y==fa[x][0])
            continue;
        s[y]+=s[x];
        dp(y);
    }
}
int lca(int x,int y)
{
    if (dep[x]<dep[y])
        return(lca(y,x));
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
int main()
{
    int n,Q;
    scanf("%d%d",&n,&Q);
    for (int i=1;i<n;i++)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        a[i][0]=y,a[i][1]=b[x],b[x]=i;
        a[i+n][0]=x,a[i+n][1]=b[y],b[y]=i+n;
    }
    dep[1]=1;
    dfs(1);
    dp(1);
    ll ans=0;
    for (int i=1;i<=n;i++)
        ans+=f[i];
    while (Q--)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        int t=lca(x,y);
        ll tmp=s[x]+s[y]-2*s[t]+f[t]+ll(cnt[t])*(n-cnt[t]);
        printf("%lld\n",ans-tmp);
    }
    return(0);
}

