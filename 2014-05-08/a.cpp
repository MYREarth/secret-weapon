#include <cstdio>
int pos[260],prev[1510],f[1510][1510],pre[1510][1510];
char a[1510];
void print(int x,int y)
{
    if (f[x][y]==0)
        return;
    int p=pre[x][y];
    if (p==-1)
        print(x,y-1);
    else
    {
        print(x,pre[x][y]-1);
        print(pre[x][y]+1,y-1);
        printf("%d %d\n",pre[x][y],y);
    }
}
int main()
{
    freopen("cable.in","r",stdin);
    freopen("cable.out","w",stdout);
    int n;
    scanf("%d%s",&n,a+1);
    for (int i=1;i<=n;i++)
    {
        prev[i]=pos[a[i]];
        pos[a[i]]=i;
    }
    for (int i=n;i;i--)
        for (int j=i+1;j<=n;j++)
        {
            f[i][j]=f[i][j-1];
            pre[i][j]=-1;
            for (int k=prev[j];k>=i;k=prev[k])
                if (f[i][k-1]+f[k+1][j-1]+1>f[i][j])
                {
                    f[i][j]=f[i][k-1]+f[k+1][j-1]+1;
                    pre[i][j]=k;
                }
        }
    printf("%d\n",f[1][n]);
    print(1,n);
    return(0);
}

