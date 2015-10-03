#include <cstdio>
#include <cstring>
const int mod=1000000007;
int s[310],a[100010],f[2][310],g[2][310];
int main()
{
    freopen("sequence.in","r",stdin);
    freopen("sequence.out","w",stdout);
    int n;
    scanf("%d",&n);
    for (int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    f[1][a[1]]=1;
    for (int i=2;i<=n;i++)
    {
        memset(f[i&1],0,sizeof(f[i&1]));
        memset(g[i&1],0,sizeof(g[i&1]));
        for (int j=300;j>=0;j--)
            s[j]=(s[j+1]+f[i-1&1][j])%mod;
        for (int j=0;j<=a[i];j++)
        {
            f[i&1][j]=(f[i-1&1][a[i]-j]+g[i-1&1][a[i]-j])%mod;
            g[i&1][j]=s[a[i]-j+1];
        }
    }
    int ans=g[n&1][0];
    for (int i=0;i<=300;i++)
        ans=(ans+f[n&1][i])%mod;
    printf("%d\n",ans);
    return(0);
}

