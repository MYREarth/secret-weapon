#include <cstdio>
#include <cstring>
#include <utility>
#include <queue>
using namespace std;
const int c[4][2]={{-1,-1},{-1,1},{1,-1},{1,1}};
int idx,t1,t2,id[20][2],to[20][20],cnt[65540],vis[20][65540];
char a[20][20];
void dfs(int x0,int y0)
{
    id[to[x0][y0]][0]=x0;
    id[to[x0][y0]][1]=y0;
    for (int i=0;i<4;i++)
    {
        int x1=x0+c[i][0],y1=y0+c[i][1];
        int x=x1+c[i][0],y=y1+c[i][1];
        if (x<=0 || x>10 || y<=0 || y>10)
            continue;
        if (to[x1][y1]==0)
            to[x1][y1]=++t2;
        if (to[x][y]==0)
        {
            to[x][y]=++t1;
            dfs(x,y);
        }
    }
}
int calc(int Sx,int Sy)
{
    memset(to,0,sizeof(to));
    to[Sx][Sy]=t1=1;
    t2=0;
    dfs(Sx,Sy);
    idx++;
    queue <pair <int,int> > Q;
    Q.push(make_pair(to[Sx][Sy],0));
    vis[to[Sx][Sy]][0]=idx;
    a[Sx][Sy]='#';
    int ans=0;
    while (!Q.empty())
    {
        int pos=Q.front().first,state=Q.front().second;
        Q.pop();
        ans=max(ans,cnt[state]);
        int x0=id[pos][0],y0=id[pos][1];
        for (int i=0;i<4;i++)
        {
            int x1=x0+c[i][0],y1=y0+c[i][1];
            int x=x1+c[i][0],y=y1+c[i][1];
            if (x<=0 || x>10 || y<=0 || y>10 || a[x][y]!='#' || a[x1][y1]!='B')
                continue;
            int mid=to[x1][y1],dest=to[x][y];
            if (!(state>>mid-1&1) && vis[dest][state|1<<mid-1]!=idx)
            {
                vis[dest][state|1<<mid-1]=idx;
                Q.push(make_pair(dest,state|1<<mid-1));
            }
        }
    }
    a[Sx][Sy]='W';
    return(ans);
}
int main()
{
    for (int i=0;i<1<<16;i++)
        cnt[i]=__builtin_popcount(i);
    int T;
    scanf("%d",&T);
    while (T--)
    {
        for (int i=1;i<=10;i++)
            scanf("%s",a[i]+1);
        int ans=0;
        for (int i=1;i<=10;i++)
            for (int j=1;j<=10;j++)
                if (a[i][j]=='W')
                    ans=max(ans,calc(i,j));
        printf("%d\n",ans);
    }
    return(0);
}
