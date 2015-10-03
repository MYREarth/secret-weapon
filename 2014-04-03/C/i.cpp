#include <cstdio>
#include <cstdlib>
#include <string>
#include <map>
#include <algorithm>
using namespace std;
typedef int array[100010];
int root;
array a,b,c,l,r,f,v,p;
string s[100010];
bool ans[100010];
char buf[1000000];
bool lose(int x,int y)
{
    return((a[x]<a[y])+(b[x]<b[y])+(c[x]<c[y])>=2);
}
int prev(int x)
{
    if (l[x]!=0)
    {
        int p=l[x];
        while (r[p])
            p=r[p];
        return(p);
    }
    while (f[x]!=0)
    {
        if (r[f[x]]==x)
            return(f[x]);
        x=f[x];
    }
    return(-1);
}
int next(int x)
{
    if (r[x]!=0)
    {
        int p=r[x];
        while (l[p])
            p=l[p];
        return(p);
    }
    while (f[x]!=0)
    {
        if (l[f[x]]==x)
            return(f[x]);
        x=f[x];
    }
    return(-1);
}
void up(int x)
{
    while (1)
    {
        if (f[x]==0 || v[x]>=v[f[x]])
            break;
        int t=f[x],y;
        if (x==l[t])
        {
            y=r[x];
            r[x]=t;
            l[t]=y;
        }
        else
        {
            y=l[x];
            l[x]=t;
            r[t]=y;
        }
        f[x]=f[t];
        f[t]=x;
        f[y]=t;
        if (f[x]==0)
            root=x;
        else if (t==l[f[x]])
            l[f[x]]=x;
        else
            r[f[x]]=x;
    }
}
int tot;
void print(int x)
{
    if (l[x])
        print(l[x]);
    p[++tot]=x;
    if (r[x])
        print(r[x]);
}
bool check(map <int,int> &M,int x,int y)
{
    map <int,int>::iterator k=M.lower_bound(x);
    if (k==M.begin())
        return(false);
    k--;
    return(k->second<y);
}
void update(map <int,int> &M,int x,int y)
{
    map <int,int>::iterator k=M.lower_bound(x);
    if (k!=M.begin())
    {
        k--;
        if (k->second<y)
            return;
    }
    while (!M.empty())
    {
        k=M.lower_bound(x);
        if (k==M.end() || k->second<y)
            break;
        M.erase(k);
    }
    M[x]=y;
}
int main()
{
    int n;
    scanf("%d",&n);
    for (int i=1;i<=n;i++)
    {
        scanf("%s%d%d%d",buf,&a[i],&b[i],&c[i]);
        s[i]=buf;
        v[i]=rand();
    }
    root=1;
    for (int i=2;i<=n;i++)
    {
        int x=root;
        while (1)
            if (lose(i,x))
            {
                int y=prev(x);
                if (y==-1)
                {
                    l[x]=i;
                    f[i]=x;
                    break;
                }
                if (lose(y,i))
                {
                    r[i]=r[y];
                    r[y]=i;
                    f[r[y]]=i;
                    f[i]=y;
                    break;
                }
                x=l[x];
            }
            else
            {
                int y=next(x);
                if (y==-1)
                {
                    r[x]=i;
                    f[i]=x;
                    break;
                }
                if (lose(i,y))
                {
                    l[i]=l[y];
                    l[y]=i;
                    f[l[y]]=i;
                    f[i]=y;
                    break;
                }
                x=r[x];
            }
        up(i);
    }
    print(root);
    reverse(p+1,p+n+1);
    int last=2;
    map <int,int> A,B,C;
    A[a[p[1]]]=b[p[1]];
    B[b[p[1]]]=c[p[1]];
    C[c[p[1]]]=a[p[1]];
    ans[p[1]]=true;
    for (int i=2;i<=n;i++)
    {
        int x=p[i];
        if (check(A,a[x],b[x]) || check(B,b[x],c[x]) || check(C,c[x],a[x]))
        {
            for (int j=last;j<=i;j++)
            {
                int y=p[j];
                ans[y]=true;
                update(A,a[y],b[y]);
                update(B,b[y],c[y]);
                update(C,c[y],a[y]);
            }
            last=i+1;
        }
    }
    for (int i=1;i<=n;i++)
        if (ans[i])
            printf("%s\n",s[i].c_str());
    return(0);
}

