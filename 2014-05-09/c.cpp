#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
char s[200010];
int lo[200010],le[200010],ro[200010],re[200010],l[400010];
ll init(int n)
{
    l[0]=1;
    for (int i=1,j=0;i!=(n<<1)-1;i++)
    {
        int p=i>>1,q=i-p,r=(j+1>>1)+l[j]-1;
        l[i]=r<q?0:min(r-q+1,l[(j<<1)-i]);
        while (p-l[i]!=-1 && q+l[i]!=n && s[p-l[i]]==s[q+l[i]])
            l[i]++;
        if (q+l[i]-1>r)
            j=i;
    }
    ll ret=0;
    for (int i=0;i<2*n-1;i+=2)
    {
        ret+=l[i];
        int pos=i/2+1;
        ro[pos]++;
        ro[pos+l[i]]--;
        lo[pos-1]++;
        lo[pos-l[i]-1]--;
    }
    for (int i=1;i<2*n-1;i+=2)
    {
        ret+=2*l[i];
        int pos=i/2+1;
        re[pos+1]++;
        re[pos+l[i]+1]--;
        le[pos-1]++;
        le[pos-l[i]-1]--;
    }
    for (int i=2;i<n;i++)
    {
        re[i]+=re[i-1];
        ro[i]+=ro[i-1];
    }
    for (int i=n-2;i>=1;i--)
    {
        le[i]+=le[i+1];
        lo[i]+=lo[i+1];
    }
    return(ret);
}
int main()
{
    scanf("%s",s);
    int len=strlen(s);
    ll ans=init(len);
    for (int i=1;i<len;i++)
        ans+=ll(lo[i])*re[i]+ll(le[i])*ro[i]+2LL*le[i]*re[i];
    printf("%lld\n",ans);
    return(0);
}

