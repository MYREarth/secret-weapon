#include <cstdio>
#include <cstring>
int q[100010],d[100010],b[100010],a[200010][2];
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    for (int i=1;i<=m;i++)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        a[i][0]=y,a[i][1]=b[x],b[x]=i;
        a[i+m][0]=x,a[i+m][1]=b[y],b[y]=i+m;
    }
    int S,T;
    scanf("%d%d",&S,&T);
    int l,r;
    q[l=r=1]=S;
    memset(d,-1,sizeof(d));
    d[S]=0;
    while (l<=r)
    {
        int x=q[l++];
        for (int i=b[x];i;i=a[i][1])
        {
            int y=a[i][0];
            if (d[y]!=-1 || x==S && y==T || x==T && y==S)
                continue;
            d[y]=d[x]+1;
            q[++r]=y;
        }
    }
    if (d[T]==-1)
        printf("Infinity\n");
    else
        printf("%d\n",d[T]-1);
    return(0);
}

