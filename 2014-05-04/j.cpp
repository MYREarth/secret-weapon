#include <cstdio>
#include <algorithm>
using namespace std;
int ans[110][110],pos[10010][2];
int main()
{
    while (1)
    {
        int n,m;
        scanf("%d%d",&n,&m);
        if (n==0 && m==0)
            break;
        for (int i=1;i<=n;i++)
            for (int j=1;j<=n;j++)
            {
                int x;
                scanf("%d",&x);
                pos[x][0]=i;
                pos[x][1]=j;
            }
        while (m--)
        {
            int x;
            scanf("%d",&x);
            if (abs(pos[x][0]-pos[0][0])+abs(pos[x][1]-pos[0][1])==1)
            {
                swap(pos[0][0],pos[x][0]);
                swap(pos[0][1],pos[x][1]);
            }
        }
        for (int i=0;i<n*n;i++)
            ans[pos[i][0]][pos[i][1]]=i;
        for (int i=1;i<=n;i++)
            for (int j=1;j<=n;j++)
                printf("%d%c",ans[i][j],i==n && j==n?'\n':' ');
    }
    return(0);
}

