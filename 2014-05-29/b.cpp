#include <cstdio>
#include <cstring>
#include <cmath>
#include <stack>
#include <algorithm>
using namespace std;
const char inf[]="infinity";
struct point
{
    double x,y;
    point(){}
    point(double x,double y):x(x),y(y){}
    void in()
    {
        scanf("%lf%lf",&x,&y);
    }
    point unit() const
    {
        double t=sqrt(x*x+y*y);
        return(point(x/t,y/t));
    }
};
inline point operator +(const point &a,const point &b)
{
    return(point(a.x+b.x,a.y+b.y));
}
inline point operator -(const point &a,const point &b)
{
    return(point(a.x-b.x,a.y-b.y));
}
inline point operator *(const point &a,double b)
{
    return(point(a.x*b,a.y*b));
}
inline point operator /(const point &a,double b)
{
    return(point(a.x/b,a.y/b));
}
inline int sign(double x,double eps=1e-8)
{
    return(x<-eps?-1:x>eps);
}
inline double dot(const point &a,const point &b)
{
    return(a.x*b.x+a.y*b.y);
}
inline double det(const point &a,const point &b)
{
    return(a.x*b.y-a.y*b.x);
}
inline double sqr(double x)
{
    return(x*x);
}
inline bool same(const point &a,const point &b,const point &c,const point &d)
{
    return(sign(det(b-a,c-a))==0 && sign(det(b-a,d-a))==0);
}
inline double dist(const point &a,const point &b)
{
    return(sqrt(sqr(a.x-b.x)+sqr(a.y-b.y)));
}
inline double dist(const point &p,const point &a,const point &b)
{
    if (sign(dot(p-a,p-b))<=0)
        return(0);
    return(min(dist(p,a),dist(p,b)));
}
inline point intersect(const point &a,const point &b,const point &c,const point &d)
{
    double s1=det(b-a,c-a),s2=det(b-a,d-a);
    return((c*s2-d*s1)/(s2-s1));
}
inline bool online(const point &p,const point &a,const point &b)
{
    return(dot(p-a,p-b)<=0);
}
inline double side(const point &p,const point &a,const point &b)
{
    return(det(b-a,p-a));
}
inline bool cross(const point &a,const point &b,const point &c,const point &d)
{
    const double eps=1e-8;
    return(side(a,c,d)*side(b,c,d)<eps && side(c,a,b)*side(d,a,b)<eps);
}
namespace SAT
{
    int tot,b[610],a[1000000][2];
    void clear()
    {
        memset(b,0,sizeof(b));
        tot=0;
    }
    void add(int x,int y)
    {
        a[++tot][0]=y,a[tot][1]=b[x],b[x]=tot;
    }
    int idx,dfn[610],low[610],c[610];
    stack <int> s;
    bool in[610];
    void tarjan(int x)
    {
        dfn[x]=low[x]=++idx;
        s.push(x);
        in[x]=true;
        for (int i=b[x];i;i=a[i][1])
        {
            int y=a[i][0];
            if (!dfn[y])
            {
                tarjan(y);
                low[x]=min(low[x],low[y]);
            }
            else if (in[y])
                low[x]=min(low[x],dfn[y]);
        }
        if (dfn[x]==low[x])
        {
            c[0]++;
            while (1)
            {
                int y=s.top();
                s.pop();
                c[y]=c[0],in[y]=false;
                if (x==y)
                    break;
            }
        }
    }
    bool solve(int n)
    {
        memset(dfn,0,sizeof(dfn));
        idx=c[0]=0;
        for (int i=1;i<=2*n;i++)
            if (!dfn[i])
                tarjan(i);
        for (int i=1;i<=n;i++)
            if (c[i]==c[i+n])
                return(false);
        return(true);
    }
}
point a[310],b[310],dir[310];
bool parellel[310][310],colli[310][310];
bool check(int n,double mid)
{
    SAT::clear();
    for (int i=1;i<=n;i++)
        for (int x=0;x<2;x++)
        {
            point p,q;
            if (x==0)
                p=a[i],q=b[i]+dir[i]*mid;
            else
                p=a[i]-dir[i]*mid,q=b[i];
            for (int j=i+1;j<=n;j++)
                for (int y=0;y<2;y++)
                {
                    point u,v;
                    if (y==0)
                        u=a[j],v=b[j]+dir[j]*mid;
                    else
                        u=a[j]-dir[j]*mid,v=b[j];
                    bool flag=false;
                    if (colli[i][j])
                        flag=online(p,u,v) || online(q,u,v) || online(u,p,q) || online(v,p,q);
                    if (!parellel[i][j])
                        flag=cross(p,q,u,v);
                    if (flag)
                    {
                        SAT::add(i+x*n,j+(y^1)*n);
                        SAT::add(j+y*n,i+(x^1)*n);
                    }
                }
        }
    return(SAT::solve(n));
}
int main()
{
    while (1)
    {
        int n;
        scanf("%d",&n);
        if (n==0)
            break;
        for (int i=1;i<=n;i++)
        {
            a[i].in(),b[i].in();
            dir[i]=(b[i]-a[i]).unit();
        }
        double l=0,r=0,ans=1e100;
        for (int i=1;i<=n;i++)
            for (int j=i+1;j<=n;j++)
            {
                parellel[i][j]=sign(det(b[i]-a[i],b[j]-a[j]))==0;
                colli[i][j]=parellel[i][j] && same(a[i],b[i],a[j],b[j]);
                if (!parellel[i][j])
                {
                    point p=intersect(a[i],b[i],a[j],b[j]);
                    double now=max(dist(p,a[i],b[i]),dist(p,a[j],b[j]));
                    ans=min(ans,now);
                    r=max(r,now);
                }
                else if (colli[i][j])
                {
                    double now=min(min(dist(a[i],a[j]),dist(a[i],b[j])),min(dist(b[i],a[j]),dist(b[i],b[j])));
                    ans=min(ans,now/2);
                    r=max(r,now);
                }
            }
        if (ans>1e95)
            printf("%s %s\n",inf,inf);
        else
        {
            printf("%.10f ",ans);
            r+=26;
            bool flag=false;
            for (int T=1;T<=100;T++)
            {
                double mid=(l+r)/2;
                if (check(n,mid))
                    l=mid;
                else
                    flag=true,r=mid;
            }
            if (!flag)
                printf("%s\n",inf);
            else
                printf("%.10f\n",(l+r)/2);
        }
    }
    return(0);
}

