#include <cstdio>
#include <cmath>
#include <algorithm>
#define y0 __y0__
#define y1 __y1__
using namespace std;
const double pi=acos(-1.0);
struct point
{
    double x,y;
    point(){}
    point(double x,double y):x(x),y(y){}
    point rotate(double t) const
    {
        return(point(x*cos(t)-y*sin(t),x*sin(t)+y*cos(t)));
    }
};
point a[100010];
double x0,x1,y0,y1;
bool calc(double angle,int n)
{
    x0=y0=1e100;
    x1=y1=-1e100;
    for (int i=1;i<=n;i++)
    {
        point p=a[i].rotate(angle);
        x0=min(x0,p.x);
        y0=min(y0,p.y);
        x1=max(x1,p.x);
        y1=max(y1,p.y);
    }
    return((x1-x0)<(y1-y0));
}
int main()
{
    freopen("garden.in","r",stdin);
    int T;
    scanf("%d",&T);
    while (T--)
    {
        int n;
        scanf("%d",&n);
        for (int i=1;i<=n;i++)
            scanf("%lf%lf",&a[i].x,&a[i].y);
        double l=0,r=pi/2;
        bool state=calc(l,n);
        for (int _=1;_<=100;_++)
        {
            double mid=(l+r)/2;
            if (calc(mid,n)==state)
                l=mid;
            else
                r=mid;
        }
        double ans=(l+r)/2;
        calc(ans,n);
        point p=point(x0,y0).rotate(-ans);
        printf("%.10f %.10f\n",p.x,p.y);
        p=point(x1,y0).rotate(-ans);
        printf("%.10f %.10f\n",p.x,p.y);
        p=point(x1,y1).rotate(-ans);
        printf("%.10f %.10f\n",p.x,p.y);
        p=point(x0,y1).rotate(-ans);
        printf("%.10f %.10f\n",p.x,p.y);
    }
    return(0);
}

