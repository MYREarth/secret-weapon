#include <cstdio>
#include <cstdlib>
#include <cmath>
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
inline ll det(const point &a,const point &b)
{
    return(ll(a.x)*b.y-ll(a.y)*b.x);
}
inline ll side(const point &p,const point &a,const point &b)
{
    return(det(b-a,p-a));
}
inline ll area(const point &a,const point &b,const point &c)
{
    return(abs(det(b-a,c-a)));
}
inline double sqr(double x)
{
    return(x*x);
}
inline double dist(const point &a,const point &b)
{
    return(sqrt(sqr(a.x-b.x)+sqr(a.y-b.y)));
}
inline double ptoline(const point &p,const point &a,const point &b)
{
    return(area(p,a,b)/dist(a,b));
}
inline void lower_convex(point a[],int &n)
{
    int m=0;
    static point b[1000010];
    for (int i=1;i<=n;i++)
    {
        while (m>=2 && det(b[m]-b[m-1],a[i]-b[m])<=0)
            m--;
        b[++m]=a[i];
    }
    n=m;
    for (int i=1;i<=n;i++)
        a[i]=b[i];
}
inline void upper_convex(point a[],int &n)
{
    int m=0;
    static point b[1000010];
    for (int i=n;i;i--)
    {
        while (m>=2 && det(b[m]-b[m-1],a[i]-b[m])<=0)
            m--;
        b[++m]=a[i];
    }
    n=m;
    for (int i=1;i<=n;i++)
        a[i]=b[n-i+1];
}
point a[1000010],b[1000010];
int main()
{
    int n;
    scanf("%d",&n);
    for (int i=1;i<=n;i++)
    {
        a[i].x=i;
        scanf("%d",&a[i].y);
    }
    for (int i=1;i<=n;i++)
    {
        b[i].x=i;
        scanf("%d",&b[i].y);
    }
    int m=n;
    upper_convex(a,n);
    lower_convex(b,m);
    double ans=1e100;
    int t=m;
    for (int i=2;i<=n;i++)
    {
        while (t>1 && (side(b[t],a[i-1],a[i])>=0 || side(b[t-1],a[i-1],a[i])<0 && area(a[i-1],a[i],b[t])<=area(a[i-1],a[i],b[t-1])))
            t--;
        if (side(b[t],a[i-1],a[i])>=0)
            ans=0;
        else
            ans=min(ans,ptoline(b[t],a[i-1],a[i]));
    }
    t=1;
    for (int i=m-1;i;i--)
    {
        while (t<n && (side(a[t],b[i+1],b[i])>=0 || side(a[t+1],b[i+1],b[i])<0 && area(b[i+1],b[i],a[t])<=area(b[i+1],b[i],a[t+1])))
            t++;
        if (side(a[t],b[i+1],b[i])>=0)
            ans=0;
        else
            ans=min(ans,ptoline(a[t],b[i+1],b[i]));
    }
    printf("%.20f\n",ans);
    return(0);
}

