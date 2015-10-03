#include <cstdio>
#include <cstring>
#include <cctype>
#include <iostream>
using namespace std;
typedef unsigned long long ull;
int a[20];
char s[20];
ull f[66000][20],g[66000][20];
inline void update(ull &x,ull y)
{
    if (y<x)
        x=y;
}
int main()
{
    scanf("%s",s);
    int n=strlen(s);
    ull inf=0;
    for (int i=0;i<64;i++)
        inf|=1LLU<<i;
    for (int i=1;i<=n;i++)
    {
        char ch=s[i-1];
        if (isdigit(ch))
            a[i]=ch-'0';
        else
            a[i]=ch-'A'+10;
    }
    for (int i=0;i<65536;i++)
        for (int j=0;j<=n;j++)
            f[i][j]=g[i][j]=inf;
    f[0][0]=0;
    g[1<<1][0]=1;
    for (int i=0;i<65536;i++)
        for (int j=1;j<=n;j++)
        {
            if (f[i][j-1]!=inf)
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
            if (g[i][j-1]==inf)
                continue;
            for (int k=0;k<16;k++)
            {
                if (i>>k&1)
                    continue;
                update(g[i|1<<k][j],g[i][j-1]*16+k);
            }
        }
    ull ans=inf;
    for (int i=0;i<65536;i++)
        if (g[i][n]!=-1)
            update(ans,g[i][n]);
    printf("%llX\n",ans);
    return(0);
}

