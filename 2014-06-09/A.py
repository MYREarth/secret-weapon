from random import randint
print 100000, 100000
print " ".join(map(str, [randint(1, 10000) for i in xrange(100000 + 1)]))
