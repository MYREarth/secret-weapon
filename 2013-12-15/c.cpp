#include <cstdio>
#include <cstdlib>
#include <cmath>
typedef long long ll;
bool f[1000010];
int m,p[1000010],ma[1000010];
void init()
{
    int n=1000000;
    for (int i=2;i<=n/2;i++)
    {
        if (f[i])
            continue;
        for (int j=2;i*j<=n;j++)
        {
            ma[i*j]=i;
            f[i*j]=true;
        }
    }
    ma[1]=1;
    for (int i=2;i<=n;i++)
        if (!f[i])
        {
            p[++m]=i;
            ma[i]=i;
        }
}
const int N=2600000;
ll ans[N+10],a[N+10];
void calc(int p)
{
    for (int i=1;i<=p;i++)
        if (a[i]%p==0)
            for (int j=i;j<=N;j+=p)
                while (a[j]%p==0)
                    a[j]/=p;
}
int main()
{
    freopen("coin.in","r",stdin);
    freopen("coin.out","w",stdout);
    init();
    ll n;
    int m,K;
    scanf("%lld%d%d",&n,&m,&K);
    int x=int(sqrt(double(n))+1e-8);
    for (int i=1;i<=N;i++)
        ans[i]=a[i]=ll(x+i)*(x+i)%n;
    for (int i=1;i<=K;i++)
        calc(p[i]);
    for (int i=1;i<=N;i++)
        if (a[i]==1)
        {
            printf("%lld%c",ans[i],m==1?'\n':' ');
            if (--m==0)
                break;
        }
    return(0);
}

