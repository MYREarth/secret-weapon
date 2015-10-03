#include <cstdio>
#include <cstring>
#include <vector>
#include <utility>
#include <map>
using namespace std;
int tot,b[750010],del[750010],a[750010][2],e[750010][2];
void add(int x,int y)
{
    a[++tot][0]=y,a[tot][1]=b[x],b[x]=tot;
}
bool vis[750010];
int sum,q[750010];
vector <int> ans[750010];
void bfs(int S,bool print)
{
    int l,r;
    q[l=r=1]=S;
    vis[S]=true;
    while (l<=r)
    {
        int x=q[l++];
        for (int i=b[x];i;i=a[i][1])
        {
            int y=a[i][0];
            if (!vis[y])
            {
                vis[y]=true;
                q[++r]=y;
            }
        }
    }
    if (!print)
        return;
    ans[sum]=vector <int>(q+1,q+r+1);
}
int main()
{
    int n;
    scanf("%d",&n);
    int num=1;
    map <pair <int,int>,int> M;
    for (int i=1;i<=n;i++)
    {
        char op[10];
        scanf("%s",op);
        if (op[0]=='v')
        {
            int x;
            scanf("%d",&x);
            e[i][0]=x;
            e[i][1]=++num;
            M[make_pair(x,num)]=i;
        }
        else if (op[0]=='e')
        {
            int x,y;
            scanf("%d%d",&x,&y);
            e[i][0]=x;
            e[i][1]=y;
            M[make_pair(x,y)]=i;
        }
        else
        {
            int x,y;
            scanf("%d%d",&x,&y);
            e[i][0]=x;
            e[i][1]=y;
            del[M[make_pair(x,y)]]=1;
            del[i]=-1;
        }
    }
    for (int i=1;i<=n;i++)
        if (del[i]==0)
            add(e[i][0],e[i][1]);
    bfs(1,false);
    for (int i=n;i;i--)
    {
        if (del[i]!=-1)
            continue;
        int x=e[i][0],y=e[i][1];
        add(x,y);
        sum++;
        if (vis[x] && !vis[y])
            bfs(y,true);
    }
    for (int i=sum;i;i--)
    {
        printf("%d",ans[i].size());
        for (int j=0;j<ans[i].size();j++)
            printf(" %d",ans[i][j]);
        printf("\n");
    }
    return(0);
}

