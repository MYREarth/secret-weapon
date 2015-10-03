#include <cstdio>
#include <cstdlib>
#include <map>
#include <queue>
using namespace std;
typedef long long ll;
const int N=200010;
int deg[N],cnt[N],d[N],q[N],ans[N],b[N],a[N*2][2];
int work(int S,int mi)
{
    int l,r;
    q[l=r=1]=S;
    d[S]=1;
    while (l<=r)
    {
        int x=q[l++];
        for (int i=b[x];i;i=a[i][1])
        {
            int y=a[i][0];
            if (!d[y])
            {
                d[y]=d[x]+1;
                q[++r]=y;
            }
        }
    }
    int tot=0;
    for (int i=1;i<=r;i++)
    {
        int x=q[i];
        if (d[x]!=2)
            continue;
        tot++;
        for (int j=b[x];j;j=a[j][1])
        {
            int y=a[j][0];
            cnt[y]++;
        }
    }
    int t=0;
    for (int i=1;i<=r;i++)
    {
        int x=q[i];
        if (d[x]!=3)
            continue;
        if (cnt[x]==tot && deg[x]==deg[S])
            d[x]=1;
        else
            t=x;
    }
    queue <int> Q;
    for (int i=1;i<=r;i++)
    {
        int x=q[i];
        if (d[x]!=2)
            continue;
        ans[x]=1;
        for (int j=b[x];j;j=a[j][1])
        {
            int y=a[j][0];
            if (y==t)
            {
                ans[x]=-1;
                break;
            }
        }
        Q.push(x);
    }
    while (!Q.empty())
    {
        int x=Q.front();
        Q.pop();
        for (int i=b[x];i;i=a[i][1])
        {
            int y=a[i][0];
            if (!ans[y] && d[y]!=1)
            {
                ans[y]=ans[x]>0?ans[x]+1:ans[x]-1;
                Q.push(y);
            }
        }
    }
    int u=1<<30,v=-1<<30;
    for (int i=1;i<=r;i++)
    {
        int x=q[i];
        u=min(u,ans[x]);
        v=max(v,ans[x]);
    }
    for (int i=1;i<=r;i++)
    {
        int x=q[i];
        ans[x]+=mi-u;
    }
    return(mi+v-u);
}
bool check(int n,int m)
{
    map <int,int> M;
    for (int i=1;i<=n;i++)
    {
        for (int j=b[i];j;j=a[j][1])
        {
            int y=a[j][0];
            if (abs(ans[i]-ans[y])!=1)
                return(false);
        }
        M[ans[i]]++;
    }
    int prev=-1,num=0;
    ll tot=0;
    for (map <int,int>::iterator k=M.begin();k!=M.end();k++)
    {
        if (k->first==prev+1)
            tot+=ll(num)*k->second;
        prev=k->first;
        num=k->second;
    }
    return(tot==m);
}
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    for (int i=1;i<=m;i++)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        a[i][0]=y,a[i][1]=b[x],b[x]=i;
        a[i+m][0]=x,a[i+m][1]=b[y],b[y]=i+m;
        deg[x]++,deg[y]++;
    }
    int mi=1;
    for (int i=1;i<=n;i++)
        if (!d[i])
            mi=work(i,mi)+2;
    if (!check(n,m))
        printf("NET\n");
    else
    {
        printf("DA\n");
        for (int i=1;i<=n;i++)
            printf("%d%c",ans[i],i==n?'\n':' ');
    }
    return(0);
}

