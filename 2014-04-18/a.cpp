#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
const double pi=acos(-1.0);
int a[1010];
int main()
{
    int n,r;
    scanf("%d%d",&n,&r);
    for (int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    sort(a+1,a+n+1);
    double ans=pi*r*r*n;
    for (int i=2;i<=n;i++)
    {
        if (a[i]-a[i-1]>=2*r)
            continue;
        double d=(a[i]-a[i-1])/2.0;
        double l=sqrt(double(r*r-d*d));
        double theta=atan(l/d);
        ans-=(r*r*theta-l*d)*2;
    }
    printf("%.10f\n",ans);
    return(0);
}

