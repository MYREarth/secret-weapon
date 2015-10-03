#include <cstdio>
#include <vector>
using namespace std;
int tot=1,id[4010],b[4010],a[1000000][3];
void add(int x,int y,int z)
{
    a[++tot][0]=y,a[tot][1]=z,a[tot][2]=b[x],b[x]=tot;
    a[++tot][0]=x,a[tot][1]=0,a[tot][2]=b[y],b[y]=tot;
}
int idx,q[4010],pre[4010],p[4010],vis[4010];
bool bfs(int S,int T)
{
    idx++;
    int l,r;
    q[l=r=1]=S;
    vis[S]=idx;
    while (l<=r)
    {
        int x=q[l++];
        for (int i=b[x];i;i=a[i][2])
        {
            int y=a[i][0];
            if (!a[i][1] || vis[y]==idx)
                continue;
            vis[y]=idx;
            q[++r]=y;
            pre[y]=x;
            p[y]=i;
        }
    }
    if (vis[T]!=idx)
        return(false);
    for (int i=T;i!=S;i=pre[i])
    {
        int x=p[i];
        a[x][1]--;
        a[x^1][1]++;
    }
    return(true);
}
bool choose[4010];
int n;
vector <int> here;
vector <vector <int> > ans;
void dfs(int x)
{
    here.push_back(x-n);
    choose[x-n]=false;
    for (int i=b[x];i;i=a[i][2])
    {
        int y=a[i][0];
        if (a[i][1] || !choose[y] || y+n==x)
            continue;
        dfs(y+n);
    }
}
int main()
{
    scanf("%d",&n);
    for (int i=1;i<=n;i++)
    {
        int K;
        scanf("%d",&K);
        for (int j=1;j<=K;j++)
        {
            int x;
            scanf("%d",&x);
            add(i+n,x,1);
        }
    }
    for (int i=1;i<=n;i++)
    {
        id[i]=tot+1;
        add(i,i+n,1);
    }
    for (int i=1;i<=n;i++)
    {
        int x=id[i];
        if (a[x][1]==0)
        {
            choose[i]=true;
            a[x^1][1]=0;
        }
        else if (bfs(i+n,i))
        {
            choose[i]=true;
            a[x][1]=0;
        }
    }
    for (int i=1;i<=n;i++)
    {
        if (!choose[i])
            continue;
        here.clear();
        dfs(i+n);
        ans.push_back(here);
    }
    printf("%d\n",ans.size());
    for (int i=0;i<ans.size();i++)
    {
        printf("%d",ans[i].size());
        for (int j=0;j<ans[i].size();j++)
            printf(" %d",ans[i][j]);
        printf("\n");
    }
    return(0);
}

