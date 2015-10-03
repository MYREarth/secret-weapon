#include <cstdio>
#include <cstring>
#include <vector>
#include <utility>
using namespace std;
vector <pair <int,int> > ans;
bool flag,block[3010];
int idx,dfn[3010],low[3010],cnt[3010],b[3010],a[20010][2];
void tarjan(int x,int father)
{
    dfn[x]=low[x]=++idx;
    cnt[x]=1;
    for (int i=b[x];i;i=a[i][1])
    {
        int y=a[i][0];
        if (block[y] || y==father)
            continue;
        if (!dfn[y])
        {
            tarjan(y,x);
            low[x]=min(low[x],low[y]);
            cnt[x]+=cnt[y];
            if (low[y]>dfn[x] && cnt[y]&1 && !block[x] && !block[y])
            {
                flag=block[x]=block[y]=true;
                ans.push_back(make_pair(x,y));
            }
        }
        else
            low[x]=min(low[x],dfn[y]);
    }
}
int main()
{
    freopen("matching.in","r",stdin);
    freopen("matching.out","w",stdout);
    int n,m;
    scanf("%d%d",&n,&m);
    for (int i=1;i<=m;i++)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        a[i][0]=y,a[i][1]=b[x],b[x]=i;
        a[i+m][0]=x,a[i+m][1]=b[y],b[y]=i+m;
    }
    if (n&1)
        printf("NULLUS\n");
    else
    {
        while (1)
        {
            memset(dfn,0,sizeof(dfn));
            idx=0;
            flag=false;
            for (int i=1;i<=n;i++)
                if (!dfn[i] && !block[i])
                    tarjan(i,0);
            if (!flag)
                break;
        }
        if (ans.size()!=n/2)
            printf("NULLUS\n");
        else
        {
            printf("42\n");
            for (int i=0;i<ans.size();i++)
                printf("%d %d\n",ans[i].first,ans[i].second);
        }
    }
    return(0);
}

