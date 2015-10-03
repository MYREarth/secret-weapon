#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
int a[100010],c[100010];
ll s[100010];
inline bool cmp(int x,int y)
{
    return(s[x]<s[y]);
}
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    for (int i=2;i<=n;i++)
        scanf("%d",&a[i]);
    for (int i=1;i<=n;i++)
    {
        c[i]=i;
        s[i]=s[i-1]+a[i];
    }
    sort(c+1,c+n+1,cmp);
    ll best=1LL<<60;
    int pos=0;
    for (int i=m;i<=n;i++)
    {
        int x=c[i],y=c[i-m+1];
        if (s[x]-s[y]<best)
        {
            best=s[x]-s[y];
            pos=i;
        }
    }
    printf("%lld\n",best);
    for (int i=pos-m+1;i<=pos;i++)
        printf("%d%c",c[i],i==pos?'\n':' ');
    return(0);
}

