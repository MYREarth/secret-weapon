#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;
double f[110][100010];
int vis[110][100010];
int main()
{
    freopen("betting.in","r",stdin);
    freopen("betting.out","w",stdout);
    while (1)
    {
        int n,m,p,t;
        scanf("%d%d%d%d",&n,&m,&p,&t);
        if (n==0 && m==0 && p==0 && t==0)
            break;
        queue <pair <int,int> > Q;
        f[0][m]=1;
        static int id=0;
        vis[0][m]=++id;
        Q.push(make_pair(0,m));
        double ans=0;
        while (!Q.empty())
        {
            int i=Q.front().first,j=Q.front().second;
            Q.pop();
            int x=min(j,n-j);
            if (j==n)
                ans+=f[i][j];
            if (i<t && x!=0)
            {
                if (vis[i+1][j+x]!=id)
                {
                    vis[i+1][j+x]=id;
                    Q.push(make_pair(i+1,j+x));
                }
                f[i+1][j+x]+=f[i][j]*p/100.0;
                if (vis[i+1][j-x]!=id)
                {
                    vis[i+1][j-x]=id;
                    Q.push(make_pair(i+1,j-x));
                }
                f[i+1][j-x]+=f[i][j]*(100-p)/100.0;
            }
            f[i][j]=0;
        }
        printf("%.10f\n",ans);
    }
    return(0);
}

