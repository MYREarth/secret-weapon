#include <cstdio>
#include <utility>
#include <queue>
#include <algorithm>
using namespace std;
int a[1510],b[1510],to[1510],c[1510];
int main()
{
    freopen("sandwiches.in","r",stdin);
    int T;
    scanf("%d",&T);
    while (T--)
    {
        int n;
        scanf("%d",&n);
        for (int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        sort(a+1,a+n+1);
        reverse(a+1,a+n+1);
        for (int i=2;i<=n;i++)
        {
            for (int j=1;j<=n;j++)
                scanf("%d",&b[j]);
            priority_queue <pair <int,int> > Q;
            for (int j=1;j<=n;j++)
            {
                to[j]=1;
                Q.push(make_pair(b[j]+a[1],j));
            }
            for (int j=1;j<=n;j++)
            {
                c[j]=Q.top().first;
                int id=Q.top().second;
                Q.pop();
                Q.push(make_pair(b[id]+a[++to[id]],id));
            }
            for (int j=1;j<=n;j++)
                a[j]=c[j];
        }
        for (int i=1;i<=n;i++)
            printf("%d%c",a[i],i==n?'\n':' ');
    }
    return(0);
}

