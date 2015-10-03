#include <cstdio>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;
typedef set <int>::iterator iter;
struct data
{
    int l,r,x,k;
};
data a[270000];
void build(int x,int l,int r)
{
    a[x].l=l,a[x].r=r,a[x].x=r-l+1,a[x].k=0;
    if (l==r)
        return;
    int ls=x<<1,rs=ls+1,mid=a[x].l+a[x].r>>1;
    build(ls,l,mid);
    build(rs,mid+1,r);
}
void update(int x)
{
    if (a[x].k>0)
    {
        a[x].x=0;
        return;
    }
    if (a[x].l==a[x].r)
    {
        a[x].x=1;
        return;
    }
    int ls=x<<1,rs=ls+1;
    a[x].x=a[ls].x+a[rs].x;
}
void modify(int x,int l,int r,int value)
{
    if (a[x].l==l && a[x].r==r)
    {
        a[x].k+=value;
        update(x);
        return;
    }
    int ls=x<<1,rs=ls+1,mid=a[x].l+a[x].r>>1;
    if (r<=mid)
        modify(ls,l,r,value);
    else if (l>mid)
        modify(rs,l,r,value);
    else
    {
        modify(ls,l,mid,value);
        modify(rs,mid+1,r,value);
    }
    update(x);
}
int n,K;
void update(int l,int r,int value)
{
    int x=max(1,r-K+1);
    int y=min(n-K+1,l);
    if (x<=y)
        modify(1,x,y,value);
}
bool flag[100010];
int m,prime[100010],to[100010];
vector <int> p[100010];
void init()
{
    const int n=100000;
    for (int i=2;i*i<=n;i++)
    {
        if (flag[i])
            continue;
        for (int j=i;i*j<=n;j++)
        {
            flag[i*j]=true;
            to[i*j]=i;
        }
    }
    for (int i=2;i<=n;i++)
        if (!flag[i])
        {
            prime[++m]=i;
            to[i]=i;
        }
    for (int i=1;i<=n;i++)
    {
        int x=i;
        while (x!=1)
        {
            p[i].push_back(to[x]);
            x/=to[x];
        }
        sort(p[i].begin(),p[i].end());
        p[i].erase(unique(p[i].begin(),p[i].end()),p[i].end());
        for (int j=0;j<p[i].size();j++)
            p[i][j]=lower_bound(prime+1,prime+m+1,p[i][j])-prime;
    }
}
set <int> s[10000];
int v[100010];
int main()
{
    init();
    while (1)
    {
        int Q;
        scanf("%d%d%d",&n,&K,&Q);
        if (n==0 && K==0 && Q==0)
            break;
        for (int i=1;i<=m;i++)
            s[i].clear();
        for (int i=1;i<=n;i++)
            scanf("%d",&v[i]);
        for (int i=1;i<=n;i++)
        {
            int x=v[i];
            for (int j=0;j<p[x].size();j++)
            {
                int y=p[x][j];
                s[y].insert(i);
            }
        }
        build(1,1,n-K+1);
        for (int i=1;i<=m;i++)
            for (iter k=s[i].begin();k!=s[i].end();k++)
            {
                iter t=k;
                t++;
                if (t!=s[i].end())
                    update(*k,*t,1);
            }
        printf("%d\n",n-K+1-a[1].x);
        while (Q--)
        {
            int x,y;
            scanf("%d%d",&x,&y);
            int t=v[x];
            for (int i=0;i<p[t].size();i++)
            {
                int u=p[t][i];
                iter k=s[u].find(x);
                iter l=k,r=k;
                r++;
                if (r!=s[u].end())
                    update(*k,*r,-1);
                if (k!=s[u].begin())
                {
                    l--;
                    update(*l,*k,-1);
                    if (r!=s[u].end())
                        update(*l,*r,1);
                }
                s[u].erase(x);
            }
            for (int i=0;i<p[y].size();i++)
            {
                int u=p[y][i];
                s[u].insert(x);
                iter k=s[u].find(x);
                iter l=k,r=k;
                r++;
                if (r!=s[u].end())
                    update(*k,*r,1);
                if (k!=s[u].begin())
                {
                    l--;
                    update(*l,*k,1);
                    if (r!=s[u].end())
                        update(*l,*r,-1);
                }
            }
            v[x]=y;
            printf("%d\n",n-K+1-a[1].x);
        }
        printf("%lld\n",accumulate(v+1,v+n+1,0LL));
    }
    return(0);
}

