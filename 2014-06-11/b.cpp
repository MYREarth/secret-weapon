#include <cstdio>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;
int tot,b[100010],a[1000010][2];
void add(int x,int y)
{
    a[++tot][0]=y,a[tot][1]=b[x],b[x]=tot;
}
int idx,dfn[100010],low[100010];
bool in[100010];
stack <int> s;
vector <int> c[100010];
void tarjan(int x)
{
    dfn[x]=low[x]=++idx;
    in[x]=true;
    s.push(x);
    for (int i=b[x];i;i=a[i][1])
    {
        int y=a[i][0];
        if (!dfn[y])
        {
            tarjan(y);
            low[x]=min(low[x],low[y]);
        }
        else if (in[y])
            low[x]=min(low[x],dfn[y]);
    }
    if (dfn[x]==low[x])
    {
        tot++;
        while (1)
        {
            int y=s.top();
            s.pop();
            in[y]=false;
            c[tot].push_back(y);
            if (x==y)
                break;
        }
    }
}
int main()
{
    int m,n;
    scanf("%d%d",&m,&n);
    for (int i=1;i<=m;i++)
    {
        int K,prev;
        scanf("%d%d",&K,&prev);
        for (int j=2;j<=K;j++)
        {
            int x;
            scanf("%d",&x);
            add(prev,x);
            prev=x;
        }
    }
    tot=0;
    for (int i=1;i<=n;i++)
        if (!dfn[i])
            tarjan(i);
    printf("%d\n",tot);
    for (int i=1;i<=tot;i++)
    {
        printf("%d",c[i].size());
        for (int j=0;j<c[i].size();j++)
            printf(" %d",c[i][j]);
        printf("\n");
    }
    return(0);
}

