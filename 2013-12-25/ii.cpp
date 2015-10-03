#include <cstdio>
#include <cstring>
#include <cctype>
#include <utility>
#include <numeric>
#include <algorithm>
#pragma comment(linker,"/STACK:16777216")
using namespace std;
typedef long long ll;
int top,fa[400010],b[400010],f[400010],p[400010],c[400010],a[800010][2];
ll s[400010],ans[400010];
pair <ll,ll> stack[400010];
void dfs(int x,int father)
{
    s[x]=s[father]+f[x];
    fa[x]=father;
    ans[x]=1LL<<60;
    for (int i=fa[x];i!=-1;i=fa[i])
    {
        ans[x]=min(ans[x],ans[i]+(s[x]-s[i])*p[x]+c[x]);
    }
    for (int i=b[x];i;i=a[i][1])
    {
        int y=a[i][0];
        if (y==father)
            continue;
        dfs(y,x);
    }
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
        fa[0]=-1;
        dfs(1,0);
        static int id=0;
        printf("Case #%d: %lld\n",++id,accumulate(ans+2,ans+n+1,0LL));
    }
    return(0);
}

