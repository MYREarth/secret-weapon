#include <cstdio>
#include <vector>
using namespace std;
typedef long long ll;
const int p=1000003,mod=1000000007;
int first[160][160],second[160][160];
void init()
{
    const int n=150;
    for (int i=1;i<=n;i++)
    {
        first[i][0]=second[i][0]=1;
        for (int j=1;j<=n;j++)
        {
            first[i][j]=ll(first[i][j-1])*i%p;
            second[i][j]=ll(second[i][j-1])*i%mod;
        }
    }
}
vector <int> bucket[p];
int cnt[p*2];
int main()
{
    init();
    int x1,x2,a1,a2,y1,y2,b1,b2;
    scanf("%d%d%d%d%d%d%d%d",&x1,&x2,&a1,&a2,&y1,&y2,&b1,&b2);
    for (int x=x1;x<=x2;x++)
        for (int a=a1;a<=a2;a++)
            for (int y=y1;y<=y2;y++)
                for (int b=b1;b<=b2;b++)
                {
                    int tmp=first[x][a]+first[y][b];
                    cnt[tmp]++;
                }
    return(0);
}

