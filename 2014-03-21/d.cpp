#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
int main()
{
    freopen("estimate.in","r",stdin);
    freopen("estimate.out","w",stdout);
    int T;
    scanf("%d",&T);
    while (T--)
    {
        int n;
        scanf("%d",&n);
        double a[20],ave=0;
        for (int i=1;i<=n;i++)
        {
            scanf("%lf",&a[i]);
            ave+=a[i];
        }
        ave/=n;
        sort(a+1,a+n+1);
        double nhb = a[n] * (1 + 0.68 / n);
        nhb = min(nhb, 990.0);
        printf("%.10f\n", nhb);
        /*
        double sum=0;
        for (int i=1;i<=n;i++)
            sum+=a[i]/i*(n+1);
        printf("%.10f\n",a[n]/n*(n+1));
 //       printf("%.10f\n",a[n]);
 //       */
        /*
        a[0]=0;
        double sum=0;
        int tot=0;
        for (int i=0;i<=n;i++)
            for (int j=i+1;j<=n;j++)
            {
                sum+=a[j]-a[i];
                tot+=j-i;
            }
        printf("%.10f\n",sum/tot*(n+1));
        */
    }
    return(0);
}

