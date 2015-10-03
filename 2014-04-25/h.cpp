#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
struct square
{
    int a[3],b[3];
    void in()
    {
        for (int i=0;i<3;i++)
            scanf("%d",&a[i]);
        for (int i=0;i<3;i++)
        {
            scanf("%d",&b[i]);
            if (a[i]>b[i])
                swap(a[i],b[i]);
        }
    }
    void change()
    {
        rotate(a,a+1,a+3);
        rotate(b,b+1,b+3);
    }
};
bool calc(const vector <square> &a,const vector <square> &b,int x,int y,int z)
{
    int xmin,xmax,ymin,ymax,zmin,zmax;
    xmax=zmax=ymin=1<<30;
    xmin=zmin=ymax=-1<<30;
    for (int i=0;i<a.size();i++)
    {
        int x1=a[i].a[x],x2=a[i].b[x],z1=a[i].a[z],z2=a[i].b[z],yy=a[i].a[y];
        ymin=min(ymin,yy);
        ymax=max(ymax,yy);
        xmin=max(xmin,x1);
        xmax=min(xmax,x2);
        zmin=max(zmin,z1);
        zmax=min(zmax,z2);
    }
    for (int i=0;i<b.size();i++)
    {
        int x1=b[i].a[x],x2=b[i].b[x],y1=b[i].a[y],y2=b[i].b[y],zz=b[i].a[z];
        if (y1<ymin && y2>ymax && zz>zmin && zz<zmax && (x1>xmin && x1<xmax || x2>xmin && x2<xmax))
            continue;
        return(false);
    }
    return(true);
}
int main()
{
    int T;
    scanf("%d",&T);
    while (T--)
    {
        int n;
        scanf("%d",&n);
        vector <square> a,b,c;
        for (int i=1;i<=n;i++)
        {
            square tmp;
            tmp.in();
            if (tmp.a[0]==tmp.b[0])
                a.push_back(tmp);
            else if (tmp.a[1]==tmp.b[1])
                b.push_back(tmp);
            else
                c.push_back(tmp);
        }
        bool flag=false;
        for (int _=0;_<3;_++)
        {
            if (!a.empty() && (!b.empty() || !c.empty()) && calc(a,b,2,0,1) && calc(a,c,1,0,2))
            {
                flag=true;
                break;
            }
            for (int i=0;i<a.size();i++)
                a[i].change();
            for (int i=0;i<b.size();i++)
                b[i].change();
            for (int i=0;i<c.size();i++)
                c[i].change();
            a.swap(b);
            b.swap(c);
        }
        printf("%s\n",flag?"YES":"NO");
    }
    return(0);
}

