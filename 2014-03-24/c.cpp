#include <cstdio>
#include <cstring>
typedef int matrix[110][110];
matrix zero,one,ans;
int m;
void init()
{
    for (int i=0;i<m;i++)
    {
        zero[i][i]=1;
        one[i][i]=i;
        one[i][(i+1)%m]=1;
    }
}
matrix d;
void multiply(matrix a,matrix b,matrix c)
{
    memset(d,0,sizeof(d));
    for (int i=0;i<m;i++)
        for (int j=0;j<m;j++)
            for (int k=0;k<m;k++)
                d[i][j]=(d[i][j]+a[i][k]*b[k][j])%m;
    memcpy(c,d,sizeof(d));
}
void power(int n)
{
    memcpy(ans,zero,sizeof(zero));
    for (;n;n>>=1)
    {
        if (n&1)
            multiply(ans,one,ans);
        multiply(one,one,one);
    }
}
int main()
{
    freopen("isomorphs.in","r",stdin);
    freopen("isomorphs.out","w",stdout);
    int n;
    scanf("%d%d",&n,&m);
    init();
    power(n);
    printf("%d\n",ans[0][0]);
    return(0);
}

