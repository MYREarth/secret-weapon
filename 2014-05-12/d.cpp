#include <cstdio>
#include <cstring>
#include <queue>
#include <utility>
#include <algorithm>
using namespace std;
const int c[4][2]={{-1,0},{1,0},{0,-1},{0,1}};
char a[60][60];
int n,m,inf,f[260][60][60];
inline int cost(int x,int y)
{
    if (x<=0 || x>n || y<=0 || y>m || a[x][y]=='R')
        return(-1);
    if (a[x][y]=='S')
        return(1);
    else if (a[x][y]=='D')
        return(2);
    else if (a[x][y]=='T')
        return(3);
    else
        return(0);
}
bool in[60][60];
void spfa(int id)
{
    queue <pair <int,int> > Q;
    for (int i=1;i<=n;i++)
        for (int j=1;j<=m;j++)
            if (f[id][i][j]!=inf)
            {
                Q.push(make_pair(i,j));
                in[i][j]=true;
            }
    while (!Q.empty())
    {
        int x0=Q.front().first,y0=Q.front().second;
        Q.pop();
        in[x0][y0]=false;
        for (int i=0;i<4;i++)
        {
            int x=x0+c[i][0],y=y0+c[i][1],t=cost(x,y);
            if (t!=-1 && f[id][x0][y0]+t<f[id][x][y])
            {
                f[id][x][y]=f[id][x0][y0]+t;
                if (!in[x][y])
                {
                    in[x][y]=true;
                    Q.push(make_pair(x,y));
                }
            }
        }
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    for (int i=1;i<=n;i++)
        scanf("%s",a[i]+1);
    memset(f,63,sizeof(f));
    inf=f[0][0][0];
    int cnt=0,Sx,Sy;
    for (int i=1;i<=n;i++)
        for (int j=1;j<=m;j++)
        {
            if (a[i][j]=='X')
                Sx=i,Sy=j;
            if (a[i][j]=='G')
            {
                f[1<<cnt][i][j]=0;
                cnt++;
            }
        }
    for (int i=1;i<1<<cnt;i++)
    {
        for (int j=1;j<=n;j++)
            for (int k=1;k<=m;k++)
            {
                int t=cost(j,k);
                if (t==-1)
                    continue;
                for (int l=i;l;l=i&l-1)
                    f[i][j][k]=min(f[i][j][k],f[l][j][k]+f[i^l][j][k]-t);
            }
        spfa(i);
    }
    if (cnt==0)
        printf("0\n");
    else
        printf("%d\n",f[(1<<cnt)-1][Sx][Sy]);
    return(0);
}

