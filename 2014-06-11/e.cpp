#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
struct point
{
    int x,y;
    point(){}
    point(int x,int y):x(x),y(y){}
};
inline point operator -(const point &a,const point &b)
{
    return(point(a.x-b.x,a.y-b.y));
}
inline bool operator <(const point &a,const point &b)
{
    return(a.x<b.x || a.x==b.x && a.y<b.y);
}
inline ll det(const point &a,const point &b)
{
    return(ll(a.x)*b.y-ll(a.y)*b.x);
}
inline void convex(point a[],int &n)
{
    sort(a+1,a+n+1);
    static point b[100010];
    int m=0;
    for (int i=1;i<=n;i++)
    {
        while (m>=2 && det(b[m]-b[m-1],a[i]-b[m])<=0)
            m--;
        b[++m]=a[i];
    }
    int rev=m;
    for (int i=n-1;i;i--)
    {
        while (m>rev && det(b[m]-b[m-1],a[i]-b[m])<=0)
            m--;
        b[++m]=a[i];
    }
    n=m-1;
    for (int i=1;i<=n;i++)
        a[i]=b[i];
}
point a[100010],p[100010];
double angle[100010];
int c[100010];
inline bool cmp(int x,int y)
{
    return(angle[x]<angle[y]);
}
inline int next(int t,int n)
{
    return(t==n?1:t+1);
}
int main()
{
    int n,m=0;
    scanf("%d",&n);
    for (int i=1;i<=n;i++)
    {
        scanf("%d%d",&a[i].x,&a[i].y);
        if (a[i].x!=0 || a[i].y!=0)
            p[++m]=a[i];
    }
    convex(a,n);
    if (m<=1)
        printf("0\n");
    else
    {
        for (int i=1;i<=m;i++)
        {
            c[i]=i;
            angle[i]=atan2(double(p[i].y),double(p[i].x));
        }
        sort(c+1,c+m+1,cmp);
        int t=1;
        for (int i=1;i<=n;i++)
            if (det(p[c[1]],a[i])>det(p[c[1]],a[t]))
                t=i;
        ll ans=det(p[c[1]],a[t]);
        for (int i=2;i<=m;i++)
        {
            point x=p[c[i]];
            while (det(x,a[next(t,n)])>det(x,a[t]))
                t=next(t,n);
            ans=max(ans,det(x,a[t]));
        }
        printf("%lld\n",ans);
    }
    return(0);
}

