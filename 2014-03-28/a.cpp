#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
int tot=1,S,T,cost,b[1100],a[1000000][4];
void add(int x,int y,int z,int c)
{
    a[++tot][0]=y,a[tot][1]=z,a[tot][2]=c,a[tot][3]=b[x],b[x]=tot;
    a[++tot][0]=x,a[tot][1]=0,a[tot][2]=-c,a[tot][3]=b[y],b[y]=tot;
}
int d[1100],pre[1100],p[1100];
bool in[1100];
bool spfa()
{
    queue <int> Q;
    memset(d,-63,sizeof(d));
    Q.push(S);
    d[S]=0;
    in[S]=true;
    while (!Q.empty())
    {
        int x=Q.front();
        in[x]=false;
        Q.pop();
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
    if (d[T]==d[0])
        return(false);
    for (int i=T;i;i=pre[i])
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
    freopen("arrays.in","r",stdin);
    freopen("arrays.out","w",stdout);
    int n,m;
    scanf("%d%d",&n,&m);
    S=n+1001,T=S+1;
    for (int i=1;i<=n;i++)
    {
        int K;
        scanf("%d",&K);
        add(S,i+1000,m,0);
        for (int j=1;j<=K;j++)
        {
            int x;
            scanf("%d",&x);
            add(i+1000,x,1,0);
        }
    }
    for (int i=1;i<=1000;i++)
        add(i,T,1,i);
    while (spfa());
    printf("%d\n",cost);
    for (int i=1;i<=n;i++)
    {
        int cnt=0;
        for (int j=b[i+1000];j;j=a[j][3])
            if (a[j][0]!=S)
                cnt+=a[j][1]==0;
        printf("%d",cnt);
        for (int j=b[i+1000];j;j=a[j][3])
            if (a[j][0]!=S && a[j][1]==0)
                printf(" %d",a[j][0]);
        printf("\n");
    }
    return(0);
}

