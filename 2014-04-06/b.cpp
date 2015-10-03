#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
bool debug,ddebug;
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
inline double Sqrt(double x)
{
    if (sign(x)==0)
        return(0);
    return(sqrt(x));
}
inline double Asin(double x)
{
    if (sign(x-1)==0)
        return(asin(1.0));
    if (sign(x+1)==0)
        return(asin(-1.0));
    return(asin(x));
}
inline double dot(const point &a,const point &b)
{
    return(a.x*b.x+a.y*b.y);
}
inline double det(const point &a,const point &b)
{
    return(a.x*b.y-a.y*b.x);
}
inline double sqr(double x)
{
    return(x*x);
}
inline double dist(const point &a,const point &b)
{
    return(sqrt(sqr(a.x-b.x)+sqr(a.y-b.y)));
}
inline int side(const point &p,const point &a,const point &b)
{
    return(sign(det(b-a,p-a)));
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
inline double ptoline(const point &p,const point &a,const point &b)
{
    point tmp=project(p,a,b);
    if (sign(dot(tmp-a,tmp-b))<=0)
        return(dist(p,tmp));
    return(min(dist(p,a),dist(p,b)));
}
inline point intersect(const point &o1,double r1,const point &o2,double r2)
{
    double d=dist(o1,o2);
    double x=(sqr(r1)-sqr(r2))/(2*d)+d/2;
    double l=Sqrt(sqr(r1)-sqr(x));
    point dir=(o2-o1).unit();
    return(o1+dir*x+dir.rotate()*l);
}
inline void intersect(const point &a,const point &b,const point &o,double r,point &p1,point &p2)
{
    point p=project(o,a,b);
    double d=dist(o,p);
    double l=Sqrt(sqr(r)-sqr(d));
    point dir=(b-a).unit();
    p1=p-dir*l;
    p2=p+dir*l;
}
inline point tangent(const point &p,const point &o,double r)
{
    return(intersect((p+o)/2,dist(p,o)/2,o,r));
}
inline double angle(double d,double r)
{
    return(Asin(d/2/r)*2);
}
inline double calc(const point &p,const point &now,const point &b,const point &o,double r,double t)
{
    point dir=(now-o).unit();
    point q=o+dir*r;
    double theta=angle(t,r);
    double dis=angle(dist(p,q),r);
    double delta=fmod(dis,theta);
    return(sin(delta/2)*r*2+(dis-delta)/theta*t+dist(b,q));
}
inline double calc(const point &now,const point &q,const point &v,const point &a,const point &b,const point &o,double r,double t)
{
    point dir=(now-o).unit();
    point p=o+dir*r;
    double L=0,R=1;
    for (int T=1;T<=100;T++)
    {
        double lx=(2*L+R)/3,rx=(L+2*R)/3;
        double t1=calc(p,v*lx+q*(1-lx),b,o,r,t);
        double t2=calc(p,v*rx+q*(1-rx),b,o,r,t);
        if (t1<t2)
            R=rx;
        else
            L=lx;
    }
    L=(L+R)/2;
    if (debug)
        ddebug=true;
    return(calc(p,v*L+q*(1-L),b,o,r,t)+dist(a,p));
}
int main()
{
    while (1)
    {
        debug=ddebug=false;
        point a,b,o;
        double r,t;
        scanf("%lf%lf%lf%lf%lf%lf%lf%lf",&a.x,&a.y,&b.x,&b.y,&o.x,&o.y,&r,&t);
        if (sign(r)==0)
            break;
        if (sign(ptoline(o,a,b)-r)>=0 || sign(t-2*r)>=0)
        {
            printf("%.10f\n",dist(a,b));
            continue;
        }
        point p=tangent(a,o,r);
        if (side(p,a,b)==side(o,a,b))
            p=reflect(p,a,o);
        point q=tangent(b,o,r);
        if (side(q,a,b)!=side(p,a,b))
            q=reflect(q,b,o);
        if (sign(t)==0)
        {
            printf("%.10f\n",dist(a,p)+dist(b,q)+angle(dist(p,q),r)*r);
            continue;
        }
        point u,v;
        intersect(a,b,o,r,u,v);
        double L=0,R=1;
        for (int T=1;T<=100;T++)
        {
            double lx=(2*L+R)/3,rx=(L+2*R)/3;
            double t1=calc(u*lx+p*(1-lx),q,v,a,b,o,r,t);
            double t2=calc(u*rx+p*(1-rx),q,v,a,b,o,r,t);
            if (t1<t2)
                R=rx;
            else
                L=lx;
        }
        L=(L+R)/2;
        debug=true;
        printf("%.10f\n",calc(u*L+p*(1-L),q,v,a,b,o,r,t));
    }
    return(0);
}

