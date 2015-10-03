#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
struct tree
{
    int l,r,cnt;
    ll len;
};
tree a[524300];
void build(int x,int l,int r)
{
    a[x].l=l,a[x].r=r,a[x].cnt=0,a[x].len=0;
    if (l==r)
        return;
    int ls=x<<1,rs=ls+1,mid=a[x].l+a[x].r>>1;
    build(ls,l,mid);
    build(rs,mid+1,r);
}
vector <ll> Y;
void update(int x)
{
    if (a[x].cnt)
        a[x].len=Y[a[x].r]-Y[a[x].l-1];
    else if (a[x].l==a[x].r)
        a[x].len=0;
    else
    {
        int ls=x<<1,rs=ls+1;
        a[x].len=a[ls].len+a[rs].len;
    }
}
void modify(int x,int l,int r,int delta)
{
    if (a[x].l==l && a[x].r==r)
        a[x].cnt+=delta;
    else
    {
        int ls=x<<1,rs=ls+1,mid=a[x].l+a[x].r>>1;
        if (r<=mid)
            modify(ls,l,r,delta);
        else if (l>mid)
            modify(rs,l,r,delta);
        else
        {
            modify(ls,l,mid,delta);
            modify(rs,mid+1,r,delta);
        }
    }
    update(x);
}
struct point
{
    ll x,y;
    point(){}
    point(ll x,ll y):x(x),y(y){}
    point rotate() const
    {
        point ret(-y,x);
        if (ret.x)
            ret.x/=abs(ret.x);
        if (ret.y)
            ret.y/=abs(ret.y);
        return(ret);
    }
};
inline point operator +(const point &a,const point &b)
{
    return(point(a.x+b.x,a.y+b.y));
}
inline point operator -(const point &a,const point &b)
{
    return(point(a.x-b.x,a.y-b.y));
}
struct event
{
    ll x,y1,y2;
    int delta;
    event(ll x,ll y1,ll y2,int delta):x(x),y1(y1),y2(y2),delta(delta){}
};
inline bool operator <(const event &a,const event &b)
{
    return(a.x<b.x);
}
vector <event> e;
void insert(const point &a,const point &b)
{
    e.push_back(event(min(a.x,b.x),min(a.y,b.y),max(a.y,b.y),-1));
    e.push_back(event(max(a.x,b.x),min(a.y,b.y),max(a.y,b.y),1));
    Y.push_back(a.y);
    Y.push_back(b.y);
}
point p[100010];
int main()
{
    p[0].x=p[0].y=0;
    int n;
    scanf("%d",&n);
    for (int i=1;i<=n;i++)
    {
        p[i]=p[i-1];
        int x;
        scanf("%d",&x);
        if (i&1)
            p[i].y+=x;
        else
            p[i].x+=x;
    }
    for (int i=1;i<=n;i++)
    {
        point dir=(p[i]-p[i-1]).rotate();
        insert(p[i-1]+dir,p[i]);
    }
    sort(e.begin(),e.end());
    sort(Y.begin(),Y.end());
    Y.erase(unique(Y.begin(),Y.end()),Y.end());
    build(1,1,Y.size()-1);
    ll ans=0;
    for (int i=0;i<e.size();i++)
    {
        if (i)
            ans+=(e[i].x-e[i-1].x)*a[1].len;
        int l=lower_bound(Y.begin(),Y.end(),e[i].y1)-Y.begin()+1;
        int r=lower_bound(Y.begin(),Y.end(),e[i].y2)-Y.begin();
        modify(1,l,r,e[i].delta);
    }
    printf("%lld\n",ans);
    return(0);
}

