#include <cstdio>
#include <algorithm>
using namespace std;
int f[110][2],pre[110][2];
char a[10][110];
bool check(int x,char ch)
{
    for (int i=1;i<=5;i++)
        if (a[i][x]!=ch && a[i][x]!='?')
            return(false);
    return(true);
}
void update(int x,int y,int delta)
{
    if (f[x-delta][y^1]==0)
        return;
    pre[x][y]=delta;
    f[x][y]=min(26,f[x][y]+f[x-delta][y^1]);
}
void print(int x,int y)
{
    if (x==0)
        return;
    print(x-pre[x][y],y^1);
    printf("%d",pre[x][y]==2);
}
int main()
{
    int n;
    scanf("%d",&n);
    for (int i=1;i<=5;i++)
        scanf("%s",a[i]+1);
    f[0][0]=f[0][1]=1;
    for (int i=1;i<=n;i++)
    {
        if (check(i,'.'))
        {
            update(i,0,1);
            if (i>=2 && check(i-1,'.'))
                update(i,0,2);
        }
        if (check(i,'X'))
        {
            update(i,1,1);
            if (i>=2 && check(i-1,'X'))
                update(i,1,2);
        }
    }
    int ans=f[n][0]+f[n][1];
    if (ans!=1)
        printf("UNDETERMINABLE");
    else if (f[n][0]==1)
        print(n,0);
    else
        print(n,1);
    printf("\n");
    return(0);
}

