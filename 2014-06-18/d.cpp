#include <cstdio>
#include <string>
#define hash __hash__
using namespace std;
typedef unsigned long long ull;
const int lq=1000000007;
string s[110];
ull ans[110],h[200010],h1[200010],h2[200010],p[200010];
void init()
{
    s[0]="0";
    s[1]="1";
    for (int i=2;;i++)
    {
        s[i]=s[i-1]+s[i-2];
        if (s[i-1].size()>=100000)
            break;
    }
    p[0]=1;
    for (int i=1;i<=200000;i++)
        p[i]=p[i-1]*lq;
}
char buf[100010];
void hash(const string &s,ull a[])
{
    for (int i=1;i<=s.size();i++)
        a[i]=a[i-1]*lq+s[i-1];
}
ull get(ull h[],int start,int len)
{
    return(h[start+len-1]-h[start-1]*p[len]);
}
bool pre[100010],suf1[100010],suf2[100010];
void prefix(ull s[],int n,bool pre[])
{
    for (int i=1;i<=n;i++)
        pre[i]=get(h,n-i+1,i)==get(s,1,i);
}
void suffix(ull s[],int m,int n,bool suf[])
{
    for (int i=1;i<=n;i++)
        suf[i]=get(s,m-i+1,i)==get(h,1,i);
}
int cnt(ull s[],int m,int n)
{
    int ret=0;
    for (int i=n;i<=m;i++)
        ret+=get(s,i-n+1,n)==get(h,1,n);
    return(ret);
}
int main()
{
    init();
    int n;
    while (scanf("%d%s",&n,buf)==2)
    {
        string a=buf;
        int pos=-1;
        for (int i=0;i<=n;i++)
            if (s[i].size()>=a.size())
            {
                pos=i;
                break;
            }
        static int id=0;
        printf("Case %d: ",++id);
        if (pos==-1)
        {
            printf("0\n");
            continue;
        }
        hash(a,h);
        hash(s[pos],h1);
        hash(s[pos+1],h2);
        prefix(h1,a.size(),pre);
        suffix(h1,s[pos].size(),a.size(),suf1);
        suffix(h2,s[pos+1].size(),a.size(),suf2);
        int odd=0,even=0;
        for (int i=1;i<a.size();i++)
        {
            odd+=suf1[i] && pre[a.size()-i];
            even+=suf2[i] && pre[a.size()-i];
        }
        if (pos&1)
            swap(odd,even);
        ans[pos]=cnt(h1,s[pos].size(),a.size());
        ans[pos+1]=cnt(h2,s[pos+1].size(),a.size());
        for (int i=pos+2;i<=n;i++)
            ans[i]=ans[i-1]+ans[i-2]+(i&1?odd:even);
        printf("%llu\n",ans[n]);
    }
    return(0);
}

