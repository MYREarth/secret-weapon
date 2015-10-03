#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
using namespace std;
const int c[4][2]={{-1,0},{1,0},{0,-1},{0,1}};
const char way[]="UDLR";
int n,m,d[2010][2010],pre[2010][2010],q[4000010][2];
char a[2010][2010];
int main()
{
    freopen("matrix.in","r",stdin);
    freopen("matrix.out","w",stdout);
    scanf("%d%d",&m,&n);
    for (int i=1;i<=n;i++)
        scanf("%s",a[i]+1);
    int Sx,Sy,Tx,Ty;
    scanf("%d%d%d%d",&Sy,&Sx,&Ty,&Tx);
    int l,r;
    q[l=r=1][0]=Sx,q[1][1]=Sy;
    memset(d,-1,sizeof(d));
    d[Sx][Sy]=0;
    int now=-1;
    char best='z';
    while (l<=r)
    {
        if (d[q[l][0]][q[l][1]]!=now)
        {
            best='z';
            for (int i=l;i<=r;i++)
            {
                int x0=q[i][0],y0=q[i][1];
                for (int j=0;j<4;j++)
                {
                    int x=x0+c[j][0],y=y0+c[j][1];
                    if (x>0 && x<=n && y>0 && y<=m)
                        best=min(best,a[x][y]);
                }
            }
            now=d[q[l][0]][q[l][1]];
        }
        int x0=q[l][0],y0=q[l++][1];
        for (int i=0;i<4;i++)
        {
            int x=x0+c[i][0],y=y0+c[i][1];
            if (x>0 && x<=n && y>0 && y<=m && a[x][y]==best && d[x][y]==-1)
            {
                d[x][y]=d[x0][y0]+1;
                pre[x][y]=i;
                q[++r][0]=x;
                q[r][1]=y;
            }
        }
    }
    if (d[Tx][Ty]==-1)
        printf("BLUEPILL\n");
    else
    {
        string ans;
        while (Tx!=Sx || Ty!=Sy)
        {
            int t=pre[Tx][Ty];
            ans+=way[t];
            Tx-=c[t][0],Ty-=c[t][1];
        }
        reverse(ans.begin(),ans.end());
        printf("%s\n",ans.c_str());
    }
}

