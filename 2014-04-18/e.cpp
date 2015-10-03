#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
int L,R,f[1010],u[100010],v[100010];
int left(int l,int r)
{
    if (l<=L && L<=r)
        return(u[L]);
    return(min(u[l],u[r]));
}
int right(int l,int r)
{
    if (l<=R && R<=r)
        return(v[R]);
    return(max(v[l],v[r]));
}
void change(int l,int r)
{
    f[l]++;
    f[r+1]--;
    if (l>r)
        f[0]++;
}
int main()
{
    int n,A,B;
    scanf("%d%*d%d%d",&n,&A,&B);
    L=R=1;
    for (int i=1;i<=n;i++)
    {
        scanf("%d%d",&u[i],&v[i]);
        if (u[i]<u[L])
            L=i;
        if (v[i]>v[R])
            R=i;
    }
    ll ans=1LL<<60;
    for (int i=1;i<=A;i++)
    {
        memset(f,0,sizeof(f));
        ll tot=0;
        for (int j=i;;j+=A)
        {
            int up=max(1,j-A+1);
            int down=min(j,n);
            int l=left(up,down);
            int r=right(up,down);
            tot+=(r-l)/B+2;
            change((r+1)%B,l%B);
            if (j>=n)
                break;
        }
        for (int i=1;i<=B;i++)
            f[i]+=f[i-1];
        ans=min(ans,tot-*max_element(f,f+B));
    }
    printf("%lld\n",ans);
    return(0);
}

