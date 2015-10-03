#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
const double pi=acos(-1.0);
struct point
{
    double x,y;
    point(){}
    point(double x,double y):x(x),y(y){}
    point unit() const
    {
        double t=sqrt(x*x+y*y);
        return(point(x/t,y/t));
    }
    point rotate() const
    {
        return(point(-y,x));
    }
    double angle() const
    {
        return(atan2(y,x));
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
inline point operator *(const point &a,double b)
{
    return(point(a.x*b,a.y*b));
}
inline int sign(double x,double eps=1e-8)
{
    return(x<-eps?-1:x>eps);
}
inline bool operator ==(const point &a,const point &b)
{
    return(sign(a.x-b.x)==0 && sign(a.y-b.y)==0);
}
inline double dot(const point &a,const point &b)
{
    return(a.x*b.x+a.y*b.y);
}
inline double sqr(double x)
{
    return(x*x);
}
inline double dist(const point &a,const point &b)
{
    return(sqrt(sqr(a.x-b.x)+sqr(a.y-b.y)));
}
inline bool in(const point &o1,double r1,const point &o2,double r2)
{
    return(sign(dist(o1,o2)-(r2-r1))<=0);
}
inline point intersect(const point &o1,double r1,const point &o2,double r2)
{
    double d=dist(o1,o2);
    double x=(sqr(r1)-sqr(r2))/(2*d)+d/2;
    double l=sqrt(sqr(r1)-sqr(x));
    point dir=(o2-o1).unit();
    return(o1+dir*x+dir.rotate()*l);
}
inline point intersect(const point &a,const point &b,const point &o,double r)
{
    double t=dot(o-a,b-a)/dot(b-a,b-a);
    point p=a+(b-a)*t;
    double d=dist(o,p);
    double l=sqrt(sqr(r)-sqr(d));
    return(p+(b-a).unit()*l);
}
inline double calc(double theta,double r)
{
    return(2*pi*r*r*cos(theta));
}
inline double calc(double L,double R,double r)
{
    return(calc(L,r)-calc(R,r));
}
point a[2010];
double r[2010];
int main()
{
    int n;
    scanf("%d",&n);
    for (int i=1;i<=n;i++)
    {
        scanf("%lf%lf",&a[i].x,&r[i]);
        a[i].y=0;
        r[i]*=14;
    }
    double ans=0;
    for (int i=1;i<=n;i++)
    {
        if (sign(r[i])==0)
            continue;
        double L=0,R=pi;
        if (sign(a[i].x-r[i])<0)
        {
            point p=intersect(point(0,-1),point(0,1),a[i],r[i]);
            if (sign(p.y)<0)
                p.y*=-1;
            R=(p-a[i]).angle();
        }
        for (int j=1;j<=n;j++)
        {
            if (i==j || sign(r[j])==0)
                continue;
            if (a[i]==a[j] && sign(r[i]-r[j])==0)
            {
                if (i<j)
                {
                    L=R=0;
                    break;
                }
                continue;
            }
            if (in(a[i],r[i],a[j],r[j]))
            {
                L=R=0;
                break;
            }
            if (sign(dist(a[i],a[j])-r[i]-r[j])>=0)
                continue;
            point p=intersect(a[i],r[i],a[j],r[j]);
            if (sign(p.y)<0)
                p.y*=-1;
            if (sign(a[j].x-a[i].x)>0)
                L=max(L,(p-a[i]).angle());
            else
                R=min(R,(p-a[i]).angle());
        }
        if (sign(L-R)>=0)
            continue;
        if (sign(R-pi/2)<=0)
            ans+=calc(L,R,r[i]);
        else if (sign(L-pi/2)>=0)
            ans+=calc(pi-R,pi-L,r[i]);
        else
            ans+=calc(L,pi/2,r[i])+calc(pi-R,pi/2,r[i]);
    }
    printf("%.10f\n",ans);
    return(0);
}

