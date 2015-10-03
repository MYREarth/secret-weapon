#include <cstdio>
#include <vector>
using namespace std;
char kind[1010];
bool vis[1010];
int tot,K,d[1010],ans[1010][3],a[1010][1010];
vector <int> math[1010],cs[1010];
void update(vector <int> &a,vector <int> &b)
{
    ans[++tot][0]=a.back(),a.pop_back();
    ans[tot][1]=a.back(),a.pop_back();
    ans[tot][2]=b.back(),b.pop_back();
}
bool work(vector <int> &a,vector <int> &b)
{
    while (!a.empty() && !b.empty())
    {
        if (a.size()>b.size())
            update(a,b);
        else
            update(b,a);
    }
    return(a.empty() && b.empty());
}
int main()
{
    freopen("teams.in","r",stdin);
    freopen("teams.out","w",stdout);
    int n,m;
    scanf("%d%d%s",&n,&m,kind+1);
    for (int i=1;i<=m;i++)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        d[x]++,d[y]++;
        a[x][++a[x][0]]=y;
        a[y][++a[y][0]]=x;
    }
    for (int i=1;i<=n;i++)
    {
        int k=0;
        for (int j=1;j<=n;j++)
        {
            if (vis[j] || kind[j]=='P')
                continue;
            if (k==0 || d[j]<d[k])
                k=j;
        }
        if (k==0)
            break;
        math[++K].push_back(k);
        vis[k]=true;
        for (int j=1;j<=a[k][0];j++)
        {
            int y=a[k][j];
            vis[y]=true;
            if (kind[y]=='M')
                math[K].push_back(y);
            else
                cs[K].push_back(y);
        }
    }
    bool flag=true;
    for (int i=1;i<=K;i++)
    {
        for (int j=0;j<math[i].size();j++)
            if (d[math[i][j]]>d[math[i].back()])
                swap(math[i].back(),math[i][j]);
        for (int j=0;j<cs[i].size();j++)
            if (d[cs[i][j]]>d[cs[i].back()])
                swap(cs[i].back(),cs[i][j]);
        int t=(math[i].size()+cs[i].size())%3;
        if (t==2)
        {
            math[0].push_back(math[i].back());
            math[i].pop_back();
            cs[0].push_back(cs[i].back());
            cs[i].pop_back();
        }
        else if (t==1)
        {
            int ma=max(math[i].size(),cs[i].size()),mi=min(math[i].size(),cs[i].size());
            if (ma!=2*mi+1)
                continue;
            if (math[i].size()==ma)
            {
                math[0].push_back(math[i].back());
                math[i].pop_back();
            }
            else
            {
                cs[0].push_back(cs[i].back());
                cs[i].pop_back();
            }
        }
        if (!work(math[i],cs[i]))
        {
            flag=false;
            break;
        }
    }
    if (flag)
    {
        for (int i=1;i<=K;i++)
        {
            if (math[i].empty())
                continue;
            if (math[0].size()<cs[0].size())
            {
                math[0].push_back(math[i].back());
                math[i].pop_back();
            }
            else
            {
                cs[0].push_back(cs[i].back());
                cs[i].pop_back();
            }
            if (!work(math[i],cs[i]))
            {
                flag=false;
                break;
            }
        }
        if (flag)
            flag=work(math[0],cs[0]);
    }
    if (flag)
    {
        printf("Yes\n");
        for (int i=1;i<=tot;i++)
            printf("%d %d %d\n",ans[i][0],ans[i][1],ans[i][2]);
    }
    else
        printf("No\n");
    return(0);
}

