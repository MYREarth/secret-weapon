#include <cstdio>
#include <cmath>
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
bool check(ll x,int K)
{
    for (int i=1;i<=K;i++)
    {
        if (x==1)
            break;
        while (x%p[i]==0)
            x/=p[i];
    }
    return(x==1);
}
int main()
{
    //freopen("coin.in","r",stdin);
    freopen("coin.out","w",stdout);
    init();
    ll n;
    int m,K;
    scanf("%lld%d%d",&n,&m,&K);
    int x=int(sqrt(double(n))+1e-8);
    for (int i=1;;i++)
    {
        ll p=ll(x+i)*(x+i)%n;
        if (check(p,K))
        {
            printf("%lld%c",p,m==1?'\n':' ');
            if (--m==0)
                break;
        }
    }
    return(0);
}

