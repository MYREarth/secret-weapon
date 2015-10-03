#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
struct point
{
    int x,y;
    point(){}
    point(int x,int y):x(x),y(y){}
};
inline point operator -(const point &a,const point &b)
{
    return(point(a.x-b.x,a.y-b.y));
}
inline ll det(const point &a,const point &b)
{
    return(ll(a.x)*b.y-ll(a.y)*b.x);
}
point a[200010];
int main()
{
    freopen("kingdom.in","r",stdin);
    freopen("kingdom.out","w",stdout);
    while (1)
    {
        int n;
        scanf("%d",&n);
        if (n==0)
            break;
        for (int i=1;i<=n;i++)
        {
            scanf("%d%d",&a[i].x,&a[i].y);
            a[i+n]=a[i];
        }
        point p,q;
        ll ans=0;
        scanf("%d%d%d%d",&p.x,&p.y,&q.x,&q.y);
        for (int i=1;i<=n;i++)
        {
            if (det(p-a[i],q-a[i])==0)
                continue;
            if (det(p-a[i],q-a[i])<0)
                swap(p,q);
            int l=i+1,r=i+n-1,left,right;
            while (l<=r)
            {
                int mid=l+r>>1;
                if (det(p-a[i],a[mid]-a[i])>0)
                    left=mid,r=mid-1;
                else
                    l=mid+1;
            }
            l=i+1,r=i+n-1;
            while (l<=r)
            {
                int mid=l+r>>1;
                if (det(a[mid]-a[i],q-a[i])>0)
                    right=mid,l=mid+1;
                else
                    r=mid-1;
            }
            ans+=right-left+1;
        }
        printf("%lld\n",ans>>1);
    }
    return(0);
}

