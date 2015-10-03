#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
int limit=1000000;
int main()
{
    int n,K;
    scanf("%d%d",&n,&K);
    if (K==1)
        printf("%lld\n",ll(n)*(n+1)/2);
    else
    {
        double div=1,ans=0;
        for (int i=0;i<=min(n,limit);i+=2)
        {
            ans+=(n-i)/div;
            div*=K;
        }
        div=K;
        for (int i=1;i<=min(n,limit);i+=2)
        {
            ans+=(n-i)/div;
            div*=K;
        }
        printf("%.10f\n",ans);
    }
    return(0);
}

