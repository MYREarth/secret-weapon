#include <cstdio>
typedef long long ll;
int mod,to[4010],full[4010],strong[4010],ans[4010],c[4010][4010];
int power(int x,int y)
{
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
    const int n=4000;
    for (int i=0;i<=n;i++)
    {
        full[i]=power(2,i*(i-1)/2);
        c[i][0]=c[i][i]=1;
        for (int j=1;j<i;j++)
            c[i][j]=(c[i-1][j-1]+c[i-1][j])%mod;
    }
    strong[1]=1;
    for (int i=2;i<=n;i++)
    {
        strong[i]=full[i];
        for (int j=1;j<i;j++)
            strong[i]=(strong[i]-ll(strong[j])*full[i-j]%mod*c[i][j]%mod+mod)%mod;
    }
    for (int i=1;i<=n;i++)
        for (int j=1;j<=i;j++)
            to[i]=(to[i]+ll(strong[j])*full[i-j]%mod*c[i-1][j-1]%mod)%mod;
    for (int i=2;i<=n;i++)
    {
        ans[i]=full[i];
        for (int j=1;j<i;j++)
            ans[i]=(ans[i]-ll(to[j])*full[i-j]%mod*c[i-2][j-1]%mod+mod)%mod;
    }
}
int main()
{
    freopen("tournament.in","r",stdin);
    freopen("tournament.out","w",stdout);
    scanf("%d",&mod);
    init();
    int n;
    while (scanf("%d",&n)==1)
        printf("%d\n",ans[n]);
    return(0);
}

