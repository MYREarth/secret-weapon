#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 1000005;
char s[N];

int main() {
    scanf("%s", s);
    int l = strlen(s);
    if (l == 1) {
        int a = s[0] - '0';
        for (int i = 1; i <= a; ++i) {
            printf("%c", i + '0');
        }
        printf("\n");
    } else {
        int a = s[0] - '0', b = s[1] - '0', tag = 0;
        while (tag < l && s[tag] == s[0]) {
            ++tag;
        }
        if (a == 1 && b == 0) {
            printf("1023456789");
            for (int i = 0; i < l - 2; ++i) {
                printf("0123456789");
            }
            printf("\n");
        } else {
            if (tag == l || s[tag] > s[0]) {
                for (int i = 1; i <= a; ++i) {
                    printf("%c", i + '0');
                }
                for (int i = 0; i < l - 1; ++i) {
                    printf("0123456789");
                }
                printf("\n");
            } else {
                for (int i = 1; i < a; ++i) {
                    printf("%c", i + '0');
                }
                for (int j = 1; j < tag; ++j) {
                    if (j == 1) {
                        printf("%d", a);
                        for (int k = 0; k < a; ++k) {
                            printf("%c", '0' + k);
                        }
                    } else {
                        for (int k = 0; k < 10; ++k) {
                            printf("%c", '0' + (a + k) % 10);
                        }
                    }
                }
                for (int i = a + 1; i <= 9; ++i) {
                    printf("%c", i + '0');
                }
                int c = s[tag] - '0';
                for (int i = c + 1; i <= a; ++i) {
                    printf("%c", i + '0');
                }
                for (int i = 0; i <= c; ++i) {
                    printf("%c", i + '0');
                }
                for (int i = a + 1; i <= 9; ++i) {
                    printf("%c", i + '0');
                }
                for (int i = tag + 1; i < l; ++i) {
                    printf("0123456789");
                }
            }
        }
    }
    return 0;
}
