#include <cstdio>
#include <cmath>
const int limit=10000000;
double ln[limit+10];
void init()
{
    for (int i=1;i<=limit;i++)
        ln[i]=log(double(i));
}
int main()
{
    init();
    int T;
    scanf("%d",&T);
    while (T--)
    {
        double x,ans=0;
        scanf("%lf",&x);
        for (int i=1;i<=limit;i++)
            ans+=ln[i]/pow(double(i),x);
        printf("%.10f\n",ans);
    }
    return(0);
}

