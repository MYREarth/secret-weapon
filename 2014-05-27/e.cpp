#include <cstdio>
#include <utility>
#include <queue>
#include <algorithm>
using namespace std;
struct tree
{
    int l,r,x,delta;
};
tree a[270000];
int v[100010],h[100010];
void build(int x,int l,int r)
{
    a[x].l=l,a[x].r=r,a[x].x=a[x].delta=0;
    if (l==r)
        return;
    int ls=x<<1,rs=ls+1,mid=a[x].l+a[x].r>>1;
    build(ls,l,mid);
    build(rs,mid+1,r);
}
void updata(int x)
{
    a[x].x+=a[x].delta;
    if (a[x].l!=a[x].r)
    {
        int ls=x<<1,rs=ls+1;
        a[ls].delta+=a[x].delta;
        a[rs].delta+=a[x].delta;
    }
    a[x].delta=0;
}
void update(int x)
{
    int ls=x<<1,rs=ls+1;
    updata(ls);
    updata(rs);
    a[x].x=max(a[ls].x,a[rs].x);
}
void modify(int x,int l,int r,int value)
{
    if (a[x].l==l && a[x].r==r)
    {
        a[x].delta+=value;
        return;
    }
    updata(x);
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
int query(int x,int l,int r)
{
    updata(x);
    if (a[x].l==l && a[x].r==r)
        return(a[x].x);
    int ls=x<<1,rs=ls+1,mid=a[x].l+a[x].r>>1;
    if (r<=mid)
        return(query(ls,l,r));
    else if (l>mid)
        return(query(rs,l,r));
    else
        return(max(query(ls,l,mid),query(rs,mid+1,r)));
}
int main()
{
    freopen("explosion.in","r",stdin);
    int T;
    scanf("%d",&T);
    while (T--)
    {
        int n;
        scanf("%d",&n);
        for (int i=1;i<=n;i++)
            scanf("%d%d",&v[i],&h[i]);
        build(1,1,n);
        priority_queue <pair <int,int> > Q;
        int ans=0;
        for (int i=n;i;i--)
        {
            while (!Q.empty() && Q.top().first>i)
            {
                int x=Q.top().second;
                Q.pop();
                modify(1,x,min(n,x+h[x]),-1);
            }
            ans=max(ans,query(1,i,min(n,i+h[i]))+1);
            modify(1,i,min(n,i+h[i]),1);
            Q.push(make_pair(i-v[i],i));
        }
        printf("%d\n",ans);
    }
    return(0);
}

