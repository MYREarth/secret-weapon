#include <cstdio>
#include <algorithm>
#define hash __hash__
using namespace std;
typedef unsigned long long ull;
const int lq=1000000007;
ull h[1000010],H[1000010],p[1000010];
char a[1000010],b[1000010];
ull hash(int pos,int len)
{
    return(h[pos]-p[len]*h[pos-len]);
}
ull rev(int pos,int len)
{
    return(H[pos]-p[len]*H[pos+len]);
}
bool check(int len,int n)
{
    for (int i=len;i<=n;i++)
        if (hash(i,len)==rev(i-len+1,len))
            return(true);
    return(false);
}
int main()
{
    p[0]=1;
    for (int i=1;i<=1000000;i++)
        p[i]=p[i-1]*lq;
    int T;
    scanf("%d",&T);
    while (T--)
    {
        int n;
        scanf("%d%s%s",&n,a+1,b+1);
        for (int i=1;i<=n;i++)
            h[i]=h[i-1]*lq+a[i];
        H[n+1]=0;
        for (int i=n;i;i--)
            H[i]=H[i+1]*lq+b[i];
        int ans=-1,l=0,r=n/2;
        while (l<=r)
        {
            int mid=l+r>>1;
            if (check(2*mid,n))
                ans=max(ans,2*mid),l=mid+1;
            else
                r=mid-1;
        }
        l=0,r=n/2;
        while (l<=r)
        {
            int mid=l+r>>1;
            if (check(2*mid+1,n))
                ans=max(ans,2*mid+1),l=mid+1;
            else
                r=mid-1;
        }
        printf("%d\n",ans);
    }
    return(0);
}

