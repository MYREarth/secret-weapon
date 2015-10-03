#include <cstdio>
#include <cstring>
#include <cctype>
typedef long long ll;
int a[20];
char s[20];
ll f[66000][20],g[66000][20];
inline void update(ll &x,ll y)
{
    if (x==-1 || y<x)
        x=y;
}
int main()
{
    scanf("%s",s);
    int n=strlen(s);
    for (int i=1;i<=n;i++)
    {
        char ch=s[i-1];
        if (isdigit(ch))
            a[i]=ch-'0';
        else
            a[i]=ch-'A'+10;
    }
    memset(f,-1,sizeof(f));
    memset(g,-1,sizeof(g));
    f[0][0]=0;
    g[1<<1][0]=1;
    for (int i=0;i<65536;i++)
        for (int j=1;j<=n;j++)
        {
            if (f[i][j-1]!=-1)
            {
                if (!(i>>a[j]&1))
                    update(f[i|1<<a[j]][j],f[i][j-1]*16+a[j]);
                for (int k=a[j]+1;k<16;k++)
                {
                    if (i>>k&1)
                        continue;
                    update(g[i|1<<k][j],f[i][j-1]*16+k);
                }
            }
            if (g[i][j-1]==-1)
                continue;
            for (int k=0;k<16;k++)
            {
                if (i>>k&1)
                    continue;
                update(g[i|1<<k][j],g[i][j-1]*16+k);
            }
        }
    ll ans=-1;
    for (int i=0;i<65536;i++)
        if (g[i][n]!=-1)
            update(ans,g[i][n]);
    printf("%llX\n",ans);
    return(0);
}

