#include <cstdio>
#include <cstring>
#include <string>
using namespace std;
char now[20];
int HP,fire[20],hp[20],pos[20],enter[20],delay[20],cost[20];
string ans[20];
int kill()
{
    for (int i=1;i<=10;i++)
    {
        delay[i]=0;
        pos[i]=0;
        enter[i]=i;
        hp[i]=HP;
    }
    for (int i=1;i<=10;i++)
    {
        if (now[i]!='S')
            continue;
        for (int j=i;j<=min(10,i+4);j++)
            delay[j]++;
    }
    for (int t=1;;t++)
    {
        bool flag=false;
        for (int i=1;i<=10;i++)
        {
            if (pos[i]==11 || hp[i]<=0)
                continue;
            flag=true;
            if (t==enter[i])
            {
                pos[i]++;
                enter[i]=t+delay[pos[i]]+1;
            }
            if (now[pos[i]]=='G' && fire[pos[i]]!=t)
            {
                fire[pos[i]]=t;
                hp[i]--;
            }
            else if (now[pos[i]]=='R' && t%3==0)
                hp[i]-=4;
        }
        if (!flag)
            break;
    }
    int ret=0;
    for (int i=1;i<=10;i++)
        ret+=hp[i]<=0;
    return(ret);
}
void dfs(int dep,int sum)
{
    if (dep==11)
    {
        int tmp=kill();
        if (sum<cost[tmp])
        {
            cost[tmp]=sum;
            ans[tmp]=now+1;
        }
        return;
    }
    now[dep]='.';
    dfs(dep+1,sum);
    now[dep]='G';
    dfs(dep+1,sum+3);
    now[dep]='R';
    dfs(dep+1,sum+10);
    now[dep]='S';
    dfs(dep+1,sum+5);
}
char buf[1000000];
int main()
{
    for (HP=1;HP<=30;HP++)
    {
        memset(cost,63,sizeof(cost));
        dfs(1,0);
        string tmp;
        for (int i=1;i<=10;i++)
        {
            bool flag=true;
            for (int j=i+1;j<=10;j++)
                if (cost[j]<=cost[i])
                {
                    flag=false;
                    break;
                }
            if (!flag || cost[i]==cost[11])
                continue;
            sprintf(buf,"$%d -> kill %d with %s\\n",cost[i],i,ans[i].c_str());
            tmp+=buf;
        }
        printf("%s,",tmp.c_str());
    }
    return(0);
}

