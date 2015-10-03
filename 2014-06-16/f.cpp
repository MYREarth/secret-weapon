#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
struct tree
{
    int l,r;
    ll a1,b1,a2,b2;
};
tree a[1100000];
vector <int> Y;
void build(int x,int l,int r)
{
    a[x].l=l,a[x].r=r,a[x].a1=a[x].b1=a[x].a2=a[x].b2=0;
    if (l==r)
        return;
    int ls=x<<1,rs=ls+1,mid=a[x].l+a[x].r>>1;
    build(ls,l,mid);
    build(rs,mid+1,r);
}
void update(int x)
{
    int ls=x<<1,rs=ls+1,llen=Y[a[ls].r]-Y[a[ls].l-1],rlen=Y[a[rs].r]-Y[a[rs].l-1];
    a[x].a2=a[ls].a2+a[ls].a1*llen+a[rs].a2+a[rs].a1*rlen;
    a[x].b2=a[ls].b2+a[ls].b1*llen+a[rs].b2+a[rs].b1*rlen;
}
void modify(int x,int l,int r,int delta,int x0)
{
    if (a[x].l==l && a[x].r==r)
    {
        a[x].a1+=delta;
        a[x].b1+=-x0*delta;
        return;
    }
    int ls=x<<1,rs=ls+1,mid=a[x].l+a[x].r>>1;
    if (r<=mid)
        modify(ls,l,r,delta,x0);
    else if (l>mid)
        modify(rs,l,r,delta,x0);
    else
    {
        modify(ls,l,mid,delta,x0);
        modify(rs,mid+1,r,delta,x0);
    }
    update(x);
}
ll query(int x,int l,int r,int t)
{
    ll ret=(a[x].a1*t+a[x].b1)*(Y[r]-Y[l-1]);
    if (a[x].l==l && a[x].r==r)
        return(ret+a[x].a2*t+a[x].b2);
    int ls=x<<1,rs=ls+1,mid=a[x].l+a[x].r>>1;
    if (r<=mid)
        return(ret+query(ls,l,r,t));
    else if (l>mid)
        return(ret+query(rs,l,r,t));
    else
        return(ret+query(ls,l,mid,t)+query(rs,mid+1,r,t));
}
struct event
{
    int x,y1,y2,kind,delta;
    event(int x,int y1,int y2,int kind,int delta):x(x),y1(y1),y2(y2),kind(kind),delta(delta){}
};
inline bool operator <(const event &a,const event &b)
{
    return(a.x<b.x);
}
vector <event> e;
ll ans[100010];
int main()
{
    int n,Q,L,W;
    scanf("%d%d%d%d",&n,&Q,&L,&W);
    for (int i=1;i<=n;i++)
    {
        int x1,y1,x2,y2;
        scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
        Y.push_back(y1);
        Y.push_back(y2);
        e.push_back(event(x1,y1,y2,0,1));
        e.push_back(event(x2,y1,y2,0,-1));
    }
    for (int i=1;i<=Q;i++)
    {
        int x1,y1;
        scanf("%d%d",&x1,&y1);
        int x2=x1+L,y2=y1+W;
        Y.push_back(y1);
        Y.push_back(y2);
        e.push_back(event(x1,y1,y2,i,-1));
        e.push_back(event(x2,y1,y2,i,1));
    }
    sort(Y.begin(),Y.end());
    Y.erase(unique(Y.begin(),Y.end()),Y.end());
    build(1,1,Y.size()-1);
    sort(e.begin(),e.end());
    for (int i=0;i<e.size();i++)
    {
        int l=lower_bound(Y.begin(),Y.end(),e[i].y1)-Y.begin()+1;
        int r=lower_bound(Y.begin(),Y.end(),e[i].y2)-Y.begin();
        if (e[i].kind==0)
            modify(1,l,r,e[i].delta,e[i].x);
        else
            ans[e[i].kind]+=query(1,l,r,e[i].x)*e[i].delta;
    }
    for (int i=1;i<=Q;i++)
        printf("%lld\n",ans[i]);
    return(0);
}

