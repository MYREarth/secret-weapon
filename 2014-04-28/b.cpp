#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
ll ans,f[100010],g[100010];
char a[100010];
int n,one[100010];
void update(int i,ll value)
{
    if (i+1<=n && a[i+1]=='1')
        f[i]=max(f[i],value);
    if (i+2<=n && a[i+1]=='0' && a[i+2]=='1')
        g[i]=max(g[i],value);
    if (i==n)
        ans=max(ans,value);
}
int main()
{
    int K;
    scanf("%d%s",&K,a+1);
    n=strlen(a+1);
    int now=0;
    for (int i=1;i<=n;i++)
    {
        one[i]=now;
        if (a[i]=='1')
            now=i;
    }
    memset(f,-63,sizeof(f));
    memset(g,-63,sizeof(g));
    ans=f[0];
    update(0,0);
    for (int i=1;i<=n;i++)
    {
        f[i]=max(f[i],f[i-1]);
        g[i]=max(g[i],g[i-1]);
        if (a[i]=='0')
            continue;
        ll now=0;
        for (int j=1;j<=K;j++)
        {
            if (i+j-1>n)
                break;
            now=now<<1|a[i+j-1]-'0';
            int p=one[i],q=one[p];
            if (i-p==p-q)
                q=one[q];
            if (q>=1)
                update(i+j-1,f[q-1]);
            if (i>=3)
                update(i+j-1,g[i-3]-now);
            if (i>=3 && a[i-1]=='0')
                update(i+j-1,f[i-3]+now);
        }
    }
    printf("%lld\n",ans);
    return(0);
}

