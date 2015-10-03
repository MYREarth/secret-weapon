#include <cstdio>
#include <cmath>
const double pi=acos(-1.0);
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
inline double area(const point &pa,const point &pb,double r)
{
    if (pa.len()<pb.len())
        return(area(pb,pa,r));
    if (sign(pb.len())==0)
        return(0);
    double a=pb.len();
    double b=pa.len();
    double c=(pb-pa).len();
    double cosB=dot(pb,pb-pa)/a/c;
    double B=acos(cosB);
    double cosC=dot(pa,pb)/a/b;
    double C=acos(cosC);
    double S;
    if (a>r)
    {
        S=C/2*r*r;
        double h=a*b*sin(C)/c;
        if (h<r && B<pi/2)
            S-=acos(h/r)*r*r-h*sqrt(r*r-h*h);
    }
    else if (b>r)
    {
        double theta=pi-B-asin(sin(B)/r*a);
        S=0.5*a*r*sin(theta)+(C-theta)/2*r*r;
    }
    else
        S=0.5*sin(C)*a*b;
    return(S);
}
point a[110];
int main()
{
    int n;
    double r;
    scanf("%d%lf",&n,&r);
    for (int i=1;i<=n;i++)
        scanf("%lf%lf",&a[i].x,&a[i].y);
    a[0]=a[n];
    double S=0;
    for (int i=1;i<=n;i++)
        S+=area(a[i-1],a[i],r)*sign(det(a[i-1],a[i]));
    printf("%.10f\n",fabs(S));
}

