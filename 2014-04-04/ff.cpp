#include <cstdio>
#include <cstring>
int n,ans,cnt;
bool a[10][10],f[10][10],g[10][10];
void calc()
{
    memset(f,0,sizeof(f));
    for (int i=1;i<=n;i++)
        for (int j=1;j<=n;j++)
            f[i][j]=a[i][j];
    for (int k=1;k<=n;k++)
        for (int i=1;i<=n;i++)
            for (int j=1;j<=n;j++)
                f[i][j]|=f[i][k]&f[k][j];
}
bool same()
{
    for (int i=1;i<=n;i++)
        for (int j=1;j<=n;j++)
            if (f[i][j]!=g[i][j])
                return(false);
    return(true);
}
int p[1000];
bool check()
{
    if (cnt<2*n-3)
        return(false);
    calc();
    memcpy(g,f,sizeof(f));
    for (int i=1;i<=n;i++)
        for (int j=1;j<=n;j++)
        {
            if (i!=j && !g[i][j])
                return(false);
            if (!a[i][j])
                continue;
            a[i][j]=false;
            calc();
            a[i][j]=true;
            if (same())
                return(false);
        }
    int tmp=0,hehe=0;
    for (int i=1;i<=n;i++)
    {
        int p=0;
        for (int j=1;j<=n;j++)
            if (a[i][j] && a[j][i])
            {
                tmp++;
                p++;
            }
        if (p==2)
            hehe=1;
    }
    if (tmp==4 && hehe)
        tmp=10;
    p[tmp]++;
    return(true);
}
void dfs(int x,int y)
{
    if (x==n+1)
    {
        ans+=check();
        return;
    }
    if (y==n+1)
    {
        dfs(x+1,1);
        return;
    }
    if (x==y)
    {
        dfs(x,y+1);
        return;
    }
    a[x][y]=false;
    dfs(x,y+1);
    cnt++;
    a[x][y]=true;
    dfs(x,y+1);
    cnt--;
}
int main()
{
    scanf("%d",&n);
    dfs(1,1);
    for (int i=0;i<=n*n;i++)
        if (p[i])
            printf("%d %d\n",i,p[i]);
    printf("%d\n",ans);
    return(0);
}

