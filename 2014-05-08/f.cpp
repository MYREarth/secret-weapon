#include <cstdio>
typedef long long ll;
int main()
{
    freopen("scarf.in","r",stdin);
    freopen("scarf.out","w",stdout);
    ll n;
    int K,Q;
    scanf("%lld%d%d",&n,&K,&Q);
    while (Q--)
    {
        ll x;
        scanf("%lld",&x);
        ll layer=1,pos=x,len=n,p=1;
        for (int i=1;i<=K;i++)
        {
            ll part=len/4;
            if (pos>part && pos<=part*3)
                pos-=part;
            else
            {
                layer=2*p-layer+1;
                if (pos<=part)
                    pos=part-pos+1;
                else
                    pos=part*5-pos+1;
            }
            len/=2;
            p*=2;
        }
        printf("%lld %lld\n",layer,pos);
    }
    return(0);
}

