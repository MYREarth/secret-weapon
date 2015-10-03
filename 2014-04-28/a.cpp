#include <cstdio>
#include <algorithm>
using namespace std;
int ans[100010];
int main()
{
    int H,P,C,K,n;
    scanf("%d%d%d%d%d",&H,&P,&C,&K,&n);
    for (int i=1;i<=H;i++)
    {
        int t=min(n,P);
        n-=t;
        int color=(i-1)/K%C+1;
        ans[color]+=P-t;
    }
    for (int i=1;i<=C;i++)
        printf("%d%c",ans[i],i==C?'\n':' ');
    return(0);
}

