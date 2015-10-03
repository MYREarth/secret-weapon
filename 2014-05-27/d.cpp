#include <cstdio>
int pos[1010],a[1010][1010],s[1010][1010];
int get(int x0,int y0,int x1,int y1)
{
    return(s[x1][y1]-s[x0-1][y1]-s[x1][y0-1]+s[x0-1][y0-1]);
}
bool work(int n)
{
    int ans=0;
    for (int i=1;i<=n;i++)
        for (int j=1;j<=n;j++)
            ans+=a[i][j];
    if (ans&1)
        return(false);
    ans>>=1;
    if (ans==0)
    {
        for (int i=1;i<=n;i++)
            pos[i]=0;
        return(true);
    }
    int sum=0;
    for (int j=1;j<=n;j++)
        for (int i=n;i;i--)
        {
            sum+=a[i][j];
            if (sum==ans)
            {
                for (int k=1;k<j;k++)
                    pos[k]=0;
                pos[j]=i-1;
                for (int k=j+1;k<=n;k++)
                    pos[k]=n;
                return(true);
            }
        }
    for (int i=1;i<=n;i++)
        for (int j=1;j<=n;j++)
            s[i][j]=s[i-1][j]+s[i][j-1]-s[i-1][j-1]+a[i][j];
    for (int i=1;i<=n;i++)
        for (int j=1;j<=n;j++)
        {
            if (a[i][j]!=1)
                continue;
            int sum=get(i,1,n,j);
            if (sum<=ans && sum+get(1,1,i-1,j-1)+get(i+1,j+1,n,n)>=ans)
            {
                for (int k=1;k<=j;k++)
                    pos[k]=i-1;
                for (int k=j+1;k<=n;k++)
                    pos[k]=n;
                if (sum!=ans)
                {
                    for (int y=1;y<j;y++)
                        for (int x=i-1;x;x--)
                        {
                            sum+=a[x][y];
                            pos[y]=x-1;
                            if (sum>=ans)
                                goto out;
                        }
                    for (int y=j+1;y<=n;y++)
                        for (int x=n;x>i;x--)
                        {
                            sum+=a[x][y];
                            pos[y]=x-1;
                            if (sum>=ans)
                                goto out;
                        }
                }
out:
                if (sum>ans)
                    pos[j]++;
                return(true);
            }
        }
    return(false);
}
int main()
{
    freopen("division.in","r",stdin);
    int T;
    scanf("%d",&T);
    while (T--)
    {
        int n;
        scanf("%d",&n);
        for (int i=1;i<=n;i++)
            for (int j=1;j<=n;j++)
                scanf("%d",&a[i][j]);
        if (!work(n))
            printf("IMPOSSIBLE\n");
        else
        {
            int now=0;
            for (int i=1;i<=n;i++)
            {
                while (now<pos[i])
                {
                    printf("S");
                    now++;
                }
                printf("E");
            }
            while (now<n)
            {
                printf("S");
                now++;
            }
            printf("\n");
        }
    }
    return(0);
}

