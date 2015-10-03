#include <cstdio>
#include <cstring>
#include <algorithm>
#define rank __rank__
using namespace std;
typedef long long ll;
const int N=200010;
int n,a[N],sa[N],rank[N],Log[N],height[N];
pair <int,int> f[18][N];
void sort(int a[])
{
    static int f[N],x[N];
    int t=0;
    memset(f,0,sizeof(f));
    for (int i=1;i<=n;i++)
    {
        f[a[i]]++;
        t=max(t,a[i]);
    }
    for (int i=1;i<=t;i++)
        f[i]+=f[i-1];
    for (int i=n;i;i--)
        x[f[a[sa[i]]]--]=sa[i];
    for (int i=1;i<=n;i++)
        sa[i]=x[i];
}
int count(int a[],int b[])
{
    rank[sa[1]]=1;
    int t=1;
    for (int i=2;i<=n;i++)
    {
        if (a[sa[i]]!=a[sa[i-1]] || b[sa[i]]!=b[sa[i-1]])
            t++;
        rank[sa[i]]=t;
    }
    return(t);
}
void build()
{
    Log[1]=0;
    for (int i=2;i<=n;i++)
    {
        Log[i]=Log[i-1];
        if (i&i-1)
            continue;
        Log[i]++;
    }
    a[n+1]=-1;
    static int b[N],c[N];
    for (int i=1;i<=n;i++)
    {
        c[i]=a[i];
        b[i]=-1;
        sa[i]=i;
    }
    sort(c);
    count(b,c);
    for (int k=1;;k<<=1)
    {
        for (int i=1;i<=n;i++)
        {
            c[i]=rank[i];
            b[i]=i+k<=n?rank[i+k]:0;
        }
        sort(b),sort(c);
        if (count(b,c)>=n)
            break;
    }
    int k=0;
    for (int i=1;i<=n;i++)
    {
        k=k?k-1:0;
        if (rank[i]==1)
        {
            height[rank[i]]=0;
            continue;
        }
        int p=sa[rank[i]-1],q=sa[rank[i]];
        while (a[p+k]==a[q+k])
            k++;
        height[rank[i]]=k;
    }
    for (int i=1;i<=n;i++)
        f[0][i]=make_pair(height[i],i);
    for (int i=1;i<=Log[n];i++)
        for (int j=1;j<=n;j++)
        {
            if (j+(1<<i)-1>n)
                break;
            f[i][j]=min(f[i-1][j],f[i-1][j+(1<<i-1)]);
        }
}
pair <int,int> get(int l,int r)
{
    int t=Log[r-l];
    return(min(f[t][l+1],f[t][r-(1<<t)+1]));
}
ll calc(int t)
{
    printf("%d\n",t);
    return((t+1LL)*t/2);
}
ll calc(int l,int r,int pre)
{
    if (l==r)
        return(calc(n-sa[l]-pre));
    pair <int,int> mid=get(l,r);
    return(calc(l,mid.second-1,mid.first)+calc(mid.second,r,mid.first)+calc(mid.first-pre-1));
}
char s[N];
int main()
{
    scanf("%d%s",&n,s);
    for (int i=1;i<=n;i++)
        a[i]=s[i-1];
    build();
    printf("%lld\n",calc(1,n,0));
    return(0);
}

