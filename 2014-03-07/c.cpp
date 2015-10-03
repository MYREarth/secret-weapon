#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;
typedef long long ll;
struct data
{
    int l,r,cnt,sum;
};
data tree[270000];
void build(int x,int l,int r)
{
    tree[x].l=l,tree[x].r=r,tree[x].cnt=tree[x].sum=0;
    if (l==r)
        return;
    int ls=x<<1,rs=ls+1,mid=tree[x].l+tree[x].r>>1;
    build(ls,l,mid);
    build(rs,mid+1,r);
}
inline pair <int,int> operator +(const pair <int,int> &a,const pair <int,int> &b)
{
    return(make_pair(a.first+b.first,a.second+b.second));
}
pair <int,int> get(int x,int l,int r)
{
    if (tree[x].l==l && tree[x].r==r)
        return(make_pair(tree[x].sum,tree[x].cnt));
    int ls=x<<1,rs=ls+1,mid=tree[x].l+tree[x].r>>1;
    if (r<=mid)
        return(get(ls,l,r));
    else if (l>mid)
        return(get(rs,l,r));
    else
        return(get(ls,l,mid)+get(rs,mid+1,r));
}
void modify(int x,int pos,int cnt,int sum)
{
    tree[x].cnt+=cnt;
    tree[x].sum+=sum;
    if (tree[x].l==tree[x].r)
        return;
    int ls=x<<1,rs=ls+1,mid=tree[x].l+tree[x].r>>1;
    pos<=mid?modify(ls,pos,cnt,sum):modify(rs,pos,cnt,sum);
}
int dep[75010],b[75010],a[150010][3],fa[75010][17];
void dfs(int x,int father)
{
    fa[x][0]=father;
    for (int i=1;i<=16;i++)
        fa[x][i]=fa[fa[x][i-1]][i-1];
    for (int i=b[x];i;i=a[i][2])
    {
        int y=a[i][0];
        if (y==father)
            continue;
        dep[y]=dep[x]+1;
        dfs(y,x);
    }
}
int lca(int x,int y)
{
    if (dep[x]<dep[y])
        swap(x,y);
    for (int i=16;i>=0;i--)
        if (dep[fa[x][i]]>=dep[y])
            x=fa[x][i];
    for (int i=16;i>=0;i--)
        if (fa[x][i]!=fa[y][i])
            x=fa[x][i],y=fa[y][i];
    return(x==y?x:fa[x][0]);
}
vector <int> w;
vector <pair <int,bool> > query[75010];
ll ans;
void getans(int x,int father)
{
    for (int i=0;i<query[x].size();i++)
    {
        int pos=upper_bound(w.begin(),w.end(),query[x][i].first)-w.begin()+1;
        if (pos<=w.size())
        {
            pair <int,int> now=get(1,pos,w.size());
            if (query[x][i].second)
                ans+=now.first-ll(query[x][i].first)*now.second;
            else
            {
                ans-=now.first-ll(query[x][i].first)*now.second;
                ans-=now.first-ll(query[x][i].first)*now.second;
            }
        }
    }
    for (int i=b[x];i;i=a[i][2])
    {
        int y=a[i][0];
        if (y==father)
            continue;
        modify(1,lower_bound(w.begin(),w.end(),a[i][1])-w.begin()+1,1,a[i][1]);
        getans(y,x);
        modify(1,lower_bound(w.begin(),w.end(),a[i][1])-w.begin()+1,-1,-a[i][1]);
    }
}
int main()
{
    freopen("span.in","r",stdin);
    freopen("span.out","w",stdout);
    int n,m;
    scanf("%d%d",&n,&m);
    for (int i=1;i<n;i++)
    {
        int x,y,z;
        scanf("%d%d%d",&x,&y,&z);
        a[i][0]=y,a[i][1]=z,a[i][2]=b[x],b[x]=i;
        a[i+n][0]=x,a[i+n][1]=z,a[i+n][2]=b[y],b[y]=i+n;
        w.push_back(z);
    }
    dep[1]=1;
    dfs(1,0);
    sort(w.begin(),w.end());
    w.erase(unique(w.begin(),w.end()),w.end());
    build(1,1,w.size());
    for (int i=n;i<=m;i++)
    {
        int x,y,z;
        scanf("%d%d%d",&x,&y,&z);
        query[x].push_back(make_pair(z,true));
        query[y].push_back(make_pair(z,true));
        query[lca(x,y)].push_back(make_pair(z,false));
    }
    getans(1,0);
    printf("%lld\n",ans);
    return(0);
}

