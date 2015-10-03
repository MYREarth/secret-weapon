#include <cstdio>
#include <cstring>
#include <utility>
#include <queue>
using namespace std;
typedef long long ll;
int ans[100010],v[100010],d[100010],b[100010],a[100010][2];
void topsort(int n)
{
    priority_queue <pair <int,int> > Q;
    for (int i=1;i<=n;i++)
        if (d[i]==0)
            Q.push(make_pair(v[i],i));
    while (!Q.empty())
    {
        int x=Q.top().second;
        Q.pop();
        ans[n--]=x;
        for (int i=b[x];i;i=a[i][1])
        {
            int y=a[i][0];
            if (--d[y]==0)
                Q.push(make_pair(v[y],y));
        }
    }
}
int main()
{
    freopen("grand.in","r",stdin);
    freopen("grand.out","w",stdout);
    while (1)
    {
        int n;
        scanf("%d",&n);
        if (n==0)
            break;
        for (int i=1;i<=n;i++)
            scanf("%d",&v[i]);
        int m;
        scanf("%d",&m);
        memset(b,0,sizeof(b));
        memset(d,0,sizeof(d));
        for (int i=1;i<=m;i++)
        {
            int x,y;
            scanf("%d%d",&x,&y);
            d[x]++;
            a[i][0]=x,a[i][1]=b[y],b[y]=i;
        }
        topsort(n);
        int best=0;
        for (int i=1;i<=n;i++)
        {
            int x=ans[i];
            best=max(best,i-v[x]);
        }
        printf("%d\n",best);
        for (int i=1;i<=n;i++)
            printf("%d%c",ans[i],i==n?'\n':' ');
    }
    return(0);
}

