#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
typedef long double ld;
const ld inf=1e15;
struct point
{
    ld x,y;
    point(){}
    point(ld x,ld y):x(x),y(y){}
    void out() {printf("%.10f %.10f\n",double(x),double(y));}
};
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
inline ld det(const point &a,const point &b)
{
    return(a.x*b.y-a.y*b.x);
}
inline point intersect(const point &a,const point &b,const point &c,const point &d)
{
    double s1=det(b-a,c-a),s2=det(b-a,d-a);
    return((c*s2-d*s1)/(s2-s1));
}
struct data
{
    ll delta,a[410];
    point p[410];
    int m,num;
    void generate()
    {
        for (int i=1;i<=400;i++)
            a[i]+=ll(num+i)*delta;
        delta=0;
        m=2;
        p[1]=point(0,a[1]);
        p[2]=point(inf,inf*(num+1)+a[1]);
        for (int i=2;i<=400;i++)
        {
            point P=point(0,a[i]),Q=point(inf,inf*(num+i)+a[i]);
            while (m>=2)
            {
                point tmp=intersect(p[m],p[m-1],P,Q);
                if (tmp.x<=p[m-1].x)
                {
                    m--;
                    continue;
                }
                p[m]=tmp;
                p[++m]=Q;
                break;
            }
            if (m==1)
            {
                p[1]=P;
                p[m=2]=Q;
            }
        }
    }
    ll query()
    {
        int l=2,r=m,t;
        while (l<=r)
        {
            int mid=l+r>>1;
            if (p[mid].x>=delta)
                t=mid,r=mid-1;
            else
                l=mid+1;
        }
        ld rate=(delta-p[t-1].x)/(p[t].x-p[t-1].x);
        ld ans=p[t-1].y+(p[t].y-p[t-1].y)*rate;
        return(ll(ans+0.5));
    }
};
data a[260];
int main()
{
//    freopen("business.in","r",stdin);
//    freopen("business.out","w",stdout);
    for (int i=1;i<=250;i++)
    {
        memset(a[i].a,0,sizeof(a[i].a));
        a[i].m=2;
        a[i].p[1]=point(0,0);
        a[i].p[2]=point(inf,inf*i*400);
        a[i].delta=0;
        a[i].num=(i-1)*400;
    }
    int T;
    scanf("%d",&T);
    while (T--)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        for (int i=1;i<=250;i++)
        {
            if (x<=i*400)
            {
                int m=x-(i-1)*400;
                for (int j=1;j<=m;j++)
                    a[i].a[j]+=ll(a[i].num+j)*y;
                a[i].generate();
                break;
            }
            a[i].delta+=y;
        }
        ll ans=0;
        for (int i=1;i<=250;i++)
            ans=max(ans,a[i].query());
        printf("%lld\n",ans);
    }
    return(0);
}

