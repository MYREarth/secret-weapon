#include <cstdio>
#include <cstring>
const int c[4][2]={{-1,0},{1,0},{0,-1},{0,1}};
int W,H,x1[80010],x2[80010],y1[80010],y2[80010],ans[80010],f[210][210][2];
bool vis[210][210],a[210][210][4];
void dfs(int x0,int y0,int xx,int yy)
{
    vis[x0][y0]=true;
    f[x0][y0][0]=xx;
    f[x0][y0][1]=yy;
    for (int i=0;i<4;i++)
    {
        int x=x0+c[i][0],y=y0+c[i][1];
        if (x<=0 || x>W || y<=0 || y>H || !a[x0][y0][i] || vis[x][y])
            continue;
        dfs(x,y,xx,yy);
    }
}
void find(int &x,int &y)
{
    if (f[x][y][0]==x && f[x][y][1]==y)
        return;
    find(f[x][y][0],f[x][y][1]);
    int xx=x,yy=y;
    x=f[xx][yy][0],y=f[xx][yy][1];
}
void Union(int x0,int y0,int x1,int y1,int &tot)
{
    find(x0,y0);
    find(x1,y1);
    if (x0==x1 && y0==y1)
        return;
    f[x0][y0][0]=x1;
    f[x0][y0][1]=y1;
    tot--;
}
int main()
{
    int n;
    scanf("%d%d%d",&W,&H,&n);
    memset(a,true,sizeof(a));
    for (int i=1;i<=n;i++)
    {
        scanf("%d%d%d%d",&x1[i],&y1[i],&x2[i],&y2[i]);
        if (x1[i]==x2[i])
            for (int j=y1[i]+1;j<=y2[i];j++)
            {
                a[x1[i]][j][1]=false;
                a[x1[i]+1][j][0]=false;
            }
        else
            for (int j=x1[i]+1;j<=x2[i];j++)
            {
                a[j][y1[i]][3]=false;
                a[j][y1[i]+1][2]=false;
            }
    }
    int tot=0;
    for (int i=1;i<=W;i++)
        for (int j=1;j<=H;j++)
            if (!vis[i][j])
            {
                tot++;
                dfs(i,j,i,j);
            }
    for (int i=n;i;i--)
    {
        ans[i]=tot;
        if (x1[i]==x2[i])
            for (int j=y1[i]+1;j<=y2[i];j++)
                Union(x1[i],j,x1[i]+1,j,tot);
        else
            for (int j=x1[i]+1;j<=x2[i];j++)
                Union(j,y1[i],j,y1[i]+1,tot);
    }
    for (int i=1;i<=n;i++)
        printf("%d\n",ans[i]);
    return(0);
}

