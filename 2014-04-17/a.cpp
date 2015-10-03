#include <cstdio>
#include <algorithm>
using namespace std;
int a[1010];
int main()
{
    freopen("avangard.in","r",stdin);
    freopen("avangard.out","w",stdout);
    int n;
    scanf("%d",&n);
    if (n%2==0 || n%3==0)
        printf("No\n");
    else
    {
        printf("Yes\n");
        for (int i=1;i<=n;i++)
            a[i]=i;
        for (int i=1;i<=n;i++)
        {
            for (int j=1;j<=n;j++)
                printf("%d%c",a[j],j==n?'\n':' ');
            rotate(a+1,a+3,a+n+1);
        }
    }
    return(0);
}

