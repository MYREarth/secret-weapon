#include <cstdio>
#include <bitset>
using namespace std;
bitset <300> use[500010],assign[500010];
char buf[100000];
int IF[500010],ELSE[500010];
int main()
{
    int T;
    scanf("%d",&T);
    while (T--)
    {
        int n;
        scanf("%d",&n);
        if (n>300)
            return(1/0);
        gets(buf);
        int top=0,now=0;
        while (1)
        {
            now++;
            gets(buf);
            use[now]=use[now-1];
            assign[now]=assign[now-1];
            if (buf[0]=='a')
            {
                int x;
                sscanf(buf,"a %d",&x);
                assign[now].set(x-1);
            }
            else if (buf[0]=='u')
            {
                int x;
                sscanf(buf,"u %d",&x);
                if (!assign[now].test(x-1))
                    use[now].set(x-1);
            }
            else if (buf[0]=='i')
            {
                IF[++top]=now;
                ELSE[now]=0;
            }
            else if (buf[0]=='e' && buf[1]=='l')
            {
                ELSE[IF[top]]=now-1;
                use[now]=use[IF[top]];
                assign[now]=assign[IF[top]];
            }
            else if (top)
            {
                int x=IF[top--];
                if (!ELSE[x])
                {
                    use[now]|=use[x];
                    assign[now]=assign[x];
                }
                else
                {
                    int y=ELSE[x];
                    use[now]|=use[y];
                    assign[now]&=assign[y];
                }
            }
            else
                break;
        }
        for (int i=0;i<n;i++)
        {
            if (i)
                printf(" ");
            if (use[now].test(i))
                printf("1");
            else if (assign[now].test(i))
                printf("-1");
            else
                printf("0");
        }
        printf("\n");
    }
    return(0);
}

