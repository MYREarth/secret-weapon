#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
using namespace std;
int sg[110][110][110];
int calc(int i,int j,int k)
{
    if (sg[i][j][k]!=-1)
        return(sg[i][j][k]);
    int &ret=sg[i][j][k];
    bool vis[10]={0};
    if (i && j)
        vis[calc(i-1,j-1,k)]=true;
    if (i && k)
        vis[calc(i-1,j,k-1)]=true;
    if (j && k)
        vis[calc(i,j-1,k-1)]=true;
    for (int p=0;;p++)
        if (!vis[p])
            return(ret=p);
}
bool odd(int x)
{
    return(x&1);
}
bool solve(int i,int j,int k)
{
    if (i>j)
        swap(i,j);
    if (i>k)
        swap(i,k);
    if (j>k)
        swap(j,k);
    if (k>=i+j)
        k=i+j;
    if (!odd(i) && !odd(j) && !odd(k))
        return(false);
    if (odd(i)+odd(j)+odd(k)==2)
        return(true);
    int sum=i+j+k;
    return(sum%4!=1);
}
int main2()
{
    memset(sg,-1,sizeof(sg));
    int n;
    scanf("%d",&n);
    for (int i=0;i<=n;i++)
        for (int j=0;j<=n;j++)
            for (int k=0;k<=n;k++)
            {
                calc(i,j,k);
                printf("%d %d %d\n",i,j,k);
                assert((sg[i][j][k]>0)==solve(i,j,k));
            }
    return(0);
}
int main()
{
    int x,y,z;
    scanf("%d%d%d",&x,&y,&z);
    printf("%s\n",solve(x,y,z)?"Masha":"Petya");
    return(0);
}

