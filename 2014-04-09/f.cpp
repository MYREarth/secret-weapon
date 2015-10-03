#include <cstdio>
#include <cstdlib>
#include <set>
#include <utility>
#include <algorithm>
using namespace std;
typedef int arr[100010];
arr l,r,s,u,v,c,f,g;
int root;
set <int> S;
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
void cut(int &x,int p)
{
    int id=x+p-u[x];
    f[id]=id;
    S.insert(id);
    r[id]=r[x];
    l[id]=r[x]=0;
    c[id]=rand();
    u[id]=p;
    v[id]=v[x];
    v[x]=p-1;
    update(x);
    update(id);
    x=merge(x,id);
}
void insert(int &x,int id,int pos,int L,int R)
{
    if (x==0)
    {
        id+=L-pos;
        l[id]=r[id]=0;
        s[id]=1;
        u[id]=L;
        v[id]=R;
        c[id]=rand();
        f[id]=id;
        S.insert(id);
        x=id;
        return;
    }
    if (u[x]<=R && R<v[x])
        cut(x,R+1);
    if (u[x]<L && L<=v[x])
        cut(x,L);
    if (L<=u[x] && v[x]<=R)
    {
        int now=id+u[x]-pos;
        f[now]=x;
        S.insert(now);
    }
    if (L<u[x])
    {
        insert(l[x],id,pos,L,min(R,u[x]-1));
        update(x);
        if (c[l[x]]<c[x])
            right(x);
    }
    if (R>v[x])
    {
        insert(r[x],id,pos,max(L,v[x]+1),R);
        update(x);
        if (c[r[x]]<c[x])
            left(x);
    }
}
pair <int,int> split(int x,int p)
{
    if (x==0)
        return(make_pair(0,0));
    if (u[x]<p && p<=v[x])
        cut(x,p);
    if (p<=u[x])
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
    if (x==0)
        return;
    dump(l[x],delta);
    dump(r[x],delta);
    insert(root,x,u[x]+delta,u[x]+delta,v[x]+delta);
}
int main()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    int n,m;
    scanf("%d%d",&n,&m);
    insert(root,1,1,1,n);
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
            dump(L,-delta);
            dump(R,-delta);
        }
        else
        {
            int delta=to-from;
            root=merge(L,R);
            dump(M,delta);
        }
    }
    for (int i=1;i<=n;i++)
    {
        set <int>::iterator k=S.upper_bound(i);
        int x=*--k;
        printf("%d%c",i-x+u[find(x)]-first,i==n?'\n':' ');
    }
    return(0);
}

