#include <cstdio>
#include <algorithm>
using namespace std;
int a[5010],b[5010],c[5010],d[5010];
double f[5010],g[5010],dis[5010][5010];
double calc(int a,int b,int c,int d)
{
    if (a+b<=d)
        return(1);
    if (c+d<=b)
        return(0);
    return(double(c+d-b)/(a+c));
}
int main()
{
    freopen("braess.in","r",stdin);
    freopen("braess.out","w",stdout);
    int n;
    scanf("%d",&n);
    for (int i=1;i<=n;i++)
    {
        int A,B,C,D;
        scanf("%d%d%d%d",&A,&B,&C,&D);
        a[i]=a[i-1]+A;
        b[i]=b[i-1]+B;
        c[i]=c[i-1]+C;
        d[i]=d[i-1]+D;
    }
    for (int i=0;i<=n;i++)
        for (int j=i+1;j<=n;j++)
        {
            int A=a[j]-a[i],B=b[j]-b[i],C=c[j]-c[i],D=d[j]-d[i];
            double x=calc(A,B,C,D);
            dis[i][j]=min(A*x+B,C*(1-x)+D);
        }
    printf("%.10f\n",dis[0][n]);
    double sum=0;
    for (int i=1;i<=n;i++)
        sum+=dis[i-1][i];
    printf("%.10f\n",sum);
    for (int i=1;i<=n;i++)
    {
        f[i]=1e100;
        g[i]=-1e100;
        for (int j=0;j<i;j++)
        {
            f[i]=min(f[i],f[j]+dis[j][i]);
            g[i]=max(g[i],g[j]+dis[j][i]);
        }
    }
    printf("%.10f\n%.10f\n",f[n],g[n]);
    return(0);
}

