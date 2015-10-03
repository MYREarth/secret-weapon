#include <cstdio>
#include <vector>
#include <string>
#include <queue>
#include <map>
#include <algorithm>
using namespace std;
char buf[1000000];
map <string,int> M;
vector <int> route[100010],at[300010];
int c[100010],len[100010],ans[300010],dis[300010];
void calc(int S)
{
    dis[S]=0;
    queue <int> Q;
    Q.push(S);
    while (!Q.empty())
    {
        int x=Q.front();
        Q.pop();
        for (int i=0;i<at[x].size();i++)
        {
            int y=at[x][i];
            if (len[y]==-1)
            {
                len[y]=dis[x]+1;
                for (int j=0;j<route[y].size();j++)
                {
                    int z=route[y][j];
                    if (dis[z]==-1)
                    {
                        dis[z]=len[y];
                        Q.push(z);
                    }
                }
            }
        }
    }
}
inline bool cmp(int x,int y)
{
    return(len[x]<len[y]);
}
void calc(int m,int S)
{
    calc(S);
    sort(c+1,c+m+1,cmp);
    ans[S]=0;
    for (int i=1;i<=m;i++)
    {
        int x=c[i],now=-1<<30;
        for (int j=0;j<route[x].size();j++)
        {
            now++;
            int y=route[x][j];
            if (len[x]==dis[y]+1)
                now=max(now,ans[y]);
            else
                ans[y]=max(ans[y],now);
        }
        now=-1<<30;
        for (int j=route[x].size()-1;j>=0;j--)
        {
            now++;
            int y=route[x][j];
            if (len[x]==dis[y]+1)
                now=max(now,ans[y]);
            else
                ans[y]=max(ans[y],now);
        }
    }
}
int main()
{
    int T;
    scanf("%d",&T);
    while (T--)
    {
        scanf("%*s");
        int n=0;
        M.clear();
        while (1)
        {
            scanf("%s",buf);
            string now=buf;
            bool flag=true;
            if (now[now.size()-1]==',')
                now=now.substr(0,now.size()-1);
            else
                flag=false;
            M[now]=++n;
            at[n].clear();
            ans[n]=dis[n]=-1;
            if (!flag)
                break;
        }
        scanf("%*s");
        int m=0;
        while (1)
        {
            scanf("%s",buf);
            string now=buf;
            bool flag=true;
            if (now[now.size()-1]!=',')
                flag=false;
            m++;
            route[m].clear();
            len[m]=-1;
            c[m]=m;
            if (!flag)
                break;
        }
        for (int i=1;i<=m;i++)
        {
            scanf("%*s%*s");
            while (1)
            {
                scanf("%s",buf);
                string now=buf;
                bool flag=true;
                if (now[now.size()-1]==',')
                    now=now.substr(0,now.size()-1);
                else
                    flag=false;
                route[i].push_back(M[now]);
                at[M[now]].push_back(i);
                if (!flag)
                    break;
            }
        }
        scanf("%*s%*s%*s%s",buf);
        printf("optimal travel from %s",buf);
        int S=M[buf];
        scanf("%*s%*s%*s%s",buf);
        printf(" to %s:",buf);
        int T=M[buf];
        calc(m,S);
        printf(" %d line%s, %d minute%s\n",dis[T],dis[T]==1?"":"s",ans[T],ans[T]==1?"":"s");
    }
    return(0);
}

