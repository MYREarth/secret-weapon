#include <cstdio>
#include <cstring>
bool vis[110];
int a[20];
bool check(int x,int n)
{
    memset(vis,0,sizeof(vis));
    for (int i=0;i<=x;i++)
    {
        int p=100*i/x,q=100*i%x;
        if (2*q>=x)
            p++;
        vis[p]=true;
    }
    for (int i=1;i<=n;i++)
        if (!vis[a[i]])
            return(false);
    return(true);
}
int main()
{
    int n;
    scanf("%d",&n);
    for (int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    for (int i=1;;i++)
        if (check(i,n))
        {
            printf("%d\n",i);
            break;
        }
    return(0);
}

