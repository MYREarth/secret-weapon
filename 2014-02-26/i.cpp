#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
using namespace std;
char a[1510],b[1510];
int q[1510],L[1510],R[1510],Q[1510][1510],f[1510][1510],pre[1510][1510][2];
int main()
{
    freopen("strings.in","r",stdin);
    freopen("strings.out","w",stdout);
    int W;
    scanf("%d%s%s",&W,a+1,b+1);
    W++;
    int n=strlen(a+1),m=strlen(b+1);
    for (int i=1;i<=m;i++)
        L[i]=1,R[i]=0;
    int ans=0,ansx,ansy;
    for (int i=1;i<=n;i++)
    {
        int l=1,r=0;
        for (int j=1;j<=m;j++)
        {
            while (L[j]<=R[j] && Q[j][L[j]]<i-W)
                L[j]++;
            while (l<=r && q[l]<j-W)
                l++;
            f[i][j]=-1<<30;
            if (a[i]==b[j])
            {
                if (i<=W && j<=W)
                    f[i][j]=1;
                if (l<=r && f[Q[q[l]][L[q[l]]]][q[l]]+1>f[i][j])
                {
                    f[i][j]=f[Q[q[l]][L[q[l]]]][q[l]]+1;
                    pre[i][j][0]=Q[q[l]][L[q[l]]];
                    pre[i][j][1]=q[l];
                }
            }
            if (L[j]<=R[j])
            {
                while (l<=r && f[Q[j][L[j]]][j]>=f[Q[q[r]][L[q[r]]]][q[r]])
                    r--;
                q[++r]=j;
            }
        }
        for (int j=1;j<=m;j++)
        {
            while (L[j]<=R[j] && f[i][j]>=f[Q[j][R[j]]][j])
                R[j]--;
            Q[j][++R[j]]=i;
            if (f[i][j]>ans && n-i+1<=W && m-j+1<=W)
            {
                ans=f[i][j];
                ansx=i;
                ansy=j;
            }
        }
    }
    if (ans==0)
        printf("%s\n",n+1<=W && m+1<=W?"":"No solution");
    else
    {
        int x=ansx,y=ansy;
        string ans;
        while (1)
        {
            ans+=a[x];
            if (f[x][y]==1)
                break;
            int u=pre[x][y][0],v=pre[x][y][1];
            x=u,y=v;
        }
        reverse(ans.begin(),ans.end());
        printf("%s\n",ans.c_str());
    }
    return(0);
}

