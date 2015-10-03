#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
ll a[1010];
int main()
{
    int T;
    scanf("%d",&T);
    while (T--)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        a[x]+=y;
        ll sum=0,ans=0;
        for (int i=1000;i;i--)
        {
            sum+=a[i];
            ans=max(ans,sum*i);
        }
        printf("%lld\n",ans);
    }
    return(0);
}

