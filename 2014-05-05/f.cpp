#include <cstdio>
#include <map>
#define prev __prev__
using namespace std;
int a[100010],prev[100010],best[100010],f[110][100010],pre[110][100010][2];
bool first;
void print(int x,int y)
{
    if (x==1)
        return;
    print(pre[x][y][0],pre[x][y][1]);
    if (pre[x][y][0]+1==x)
    {
        if (!first)
            printf(" ");
        first=false;
        printf("%d",y-1);
    }
}
int main()
{
    freopen("funny.in","r",stdin);
    freopen("funny.out","w",stdout);
    while (1)
    {
        int n,m;
        scanf("%d%d",&n,&m);
        if (n==0 && m==0)
            break;
        map <int,int> M;
        for (int i=1;i<=n;i++)
        {
            scanf("%d",&a[i]);
            prev[i]=M[a[i]];
            M[a[i]]=i;
        }
        for (int i=1;i<=m;i++)
            for (int j=1;j<=n;j++)
                f[i][j]=-1<<30;
        for (int i=1;i<=n;i++)
            if (prev[i]==0)
                f[1][i]=1;
            else
                f[1][i]=f[1][prev[i]]+1;
        for (int i=2;i<=m;i++)
        {
            best[1]=1;
            for (int j=2;j<=n;j++)
                if (f[i-1][best[j-1]]>f[i-1][j])
                    best[j]=best[j-1];
                else
                    best[j]=j;
            for (int j=1;j<=n;j++)
            {
                if (j>1 && f[i-1][best[j-1]]+1>f[i][j])
                {
                    f[i][j]=f[i-1][best[j-1]]+1;
                    pre[i][j][0]=i-1;
                    pre[i][j][1]=best[j-1];
                }
                if (prev[j]!=0 && f[i][prev[j]]+1>f[i][j])
                {
                    f[i][j]=f[i][prev[j]]+1;
                    pre[i][j][0]=i;
                    pre[i][j][1]=prev[j];
                }
            }
        }
        int ans=1;
        for (int i=1;i<=n;i++)
            if (f[m][i]>f[m][ans])
                ans=i;
        printf("%d\n",f[m][ans]);
        first=true;
        print(m,ans);
        printf("\n");
    }
    return(0);
}

