#include <cstdio>
#include <cstring>
typedef long long ll;
int f[2010][2010][2][2];
ll a[2010];
int dp(int x,int y,int p,int q)
{
    if (f[x][y][p][q]!=-1)
        return(f[x][y][p][q]);
    int &ret=f[x][y][p][q];
    if (x==0 && y==0)
    {
        if (p<q)
            ret=0;
        else if (p==q)
            ret=1;
        else
            ret=2;
        return(ret);
    }
    ret=0;
    if (x)
    {
        int tmp=dp(x-1,y,q,p);
        if (tmp==0)
            return(ret=2);
        if (tmp==1)
            ret=1;
    }
    if (y)
    {
        int tmp=dp(x,y-1,q,p^1);
        if (tmp==0)
            return(ret=2);
        if (tmp==1)
            ret=1;
    }
    return(ret);
}
int calc(int n)
{
    for (int i=62;i>=0;i--)
    {
        int x=0,y=0;
        for (int j=1;j<=n;j++)
            if (a[j]>>i&1)
                y++;
            else
                x++;
        if (y%2==1)
        {
            memset(f,-1,sizeof(f));
            return(dp(x,y,0,0));
        }
    }
    return(1);
}
int main()
{
    int n;
    scanf("%d",&n);
    for (int i=1;i<=n;i++)
        scanf("%lld",&a[i]);
    int ans=calc(n);
    if (ans==0)
        printf("Second\n");
    else if (ans==1)
        printf("Draw\n");
    else
        printf("First\n");
    return(0);
}

