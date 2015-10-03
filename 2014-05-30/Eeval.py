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
    p = map(int, raw_input().split())
    aa = 0
    for i in xrange(n):
        aa += Fraction(1, a[i])
    c = m / aa
    b = [c / a[i] for i in xrange(n)]
    result = 0
    for i in xrange(n):
        result += sqr(b[i] - p[i])
    print result
