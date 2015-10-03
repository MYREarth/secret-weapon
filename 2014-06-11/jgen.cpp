#include <cstdio>
#include <cstdlib>
#include <ctime>
int main()
{
    FILE *out=fopen("J.in","w");
    srand(time(0));
    int t,n=10000;
    scanf("%d",&t);
    fprintf(out,"%d %d\n",t,n);
    for (int i=1;i<=n;i++)
        fprintf(out,"%d%c",/*rand()%(t-100)+100*/ rand() % 5 + 1,i==n?'\n':' ');
    fclose(out);
    system("time ./J <J.in");
    return(0);
}

