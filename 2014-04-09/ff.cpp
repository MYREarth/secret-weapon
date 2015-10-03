#include <cstdio>
#include <cstdlib>
#include <utility>
using namespace std;
typedef int array[100010];
array l,r,s,d,c,f;
int root;
inline void update(int x)
{
    s[x]=s[l[x]]+s[r[x]]+1;
}
int find(int x)
{
    if (x!=f[x])
        f[x]=find(f[x]);
    return(f[x]);
}
void right(int &x)
{
    int t=l[x],y=r[t];
    r[t]=x;
    l[x]=y;
    update(x);
    update(t);
    x=t;
}
void left(int &x)
{
    int t=r[x],y=l[t];
    l[t]=x;
    r[x]=y;
    update(x);
    update(t);
    x=t;
}
void insert(int &x,int id,int pos)
{
    if (x==0)
    {
        l[id]=r[id]=0;
        s[id]=1;
        d[id]=pos;
        c[id]=rand();
        x=id;
        return;
    }
    if (pos==d[x])
    {
        f[id]=x;
        return;
    }
    s[x]++;
    if (pos<d[x])
    {
        insert(l[x],id,pos);
        if (c[l[x]]<c[x])
            right(x);
    }
    else
    {
        insert(r[x],id,pos);
        if (c[r[x]]<c[x])
            left(x);
    }
}
int merge(int x,int y)
{
    if (x==0 || y==0)
        return(x+y);
    if (c[x]<c[y])
    {
        r[x]=merge(r[x],y);
        update(x);
        return(x);
    }
    else
    {
        l[y]=merge(x,l[y]);
        update(y);
        return(y);
    }
}
pair <int,int> split(int x,int p)
{
    if (x==0)
        return(make_pair(0,0));
    if (p<=d[x])
    {
        int t=l[x];
        l[x]=0;
        update(x);
        pair <int,int> tmp=split(t,p);
        return(make_pair(tmp.first,merge(tmp.second,x)));
    }
    else
    {
        int t=r[x];
        r[x]=0;
        update(x);
        pair <int,int> tmp=split(t,p);
        return(make_pair(merge(x,tmp.first),tmp.second));
    }
}
void dump(int x,int delta)
{
    if (l[x])
        dump(l[x],delta);
    if (r[x])
        dump(r[x],delta);
    insert(root,x,d[x]+delta);
}
int main()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    int n,m;
    scanf("%d%d",&n,&m);
    for (int i=1;i<=n;i++)
    {
        f[i]=i;
        insert(root,i,i);
    }
    int first=0;
    for (int i=1;i<=m;i++)
    {
        int cnt,from,to;
        scanf("%d%d%d",&cnt,&from,&to);
        from+=first;
        to+=first;
        pair <int,int> tmp=split(root,from);
        int L=tmp.first;
        int M=tmp.second;
        tmp=split(M,from+cnt);
        M=tmp.first;
        int R=tmp.second;
        if (s[L]+s[R]<=s[M])
        {
            int delta=to-from;
            first-=delta;
            root=M;
            if (L)
                dump(L,-delta);
            if (R)
                dump(R,-delta);
        }
        else
        {
            int delta=to-from;
            root=merge(L,R);
            if (M)
                dump(M,delta);
        }
    }
    for (int i=1;i<=n;i++)
        printf("%d%c",d[find(i)]-first,i==n?'\n':' ');
    return(0);
}

