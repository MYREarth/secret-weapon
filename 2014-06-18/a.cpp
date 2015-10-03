#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;
const double eps=1e-8;
struct edge
{
    int x,y,id;
    double len;
    edge(){}
    edge(int x,int y,int id,double len):x(x),y(y),id(id),len(len){}
};
inline bool operator <(const edge &a,const edge &b)
{
    return(a.len<b.len);
}
edge e[1260];
struct data
{
    double A,B,C;
    int u,v;
    double calc(double x) const
    {
        return(A*x*x+B*x+C);
    }
};
data a[1260];
double X[60],Y[60],Z[60],vx[60],vy[60],vz[60];
inline double sqr(double x)
{
    return(x*x);
}
data calc(int i,int j)
{
    data ret;
    ret.u=i,ret.v=j;
    ret.A=sqr(vx[i]-vx[j])+sqr(vy[i]-vy[j])+sqr(vz[i]-vz[j]);
    ret.B=2*((X[i]-X[j])*(vx[i]-vx[j])+(Y[i]-Y[j])*(vy[i]-vy[j])+(Z[i]-Z[j])*(vz[i]-vz[j]));
    ret.C=sqr(X[i]-X[j])+sqr(Y[i]-Y[j])+sqr(Z[i]-Z[j]);
    return(ret);
}
struct event
{
    double x;
    int u,v;
    event(double x,int u,int v):x(x),u(u),v(v){}
};
inline bool operator <(const event &a,const event &b)
{
    return(a.x<b.x);
}
inline bool zero(double x)
{
    return(fabs(x)<eps);
}
vector <event> eve;
void intersect(int i,int j)
{
    double A=a[i].A-a[j].A,B=a[i].B-a[j].B,C=a[i].C-a[j].C;
    if (zero(A))
    {
        if (!zero(B))
        {
            double x=-C/B;
            if (x>=0)
                eve.push_back(event(x,i,j));
        }
        return;
    }
    double delta=sqr(B)-4*A*C;
    if (delta<0)
        return;
    double x1=(-B-sqrt(delta))/(2*A);
    double x2=(-B+sqrt(delta))/(2*A);
    if (x1>=0)
        eve.push_back(event(x1,i,j));
    if (x2>=0)
        eve.push_back(event(x2,i,j));
}
edge get(int id,double x)
{
    return(edge(a[id].u,a[id].v,id,a[id].calc(x)));
}
int idx,now[60],choose[60],f[60],vis[1260];
int find(int x)
{
    if (x!=f[x])
        f[x]=find(f[x]);
    return(f[x]);
}
void kruskal(int n,int m)
{
    sort(e+1,e+m+1);
    for (int i=1;i<=n;i++)
        f[i]=i;
    int cnt=0;
    for (int i=1;i<=m;i++)
    {
        int x=find(e[i].x),y=find(e[i].y);
        if (x==y)
            continue;
        f[x]=y;
        choose[++cnt]=e[i].id;
        if (cnt==n-1)
            break;
    }
    sort(choose+1,choose+n);
}
int main()
{
    int n;
    while (scanf("%d",&n)==1)
    {
        for (int i=1;i<=n;i++)
            scanf("%lf%lf%lf%lf%lf%lf",&X[i],&Y[i],&Z[i],&vx[i],&vy[i],&vz[i]);
        int m=0;
        for (int i=1;i<=n;i++)
            for (int j=i+1;j<=n;j++)
                a[++m]=calc(i,j);
        for (int i=1;i<=m;i++)
            e[i]=get(i,0);
        kruskal(n,m);
        for (int i=1;i<n;i++)
            now[i]=choose[i];
        eve.clear();
        for (int i=1;i<=m;i++)
            for (int j=i+1;j<=m;j++)
                intersect(i,j);
        sort(eve.begin(),eve.end());
        int ans=1;
        for (int i=0,j;i<eve.size();i=j)
        {
            idx++;
            int tot=0;
            for (j=i;j<eve.size() && zero(eve[i].x-eve[j].x);j++);
            double t=j==eve.size()?eve[i].x+26:(eve[i].x+eve[j].x)/2;
            for (j=i;j<eve.size() && zero(eve[i].x-eve[j].x);j++)
            {
                if (vis[eve[j].u]!=idx)
                {
                    vis[eve[j].u]=idx;
                    e[++tot]=get(eve[j].u,t);
                }
                if (vis[eve[j].v]!=idx)
                {
                    vis[eve[j].v]=idx;
                    e[++tot]=get(eve[j].v,t);
                }
            }
            for (int j=1;j<n;j++)
                if (vis[now[j]]!=idx)
                {
                    vis[now[j]]=idx;
                    e[++tot]=get(now[j],t);
                }
            kruskal(n,tot);
            bool flag=false;
            for (int j=1;j<n;j++)
                if (choose[j]!=now[j])
                {
                    flag=true;
                    now[j]=choose[j];
                }
            ans+=flag;
        }
        static int id=0;
        printf("Case %d: %d\n",++id,ans);
    }
    return(0);
}

