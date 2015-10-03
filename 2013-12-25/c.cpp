#include <cstdio>
#include <cstring>
#pragma comment(linker,"/STACK:16777216")
const int c[8][2]={{-1,0},{1,0},{0,-1},{0,1},{1,-1},{1,1},{-1,1},{-1,-1}};
int n,m,a[1010][1010];
bool vis[1010][1010];
int dfs(int x0,int y0)
{
    vis[x0][y0]=true;
    if (a[x0][y0]>0)
        return(1);
    int ret=0;
    for (int i=0;i<8;i++)
    {
        int x=x0+c[i][0],y=y0+c[i][1];
        if (x>0 && x<=n && y>0 && y<=m && a[x][y]!=-1 && !vis[x][y])
            ret+=dfs(x,y);
    }
    return(ret);
}
int main()
{
    int T;
    scanf("%d",&T);
    while (T--)
    {
        int K;
        scanf("%d%d%d",&n,&m,&K);
        memset(a,0,sizeof(a));
        for (int i=1;i<=K;i++)
        {
            int x,y;
            scanf("%d%d",&x,&y);
            x++,y++;
            a[x][y]=-1;
        }
        for (int i=1;i<=n;i++)
            for (int j=1;j<=m;j++)
            {
                if (a[i][j]!=-1)
                    continue;
                for (int k=0;k<8;k++)
                {
                    int x=i+c[k][0],y=j+c[k][1];
                    if (x>0 && x<=n && y>0 && y<=m && a[x][y]!=-1)
                        a[x][y]++;
                }
            }
        memset(vis,0,sizeof(vis));
        int ans=0;
        for (int i=1;i<=n;i++)
            for (int j=1;j<=m;j++)
                if (a[i][j]==0 && !vis[i][j])
                {
                    int cnt=dfs(i,j);
                    ans^=cnt%2+1;
                }
        for (int i=1;i<=n;i++)
            for (int j=1;j<=m;j++)
                if (a[i][j]>0 && !vis[i][j])
                    ans^=1;
        static int id=0;
        printf("Case #%d: %s\n",++id,ans?"Xiemao":"Fanglaoshi");
    }
    return(0);
}

