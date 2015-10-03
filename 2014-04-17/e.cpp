#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
struct state
{
    ll a[3];
    state(ll x,ll y,ll z)
    {
        a[0]=x,a[1]=y,a[2]=z;
    }
    state divide(int t) const
    {
        if (t==2)
            return(divide(a[0],a[2]));
        return(divide(a[0],a[1]));
    }
    state divide(ll u,ll v) const
    {
        if (u<v/2)
            return(state(u,v/2,v-v/2));
        if (v==1)
            return(state(0,1,1));
        if (u==v)
            return(state(1,v-1,u));
        return(state(1,u,v-1));
    }
};
inline bool operator <(const state &a,const state &b)
{
    if (a.a[0]==0 && b.a[0]!=0)
        return(true);
    if (b.a[0]==0)
        return(false);
    return(a.a[1]<b.a[1]);
}
int main()
{
    freopen("eating.in","r",stdin);
    freopen("eating.out","w",stdout);
    while (1)
    {
        ll a,b,c;
        scanf("%lld%lld%lld",&a,&b,&c);
        if (a==0 && b==0 && c==0)
            break;
        vector <ll> ans;
        state now(a,b,c);
        sort(now.a,now.a+3);
        for (int i=1;;i++)
        {
            if (now.a[0]==0)
                break;
            int t=0;
            state best=now.divide(0);
            for (int j=1;j<3;j++)
                if (best<now.divide(j))
                {
                    t=j;
                    best=now.divide(j);
                }
            ans.push_back(t==2?now.a[1]:now.a[2]);
            now=now.divide(t);
        }
        static int id=0;
        printf("Case #%d:\n",++id);
        printf("%d\n",ans.size());
        for (int i=0;i<ans.size();i++)
            printf("%lld%c",ans[i],i+1==ans.size()?'\n':' ');
    }
    return(0);
}

