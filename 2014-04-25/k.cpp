#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
using namespace std;
bool vis[30],a[30][30];
int pre[30],f[30][30],route[30][30];
void dfs(int x)
{
    for (int i=1;i<=26;i++)
    {
        if (vis[i] || !a[x][i])
            continue;
        vis[i]=true;
        pre[i]=x;
        dfs(i);
    }
}
void cycle(int x)
{
    string ret;
    for (int i=pre[x];i!=x;i=pre[i])
        ret+=char(i+'a'-1);
    ret+=char(x+'a'-1);
    reverse(ret.begin(),ret.end());
    for (int i=1;i<=20;i++)
    {
        for (int j=1;j<=20;j++)
            printf("%c",ret[(i+j-2)%ret.size()]);
        printf("\n");
    }
}
string get(int x,int y)
{
    if (route[x][y]==0)
        return(string(1,char(x+'a'-1)));
    return(get(x,route[x][y])+get(route[x][y],y));
}
void print(int S,int T)
{
    string ret=get(S,T)+char(T+'a'-1);
    int len=min(20,int(ret.size()+1)/2);
    for (int i=1;i<=len;i++)
    {
        for (int j=1;j<=len;j++)
            printf("%c",ret[i+j-2]);
        printf("\n");
    }
}
int main()
{
    int T;
    scanf("%d",&T);
    while (T--)
    {
        memset(a,true,sizeof(a));
        int m;
        scanf("%d",&m);
        while (m--)
        {
            char s[10];
            scanf("%s",s);
            a[s[0]-'a'+1][s[1]-'a'+1]=false;
        }
        int pos=0;
        for (int i=1;i<=26;i++)
        {
            memset(vis,0,sizeof(vis));
            dfs(i);
            if (vis[i])
            {
                pos=i;
                break;
            }
        }
        if (pos!=0)
            cycle(pos);
        else
        {
            memset(f,-63,sizeof(f));
            for (int i=1;i<=26;i++)
                for (int j=1;j<=26;j++)
                    if (a[i][j])
                    {
                        f[i][j]=1;
                        route[i][j]=0;
                    }
            for (int k=1;k<=26;k++)
                for (int i=1;i<=26;i++)
                    for (int j=1;j<=26;j++)
                        if (f[i][k]+f[k][j]>f[i][j])
                        {
                            f[i][j]=f[i][k]+f[k][j];
                            route[i][j]=k;
                        }
            int x=0,y=0,best=0;
            for (int i=1;i<=26;i++)
                for (int j=1;j<=26;j++)
                    if (f[i][j]>best)
                    {
                        best=f[i][j];
                        x=i,y=j;
                    }
            if (best==0)
                printf("a\n");
            else
                print(x,y);
        }
    }
    return(0);
}

