#include <cstdio>
#include <cstring>
int d[310],q[310],b[310],a[910][3],f[310][310][310];
void topsort(int n)
{
    int l=1,r=0;
    for (int i=1;i<=n;i++)
        if (d[i]==0)
            q[++r]=i;
    while (l<=r)
    {
        int x=q[l++];
        for (int i=b[x];i;i=a[i][2])
        {
            int y=a[i][0];
            if (--d[y]==0)
                q[++r]=y;
        }
    }
}
void update(int &x,int y)
{
    if (y>x)
        x=y;
}
int main()
{
    int n,m,K;
    scanf("%d%d%d",&n,&m,&K);
    for (int i=1;i<=m;i++)
    {
        int x,y,z;
        scanf("%d%d%d",&x,&y,&z);
        d[y]++;
        a[i][0]=y,a[i][1]=z,a[i][2]=b[x],b[x]=i;
    }
    topsort(n);
    memset(f,-63,sizeof(f));
    int inf=f[0][0][0];
    for (int i=1;i<=n;i++)
        f[i][0][0]=0;
    for (int i=1;i<=n;i++)
    {
        int x=q[i];
        for (int j=0;j<=K;j++)
            for (int k=0;k<=K;k++)
            {
                if (f[x][j][k]==inf)
                    continue;
                for (int l=b[x];l;l=a[l][2])
                {
                    int y=a[l][0];
                    update(f[y][j][k],f[x][j][k]);
                    update(f[y][j+1][k],f[x][j][k]+a[l][1]);
                    update(f[y][j][k+1],f[x][j][k]-a[l][1]);
                    update(f[y][j+1][k+1],f[x][j][k]);
                }
            }
    }
    int ans=inf;
    for (int i=1;i<=n;i++)
        update(ans,f[i][K][K]);
    if (ans==inf)
        ans=-1;
    printf("%d\n",ans);
    return(0);
}

