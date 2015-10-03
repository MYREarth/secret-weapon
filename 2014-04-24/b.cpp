#include <cstdio>
#include <cmath>
#include <utility>
#include <algorithm>
using namespace std;
const double pi=acos(-1.0);
struct point
{
    double x,y;
    point(){}
    point(double x,double y):x(x),y(y){}
    double angle() const
    {
        return(atan2(y,x));
    }
};
inline point operator -(const point &a,const point &b)
{
    return(point(a.x-b.x,a.y-b.y));
}
inline int sign(double x,double eps=1e-8)
{
    return(x<-eps?-1:x>eps);
}
inline double fix(double theta)
{
    while (sign(theta+pi)<0)
        theta+=2*pi;
    while (sign(theta-pi)>0)
        theta-=2*pi;
    return(theta);
}
inline double sqr(double x)
{
    return(x*x);
}
inline double dist(const point &a,const point &b)
{
    return(sqrt(sqr(a.x-b.x)+sqr(a.y-b.y)));
}
inline pair <double,double> calc(const point &a,const point &b,double angle)
{
    double theta=fix((b-a).angle()-angle);
    if (sign(theta)==0)
        return(make_pair(dist(a,b),angle));
    double r=dist(a,b)/2/sin(theta);
    return(make_pair(r*2*theta,fix(angle+2*theta)));
}
inline double calc(int n,point *a,double angle)
{
    double ret=0;
    for (int i=2;i<=n;i++)
    {
        pair <double,double> tmp=calc(a[i-1],a[i],angle);
        ret+=tmp.first;
        angle=tmp.second;
    }
    return(ret);
}
int main()
{
    int n;
    scanf("%d",&n);
    point a[1010];
    for (int i=1;i<=n;i++)
        scanf("%lf%lf",&a[i].x,&a[i].y);
    double ans=1e100;
    const int oo=260;
    for (int _=0;_<oo;_++)
    {
        double l=-pi+_*pi*2/oo,r=l+pi*2/oo;
        ans=min(ans,min(calc(n,a,l),calc(n,a,r)));
        for (int T=1;T<=100;T++)
        {
            double lx=(2*l+r)/3,rx=(l+2*r)/3;
            if (calc(n,a,lx)>calc(n,a,rx))
                l=lx;
            else
                r=rx;
        }
        ans=min(ans,calc(n,a,(l+r)/2));
    }
    for (int i=2;i<=n;i++)
    {
        double now=dist(a[i-1],a[i]),angle=(a[i]-a[i-1]).angle();
        for (int j=i+1;j<=n;j++)
        {
            pair <double,double> tmp=calc(a[j-1],a[j],angle);
            now+=tmp.first;
            angle=tmp.second;
        }
        angle=(a[i-1]-a[i]).angle();
        for (int j=i-2;j;j--)
        {
            pair <double,double> tmp=calc(a[j+1],a[j],angle);
            now+=tmp.first;
            angle=tmp.second;
        }
        ans=min(ans,now);
    }
    printf("%.10f\n",ans);
    return(0);
}

