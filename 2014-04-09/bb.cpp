#include <cstdio>
typedef long long ll;
struct point
{
    int x,y;
};
point p[100010];
ll s[100010];
int main()
{
    int n;
    scanf("%d",&n);
    for (int i=1;i<=n;i++)
        scanf("%d%d",&a[i].x,&a[i].y);
    s[1]=0;
    for (int i=2;i<=n;i++)
        s[i]=s[i-1]+area(1,i-1,i);
    build(1,1,n);
    int Q;
    scanf("%d",&Q);
    while (Q--)
    {
        char op;
        scanf("%s",&op);
        if (op[0]=='-')
        {
            int x;
            scanf("%d",&x);
            int l=lower(x),r=upper(x);
            if (x<r)
            {
                modify(1,r,n,-area(l,x,r));
                del(1,x);
            }
        }
        if (op[0]=='+')
        {
            int x;
            scanf("%d",&x);
            int l=lower(x),r=upper(x);
            if (x<r)
            {
                modify(1,r,n,area(l,x,r));
                if (l<x)
                    add(1,x,query(1,l)+area(l,x,r));
                else
                    add(1,x,0);
            }
        }

