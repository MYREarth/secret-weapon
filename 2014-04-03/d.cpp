#include <cstdio>
#include <cstring>
#include <queue>
#include <utility>
#include <algorithm>
using namespace std;
const int inf=1000000000;
int tot,last[100010],v[100010],d[100010],b[100010],a[100010][3];
inline void add(int x,int y,int z)
{
    a[++tot][0]=y,a[tot][1]=z,a[tot][2]=b[x],b[x]=tot;
}
int main()
{
    int n;
    scanf("%d",&n);
    for (int i=1;i<=n;i++)
    {
        scanf("%d",&v[i]);
        last[v[i]]=i;
    }
    int N=*max_element(v+1,v+n+1);
    memset(d,-1,sizeof(d));
    d[1]=0;
    priority_queue <pair <int,int> > Q;
    Q.push(make_pair(0,-1));
    for (int i=2,j;i<=n;i=j)
    {
        int x=-Q.top().second;
        Q.pop();
        vector <int> c;
        for (j=i;j==i || j<=n && v[j]>v[j-1];j++)
        {
            int y=v[j];
            if (j==last[y])
            {
                add(x,y,1);
                d[y]=d[x]+1;
                Q.push(make_pair(-d[y],-y));
            }
            else if (d[y]==-1)
            {
                add(x,y,inf);
                d[y]=d[x]+inf;
            }
            else
            {
                add(x,y,d[y]-d[x]-1);
                d[y]--;
            }
        }
    }
    printf("%d %d\n",N,tot);
    for (int i=1;i<=N;i++)
        for (int j=b[i];j;j=a[j][2])
            printf("%d %d %d\n",i,a[j][0],a[j][1]);
    return(0);
}

