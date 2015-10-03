#include <cstdio>
#include <algorithm>
using namespace std;
struct point
{
    double x,y;
    point(){}
    point(double x,double y):x(x),y(y){}
};
inline point operator -(const point &a,const point &b)
{
    return(point(a.x-b.x,a.y-b.y));
}
inline int sign(double x,double eps=1e-8)
{
    return(x<-eps?-1:x>eps);
}
inline bool operator <(const point &a,const point &b)
{
    return(sign(a.x-b.x)<0 || sign(a.x-b.x)==0 && sign(a.y-b.y)<0);
}
inline double det(const point &a,const point &b)
{
    return(a.x*b.y-a.y*b.x);
}
inline bool convex(int n,double *X,double *Y)
{
    static point a[10010],b[10010];
    for (int i=1;i<=n;i++)
        a[i]=point(X[i],Y[i]);
    sort(a+1,a+n+1);
    int m=0;
    for (int i=1;i<=n;i++)
    {
        while (m>=2 && sign(det(b[m]-b[m-1],a[i]-b[m]))<0)
            m--;
        b[++m]=a[i];
    }
    int limit=m;
    for (int i=n-1;i;i--)
    {
        while (m>limit && sign(det(b[m]-b[m-1],a[i]-b[m]))<0)
            m--;
        b[++m]=a[i];
    }
    return(n+1==m);
}
double X[10010],Y[10010];
double ansx[10010],ansy[10010];
int main()
{
    freopen("polygon.in","r",stdin);
    freopen("polygon.out","w",stdout);
    int n;
    scanf("%d",&n);
    for (int i=1;i<=n;i++)
        scanf("%lf%lf",&X[i],&Y[i]);
    double cx=0,cy=0;
    for (int i=1;i<=n;i++)
    {
        double dx=cx-X[i],dy=cy-Y[i];
        cx=X[i]-dy;
        cy=Y[i]+dx;
    }
    bool flag=convex(n,X,Y);
    X[0]=X[n],Y[0]=Y[n];
    X[n+1]=X[1],Y[n+1]=Y[1];
    for (int i=1;i<=n;i++)
    {
        double x1=X[i]-X[i-1],y1=Y[i]-Y[i-1],x2=X[i+1]-X[i],y2=Y[i+1]-Y[i];
        if (sign(x1*y2-x2*y1)>0)
        {
            flag=false;
            break;
        }
    }
    if (!flag)
        printf("-2\n");
    else
    {
        double a1,b1,c1,a2,b2,c2;
        a1=b1=c1=a2=b2=c2=0;
        if (n%4==0)
            a1=1,b2=1;
        else if (n%4==1)
            b1=-1,a2=1;
        else if (n%4==2)
            a1=-1,b2=-1;
        else
            b1=1,a2=-1;
        a1--,b2--;
        c1=-cx,c2=-cy;
        if (sign(a1*b2-a2*b1)==0)
            printf("%d\n",sign(c1*b2-c2*b1)==0 && sign(c1*a2-c2*a1)==0?-1:-2);
        else
        {
            ansx[1]=(c1*b2-c2*b1)/(a1*b2-a2*b1);
            ansy[1]=(c1*a2-c2*a1)/(b1*a2-b2*a1);
            for (int i=1;i<n;i++)
            {
                double dx=ansx[i]-X[i],dy=ansy[i]-Y[i];
                ansx[i+1]=X[i]-dy;
                ansy[i+1]=Y[i]+dx;
            }
            bool flag=convex(n,ansx,ansy);
            ansx[0]=ansx[n],ansy[0]=ansy[n];
            ansx[n+1]=ansx[1],ansy[n+1]=ansy[1];
            for (int i=1;i<=n;i++)
            {
                double x1=ansx[i]-ansx[i-1],y1=ansy[i]-ansy[i-1],x2=ansx[i+1]-ansx[i],y2=ansy[i+1]-ansy[i];
                if (sign(x1*y2-x2*y1)>0)
                {
                    flag=false;
                    break;
                }
            }
            if (flag)
            {
                printf("%d\n",n);
                for (int i=1;i<=n;i++)
                    printf("%.10f %.10f\n",ansx[i],ansy[i]);
            }
            else
                printf("-2\n");
        }
    }
    return(0);
}

