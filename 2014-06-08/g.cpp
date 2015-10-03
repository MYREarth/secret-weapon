#include <cstdio>
typedef long long ll;
const int limit=500;
bool big[100010];
int idx,cnt[100010],s[100010],vis[100010],d[100010],b[100010],B[100010],a[200010][2],A[200010][2];
int main()
{
    freopen("guests.in","r",stdin);
    freopen("guests.out","w",stdout);
    int n,m,K;
    scanf("%d%d%d",&n,&m,&K);
    for (int i=1;i<=K;i++)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        d[x]++;
        a[i][0]=y,a[i][1]=b[x],b[x]=i;
        A[i][0]=x,A[i][1]=B[y],B[y]=i;
    }
    for (int i=1;i<=n;i++)
        big[i]=d[i]>=limit;
    ll ans=0;
    for (int i=1;i<=n;i++)
    {
        if (!big[i])
            continue;
        idx++;
        for (int j=b[i];j;j=a[j][1])
        {
            int x=a[j][0];
            vis[x]=idx;
        }
        for (int j=1;j<=n;j++)
        {
            if (big[j] && j<=i)
                continue;
            int cnt=0;
            for (int k=b[j];k;k=a[k][1])
            {
                int x=a[k][0];
                cnt+=vis[x]==idx;
            }
            ans+=ll(cnt)*(cnt-1)/2;
        }
    }
    for (int i=1;i<=m;i++)
    {
        idx++;
        int tot=0;
        for (int j=B[i];j;j=A[j][1])
        {
            int x=A[j][0];
            if (big[x])
                continue;
            for (int k=b[x];k;k=a[k][1])
            {
                int y=a[k][0];
                if (y<=i)
                    continue;
                if (vis[y]!=idx)
                {
                    vis[y]=idx;
                    cnt[y]=0;
                    s[++tot]=y;
                }
                cnt[y]++;
            }
        }
        for (int j=1;j<=tot;j++)
        {
            int x=s[j];
            ans+=ll(cnt[x])*(cnt[x]-1)/2;
        }
    }
    printf("%lld\n",ans);
}

