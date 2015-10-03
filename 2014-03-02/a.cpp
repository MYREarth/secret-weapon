#include <cstdio>
#include <algorithm>
using namespace std;
int a[100010],b[100010],ans[100010];
void minus(int n,int m)
{
    reverse(a+1,a+n+1);
    reverse(b+1,b+n+1);
    for (int i=1;i<=n;i++)
    {
        ans[i]+=a[i]-b[i];
        if (ans[i]<0)
        {
            ans[i]+=m;
            ans[i+1]--;
        }
    }
    while (n>1 && ans[n]==0)
        n--;
    for (int i=n;i;i--)
        printf("%c",ans[i]<10?ans[i]+'0':ans[i]-10+'A');
    printf("\n");
}
int main()
{
    int m,n;
    scanf("%d%d",&m,&n);
    for (int i=1;i<=n/2;i++)
    {
        a[i]=m-1;
        b[n-i+1]=m-1;
    }
    a[n/2+1]=1;
    b[1]=1;
    minus(n,m);
    return(0);
}

