#include <cstdio>
#include <vector>
#include <map>
#include <set>
#include <queue>
#define array ARRAY
using namespace std;
typedef int array[100010];
struct state
{
    int time,kind,id;
    state(int x,int y,int z):time(x),kind(y),id(z){}
};
inline bool operator <(const state &a,const state &b)
{
    return(a.time<b.time || a.time==b.time && (a.kind<b.kind || a.kind==b.kind && a.id<b.id));
}
array from,to,start,dir,d,pos;
map <pair <int,int>,int> left[100010],right[100010];
queue <pair <int,int> > track[100010];
vector <int> ans[100010];
set <state> all;
int main()
{
    freopen("commuter.in","r",stdin);
    freopen("commuter.out","w",stdout);
    int n;
    scanf("%d",&n);
    for (int i=1;i<=n;i++)
        scanf("%d",&d[i]);
    for (int i=n;i;i--)
        d[i]-=d[i-1];
    int m;
    scanf("%d",&m);
    for (int i=1;i<=m;i++)
    {
        scanf("%d%d%d",&from[i],&to[i],&start[i]);
        pos[i]=from[i];
        if (from[i]<to[i])
        {
            right[from[i]][make_pair(start[i],start[i])]=i;
            dir[i]=1;
            all.insert(state(start[i],1,from[i]));
        }
        else
        {
            left[from[i]][make_pair(start[i],start[i])]=i;
            dir[i]=-1;
            all.insert(state(start[i],1,-from[i]));
        }
    }
    while (!all.empty())
    {
        int now=all.begin()->time,kind=all.begin()->kind,id=all.begin()->id;
        all.erase(all.begin());
        if (kind==0)
        {
            ans[id].push_back(now);
            if (dir[id]==1)
                track[pos[id]+1].pop();
            else
                track[pos[id]].pop();
            pos[id]+=dir[id];
            if (pos[id]==to[id])
                continue;
            if (dir[id]>0)
            {
                right[pos[id]][make_pair(now+1,start[id])]=id;
                if (right[pos[id]].begin()->second==id)
                    all.insert(state(now+1,1,pos[id]));
            }
            else
            {
                left[pos[id]][make_pair(now+1,start[id])]=id;
                if (left[pos[id]].begin()->second==id)
                    all.insert(state(now+1,1,-pos[id]));
            }
        }
        else if (id>0)
        {
            int x=right[id].begin()->second;
            if (track[id+1].empty() || dir[x]==dir[track[id+1].front().second])
            {
                ans[x].push_back(now);
                track[id+1].push(make_pair(now+d[id+1],x));
                all.insert(state(now+d[id+1],0,x));
                right[id].erase(right[id].begin());
            }
            else if (!track[id+1].empty() && dir[x]!=dir[track[id+1].front().second])
                all.insert(state(track[id+1].front().first,1,id));
            else
                all.insert(state(now+1,1,id));
        }
        else
        {
            id*=-1;
            int x=left[id].begin()->second;
            if (track[id].empty() || dir[x]==dir[track[id].front().second])
            {
                ans[x].push_back(now);
                track[id].push(make_pair(now+d[id],x));
                all.insert(state(now+d[id],0,x));
                left[id].erase(left[id].begin());
            }
            else if (!track[id].empty() && dir[x]!=dir[track[id].front().second])
                all.insert(state(track[id].front().first,1,-id));
            else
                all.insert(state(now+1,1,-id));
        }
    }
    for (int i=1;i<=m;i++)
    {
        printf("Train %d\n",i);
        printf("%d * %d\n",from[i],ans[i][0]);
        int t=1;
        for (int j=from[i]+dir[i];j!=to[i];j+=dir[i])
        {
            printf("%d %d %d\n",j,ans[i][t],ans[i][t+1]);
            t+=2;
        }
        printf("%d %d *\n",to[i],ans[i][t]);
    }
    return(0);
}

