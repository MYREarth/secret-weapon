#include<cstdio>
#include<cstring>
using namespace std;

int main() {
    for (int i = 1; i <= 50000; ++i) {
        printf("buy 1000000 %d\n", 1000000000 - i);
        printf("sell 1000000 %d\n", i);
    }
    printf("end\n");
    return 0;
}
