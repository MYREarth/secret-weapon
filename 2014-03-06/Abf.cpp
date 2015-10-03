const int N = 30;

int n, g[N], a[N];

int search(int i, int m) {
    if (i < n) {
        for (a[i] = 1; a[i] <= m; ++ a[i]) {
            search(i + 1, m - a[i]);
        }
    } else {
    }
}

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; ++ i) {
        scanf("%d", g + i);
    }
    int m;
    scanf("%d", &m);
    search(0, m);
    return 0;
}
