#include <cstdio>
#include <cstring>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#define hash __hash__
using namespace std;
int d[20];
struct Match
{
    int a,b,ga,gb;
    Match(){}
    Match(int a,int b,int ga,int gb):a(a),b(b),ga(ga),gb(gb){}
    void init()
    {
        if (ga<gb || ga==gb && a>b)
        {
            swap(a,b);
            swap(ga,gb);
        }
    }
    int degree()
    {
        return(min(d[a],d[b]));
    }
    bool draw()
    {
        return(ga==gb);
    }
};
inline bool operator ==(const Match &a,const Match &b)
{
    return(a.a==b.a && a.b==b.b && a.ga==b.ga && a.gb==b.gb);
}
map <string,int> M;
string name[20];
int hash(const string &s)
{
    if (!M.count(s))
    {
        int tmp=M.size()+1;
        name[tmp]=s;
        M[s]=tmp;
    }
    return(M[s]);
}
Match match[40];
int ans,group[20],point[20],goal[20],pos[20],tmp[20];
bool finish[40];
void deal(int t)
{
    finish[t]=true;
    int x=match[t].a,y=match[t].b,ga=match[t].ga,gb=match[t].gb;
    tmp[x]++;
    tmp[y]++;
    if (ga==gb)
        point[x]++,point[y]++;
    else
    {
        point[x]+=3;
        goal[x]+=ga-gb;
        goal[y]-=ga-gb;
    }
}
inline bool cmp(int x,int y)
{
    return(point[x]>point[y] || point[x]==point[y] && (goal[x]>goal[y] || goal[x]==goal[y] && name[x]<name[y]));
}
inline bool cmp1(int x,int y)
{
    return(match[x].degree()<match[y].degree());
}
void check()
{
    vector <int> now;
    for (int i=1;i<=31;i++)
        if (!finish[i])
            now.push_back(i);
    if (now.size()!=7)
        return;
    sort(now.begin(),now.end(),cmp1);
    set <int> S;
    for (int i=0;i<4;i++)
    {
        int x=now[i];
        if (match[x].draw())
            return;
        int a=match[x].a,b=match[x].b;
        S.insert(a);
        S.insert(b);
        if (d[a]<=4 || d[b]!=4 || pos[a]+pos[b]!=3)
            return;
    }
    if (S.size()!=8)
        return;
    S.clear();
    for (int i=4;i<6;i++)
    {
        int x=now[i];
        if (match[x].draw())
            return;
        int a=match[x].a,b=match[x].b;
        S.insert(a);
        S.insert(b);
        if (d[a]<=5 || d[b]!=5)
            return;
    }
    if (S.size()!=4)
        return;
    int x=now[6];
    if (match[x].draw())
        return;
    int a=match[x].a,b=match[x].b;
    if (d[a]!=6 || d[b]!=6)
        return;
    ans++;
}
void dfs(int dep)
{
    if (dep==5)
    {
        check();
        return;
    }
    for (int i=1;i<=16;i++)
        if (group[i]==dep)
            group[i]=0;
    int k=-1;
    for (int i=1;i<=16;i++)
        if (!group[i] && d[i]==3)
        {
            k=i;
            break;
        }
    if (k==-1)
        return;
    group[k]=dep;
    for (int i=1;i<=31;i++)
    {
        if (match[i].a==k && !group[match[i].b])
            group[match[i].b]=dep;
        if (match[i].b==k && !group[match[i].a])
            group[match[i].a]=dep;
    }
    vector <int> a,b;
    for (int i=1;i<=31;i++)
    {
        if (group[match[i].a]!=dep || group[match[i].b]!=dep)
            continue;
        if (match[i].degree()==3)
            a.push_back(i);
        else
            b.push_back(i);
    }
    if (a.size()!=5 || b.size()!=1 && b.size()!=2)
        return;
    vector <int> now;
    for (int i=1;i<=16;i++)
        if (group[i]==dep)
            now.push_back(i);
    if (now.size()!=4)
        return;
    for (int _=0;_<2;_++)
    {
        memset(point,0,sizeof(point));
        memset(goal,0,sizeof(goal));
        memset(tmp,0,sizeof(tmp));
        for (int i=0;i<5;i++)
            deal(a[i]);
        deal(b[0]);
        sort(now.begin(),now.end(),cmp);
        bool flag=true;
        for (int i=0;i<4;i++)
            if (tmp[now[i]]!=3)
            {
                flag=false;
                break;
            }
        if (flag && d[now[0]]>3 && d[now[1]]>3 && d[now[2]]==3 && d[now[3]]==3)
        {
            pos[now[0]]=1;
            pos[now[1]]=2;
            dfs(dep+1);
        }
        if (b.size()==1 || match[b[0]]==match[b[1]])
            break;
        finish[b[0]]=false;
        swap(b[0],b[1]);
    }
}
void calc()
{
    ans=0;
    if (M.size()!=16)
        return;
    memset(d,0,sizeof(d));
    for (int i=1;i<=31;i++)
    {
        d[match[i].a]++;
        d[match[i].b]++;
        if (match[i].a==match[i].b)
            return;
    }
    int cnt[10]={0};
    for (int i=1;i<=16;i++)
    {
        if (d[i]>8)
            return;
        cnt[d[i]]++;
    }
    if (cnt[3]!=8 || cnt[4]!=4 || cnt[5]!=2 || cnt[6]!=2)
        return;
    memset(group,0,sizeof(group));
    memset(finish,0,sizeof(finish));
    dfs(1);
}
int main()
{
    int T;
    scanf("%d",&T);
    while (T--)
    {
        M.clear();
        for (int i=1;i<=31;i++)
        {
            char a[10],b[10];
            int x,y;
            scanf("%s %d:%d %s",a,&x,&y,b);
            match[i]=Match(hash(a),hash(b),x,y);
            match[i].init();
        }
        calc();
        printf("There %s ",ans==1?"is":"are");
        if (ans==0)
            printf("no");
        else
            printf("%d",ans);
        static int id=0;
        printf(" possible championship%s for list #%d%s\n",ans==1?"":"s",++id,ans==0?"!":".");
    }
    return(0);
}

