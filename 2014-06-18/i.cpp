#include <cstdio>
#include <cstring>
#include <utility>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;
typedef long long ll;
pair <int,int> a[200010],b[200010];
int get(const vector <int> &a,int v)
{
    return(lower_bound(a.begin(),a.end(),v)-a.begin()+1);
}
map <int,bool> row[400010],col[400010];
vector <int> X,Y;
struct line
{
    int u1,u2,v;
    line(int x1,int x2,int y):u1(min(x1,x2)),u2(max(x1,x2)),v(y){}
};
vector <line> verti1,hori1,verti2,hori2;
void go(int &x0,int &y0,int &dir,vector <line > &verti,vector <line > &hori)
{
    verti.clear();
    hori.clear();
    while (1)
    {
        int x,y,tmp;
        if (dir==3)
        {
            x=x0;
            auto k=row[x].upper_bound(y0);
            if (k==row[x].end())
                y=Y.size()+1;
            else
            {
                y=k->first;
                tmp=k->second?1:0;
            }
        }
        else if (dir==2)
        {
            x=x0;
            auto k=row[x].lower_bound(y0);
            if (k==row[x].begin())
                y=0;
            else
            {
                k--;
                y=k->first;
                tmp=k->second?0:1;
            }
        }
        else if (dir==1)
        {
            y=y0;
            auto k=col[y].upper_bound(x0);
            if (k==col[y].end())
                x=X.size()+1;
            else
            {
                x=k->first;
                tmp=k->second?3:2;
            }
        }
        else
        {
            y=y0;
            auto k=col[y].lower_bound(x0);
            if (k==col[y].begin())
                x=0;
            else
            {
                k--;
                x=k->first;
                tmp=k->second?2:3;
            }
        }
        if (dir==2 || dir==3)
            hori.push_back(line(y,y0,x));
        else
            verti.push_back(line(x,x0,y));
        x0=x,y0=y,dir=tmp;
        if (x==0 || y==0 || x==X.size()+1 || y==Y.size()+1)
            break;
    }
}
struct event
{
    int y1,y2,x,kind;
    event(int y1,int y2,int x,int kind):y1(y1),y2(y2),x(x),kind(kind){}
};
inline bool operator <(const event &a,const event &b)
{
    return(a.x<b.x || a.x==b.x && a.kind<b.kind);
}
ll sum;
pair <int,int> ans;
vector <event> e;
int c[400010];
void modify(int x,int value)
{
    for (int i=x;i<=Y.size();i+=i&-i)
        c[i]+=value;
}
int query(int x)
{
    int ret=0;
    for (int i=x;i;i-=i&-i)
        ret+=c[i];
    return(ret);
}
void calc(const vector <line> &verti,const vector <line> &hori)
{
    e.clear();
    for (int i=0;i<verti.size();i++)
    {
        int x1=verti[i].u1,x2=verti[i].u2,y=verti[i].v;
        e.push_back(event(y,y,x1,1));
        e.push_back(event(y,y,x2,-1));
    }
    for (int i=0;i<hori.size();i++)
    {
        int y1=hori[i].u1,y2=hori[i].u2,x=hori[i].v;
        e.push_back(event(y1,y2,x,0));
    }
    sort(e.begin(),e.end());
    memset(c,0,sizeof(c));
    int first=-1;
    for (int i=0;i<e.size();i++)
    {
        if (e[i].kind!=0)
        {
            modify(e[i].y1,e[i].kind);
            continue;
        }
        int tmp=query(e[i].y2-1)-query(e[i].y1);
        if (tmp && (first==-1 || first==e[i].x))
        {
            first=e[i].x;
            for (int j=e[i].y1+1;j<e[i].y2;j++)
                if (query(j)-query(j-1)>0)
                {
                    ans=min(ans,make_pair(e[i].x,j));
                    break;
                }
        }
        sum+=tmp;
    }
}
int main()
{
    int R,C,n,m;
    while (scanf("%d%d%d%d",&R,&C,&n,&m)==4)
    {
        X.clear();
        Y.clear();
        for (int i=1;i<=n;i++)
        {
            scanf("%d%d",&a[i].first,&a[i].second);
            X.push_back(a[i].first);
            Y.push_back(a[i].second);
        }
        for (int i=1;i<=m;i++)
        {
            scanf("%d%d",&b[i].first,&b[i].second);
            X.push_back(b[i].first);
            Y.push_back(b[i].second);
        }
        X.push_back(1);
        X.push_back(R);
        sort(X.begin(),X.end());
        X.erase(unique(X.begin(),X.end()),X.end());
        sort(Y.begin(),Y.end());
        Y.erase(unique(Y.begin(),Y.end()),Y.end());
        for (int i=1;i<=n;i++)
            a[i]=make_pair(get(X,a[i].first),get(Y,a[i].second));
        for (int i=1;i<=m;i++)
            b[i]=make_pair(get(X,b[i].first),get(Y,b[i].second));
        for (int i=1;i<=X.size();i++)
            row[i].clear();
        for (int i=1;i<=Y.size();i++)
            col[i].clear();
        for (int i=1;i<=n;i++)
        {
            int x=a[i].first,y=a[i].second;
            row[x][y]=false;
            col[y][x]=false;
        }
        for (int i=1;i<=m;i++)
        {
            int x=b[i].first,y=b[i].second;
            row[x][y]=true;
            col[y][x]=true;
        }
        int x=1,y=0,dir=3;
        go(x,y,dir,verti1,hori1);
        static int id=0;
        printf("Case %d: ",++id);
        if (x==X.size() && y==Y.size()+1)
            printf("0\n");
        else
        {
            x=X.size(),y=Y.size()+1,dir=2;
            go(x,y,dir,verti2,hori2);
            sum=0;
            ans.first=1<<30;
            calc(verti1,hori2);
            calc(verti2,hori1);
            if (sum==0)
                printf("impossible\n");
            else
                printf("%lld %d %d\n",sum,X[ans.first-1],Y[ans.second-1]);
        }
    }
    return(0);
}

