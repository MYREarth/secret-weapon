#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
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
    double l=sqrt(sqr(r1)-sqr(x));
    point dir=(o2-o1).unit();
    return(o1+dir*x+dir.rotate()*l);
}
inline point intersect(const point &a,const point &b,const point &c,const point &d)
{
    double s1=det(b-a,c-a),s2=det(b-a,d-a);
    return((c*s2-d*s1)/(s2-s1));
}
inline point tangent(const point &p,const point &o,double r)
{
    return(intersect((p+o)/2,dist(p,o)/2,o,r));
}
inline bool online(const point &p,const point &a,const point &b)
{
    return(sign(dot(p-a,p-b))<=0 && sign(det(p-a,p-b))==0);
}
inline point incenter(const point &a,const point &b,const point &c)
{
    double A=dist(b,c),B=dist(a,c),C=dist(a,b);
    return((a*A+b*B+c*C)/(A+B+C));
}
inline double ptoline(const point &p,const point &a,const point &b)
{
    return(fabs(det(p-a,b-a))/dist(a,b));
}
point o[5000010];
double r[5000010];
int main()
{
    freopen("circle.in","r",stdin);
    freopen("circle.out","w",stdout);
    double ab,ac,bc,R;
    scanf("%lf%lf%lf%lf",&ab,&ac,&bc,&R);
    point A(0,0),B(ab,0),C=intersect(A,ac,B,bc);
    double theta=fabs((C-A).angle()-(B-A).angle())/2;
    o[1]=point(R/tan(theta),R);
    r[1]=R;
    int n;
    scanf("%d",&n);
    n=min(n,4999998+n%6);
    for (int i=2;i<=n;i++)
        if (i%3==2)
        {
            point tmp=tangent(C,o[i-1],r[i-1]);
            if (online(tmp,A,C))
                tmp=reflect(tmp,o[i-1],C);
            point D=intersect(C,tmp,A,B);
            o[i]=incenter(B,C,D);
            r[i]=ptoline(o[i],B,C);
        }
        else if (i%3==0)
        {
            point tmp=tangent(A,o[i-1],r[i-1]);
            if (online(tmp,A,B))
                tmp=reflect(tmp,o[i-1],A);
            point E=intersect(A,tmp,B,C);
            o[i]=incenter(A,C,E);
            r[i]=ptoline(o[i],A,C);
        }
        else
        {
            point tmp=tangent(B,o[i-1],r[i-1]);
            if (online(tmp,B,C))
                tmp=reflect(tmp,o[i-1],B);
            point F=intersect(B,tmp,A,C);
            o[i]=incenter(A,B,F);
            r[i]=ptoline(o[i],A,B);
        }
    printf("%.10f\n",r[n]);
    return(0);
}

