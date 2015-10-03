#include <cstdio>
#include <utility>
#include <set>
#include <algorithm>
using namespace std;
typedef long long ll;
pair <int,int> a[100010];
int main()
{
    int n;
    scanf("%d",&n);
    for (int i=1;i<=n;i++)
        scanf("%d%d",&a[i].first,&a[i].second);
    sort(a+1,a+n+1);
    multiset <int> S;
    ll now,ans=0;
    for (int i=1;i<=n;i++)
    {
        while (!S.empty())
        {
            int t=*S.begin();
            S.erase(S.begin());
            if (t>a[i].first-now)
            {
                S.insert(t-(a[i].first-now));
                break;
            }
            now+=t;
            ans+=now;
        }
        S.insert(a[i].second);
        now=a[i].first;
    }
    while (!S.empty())
    {
        now+=*S.begin();
        ans+=now;
        S.erase(S.begin());
    }
    printf("%lld\n",ans);
    return(0);
}

