from random import randint

n = 5000
d = 10
print n, d
a = [randint(-100, 100) for i in xrange(d)]
for i in xrange(n):
    x = [randint(-100, 100) for i in xrange(d)]
    ret = 1 if sum(map(lambda p: p[0] * p[1], zip(a, x))) > 0 else -1
    print " ".join(map(str, x)), ret


