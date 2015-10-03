#include <cstdio>
#include <cstring>
#include <utility>
#include <set>
#include <queue>
using namespace std;
typedef long long ll;
struct edge
{
    int x,y,len;
    edge(){}
    edge(int x,int y,int len):x(x),y(y),len(len){}
};
edge e[400010];
bool vis[400010];
set <pair <int,int> > a[100010];
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    for (int i=1;i<=m;i++)
    {
        int x,y,z;
        scanf("%d%d%d",&x,&y,&z);
        e[i]=edge(x,y,z);
        a[y].insert(make_pair(z,i));
        e[i+m]=edge(y,x,z);
        a[x].insert(make_pair(z,i+m));
    }
    priority_queue <pair <ll,int> > Q;
    for (auto k=a[n].begin();k!=a[n].end();k++)
    {
        int id=k->second;
        Q.push(make_pair(-e[id].len,id));
    }
    ll ans=1LL<<60;
    while (!Q.empty())
    {
        ll dis=-Q.top().first;
        int id=Q.top().second;
        Q.pop();
        if (vis[id])
            continue;
        vis[id]=true;
        int x=e[id].x,y=e[id].y,len=e[id].len;
        if (x==1)
            ans=min(ans,dis+len);
        a[y].erase(make_pair(len,id));
        auto k=a[y].upper_bound(make_pair(len,1<<30));
        if (k!=a[y].end())
            Q.push(make_pair(-(dis+e[k->second].len-len),k->second));
        if (k!=a[y].begin())
        {
            k--;
            Q.push(make_pair(-dis,k->second));
        }
        k=a[x].upper_bound(make_pair(len,1<<30));
        if (k!=a[x].end())
            Q.push(make_pair(-(dis+e[k->second].len),k->second));
        if (k!=a[x].begin())
        {
            k--;
            Q.push(make_pair(-(dis+len),k->second));
        }
    }
    printf("%lld\n",ans);
}

