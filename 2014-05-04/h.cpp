#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;
const int maxn=20010,inf=1<<30;
struct point
{
    int x,y,id;
};
inline bool cmp(const point &a,const point &b)
{
    return(a.y-a.x<b.y-b.x || a.y-a.x==b.y-b.x && a.y>b.y);
}
inline int lowbit(int x)
{
    return(x&-x);
}
inline int calc(const point &a,const point &b)
{
    return(abs(a.x-b.x)+abs(a.y-b.y));
}
inline void rotate(point &a)
{
    int t=a.x;
    a.x=-a.y;
    a.y=t;
}
struct edge
{
    int x,y,z;
    edge(int x,int y,int z):x(x),y(y),z(z){}
};
inline bool operator <(const edge &a,const edge &b)
{
    return(a.z<b.z);
}
vector <edge> Edge;
int n,father[maxn];
int find(int x)
{
    int t,tt;
    for (t=x;father[t]>=0;t=father[t]);
    while (father[x]>=0)
    {
        tt=father[x];
        father[x]=t;
        x=tt;
    }
    return(t);
}
void Union(int x,int y)
{
    if (-father[x]>-father[y])
        swap(x,y);
    father[y]+=father[x];
    father[x]=y;
}
void kruskal()
{
    sort(Edge.begin(),Edge.end());
    for (int i=0;i<n;i++)
        father[i]=-1;
    int ans=0;
    for (int i=0,kn=0;i<Edge.size() && kn<n-1;i++)
    {
        int kx=find(Edge[i].x),ky=find(Edge[i].y);
        if (kx!=ky)
        {
            ans=max(ans,Edge[i].z);
            Union(kx,ky);
            kn++;
        }
    }
    printf("%d\n",ans);
}
point a[maxn],cp[maxn];
int dp[maxn],rec[maxn],yl[maxn];
void work()
{
    for (int i=0;i<n;i++)
        cp[i]=a[i];
    for (int i=0;i<n;i++)
        yl[i]=cp[i].y;
    sort(yl,yl+n);
    int tot=unique(yl,yl+n)-yl;
    sort(cp,cp+n,cmp);
    for (int i=1;i<=tot;i++)
        dp[i]=inf;
    for (int i=0;i<n;i++)
    {
        int id=-1,res=inf;
        int pos=lower_bound(yl,yl+tot,cp[i].y)-yl+1;
        for (int x=pos;x<=tot;x+=lowbit(x))
            if (dp[x]<res)
            {
                res=dp[x];
                id=rec[x];
            }
        if (id!=-1)
            Edge.push_back(edge(cp[i].id,id,calc(a[cp[i].id],a[id])));
        res=cp[i].x+cp[i].y;
        for (int x=pos;x>0;x-=lowbit(x))
            if (res<dp[x])
            {
                dp[x]=res;
                rec[x]=cp[i].id;
            }
    }
}
int main()
{
    scanf("%d",&n);
    for (int i=0;i<n;i++)
    {
        scanf("%d%d",&a[i].x,&a[i].y);
        a[i].id=i;
    }
    work();
    for (int j=0;j<n;j++)
        swap(a[j].x,a[j].y);
    work();
    for (int j=0;j<n;j++)
        swap(a[j].x,a[j].y);
    for (int j=0;j<n;j++)
        rotate(a[j]);
    work();
    for (int j=0;j<n;j++)
        swap(a[j].x,a[j].y);
    work();
    kruskal();
    return(0);
}

