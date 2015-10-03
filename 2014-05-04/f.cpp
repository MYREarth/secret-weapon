#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
ll mod;
ll mulmod(ll x,ll y)
{
    ll ret=0;
    for (;y;y>>=1)
    {
        if (y&1)
            ret=(ret+x)%mod;
        x=(x+x)%mod;
    }
    return(ret);
}
ll power(ll x,ll y)
{
    ll ret=1;
    for (;y;y>>=1)
    {
        if (y&1)
            ret=mulmod(ret,x);
        x=mulmod(x,x);
    }
    return(ret);
}
ll a[70],w[70];
bool use[70];
int main()
{
    while (1)
    {
        int n;
        ll r;
        scanf("%d%lld%lld",&n,&mod,&r);
        if (n==0 && mod==0 && r==0)
            break;
        r=power(r,mod-2);
        for (int i=1;i<=n;i++)
        {
            scanf("%lld",&w[i]);
            a[i]=mulmod(w[i],r);
        }
        ll c;
        scanf("%lld",&c);
        c=mulmod(c,r);
        for (int i=n;i;i--)
            if (c>=a[i])
            {
                use[i]=true;
                c-=a[i];
            }
            else
                use[i]=false;
        vector <ll> ans;
        for (int i=1;i<=n;i++)
            if (use[i])
                ans.push_back(w[i]);
        sort(ans.begin(),ans.end());
        for (int i=0;i<ans.size();i++)
            printf("%lld%c",ans[i],i+1==ans.size()?'\n':' ');
    }
    return(0);
}

