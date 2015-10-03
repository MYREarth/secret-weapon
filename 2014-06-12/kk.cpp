#include <cstdio>
#include <algorithm>
using namespace std;
int a[1010],b[1010],f[1010][1010];
int main()
{
    int n;
    scanf("%d",&n);
    for (int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    for (int i=1;i<=n;i++)
        scanf("%d",&b[i]);
    for (int i=0;i<=n;i++)
        f[i][0]=f[0][i]=i;
    for (int i=1;i<=n;i++)
        for (int j=1;j<=n;j++)
            if (a[i]==b[j])
                f[i][j]=min(f[i-1][j],f[i][j-1])+1;
            else
                f[i][j]=f[i-1][j-1]+1;
    for (int i=0;i<=n;i++)
    {
        for (int j=0;j<=n;j++)
            printf("%d ",f[i][j]);
        printf("\n");
    }
    printf("%d\n",f[n][n]);
}

