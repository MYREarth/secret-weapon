#include <cstdio>
#include <cstring>
#include <cctype>
#include <utility>
#include <numeric>
#pragma comment(linker,"/STACK:16777216")
using namespace std;
typedef long long ll;
typedef long double ld;
int top,b[400010],f[400010],p[400010],c[400010],a[800010][2];
ll s[400010],ans[400010];
pair <ll,ll> stack[400010];
int find(ll k,ll b)
{
    int l=1,r=top-1,ans=top+1;
    while (l<=r)
    {
        int mid=l+r>>1;
        ll k1=stack[mid].first,b1=stack[mid].second;
        ll k2=stack[mid+1].first,b2=stack[mid+1].second;
        ld x=ld(b2-b1)/(k1-k2);
        if (k*x+b<=k1*x+b1)
            ans=mid+1,r=mid-1;
        else
            l=mid+1;
    }
    return(ans);
}
ll query(int X)
{
    int l=1,r=top-1,ans=1;
    while (l<=r)
    {
        int mid=l+r>>1;
        ll k1=stack[mid].first,b1=stack[mid].second;
        ll k2=stack[mid+1].first,b2=stack[mid+1].second;
        ld x=ld(b2-b1)/(k1-k2);
        if (x>=X)
            ans=mid,r=mid-1;
        else
            ans=mid+1,l=mid+1;
    }
    return(X*stack[ans].first+stack[ans].second);
}
void dfs(int x,int father)
{
    s[x]=s[father]+f[x];
    ll best=query(p[x]);
    ans[x]=best+p[x]*s[x]+c[x];
    int pos=find(-s[x],ans[x]);
    pair <ll,ll> value=stack[pos];
    int tmp=top;
    stack[top=pos]=make_pair(-s[x],ans[x]);
    for (int i=b[x];i;i=a[i][1])
    {
        int y=a[i][0];
        if (y==father)
            continue;
        dfs(y,x);
    }
    stack[pos]=value;
    top=tmp;
}
void read(int &x)
{
    char ch=getchar();
    while (!isdigit(ch))
        ch=getchar();
    x=0;
    while (isdigit(ch))
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
}
int main()
{
    int T;
    read(T);
    while (T--)
    {
        int n;
        read(n);
        for (int i=1;i<=n;i++)
        {
            read(f[i]);
            read(p[i]);
            read(c[i]);
        }
        memset(b,0,sizeof(b));
        for (int i=1;i<n;i++)
        {
            int x,y;
            read(x);
            read(y);
            a[i][0]=y,a[i][1]=b[x],b[x]=i;
            a[i+n][0]=x,a[i+n][1]=b[y],b[y]=i+n;
        }
        stack[top=1]=make_pair(0,0);
        dfs(1,0);
        static int id=0;
        printf("Case #%d: %lld\n",++id,accumulate(ans+2,ans+n+1,0LL));
    }
    return(0);
}

