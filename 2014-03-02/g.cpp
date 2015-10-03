#include <cstdio>
typedef long long ll;
typedef long double ld;
ll p,mod,ans,a[30];
int n;
ll mulmod(ll x,ll y)
{
    ll d=ll(ld(x)*y/mod);
    d=x*y-mod*d;
    while (d<0)
        d+=mod;
    while (d>=mod)
        d-=mod;
    return(d);
}
ll inverse(ll a,ll mod)
{
    return(a==1?1:mulmod(mod-mod/a,inverse(mod%a,mod)));
}
void update(ll c1,ll c2)
{
    ll now=ll(c1)*p+c2;
    if (ans==-1 || now<ans)
        ans=now;
}
void calc(ll d)
{
    ll c1=0,c2=a[n];
    for (int i=n-1;i>=0;i--)
    {
        ll t1=(mulmod(c1,d)+mulmod(c2,p))%mod,t2=mulmod(c2,d);
        c1=t1,c2=(t2+a[i])%mod;
    }
    c2=(mod-c2)%mod;
    if (c1==0)
    {
        if (c2==0)
            update(0,d);
        return;
    }
    if (c1%p==0)
    {
        if (c2%p==0)
            update(mulmod(inverse(c1/p,p),c2/p)%p,d);
        return;
    }
    update(mulmod(inverse(c1,mod),c2),d);
}
int main()
{
    scanf("%lld%d",&p,&n);
    mod=ll(p)*p;
    for (int i=n;i>=0;i--)
    {
        scanf("%lld",&a[i]);
        a[i]=(a[i]+mod)%mod;
    }
    ans=-1;
    for (int i=0;i<p;i++)
        calc(i);
    printf("%lld\n",ans);
    return(0);
}

