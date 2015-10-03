#include <cstdio>
#include <algorithm>
using namespace std;
int to[1000010],pos[1000010],a[2000010];
int main()
{
    int n;
    scanf("%d",&n);
    for (int i=1;i<=n;i++)
    {
        int x;
        scanf("%d",&x);
        to[x]=i;
    }
    for (int i=1;i<=n;i++)
    {
        int x;
        scanf("%d",&x);
        pos[to[x]]=i;
    }
    int start=n;
    for (int i=0;i<=n;i++)
        a[start+i]=i;
    for (int i=1;i<=n;i++)
    {
        int tmp=a[start+pos[i]];
        if (pos[i]==1)
            tmp=min(tmp,i);
        else
            tmp=min(tmp,a[start+pos[i]-2]+1);
        start--;
        a[start+pos[i]]=tmp;
    }
    printf("%d\n",a[n]+n);
    return(0);
}

