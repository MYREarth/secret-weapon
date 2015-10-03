#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
int a[200010],f[200010];
vector <int> v,pos[200010];
int main()
{
    int n;
    scanf("%d",&n);
    for (int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
        v.push_back(a[i]);
    }
    sort(v.begin(),v.end());
    v.erase(unique(v.begin(),v.end()),v.end());
    for (int i=1;i<=n;i++)
    {
        a[i]=lower_bound(v.begin(),v.end(),a[i])-v.begin()+1;
        pos[a[i]].push_back(i);
    }
    int ans=n;
    for (int i=n;i;i--)
    {
        int x=a[i];
        if (i!=pos[x].front())
            continue;
        if (pos[x+1].empty() || pos[x].back()<pos[x+1].front())
            f[x]=pos[x].size()+f[x+1];
        else
        {
            f[x]=pos[x].size();
            int tmp=lower_bound(pos[x+1].begin(),pos[x+1].end(),pos[x].back())-pos[x+1].begin();
            f[x]+=pos[x+1].size()-tmp;
        }
        int now=f[x]+lower_bound(pos[x-1].begin(),pos[x-1].end(),pos[x].front())-pos[x-1].begin();
        ans=min(ans,n-now);
    }
    for (int i=1;i<=n;i++)
    {
        int x=a[i];
        int s1=upper_bound(pos[x].begin(),pos[x].end(),i)-pos[x].begin();
        int s2=lower_bound(pos[x+1].begin(),pos[x+1].end(),i)-pos[x+1].begin();
        int now=s1+pos[x+1].size()-s2;
        ans=min(ans,n-now);
    }
    printf("%d\n",ans);
    return(0);
}

