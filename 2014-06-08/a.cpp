#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
struct point
{
    int x,y;
    point(){}
    point(int x,int y):x(x),y(y){}
    point rotate() const
    {
        return(point(-y,x));
    }
};
inline bool operator <(const point &a,const point &b)
{
    return(a.x<b.x);
}
inline point operator -(const point &a,const point &b)
{
    return(point(a.x-b.x,a.y-b.y));
}
inline ll dot(const point &a,const point &b)
{
    return(ll(a.x)*b.x+ll(a.y)*b.y);
}
inline ll det(const point &a,const point &b)
{
    return(ll(a.x)*b.y-ll(a.y)*b.x);
}
struct event
{
    point p;
    int u,v;
    event(const point &p,int u,int v):p(p),u(u),v(v){}
};
inline bool operator <(const event &a,const event &b)
{
    return(det(a.p,b.p)>0);
}
int c[1010],to[1010];
point N,a[1010];
inline bool lq(int x,int y)
{
    return(dot(N,a[x])<dot(N,a[y]));
}
inline bool cmp(int x,int y)
{
    return(a[x]<a[y]);
}
vector <event> e;
inline bool fuck(const pair <int,int> &a,const pair <int,int> &b)
{
    return(a.first<b.first || a.first==b.first && a.second>b.second);
}
void print(int m)
{
    sort(c+1,c+m+1);
    for (int i=1;i<=m;i++)
        printf("%d%c",c[i],i==m?'\n':' ');
}
ll work(int n,int m,ll ans)
{
    for (int i=1;i<=n;i++)
        c[i]=i;
    sort(c+1,c+n+1,cmp);
    int A=0,B=0;
    for (int i=1;i<=m;i++)
        A+=a[c[i]].x,B+=a[c[i]].y;
    for (int i=1;i<=n;i++)
        to[c[i]]=i;
    ll ret=ll(A)*B;
    if (ret==ans)
    {
        print(m);
        return(ret);
    }
    for (int i=0,j;i<e.size();i=j)
    {
        vector <pair <int,int> > b;
        for (j=i;j<e.size() && det(e[i].p,e[j].p)==0;j++)
        {
            int x=to[e[j].u],y=to[e[j].v];
            b.push_back(make_pair(min(x,y),max(x,y)));
        }
        sort(b.begin(),b.end(),fuck);
        int l=1,r=0,tmp=j;
        for (int j=0;j<b.size();j++)
        {
            if (b[j].first>=l && b[j].second<=r)
                continue;
            l=b[j].first,r=b[j].second;
            for (int k=l;k<=min(r,m);k++)
                A-=a[c[k]].x,B-=a[c[k]].y;
            if (tmp==e.size())
                N=point(0,1);
            else
                N=e[tmp].p;
            sort(c+l,c+r+1,lq);
            for (int k=l;k<=min(r,m);k++)
                A+=a[c[k]].x,B+=a[c[k]].y;
            for (int k=l;k<=r;k++)
                to[c[k]]=k;
        }
        ret=min(ret,ll(A)*B);
        if (ret==ans)
        {
            print(m);
            return(ret);
        }
    }
    return(ret);
}
int main()
{
    freopen("ancients.in","r",stdin);
    freopen("ancients.out","w",stdout);
    int n,m;
    scanf("%d%d",&n,&m);
    for (int i=1;i<=n;i++)
        scanf("%d%d",&a[i].x,&a[i].y);
    for (int i=1;i<=n;i++)
        for (int j=1;j<=n;j++)
        {
            point dir=(a[j]-a[i]).rotate();
            if (dir.x<=0 || dir.y<=0)
                continue;
            e.push_back(event(dir,i,j));
        }
    sort(e.begin(),e.end());
    ll ans=work(n,m,-1);
    printf("%lld\n",ans);
    work(n,m,ans);
    return(0);
}

