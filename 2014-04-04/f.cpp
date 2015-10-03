#include <cstdio>
typedef long long ll;
const int mod=1000000007;
inline int power(int x,int y)
{
    if (y<=0)
        return(1);
    int ret=1;
    for (;y;y>>=1)
    {
        if (y&1)
            ret=ll(ret)*x%mod;
        x=ll(x)*x%mod;
    }
    return(ret);
}
int a[110],c[110][110];
void init(int n)
{
    for (int i=0;i<=n;i++)
    {
        a[i]=power(i,i-2);
        c[i][0]=c[i][i]=1;
        for (int j=1;j<i;j++)
            c[i][j]=(c[i-1][j-1]+c[i-1][j])%mod;
    }
}
int ans[110];
int calc(int n)
{
    for (int i=1;i<=n;i++)
        for (int j=1;j<=n-i;j++)
            ans[i+j]=(ans[i+j]+ll(a[i])*a[j]%mod*c[n][i]%mod*c[n-i][j]%mod*i%mod*j%mod)%mod;
    int ret=0;
    for (int i=1;i<=n;i++)
        ret=(ret+ll(ans[n-i])*a[i+1])%mod;
    for (int i=1;i<=n;i++)
        ret=(ret-ll(ans[n-i])*a[i]%mod*i*2%mod*power(3,mod-2))%mod;
    return((ret+mod)%mod);
}
int main()
{
    int n;
    scanf("%d",&n);
    init(n);
    printf("%d\n",(calc(n)+a[n])%mod);
    return(0);
}

