#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;
vector <int> strong[100010],weak[100010];
pair <int,int> a[100010];
int main()
{
    freopen("students.in","r",stdin);
    freopen("students.out","w",stdout);
    int K,n;
    scanf("%d%d",&K,&n);
    int m=2*K*n;
    for (int i=1;i<=m;i++)
        scanf("%d",&a[i].first);
    for (int i=1;i<=m;i++)
        scanf("%d",&a[i].second);
    sort(a+1,a+m+1);
    reverse(a+1,a+m+1);
    int t,l,r,ans;
    t=1,l=1,r=0,ans=0;
    for (int i=1;i<=m;i++)
        if (a[i].second==1)
            if (t<=n)
            {
                strong[t].push_back(a[i].first);
                ans++;
                if (strong[t].size()==K)
                {
                    r++;
                    t++;
                }
            }
            else
            {
                weak[l].push_back(a[i].first);
                if (weak[l].size()==K)
                    l++;
            }
        else if (l<=r)
        {
            ans++;
            weak[l].push_back(a[i].first);
            if (weak[l].size()==K)
                l++;
        }
        else
        {
            strong[t].push_back(a[i].first);
            if (strong[t].size()==K)
            {
                r++;
                t++;
            }
        }
    printf("%d\n",ans);
    for (int i=1;i<=n;i++)
    {
        for (int j=0;j<strong[i].size();j++)
            printf("%d ",strong[i][j]);
        for (int j=0;j<weak[i].size();j++)
            printf("%d%c",weak[i][j],j+1==weak[i].size()?'\n':' ');
    }
    return(0);
}

