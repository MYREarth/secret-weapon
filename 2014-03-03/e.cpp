#include <cstdio>
#include <cstring>
#include <list>
#include <bitset>
using namespace std;
const int N=30000;
typedef bitset <N> Bitset;
char buf[100000];
int to[100010],q=0;
list <Bitset> Use,Assign;
Bitset use,assign;
int main()
{
    int T;
    scanf("%d",&T);
    while (T--)
    {
        int n;
        scanf("%d",&n);
        gets(buf);
        use.reset();
        assign.reset();
        memset(to,-1,sizeof(to));
        int m=0;
        while (1)
        {
            gets(buf);
            if (buf[0]=='a')
            {
                int x;
                sscanf(buf,"a %d",&x);
                if (to[x]==-1)
                {
                    to[x]=m++;
                    if (m>N)
                        return(1/q);
                }
                assign.set(to[x]);
            }
            else if (buf[0]=='u')
            {
                int x;
                sscanf(buf,"u %d",&x);
                if (to[x]==-1)
                {
                    to[x]=m++;
                    if (m>N)
                        return(1/q);
                }
                if (!assign.test(to[x]))
                    use.set(to[x]);
            }
            else if (buf[0]=='i')
            {
                Use.push_back(use);
                Assign.push_back(assign);
            }
            else if (buf[0]=='e' && buf[1]=='l')
            {
                swap(Use.back(),use);
                swap(Assign.back(),assign);
            }
            else if (!Use.empty())
            {
                use|=Use.back();
                assign&=Assign.back();
                Use.pop_back();
                Assign.pop_back();
            }
            else
                break;
        }
        for (int i=1;i<=n;i++)
        {
            if (i>1)
                printf(" ");
            if (to[i]==-1)
            {
                printf("0");
                continue;
            }
            int x=to[i];
            if (use.test(x))
                printf("1");
            else if (assign.test(x))
                printf("-1");
            else
                printf("0");
        }
        printf("\n");
    }
    return(0);
}

