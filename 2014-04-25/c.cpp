#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N=100010;
int Log[N];
ll f[17][N];
ll gcd(int x,int y)
{
    int t=Log[y-x+1];
    return(__gcd(f[t][x],f[t][y-(1<<t)+1]));
}
ll calc(int left,int right)
{
    ll ret=0;
    while (1)
    {
        ll value=gcd(left,right);
        int l=1,r=left,ans=-1;
        while (l<=r)
        {
            int mid=l+r>>1;
            if (gcd(mid,right)==value)
                ans=mid,r=mid-1;
            else
                l=mid+1;
        }
        int len=right-ans+1;
        ret=max(ret,gcd(ans,right)*len);
        if (ans==1)
            break;
        left=max(1,ans-len);
    }
    return(ret);
}
int main()
{
    Log[1]=0;
    for (int i=2;i<=100000;i++)
    {
        Log[i]=Log[i-1];
        if (i&i-1)
            continue;
        Log[i]++;
    }
    int T;
    scanf("%d",&T);
    while (T--)
    {
        int n;
        scanf("%d",&n);
        ll ans=0;
        for (int i=1;i<=n;i++)
        {
            scanf("%lld",&f[0][i]);
            ans=max(ans,f[0][i]);
        }
        for (int i=1;i<=Log[n];i++)
            for (int j=1;j<=n;j++)
            {
                if (j+(1<<i)-1>n)
                    break;
                f[i][j]=__gcd(f[i-1][j],f[i-1][j+(1<<i-1)]);
            }
        for (int i=2;i<=n;i++)
            ans=max(ans,calc(i-1,i));
        printf("%lld\n",ans);
    }
    return(0);
}

