#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N=200010;
struct point
{
    int x,y,id;
};
int n,ans1,ans2,ys[N],tmp[N];
ll ans=1LL<<62;
point a[N];
inline bool xcmp(const point &a,const point &b)
{
    return(a.x<b.x);
}
inline bool ystmp(int v1,int v2)
{
    return(a[v1].y<a[v2].y);
}
inline ll sqr(int x)
{
    return(ll(x)*x);
}
void update(const point &a,const point &b)
{
    ll now=sqr(a.x-b.x)+sqr(a.y-b.y);
    if (now<=ans)
        ans=now,ans1=a.id,ans2=b.id;
}
void minimal_dis(point c[],int n,int ys[])
{
    int mid=n/2,xmid=c[mid].x;
    if (n<20)
    {
        for (int i=0;i<n;i++)
            for (int j=i+1;j<n;j++)
            {
                update(c[i],c[j]);
                if (a[ys[i]].y>a[ys[j]].y)
                    swap(ys[i],ys[j]);
            }
        return;
    }
    minimal_dis(c,mid,ys);
    minimal_dis(c+mid,n-mid,ys+mid);
    merge(ys,ys+mid,ys+mid,ys+n,tmp,ystmp);
    copy(tmp,tmp+n,ys);
    for (int i=0;i<n;i++)
    {
        while (i<n && sqr(a[ys[i]].x-xmid)>ans)
            i++;
        int j=i+1,cnt=0;
        while (j<n && sqr(a[ys[j]].y-a[ys[i]].y)<=ans)
        {
            if (sqr(a[ys[j]].x-xmid)<=ans)
            {
                update(a[ys[i]],a[ys[j]]);
                if (++cnt>=10)
                    break;
            }
            j++;
        }
    }
}
int main()
{
    freopen("illegal.in","r",stdin);
    freopen("illegal.out","w",stdout);
    scanf("%d",&n);
    for (int i=0;i<n;i++)
    {
        scanf("%d%d",&a[i].x,&a[i].y);
        a[i].id=i+1;
    }
    sort(a,a+n,xcmp);
    for (int i=0;i<n;i++)
        ys[i]=i;
    minimal_dis(a,n,ys);
    printf("%d %d\n",ans1,ans2);
}

