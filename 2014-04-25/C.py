from random import randint

n = 100000
print 1
print n
print " ".join(map(str, [randint(1, 10 ** 12) for i in xrange(n)]))
