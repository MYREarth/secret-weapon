#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
const double pi=acos(-1.0);
struct point
{
    double x,y;
    point(double x,double y):x(x),y(y){}
};
inline double det(const point &a,const point &b)
{
    return(a.x*b.y-a.y*b.x);
}
inline point get(double x)
{
    return(point(cos(x),sin(x)));
}
double a[70],f[70][40],area[70][70];
bool check(int n,int m,double mid)
{
    for (int i=1;i<=n;i++)
    {
        for (int j=2;j<=m;j++)
            f[i][j]=1e100;
        f[i][1]=0;
    }
    for (int i=1;i<=n;i++)
        for (int j=1;j<m;j++)
            for (int k=i+1;k<=n;k++)
            {
                if (area[i][k]<mid)
                    continue;
                f[k][j+1]=min(f[k][j+1],f[i][j]+area[i][k]);
            }
    for (int i=1;i<=n;i++)
        if (pi-f[i][m]>=mid)
            return(true);
    return(false);
}
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    for (int i=1;i<=n;i++)
    {
        int x;
        scanf("%d",&x);
        a[i]=x/180.0*pi;
        a[i+n]=a[i]+2*pi;
    }
    n<<=1;
    for (int i=1;i<=n;i++)
        for (int j=i+1;j<=n;j++)
            area[i][j]=(a[j]-a[i])/2-det(get(a[i]),get(a[j]))/2;
    printf("%.10f\n",area[1][2]);
    double l=0,r=pi;
    for (int T=1;T<=100;T++)
    {
        double mid=(l+r)/2;
        if (check(n,m,mid))
            l=mid;
        else
            r=mid;
    }
    printf("%.10f\n",(l+r)/2);
    return(0);
}

