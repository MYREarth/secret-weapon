#include <cstdio>
#include <vector>
#include <string>
#include <utility>
#include <map>
using namespace std;
typedef long long ll;
const int c[2][2]={{0,1},{1,0}};
const ll inf=ll(1e18)+26;
char a[40][40];
ll f[40][40];
ll multiply(ll x,ll y)
{
    if (x>inf/y)
        return(inf);
    return(min(inf,x*y));
}
int main()
{
    freopen("kthpath.in","r",stdin);
    freopen("kthpath.out","w",stdout);
    int n,m;
    scanf("%d%d",&n,&m);
    for (int i=1;i<=n;i++)
        scanf("%s",a[i]+1);
    ll K;
    scanf("%lld",&K);
    for (int i=n;i;i--)
        for (int j=m;j;j--)
        {
            if (i==n && j==m)
            {
                f[i][j]=1;
                continue;
            }
            if (i<n)
                f[i][j]=min(inf,f[i][j]+f[i+1][j]);
            if (j<m)
                f[i][j]=min(inf,f[i][j]+f[i][j+1]);
        }
    string ans;
    ans+=a[1][1];
    vector <pair <pair <int,int>,ll> > now;
    now.push_back(make_pair(make_pair(1,1),1));
    for (int i=2;i<n+m;i++)
    {
        map <pair <char,pair <int,int> >,ll> M;
        ll b[26]={0};
        for (int j=0;j<now.size();j++)
        {
            int x0=now[j].first.first,y0=now[j].first.second;
            ll value=now[j].second;
            for (int k=0;k<2;k++)
            {
                int x=x0+c[k][0],y=y0+c[k][1];
                if (x<=n && y<=m)
                {
                    pair <char,pair <int,int> > now=make_pair(a[x][y],make_pair(x,y));
                    M[now]=min(M[now]+value,inf);
                    int id=a[x][y]-'a';
                    b[id]=min(b[id]+multiply(value,f[x][y]),inf);
                }
            }
        }
        char ch;
        for (int j=0;j<26;j++)
        {
            if (K<=b[j])
            {
                ch=j+'a';
                break;
            }
            K-=b[j];
        }
        ans+=ch;
        now.clear();
        for (map <pair <char,pair <int,int> >,ll>::iterator k=M.begin();k!=M.end();k++)
            if (k->first.first==ch)
                now.push_back(make_pair(k->first.second,k->second));
    }
    printf("%s\n",ans.c_str());
    return(0);
}

