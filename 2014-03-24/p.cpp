#include <cstdio>
#include <cmath>
#include <utility>
#include <vector>
#include <algorithm>
using namespace std;
const double pi=acos(-1.0);
struct point
{
    double x,y;
    point(){}
    point(double x,double y):x(x),y(y){}
    point rotate() const
    {
        return(point(-y,x));
    }
    point unit() const
    {
        double t=sqrt(x*x+y*y);
        return(point(x/t,y/t));
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
inline point operator /(const point &a,double b)
{
    return(point(a.x/b,a.y/b));
}
inline int sign(double x,double eps=1e-8)
{
    return(x<-eps?-1:x>eps);
}
inline bool operator <(const point &a,const point &b)
{
    return(sign(a.x-b.x)<0 || sign(a.x-b.x)==0 && sign(a.y-b.y)<0);
}
inline double dot(const point &a,const point &b)
{
    return(a.x*b.x+a.y*b.y);
}
inline double det(const point &a,const point &b)
{
    return(a.x*b.y-a.y*b.x);
}
inline double Sqrt(double x)
{
    if (sign(x)==0)
        return(0);
    return(sqrt(x));
}
inline double sqr(double x)
{
    return(x*x);
}
inline double dist(const point &a,const point &b)
{
    return(sqrt(sqr(a.x-b.x)+sqr(a.y-b.y)));
}
inline point project(const point &p,const point &a,const point &b)
{
    double t=dot(p-a,b-a)/dot(b-a,b-a);
    return(a+(b-a)*t);
}
inline point reflect(const point &p,const point &a,const point &b)
{
    return(project(p,a,b)*2-p);
}
inline point intersect(const point &o1,double r1,const point &o2,double r2)
{
    double d=dist(o1,o2);
    double x=(sqr(r1)-sqr(r2))/(2*d)+d/2;
    double l=Sqrt(sqr(r1)-sqr(x));
    point dir=(o2-o1).unit();
    return(o1+dir*x+dir.rotate()*l);
}
inline point tangent(const point &p,const point &o,double r)
{
    return(intersect((p+o)/2,dist(p,o)/2,o,r));
}
inline pair <point,point> tangent(const point &o1,double r1,const point &o2,double r2)
{
    if (sign(r1-r2)==0)
    {
        point dir=(o2-o1).rotate().unit()*r1;
        return(make_pair(o1+dir,o2+dir));
    }
    if (sign(r1-r2)<0)
    {
        pair <point,point> tmp=tangent(o2,r2,o1,r1);
        return(make_pair(tmp.second,tmp.first));
    }
    point p=tangent(o2,o1,r1-r2);
    point dir=(p-o1).unit()*r2;
    return(make_pair(p+dir,o2+dir));
}
inline double convex(pair <point,int> *a,int n,point *o,double *r)
{
    sort(a+1,a+n+1);
    static pair <point,int> b[2100010];
    int m=0;
    for (int i=1;i<=n;i++)
    {
        while (m>=2 && sign(det(b[m].first-b[m-1].first,a[i].first-b[m].first))<=0)
            m--;
        b[++m]=a[i];
    }
    int limit=m;
    for (int i=n-1;i;i--)
    {
        while (m>limit && sign(det(b[m].first-b[m-1].first,a[i].first-b[m].first))<=0)
            m--;
        b[++m]=a[i];
    }
    double ans=0;
    for (int i=2;i<=m;i++)
    {
        if (b[i-1].second!=b[i].second)
        {
            ans+=dist(b[i-1].first,b[i].first);
            continue;
        }
        int id=b[i].second;
        if (sign(r[id])==0)
            continue;
        double s1=(b[i-1].first-o[id]).angle();
        double s2=(b[i].first-o[id]).angle();
        if (sign(s2-s1)<0)
            s2+=2*pi;
        ans+=(s2-s1)*r[id];
    }
    for (int i=1;i<=m;i++)
        printf("%.10f %.10f %d\n",b[i].first.x,b[i].first.y,b[i].second);
    return(ans);
}
point o[1010];
double r[1010];
pair <point,int> a[2100010];
bool ok[1010];
int main()
{
    int n;
    scanf("%d",&n);
    for (int i=1;i<=n;i++)
    {
        scanf("%lf%lf%lf",&o[i].x,&o[i].y,&r[i]);
        ok[i]=true;
    }
    for (int i=1;i<=n;i++)
        for (int j=1;j<=n;j++)
        {
            if (i==j || !ok[j])
                continue;
            if (sign(dist(o[i],o[j])-(r[j]-r[i]))<=0)
            {
                ok[i]=false;
                break;
            }
        }
    int tot=0;
    for (int i=1;i<=n;i++)
    {
        if (!ok[i])
            continue;
        a[++tot]=make_pair(o[i]+point(0,r[i]),i);
        a[++tot]=make_pair(o[i]-point(0,r[i]),i);
        a[++tot]=make_pair(o[i]+point(r[i],0),i);
        a[++tot]=make_pair(o[i]-point(r[i],0),i);
        for (int j=i+1;j<=n;j++)
        {
            if (!ok[j])
                continue;
            if (sign(r[i])==0 && sign(r[j])==0)
                continue;
            if (sign(r[i])==0)
            {
                point tmp=tangent(o[i],o[j],r[j]);
                a[++tot]=make_pair(tmp,j);
                a[++tot]=make_pair(reflect(tmp,o[i],o[j]),j);
            }
            else if (sign(r[j])==0)
            {
                point tmp=tangent(o[j],o[i],r[i]);
                a[++tot]=make_pair(tmp,i);
                a[++tot]=make_pair(reflect(tmp,o[i],o[j]),i);
            }
            else
            {
                pair <point,point> tmp=tangent(o[i],r[i],o[j],r[j]);
                a[++tot]=make_pair(tmp.first,i);
                a[++tot]=make_pair(tmp.second,j);
                a[++tot]=make_pair(reflect(tmp.first,o[i],o[j]),i);
                a[++tot]=make_pair(reflect(tmp.second,o[i],o[j]),j);
            }
        }
    }
    printf("%.2f\n",convex(a,tot,o,r));
    return(0);
}

