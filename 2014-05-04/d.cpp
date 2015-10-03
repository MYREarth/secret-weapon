#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
const int N=500010;
int b[N],a[N*2][2];
bool block[N];
vector <int> ans;
int q[N],fa[N],son[N];
bool leaf[N],flag[N];
void bfs()
{
    int l,r;
    q[l=r=1]=1;
    while (l<=r)
    {
        int x=q[l++];
        leaf[x]=true;
        for (int i=b[x];i;i=a[i][1])
        {
            int y=a[i][0];
            if (y==fa[x])
                continue;
            leaf[x]=false;
            fa[y]=x;
            q[++r]=y;
        }
    }
    for (int i=r;i;i--)
    {
        int x=q[i],cnt=0;
        for (int i=b[x];i;i=a[i][1])
        {
            int y=a[i][0];
            if (y==fa[x])
                continue;
            if (!flag[y])
                flag[x]=false;
            if (!leaf[y])
            {
                cnt++;
                son[x]=y;
            }
        }
        if (cnt>1)
            flag[x]=false;
    }
}
void printleaf(vector <int> &ans,int x)
{
    for (int i=b[x];i;i=a[i][1])
    {
        int y=a[i][0];
        if (block[y] || !leaf[y])
            continue;
        ans.push_back(y);
    }
}
int list[N];
void print(int x,int pp)
{
    vector <int> tmp;
    int m=0;
    for (int i=x;i;i=son[i])
        list[++m]=i;
    if (m%2==1)
    {
        for (int i=1;i<m;i+=2)
        {
            int x=list[i];
            tmp.push_back(x);
            printleaf(tmp,son[x]);
        }
        tmp.push_back(list[m]);
        printleaf(tmp,list[m]);
        for (int i=m-1;i;i-=2)
        {
            int x=list[i];
            tmp.push_back(x);
            printleaf(tmp,fa[x]);
        }
    }
    else
    {
        for (int i=1;i<=m;i+=2)
        {
            int x=list[i];
            tmp.push_back(x);
            printleaf(tmp,son[x]);
        }
        for (int i=m;i;i-=2)
        {
            int x=list[i];
            tmp.push_back(x);
            printleaf(tmp,fa[x]);
        }
    }
    if (pp)
        reverse(tmp.begin(),tmp.end());
    ans.insert(ans.end(),tmp.begin(),tmp.end());
}
int to[N];
bool f[N],g[N];
bool work(int n)
{
    bfs();
    for (int i=n;i;i=fa[i])
    {
        block[i]=true;
        to[fa[i]]=i;
    }
    to[n]=0;
    if (leaf[n])
        f[n]=true;
    if (flag[n])
        g[n]=true;
    int x=fa[n],y=n;
    while (x)
    {
        int u=0,v=0;
        for (int i=b[x];i;i=a[i][1])
        {
            int z=a[i][0];
            if (block[z])
                continue;
            if (!flag[z])
                return(false);
            if (!leaf[z])
                u++;
            else
                v++;
        }
        if (u>2)
            return(false);
        if (u==0)
        {
            if (v>0)
                f[x]=f[y];
            else
                f[x]=f[y] || g[y];
            g[x]=f[y] || g[y];
        }
        else if (u==1)
        {
            f[x]=f[y];
            g[x]=f[y] || g[y];
        }
        else
        {
            f[x]=false;
            g[x]=f[y];
        }
    }
    if (!f[1])
        return(false);
    bool isF=true;
    x=1;
    while (1)
    {
        int y=to[x],u=0,v=0;
        for (int i=b[x];i;i=a[i][1])
        {
            int z=a[i][0];
            if (block[z])
                continue;
            if (!leaf[z])
                u++;
            else
                v++;
        }
        if (isF)
        {
            ans.push_back(x);
            if (u==0)
                if (v==0)
                {
                    if (f[y])
                    {
                        isF=true;
                        continue;
                    }
                    if (g[y])
                    {
                        isF=false;
                        continue;
                    }
                }
                else
                {
                    printleaf(ans,x);
                    isF=true;
                }
            else
            {
                int t;
                for (int i=b[x];i;i=a[i][1])
                {
                    int z=a[i][0];
                    if (!leaf[z])
                    {
                        t=z;
                        break;
                    }
                }
                print(t,1);
                printleaf(ans,x);
                isF=true;
            }
        }
        else if (u==0)
        {
            printleaf(ans,x);
            ans.push_back(x);
            if (f[y])
            {
                isF=true;
                continue;
            }
            if (g[y])
            {
                isF=false;
                continue;
            }
        }
        else if (u==1)
        {
            int t;
            for (int i=b[x];i;i=a[i][1])
            {
                int z=a[i][0];
                if (!leaf[z])
                {
                    t=z;
                    break;
                }
            }
            print(t,0);
            printleaf(ans,x);
            if (f[y])
            {
                isF=true;
                continue;
            }
            if (g[y])
            {
                isF=false;
                continue;
            }
        }
        else
        {
            int t1=0,t2;
            for (int i=b[x];i;i=a[i][1])
            {
                int z=a[i][0];
                if (t1==0)
                    t1=z;
                else
                {
                    t2=z;
                    break;
                }
            }
            print(t1,0);
            ans.push_back(x);
            print(t2,1);
            printleaf(ans,x);
            isF=true;
        }
        if (x==n)
            break;
        x=y;
    }
    for (int i=0;i<ans.size();i++)
        printf("%d\n",ans[i]);
    return(true);
}
int main()
{
    int n;
    scanf("%d",&n);
    for (int i=1;i<n;i++)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        a[i][0]=y,a[i][1]=b[x],b[x]=i;
        a[i+n][0]=x,a[i+n][1]=b[y],b[y]=i+n;
    }
    if (!work(n))
        printf("BRAK\n");
    return(0);
}

