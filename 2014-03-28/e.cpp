#include <cstdio>
const int c[4][2]={{-1,0},{1,0},{0,-1},{0,1}};
char a[30][30];
bool vis[30][30];
int n,m,tot,fa[410];
void dfs(int x0,int y0,int father)
{
    vis[x0][y0]=true;
    if (a[x0][y0]=='O')
    {
        fa[++tot]=father;
        father=tot;
    }
    for (int i=0;i<4;i++)
    {
        if (a[x0][y0]=='-' && i<=1)
            continue;
        if (a[x0][y0]=='|' && i>=2)
            continue;
        int x=x0+c[i][0],y=y0+c[i][1];
        if (x>0 && x<=n && y>0 && y<=m && !vis[x][y] && a[x][y]!='.')
            dfs(x,y,father);
    }
}
int main()
{
    freopen("picture.in","r",stdin);
    freopen("picture.out","w",stdout);
    scanf("%d%d",&n,&m);
    for (int i=1;i<=n;i++)
        scanf("%s",a[i]+1);
    for (int i=1;i<=n;i++)
        for (int j=1;j<=m;j++)
            if (a[i][j]=='O')
            {
                dfs(i,j,0);
                goto out;
            }
out:
    printf("%d\n",tot);
    for (int i=2;i<=tot;i++)
        printf("%d %d\n",fa[i],i);
    return(0);
}

