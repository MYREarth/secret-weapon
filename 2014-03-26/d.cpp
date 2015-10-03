#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
const int mod=1000000007;
int a[5010],f[5010][5010],g[5010][5010],s1[5010][5010],s2[5010][5010];
vector <int> value;
int main()
{
    freopen("subsequences.in","r",stdin);
    freopen("subsequences.out","w",stdout);
    int n;
    scanf("%d",&n);
    for (int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
        value.push_back(a[i]);
    }
    sort(value.begin(),value.end());
    value.erase(unique(value.begin(),value.end()),value.end());
    for (int i=1;i<=n;i++)
        a[i]=lower_bound(value.begin(),value.end(),a[i])-value.begin()+1;
    for (int i=n;i;i--)
    {
        for (int j=i+1;j<=n;j++)
        {
            if (a[i]==a[j])
                continue;
            f[i][j]=1;
            if (a[i]<a[j])
                f[i][j]=(f[i][j]+s1[j][a[i]-1])%mod;
            else
                f[i][j]=(f[i][j]+s2[j][a[i]+1])%mod;
            g[i][a[j]]=(g[i][a[j]]+f[i][j])%mod;
        }
        for (int j=1;j<=n;j++)
            s1[i][j]=(s1[i][j-1]+g[i][j])%mod;
        for (int j=n;j;j--)
            s2[i][j]=(s2[i][j+1]+g[i][j])%mod;
    }
    int ans=n;
    for (int i=1;i<=n;i++)
        for (int j=i+1;j<=n;j++)
            ans=(ans+f[i][j])%mod;
    printf("%d\n",ans);
    return(0);
}

