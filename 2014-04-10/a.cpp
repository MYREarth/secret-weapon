#include <cstdio>
#include <algorithm>
using namespace std;
int main()
{
    int n;
    scanf("%d",&n);
    int ma=0,sum=0;
    for (int i=1;i<=n;i++)
    {
        int x;
        scanf("%d",&x);
        ma=max(ma,x);
        sum+=x;
    }
    if (n<3)
        printf("0\n");
    else
    {
        sum-=ma;
        if (2*sum<=ma)
            printf("%d\n",sum);
        else
            printf("%d\n",(sum+ma)/3);
    }
    return(0);
}

