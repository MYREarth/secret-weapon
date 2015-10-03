#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
inline ll C(ll n,int m)
{
    ll ret=1;
    for (int i=1;i<=m;i++)
        ret*=(n-i+1);
    for (int i=1;i<=m;i++)
        ret/=i;
    return(ret);
}
pair <int,int> a[16000010];
ll calc(ll n)
{
    ll ret=0;
    int tot=0;
    for (int i=0;i<n;i++)
        for (int j=0;j<n;j++)
        {
            int p=(i+1)*(j+1),q=(n-i)*(n-j);
            int t=__gcd(p,q);
            p/=t,q/=t;
            a[++tot]=make_pair(p,q);
        }
    sort(a+1,a+tot+1);
    for (int i=1,j;i<=tot;i=j)
    {
        int cnt=0;
        for (j=i;j<=tot && a[i]==a[j];j++)
            cnt++;
        ret+=ll(cnt)*cnt;
    }
    return(ret);
}
int main()
{
    freopen("tetrahedron.in","r",stdin);
    freopen("tetrahedron.out","w",stdout);
    ll n;
    scanf("%lld",&n);
    n--;
    ll tot=C(n*6,4);
    tot-=C(n,4)*6;
    tot-=C(n,3)*n*30;
    tot-=C(n,2)*C(n,2)*12;
    tot-=C(n,2)*n*n*12;
    tot-=calc(n)*3;
    printf("%lld\n",tot);
    return(0);
}

