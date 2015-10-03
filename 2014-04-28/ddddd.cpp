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
double a[40],area[40][40],triangle[40][40][40],g[40][40][40],left[40][40][40],right[40][40][40];
point p[40];
bool ok[40][40][40][2],f[40][40][40][2];
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
            {
                g[i][j][k]=1e100;
                for (int l=0;l<2;l++)
                    ok[i][j][k][l]=f[i][j][k][l]=false;
            }
        g[i][i][0]=0;
    }
    for (int i=1;i<=n;i++)
        for (int _=0;_<n;_++)
        {
            int j=next(i,_);
            for (int k=0;k<m;k++)
                for (int l=next(j);l!=i;l=next(l))
                {
                    if (area[j][l]>=mid)
                        g[i][l][k+1]=min(g[i][l][k+1],g[i][j][k]+area[j][l]);
                    if (area[l][j]-g[i][j][k]>=mid)
                        ok[l][j][k][0]=true;
                    if (area[i][l]-g[i][j][k]>=mid)
                        ok[i][l][k][1]=true;
                }
        }
    for (int i=1;i<=n;i++)
        for (int k=0;k<=m;k++)
        {
            left[i][i][k]=right[i][i][k]=g[i][i][k];
            for (int j=next(i);j!=i;j=next(j))
                left[i][j][k]=min(left[i][prev(j)][k],g[i][j][k]);
            for (int j=prev(i);j!=i;j=prev(j))
                right[j][i][k]=min(right[next(j)][i][k],g[j][i][k]);
        }
    for (int _=1;_<n;_++)
        for (int i=1;i<=n;i++)
        {
            int j=next(i,_);
            for (int k=1;k<=m;k++)
            {
                for (int l=0;l<2;l++)
                    if (ok[i][j][k-1][l])
                        f[i][j][k][l]=true;
                if (k>=2)
                    for (int l=next(i);l!=j;l=next(l))
                    {
                        if (area[l][j]>=mid && area[i][l]+triangle[i][j][l]-right[next(i)][l][k-2]>=mid)
                            f[i][j][k][0]=true;
                        if (area[i][l]>=mid && area[l][j]+triangle[i][j][l]-left[l][prev(j)][k-2]>=mid)
                            f[i][j][k][1]=true;
                    }
                if (f[i][j][k][0])
                {
                    if (ok[j][i][m-k][1])
                        return(true);
                    if (k==m)
                        continue;
                    for (int l=next(j);l!=i;l=next(l))
                    {
                        double now=area[j][l]+triangle[i][j][l];
                        if (now>=mid)
                            f[i][l][k+1][1]=true;
                        if (area[l][i]>=mid && now-right[next(j)][l][m-k-1]>=mid)
                            return(true);
                    }
                }
                if (f[i][j][k][1])
                {
                    if (ok[j][i][m-k][0])
                        return(true);
                    if (k==m)
                        continue;
                    for (int l=next(j);l!=i;l=next(l))
                    {
                        double now=area[l][i]+triangle[i][j][l];
                        if (now>=mid)
                            f[l][j][k+1][0]=true;
                        if (area[j][l]>=mid && now-left[l][prev(i)][m-k-1]>=mid)
                            return(true);
                    }
                }
            }
        }
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

