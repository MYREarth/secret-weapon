#include <cstdio>
typedef long long ll;
int t[40],p[40];
ll l[66000],r[66000];
int main()
{
    freopen("bit-permutation.in","r",stdin);
    freopen("bit-permutation.out","w",stdout);
    unsigned n,a,c,s;
    scanf("%d%d%d%d",&n,&a,&c,&s);
    for (int i=0;i<32;i++)
        scanf("%d",&p[i]);
    for (int i=0;i<65536;i++)
    {
        for (int j=0;j<16;j++)
            if (i>>j&1)
                l[i]+=p[j]==31?-(1LL<<31):1LL<<p[j];
        for (int j=16;j<32;j++)
            if (i>>j-16&1)
                r[i]+=p[j]==31?-(1LL<<31):1LL<<p[j];
    }
    ll ans=0;
    for (int i=1;i<=n;i++)
    {
        s=(s*a+c);
        ans+=l[s&65535]+r[s>>16];
    }
    printf("%lld\n",ans);
    return(0);
}

