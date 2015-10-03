#include <cmath>
#include <cstdio>
#include <set>
#include <vector>
using namespace std;

vector<int> A;

const int N = 30500;
const int K = 505;
double D[K][N];

double fact(int n)
{
    double ans = 0;
    for (int i = 1; i <= n; i++)
        ans += log((double)i);
    return ans;
}


/*
 * 1 2 3 | 0
 * 2 1 3 | 1
 * 1 3 2 | 1                                        2
 * 2 3 1 | 2
 * 3 1 2 | 2
 * 3 2 1 | 3
*/

int main()
{
    fprintf(stderr, "sizeof(D) = %d\n", sizeof(D));
    int n, k;
    scanf("%d %d", &n, &k);

    if (k == n)
    {
        double tot = (k == 1) ? 0 : fact(n) - log(2.0);
        double ans;
        if ((n * (n - 1) / 2) % 2 == 1)
            ans = 0;
        else
            ans = exp(-tot);
        printf("%.12lf\n", ans);
        return 0;
    }
    else if (k == n - 1)
    {
        if (n > 30)
            printf("%.12lf\n", 0.0);
        else
        {
            int A[50], B[50];
            double tot = fact(n) - log(2.0);  
            if (n == 1)
                tot = 0;
            double en = 0;
            set<vector<int> > was;
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                {                                
                    #define eprintf(...) //fprintf(stderr, __VA_ARGS__)
                    eprintf("============\n%d %d\n", i, j);
                    if (j == n - i - 1 && i != 0)
                        continue;
                    int pt = 0;
                    for (int t = n - 1; t >= 0; t--)
                        if (t != j)
                            A[pt++] = t;
                    B[i] = j;
                    pt = 0;
                    for (int t = 0; t < n; t++)
                        if (t != i)
                            B[t] = A[pt++];
                    vector<int> BB(B, B + n);
                    if (was.find(BB) != was.end())
                        continue;
                    was.insert(BB);
                    for (int t = 0; t < n; t++)
                        eprintf("%d ", B[t]);
                    eprintf("\n");
                    int inv = 0;
                    int megainv = 0;
                    for (int a = 0; a < n; a++)
                        for (int b = 0; b < a; b++)
                            if (B[a] < B[b])   
                                inv++;
                    int mgin = 0;
                    for (int exc = 0; exc < n; exc++)
                    {
                        bool bad = false;
                        int lst = -1;
                        for (int t = 0; t < n; t++)
                        {
                            if (t == exc)
                                continue;
                            if (lst == -1)
                                lst = t;
                            else
                            {
                                if (B[lst] < B[t])
                                    bad = true;
                                lst = t;
                            }
                        }
                        if (!bad)
                            mgin++;
                    }
                    eprintf("%d %d\n", inv, mgin);
                    if (inv % 2 == 0)
                        en += mgin;
                }    
            printf("%.12lf\n", en / exp(tot));
        }
        return 0;
    }
    else if (k > 500)                                       
    {
        printf("%.12lf\n", 0.0);
        return 0;
    }
    for (int j = 0; j <= n; j++)
        D[1][j] = j;

    for (int i = 2; i <= k; i++)
    {
        D[i][0] = 0;
        double got = 0;
        for (int j = 1; j <= n; j++)
        {
            D[i][j] = D[i][j - 1];
            double sm = 0;
            got += D[i - 1][j - 1];
            //for (int t = 0; t < j; t++)
            //    sm += D[(3000000 + q - t) % 3][i - 1][t];
            D[i][j] += got / j;                
        }
    }
    
    printf("%.12lf", D[k][n]);

}                                                             