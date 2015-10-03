from random import randint
n, q = 100000, 200000
print n
for i in xrange(n):
    print i + 1, i + 2
print q
for i in xrange(q):
    print '?', randint(1, n), randint(1, n)
