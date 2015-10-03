#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
namespace gxx
{
    const int N=1000001;
    int n,k,perm[N];
    short selected[N];
    bool visit[N],valid[N];
    vector <vector <int> > cycles[N];
    bool main()
    {
        memset(visit,0,sizeof(visit));
        for (int i=1;i<=n;i++)
            if (!visit[i])
            {
                vector <int> cycle;
                int j=i;
                while (1)
                {
                    visit[j]=true;
                    cycle.push_back(j);
                    j=perm[j];
                    if (i==j)
                        break;
                }
                cycles[cycle.size()].push_back(cycle);
            }
        vector <int> divisors;
        for (int d=1;d*d<=k;d++)
            if (k%d==0)
            {
                divisors.push_back(d);
                divisors.push_back(k/d);
            }
        sort(divisors.begin(),divisors.end());
        divisors.erase(unique(divisors.begin(),divisors.end()),divisors.end());
        for (int l=1;l<=n;l++)
        {
            int m=cycles[l].size();
            if (m==0)
                continue;
            vector <int> choices;
            if (__gcd(l,k)==1)
                choices.push_back(1);
            else
                for (int i=0;i<divisors.size() && divisors[i]<=m;i++)
                    if (__gcd(l,k/divisors[i])==1)
                        choices.push_back(divisors[i]);
            valid[0]=true;
            for (int i=1;i<=m;i++)
            {
                valid[i]=false;
                for (int j=0;j<choices.size() && choices[j]<=i && !valid[i];j++)
                    if (valid[i-choices[j]])
                    {
                        valid[i]=true;
                        selected[i]=j;
                    }
            }
            if (!valid[m])
                return(false);
            for (int i=m;i>0;i-=choices[selected[i]])
            {
                int d=choices[selected[i]];
                vector <int> cycle(d*l);
                for (int j=0;j<d;j++)
                {
                    for (int p=0;p<l;p++)
                        cycle[(j+ll(p)*k)%cycle.size()]=cycles[l].back()[p];
                    cycles[l].pop_back();
                }
                for (int j=0;j<cycle.size();j++)
                    perm[cycle[j]]=cycle[(j+1)%cycle.size()];
            }
        }
        return(true);
    }
}
int a[1000010],b[1000010],c[1000010];
void apply(int n,int a[],int b[])
{
    for (int i=1;i<=n;i++)
        c[i]=b[a[i]];
    for (int i=1;i<=n;i++)
        b[i]=c[i];
}
void inverse(int n,int a[])
{
    for (int i=1;i<=n;i++)
        c[a[i]]=i;
    for (int i=1;i<=n;i++)
        a[i]=c[i];
}
int main()
{
    freopen("permgame.in","r",stdin);
    freopen("permgame.out","w",stdout);
    int n,m;
    scanf("%d%d",&n,&m);
    for (int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    for (int i=1;i<=n;i++)
        scanf("%d",&b[i]);
    if (m&1)
    {
        apply(n,a,b);
        m++;
    }
    gxx::n=n;
    gxx::k=m/2;
    for (int i=1;i<=n;i++)
        gxx::perm[i]=b[i];
    if (!gxx::main())
        printf("-1\n");
    else
    {
        for (int i=1;i<=n;i++)
            b[i]=gxx::perm[i];
        inverse(n,a);
        apply(n,a,b);
        for (int i=1;i<=n;i++)
            printf("%d%c",b[i],i==n?'\n':' ');
    }
    return(0);
}

