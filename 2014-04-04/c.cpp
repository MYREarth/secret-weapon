#include <cstdio>
#include <cstring>
#include <utility>
#include <map>
using namespace std;
typedef unsigned long long ull;
struct state
{
    int pos,len;
    ull value;
    state(int pos,int len,ull value):pos(pos),len(len),value(value){}
};
inline bool operator <(const state &a,const state &b)
{
    return(a.len>b.len || a.len==b.len && (a.value<b.value || a.value==b.value && a.pos<b.pos));
}
const int lq=10007;
char a[50010];
map <ull,int> odd,even;
ull ans,ha[50010],rev[50010],p[50010];
inline ull hash(int pos,int len)
{
    return(ha[pos+len-1]-ha[pos-1]*p[len]);
}
inline ull revhash(int pos,int len)
{
    return(rev[pos-len+1]-rev[pos+1]*p[len]);
}
void calc(int n,bool first)
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
    map <state,int> M;
    for (int i=1;i<=n;i++)
    {
        int l=1,r=n,ans=0;
        while (l<=r)
        {
            int mid=l+r>>1;
            if (i+mid-1<=n && i-mid+1>=1 && hash(i,mid)==revhash(i,mid))
                ans=mid,l=mid+1;
            else
                r=mid-1;
        }
        if (ans!=0)
            M[state(i,ans,hash(i,ans))]=1;
    }
    while (!M.empty())
    {
        int len=M.begin()->first.len,pos=M.begin()->first.pos,cnt=M.begin()->second;
        ull now=M.begin()->first.value;
        M.erase(M.begin());
        while (!M.empty() && M.begin()->first.len==len && M.begin()->first.value==now)
        {
            cnt+=M.begin()->second;
            M.erase(M.begin());
        }
        if (len>1)
            M.insert(make_pair(state(pos,len-1,hash(pos,len-1)),cnt));
        if (first)
            odd[now]=cnt;
        else if (odd.count(now))
            ans+=ull(cnt)*odd[now];
    }
    M.clear();
    for (int i=1;i<=n;i++)
    {
        int l=1,r=n,ans=0;
        while (l<=r)
        {
            int mid=l+r>>1;
            if (i+mid-1<=n && i-mid>=1 && hash(i,mid)==revhash(i-1,mid))
                ans=mid,l=mid+1;
            else
                r=mid-1;
        }
        if (ans!=0)
            M[state(i,ans,hash(i,ans))]=1;
    }
    while (!M.empty())
    {
        int len=M.begin()->first.len,pos=M.begin()->first.pos,cnt=M.begin()->second;
        ull now=M.begin()->first.value;
        M.erase(M.begin());
        while (!M.empty() && M.begin()->first.len==len && M.begin()->first.value==now)
        {
            cnt+=M.begin()->second;
            M.erase(M.begin());
        }
        if (len>1)
            M.insert(make_pair(state(pos,len-1,hash(pos,len-1)),cnt));
        if (first)
            even[now]=cnt;
        else if (even.count(now))
            ans+=ull(cnt)*even[now];
    }
}
int main()
{
    scanf("%s",a+1);
    int len=strlen(a+1);
    calc(len,true);
    scanf("%s",a+1);
    len=strlen(a+1);
    calc(len,false);
    printf("%llu\n",ans);
    return(0);
}

