#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
struct point
{
    int x,y,id;
    point(){}
    point(int x,int y):x(x),y(y){}
};
inline point operator -(const point &a,const point &b)
{
    return(point(a.x-b.x,a.y-b.y));
}
inline bool operator <(const point &a,const point &b)
{
    return(a.x<b.x || a.x==b.x && a.y<b.y);
}
inline int sign(ll x)
{
    return(x<0?-1:x>0);
}
inline ll det(const point &a,const point &b)
{
    return(ll(a.x)*b.y-ll(a.y)*b.x);
}
inline int side(const point &p,const point &a,const point &b)
{
    return(sign(det(b-a,p-a)));
}
int m1,m2;
point a[100010],up[100010],down[100010];
void convex(int n)
{
    sort(a+1,a+n+1);
    for (int i=1;i<=n;i++)
    {
        while (m1>=2 && det(down[m1]-down[m1-1],a[i]-down[m1])<=0)
            m1--;
        down[++m1]=a[i];
    }
    for (int i=n;i;i--)
    {
        while (m2>=2 && det(up[m2]-up[m2-1],a[i]-up[m2])<=0)
            m2--;
        up[++m2]=a[i];
    }
}
point P,Q;
ll best1,best2;
void far(point *a,int m,const point &A,const point &B)
{
    vector <point> tmp;
    int sgn=sign(det(B-A,a[2]-a[1])),l=1,r=m-1,ans;
    while (l<=r)
    {
        int mid=(l+r)>>1;
        if (sign(det(B-A,a[mid+1]-a[mid]))==sgn)
            ans=mid,l=mid+1;
        else
            r=mid-1;
    }
    tmp.push_back(a[1]);
    tmp.push_back(a[m]);
    tmp.push_back(a[ans]);
    if (ans>1)
        tmp.push_back(a[ans-1]);
    if (ans<m)
        tmp.push_back(a[ans+1]);
    for (int i=0;i<tmp.size();i++)
    {
        ll now=det(B-A,tmp[i]-A);
        if (now>=0 && now>best1)
        {
            best1=now;
            P=tmp[i];
        }
        if (now<=0 && now<best2)
        {
            best2=now;
            Q=tmp[i];
        }
    }
}
void work(const point &a,const point &b)
{
    best1=-1;
    best2=1;
    far(down,m1,a,b);
    far(up,m2,a,b);
    if (best1!=-1 && best2!=1 && side(P,a,b)*side(Q,a,b)==-1)
        printf("%d %d\n",P.id,Q.id);
    else
        printf("0\n");
}
int main()
{
    int n;
    scanf("%d",&n);
    for (int i=1;i<=n;i++)
    {
        scanf("%d%d",&a[i].x,&a[i].y);
        a[i].id=i;
    }
    convex(n);
    int Q;
    scanf("%d",&Q);
    while (Q--)
    {
        point A,B;
        scanf("%d%d%d%d",&A.x,&A.y,&B.x,&B.y);
        if (n<=1)
            printf("0\n");
        else
            work(A,B);
    }
    return(0);
}

