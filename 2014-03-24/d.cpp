#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
int n,cnt[100010],b[100010],a[200010][2];
ll ans[100010],f[100010];
void dfs(int x,int father)
{
    cnt[x]=1;
    for (int i=b[x];i;i=a[i][1])
    {
        int y=a[i][0];
        if (y==father)
            continue;
        dfs(y,x);
        cnt[x]+=cnt[y];
        f[x]+=f[y]+cnt[y];
    }
}
void getans(int x,int father,ll up)
{
    ans[x]=f[x]+up;
    for (int i=b[x];i;i=a[i][1])
    {
        int y=a[i][0];
        if (y==father)
            continue;
        getans(y,x,ans[x]-f[y]+n-2*cnt[y]);
    }
}
int main()
{
    scanf("%d",&n);
    for (int i=1;i<n;i++)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        a[i][0]=y,a[i][1]=b[x],b[x]=i;
        a[i+n][0]=x,a[i+n][1]=b[y],b[y]=i+n;
    }
    dfs(1,0);
    getans(1,0,0);
    ll best=*min_element(ans+1,ans+n+1);
    printf("%lld %d",best,count(ans+1,ans+n+1,best));
    for (int i=1;i<=n;i++)
        if (ans[i]==best)
            printf(" %d",i);
    printf("\n");
    return(0);
}

