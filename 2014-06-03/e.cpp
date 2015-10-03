#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
struct point
{
    double x,y;
    point(){}
    point(double x,double y):x(x),y(y){}
    double len() const
    {
        return(sqrt(x*x+y*y));
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
inline point project(const point &p,const point &a,const point &b)
{
    double t=dot(p-a,b-a)/dot(b-a,b-a);
    return(a+(b-a)*t);
}
inline double solve(double a,double b,double c)
{
    double delta=sqr(b)-4*a*c;
    double x=(-b-sqrt(delta))/(2*a);
    if (sign(x)>=0)
        return(x);
    return((-b+sqrt(delta))/(2*a));
}
point a[20],v[20];
double V,ans;
int n,c[20];
int main()
{
    int T;
    scanf("%d",&T);
    while (T--)
    {
        point o;
        scanf("%lf%lf%lf%d",&o.x,&o.y,&V,&n);
        for (int i=1;i<=n;i++)
        {
            scanf("%lf%lf%lf%lf",&a[i].x,&a[i].y,&v[i].x,&v[i].y);
            c[i]=i;
        }
        ans=1e100;
        while (1)
        {
            double tot=0;
            point now=o;
            for (int i=1;i<=n;i++)
            {
                int x=c[i];
                point F=a[x]+v[x]*tot;
                point tmp=project(now,F,F+v[x]);
                double H=dist(now,tmp),A=dist(F,tmp)*sign(dot(v[x],F-tmp));
                double t=solve(sqr(v[x].len())-sqr(V),2*v[x].len()*A,sqr(A)+sqr(H));
                now=F+v[x]*t;
                tot+=t;
            }
            ans=min(ans,tot);
            if (!next_permutation(c+1,c+n+1))
                break;
        }
        printf("%.20f\n",ans);
    }
    return(0);
}

