#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;
int main()
{
    int n=100,m=50000;
    printf("%d %d\n",n,m);
    for (int i=1;i<=m;i++)
    {
        int from=rand()%n+1,to=rand()%n+1;
        int cnt=rand()%(n+1-max(from,to))+1;
        printf("%d %d %d\n",cnt,from,to);
    }
    return(0);
}

