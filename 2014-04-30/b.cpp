#include <cstdio>
#include <map>
using namespace std;
const int mod=101;
map <int,int> f[10];
int dp(int x,int n)
{
    if (n==1)
        return(1);
    if (f[x].count(n))
        return(f[x][n]);
    int ans=0;
    for (int i=2;i<10;i++)
        if (n%i==0)
            ans+=dp(i,n/i);
    return(f[x][n]=ans%mod);
}
int main()
{
    int n;
    scanf("%d",&n);
    if (n<=1)
        printf("0\n");
    else
    {
        int ans=0;
        for (int i=2;i<10;i++)
            if (n%i==0)
                ans+=dp(i,n/i);
        printf("%d\n",ans%mod);
    }
    return(0);
}

