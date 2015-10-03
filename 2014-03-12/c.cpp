#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;
const double pi=acos(-1.0),angle=5/180.0*pi,eps=1e-5;
struct point
{
    double x,y;
    point(){}
    point(double x,double y):x(x),y(y){}
    point rotate(double t)
    {
        return(point(x*cos(t)-y*sin(t),x*sin(t)+y*cos(t)));
    }
};
inline point operator +(const point &a,const point &b)
{
    return(point(a.x+b.x,a.y+b.y));
}
inline point operator -(const point &a,const point &b)
{
    return(point(a.x-b.x,a.y-b.y));
}
inline point operator *(const point &a,double b)
{
    return(point(a.x*b,a.y*b));
}
struct circle
{
    point o;
    int r;
    circle(const point &o,int r):o(o),r(r){}
    bool in(const point &p)
    {
        double x=o.x-p.x,y=o.y-p.y;
        return(x*x+y*y<=r*r);
    }
};
struct state
{
    point p;
    int level,dis,kind;
};
inline bool operator <(const state &a,const state &b)
{
    return(a.level<b.level || a.level==b.level && a.dis<b.dis);
}
vector <state> a;
void generate()
{
    for (int i=0;i<=20;i++)
        for (int j=0;j<=20;j++)
        {
            state now;
            now.p=point(i,j);
            now.level=min(min(i,j),min(20-i,20-j));
            if (i==now.level && j<=10)
            {
                now.dis=j-now.level;
                now.kind=0;
            }
            else if (j==now.level && i<=10)
            {
                now.dis=i-now.level;
                now.kind=1;
            }
            else if (j==now.level)
            {
                now.dis=20-now.level-i;
                now.kind=2;
            }
            else if (i==20-now.level && j<=10)
            {
                now.dis=j-now.level;
                now.kind=3;
            }
            else if (i==20-now.level)
            {
                now.dis=20-now.level-j;
                now.kind=4;
            }
            else if (j==20-now.level && i>=10)
            {
                now.dis=20-now.level-i;
                now.kind=5;
            }
            else if (j==20-now.level)
            {
                now.dis=i-now.level;
                now.kind=6;
            }
            else
            {
                now.dis=20-now.level-j;
                now.kind=7;
            }
            a.push_back(now);
        }
    sort(a.begin(),a.end());
}
vector <circle> ans,tmp;
int test(const point &p)
{
    int ret=0;
 /*   for (int i=0;i<tmp.size();i++)
        ret+=tmp[i].in(p);
    return(ret);*/
    printf("%.5f %.5f\n",p.x,p.y);
    fflush(stdout);
    scanf("%d",&ret);
    return(ret);
}
int calc(const point &p)
{
    int ret=0;
    for (int i=0;i<ans.size();i++)
        ret+=ans[i].in(p);
    return(ret);
}
point get(const state &now,int dis)
{
    if (now.kind==0 || now.kind==7)
        return(now.p+point(dis,0));
    else if (now.kind==1 || now.kind==2)
        return(now.p+point(0,dis));
    else if (now.kind==3 || now.kind==4)
        return(now.p-point(dis,0));
    else
        return(now.p-point(0,dis));
}
point work(const point &o,int r,int kind)
{
    if (kind==0)
        return(o+point(-1,0).rotate(angle)*(r-eps));
    else if (kind==1)
        return(o+point(0,-1).rotate(-angle)*(r-eps));
    else if (kind==2)
        return(o+point(0,-1).rotate(angle)*(r-eps));
    else if (kind==3)
        return(o+point(1,0).rotate(-angle)*(r-eps));
    else if (kind==4)
        return(o+point(1,0).rotate(angle)*(r-eps));
    else if (kind==5)
        return(o+point(0,1).rotate(-angle)*(r-eps));
    else if (kind==6)
        return(o+point(0,1).rotate(angle)*(r-eps));
    else
        return(o+point(-1,0).rotate(-angle)*(r-eps));
}
void query(const state &now)
{
    int num=test(now.p);
    if (num==calc(now.p))
        return;
    for (int i=now.dis;i;i--)
    {
        point o=get(now,i);
        int r=i;
        point p=work(o,r,now.kind);
        int num=test(p)-calc(p);
        for (int j=1;j<=num;j++)
            ans.push_back(circle(o,r));
    }
}
int main()
{
    generate();
   /* srand(324235123);
    int limit=2000;
    for (int i=1;i<=limit;i++)
    {
        int x=rand()%20+1,y=rand()%20+1,r=rand()%10+1;
        if (x>=r && y>=r && x+r<=20 && y+r<=20)
            tmp.push_back(circle(point(x,y),r));
    }*/
    for (int i=0;i<a.size();i++)
        query(a[i]);
    printf("Done %d\n",ans.size());
    //printf("%d\n",tmp.size());
    return(0);
}

