#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
struct tree
{
    int l,r,sum;
};
struct state
{
    int start,num,id;
    state(){}
    state(int x,int y,int z):start(x),num(y),id(z){}
};
inline bool operator <(const state &a,const state &b)
{
    return(a.start<b.start);
}
tree a[524300];
void build(int x,int l,int r,int n)
{
    a[x].l=l,a[x].r=r;
    if (l==r)
    {
        a[x].sum=l<=n;
        return;
    }
    int ls=x<<1,rs=ls+1,mid=a[x].l+a[x].r>>1;
    build(ls,l,mid,n);
    build(rs,mid+1,r,n);
    a[x].sum=a[ls].sum+a[rs].sum;
}
void modify(int x,int pos,int value)
{
    if (a[x].l==a[x].r)
    {
        a[x].sum=value;
        return;
    }
    int ls=x<<1,rs=ls+1,mid=a[x].l+a[x].r>>1;
    if (pos<=mid)
        modify(ls,pos,value);
    else
        modify(rs,pos,value);
    a[x].sum=a[ls].sum+a[rs].sum;
}
int query(int x,int num)
{
    if (a[x].sum<num)
        return(-1);
    if (a[x].l==a[x].r)
        return(a[x].l);
    int ls=x<<1,rs=ls+1;
    if (num<=a[ls].sum)
        return(query(ls,num));
    else
        return(query(rs,num-a[ls].sum));
}
state b[100010];
char s[100010];
int ans[100010],l[200010];
vector <int> ban[100010];
void calc(int n)
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
int main()
{
    freopen("palindrome.in","r",stdin);
    freopen("palindrome.out","w",stdout);
    scanf("%s",s);
    int n=strlen(s);
    calc(n);
    for (int i=0;i<2*n-1;i++)
    {
        if (l[i]==0)
            continue;
        int pos=i/2+1-l[i]+1;
        if (i%2==0)
            ban[pos].push_back(2*l[i]-1);
        else
            ban[pos].push_back(2*l[i]);
    }
    int m;
    scanf("%d",&m);
    for (int i=1;i<=m;i++)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        b[i]=state(x,y,i);
    }
    sort(b+1,b+m+1);
    build(1,1,2*n,n);
    int delta=0,t=1;
    for (int i=1;i<=n;i++)
    {
        for (int j=0;j<ban[i].size();j++)
        {
            int x=ban[i][j];
            modify(1,x+delta,0);
        }
        while (t<=m && b[t].start==i)
        {
            int now=query(1,b[t].num);
            ans[b[t].id]=now==-1?-1:now-delta;
            t++;
        }
        delta+=2;
        while (a[1].sum>0)
        {
            int p=query(1,1);
            if (p<=delta)
                modify(1,p,0);
            else
                break;
        }
        modify(1,n-i+delta,1);
    }
    for (int i=1;i<=m;i++)
        printf("%d\n",ans[i]);
    return(0);
}

