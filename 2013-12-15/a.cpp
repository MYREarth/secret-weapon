#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
int a[110],b[110],l[110],r[100],dep[110],dep1[110];
bool flag[110];
void dfs(int x)
{
    flag[x]&=a[x]==b[x];
    for (int i=l[x];i;i=r[i])
    {
        dep[i]=dep[x]+1;
        dfs(i);
        if (!flag[i])
            flag[x]=false;
    }
}
void build(int *a,int n)
{
    memset(l,0,sizeof(l));
    memset(r,0,sizeof(r));
    for (int i=1;i<=n;i++)
    {
        int x=a[i];
        if (x==0)
            continue;
        if (l[x]==0)
            l[x]=i;
        else
        {
            int p=l[x];
            while (r[p])
                p=r[p];
            r[p]=i;
        }
    }
}
struct state
{
    int a,b;
    state(int a,int b):a(a),b(b){}
};
inline bool operator <(const state &a,const state &b)
{
    return(dep[a.a]<dep[b.a]);
}
int main()
{
    freopen("bag-repacking.in","r",stdin);
    freopen("bag-repacking.out","w",stdout);
    int n;
    scanf("%d",&n);
    for (int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    build(a,n);
    for (int i=1;i<=n;i++)
        scanf("%d",&b[i]);
    memset(flag,true,sizeof(flag));
    for (int i=1;i<=n;i++)
        if (a[i]==0)
            dfs(i);
    memcpy(dep1,dep,sizeof(dep));
    build(b,n);
    for (int i=1;i<=n;i++)
        if (b[i]==0)
        {
            dep[i]=0;
            dfs(i);
        }
    vector <state> out;
    for (int i=1;i<=n;i++)
        if (!flag[i] && a[i]!=0)
            out.push_back(state(i,a[i]));
    vector <state> in;
    for (int i=1;i<=n;i++)
        if (!flag[i] && b[i]!=0)
            in.push_back(state(i,b[i]));
    sort(in.begin(),in.end());
    reverse(in.begin(),in.end());
    memcpy(dep,dep1,sizeof(dep1));
    sort(out.begin(),out.end());
    printf("%d\n",in.size()+out.size());
    for (int i=0;i<out.size();i++)
        printf("out %d %d\n",out[i].a,out[i].b);
    for (int i=0;i<in.size();i++)
        printf("in %d %d\n",in[i].a,in[i].b);
    return(0);
}

