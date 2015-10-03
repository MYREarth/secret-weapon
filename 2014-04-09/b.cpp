#include <cstdio>
#include <set>
using namespace std;
typedef long long ll;
struct point
{
    int x,y;
    point(){}
    point(int x,int y):x(x),y(y){}
};
inline point operator -(const point &a,const point &b)
{
    return(point(a.x-b.x,a.y-b.y));
}
inline ll det(const point &a,const point &b)
{
    return(ll(a.x)*b.y-ll(a.y)*b.x);
}
inline ll area(const point &a,const point &b,const point &c)
{
    return(det(b-a,c-a));
}
int N;
point a[200010];
ll s[200010],c[200010];
set <int> S;
void modify(int x,ll value)
{
    for (int i=x;i<=N;i+=i&-i)
        c[i]+=value;
}
ll query(int x)
{
    ll ret=0;
    for (int i=x;i;i-=i&-i)
        ret+=c[i];
    return(ret);
}
int lower(int x)
{
    set <int>::iterator k=S.lower_bound(x);
    if (k==S.begin())
        return(-1);
    return(*--k);
}
int upper(int x)
{
    set <int>::iterator k=S.upper_bound(x);
    if (k==S.end())
        return(-1);
    return(*k);
}
void del(int x)
{
    int p=lower(x),q=upper(x);
    if (p!=-1)
        modify(x,-area(a[0],a[p],a[x]));
    if (q!=-1)
        modify(q,-area(a[0],a[x],a[q]));
    if (p!=-1 && q!=-1)
        modify(q,area(a[0],a[p],a[q]));
    S.erase(x);
}
void add(int x)
{
    int p=lower(x),q=upper(x);
    if (p!=-1 && q!=-1)
        modify(q,-area(a[0],a[p],a[q]));
    if (p!=-1)
        modify(x,area(a[0],a[p],a[x]));
    if (q!=-1)
        modify(q,area(a[0],a[x],a[q]));
    S.insert(x);
}
int main()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    int n;
    scanf("%d",&n);
    for (int i=1;i<=n;i++)
    {
        scanf("%d%d",&a[i].x,&a[i].y);
        a[i+n]=a[i];
    }
    a[0]=point(0,0);
    s[1]=0;
    N=n<<1;
    for (int i=2;i<=N;i++)
        s[i]=area(a[0],a[i-1],a[i]);
    for (int i=1;i<=N;i++)
    {
        S.insert(i);
        modify(i,s[i]);
    }
    int Q;
    scanf("%d",&Q);
    while (Q--)
    {
        char op[10];
        scanf("%s",op);
        if (op[0]=='-')
        {
            int x;
            scanf("%d",&x);
            del(x);
            del(x+n);
        }
        else if (op[0]=='+')
        {
            int x;
            scanf("%d",&x);
            add(x);
            add(x+n);
        }
        else
        {
            int x,y;
            scanf("%d%d",&x,&y);
            if (x>y)
                y+=n;
            printf("%lld\n",query(y)-query(x)+area(a[0],a[y],a[x]));
        }
    }
    return(0);
}

