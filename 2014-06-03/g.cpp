#include <cstdio>
#include <stack>
#include <utility>
#include <algorithm>
using namespace std;
int idx,tot,fa[2000010],b[2000010],rev[2000010],dfn[2000010],low[2000010],c[2000010],a[8000010][2];
char color[1000010][2];
bool in[2000010];
void add(int x,int y)
{
    a[++tot][0]=y,a[tot][1]=b[x],b[x]=tot;
}
void tarjan(int S)
{
    stack <int> s;
    stack <pair <int,int> > lq;
    lq.push(make_pair(S,-1));
    fa[S]=0;
    while (!lq.empty())
    {
        int x=lq.top().first;
        if (lq.top().second==-1)
        {
            lq.top().second=b[x];
            dfn[x]=low[x]=++idx;
            in[x]=true;
            s.push(x);
        }
        else if (lq.top().second)
        {
            int y=a[lq.top().second][0];
            lq.top().second=a[lq.top().second][1];
            if (!dfn[y])
            {
                fa[y]=x;
                lq.push(make_pair(y,-1));
            }
            else if (in[y])
                low[x]=min(low[x],dfn[y]);
        }
        else
        {
            lq.pop();
            if (fa[x])
                low[fa[x]]=min(low[fa[x]],low[x]);
            if (dfn[x]==low[x])
            {
                c[0]++;
                while (1)
                {
                    int y=s.top();
                    s.pop();
                    c[y]=c[0],in[y]=false;
                    if (x==y)
                        break;
                }
            }
        }
    }
}
int main()
{
    int T;
    scanf("%d",&T);
    while (T--)
    {
        int n;
        scanf("%d",&n);
        for (int i=1;i<=n;i++)
        {
            scanf(" %c %c",&color[i][0],&color[i][1]);
            rev[i]=i+n;
            rev[i+n]=i;
            b[i]=b[i+n]=0;
            dfn[i]=dfn[i+n]=0;
        }
        tot=0;
        for (int i=1;i<=n;i++)
        {
            int j=i==n?1:i+1;
            for (int u=0;u<=1;u++)
                for (int v=0;v<=1;v++)
                    if (color[i][u]==color[j][v])
                    {
                        int x=i+u*n,y=j+v*n;
                        add(x,rev[y]);
                        add(y,rev[x]);
                    }
        }
        idx=c[0]=0;
        for (int i=1;i<=2*n;i++)
            if (!dfn[i])
                tarjan(i);
        bool flag=true;
        for (int i=1;i<=n;i++)
            if (c[i]==c[i+n])
            {
                flag=false;
                break;
            }
        if (!flag)
            printf("-\n");
        else
        {
            for (int i=1;i<=n;i++)
                printf("%c",c[i]<c[i+n]?color[i][0]:color[i][1]);
            printf("\n");
        }
    }
    return(0);
}

