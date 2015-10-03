#include <cstdio>
#include <cstring>
#include <vector>
#include <utility>
#include <set>
#include <algorithm>
#define rank __rank__
using namespace std;
const int N=200010;
int n,Log[N],a[N],sa[N],rank[N],height[N],f[18][N];
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
        f[0][i]=height[i];
    for (int i=1;i<=17;i++)
        for (int j=1;j<=n;j++)
        {
            if (j+(1<<i)-1>n)
                break;
            f[i][j]=min(f[i-1][j],f[i-1][j+(1<<i-1)]);
        }
}
int len,l[N];
char s[N];
void palindrome(int n)
{
    l[0]=1;
    for (int i=1,j=0;i!=(n<<1)-1;i++)
    {
        int p=i>>1,q=i-p,r=(j+1>>1)+l[j]-1;
        l[i]=r<q?0:min(r-q+1,l[(j<<1)-i]);
        while (p-l[i]!=-1 && q+l[i]!=n && s[p-l[i]]==s[q+l[i]])
            l[i]++;
        if (q+l[i]-1>r)
            j=i;
    }
}
inline bool cmp(const pair <int,int> &a,const pair <int,int> &b)
{
    return(a.second>b.second);
}
int rmq(int x,int y)
{
    int t=Log[y-x+1];
    return(min(f[t][x],f[t][y-(1<<t)+1]));
}
void calc(int x,int &lcp,int &pos,const set <int> &S)
{
    lcp=0;
    if (x==0)
        return;
    x=rank[n-x+1];
    set <int>::iterator k=S.lower_bound(x);
    if (k!=S.end())
    {
        int tmp=rmq(x+1,*k);
        if (tmp>lcp)
        {
            lcp=tmp;
            pos=sa[*k];
        }
    }
    if (k!=S.begin())
    {
        k--;
        int tmp=rmq(*k+1,x);
        if (tmp>lcp)
        {
            lcp=tmp;
            pos=sa[*k];
        }
    }
}
void solve(int &ans,int &l1,int &r1,int &l2,int &r2)
{
    palindrome(len);
    vector <pair <int,int> > event;
    for (int i=0;i<2*len-1;i++)
    {
        int start=i/2+1;
        if (i&1)
        {
            if (l[i]==0)
                continue;
            event.push_back(make_pair(start-l[i]+1,start+l[i]));
        }
        else
            event.push_back(make_pair(start-l[i]+1,start+l[i]-1));
    }
    sort(event.begin(),event.end(),cmp);
    n=0;
    for (int i=0;i<len;i++)
        a[++n]=s[i];
    a[++n]='#';
    for (int i=len-1;i>=0;i--)
        a[++n]=s[i];
    build();
    set <int> S;
    int now=len;
    ans=0;
    for (int i=0;i<event.size();i++)
    {
        int l=event[i].first,r=event[i].second;
        while (now>r)
            S.insert(rank[now--]);
        int lcp,k;
        calc(l-1,lcp,k,S);
        if (r-l+1+2*lcp>ans)
        {
            ans=r-l+1+2*lcp;
            l1=l-lcp;
            r1=r;
            if (lcp==0)
                l2=r2=-1;
            else
            {
                l2=k;
                r2=k+lcp-1;
            }
        }
    }
}
int reverse(int x)
{
    if (x==-1)
        return(-1);
    return(len-x+1);
}
int main()
{
    scanf("%s",s);
    len=strlen(s);
    int ans,l1,r1,l2,r2;
    solve(ans,l1,r1,l2,r2);
    reverse(s,s+len);
    int ANS,L1,R1,L2,R2;
    solve(ANS,L1,R1,L2,R2);
    if (ans<ANS)
    {
        ans=ANS;
        l1=reverse(R2);
        r1=reverse(L2);
        l2=reverse(R1);
        r2=reverse(L1);
    }
    printf("%d\n%d %d\n%d %d\n",ans,l1,r1,l2,r2);
    return(0);
}

