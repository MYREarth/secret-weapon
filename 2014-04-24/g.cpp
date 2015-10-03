#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int N=1000010;
struct SA
{
    int n,a[N],sa[N],rank[N],height[N],rmq[20][N];
    static int Log[N];
    int f[N],x[N];
    void sort(int *a)
    {
        memset(f,0,sizeof(f));
        int t=0;
        for (int i=1;i<=n;i++)
        {
            f[a[i]]++;
            t=max(t,a[i]);
        }
        for (int i=1;i<=t;i++)
            f[i]+=f[i-1];
        for (int i=n;i;i--)
            x[f[a[sa[i]]]--]=sa[i];
        for (int i=1;i<=n;i++)
            sa[i]=x[i];
    }
    int count(int *a,int *b)
    {
        rank[sa[1]]=1;
        int t=1;
        for (int i=2;i<=n;i++)
        {
            if (a[sa[i]]!=a[sa[i-1]] || b[sa[i]]!=b[sa[i-1]])
                t++;
            rank[sa[i]]=t;
        }
        return(t);
    }
    int b[N],c[N];
    void build(int len,char *s)
    {
        n=len;
        for (int i=1;i<=n;i++)
            a[i]=s[i];
        a[n+1]=-1;
        for (int i=1;i<=n;i++)
        {
            c[i]=a[i];
            b[i]=-1;
            sa[i]=i;
        }
        sort(c);
        count(b,c);
        for (int k=1;;k<<=1)
        {
            for (int i=1;i<=n;i++)
            {
                c[i]=rank[i];
                b[i]=i+k<=n?rank[i+k]:0;
            }
            sort(b),sort(c);
            if (count(b,c)>=n)
                break;
        }
        int k=0;
        for (int i=1;i<=n;i++)
        {
            k=k?k-1:0;
            if (rank[i]==1)
            {
                height[rank[i]]=0;
                continue;
            }
            int p=sa[rank[i]-1],q=sa[rank[i]];
            while (a[p+k]==a[q+k])
                k++;
            height[rank[i]]=k;
        }
        for (int i=1;i<=n;i++)
            rmq[0][i]=height[i];
        for (int i=1;i<=Log[n];i++)
            for (int j=1;j<=n;j++)
            {
                if (j+(1<<i)-1>n)
                    break;
                rmq[i][j]=min(rmq[i-1][j],rmq[i-1][j+(1<<i-1)]);
            }
    }
    int query(int x,int y)
    {
        x=rank[x],y=rank[y];
        if (x>y)
            swap(x,y);
        int t=Log[y-x];
        return(min(rmq[t][x+1],rmq[t][y-(1<<t)+1]));
    }
};
int SA::Log[N];
char s[N];
SA a,b;
int main()
{
    scanf("%s",s+1);
    int len=strlen(s+1);
    SA::Log[1]=0;
    for (int i=2;i<=len;i++)
    {
        SA::Log[i]=SA::Log[i-1];
        if (i&i-1)
            continue;
        SA::Log[i]++;
    }
    a.build(len,s);
    reverse(s+1,s+len+1);
    b.build(len,s);
    return(0);
    int ans=1;
    for (int i=1;i<=len;i++)
        for (int j=i+1;j<=len;j+=i)
        {
            int suffix=a.query(j-i,j);
            int prefix=b.query(len-j+1,len-(j-i)+1);
            ans=max(ans,(suffix+prefix+i-1)/i);
        }
    printf("%d\n",ans);
    return(0);
}

