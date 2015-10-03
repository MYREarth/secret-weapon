#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

long long Sqrt(long long n,bool up)
{
    long long ret=sqrt((long double)n)-2;
    if (ret<0)
        ret=0;
    while (ret*ret<n)
        ret++;
    if (ret*ret==n || up)
        return(ret);
    return(ret-1);
}

int main() {
    long long a, b, p;
    scanf("%lld", &p);
    if (p % 4 == 1) {
        puts("YES");
    } else {
        puts("NO");
        return 0;
    }
    a = 1, b = Sqrt(p,false);
    long long s;
    while (true) {
        s = a * a + b * b;
        printf("%lld %lld\n",a,b);
        if (s == p) {
            break;
        } else if (s < p) {
            a = Sqrt(p - b * b,true);
        } else {
            b = Sqrt(p - a * a,false);
        }
    }
    printf("%lld %lld\n", a, b);
    return 0;
}

