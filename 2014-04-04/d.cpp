#include <cstdio>
#include <cstring>
#include <map>
#include <queue>
using namespace std;
map <int,int> M;
int S,T,cost,tot=1,b[3010],a[1000000][4];
void add(int x,int y,int z,int c)
{
    a[++tot][0]=y,a[tot][1]=z,a[tot][2]=c,a[tot][3]=b[x],b[x]=tot;
    a[++tot][0]=x,a[tot][1]=0,a[tot][2]=-c,a[tot][3]=b[y],b[y]=tot;
}
int hash(int x)
{
    if (!M.count(x))
    {
        int tmp=M.size()+1;
        M[x]=tmp;
    }
    return(M[x]);
}
int d[3010],pre[3010],p[3010];
bool in[3010];
bool spfa()
{
    memset(d,-63,sizeof(d));
    queue <int> Q;
    Q.push(S);
    d[S]=0;
    in[S]=true;
    while (!Q.empty())
    {
        int x=Q.front();
        Q.pop();
        in[x]=false;
        for (int i=b[x];i;i=a[i][3])
        {
            int y=a[i][0];
            if (a[i][1] && d[x]+a[i][2]>d[y])
            {
                d[y]=d[x]+a[i][2];
                pre[y]=x;
                p[y]=i;
                if (!in[y])
                {
                    in[y]=true;
                    Q.push(y);
                }
            }
        }
    }
    if (d[T]==d[0] || d[T]<=0)
        return(false);
    for (int i=T;i!=S;i=pre[i])
    {
        int x=p[i];
        a[x][1]--;
        a[x^1][1]++;
    }
    cost+=d[T];
    return(true);
}
int main()
{
    int n;
    scanf("%d",&n);
    for (int i=1;i<=n;i++)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        add(i,hash(x)+n,1,y);
        add(i,hash(y)+n,1,x);
    }
    S=n+M.size()+1,T=S+1;
    for (int i=1;i<=n;i++)
        add(S,i,1,0);
    for (int i=1;i<=M.size();i++)
        add(i+n,T,1,0);
    while (spfa());
    printf("%d\n",cost);
    return(0);
}

