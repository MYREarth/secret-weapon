#include <cstdio>
#include <cstring>
#include <cctype>
#include <string>
#include <valarray>
using namespace std;
typedef long long ll;
const ll mod=1000000000;
typedef valarray <ll> data;
inline data add(const data &a,const data &b)
{
    if (a.size()==1)
        return((a[0]+b)%mod);
    if (b.size()==1)
        return((a+b[0])%mod);
    return((a+b)%mod);
}
inline data subtract(const data &a,const data &b)
{
    if (a.size()==1)
        return((a[0]-b+mod)%mod);
    if (b.size()==1)
        return((a-b[0]+mod)%mod);
    return((a-b+mod)%mod);
}
inline data multiply(const data &a,const data &b)
{
    if (a.size()==1)
        return(a[0]*b%mod);
    if (b.size()==1)
        return(a*b[0]%mod);
    return(a*b%mod);
}
inline data calc(const data &a,char op,const data &b)
{
    if (op=='+')
        return(add(a,b));
    if (op=='-')
        return(subtract(a,b));
    return(multiply(a,b));
}
inline data square(const data &a)
{
    return(multiply(a,a));
}
inline data negative(const data &a)
{
    return((mod-a)%mod);
}
inline data sum(const data &a)
{
    return(data(a.sum()%mod,1));
}
data a,ans[100010];
char buf[100010],op[100010];
string s;
int ansn,opn;
int main()
{
//    freopen("j.in","r",stdin);
//    freopen("j.out","w",stdout);
    int n;
    scanf("%d",&n);
    a.resize(n);
    for (int i=0;i<n;i++)
        scanf("%lld",&a[i]);
    scanf("%s",buf);
    int len=strlen(buf);
    for (int i=0;i<len;i++)
        if (buf[i]=='+' && buf[i+1]=='/')
        {
            s+='#';
            i++;
        }
        else if (buf[i]=='*' && buf[i+1]==':')
        {
            s+='^';
            i++;
        }
        else if (buf[i]=='-' && (i==0 || buf[i-1]!=')' && !isalnum(buf[i-1])))
            s+='~';
        else
            s+=buf[i];
    reverse(s.begin(),s.end());
    for (int i=0;i<s.size();i++)
    {
        if (s[i]==')')
        {
            op[++opn]=s[i];
            continue;
        }
        if (s[i]=='^')
        {
            ans[ansn]=square(ans[ansn]);
            continue;
        }
        else if (s[i]=='~')
        {
            ans[ansn]=negative(ans[ansn]);
            continue;
        }
        else if (s[i]=='#')
        {
            ans[ansn]=sum(ans[ansn]);
            continue;
        }
        else if (s[i]=='+' || s[i]=='-' || s[i]=='*')
        {
            op[++opn]=s[i];
            continue;
        }
        else if (isdigit(s[i]))
        {
            int p=1,now=0;
            while (1)
            {
                now+=p*(s[i]-'0');
                if (i+1==s.size() || !isdigit(s[i+1]))
                    break;
                i++;
                p*=10;
            }
            ans[++ansn]=data(now,1);
        }
        else if (s[i]=='X')
            ans[++ansn]=a;
        else if (s[i]=='N')
            ans[++ansn]=data(n,1);
        else
            opn--;
        if (opn!=0 && op[opn]!=')')
        {
            ansn--;
            ans[ansn]=calc(ans[ansn+1],op[opn--],ans[ansn]);
        }
    }
    printf("%lld\n",ans[ansn][0]);
    return(0);
}

