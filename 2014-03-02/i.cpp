#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
struct point
{
    double x,y;
    point(){}
    point(double x,double y):x(x),y(y){}
    point rotate() const
    {
        return(point(-y,x));
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
inline double det(const point &a,const point &b)
{
    return(a.x*b.y-a.y*b.x);
}
inline double xmul(const point &p0,const point &p1,const point &p2)
{
    return(det(p1-p0,p2-p0));
}
struct segement
{
    point s,e;
};
inline point intersect(const segement &s1,const segement &s2)
{
    double u=xmul(s1.s,s1.e,s2.s),v=xmul(s1.e,s1.s,s2.e);
    return(point(s2.s*v+s2.e*u)/(u+v));
}
point tmp[50010];
segement a[50010],seg[50010];
void init(int n)
{
    if (det(tmp[2]-tmp[1],tmp[3]-tmp[2])<0)
        reverse(tmp+1,tmp+n+1);
    tmp[0]=tmp[n];
    for (int i=1;i<=n;i++)
    {
        a[i].s=tmp[i-1];
        a[i].e=tmp[i];
    }
}
void generate(double R,int n)
{
    for (int i=1;i<=n;i++)
    {
        point dir=(a[i].e-a[i].s).rotate().unit();
        seg[i-1].s=a[i].s+dir*R;
        seg[i-1].e=a[i].e+dir*R;
    }
}
segement deq[50010];
int HPI(int n)
{
    deq[0]=seg[0],deq[1]=seg[1];
    int head=0,tail=1;
    for (int i=2;i<n;i++)
    {
        while (head<tail && xmul(seg[i].s,seg[i].e,intersect(deq[tail],deq[tail-1]))<0)
            tail--;
        while (head<tail && xmul(seg[i].s,seg[i].e,intersect(deq[head],deq[head+1]))<0)
            head++;
        deq[++tail]=seg[i];
    }
    while (head<tail && xmul(deq[head].s,deq[head].e,intersect(deq[tail],deq[tail-1]))<0)
        tail--;
    while (head<tail && xmul(deq[tail].s,deq[tail].e,intersect(deq[head],deq[head+1]))<0)
        head++;
    if (head==tail)
        return(0);
    int ret=0;
    for (int i=head;i<tail;i++)
        ret++;
    if (tail>head+1)
        ret++;
    return(ret);
}
int main()
{
    int n;
    scanf("%d",&n);
    for (int i=1;i<=n;i++)
        scanf("%lf%lf",&tmp[i].x,&tmp[i].y);
    init(n);
    double l=0,r=2e7;
    for (int T=1;T<=100;T++)
    {
        double mid=(l+r)/2;
        generate(mid,n);
        int m=HPI(n);
        if (m<3)
            r=mid;
        else
            l=mid;
    }
    printf("%.10f\n",(l+r)/2);
    return(0);
}

