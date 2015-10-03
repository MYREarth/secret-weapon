#include <cstdio>
#include <algorithm>
using namespace std;
int main()
{
    int n=1000;
    printf("%d\n",n);
    int a[1010];
    for (int i=1;i<=n;i++)
        a[i]=i;
    for (int _=1;_<=2;_++)
    {
        random_shuffle(a+1,a+n+1);
        for (int i=1;i<=n;i++)
            printf("%d ",a[i]);
        printf("\n");
    }
    return(0);
}

