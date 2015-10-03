#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
const int c[8][2]={{-1,2},{-1,-2},{1,2},{1,-2},{2,-1},{2,1},{-2,-1},{-2,1}};
const char upper[][11]={"QWERTYUIOP","ASDFGHJKL:","ZXCVBNM<>?","^^      ^^"};
const char lower[][11]={"qwertyuiop","asdfghjkl;","zxcvbnm,./","^^      ^^"};
struct state
{
    int len,u,v;
    state(int len,int u,int v):len(len),u(u),v(v){}
};
int idx,vis[110][40][40];
char a[110];
int main()
{
    while (1)
    {
        gets(a+1);
        if (a[1]=='*')
            break;
        int n=strlen(a+1);
        queue <state> Q;
        Q.push(state(0,30,39));
        vis[0][30][39]=++idx;
        bool flag=false;
        while (!Q.empty())
        {
            int len=Q.front().len,u=Q.front().u,v=Q.front().v;
            Q.pop();
            int x0=u/10,y0=u%10,x1=v/10,y1=v%10;
            for (int i=0;i<8;i++)
            {
                int x=x0+c[i][0],y=y0+c[i][1];
                if (x<0 || x>=4 || y<0 || y>=10 || x==x1 && y==y1)
                    continue;
                int now=x*10+y;
                if (lower[x][y]=='^')
                {
                    if (vis[len][now][v]!=idx)
                    {
                        vis[len][now][v]=idx;
                        Q.push(state(len,now,v));
                    }
                    continue;
                }
                char ch=lower[x1][y1]=='^'?upper[x][y]:lower[x][y];
                if (ch==a[len+1])
                {
                    if (len==n-1)
                    {
                        flag=true;
                        break;
                    }
                    if (vis[len+1][now][v]!=idx)
                    {
                        vis[len+1][now][v]=idx;
                        Q.push(state(len+1,now,v));
                    }
                }
            }
            for (int i=0;i<8;i++)
            {
                int x=x1+c[i][0],y=y1+c[i][1];
                if (x<0 || x>=4 || y<0 || y>=10 || x==x0 && y==y0)
                    continue;
                int now=x*10+y;
                if (lower[x][y]=='^')
                {
                    if (vis[len][u][now]!=idx)
                    {
                        vis[len][u][now]=idx;
                        Q.push(state(len,u,now));
                    }
                    continue;
                }
                char ch=lower[x0][y0]=='^'?upper[x][y]:lower[x][y];
                if (ch==a[len+1])
                {
                    if (len==n-1)
                    {
                        flag=true;
                        break;
                    }
                    if (vis[len+1][u][now]!=idx)
                    {
                        vis[len+1][u][now]=idx;
                        Q.push(state(len+1,u,now));
                    }
                }
            }
            if (flag)
                break;
        }
        printf("%d\n",flag);
    }
    return(0);
}


