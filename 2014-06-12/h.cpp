#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;
const double pi=acos(-1.0);
struct point
{
    double x,y;
    int id;
};
inline bool operator <(const point &a,const point &b)
{
    return(a.x<b.x);
}
inline int sign(double x,double eps=1e-8)
{
    return(x<-eps?-1:x>eps);
}
inline double randAngle()
{
    int x=rand()%10000;
    return(x/10000.0*2*pi);
}
point a[500010];
int X[500010],Y[500010],R[500010];
inline ll sqr(int x)
{
    return(ll(x)*x);
}
inline bool check(int u,int v)
{
    return((R[u]>R[v] || R[u]==R[v] && u>v) && sqr(X[u]-X[v])+sqr(Y[u]-Y[v])==sqr(R[u]+R[v]));
}
int main()
{
    int n;
    scanf("%d",&n);
    for (int i=1;i<=n;i++)
        scanf("%d%d%d",&X[i],&Y[i],&R[i]);
    double theta=randAngle();
    for (int i=1;i<=n;i++)
    {
        a[i].x=X[i]*cos(theta)-Y[i]*sin(theta);
        a[i].y=X[i]*sin(theta)+Y[i]*cos(theta);
        a[i].id=i;
    }
    sort(a+1,a+n+1);
    int ans=0;
    for (int i=1;i<=n;i++)
    {
        int x=a[i].id;
        for (int j=i+1;j<=n;j++)
        {
            if (sign(a[j].x-a[i].x-2*R[x])>0)
                break;
            ans+=check(x,a[j].id);
        }
        for (int j=i-1;j;j--)
        {
            if (sign(a[i].x-a[j].x-2*R[x])>0)
                break;
            ans+=check(x,a[j].id);
        }
    }
    printf("%d\n",ans);
    return(0);
}

