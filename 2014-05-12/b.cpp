#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
char a[500010];
int v[500010],c[500010];
queue <int> Q[26];
int main()
{
    int M,K;
    scanf("%d%d%s",&M,&K,a+1);
    int n=strlen(a+1);
    for (int i=1;i<=n;i++)
    {
        int x=a[i]-'a';
        Q[x].push(i);
        v[i]=v[i-1];
        c[i]=c[i-1];
        if (a[i]=='a' || a[i]=='e' || a[i]=='i' || a[i]=='o' || a[i]=='u')
            v[i]++;
        else
            c[i]++;
    }
    int t=0;
    while (1)
    {
        if (v[n]-v[t]<=M && c[n]-c[t]<=K)
        {
            printf("\n");
            break;
        }
        for (int i=0;i<26;i++)
        {
            while (!Q[i].empty() && Q[i].front()<t)
                Q[i].pop();
            if (Q[i].empty())
                continue;
            int x=Q[i].front();
            if (v[x-1]-v[t]<=M && c[x-1]-c[t]<=K)
            {
                printf("%c",i+'a');
                M-=v[x-1]-v[t];
                K-=c[x-1]-c[t];
                t=x;
                Q[i].pop();
                break;
            }
        }
    }
    return(0);
}

