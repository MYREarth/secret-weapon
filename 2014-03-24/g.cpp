#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
ll f[1010][1010],g[1010][1010];
int a[1010],b[1010];
int main()
{
    int n;
    scanf("%d",&n);
    for (int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
        a[i]--;
    }
    int m;
    scanf("%d",&m);
    for (int i=1;i<=m;i++)
    {
        scanf("%d",&b[i]);
        b[i]--;
    }
    memset(f,63,sizeof(f));
    memset(g,63,sizeof(g));
    f[1][1]=g[1][1]=a[1]*b[1];
    for (int i=1;i<=n;i++)
        for (int j=1;j<=m;j++)
        {
            if (i<n && j<m)
            {
                f[i+1][j+1]=min(f[i+1][j+1],min(f[i][j],g[i][j])+a[i+1]*b[j+1]);
                g[i+1][j+1]=min(g[i+1][j+1],min(f[i][j],g[i][j])+a[i+1]*b[j+1]);
            }
            if (i<n)
                f[i+1][j]=min(f[i+1][j],f[i][j]+a[i+1]*b[j]);
            if (j<m)
                g[i][j+1]=min(g[i][j+1],g[i][j]+a[i]*b[j+1]);
        }
    printf("%lld\n",min(f[n][m],g[n][m]));
    return(0);
}

