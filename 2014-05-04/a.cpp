#include <cstdio>
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
ll work()
{
    int a,b,p,K;
    scanf("%d%d%d%d",&a,&b,&p,&K);
    mod=1;
    for (int i=1;i<=K;i++)
        mod*=p;
    for (int i=1;i<=100;i++)
        if ((power(a,i)+power(b,i))%mod==0)
            return(i);
    ll phi=mod/p*(p-1);
    for (int i=1;i<p;i++)
    {
        if ((p-1)%i!=0)
            continue;
        ll now=i;
        for (int j=0;j<K;j++)
        {
            ll tmp=now;
            while (1)
            {
                if ((power(a,tmp)+power(b,tmp))%mod==0)
                    return(tmp);
                tmp<<=1;
                if (tmp>phi)
                    break;
            }
            now*=p;
        }
    }
    return(-1);
}
int main()
{
    printf("%lld\n",work());
    return(0);
}

