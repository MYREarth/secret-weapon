#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
int a[200010];
vector <int> pos[200010];
void work(int n)
{
    vector <int> value;
    for (int i=1;i<=n;i++)
        value.push_back(a[i]);
    sort(value.begin(),value.end());
    value.erase(unique(value.begin(),value.end()),value.end());
    for (int i=1;i<=n;i++)
    {
        a[i]=lower_bound(value.begin(),value.end(),a[i])-value.begin()+1;
        pos[a[i]].push_back(i);
    }
}
int n,ans[200010],start[200010],value[200010],c[200010],f[200010];
inline bool cmp(int x,int y)
{
    return(start[x]>start[y]);
}
void modify(int x,int value)
{
    for (int i=x;i<=n;i+=i&-i)
        f[i]+=value;
}
int query(int x)
{
    int ret=0;
    for (int i=x;i;i-=i&-i)
        ret+=f[i];
    return(ret);
}
int next(int x,int p)
{
    vector <int>::iterator k=upper_bound(pos[x].begin(),pos[x].end(),p);
    if (k==pos[x].end())
        return(n+1);
    return(*k);
}
int get(int x,int p)
{
    return(*lower_bound(pos[x].begin(),pos[x].end(),p));
}
int main()
{
    freopen("data.in","r",stdin);
    freopen("data.out","w",stdout);
    scanf("%d",&n);
    for (int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    work(n);
    int m;
    scanf("%d",&m);
    for (int i=1;i<=m;i++)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        start[i]=x;
        value[i]=a[x+y-1];
        c[i]=i;
    }
    sort(c+1,c+m+1,cmp);
    int now=1;
    for (int i=n;i;i--)
    {
        int x=a[i];
        modify(i,1);
        modify(next(x,i),-1);
        while (now<=m)
        {
            int y=c[now];
            if (start[y]!=i)
                break;
            int t=get(value[y],i);
            ans[y]=query(t);
            now++;
        }
    }
    for (int i=1;i<=m;i++)
        printf("%d\n",ans[i]);
    return(0);
}

