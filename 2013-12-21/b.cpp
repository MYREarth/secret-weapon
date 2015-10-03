#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
char a[200010];
int main()
{
    freopen("bad.in","r",stdin);
    freopen("bad.out","w",stdout);
    scanf("%s",a+1);
    int n=strlen(a+1);
    int cnt=count(a+1,a+n+1,'1');
    int ans=1<<30,t=1;
    for (int i=1;i<=n;i++)
    {
        while (t<=n && (t==i || a[t]=='0'))
            t++;
        if (t>n)
            break;
        ans=min(ans,2*(i-1)+n-t+1);
    }
    t=n;
    for (int i=n;i;i--)
    {
        while (t>1 && (t==i || a[t]=='0'))
            t--;
        if (t==1)
            break;
        ans=min(ans,2*(n-i+1)+t-1);
    }
    t=0;
    for (int i=1;i<=n;i++)
    {
        t+=a[i]=='1';
        if (t==cnt)
        {
            ans=min(ans,i-1);
            break;
        }
    }
    t=0;
    for (int i=n;i>1;i--)
    {
        t+=a[i]=='1';
        if (t==cnt)
        {
            ans=min(ans,n-i+1);
            break;
        }
    }
    if (cnt==0)
        ans=0;
    printf("%d\n",ans*7+cnt*4);
    return(0);
}

