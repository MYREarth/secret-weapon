#include <cstdio>
typedef long long ll;
struct polynomial
{
    int n,*a;
};
ll ans[10];
void init()
{

}
int main()
{
    init();
    while (1)
    {
        int n;
        scanf("%d",&n);
        if (n==0)
            break;
        static int id=0;
        printf("Case #%d: %lld\n",++id,ans[n]-ans[n-1]);
    }
    return(0);
}

