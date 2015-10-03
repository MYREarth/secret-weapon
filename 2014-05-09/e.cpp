#include <cstdio>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;
struct segement
{
    struct tree
    {
        int l,r;
        set <int> s;
    };
    tree a[270000];
    void build(int x,int l,int r)
    {
        a[x].l=l,a[x].r=r,a[x].s.clear();
        if (l==r)
            return;
        int ls=x<<1,rs=ls+1,mid=a[x].l+a[x].r>>1;
        build(ls,l,mid);
        build(rs,mid+1,r);
    }
    void insert(int x,int l,int r,int value)
    {
        if (a[x].l==l && a[x].r==r)
        {
            a[x].s.insert(value);
            return;
        }
        int ls=x<<1,rs=ls+1,mid=a[x].l+a[x].r>>1;
        if (r<=mid)
            insert(ls,l,r,value);
        else if (l>mid)
            insert(rs,l,r,value);
        else
        {
            insert(ls,l,mid,value);
            insert(rs,mid+1,r,value);
        }
    }
    bool exist(int x,int pos,int value)
    {
        if (a[x].s.count(value))
            return(true);
        if (a[x].l==a[x].r)
            return(false);
        int ls=x<<1,rs=ls+1,mid=a[x].l+a[x].r>>1;
        return(pos<=mid?exist(ls,pos,value):exist(rs,pos,value));
    }
    int less(int x,int pos,int value)
    {
        set <int>::iterator k=a[x].s.lower_bound(value);
        int ret;
        if (k==a[x].s.begin())
            ret=-1;
        else
            ret=*--k;
        if (a[x].l!=a[x].r)
        {
            int ls=x<<1,rs=ls+1,mid=a[x].l+a[x].r>>1;
            ret=max(ret,pos<=mid?less(ls,pos,value):less(rs,pos,value));
        }
        return(ret);
    }
    int more(int x,int pos,int value)
    {
        set <int>::iterator k=a[x].s.upper_bound(value);
        int ret;
        if (k==a[x].s.end())
            ret=1<<30;
        else
            ret=*k;
        if (a[x].l!=a[x].r)
        {
            int ls=x<<1,rs=ls+1,mid=a[x].l+a[x].r>>1;
            ret=min(ret,pos<=mid?more(ls,pos,value):more(rs,pos,value));
        }
        return(ret);
    }
};
segement a,b;
vector <int> X,Y;
int xx[100010],yy[100010];
int main()
{
    int W,H,n;
    scanf("%d%d%d",&W,&H,&n);
    X.push_back(0);
    X.push_back(W);
    Y.push_back(0);
    Y.push_back(H);
    for (int i=1;i<=n;i++)
    {
        scanf("%d%d",&xx[i],&yy[i]);
        X.push_back(xx[i]);
        Y.push_back(yy[i]);
    }
    sort(X.begin(),X.end());
    X.erase(unique(X.begin(),X.end()),X.end());
    sort(Y.begin(),Y.end());
    Y.erase(unique(Y.begin(),Y.end()),Y.end());
    int ans=1;
    a.build(1,1,X.size());
    b.build(1,1,Y.size());
    a.insert(1,1,X.size(),1);
    a.insert(1,1,X.size(),Y.size());
    b.insert(1,1,Y.size(),1);
    b.insert(1,1,Y.size(),X.size());
    for (int i=1;i<=n;i++)
    {
        int x=lower_bound(X.begin(),X.end(),xx[i])-X.begin()+1;
        int y=lower_bound(Y.begin(),Y.end(),yy[i])-Y.begin()+1;
        int l=x,r=x,u=y,d=y;
        if (x!=1 && !a.exist(1,x,y))
            l=b.less(1,y,x);
        if (x!=X.size() && !a.exist(1,x+1,y))
            r=b.more(1,y,x);
        if (y!=1 && !b.exist(1,y,x))
            d=a.less(1,x,y);
        if (y!=Y.size() && !b.exist(1,y+1,x))
            u=a.more(1,x,y);
        int cnt=(l<x)+(x<r)+(d<y)+(y<u);
        if (cnt==4)
            ans+=3;
        else if (cnt==2)
            ans+=2;
        else if (cnt==1)
            ans++;
        if (x==1 || x==X.size())
            u=d=y;
        if (y==1 || y==Y.size())
            l=r=x;
        if (l<r)
            a.insert(1,l+1,r,y);
        if (d<u)
            b.insert(1,d+1,u,x);
    }
    printf("%d\n",ans);
    return(0);
}

