#include <cstdio>
#include <cstring>
#include <map>
#define hash __hash__
using namespace std;
const int N=400010;
char buf[1000000];
map <string,int> M;
bool bad[N],in[N],vis[N];
int idx,top,tot,n,m,to[N],cnt[N],c[N],s[N],b[N],dfn[N],low[N],inv[N],a[N][2],e[N][2];
void add(int x,int y)
{
    if (x==y)
        return;
    a[++tot][0]=y,a[tot][1]=b[x],b[x]=tot;
}
void tarjan(int x)
{
    dfn[x]=low[x]=++idx;
    in[x]=true;
    s[++top]=x;
    for (int i=b[x];i;i=a[i][1])
    {
        int y=a[i][0];
        if (!dfn[y])
        {
            tarjan(y);
            low[x]=min(low[x],low[y]);
        }
        else if (in[y])
            low[x]=min(low[x],dfn[y]);
    }
    if (dfn[x]==low[x])
    {
        c[0]++;
        while (1)
        {
            int y=s[top--];
            c[y]=c[0];
            in[y]=false;
            if (y==x)
                break;
        }
    }
}
void check()
{
    for (int i=1;i<=2*n;i++)
        if (!dfn[i])
            tarjan(i);
    for (int i=1;i<=n;i++)
    {
        if (c[i]==c[inv[i]])
        {
            printf("NO\n");
            return;
        }
        if (bad[i])
        {
            cnt[c[i]]++;
            to[c[i]]=i;
            cnt[c[inv[i]]]++;
            to[c[inv[i]]]=inv[i];
        }
    }
    for (int i=1;i<=c[0];i++)
        if (cnt[i]>1)
        {
            printf("MAYBE\n");
            return;
        }
    memset(b,0,sizeof(b));
    tot=0;
    for (int i=1;i<=m;i++)
    {
        int x=e[i][0],y=e[i][1];
        add(c[x],c[y]);
        add(c[inv[y]],c[inv[x]]);
    }
    for (int i=1;i<=c[0];i++)
        for (int j=b[i];j;j=a[j][1])
        {
            int y=a[j][0];
            if (vis[y] || cnt[y]>0)
                vis[i]=true;
        }
    for (int i=1;i<=n;i++)
    {
        if (bad[i])
        {
            if (vis[c[i]] || vis[c[inv[i]]])
            {
                printf("MAYBE\n");
                return;
            }
            continue;
        }
        int x=c[i],y=c[inv[i]];
        if (vis[x] && vis[y] || vis[x] && cnt[y]>0 || cnt[x]>0 && vis[y])
        {
            printf("MAYBE\n");
            return;
        }
        if (cnt[x]>1 && cnt[y]>0 || cnt[x]>0 && cnt[y]>1 || cnt[x]==1 && cnt[y]==1 && to[x]!=inv[to[y]])
        {
            printf("MAYBE\n");
            return;
        }
    }
    printf("YES\n");
}
int hash(const string &s)
{
    if (!M.count(s))
    {
        int tmp=M.size()+1;
        M[s]=tmp;
    }
    return(M[s]);
}
int read()
{
    scanf("%s",buf);
    int id=hash(buf+1);
    if (buf[0]=='-')
        id*=-1;
    return(id);
}
int main()
{
    scanf("%d",&m);
    for (int i=1;i<=m;i++)
    {
        int x=read(),y=read();
        e[i][0]=x,e[i][1]=y;
    }
    n=M.size();
    for (int i=1;i<=2*n;i++)
        inv[i]=2*n-i+1;
    for (int i=1;i<=m;i++)
        for (int j=0;j<2;j++)
            if (e[i][j]<0)
                e[i][j]=inv[-e[i][j]];
    for (int i=1;i<=m;i++)
    {
        int x=e[i][0],y=e[i][1];
        add(x,y);
        add(inv[y],inv[x]);
    }
    int Q;
    scanf("%d",&Q);
    while (Q--)
    {
        scanf("%s",buf);
        if (M.count(buf))
            bad[M[buf]]=true;
    }
    check();
    return(0);
}

