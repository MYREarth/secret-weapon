from sys    import argv
from random import randint

T = int(argv[1])
for _ in xrange(T):
    n = randint(1, int(argv[2]))
    m = randint(n, int(argv[3]))
    print n, m
    assert n <= m
    print " ".join(map(str, [randint(1, 18) for i in xrange(n)]))
    l = randint(1, m / n)
    r = max(l, randint((m + n - 1) / n, m))
    assert 1 <= l <= r <= m and l * n <= m <= r * n
    print l, r
print 0, 0

