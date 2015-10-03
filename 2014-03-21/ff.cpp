#include <cstdio>
#include <algorithm>
using namespace std;
int n=100,m,f[10010],a[10010][10],lq[100010],e[100010][3];
bool vis[10010];
int pos(int x,int y)
{
    return((x-1)*100+y);
}
int find(int x)
{
    if (x!=f[x])
        f[x]=find(f[x]);
    return(f[x]);
}
int dfs(int x)
{
    int ret=0;
    vis[x]=true;
    for (int i=1;i<=a[x][0];i++)
    {
        int y=a[x][i];
        if (!vis[y])
            ret=max(ret,dfs(y)+1);
    }
    return(ret);
}
void init()
{
    m=0;
    for (int i=1;i<=n;i++)
        for (int j=1;j<=n;j++)
        {
            if (i<n)
                e[++m][0]=pos(i,j),e[m][1]=pos(i+1,j),e[m][2]=0;
            if (j<n)
                e[++m][0]=pos(i,j),e[m][1]=pos(i,j+1),e[m][2]=0;
        }
    for (int i=1;i<=n*n;i++)
    {
        vis[i]=false;
        f[i]=i;
        a[i][0]=0;
    }
}
int getans()
{
    for (int i=1;i<=m;i++)
    {
        if (!e[i][2])
            continue;
        int x=e[i][0],y=e[i][1];
        a[x][++a[x][0]]=y;
        a[y][++a[y][0]]=x;
    }
    return(dfs(1));
}
int kruskal()
{
    init();
    for (int i=1;i<n*n;i++)
    {
        int tot=0;
        for (int j=1;j<=m;j++)
            if (find(e[j][0])!=find(e[j][1]))
                lq[++tot]=j;
        int x=lq[rand()%tot+1];
        e[x][2]=1;
        f[find(e[x][0])]=find(e[x][1]);
    }
    return(getans());
}
int prim()
{
    init();
    for (int i=1;i<n*n;i++)
    {
        int tot=0;
        for (int j=1;j<=m;j++)
        {
            int x=find(e[j][0]),y=find(e[j][1]),z=find(1);
            if (x==z && y!=z || x!=z && y==z)
                lq[++tot]=j;
        }
        int x=lq[rand()%tot+1];
        e[x][2]=1;
        f[find(e[x][0])]=find(e[x][1]);
    }
    return(getans());
}
int main()
{
    for (int i=1;i<=10;i++)
        printf("%d\n",kruskal());
    printf("==============================\n");
    for (int i=1;i<=10;i++)
        printf("%d\n",prim());
    return(0);
}

