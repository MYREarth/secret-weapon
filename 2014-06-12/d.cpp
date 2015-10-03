#include <cstdio>
#include <cstring>
#include <algorithm>
#define y0 __y0__
#define y1 __y1__
using namespace std;
char a[1010][1010];
int tot,vis[1010][1010];
void fill(int x0,int y0,int x1,int y1,int value)
{
    for (int i=x0;i<=x1;i++)
        for (int j=y0;j<=y1;j++)
            vis[i][j]=value;
}
int x0[1000010],y0[1000010],x1[1000010],y1[1000010];
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    for (int i=1;i<=n;i++)
        scanf("%s",a[i]+1);
    int prev=1;
    for (int i=1;i<=n;i++)
    {
        bool flag=false;
        int pos=1;
        for (int j=1;j<=n;j++)
            if (a[i][j]=='x')
            {
                flag=true;
                fill(prev,pos,i,j,++tot);
                pos=j+1;
                if (tot==m)
                    goto out;
            }
        if (flag)
            prev=i+1;
    }
out:
    for (int i=1;i<=n;i++)
        for (int j=1;j<=n;j++)
            if (!vis[i][j] && j>1 && vis[i][j-1])
                vis[i][j]=vis[i][j-1];
    for (int i=1;i<=n;i++)
        for (int j=1;j<=n;j++)
            if (!vis[i][j])
                vis[i][j]=vis[i-1][j];
    memset(x0,63,sizeof(x0));
    memset(y0,63,sizeof(y0));
    for (int i=1;i<=n;i++)
        for (int j=1;j<=n;j++)
        {
            int t=vis[i][j];
            x0[t]=min(x0[t],j-1);
            y0[t]=min(y0[t],n-i);
            x1[t]=max(x1[t],j);
            y1[t]=max(y1[t],n-i+1);
        }
    for (int i=1;i<=m;i++)
        printf("%d %d %d %d\n",x0[i],y0[i],x1[i],y1[i]);
    return(0);
}

