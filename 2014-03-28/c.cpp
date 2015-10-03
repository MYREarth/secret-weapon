#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
const double eps=1e-8,PI=acos(-1.0);
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
inline point operator -(const point &a,const point &b)
{
    return(point(a.x-b.x,a.y-b.y));
}
inline int sign(double x)
{
    return(x<-eps?-1:x>eps);
}
inline double dot(const point &a,const point &b)
{
    return(a.x*b.x+a.y*b.y);
}
inline double cross(const point &a,const point &b)
{
    return(a.x*b.y-a.y*b.x);
}
double r;
int n;
point info[100];
double area2(point pa,point pb)
{
    if (pa.len()<pb.len())
        swap(pa,pb);
    if (pb.len()<eps)
        return(0);
    double a=pb.len();
    double b=pa.len();
    double c=(pb-pa).len();
    double cosB=dot(pb,pb-pa)/a/c;
    double B=acos(cosB);
    double cosC=dot(pa,pb)/a/b;
    double C=acos(cosC),S;
    if (a>r)
    {
        S=C/2*r*r;
        double h=a*b*sin(C)/c;
        if (h<r && B<PI/2)
            S-=acos(h/r)*r*r-h*sqrt(r*r-h*h);
    }
    else if (b>r)
    {
        double theta=PI-B-asin(sin(B)/r*a);
        S=0.5*a*r*sin(theta)+(C-theta)/2*r*r;
    }
    else
        S=0.5*sin(C)*a*b;
    return(S);
}
double area()
{
    double S=0;
    info[n]=info[0];
    for (int i=0;i<n;i++)
        S+=area2(info[i],info[i+1])*sign(cross(info[i],info[i+1]));
    return(fabs(S));
}
int main()
{
    freopen("intersection.in","r",stdin);
    freopen("intersection.out","w",stdout);
    double x0,y0;
    scanf("%lf%lf%lf%d",&x0,&y0,&r,&n);
    for (int i=0;i<n;i++)
    {
        double x,y;
        scanf("%lf%lf",&x,&y);
        info[i]=point(x-x0,y-y0);
    }
    printf("%.10f\n",area());
    return(0);
}

