#include <cstdio>
#include <cstring>
#include <algorithm>
#define rank RANK
using namespace std;
typedef long long ll;
const int N=100010;
int n,a[N],sa[N],rank[N],height[N],f[17][N];
void sort(int *a)
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
    for  (int i=1;i<=n;i++)
        sa[i]=x[i];
}
int count(int *a,int *b)
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
inline int best(int i,int j)
{
    return(height[i]<height[j]?i:j);
}
void build()
{
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
        f[0][i]=i;
    for (int i=1;i<=16;i++)
        for (int j=1;j<=n;j++)
        {
            if (j+(1<<i)-1>n)
                break;
            f[i][j]=best(f[i-1][j],f[i-1][j+(1<<i-1)]);
        }
}
int Log[N];
int query(int x,int y)
{
    int t=Log[y-x+1];
    return(best(f[t][x],f[t][y-(1<<t)+1]));
}
ll calc(int l,int r)
{
    if (l==r)
        return(0);
    int t=query(l+1,r);
    return(ll(t-l)*(r-t+1)*height[t]+calc(l,t-1)+calc(t,r));
}
char s[N];
int main()
{
    freopen("borders.in","r",stdin);
    scanf("%s",s);
    printf("%d %d %d\n",l,r,t);
    n=strlen(s);
    Log[1]=0;
    for (int i=2;i<=n;i++)
    {
        Log[i]=Log[i-1];
        if (i&i-1)
            continue;
        Log[i]++;
    }
    for (int i=1;i<=n;i++)
        a[i]=s[i-1];
    build();
    printf("%lld\n",calc(1,n));
    return(0);
}

