#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
const int N=400010;
struct edge
{
    int x,y,len;
};
inline bool operator <(const edge &a,const edge &b)
{
    return(a.len<b.len);
}
int tot,timestamp,vis[N],F[N],f[N],ans[N],b[N],a[N*2][3];
vector <int> p[N];
edge e[N],tmp[N*2];
void add(int x,int y,int z)
{
    a[++tot][0]=y,a[tot][1]=z,a[tot][2]=b[x],b[x]=tot;
    a[++tot][0]=x,a[tot][1]=z,a[tot][2]=b[y],b[y]=tot;
}
int idx,node,super,in[N],out[N],dep[N],fa[N][19];
bool inrange(int x,int y)
{
    return(in[x]>=in[y] && in[x]<=out[y]);
}
int find(int x)
{
    if (vis[x]!=timestamp)
    {
        vis[x]=timestamp;
        if (node!=-1 && !inrange(x,node))
            f[x]=super;
        else
            f[x]=F[x];
    }
    if (x!=f[x])
        f[x]=find(f[x]);
    return(f[x]);
}
bool choose[N];
int kruskal(int n,int m)
{
    sort(e+1,e+m+1);
    int cnt=0;
    timestamp++;
    int ret=0;
    f[super]=super;
    vis[super]=timestamp;
    for (int i=1;i<=m;i++)
    {
        if (e[i].x==node || e[i].y==node)
            continue;
        int x=find(e[i].x),y=find(e[i].y);
        if (x==y)
            continue;
        choose[i]=true;
        cnt++;
        ret=e[i].len;
        f[x]=y;
    }
    return(cnt+1==n?ret:-1);
}
void dfs(int x)
{
    in[x]=++idx;
    for (int i=1;i<=18;i++)
        fa[x][i]=fa[fa[x][i-1]][i-1];
    for (int i=b[x];i;i=a[i][2])
    {
        int y=a[i][0];
        if (y==fa[x][0])
            continue;
        dep[y]=dep[x]+1;
        fa[y][0]=x;
        dfs(y);
    }
    out[x]=++idx;
}
int lca(int x,int y)
{
    if (dep[x]<dep[y])
        swap(x,y);
    for (int i=18;i>=0;i--)
        if (dep[fa[x][i]]>=dep[y])
            x=fa[x][i];
    if (x==y)
        return(x);
    for (int i=18;i>=0;i--)
        if (fa[x][i]!=fa[y][i])
            x=fa[x][i],y=fa[y][i];
    return(fa[x][0]);
}
int best,root[N],l[N*2],r[N*2],v[N*2],d[N*2];
vector <int> adj[N];
int merge(int x,int y)
{
    if (x==0 || y==0)
        return(x+y);
    if (v[x]>v[y])
        swap(x,y);
    r[x]=merge(r[x],y);
    if (d[l[x]]<d[r[x]])
        swap(l[x],r[x]);
    d[x]=d[r[x]]+1;
    return(x);
}
void getans(int x)
{
    int here=1<<30;
    for (int i=b[x];i;i=a[i][2])
    {
        int y=a[i][0];
        here=min(here,a[i][1]);
        if (y==fa[x][0])
            continue;
        getans(y);
    }
    int tot=0,cnt=x!=1;
    for (int i=b[x];i;i=a[i][2])
    {
        int y=a[i][0];
        if (y==fa[x][0])
            continue;
        cnt++;
        if (root[y])
            e[++tot]=tmp[root[y]];
    }
    for (int i=0;i<p[x].size();i++)
        e[++tot]=tmp[p[x][i]];
    node=x;
    int now=kruskal(cnt,tot);
    for (int i=b[x];i;i=a[i][2])
    {
        int y=a[i][0];
        if (y==fa[x][0])
            continue;
        while (F[y]!=F[F[y]])
            F[y]=F[F[y]];
        F[y]=x;
        root[x]=merge(root[x],root[y]);
    }
    for (int i=0;i<adj[x].size();i++)
    {
        int y=adj[x][i];
        root[x]=merge(root[x],y);
        here=min(here,tmp[y].len);
    }
    if (now!=-1)
        ans[x]=max(max(best,now),here);
    while (root[x])
    {
        int id=root[x];
        if (inrange(tmp[id].x,x) && inrange(tmp[id].y,x))
            root[x]=merge(l[root[x]],r[root[x]]);
        else
            break;
    }
}
int main()
{
    int n,m;
    while (scanf("%d%d",&n,&m)==2)
    {
        for (int i=1;i<=n;i++)
        {
            b[i]=0;
            F[i]=i;
            p[i].clear();
            adj[i].clear();
            ans[i]=-1;
        }
        super=n+1;
        for (int i=1;i<=m;i++)
        {
            scanf("%d%d%d",&e[i].x,&e[i].y,&e[i].len);
            choose[i]=false;
        }
        node=-1;
        best=kruskal(n,m);
        if (best!=-1)
        {
            tot=0;
            for (int i=1;i<=m;i++)
                if (choose[i])
                    add(e[i].x,e[i].y,e[i].len);
            idx=0;
            dep[1]=1;
            dfs(1);
            for (int i=1;i<=m;i++)
            {
                if (choose[i])
                    continue;
                p[lca(e[i].x,e[i].y)].push_back(i);
                adj[e[i].x].push_back(i);
                adj[e[i].y].push_back(i+m);
                tmp[i+m]=tmp[i]=e[i];
                l[i]=0,r[i]=0,v[i]=tmp[i].len,d[i]=1;
                l[i+m]=0,r[i+m]=0,v[i+m]=tmp[i+m].len,d[i+m]=1;
            }
            for (int i=1;i<=n;i++)
            {
                F[i]=i;
                root[i]=0;
            }
            getans(1);
        }
        static int id=0;
        printf("Case %d:",++id);
        for (int i=1;i<=n;i++)
            printf(" %d",ans[i]);
        printf("\n");
    }
    return(0);
}

