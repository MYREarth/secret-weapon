#include <cstdio>
typedef long long ll;
const int mod=1000007,lq=19;
ll f[10][11][mod];
int positive[10],negative[10];
int calc(int x,int y)
{
    return(ll(positive[x])*negative[y]%mod);
}
void init()
{
    const int n=9;
    positive[0]=negative[0]=1;
    for (int i=1;i<=n;i++)
    {
        positive[i]=ll(positive[i-1])*lq%mod;
        negative[i]=(ll(negative[i-1])*(1-lq)%mod+mod)%mod;
    }
    f[0][1][0]=f[0][1][1]=1;
    for (int i=1;i<=n;i++)
    {
        for (int j=0;j<mod;j++)
            f[i][0][j]=f[i-1][i][j];
        for (int j=0;j<=i;j++)
            for (int k=0;k<mod;k++)
            {
                f[i][j+1][k]+=f[i][j][k];
                f[i][j+1][(k+calc(j,i-j))%mod]+=f[i][j][k];
            }
    }
}
int main()
{
    init();
    while (1)
    {
        int n;
        scanf("%d",&n);
        if (n==0)
            break;
        static int id=0;
        printf("Case #%d: %lld\n",++id,f[n][n+1][1]-f[n-1][n][1]);
    }
    return(0);
}

