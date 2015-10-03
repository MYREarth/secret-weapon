#include <cstdio>
#include <cstring>
#include <cmath>
typedef long long ll;
const double pi=acos(-1.0);
const int mod=1000000009;
struct point
{
    double x,y;
    point(){}
    point(double x,double y):x(x),y(y){}
};
inline point operator +(const point &a,const point &b)
{
    return(point(a.x+b.x,a.y+b.y));
}
inline point operator *(const point &a,double b)
{
    return(point(a.x*b,a.y*b));
}
inline int sign(double x,double eps=1e-8)
{
    return(x<-eps?-1:x>eps);
}
point a[110];
int n,c[110][110],f[110][110];
bool vis[110][110];
inline int next(int x)
{
    return(x==n?1:x+1);
}
inline int prev(int x)
{
    return(x==1?n:x-1);
}
inline int num(int x,int y)
{
    if (x>y)
        y+=n;
    return(y-x+1);
}
int dp(int x,int y)
{
    if (!vis[x][y])
        return(0);
    if (x==y)
        return(1);
    if (f[x][y]!=-1)
        return(f[x][y]);
    int &ret=f[x][y];
    ret=0;
    ret=(dp(next(x),y)+dp(x,prev(y)))%mod;
    for (int i=next(x);i!=y;i=next(i))
        ret=(ret+ll(dp(x,prev(i)))*dp(next(i),y)%mod*c[num(x,y)-1][num(x,prev(i))])%mod;
    return(ret);
}
int main()
{
    double R,D;
    scanf("%d%lf%lf",&n,&R,&D);
    if (n==1)
        printf("1\n");
    else
    {
        double angle=pi*2/n;
        double dis=2*R*sin(angle/2)/3/(angle/2);
        for (int i=1;i<=n;i++)
        {
            double now=angle*(i-1)+angle/2;
            a[i]=point(cos(now),sin(now))*dis+point(0,D);
        }
        for (int i=1;i<=n;i++)
        {
            int j=i;
            point center(0,0);
            while (1)
            {
                center=center+a[j];
                vis[i][j]=sign(center.y)>=0;
                j=next(j);
                if (j==i)
                    break;
            }
        }
        for (int i=0;i<=n;i++)
        {
            c[i][0]=c[i][i]=1;
            for (int j=1;j<i;j++)
                c[i][j]=(c[i-1][j-1]+c[i-1][j])%mod;
        }
        int ans=0;
        memset(f,-1,sizeof(f));
        for (int i=1;i<=n;i++)
            ans=(ans+dp(next(i),prev(i)))%mod;
        printf("%d\n",ans);
    }
    return(0);
}

