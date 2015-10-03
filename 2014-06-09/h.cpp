#include <cstdio>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;
struct edge
{
    int x,y,len;
};
edge e[1000010];
map <int,int> a[1000010];
int dep[1000010],q[1000010];
inline bool operator <(const edge &a,const edge &b)
{
    return(a.len>b.len || a.len==b.len && dep[a.x]<dep[b.x]);
}
void init()
{
    int l,r;
    dep[1]=1;
    q[l=r=1]=1;
    while (l<=r)
    {
        int x=q[l++];
        for (map <int,int>::iterator k=a[x].begin();k!=a[x].end();k++)
        {
            int y=k->first;
            if (!dep[y])
            {
                dep[y]=dep[x]+1;
                q[++r]=y;
            }
        }
    }
}
bool vis[1000010];
int sg[1000010];
int bfs(int S,int value)
{
    int l,r;
    q[l=r=1]=S;
    while (l<=r)
    {
        int x=q[l++];
        vis[x]=true;
        for (map <int,int>::iterator k=a[x].begin();k!=a[x].end();k++)
            q[++r]=k->first;
    }
    for (int i=r;i;i--)
    {
        int x=q[i];
        sg[x]=0;
        for (map <int,int>::iterator k=a[x].begin();k!=a[x].end();k++)
        {
            int y=k->first;
            if (k->second<value)
                sg[x]^=sg[y];
            else if (k->second==value)
                sg[x]^=sg[y]+1;
        }
    }
    return(sg[S]);
}
int main()
{
    int n;
    scanf("%d",&n);
    for (int i=1;i<n;i++)
    {
        scanf("%d%d%d",&e[i].x,&e[i].y,&e[i].len);
        a[e[i].x][e[i].y]=0;
        a[e[i].y][e[i].x]=0;
    }
    init();
    for (int i=1;i<=n;i++)
        a[i].clear();
    for (int i=1;i<n;i++)
    {
        if (dep[e[i].x]>dep[e[i].y])
            swap(e[i].x,e[i].y);
        a[e[i].x][e[i].y]=e[i].len;
    }
    sort(e+1,e+n);
    vector <bool> nim,anti;
    for (int i=1,j;i<n;i=j)
    {
        int sg=0;
        bool flag=true;
        for (j=i;j<n && e[i].len==e[j].len;j++)
        {
            int y=e[j].y;
            if (vis[y])
                continue;
            int tmp=bfs(y,e[j].len)+1;
            sg^=tmp;
            if (tmp>1)
                flag=false;
            a[e[j].x].erase(y);
        }
        nim.push_back(sg>0);
        anti.push_back(flag && sg==0 || !flag && sg>0);
    }
    reverse(nim.begin(),nim.end());
    reverse(anti.begin(),anti.end());
    bool win=nim[0];
    for (int i=1;i<nim.size();i++)
        win=win?anti[i]:nim[i];
    printf("%s\n",win?"Misha":"Shura");
    return(0);
}

