#include <cstdio>
#include <map>
using namespace std;
int main()
{
    int n,K,ans=0;
    scanf("%d%d",&n,&K);
    for (int i=0;i<n;i++)
    {
        int now=1;
        for (int j=0;j<K;j++)
            now=now*i%n;
        if (now==i)
        {
            printf("%d\n",i);
            ans++;
        }
    }
    printf("%d\n",ans);
    return(0);
}

