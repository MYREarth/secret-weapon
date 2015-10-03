#include <cstdio>
#include <algorithm>
using namespace std;
int a[100010],v[100010];
double calc(double t,int n)
{
    double mi=1e100,ma=-1e100;
    for (int i=1;i<=n;i++)
    {
        double now=a[i]+v[i]*t;
        mi=min(mi,now);
        ma=max(ma,now);
    }
    return(ma-mi);
}
int main()
{
    while (1)
    {
        int n;
        scanf("%d",&n);
        if (n==0)
            break;
        for (int i=1;i<=n;i++)
            scanf("%d%d",&a[i],&v[i]);
        double l=0,r=1e6;
        for (int T=1;T<=100;T++)
        {
            double lx=(2*l+r)/3,rx=(l+2*r)/3;
            if (calc(lx,n)<calc(rx,n))
                r=rx;
            else
                l=lx;
        }
        printf("%.10f\n",calc((l+r)/2,n));
    }
    return(0);
}

