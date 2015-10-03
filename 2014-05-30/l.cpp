#include <cstdio>
int tot,l[200000][3],r[200000][3];
bool calc(int &x,int u,int v)
{
    if (u==0 || v==0)
        return(u==v);
    tot++;
    l[tot][2]=r[tot][2]=0;
    x=tot;
    if (!calc(l[x][2],l[u][0],l[v][1]))
    {
        if (r[u][0]!=0 && r[v][1]!=0)
        {
            tot++;
            l[tot][2]=r[tot][2]=0;
            r[x][2]=tot;
        }
        return(false);
    }
    return(calc(r[x][2],r[u][0],r[v][1]));
}
int main()
{
    freopen("lca.in","r",stdin);
    freopen("lca.out","w",stdout);
    while (1)
    {
        int n;
        scanf("%d",&n);
        if (n==0)
            break;
        for (int i=1;i<=n;i++)
            scanf("%d%d",&l[i][0],&r[i][0]);
        int m;
        scanf("%d",&m);
        for (int i=1;i<=m;i++)
            scanf("%d%d",&l[i][1],&r[i][1]);
        tot=0;
        calc(*new(int),1,1);
        printf("%d\n",tot);
        for (int i=1;i<=tot;i++)
            printf("%d %d\n",l[i][2],r[i][2]);
    }
    return(0);
}

