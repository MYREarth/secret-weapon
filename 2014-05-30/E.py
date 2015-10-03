from fractions import Fraction

def get_min(a, b):
    if a == -1:
        return b
    return min(a, b)

sqr = lambda x : x * x
while True:
    n, m = map(int, raw_input().split())
    if n == 0:
        break
    a = map(int, raw_input().split())
    l, r = map(int, raw_input().split())
    aa = 0
    for i in xrange(n):
        aa += Fraction(1, a[i])
    c = m / aa
    b = [c / a[i] for i in xrange(n)]
    minimum = [[-1] * (m + 1) for i in xrange(n + 1)]
    previous = [[-1] * (m + 1) for i in xrange(n + 1)]
    minimum[0][0] = 0
    for i in xrange(n):
        for j in xrange(m + 1):
            if minimum[i][j] != -1:
                for p in xrange(l, r + 1):
                    if j + p <= m:
                        if minimum[i + 1][j + p] == -1 or minimum[i][j] + sqr(b[i] - p) < minimum[i + 1][j + p]:
                            previous[i + 1][j + p] = p
                            minimum[i + 1][j + p] = minimum[i][j] + sqr(b[i] - p)
    assert previous[n][m] != -1
    results = [0 for i in xrange(n)]
    j = m
    for i in reversed(xrange(n)):
        results[i] = previous[i + 1][j]
        j -= previous[i + 1][j]
    print n, m
    print " ".join(map(str, a))
    print l, r
    print " ".join(map(str, results))
print 0, 0
