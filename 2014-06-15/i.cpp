#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
int b[510],s[510],left[510],right[510],a[510][510];
ll get(int A,int B,int D,int n,int m)
{
    ll p=ll(D)*n*m,q=n*m-A*B;
    ll h=p/q;
    if (p%q==0)
        h--;
    return(h*A*B);
}
ll solve(int A,int B,int n,int m)
{
    A=min(A,n);
    B=min(B,m);
    ll ans=0;
    for (int i=1;i<=n;i++)
    {
        for (int j=1;j<=m;j++)
            b[j]=a[i][j];
        for (int j=i;j<=n;j++)
        {
            if (j-i+1>A)
                break;
            for (int k=1;k<=m;k++)
                b[k]=min(b[k],a[j][k]);
            int top=0;
            for (int k=1;k<=m;k++)
            {
                while (top && b[k]<=b[s[top]])
                    top--;
                s[++top]=k;
                left[k]=top==1?0:s[top-1];
            }
            top=0;
            for (int k=m;k;k--)
            {
                while (top && b[k]<=b[s[top]])
                    top--;
                s[++top]=k;
                right[k]=top==1?m+1:s[top-1];
            }
            for (int k=1;k<=m;k++)
            {
                int len=min(B,right[k]-left[k]-1);
                ans=max(ans,get(j-i+1,len,b[k],n,m));
            }
        }
    }
    return(ans);
}
int main()
{
    int A,B,n,m;
    scanf("%d%d%d%d",&A,&B,&n,&m);
    for (int i=1;i<=n;i++)
        for (int j=1;j<=m;j++)
            scanf("%d",&a[i][j]);
    printf("%lld\n",max(solve(A,B,n,m),solve(B,A,n,m)));
    return(0);
}

