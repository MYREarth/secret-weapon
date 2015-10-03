#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
int b[110],a[10010][3];
double ans[110],result[110],value[110],coef[110][110];
void gauss(int n)
{
    double *a[110];
    for (int i=2;i<n;i++)
        a[i]=coef[i];
    for (int i=2;i<n;i++)
    {
        for (int j=i;j<n;j++)
            if (fabs(a[j][i])>fabs(a[i][i]))
            {
                swap(a[j][i],a[i][i]);
                swap(value[j],value[i]);
            }
        for (int j=2;j<n;j++)
        {
            if (i==j)
                continue;
            double t=a[j][i]/a[i][i];
            for (int k=i;k<n;k++)
                a[j][k]-=a[i][k]*t;
            value[j]-=value[i]*t;
        }
    }
    for (int i=2;i<n;i++)
        result[i]=value[i]/a[i][i];
}
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    for (int i=1;i<=m;i++)
    {
        int x,y,z;
        scanf("%d%d%d",&x,&y,&z);
        a[i][0]=y,a[i][1]=z,a[i][2]=b[x],b[x]=i;
        a[i+m][0]=x,a[i+m][1]=z,a[i+m][2]=b[y],b[y]=i+m;
    }
    for (int i=2;i<n;i++)
        for (int j=b[i];j;j=a[j][2])
        {
            int y=a[j][0];
            coef[i][i]--;
            if (y==1)
                continue;
            else if (y==n)
                value[i]--;
            else
                coef[i][y]++;
        }
    gauss(n);
    for (int i=2;i<n;i++)
        ans[i]=result[i];
    ans[1]=0;
    ans[n]=1;
    double upper=1e100;
    for (int i=1;i<=n;i++)
        for (int j=b[i];j;j=a[j][2])
        {
            int y=a[j][0];
            upper=min(upper,a[j][1]/fabs(ans[i]-ans[y]));
        }
    for (int i=1;i<=n;i++)
        ans[i]*=upper;
    double res=0;
    for (int i=b[n];i;i=a[i][2])
    {
        int y=a[i][0];
        res+=ans[n]-ans[y];
    }
    printf("%.10f\n",res);
    return(0);
}

