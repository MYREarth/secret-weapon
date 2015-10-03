#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
struct point
{
    int x,y,z;
    point(){}
    point(int x,int y,int z):x(x),y(y),z(z){}
    void in()
    {
        scanf("%d%d%d",&x,&y,&z);
    }
    point nega() const
    {
        return(point(-x,-y,-z));
    }
    bool zero() const
    {
        return(x==0 && y==0 && z==0);
    }
};
inline ll dot(const point &a,const point &b)
{
    return(ll(a.x)*b.x+ll(a.y)*b.y+ll(a.z)*b.z);
}
inline point det(const point &a,const point &b)
{
    return(point(a.y*b.z-a.z*b.y,a.z*b.x-a.x*b.z,a.x*b.y-a.y*b.x));
}
inline ll mix(const point &a,const point &b,const point &c)
{
    return(dot(det(a,b),c));
}
inline bool side(const point &u,const point &v,const point &a)
{
    if (mix(u,v,a)!=0)
        return(mix(u,v,a)>0);
    return(dot(u,a)>0);
}
point u,v,a[1120],f[1120];
inline bool cmp(const point &a,const point &b)
{
    if (side(u,v,a)!=side(u,v,b))
        return(side(u,v,a)<side(u,v,b));
    return(side(a,v,b));
}
int main()
{
    int n;
    scanf("%d",&n);
    for (int i=1;i<=n;i++)
    {
        a[i].in();
        f[i].in();
        if (dot(a[i],f[i])<0)
            f[i]=f[i].nega();
    }
    int ans=0;
    for (int i=1;i<=n;i++)
    {
        int sum=0;
        vector <point> b;
        for (int j=1;j<=n;j++)
            if (det(f[i],f[j]).zero())
                sum+=dot(f[i],f[j])>0;
            else
                b.push_back(f[j]);
        if (b.empty())
        {
            ans=max(ans,sum);
            continue;
        }
        u=b[0],v=f[i];
        sort(b.begin(),b.end(),cmp);
        int m=b.size();
        for (int j=0;j<m;j++)
            b.push_back(b[j]);
        int t=0;
        for (int j=0;j<m;j++)
        {
            while (t<j+m && side(b[j],f[i],b[t]))
                t++;
            ans=max(ans,t-j+sum);
        }
    }
    printf("%d\n",ans);
}

