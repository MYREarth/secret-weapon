#include <cstdio>
#include <cassert>
using namespace std;

#if ( _WIN32 || __WIN32__ || _WIN64 || __WIN64__ )
#define LLD "%I64d"
#else
#define LLD "%lld"
#endif


typedef long long llong;

inline llong C(llong a, llong b)
{
    return (a & b) == 0;
}

llong go(llong a, llong b)
{
    llong ans = 0;
    for (int i = 0; i < 62; i++)
        ans |= C(a + (1LL << i), b - (1LL << i)) << i;
    assert(ans >= 0);
    return ans;
}

int main()
{
    int T;
    scanf("%d", &T);
    for (int i = 0; i < T; i++)
    {
        llong x, y;
        scanf(LLD" "LLD, &x, &y);
        printf(LLD"\n", go(x, y));
    }
    return 0;

}
