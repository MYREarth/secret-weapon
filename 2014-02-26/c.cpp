#include <cstdio>
#include <cstring>
typedef long long ll;
const int mod=1000000007;
char a[1000010],b[1000010];
int fac[1000010],inv[1000010];
int power(int x,int y)
{
    if (y<0)
        return(0);
    int ret=1;
    for (;y;y>>=1)
    {
        if (y&1)
            ret=ll(ret)*x%mod;
        x=ll(x)*x%mod;
    }
    return(ret);
}
void init()
{
    fac[0]=inv[0]=1;
    for (int i=1;i<=1000000;i++)
    {
        fac[i]=ll(fac[i-1])*i%mod;
        inv[i]=power(fac[i],mod-2);
    }
}
inline int C(int n,int m)
{
    if (n<0 || m<0 || n<m)
        return(0);
    return(ll(fac[n])*inv[m]%mod*inv[n-m]%mod);
}
int main()
{
    freopen("password.in","r",stdin);
    freopen("password.out","w",stdout);
    init();
    int A,B;
    scanf("%s%s%d%d",a,b,&A,&B);
    int len=strlen(a),x=0,y=0;
    for (int i=0;i<len;i++)
    {
        x+=a[i]==b[i];
        y+=a[i]!=b[i];
    }
    int ans=0;
    for (int t=0;t<=len;t++)
    {
        int now=ll(C(x,t))*power(25,x-t)%mod*C(y,A-t)%mod*C(y-(A-t),B-t)%mod*power(24,y-(A-t)-(B-t))%mod;
        ans=(ans+now)%mod;
    }
    printf("%d\n",ans);
    return(0);
}

