#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef unsigned long long ull;
const ull lq=10007;
namespace work
{
    const int N=400010;
    int n,a[N],b[N],c[N],sa[N],rank[N],height[N],x[N],f[N];
    void sort(int *a)
    {
        memset(f,0,sizeof(f));
        int t=0;
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
    void build()
    {
        a[n+1]=-1;
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
                b[i]=i+k<=n?rank[i+k]:0;
                c[i]=rank[i];
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
    }
    int lcp[200010],s[200010];
    ull calc(char *s1,int len1,char *s2,int len2,bool *pre,bool *suf)
    {
        n=len1+len2+1;
        for (int i=1;i<=len2;i++)
            a[i]=s2[i];
        a[len2+1]=260;
        for (int i=1;i<=len1;i++)
            a[i+len2+1]=s1[i];
        build();
        int now=0;
        for (int i=1;i<=n;i++)
        {
            int x=sa[i];
            if (x==len2+1)
                now=0;
            else if (x>len2)
                now=1<<30;
            else
            {
                now=min(now,height[i]);
                lcp[x]=now;
            }
        }
        for (int i=n;i;i--)
        {
            int x=sa[i];
            if (x==len2+1)
                now=0;
            else if (x>len2)
                now=height[i];
            else
            {
                lcp[x]=max(lcp[x],now);
                now=min(now,height[i]);
            }
        }
        ull ans=0;
        for (int i=1;i<=len2;i++)
            s[i]=s[i-1]+suf[i];
        for (int i=1;i<=len2;i++)
        {
            if (!pre[i])
                continue;
            int l=i+(len2+1)/2,r=i+lcp[i]-1;
            if (l<=r)
                ans+=s[r]-s[l-1];
            if (2*i-1==len2 && lcp[i]>=i)
                ans++;
        }
        return(ans);
    }
}
bool pre[200010],suf[200010];
ull ha[200010],rev[200010],p[200010];
inline ull Hash(int i,int len,int n)
{
    if (i+len-1>n)
        return(0);
    return(ha[i+len-1]-ha[i-1]*p[len]);
}
inline ull revhash(int i,int len)
{
    if (i-len+1<1)
        return(0);
    return(rev[i-len+1]-rev[i+1]*p[len]);
}
void init(char *a,int n)
{
    p[0]=1;
    for (int i=1;i<=n;i++)
    {
        ha[i]=ha[i-1]*lq+a[i];
        p[i]=p[i-1]*lq;
    }
    rev[n+1]=0;
    for (int i=n;i;i--)
        rev[i]=rev[i+1]*lq+a[i];
    for (int i=1;i<=n;i++)
    {
        pre[i]=Hash(i+1,i-1,n)==revhash(i-1,i-1);
        suf[i]=Hash(i+1,n-i,n)==revhash(i-1,n-i);
    }
}
char a[200010],b[200010];
int main()
{
    scanf("%s%s",a+1,b+1);
    int n=strlen(a+1),m=strlen(b+1);
    init(b,m);
    ull ans=work::calc(a,n,b,m,pre,suf);
    reverse(a+1,a+n+1);
    ans+=work::calc(a,n,b,m,pre,suf);
    if (m==1)
        ans>>=1;
    printf("%llu\n",ans);
    return(0);
}

