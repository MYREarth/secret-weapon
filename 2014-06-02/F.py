from random import randint

print 2000
print " ".join(map(str, [randint(-1000, 1000) for i in xrange(2000)]))
