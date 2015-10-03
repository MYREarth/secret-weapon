#include <cstdio>
#include <cstring>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;
typedef long long ll;
struct point
{
    double x,y;
    point(){}
    point(double x,double y):x(x),y(y){}
    void in()
    {
        scanf("%lf%lf",&x,&y);
    }
};
typedef vector <pair <point,int> > data;
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
inline bool operator <(const point &a,const point &b)
{
    return(sign(a.x-b.x)<0 || sign(a.x-b.x)==0 && sign(a.y-b.y)<0);
}
inline bool operator ==(const point &a,const point &b)
{
    return(sign(a.x-b.x)==0 && sign(a.y-b.y)==0);
}
inline double dot(const point &a,const point &b)
{
    return(a.x*b.x+a.y*b.y);
}
inline double det(const point &a,const point &b)
{
    return(a.x*b.y-a.y*b.x);
}
inline bool parellel(const point &a,const point &b)
{
    return(sign(det(a,b))==0);
}
inline point intersect(const point &a,const point &b,const point &c,const point &d)
{
    double s1=det(b-a,c-a),s2=det(b-a,d-a);
    return((c*s2-d*s1)/(s2-s1));
}
point a[100010],b[100010];
data up,down,left,right;
int m,l[100010],r[100010],c[100010],f[200010];
inline bool cmp(int x,int y)
{
    return(l[x]<l[y]);
}
void calc(const data &a)
{
    for (int i=0;i<a.size();i++)
    {
        int x=a[i].second;
        m++;
        if (l[x]==0)
            l[x]=r[x]=m;
        else
            r[x]=m;
    }
}
int query(int x)
{
    int ret=0;
    for (int i=x;i;i-=i&-i)
        ret+=f[i];
    return(ret);
}
void insert(int x)
{
    for (int i=x;i<=m;i+=i&-i)
        f[i]++;
}
int main()
{
    int n;
    scanf("%d",&n);
    for (int i=1;i<=n;i++)
        a[i].in(),b[i].in();
    int x[4],y[4];
    for (int i=0;i<4;i++)
        scanf("%d%d",&x[i],&y[i]);
    int x0=*min_element(x,x+4);
    int y0=*min_element(y,y+4);
    int x1=*max_element(x,x+4);
    int y1=*max_element(y,y+4);
    for (int i=1;i<=n;i++)
    {
        if (!parellel(b[i]-a[i],point(1,0)))
        {
            point A=point(x0,y1),B=point(x1,y1);
            point P=intersect(a[i],b[i],A,B);
            if (sign(dot(P-A,P-B))<=0)
                up.push_back(make_pair(P,i));
            A=point(x0,y0),B=point(x1,y0);
            P=intersect(a[i],b[i],A,B);
            if (sign(dot(P-A,P-B))<=0)
                down.push_back(make_pair(P,i));
        }
        if (!parellel(b[i]-a[i],point(0,1)))
        {
            point A=point(x0,y0),B=point(x0,y1);
            point P=intersect(a[i],b[i],A,B);
            if (sign(dot(P-A,P-B))<0)
                left.push_back(make_pair(P,i));
            A=point(x1,y0),B=point(x1,y1);
            P=intersect(a[i],b[i],A,B);
            if (sign(dot(P-A,P-B))<0)
                right.push_back(make_pair(P,i));
        }
    }
    sort(up.begin(),up.end());
    sort(down.begin(),down.end());
    sort(left.begin(),left.end());
    sort(right.begin(),right.end());
    reverse(up.begin(),up.end());
    reverse(left.begin(),left.end());
    calc(down);
    calc(right);
    calc(up);
    calc(left);
    for (int i=1;i<=n;i++)
        c[i]=i;
    sort(c+1,c+n+1,cmp);
    ll ans=0;
    for (int i=1;i<=n;i++)
    {
        int x=c[i];
        if (l[x]==0)
            continue;
        ans+=query(r[x])-query(l[x]);
        insert(r[x]);
    }
    printf("%lld\n",ans);
}

