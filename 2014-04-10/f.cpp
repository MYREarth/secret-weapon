#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int f[1500],a[1500];
char kind[1500];
inline void update(int &x,int y)
{
    if (x==-1 || y<x)
        x=y;
}
inline int price(int id)
{
    return(kind[id]=='U'?28:26);
}
int dp(int n,bool self)
{
    memset(f,-1,sizeof(f));
    f[1]=0;
    for (int i=1;i<=n;i++)
    {
        if (f[i]==-1)
            continue;
        if (self)
            update(f[i+1],f[i]+price(i));
        int sum=0,cnt=0;
        for (int j=i;;j++)
        {
            cnt+=kind[j]=='U';
            if (j==n+1 || cnt==2 || a[j]-a[i]>90)
            {
                update(f[j],f[i]+min(sum,44));
                break;
            }
            sum+=price(i);
        }
    }
    return(f[n+1]);
}
int main()
{
    int n;
    scanf("%d",&n);
    for (int i=1;i<=n;i++)
    {
        int x,y;
        scanf("%d:%d %c",&x,&y,&kind[i]);
        a[i]=x*60+y;
    }
    printf("%d %d\n",dp(n,false),dp(n,true));
    return(0);
}

