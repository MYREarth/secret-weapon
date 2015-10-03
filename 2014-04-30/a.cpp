#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
ll a[1010];
int main()
{
    int n,D;
    scanf("%d%d",&n,&D);
    for (int i=1;i<=n;i++)
        scanf("%lld",&a[i]);
    bool flag=false;
    for (ll first=a[1]-D;first<=a[1]+D;first++)
    {
        ll lower=-1LL<<60,upper=1LL<<60;
        for (int i=2;i<=n;i++)
        {
            lower=max(lower,(a[i]-D-first+i-2)/(i-1));
            upper=min(upper,(a[i]+D-first)/(i-1));
        }
        if (lower<=upper)
        {
            flag=true;
            for (int i=1;i<=n;i++)
                printf("%lld%c",first+(i-1)*lower,i==n?'\n':' ');
            break;
        }
    }
    if (!flag)
        printf("0\n");
    return(0);
}

