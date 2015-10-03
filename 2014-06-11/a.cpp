#include <cstdio>
#include <algorithm>
using namespace std;
int l,r,d[2000010],a[2000010],q[2000010];
bool vis[2000010],ans[2000010],mark[2000010];
void topsort()
{
    while (l<=r)
    {
        int x=q[l++],y=a[x];
        vis[x]=true;
        if (!mark[x])
            ans[x]=mark[y]=true;
        if (--d[y]==0)
            q[++r]=y;
    }
}
int main()
{
    int n;
    scanf("%d",&n);
    for (int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
        d[a[i]]++;
    }
    l=1,r=0;
    for (int i=1;i<=n;i++)
        if (!d[i])
            q[++r]=i;
    topsort();
    for (int i=1;i<=n;i++)
        if (!vis[i] && mark[i])
        {
            q[++r]=a[i];
            d[a[i]]--;
            topsort();
        }
    for (int i=1;i<=n;i++)
        if (!vis[i])
        {
            mark[i]=true;
            q[++r]=a[i];
            d[a[i]]--;
            topsort();
        }
    printf("%d\n",int(count(ans+1,ans+n+1,true)));
    for (int i=1;i<=n;i++)
        if (ans[i])
            printf("%d\n",i);
    return(0);
}

