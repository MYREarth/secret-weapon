#include <cstdio>
#include <cstdlib>
#include <cmath>
typedef long long ll;
const int N=1000000;
bool f[N+10];
int m,p[N+10],ma[N+10];
void init()
{
    int n=N;
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
bool check(ll x,int K)
{
    for (int i=1;i<=K && x>N;i++)
        while (x%p[i]==0)
            x/=p[i];
    return(x<=N && ma[x]<=p[K]);
}
int main()
{
    //freopen("coin.in","r",stdin);
    //freopen("coin.out","w",stdout);
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
 //           printf("%d\n",i);
            if (--m==0)
                break;
        }
    }
    return(0);
}

