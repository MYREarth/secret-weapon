#include <cstdio>
const int mod=1000000009;
int f[21][1000010],s[21][1000010];
int main()
{
    int n,K;
    scanf("%d%d",&n,&K);
    for (int i=1;i<=n;i++)
    {
        f[1][i]=1;
        s[1][i]=i;
    }
    for (int i=2;i<=K;i++)
    {
        for (int j=1;j<=n;j++)
        {
            f[i][j]=s[i-1][j/2];
            s[i][j]=(s[i][j-1]+f[i][j])%mod;
        }
    }
    printf("%d\n",f[K][n]);
    return(0);
}

