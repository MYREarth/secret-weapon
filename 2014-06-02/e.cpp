#include <cstdio>
struct point
{
    int x,y,z;
    point(){}
    point(int x,int y,int z):x(x),y(y),z(z){}
};
inline point operator -(const point &a,const point &b)
{
    return(point(a.x-b.x,a.y-b.y,a.z-b.z));
}
inline int dot(const point &a,const point &b)
{
    return(a.x*b.x+a.y*b.y+a.z*b.z);
}
inline point det(const point &a,const point &b)
{
    return(point(a.y*b.z-a.z*b.y,a.z*b.x-a.x*b.z,a.x*b.y-a.y*b.x));
}
point a[60];
double p[60];
int main()
{
    int n;
    scanf("%d",&n);
    for (int i=1;i<=n;i++)
        scanf("%lf%d%d%d",&p[i],&a[i].x,&a[i].y,&a[i].z);
    double ans=0;
    for (int i=1;i<=n;i++)
        for (int j=1;j<=n;j++)
        {
            if (i==j)
                continue;
            for (int k=1;k<=n;k++)
            {
                if (i==k || j==k)
                    continue;
                double now=p[i]*p[j]*p[k];
                point dir=det(a[j]-a[i],a[k]-a[i]);
                for (int l=1;l<=n;l++)
                    if (dot(a[l]-a[i],dir)>0)
                        now*=(1-p[l]);
                ans+=now;
            }
        }
    double sum=0,tmp=0;
    for (int i=1;i<=n;i++)
    {
        double now=p[i];
        for (int j=1;j<=n;j++)
        {
            if (i==j)
                continue;
            now*=(1-p[j]);
        }
        tmp+=now;
        sum+=now;
    }
    for (int i=1;i<=n;i++)
        for (int j=i+1;j<=n;j++)
        {
            double now=p[i]*p[j];
            for (int k=1;k<=n;k++)
            {
                if (i==k || j==k)
                    continue;
                now*=(1-p[k]);
            }
            tmp+=now*2;
            sum+=now;
        }
    double now=1;
    for (int i=1;i<=n;i++)
        now*=(1-p[i]);
    sum+=now;
    printf("%.10f\n",ans/6+2*(1-sum)+tmp);
    return(0);
}

