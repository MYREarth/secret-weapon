#include <cstdio>
#include <stack>
using namespace std;
bool in[210],a[210][210];
int n,idx,dfn[210],low[210],c[210];
stack <int> s;
inline int to(int x)
{
    return(x<0?n-x:x);
}
inline void add(int x,int y,int z)
{
    a[to(x)][to(y)]=a[to(x)][to(z)]=true;
}
void tarjan(int x,int father)
{
    dfn[x]=low[x]=++idx;
    s.push(x);
    in[x]=true;
    for (int y=1;y<=2*n;y++)
    {
        if (y==father || !a[x][y])
            continue;
        if (!dfn[y])
        {
            tarjan(y,x);
            low[x]=min(low[x],low[y]);
        }
        else if (in[y])
            low[x]=min(low[x],dfn[y]);
    }
    if (dfn[x]==low[x])
    {
        c[0]++;
        while (1)
        {
            int p=s.top();
            s.pop();
            c[p]=c[0];
            in[p]=false;
            if (p==x)
                break;
        }
    }
}
int main()
{
    int m;
    scanf("%d%d",&n,&m);
    for (int i=1;i<=m;i++)
    {
        int x,y,z;
        scanf("%d%d%d",&x,&y,&z);
        add(-x,y,z);
        add(-y,x,z);
        add(-z,x,y);
    }
    for (int i=1;i<=2*n;i++)
        if (!dfn[i])
            tarjan(i,0);
    bool flag=true;
    for (int i=1;i<=n;i++)
        if (c[i]==c[n+i])
        {
            flag=false;
            break;
        }
    if (!flag)
        printf("NO\n");
    else
    {
        printf("YES\n");
        for (int i=1;i<=n;i++)
            printf("%d%c",c[i]<c[n+i]?i:-i,i==n?'\n':' ');
    }
    return(0);
}

