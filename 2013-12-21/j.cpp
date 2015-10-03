#include <cstdio>
typedef long long ll;
bool f[1000010];
int m,p[1000010];
void init()
{
    int n=1000000;
    for (int i=2;i*i<=n;i++)
    {
        if (f[i])
            continue;
        for (int j=i;i*j<=n;j++)
            f[i*j]=true;
    }
    for (int i=2;i<=n;i++)
        if (!f[i])
            p[++m]=i;
}
ll calc(ll n)
{
    if (n==0)
        return(1);
    ll ret=1;
    for (int i=1;i<=m;i++)
    {
        int now=0;
        while (n%p[i]==0)
        {
            now++;
            n/=p[i];
        }
        ret*=(now+1);
        if (n==1)
            break;
    }
    if (n!=1)
        ret*=2;
    return(ret);
}
int main()
{
    freopen("job.in","r",stdin);
    freopen("job.out","w",stdout);
    init();
    ll n,ans=0;
    scanf("%lld",&n);
    for (int i=1;ll(i)*i<=n;i++)
    {
        if (n%i!=0)
            continue;
        ans+=calc(i-1);
        if (n/i!=i)
            ans+=calc(n/i-1);
    }
    printf("%lld\n",ans);
    return(0);
}

