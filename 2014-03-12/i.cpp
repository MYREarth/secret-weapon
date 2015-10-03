#include <cstdio>
#include <cmath>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
int a[10];
ll calc(ll x)
{
    memset(a,0,sizeof(a));
    vector <int> b;
    if (x==0)
        a[0]++;
    while (x)
    {
        b.push_back(x%10);
        a[x%10]++;
        x/=10;
    }
    sort(b.begin(),b.end());
    reverse(b.begin(),b.end());
    ll ret=0;
    for (int i=0;i<b.size();i++)
        ret=ret*10+b[i];
    return(ret);
}
bool check(ll x)
{
    if (x==0)
        return(a[0]>0);
    int b[10]={0};
    while (x)
    {
        int t=x%10;
        if (++b[t]>a[t])
            return(false);
        x/=10;
    }
    return(true);
}
int main()
{
    freopen("interesting.in","r",stdin);
    freopen("interesting.out","w",stdout);
    while (1)
    {
        ll n;
        scanf("%lld",&n);
        if (n==0)
            break;
        int limit=sqrt(double(calc(n)))+3;
        printf("Hidden squares in %lld\n",n);
        for (int i=0;i<=limit;i++)
            if (check(ll(i)*i) && check(i))
                printf("%d * %d = %lld\n",i,i,ll(i)*i);
        printf("\n");
    }
    return(0);
}

