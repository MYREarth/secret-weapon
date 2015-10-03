#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <vector>
#include <string>
#include <map>
#include <sstream>
#define rotate __rotate__
#define hash __hash__
using namespace std;
char s[1000010],buf[110][10010];
int len[110],a[510],f[110][510];
bool vis[110],fail[110],rotate[110];
vector <int> b[110];
bool check(int id,int l)
{
    if (f[id][l]!=-1)
        return(f[id][l]);
    int &ret=f[id][l];
    if (fail[id])
        ret=false;
    else if (!rotate[id])
    {
        ret=true;
        int t=l;
        for (int i=0;i<b[id].size();i++)
        {
            int x=b[id][i];
            if (x<0)
            {
                if (a[t]!=x)
                {
                    ret=false;
                    break;
                }
                t++;
            }
            else
            {
                if (!check(x,t))
                {
                    ret=false;
                    break;
                }
                t+=len[x];
            }
        }
    }
    else
    {
        int limit=1<<b[id].size(),pos[limit];
        bool flag[limit];
        memset(flag,0,sizeof(flag));
        flag[0]=true;
        pos[0]=l;
        for (int i=0;i<limit;i++)
        {
            if (!flag[i])
                continue;
            for (int j=0;j<b[id].size();j++)
            {
                if (i>>j&1)
                    continue;
                int x=b[id][j],t=pos[i];
                if (x<0 && a[t]==x)
                {
                    flag[i|1<<j]=true;
                    pos[i|1<<j]=t+1;
                }
                if (x>0 && check(x,t))
                {
                    flag[i|1<<j]=true;
                    pos[i|1<<j]=t+len[x];
                }
            }
        }
        ret=flag[limit-1];
    }
    return(ret);
}
map <string,int> M;
int hash(const string &s)
{
    if (!M.count(s))
    {
        int id=M.size()+1;
        M[s]=-id;
    }
    return(M[s]);
}
void init(int id)
{
    vis[id]=true;
    stringstream sin(buf[id]);
    string tmp;
    while (sin>>tmp)
    {
        if (tmp[0]=='[')
        {
            rotate[id]=true;
            tmp=tmp.substr(1);
        }
        if (tmp[tmp.size()-1]==']')
        {
            rotate[id]=true;
            tmp=tmp.substr(0,tmp.size()-1);
        }
        if (isdigit(tmp[0]))
        {
            int x=atoi(tmp.c_str());
            if (!vis[x])
                init(x);
            if (fail[x])
            {
                fail[id]=true;
                return;
            }
            b[id].push_back(x);
            len[id]+=len[x];
        }
        else
        {
            if (!M.count(tmp))
            {
                fail[id]=true;
                return;
            }
            b[id].push_back(M[tmp]);
            len[id]++;
        }
    }
}
int main()
{
    freopen("patterns.in","r",stdin);
    freopen("patterns.out","w",stdout);
    int n;
    scanf("%d",&n);
    for (int i=1;i<=n;i++)
    {
        int x;
        scanf("%d: ",&x);
        gets(buf[x]);
    }
    gets(s);
    stringstream sin(s);
    string tmp;
    int m=0;
    while (sin>>tmp)
        a[++m]=hash(tmp);
    for (int i=1;i<=n;i++)
        if (!vis[i])
            init(i);
    memset(f,-1,sizeof(f));
    for (int i=1;i<=n;i++)
        if (len[i]!=m)
            printf("NO\n");
        else
            printf("%s\n",check(i,1)?"YES":"NO");
    return(0);
}

