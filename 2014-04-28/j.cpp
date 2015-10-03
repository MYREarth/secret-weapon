#include <cstdio>
#include <cstring>
#include <string>
using namespace std;
char buf[1000000];
string a[20];
int delta[20][20],f[1100][20],pre[1100][20];
bool contain[20][20];
void work(int i,int j)
{
    contain[i][j]=a[i].find(a[j])!=string::npos;
    delta[i][j]=a[j].size();
    for (int k=0;k<a[i].size();k++)
    {
        int len=a[i].size()-k;
        if (a[i].substr(k)==a[j].substr(0,len))
        {
            delta[i][j]=a[j].size()-len;
            break;
        }
    }
}
void print(int x,int y)
{
    if (pre[x][y]==0)
    {
        printf("%s",a[y].c_str());
        return;
    }
    print(x^(1<<y-1),pre[x][y]);
    printf("%s",a[y].substr(a[y].size()-delta[pre[x][y]][y]).c_str());
}
int main()
{
    int len,n;
    scanf("%d%d",&len,&n);
    for (int i=1;i<=n;i++)
    {
        scanf("%s",buf);
        a[i]=buf;
    }
    for (int i=1;i<=n;i++)
        for (int j=1;j<=n;j++)
            work(i,j);
    memset(f,63,sizeof(f));
    int inf=f[0][0];
    for (int i=1;i<=n;i++)
        f[1<<i-1][i]=a[i].size();
    for (int i=0;i<1<<n;i++)
        for (int j=1;j<=n;j++)
        {
            if (f[i][j]==inf)
                continue;
            for (int k=1;k<=n;k++)
            {
                if (i>>k-1&1)
                    continue;
                if (f[i][j]+delta[j][k]<f[i|1<<k-1][k])
                {
                    f[i|1<<k-1][k]=f[i][j]+delta[j][k];
                    pre[i|1<<k-1][k]=j;
                }
            }
        }
    int best=0,x=0,y=0,l=0;
    for (int i=0;i<1<<n;i++)
    {
        int state=i;
        for (int j=1;j<=n;j++)
        {
            if (!(i>>j-1&1))
                continue;
            for (int k=1;k<=n;k++)
                if (contain[j][k])
                    state|=1<<k-1;
        }
        int now=__builtin_popcount(state);
        for (int j=1;j<=n;j++)
            if (f[i][j]<=len && now>best)
            {
                best=now;
                l=len-f[i][j];
                x=i;
                y=j;
            }
    }
    print(x,y);
    printf("%s\n",string(l,'a').c_str());
    return(0);
}

