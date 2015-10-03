#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int n=100;
int a[10010][10];
bool vis[10010];
inline int pos(int x,int y)
{
    return((x-1)*n+y);
}
inline void add(int x,int y)
{
    a[x][++a[x][0]]=y;
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
int main()
{
    freopen("maze.in","r",stdin);
    freopen("maze.out","w",stdout);
    for (int i=1;i<=n;i++)
        for (int j=1;j<=n;j++)
        {
            char s[10];
            scanf("%s",s);
            int len=strlen(s);
            for (int k=0;k<len;k++)
                if (s[k]=='N')
                    add(pos(i,j),pos(i-1,j));
                else if (s[k]=='S')
                    add(pos(i,j),pos(i+1,j));
                else if (s[k]=='W')
                    add(pos(i,j),pos(i,j-1));
                else
                    add(pos(i,j),pos(i,j+1));
        }
    printf("%s\n",dfs(1)<=260?"PRIM":"KRUSKAL");
    return(0);
}

