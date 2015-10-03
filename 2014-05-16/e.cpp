#include <cstdio>
int idx,vis[20],dep[20],b[20],a[20][20],ans[20][20],e[100010][2],pre[65540][20];
bool ok[65540],f[65540][20];
void dfs(int tot,int x)
{
    vis[x]=idx;
    for (int i=1;i<=tot;i++)
    {
        int y=b[i];
        if (a[x][y] && vis[y]!=idx)
            dfs(tot,y);
    }
}
bool calc(int n,int state)
{
    int tot=0;
    for (int i=1;i<=n;i++)
        if (state>>i-1&1)
            b[++tot]=i;
    idx++;
    dfs(tot,b[1]);
    for (int i=1;i<=tot;i++)
        if (vis[b[i]]!=idx)
            return(false);
    for (int i=1;i<=tot;i++)
        for (int j=i+1;j<=tot;j++)
        {
            int x=b[i],y=b[j];
            if (a[x][y]!=1)
                continue;
            a[x][y]=a[y][x]=0;
            idx++;
            dfs(tot,b[1]);
            a[x][y]=a[y][x]=1;
            for (int k=1;k<=tot;k++)
                if (vis[b[k]]!=idx)
                    return(false);
        }
    return(true);
}
void tarjan(int x,int tot)
{
    vis[x]=idx;
    for (int i=1;i<=tot;i++)
    {
        int y=b[i];
        if (!a[x][y])
            continue;
        if (vis[y]!=idx)
        {
            a[x][y]--;
            a[y][x]--;
            ans[x][y]++;
            tarjan(y,tot);
        }
        else
        {
            ans[x][y]=a[x][y];
            a[x][y]=a[y][x]=0;
        }
    }
}
void getans(int state,int p,int n)
{
    int tot=0;
    for (int i=1;i<=n;i++)
        if (state>>i-1&1)
        {
            b[++tot]=i;
            dep[i]=p;
        }
    idx++;
    tarjan(b[1],tot);
}
void print(int x,int y,int n)
{
    if (x==0 && y==0)
        return;
    int z=pre[x][y];
    getans(z,y,n);
    print(x^z,y-1,n);
}
int main()
{
    freopen("scc.in","r",stdin);
    freopen("scc.out","w",stdout);
    int n,m,K;
    scanf("%d%d%d",&n,&m,&K);
    for (int i=1;i<=m;i++)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        e[i][0]=x,e[i][1]=y;
        a[x][y]++;
        a[y][x]++;
    }
    for (int i=1;i<1<<n;i++)
        ok[i]=calc(n,i);
    f[0][0]=true;
    for (int i=0;i<1<<n;i++)
        for (int j=0;j<K;j++)
            for (int k=i;k;k=i&k-1)
                if (ok[k] && f[i^k][j])
                {
                    f[i][j+1]=true;
                    pre[i][j+1]=k;
                }
    if (!f[(1<<n)-1][K])
        printf("NO\n");
    else
    {
        printf("YES\n");
        print((1<<n)-1,K,n);
        for (int i=1;i<=m;i++)
        {
            int x=e[i][0],y=e[i][1];
            if (dep[x]!=dep[y])
            {
                if (dep[x]<dep[y])
                    printf("%d %d\n",x,y);
                else
                    printf("%d %d\n",y,x);
                continue;
            }
            if (ans[x][y])
            {
                printf("%d %d\n",x,y);
                ans[x][y]--;
            }
            else
            {
                printf("%d %d\n",y,x);
                ans[y][x]--;
            }
        }
    }
    return(0);
}

