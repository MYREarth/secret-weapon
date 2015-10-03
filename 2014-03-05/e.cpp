#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
const char s[]=" RGB";
bool vis[510],adj[510],a[510][510];
int n,color[510];
queue <int> Q;
void dfs(int x,int p)
{
    vis[x]=true;
    for (int i=1;i<=n;i++)
    {
        if (!a[x][i] || vis[i] || !adj[i])
            continue;
        if (color[i]==0)
        {
            color[i]=6-color[x]-p;
            Q.push(i);
        }
        dfs(i,p);
    }
}
int main()
{
    int m;
    scanf("%d%d",&n,&m);
    if (n==1)
        printf("Plan OK\nR\n");
    else
    {
        for (int i=1;i<=m;i++)
        {
            int x,y;
            scanf("%d%d",&x,&y);
            a[x][y]=a[y][x]=true;
        }
        color[1]=1;
        Q.push(1);
        for (int i=1;i<=n;i++)
            if (a[1][i])
            {
                color[i]=2;
                Q.push(i);
                break;
            }
        while (!Q.empty())
        {
            int x=Q.front(),y;
            Q.pop();
            for (int i=1;i<=n;i++)
            {
                adj[i]=a[x][i];
                if (a[x][i] && color[i]!=0)
                    y=i;
            }
            memset(vis,0,sizeof(vis));
            dfs(y,color[x]);
        }
        bool flag=true;
        for (int i=1;i<=n;i++)
            for (int j=1;j<=n;j++)
                if (a[i][j] && color[i]==color[j])
                {
                    flag=false;
                    goto out;
                }
out:
        if (flag)
        {
            printf("Plan OK\n");
            for (int i=1;i<=n;i++)
                printf("%c",s[color[i]]);
            printf("\n");
        }
        else
            printf("Plan failed\n");
    }
    return(0);
}

