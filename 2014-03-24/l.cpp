#include <cstdio>
#include <cstdlib>
typedef long long ll;
const int c[4][2]={{-1,0},{1,0},{0,-1},{0,1}};
const int N=1<<24;
struct robot
{
    int x,y,dx,dy,n,a[300];
    bool x0,x1,y0,y1;
    void init()
    {
        dx=dy=0;
        for (int i=1;i<=n;i++)
        {
            int t=a[i];
            dx+=c[t][0];
            dy+=c[t][1];
        }
        x0=x1=y0=y1=true;
    }
    void move(int id)
    {
        int t=a[id];
        x+=c[t][0];
        y+=c[t][1];
    }
    void speed()
    {
        x+=dx;
        y+=dy;
    }
    bool board()
    {
        if (x<=256 && (x0 || dx!=0))
        {
            x0=false;
            return(true);
        }
        if (y<=256 && (y0 || dy!=0))
        {
            y0=false;
            return(true);
        }
        if (x>=N-255 && (x1 || dx!=0))
        {
            x1=false;
            return(true);
        }
        if (y>=N-255 && (y1 || dy!=0))
        {
            y1=false;
            return(true);
        }
        return(false);
    }
    bool out()
    {
        return(x<=0 || y<=0 || x>N || y>N);
    }
};
robot u,v;
char s[300];
inline int get(char ch)
{
    if (ch=='E')
        return(1);
    else if (ch=='W')
        return(0);
    else if (ch=='N')
        return(3);
    else
        return(2);
}
inline bool same()
{
    return(u.x==v.x && u.y==v.y);
}
inline bool check()
{
    return(u.board() || v.board() || abs(u.x-v.x)+abs(u.y-v.y)<=512 && (u.dx!=v.dx || u.dy!=v.dy));
}
inline void collide(ll T)
{
    printf("The two robots collide at time %lld.\n",T);
}
inline void fall(int i,ll T)
{
    if (i==0)
        printf("Both robots fall off the board at time %lld.\n",T);
    else
        printf("Robot %d falls off the board at time %lld.\n",i,T);
}
void work()
{
    ll ans=0;
    if (same())
    {
        collide(0);
        return;
    }
    bool first=true;
    while (1)
    {
        if (first || check())
        {
            first=false;
            for (int i=1;i<=u.n;i++)
            {
                u.move(i);
                v.move(i);
                ans++;
                if (u.out() && v.out())
                {
                    fall(0,ans);
                    return;
                }
                if (u.out())
                {
                    fall(1,ans);
                    return;
                }
                if (v.out())
                {
                    fall(2,ans);
                    return;
                }
                if (same())
                {
                    collide(ans);
                    return;
                }
            }
            continue;
        }
        ans+=u.n;
        u.speed();
        v.speed();
    }
}
int main()
{
    scanf("%d%d%d%d",&u.x,&u.y,&v.x,&v.y);
    u.x++,u.y++;
    v.x++,v.y++;
    scanf("%d",&u.n);
    v.n=u.n;
    scanf("%s",s+1);
    for (int i=1;i<=u.n;i++)
        u.a[i]=get(s[i]);
    scanf("%s",s+1);
    for (int i=1;i<=v.n;i++)
        v.a[i]=get(s[i]);
    u.init();
    v.init();
    work();
    return(0);
}

