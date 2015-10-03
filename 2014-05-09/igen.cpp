#include <cstdio>
#include <cstdlib>
const int inf=100000000;
int ran()
{
    return(rand()%(2*inf+1)-inf);
}
int main()
{
    FILE *out=fopen("II.in","w");
    int n=1000;
    int Q=1000;
    fprintf(out,"%d %d\n",n,Q);
    fprintf(out,"%d\n",rand()%inf+1);
    fprintf(out,"%d %d %d\n",ran(),ran(),ran());
    fprintf(out,"%d %d %d\n",ran(),ran(),ran());
    for (int i=0;i<=n;i++)
        fprintf(out,"%d %d\n",ran(),ran());
    fclose(out);
    system("make I");
    system("make i");
    system("./I <II.in >I.out");
    system("./i <II.in >i.out");
    system("diff I.out i.out");
    return(0);
}

