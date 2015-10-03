#include <cstdio>
#include <cmath>
double a[100010];
int main()
{
    int n=100000;
    freopen("estimate.out","r",stdin);
    for (int i=1;i<=n;i++)
        scanf("%lf",&a[i]);
    freopen("estimate.ans","r",stdin);
    double sum=0;
    for (int i=1;i<=n;i++)
    {
        double x;
        scanf("%lf",&x);
        sum+=fabs(a[i]-x);
    }
    printf("%.10f\n",sum/n);
    return(0);
}

