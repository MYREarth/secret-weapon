#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <utility>
#include <map>
#include <algorithm>
using namespace std;
typedef long long ll;
struct point
{
    int x,y;
    point(){}
    point(int x,int y):x(x),y(y){}
};
inline ll det(const point &a,const point &b)
{
    return(ll(a.x)*b.y-ll(a.y)*b.x);
}
char s[100010];
point p[100010];
int tot,b[100010],to[200010],a[200010][2];
bool choose[200010],vis[200010];
void add(int x,int y)
{
    a[++tot][0]=y,a[tot][1]=b[x],b[x]=tot;
    a[++tot][0]=x,a[tot][1]=b[y],b[y]=tot;
}
void farmland(int n)
{
    for (int i=1;i<=n;i++)
    {
        vector <pair <double,int> > lq;
        for (int j=b[i];j;j=a[j][1])
        {
            int x=a[j][0];
            lq.push_back(make_pair(atan2(p[x].y-p[i].y,p[x].x-p[i].x),j));
        }
        sort(lq.begin(),lq.end());
        for (int j=0;j<lq.size();j++)
            to[lq[(j+1)%lq.size()].second^1]=lq[j].second;
    }
    memset(vis,0,sizeof(vis));
    memset(choose,0,sizeof(choose));
    for (int i=2;i<=tot;i++)
        if (!vis[i])
        {
            ll area=0;
            vector <int> tmp;
            for (int j=i;!vis[j];j=to[j])
            {
                area+=det(p[a[j^1][0]],p[a[j][0]]);
                vis[j]=true;
                tmp.push_back(j);
            }
            if (area>0)
                for (int j=0;j<tmp.size();j++)
                    choose[tmp[j]]=true;
        }
}
map <pair <int,int>,int > M;
int get(int x,int y)
{
    pair <int,int> tmp(x,y);
    if (!M.count(tmp))
    {
        int id=M.size()+1;
        p[id]=point(x,y);
        M[tmp]=id;
    }
    return(M[tmp]);
}
int main()
{
    int T;
    scanf("%d",&T);
    while (T--)
    {
        scanf("%s",s+1);
        int n=strlen(s+1),x=0,y=0,prev=0;
        M.clear();
        memset(b,0,sizeof(b));
        tot=1;
        for (int i=1;i<=n;i++)
        {
            int now=get(x,y);
            if (i>1)
                add(prev,now);
            prev=now;
            if (s[i]=='U')
                y++;
            else if (s[i]=='D')
                y--;
            else if (s[i]=='L')
                x--;
            else
                x++;
        }
        add(prev,1);
        farmland(M.size());
        int ans=1;
        for (int i=2;i<=tot;i++)
            if (choose[i] && choose[i^1])
            {
                ans=2;
                break;
            }
        printf("%d\n",ans);
    }
    return(0);
}

