#include <cstdio>
#include <algorithm>
using namespace std;
int a[100010],p[100010];
bool check(int value,int mid,int X,int n)
{
    int t=n;
    for (int i=1;i<n;i++)
    {
        while (t>=1 && (t==mid || a[i]+p[t]<=value))
            t--;
        if (t--==0)
            break;
        if (i==X)
            return(false);
    }
    return(true);
}
int main()
{
    freopen("hop.in","r",stdin);
    freopen("hop.out","w",stdout);
    int n,X,me;
    scanf("%d%d%d",&n,&X,&me);
    for (int i=1;i<n;i++)
        scanf("%d",&a[i]);
    sort(a+1,a+n);
    reverse(a+1,a+n);
    for (int i=1;i<=n;i++)
        scanf("%d",&p[i]);
    int l=1,r=n,ans=-1;
    while (l<=r)
    {
        int mid=l+r>>1;
        if (check(me+p[mid],mid,X,n))
            ans=mid,l=mid+1;
        else
            r=mid-1;
    }
    printf("%d\n",ans);
    return(0);
}

