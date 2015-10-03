#include <cstdio>
#include <cstring>
#include <string>
#include <stack>
#include <queue>
#include <vector>
#include <utility>
#include <algorithm>
#include <cassert>
using namespace std;
typedef long long ull;
const int N=500010;
const ull magic=10007,mod=1000000007;
char s[N];
int anslen,anscnt,ansl,ansr,n,len,next[N],a[N],size[N],position[N],to[N],p[N];
ull ans;
pair <ull,ull> power[N],hash[N];
void init()
{
    memset(next,-1,sizeof(next));
    stack <int> S;
    for (int i=1;i<=len;i++)
        if (s[i]=='0')
            S.push(i);
        else if (!S.empty())
        {
            next[S.top()]=i;
            S.pop();
        }
    power[0]=make_pair(1,1);
    for (int i=1;i<=len;i++)
    {
        power[i].first=power[i-1].first*3;
        power[i].second=power[i-1].second*magic%mod;
    }
    for (int i=len;i;i--)
    {
        if (next[i]==-1)
            continue;
        hash[i].first=power[next[i]-i].first+2;
        hash[i].second=(power[next[i]-i].second*26+1)%mod;
        if (next[i]!=i+1)
        {
            hash[i].first+=hash[i+1].first*3;
            hash[i].second=(hash[i].second+hash[i+1].second*magic)%mod;
        }
    }
    vector <pair <ull,ull> > lq;
    for (int i=len;i;i--)
    {
        if (next[i]==-1)
            continue;
        lq.push_back(hash[i]);
        if (next[next[i]+1]!=-1)
            to[i]=to[next[i]+1];
        else
            to[i]=next[i];
    }
    sort(lq.begin(),lq.end());
    lq.erase(unique(lq.begin(),lq.end()),lq.end());
    int cnt=0;
    for (int i=1;i<=len;i++)
        if (next[i]!=-1)
        {
            p[i]=lower_bound(lq.begin(),lq.end(),hash[i])-lq.begin()+1;
            cnt++;
        }
    queue <int> Q;
    for (int i=1;i<=len;i++)
        if (next[i]!=-1)
        {
            Q.push(i);
            i=to[i];
        }
    while (!Q.empty())
    {
        int l=Q.front(),r=to[l];
        Q.pop();
        bool flag=false;
        if (r-l+1>ans)
        {
            ans=r-l+1;
            anslen=r-l+1;
            anscnt=1;
            ansl=l;
            flag=true;
        }
        for (int i=l;i<=r;i++)
        {
            if (flag)
                ansr=i;
            if (next[i]!=i+1)
                Q.push(i+1);
            a[++n]=p[i];
            size[n]=next[i]-i+1;
            position[n]=i;
            i=next[i];
        }
        a[++n]=++cnt;
        size[n]=0;
    }
}
int sa[N],rank[N],height[N],f[N],x[N];
void sort(int *a)
{
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
int b[N],c[N];
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
}
int log[N],st[20][N];
ull sum[N];
void calc(int l,int r)
{
    if (l>=r)
        return;
    int t=log[r-l],u=st[t][l+1],v=st[t][r-(1<<t)+1];
    int pos=height[u]<height[v]?u:v,value=height[pos];
    if (size[sa[l]]!=0)
    {
        int now=sum[sa[pos]+value-1]-sum[sa[pos]-1];
        if (ull(now)*(r-l+1)>ans)
        {
            ans=ull(now)*(r-l+1);
            anslen=now;
            anscnt=r-l+1;
            ansl=position[sa[pos]];
            ansr=position[sa[pos]+value-1];
        }
    }
    calc(l,pos-1);
    calc(pos,r);
}
void getans()
{
    sum[0]=0;
    for (int i=1;i<=n;i++)
        sum[i]=sum[i-1]+size[i];
    log[1]=0;
    for (int i=2;i<=n;i++)
    {
        log[i]=log[i-1];
        if (i&i-1)
            continue;
        log[i]++;
    }
    for (int i=1;i<=n;i++)
        st[0][i]=i;
    for (int i=1;i<=log[n];i++)
        for (int j=1;j<=n;j++)
        {
            if (j+(1<<i)-1>n)
                break;
            int p=height[st[i-1][j]],q=height[st[i-1][j+(1<<i-1)]];
            st[i][j]=p<q?st[i-1][j]:st[i-1][j+(1<<i-1)];
        }
    calc(1,n);
}
bool check(const string &s)
{
    int now=0;
    for (int i=0;i<s.size();i++)
    {
        if (s[i]!='0' && s[i]!='1')
            return(false);
        if (s[i]=='0')
            now++;
        else
            now--;
        if (now<0)
            return(false);
    }
    return(now==0);
}
ull hehe[N];
int main()
{
 //   freopen("abyss.in","r",stdin);
  //  freopen("abyss.out","w",stdout);
    scanf("%s",s+1);
    len=strlen(s+1);
    init();
    build();
    getans();
    printf("%lld\n",ans);
    string final;
    for (int i=ansl;i<=ansr;i++)
    {
        for (int j=i;j<=next[i];j++)
            final+=s[j];
        i=next[i];
    }
    printf("%s\n",final.c_str());
    for (int i=1;i<=len;i++)
        hehe[i]=(hehe[i-1]*magic+s[i])%mod;
    ull lq=0;
    for (int i=0;i<final.size();i++)
        lq=(lq*magic+final[i])%mod;
    int cnt=0;
    for (int i=final.size();i<=len;i++)
    {
        ull now=((long long)hehe[i]-hehe[i-final.size()]*power[final.size()].second)%mod;
        if (now<0)
            now+=mod;
        cnt+=now==lq;
    }
    assert(anscnt==cnt);
    //assert(check(final));
    //assert(ans==cnt*ull(final.size()));
    return(0);
}

