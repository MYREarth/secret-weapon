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
};
inline point operator -(const point &a,const point &b)
{
    return(point(a.x-b.x,a.y-b.y));
}
inline double det(const point &a,const point &b)
{
    return(a.x*b.y-a.y*b.x);
}
inline point get(double x)
{
    return(point(cos(x),sin(x)));
}
double a[40],area[40][40],triangle[40][40][40],f[40][40][40][2];
point p[40];
int n;
inline int next(int i,int len=1)
{
    return(i+len>n?i+len-n:i+len);
}
inline int prev(int i)
{
    return(next(i,n-1));
}
bool check(int m,double mid)
{
    for (int i=1;i<=n;i++)
    {
        for (int j=1;j<=n;j++)
            for (int k=0;k<=m;k++)
                for (int l=0;l<2;l++)
                    f[i][j][k][l]=1e100;
        f[i][i][0][0]=f[i][i][0][1]=0;
    }
    for (int _=0;_<n;_++)
        for (int i=1;i<=n;i++)
        {
            int j=next(i,_);
            for (int k=0;k<m;k++)
                for (int l=next(j);l!=i;l=next(l))
                {
                    double delta=area[i][j]-f[i][j][k][0];
                    if (area[l][i]>=mid)
                        f[l][j][k+1][0]=min(f[l][j][k+1][0],f[i][j][k][0]+area[l][i]);
                    if (area[j][l]+triangle[i][j][l]+delta>=mid)
                        f[i][l][k+1][1]=min(f[i][l][k+1][1],f[i][j][k][0]+area[j][l]+triangle[i][j][l]+delta);
                    delta=area[i][j]-f[i][j][k][1];
                    if (area[j][l]>=mid)
                        f[i][l][k+1][1]=min(f[i][l][k+1][1],f[i][j][k][1]+area[j][l]);
                    if (area[l][i]+triangle[i][j][l]+delta>=mid)
                        f[l][j][k+1][0]=min(f[l][j][k+1][0],f[i][j][k][1]+area[l][i]+triangle[i][j][l]+delta);
                }
        }
    for (int i=1;i<=n;i++)
        for (int j=1;j<=n;j++)
            if (pi-min(f[i][j][m][0],f[i][j][m][1])>=mid)
                return(true);
    return(false);
}
int main()
{
    int m;
    scanf("%d%d",&n,&m);
    m--;
    for (int i=1;i<=n;i++)
    {
        int x;
        scanf("%d",&x);
        a[i]=x/180.0*pi;
        p[i]=get(a[i]);
    }
    for (int i=1;i<=n;i++)
        for (int j=1;j<=n;j++)
        {
            double l=a[i],r=a[j];
            if (l>r)
                r+=pi*2;
            area[i][j]=(r-l-det(p[i],p[j]))/2;
            for (int k=1;k<=n;k++)
                triangle[i][j][k]=fabs(det(p[j]-p[i],p[k]-p[i]))/2;
        }
    double l=0,r=pi;
    for (int T=1;T<=100;T++)
    {
        double mid=(l+r)/2;
        if (check(m,mid))
            l=mid;
        else
            r=mid;
    }
    printf("%.10f\n",(l+r)/2);
    return(0);
}

