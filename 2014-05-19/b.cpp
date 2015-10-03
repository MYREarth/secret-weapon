#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
typedef long long ll;
const ll limit=10000000000LL;
const int TWO=1024,FIVE=9765625,phi2=512,phi5=7812500;
bool force(ll n,ll m)
{
    ll now=1;
    for (int i=1;i<=m;i++)
    {
        now=ll(now)*(n-i+1)/i;
        if (now>=limit)
            return(false);
    }
    printf("%lld\n",now);
    return(true);
}
int two[1100],inv2[1100],five[10000000],inv5[10000000],div[10000000];
int power(int x,ll y,int mod)
{
    int ret=1;
    for (;y;y>>=1)
    {
        if (y&1)
            ret=ll(ret)*x%mod;
        x=ll(x)*x%mod;
    }
    return(ret);
}
void init(int fac[],int inv[],int mod,int phi,int p)
{
    fac[0]=1;
    for (int i=1;i<=mod;i++)
    {
        fac[i]=fac[i-1];
        if (i%p!=0)
            fac[i]=ll(fac[i])*i%mod;
    }
    vector <int> ps;
    memset(div,-1,sizeof(div));
    for (int i=2;i<=mod;i++)
    {
        if (div[i]==-1)
            ps.push_back(i);
        for (int j=0;j<ps.size() && i*ps[j]<=mod;j++)
        {
            div[i*ps[j]]=ps[j];
            if (i%ps[j]==0)
                break;
        }
    }
    inv[0]=inv[1]=1;
    for (int i=2;i<=mod;i++)
    {
        if (div[i]==-1)
            inv[i]=power(i,phi-1,mod);
        else
            inv[i]=(ll)inv[i/div[i]]*inv[div[i]]%mod;
    }
    for (int i=2;i<=mod;i++)
    {
        if (i%p==0)
            inv[i]=1;
        inv[i]=(ll)inv[i-1]*inv[i]%mod;
    }
}
ll calc(ll n,int p)
{
    ll ret=0;
    while (n)
    {
        ret+=n/p;
        n/=p;
    }
    return(ret);
}
int calc(ll n,int a[],int mod,int p)
{
    if (n==0)
        return(1);
    ll cnt=n/mod;
    int ret=power(a[mod],cnt,mod);
    ret=ll(ret)*a[n%mod]%mod;
    return(ll(ret)*calc(n/p,a,mod,p)%mod);
}
ll mulmod(ll x,ll y,ll mod)
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
ll Power(ll x,ll y,ll mod)
{
    ll ret=1;
    for (;y;y>>=1)
    {
        if (y&1)
            ret=mulmod(ret,x,mod);
        x=mulmod(x,x,mod);
    }
    return(ret);
}
ll CRT(int mod2,int mod5)
{
    ll ans2=mulmod(mulmod(mod2,FIVE,limit),Power(FIVE,phi2-1,limit),limit);
    ll ans5=mulmod(mulmod(mod5,TWO,limit),Power(TWO,phi5-1,limit),limit);
    return((ans2+ans5)%limit);
}
int main()
{
    freopen("combi.in","r",stdin);
    freopen("combi.out","w",stdout);
    ll n,m;
    scanf("%lld%lld",&n,&m);
    if (n-m<m)
        m=n-m;
    if (!force(n,m))
    {
        init(two,inv2,TWO,phi2,2);
        init(five,inv5,FIVE,phi5,5);
        ll c2=calc(n,2)-calc(m,2)-calc(n-m,2);
        int mod2=ll(calc(n,two,TWO,2))*calc(m,inv2,TWO,2)%TWO*calc(n-m,inv2,TWO,2)%TWO*power(2,c2,TWO)%TWO;
        ll c5=calc(n,5)-calc(m,5)-calc(n-m,5);
        int mod5=ll(calc(n,five,FIVE,5))*calc(m,inv5,FIVE,5)%FIVE*calc(n-m,inv5,FIVE,5)%FIVE*power(5,c5,FIVE)%FIVE;
        printf("...%010lld\n",CRT(mod2,mod5));
    }
    return(0);
}

